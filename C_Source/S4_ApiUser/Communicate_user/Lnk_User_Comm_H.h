/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Lnk_User_Comm_H.H
**Author: maji
**date: 
**description:  �û�ͨѶ������·����������ļ�
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
//              1     ������Ԥ����                                                                 
//******************************************************************
#define UART_BUFF_MAX_LENTH 64   //  //
///////////////
//  ������//
///////////////
//IEC62056-21 �����ֶ���//
#define   IEC_COMM_END                                   0x00   //  //
#define   IEC_COMM_REQUEST                            '/'    //  //
#define   IEC_COMM_ACKNOWLEDGEMENT           0x06   // ACK //
#define   IEC_COMM_COMMAND                          0X01   // SOH  //

//  ��ʼ�������ݵĹ̶��ֳ�����  //
#define IEC_START_LENTH05   5      // no meter id
#define Meter_INFO_LENTH  16     //�����Ϣ���鳤��   //
#define MIMA_INFO_LENTH   10    // ��������ʶ���鳤�� //

//C Mode BaudRate  �̶�Ϊ9600������
#define CBaud_3     '5'
#define	CBaud_6     '5'
#define	CBaud_12	'5'
#define	CBaud_24 	'5'
#define	CBaud_48	'5'
#define	CBaud_96 	'5'
#define	CBaud_192	'5'

//////////////////////////////////////
// IEC62056-21 C  �����ַ����� //
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
#define  mmok    0x00           //   Ȩ���ж���ȷ
#define  mmover  0x01           // ���볬Ȩ��
#define  mmerr   0x02           //  �������
#define  keyoff  0x03            //   ��̿�����Ч

//******************************************************************
//               2     ���ݽṹ����                               
//******************************************************************
//ͨѶ�����е�Ӧ�ò�������� //
struct UART_COMM_APP_VAR
{
    INT8U                        len;                                      //���շ���֡���ݳ���//
    INT8U                        baud_rate;                             //ͨѶ�������ݴ�//
    INT8U                        err_flg;                                //��·�����״̬�ݴ�//
    INT8U                        iec_status;                            //ͨѶģʽ//
    INT8U                        tx_ready_10ms;                  //  ��������ǰ�ĵȴ���ʱ��Ĭ��120ms  //
    INT8U                        index_front_byte;                  // ǰ���ֽڳ��ȼĴ��� //
	INT16U                       delay_10ms;                         //  ���ֳɹ����3S���еȴ���λ��ʱ�Ĵ���    //
    INT8U                        tx_delay_flg;
} ;

//******************************************************************
//              3    ��������                                      
//******************************************************************
extern struct UART_COMM_APP_VAR  gs_uart_iec_app_var;


//******************************************************************
//             4     ��������                                      
//******************************************************************
extern void Lnk_User_Comm_INIT(void);
extern INT8U IEC_Comm_Acknowledgement_Cmd_Judge(INT8U* sptr,INT8U len);
extern void Lnk_process_iec62056_21 (void);
extern INT16U comm_IEC_Tx_Ready(void);
extern void IEC_Comm_10ms_run(void);

//******************************************************************
//             5     �������ݣ�����αָ���             
//******************************************************************

//uart_vomm_app_avr.err_flg define
#define  FRAME_ERROR     0X01     //֡������Ҫ��λ  //
#define  RF_ERROR     0X02     //֡������Ҫ��λ  //




#endif
/***************************************************************
*    END
****************************************************************/

