/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Drv_ADC_H.H
**Author: maji
**date: 
**description:  define for MCU ��ʱ�� ������
**note: memer type  SD03A
**--------------------Version History -------------------------------------
** NO.	Date        		Ver    		By     			Description 
**==============================================================
** 1		2015-10-27  		0.1  			sosomj   			1. frist version                             
**
**==============================================================
*/


#ifndef _Drv_Uart_H
#define _Drv_Uart_H

//******************************************************************
//              1     ������Ԥ����                                            
//       
//******************************************************************			
#define     UART_BAUDRATE_300		         (65536-FSYSCLK/32UL/300UL)	
#define     UART_BAUDRATE_600		         (65536-FSYSCLK/32UL/600UL)	
#define	    UART_BAUDRATE_1200	         (65536-FSYSCLK/32UL/1200UL)	
#define     UART_BAUDRATE_2400            (65536-FSYSCLK/32UL/2400UL)	
#define     UART_BAUDRATE_4800            (65536-FSYSCLK/32UL/4800UL)	
#define     UART_BAUDRATE_9600            (65536-FSYSCLK/32UL/9600UL)	


#define BPS300     300
#define BPS600     600
#define BPS1200    1200
#define BPS2400    2400
#define BPS4800    4800
#define BPS9600    9600

//uart  data bits lenth  define 
#define UART_8BITS    8
#define UART_7BITS    7

//  //
#define UART_BUFF_SIZE   250

//UART_DRV_VAR. status define  //
#define UART_STATUS_IDLE                    0                                                                    // ����״̬ //
#define UART_STATUS_BUSY_RX            UART_STATUS_IDLE+1                   // ����״̬ //
#define UART_STATUS_BUSY_RX_OVER       UART_STATUS_BUSY_RX+1    // ����״̬ //
#define UART_STATUS_BUSY_TX            UART_STATUS_BUSY_RX_OVER+1    // ����״̬ //
#define UART_STATUS_BUSY_TX_OVER       UART_STATUS_BUSY_TX+1    // ����״̬ //
//******************************************************************
//               2     ���ݽṹ����                             //
//******************************************************************
typedef struct 
{	
    INT8U  tx_len;                     // ���ڷ������ݳ���//
    INT8U  rx_len;                     // ���ڽ������ݳ���//
    INT8U  rx_buff_index;                 // ��ǰ���ڽ�������BUFF ָ���±� //
    INT8U  tx_buff_index;                 // ��ǰ���ڷ�������BUFF ָ���±� //
    INT8U  rx_time;                    // ������Ч��ʱ //
    INT8U  rx_over_ticks;              // ���ڽ������ݳ�ʱ������ʱ����10mS��׼  //
    INT8U  rx_buff[UART_BUFF_SIZE];    // ���ڽ��ջ����� //
    INT8U  tx_buff[UART_BUFF_SIZE];    // ���ڽ��ջ����� //
    INT8U  status;                     // ���ڹ�����ʶ//
    INT16U badu;                       // ���ڲ����� //
    INT8U  bits_len;                   // ����λ�� 8��7 //
} UART_DRV_VAR;

//******************************************************************
//              3    ��������                                    //
//******************************************************************
extern UART_DRV_VAR gs_uart_drv_var;

//******************************************************************
//             4     ��������                                   //
//******************************************************************
extern void Drv_UART_Hard_Init(u16 badu, u8 bits_len);
extern void Drv_UART_rx_dis(void);
extern u16 Drv_UART_badu_get(void);
extern u8 Drv_UART_status_get(void);
extern void Drv_UART_10ms_run(void);
extern void Drv_UART_tx (u8 len);
extern u8 Drv_UART_get_rx_buff (u8 **p_buf);
extern void Drv_UART_ram_Init(void);

//******************************************************************
//             5     �������ݣ�����αָ���              //
//******************************************************************



#endif

/***************************************************************
*    END
****************************************************************/

