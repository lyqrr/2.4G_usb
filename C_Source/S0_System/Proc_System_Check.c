/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Proc_System_Check.c
**Author: maji
**date: 
**description: c code for system check function
**note: memer type  "G80F903A_LSD4RF_2F717N01"
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-03-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>


/****************************************************************
Function:   		void SysInitialize(void)  
Description: 		系统上电/复位初始化函数 
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_System_Check_Pre_Cycle(void)
{


	    
}



//-------------------------------------------------------------------------------//
//  Function:     BOOL Proc_Power_check(void)
//  Description:  系统AC电源状态检测函数
//  Parameters:   无  
//  Returns:      =SYS_RUN_FG_POWER_OFF, 掉电状态
//                =SYS_RUN_FG_POWER_ON, 上电状态
//  Others:   已经设计了 50*5次的滤波检测 
//-------------------------------------------------------------------------------//
//BOOL Proc_Power_check(void)
//{
//		;
//}





/***************************************************************
*    END
****************************************************************/

