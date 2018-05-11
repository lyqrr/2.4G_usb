/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Drv_GPIO.c
**Author: maji
**date: 
**description: c code for RN8213 ��GPIO����ģ�����������
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
0      0          ׼˫��ģʽ
0      1          �������
1      0          ��Ϊ����
1      1          ��©
*/

/*****************************************************************************
** Function name:	void Drv_GPIO_Init(INT8U mode)
**
** Description:		MCU ��GPIOģ����ؼĴ�����ʼ��
**
** Parameters:		mode��ʼ��ģʽ�֣�
**                  ==GPIO_MODE_ON����ʼ��Ϊ��������״̬�Ŀ������ģ��
**                  ==GPIO_MODE_OFF��Ƿ�ֵ����ʼ��Ϊ�͹���״̬�Ŀ������ģ��
**                  ==GPIO_MODE_RESET����ʼ��Ϊ��������״̬�Ŀ������ģ��
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
		case GPIO_MODE_ON:  // �е繩��������������µ�MCU�����ʼ��  //	

		 	/*p1.6 ��  TEN �͵�ƽ��Ч
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
		case GPIO_MODE_RESET:  // ��λ���MCU�����ʼ��  //	
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

		case GPIO_MODE_OFF:			//��ع�������µ�MCU��ʼ��  //		
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

