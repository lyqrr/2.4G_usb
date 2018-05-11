/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Lib_mySpring.c
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
Function:   	INT8U Lib_Cmp_TwoArry(INT8U* s1, INT8U* s2, INT8U len) 
Description: 	两个同样长度的字符串比较大小 
Input:		INT8U* s1   比较数组1首地址
			INT8U* s2   比较数组2首地址  
			INT8U len    数组长度
Parameters:     
Returns:		s1 > s2 时,OUT = 1
			s1 < s2 时,OUT = 255
			s1 == s2 时 ,OUT = 0
Others:	
****************************************************************/
INT8U Lib_Cmp_TwoArry(INT8U* s1, INT8U* s2, INT8U len) 
{
    INT8U i;
    
    s1=s1+(char)(len-1);
    s2=s2+(char)(len-1);
    for (i=0; i<len;i++)
    {
        if((*s1) > (*s2))  return (1);
        if((*s1) < (*s2))  return (255);
        s1--;
        s2--;
    }
    return (0);
}


/****************************************************************
Function:   	void  Lib_Rev_Copy_Arry(INT8U* s1, INT8U len) 
Description: 	实现自身数组顺序颠倒 
			such as   A0A1A2A3 ---> A3A2A1A0;
Input:		INT8U* s1   数组1首地址
			INT8U len    数组长度
Parameters:     
Returns:		no
Others:	
****************************************************************/
void  Lib_Rev_Copy_Arry(INT8U* s1, INT8U len) 
{
    INT8U tmpData;
    INT8U i = len/2;

    for(i=0; i<len/2;i++)
    {
        tmpData=  *(s1+i) ;
         *(s1+i) = *(s1+len-1-i);
         *(s1+len-1-i) = tmpData;   
    }
}


/****************************************************************
Function:   	void  Lib_Copy_Str_TwoArry(INT8U *s1, INT8U *s2, INT8U len) 
Description: 	将S2字符串按照原来顺序拷贝至S1数据串
Input:		INT8U* s1   目标数组首地址
			INT8U* s2   源数组首地址  
			INT8U len    数组长度
Parameters:     
Returns:		NO
Others:	
****************************************************************/
void  Lib_Copy_Str_TwoArry(INT8U *s1, INT8U *s2, INT16U len) 
{
    while(len > 0)
    {
        *s1 =*s2;
        s1++;
        s2++;
        len--;
    }
}


/****************************************************************
Function:   	void  Lib_Set_String(INT8U *s1, INT8U tmp, INT8U len) 
Description: 	将s1地址开始的len个数据设置为tmp值
Input:		INT8U* s1   目标数组首地址
			INT8U tmp   将要设定的数值  
			INT8U len    数组长度
Parameters:     
Returns:		NO
Others:	
****************************************************************/
void  Lib_Set_String(INT8U *s1, INT8U tmp, INT16U len) 
{
    while(len > 0)
    {
        *s1 =tmp;
        s1++;
        len--;
    }
}


/****************************************************************
Function:   	void  Lib_Clr_String_U16(INT16U *s1,  INT8U len) 
Description: 	将给定的字符串U16格式的数据清零
Input:		INT16U *s1   目标数组首地址，16位数据指针
			INT8U len    数组长度
Parameters:     
Returns:		NO
Others:	
****************************************************************/
void  Lib_Clr_String_U16(INT16U *s1,  INT16U len) 
{
    while(len > 0)
    {
        *s1 =0;
        s1++;
        len--;
    }
    
}

/****************************************************************
Function:   	void  Lib_Clr_String(INT8U *s1,  INT8U len) 
Description: 	将给定的字符串U16格式的数据清零//
Input:		INT8U *s1   目标数组首地址，8位数据指针
			INT8U len    数组长度
Parameters:     
Returns:		NO
Others:	
****************************************************************/
void  Lib_Clr_String(INT8U *s1,  INT16U len) 
{
    while(len > 0)
    {
        *s1 =0;
        s1++;
        len--;
    }
    
}


/***************************************************************
*    END
****************************************************************/


