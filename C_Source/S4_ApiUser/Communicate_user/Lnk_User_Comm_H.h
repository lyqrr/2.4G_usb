/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Lnk_User_Comm_H.H
**Author: maji
**date: 
**description:  用户通讯程序链路层相关声明文件
**note: memer type  SD03A
**--------------------Version History -------------------------------------
** NO.	Date        		Ver    		By     			Description 
**==============================================================
** 1    2015-10-21  		0.1  		sosomj   		1. frist version                             
**
**==============================================================
*/


#ifndef _Lnk_User_Comm_H
#define _Lnk_User_Comm_H


//******************************************************************
//              1     立即数预定义                                                                 
//******************************************************************
#define UART_BUFF_MAX_LENTH 64   //  //
///////////////
//  公共区//
///////////////
//IEC62056-21 操作字定义//
#define   IEC_COMM_END                                   0x00   //  //
#define   IEC_COMM_REQUEST                            '/'    //  //
#define   IEC_COMM_ACKNOWLEDGEMENT           0x06   // ACK //
#define   IEC_COMM_COMMAND                          0X01   // SOH  //

//  起始请求数据的固定字长定义  //
#define IEC_START_LENTH05   5      // no meter id
#define Meter_INFO_LENTH  16     //电表信息数组长度   //
#define MIMA_INFO_LENTH   10    // 电表密码标识数组长度 //

//C Mode BaudRate  固定为9600波特率
#define CBaud_3     '5'
#define	CBaud_6     '5'
#define	CBaud_12	'5'
#define	CBaud_24 	'5'
#define	CBaud_48	'5'
#define	CBaud_96 	'5'
#define	CBaud_192	'5'

//////////////////////////////////////
// IEC62056-21 C  特殊字符定义 //
//////////////////////////////////////
#define	SOH		0x01
#define	STX		0x02
#define	ETX		0x03
#define	EOT		0x04
#define	ENQ		0x05
#define	ACK		0x06
#define	BEL		0x07
#define	BS		0x08
#define	TAB		0x09
#define	LF		0x0A
#define	VT		0x0B
#define	FF		0x0C
#define	CR		0x0D
#define	SO		0x0E
#define	SI		0x0F
#define	DLE		0x10
#define	DC1		0x11
#define	DC2		0x12
#define	DC3		0x13
#define	DC4		0x14
#define	NAK		0x15
#define	SYN		0x16
#define	ETB		0x17
#define	CAN		0x18
#define	EM		0x19
#define	SUB		0x1A
#define	ESC		0x1B
#define	FS		0x1C
#define	GS		0x1D
#define	RS		0x1E
#define	US		0x1F

/////////////////////////////////
//security
////////////////////////////////
#define  mmok    0x00           //   权限判断正确
#define  mmover  0x01           // 密码超权限
#define  mmerr   0x02           //  密码错误
#define  keyoff  0x03            //   编程开关无效

//******************************************************************
//               2     数据结构声明                               
//******************************************************************
//通讯过程中的应用层变量数据 //
struct UART_COMM_APP_VAR
{
    INT8U                        len;                                      //接收发送帧数据长度//
    INT8U                        baud_rate;                             //通讯波特率暂存//
    INT8U                        err_flg;                                //链路层操作状态暂存//
    INT8U                        iec_status;                            //通讯模式//
    INT8U                        tx_ready_10ms;                  //  发送数据前的等待延时，默认120ms  //
    INT8U                        index_front_byte;                  // 前导字节长度寄存器 //
	INT16U                       delay_10ms;                         //  握手成功后的3S空闲等待复位延时寄存器    //
    INT8U                        tx_delay_flg;
} ;

//******************************************************************
//              3    变量声明                                      
//******************************************************************
extern struct UART_COMM_APP_VAR  gs_uart_iec_app_var;


//******************************************************************
//             4     函数声明                                      
//******************************************************************
extern void Lnk_User_Comm_INIT(void);
extern INT8U IEC_Comm_Acknowledgement_Cmd_Judge(INT8U* sptr,INT8U len);
extern void Lnk_process_iec62056_21 (void);
extern INT16U comm_IEC_Tx_Ready(void);
extern void IEC_Comm_10ms_run(void);

//******************************************************************
//             5     其他内容，例如伪指令等             
//******************************************************************

//uart_vomm_app_avr.err_flg define
#define  FRAME_ERROR     0X01     //帧错误，需要复位  //
#define  RF_ERROR     0X02     //帧错误，需要复位  //




#endif
/***************************************************************
*    END
****************************************************************/

