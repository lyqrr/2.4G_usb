/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Lnk_User_Comm.c
**Author: maji
**date: 
**description: c code for 用户通讯程序链路层
**note:  Driver code for GENERAL
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2015-10-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include "..\..\S6_MyIncludes\MyIncludes_H.h"



struct UART_COMM_APP_VAR  gs_uart_iec_app_var;
u8g_t *P_IEC_BUFF; 


static __CODE const  INT8U meter_info[Meter_INFO_LENTH] = {'X','L','E','4','A','M','I','0','1','A','-','1','V','1','.','0',};

/*****************************************************************************
** Function name:	  void lnk_User_Comm_ram_INIT(void)
**
** Description:        
**
** Parameters:        NONE          
**
** Returned value:	NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-13
******************************************************************************/
void Lnk_User_Comm_INIT(void)
{
    gs_uart_iec_app_var.len = 0;
    gs_uart_iec_app_var.baud_rate = CBaud_96;
    gs_uart_iec_app_var.iec_status = 0;
    gs_uart_iec_app_var.err_flg = 0;
    gs_uart_iec_app_var.delay_10ms = 0;
    gs_uart_iec_app_var.tx_ready_10ms = 0;
    gs_uart_iec_app_var.index_front_byte = 0;
    gs_uart_iec_app_var.tx_delay_flg= FALSE;
    Drv_UART_ram_Init();
    Drv_UART_Hard_Init(BPS9600,7);

}

/***************************************************************
*    END
****************************************************************/

