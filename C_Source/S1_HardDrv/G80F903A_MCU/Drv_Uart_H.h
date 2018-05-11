/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Drv_ADC_H.H
**Author: maji
**date: 
**description:  define for MCU 定时器 驱动层
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
//              1     立即数预定义                                            
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
#define UART_STATUS_IDLE                    0                                                                    // 空闲状态 //
#define UART_STATUS_BUSY_RX            UART_STATUS_IDLE+1                   // 空闲状态 //
#define UART_STATUS_BUSY_RX_OVER       UART_STATUS_BUSY_RX+1    // 空闲状态 //
#define UART_STATUS_BUSY_TX            UART_STATUS_BUSY_RX_OVER+1    // 空闲状态 //
#define UART_STATUS_BUSY_TX_OVER       UART_STATUS_BUSY_TX+1    // 空闲状态 //
//******************************************************************
//               2     数据结构声明                             //
//******************************************************************
typedef struct 
{	
    INT8U  tx_len;                     // 串口发送数据长度//
    INT8U  rx_len;                     // 串口接收数据长度//
    INT8U  rx_buff_index;                 // 当前串口接收数据BUFF 指针下标 //
    INT8U  tx_buff_index;                 // 当前串口发送数据BUFF 指针下标 //
    INT8U  rx_time;                    // 接收有效定时 //
    INT8U  rx_over_ticks;              // 串口接收数据超时结束定时器，10mS基准  //
    INT8U  rx_buff[UART_BUFF_SIZE];    // 串口接收缓冲区 //
    INT8U  tx_buff[UART_BUFF_SIZE];    // 串口接收缓冲区 //
    INT8U  status;                     // 串口工作标识//
    INT16U badu;                       // 串口波特率 //
    INT8U  bits_len;                   // 串口位数 8或7 //
} UART_DRV_VAR;

//******************************************************************
//              3    变量声明                                    //
//******************************************************************
extern UART_DRV_VAR gs_uart_drv_var;

//******************************************************************
//             4     函数声明                                   //
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
//             5     其他内容，例如伪指令等              //
//******************************************************************



#endif

/***************************************************************
*    END
****************************************************************/

