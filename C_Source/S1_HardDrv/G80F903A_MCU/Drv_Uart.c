/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Drv_Uart.c
**Author: maji
**date: 
**description: c code for RN8213 ��ģ��ADģ�����������
**note:  Driver code for GENERAL
**  UART3�뵥�����оƬRN8207ͨѶ������ѭ���в�ѯ����
**  UART1�������ͨ�Žӿ�ͨѶ�������жϽ��շ��ʹ���
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2015-10-27   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include "..\..\S6_MyIncludes\MyIncludes_H.h"

UART_DRV_VAR gs_uart_drv_var;

/*****************************************************************************
** Function name:	void Drv_IR_UART1_Hard_Init(u16 badu, u8 bits_len)
**
** Description:      uart1 for IR comm port  hard initlize ,  default 1bit stop,1bit even check 
**
** Parameters:		NONE
**
** Returned value:	NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-13
******************************************************************************/
void Drv_UART_Hard_Init(u16 badu, u8 bits_len)
{
    // �����ʴ����� //
    T2CON=Bin(00110000);                 //T2��UART0���շ������ʷ�����//
    T2MOD=Bin(10000000);                 //ѡ��ϵͳʱ����ΪT2��ʱ��Դ//

    badu =  BPS9600;   
    TL2=LOBYTE(UART_BAUDRATE_9600);
    TH2=HIBYTE(UART_BAUDRATE_9600);
    RCAP2L=LOBYTE(UART_BAUDRATE_9600);
    RCAP2H=HIBYTE(UART_BAUDRATE_9600);    

    TR2=1;                               //T2��//
    gs_uart_drv_var.badu = badu;

    // ����λ���� //
    PCON =Bin(00000000);      
    if(bits_len == 7)
    {
           SCON =Bin(01000000);		         //ѡ��ģʽ1, 8λ���� �첽 (data bit: 7����λ+ 1λУ��λ) �ɱ䲨���� �����ж�ʹ��//
    }
    else
    {
        bits_len = 8;
        SCON =Bin(11000000);		         //ѡ��ģʽ3, 9λ���� �첽(data bit: 8 ����λ+ 1λУ��λ) �ɱ䲨���� �����ж�ʹ��//
    }
    gs_uart_drv_var.bits_len = bits_len;

    REN=1;                           //�򿪴���0�����ж�//
    ES0 =1;                          //ʹ��UART0�ж�	//
}


/*****************************************************************************
** Function name:	void Drv_IR_UART1_Hard_Init(u16 badu, u8 bits_len)
**
** Description:      uart1 for IR comm port  hard initlize ,  default 1bit stop,1bit even check 
**
** Parameters:		NONE
**
** Returned value:	NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-13
******************************************************************************/
void Drv_UART_ram_Init(void)
{
INT8U i;
    //init mem
    gs_uart_drv_var.tx_len = 0;      //COMM_485_TX_LEN = 0 ;
    gs_uart_drv_var.rx_len = 0;      //COMM_485_TX_LEN = 0 ;
    gs_uart_drv_var.rx_buff_index = 0;  //    COMM_485_BUFF_INDEX = 0 ;
    gs_uart_drv_var.tx_buff_index = 0;  //    COMM_485_BUFF_INDEX = 0 ;
    gs_uart_drv_var.rx_time = 0;  //    COMM_485_BUFF_INDEX = 0 ;
    gs_uart_drv_var.rx_over_ticks = 0;   //COMM_485_RX_OVERTIME_TICKS = 0 ;
    for (i=0; i<UART_BUFF_SIZE; i++)
    {
        gs_uart_drv_var.rx_buff[i]=0; 
        gs_uart_drv_var.tx_buff[i]=0;    
    }
}



/*****************************************************************************
** Function name:	void Drv_IR_UART1_rx_dis(void)
**
** Description:	 // �رս����ж� //
**
** Parameters:		NONE
**
** Returned value:	NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-13
******************************************************************************/
void Drv_UART_rx_dis(void)
{
    REN=0;                           //�رմ��ڽ����ж�//
}

