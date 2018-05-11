/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Drv_GPIO.c
**Author: maji
**date: 
**description: c code for RN8213 的GPIO功能模块驱动层程序
**note:  Driver code for GENERAL
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2015-10-28   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include "..\..\S6_MyIncludes\MyIncludes_H.h"



/*
PxM0  PxM1
0      0          准双向模式
0      1          推勉输出
1      0          仅为输入
1      1          开漏
*/

/*****************************************************************************
** Function name:	void Drv_GPIO_Init(INT8U mode)
**
** Description:		MCU 的GPIO模块相关寄存器初始化
**
** Parameters:		mode初始化模式字，
**                  ==GPIO_MODE_ON，初始化为正常工作状态的开启相关模块
**                  ==GPIO_MODE_OFF或非法值，初始化为低功耗状态的开启相关模块
**                  ==GPIO_MODE_RESET，初始化为正常工作状态的开启相关模块
**
** Returned value:	NONE
**
**----------------------------------------------------------------------------
** V01.01  MJ  2015-10-27
******************************************************************************/
void Drv_GPIO_Init(INT8U mode)
{
	switch(mode)
	{
		case GPIO_MODE_ON:  // 市电供电正常工作情况下的MCU常规初始化  //	

		 	/*p1.6 口  TEN 低电平有效
		 	*/
			P1  =Bin(10000000); 
			P1M0=Bin(10000011);
			P1M1=Bin(00111100);
			/*
			P3.2  CLK     CLK
			P3.3  NSS	  MOSO
			p3.4  MOSI    MOSI
			P3.5  MOSO    RST
			P3.7  RST	  NSS
			*/
			P3  =Bin(00000011);  
			P3M0=Bin(00010001);
			P3M1=Bin(11101110);

			P4  =Bin(00000000); 
			P4M0=Bin(00000000);
			P4M1=Bin(11111111);
			break;
			LSD_RF_SET_DIO0_DIR_IN();
		case GPIO_MODE_RESET:  // 复位后的MCU常规初始化  //	
			P1  =Bin(00000000); 
			P1M0=Bin(01000011);
			P1M1=Bin(10111100);

			P3  =Bin(00000011);  
			P3M0=Bin(00010001);
			P3M1=Bin(11101110);
				 
			P4  =Bin(00000000); 
			P4M0=Bin(00000000);
			P4M1=Bin(11111111);
			break;

		case GPIO_MODE_OFF:			//电池供电情况下的MCU初始化  //		
		default:
			P1  =Bin(00000000); 
			P1M0=Bin(01000011);
			P1M1=Bin(10111100);

			P3  =Bin(00000011);  
			P3M0=Bin(00010001);
			P3M1=Bin(11101110);
				 
			P4  =Bin(00000000); 
			P4M0=Bin(00000000);
			P4M1=Bin(11111111);
			break;
	}   
}



/***************************************************************
*    END
****************************************************************/

