/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Prco_Data_H.H
**Author: maji
**date: 
**description:  define for  system function 
**note: memer type  "G80F903A_LSD4RF_2F717N01"
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-03-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/



#ifndef _PROC_DATA_H
#define _PROC_DATA_H

//******************************************************************
//              1     ������Ԥ����                                            //                      
//******************************************************************


//******************************************************************
//               2     ���ݽṹ����                                                 //
//******************************************************************
typedef struct 
{	
	INT8U	back_fg;                     // �ж��γɱ�ʶ //
	INT8U	font_fg;                     // �����������в�����ʶ //
	INT8U   ms_500cnt;
} SYS_RUN_STATUS;


//******************************************************************
//              3    ��������                                                             //
//******************************************************************
extern SYS_RUN_STATUS  gs_sys_run;

//******************************************************************
//             4     ��������                                                              //
//******************************************************************
extern void Proc_sys_data_init(void);

//******************************************************************
//             5     �������ݣ�����αָ���              //
//******************************************************************
//  gs_sys_run.font_fg define 
#define  BIT0_FONT_FG_10MS   BIT0   // 10ms �жϲ�����ʶ //
#define  BIT1_FONT_P17_500MS   BIT1   // 10ms �жϲ�����ʶ //

#endif
/***************************************************************
*    END
****************************************************************/