/*****************************************************************************
** Function name:	u16 Drv_IR_UART1_badu_get(void)
**
** Description:	 // ��ȡ��ǰ���ڲ�����//
**
** Parameters:		NONE
**
** Returned value:	  ��ǰ���ڲ�����
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-13
******************************************************************************/
u16 Drv_UART_badu_get(void)
{
    return (gs_uart_drv_var.badu);
}

/*****************************************************************************
** Function name:	u8 Drv_IR_UART1_status_get(void)
**
** Description:	 // ��ȡ��ǰ���ڹ���״̬//
**
** Parameters:		NONE
**
** Returned value:	  ��ǰ���ڹ���״̬
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-13
******************************************************************************/
u8 Drv_UART_status_get(void)
{
    return (gs_uart_drv_var.status);
}

/*****************************************************************************
** Function name:	void Drv_IR_UART1_10ms_run(void)
**
** Description:    uart1 pre 10ms handel code 
**
** Parameters:		NONE
**
** Returned value:	NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-13
******************************************************************************/
void Drv_UART_10ms_run(void)
{
    u8 i ;uchar buf1[5];uchar temp;
	gs_uart_drv_var.rx_time++;
	if(gs_uart_drv_var.rx_time>13) //130msδ���յ�����//
	{
	  if(gs_uart_drv_var.rx_len<1)   
	  return;    //���յ����ݳ���С��1

	  G_LoRaConfig.PayloadLength = gs_uart_drv_var.rx_len;
	  gs_uart_drv_var.rx_len=0;    //�������
	  gs_uart_drv_var.rx_buff_index = 0;
	  LOAR_DIO0_HIGH();//LORA���յ����ݵ���P1.7 
	  gs_sys_run.font_fg |= BIT1_FONT_P17_500MS;
	  gs_uart_drv_var.tx_buff[0] = G_LoRaConfig.PayloadLength;
	  for(i=0;i<G_LoRaConfig.PayloadLength;i++)
	  {

	   gs_uart_drv_var.tx_buff[i+2] = gs_uart_drv_var.rx_buff[i];
	  }


		NRFSetTxMode(&gs_uart_drv_var.tx_buff[0], G_LoRaConfig.PayloadLength);//����
		NRTxDate(&gs_uart_drv_var.tx_buff[0]);
	 
		//SX1276Reset();
	  	
	  
	}


}


/*****************************************************************************
** Function name:	  void Drv_IR_UART1_tx (u8 *p_buf, u8 len)
**
** Description:       ����1���ݷ��ʹ���
**
** Parameters:     const u8 *p_buf:
**                      u8 len :���������ֽڳ���        
**
** Returned value:	NONE
**
**NOTE:   ���׸��ֽ�����ʱ����   //
**----------------------------------------------------------------------------
** V01.01  MJ  2015-11-30
******************************************************************************/
void Drv_UART_tx ( u8 len)
{    
    
    uchar i = 0;
    if (len > UART_BUFF_SIZE)
    {
        len = UART_BUFF_SIZE ;
    }
	gs_uart_drv_var.tx_len = len;
	for(i = 0;i < len;i++)
	{
		gs_uart_drv_var.tx_buff[i] = gs_uart_drv_var.tx_buff[i+2];
	}
	if(gs_uart_drv_var.bits_len==7)
	{
	// 8λ���ݴ���ʽ ��У��//
	 ACC=(gs_uart_drv_var.tx_buff[0] &0xFF);
	}
	else 
	{
	// 8λ���ݴ���ʽ //
	ACC=(gs_uart_drv_var.tx_buff[0]);
	TB8=P;
	}
    SBUF=gs_uart_drv_var.tx_buff[0];
    //SBUF = gs_uart_drv_var.tx_len;
    gs_uart_drv_var.tx_buff_index++;
    gs_uart_drv_var.tx_len-- ;
}




/***************************************************************
*    END
****************************************************************/

