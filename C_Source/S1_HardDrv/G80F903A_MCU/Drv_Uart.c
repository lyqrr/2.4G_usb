/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Drv_Uart.c
**Author: maji
**date: 
**description: c code for RN8213 的模拟AD模块驱动层程序
**note:  Driver code for GENERAL
**  UART3与单相计量芯片RN8207通讯，程序循环中查询处理
**  UART1与近红外通信接口通讯，采用中断接收发送处理
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
    // 波特率处理部分 //
    T2CON=Bin(00110000);                 //T2做UART0的收发波特率发生器//
    T2MOD=Bin(10000000);                 //选择系统时钟做为T2的时钟源//

    badu =  BPS9600;   
    TL2=LOBYTE(UART_BAUDRATE_9600);
    TH2=HIBYTE(UART_BAUDRATE_9600);
    RCAP2L=LOBYTE(UART_BAUDRATE_9600);
    RCAP2H=HIBYTE(UART_BAUDRATE_9600);    

    TR2=1;                               //T2起动//
    gs_uart_drv_var.badu = badu;

    // 数据位配置 //
    PCON =Bin(00000000);      
    if(bits_len == 7)
    {
           SCON =Bin(01000000);		         //选用模式1, 8位数据 异步 (data bit: 7数据位+ 1位校验位) 可变波特率 接收中断使能//
    }
    else
    {
        bits_len = 8;
        SCON =Bin(11000000);		         //选用模式3, 9位数据 异步(data bit: 8 数据位+ 1位校验位) 可变波特率 接收中断使能//
    }
    gs_uart_drv_var.bits_len = bits_len;

    REN=1;                           //打开串口0接收中断//
    ES0 =1;                          //使能UART0中断	//
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
** Description:	 // 关闭接收中断 //
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
    REN=0;                           //关闭串口接收中断//
}

/*****************************************************************************
** Function name:	u16 Drv_IR_UART1_badu_get(void)
**
** Description:	 // 获取当前串口波特率//
**
** Parameters:		NONE
**
** Returned value:	  当前串口波特率
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
** Description:	 // 获取当前串口工作状态//
**
** Parameters:		NONE
**
** Returned value:	  当前串口工作状态
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
	if(gs_uart_drv_var.rx_time>13) //130ms未接收到数据//
	{
	  if(gs_uart_drv_var.rx_len<1)   
	  return;    //接收的数据长度小于1

	  G_LoRaConfig.PayloadLength = gs_uart_drv_var.rx_len;
	  gs_uart_drv_var.rx_len=0;    //接收完成
	  gs_uart_drv_var.rx_buff_index = 0;
	  LOAR_DIO0_HIGH();//LORA接收到数据点亮P1.7 
	  gs_sys_run.font_fg |= BIT1_FONT_P17_500MS;
	  gs_uart_drv_var.tx_buff[0] = G_LoRaConfig.PayloadLength;
	  for(i=0;i<G_LoRaConfig.PayloadLength;i++)
	  {

	   gs_uart_drv_var.tx_buff[i+2] = gs_uart_drv_var.rx_buff[i];
	  }


		NRFSetTxMode(&gs_uart_drv_var.tx_buff[0], G_LoRaConfig.PayloadLength);//发送
		NRTxDate(&gs_uart_drv_var.tx_buff[0]);
	 
		//SX1276Reset();
	  	
	  
	}


}


/*****************************************************************************
** Function name:	  void Drv_IR_UART1_tx (u8 *p_buf, u8 len)
**
** Description:       串口1数据发送处理
**
** Parameters:     const u8 *p_buf:
**                      u8 len :发送数据字节长度        
**
** Returned value:	NONE
**
**NOTE:   发首个字节数据时调用   //
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
	// 8位数据处理方式 无校验//
	 ACC=(gs_uart_drv_var.tx_buff[0] &0xFF);
	}
	else 
	{
	// 8位数据处理方式 //
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

