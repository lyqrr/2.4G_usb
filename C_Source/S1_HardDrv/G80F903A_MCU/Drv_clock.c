/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Drv_clock.c
**Author: maji
**date: 
**description: c code for G80F903A 的时钟信号处理
**note:  Driver code for GENERAL
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-04-24   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include "..\..\S6_MyIncludes\MyIncludes_H.h"



/*****************************************************************************
** Function name:	void Drv_MainClock_Init(void)
**
** Description:		
**
** Parameters:		NONE
**
** Returned value:	NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-13
******************************************************************************/
void Drv_MainClock_Init( void )
{
   uint8 i;

   CLKCON = Bin(00001000);        //打开内部RC
   for(i=0;i<32;i++);
   CLKCON = Bin(00001100);        //系统时钟=RC
}

/***************************************************************
*    END
****************************************************************/

