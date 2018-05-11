/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Lib_myTimer.c
**Author: maji
**date: 
**description: c code for general library function 
**note: memer type  DJ04A
**--------------------Version History -------------------------------------
** NO.	Date        		Ver    		By     			Description 
**==============================================================
** 1		2014-07-08  		0.1  			sosomj   			1. frist version                             
**
**==============================================================
*/

#include "..\..\S6_MyIncludes\MyIncludes_H.h"


/****************************************************************
Function:		void Lib_Delay_Nop(uchar cnt)
Description:	��ʱCNT��NOP() 
Input:
Parameters:     
Returns:                                
Others:         
****************************************************************/
void Lib_Delay_Nop(uchar cnt)
{
	while(cnt--)
	{
		NOP();
	}
}

/****************************************************************
Function:   	void Lib_Delay2us(uint cnt)    
Description: 	CNT��2us��ʱ
Input:		cnt
Parameters:     
Returns:                                
Others:	��������: 8MHz   
****************************************************************/
void Lib_Delay_2us(uint cnt)  
{
	uint i;
	for(i=0;i<cnt;i++)
	{
		NOP();
	}
}

/****************************************************************
Function:   	void Lib_Delay_ms(uint cnt)   
Description: 	CNT��1ms��ʱ
Input:		cnt :��ʱ��Ӧ��ms
Parameters:     
Returns:                                
Others:	��������: 8MHz   
****************************************************************/
void Lib_Delay_ms(uint cnt)
{
	uint i;
	for(i=0;i<cnt;i++)
	{
		Lib_Delay_2us(210);
	}
}

/****************************************************************
Function:   	void Lib_Delay_sec(uint cnt)  
Description: 	CNT��s��ʱ
Input:		cnt :��ʱ��Ӧ��s
Parameters:     
Returns:                                
Others:	��������: 8MHz   
****************************************************************/
void Lib_Delay_sec(uint cnt)
{
	uint i;
	for(i=0;i<cnt;i++)
	{
		CLRWDT();
		Lib_Delay_ms(1000);
	}
}



/****************************************************************
Function:   	void SystemDelay(uint cnt)  
Description: 	����΢��˾�ṩ��ϵͳ��ʱ����,ÿ��ѭ����ʱԼ1ms
Input:		
Parameters:     
Returns:                                
Others:	
****************************************************************/
void Lib_SystemDelay(u16 t)
{
	u16 i;
	while(t--)
	{
		for (i = 0;i < 400;i++)
		  ;
		CLRWDT();
	}
}

/***************************************************************
*    END
****************************************************************/


