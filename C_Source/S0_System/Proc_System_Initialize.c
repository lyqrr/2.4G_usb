/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Proc_System.c
**Author: maji
**date: 
**description: c code for system interlize function
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
void Proc_Target_Hard_Initialize(INT8U mode)
{

    //0 复位后的MCU常规初始化  //
    switch(mode)
    {
        case POWER_OFF:             // 低功耗主板硬件初始化  //

        break;


        case POWER_RESET:           //复位后的硬件常规初始化  //


            break;

        case POWER_ON:
        default:
            Drv_MainClock_Init();  // 初始化时钟 //
            Drv_GPIO_Init(GPIO_MODE_ON);    // 初始化IO口 //
            Drv_Timer_Init();   //定时器初始化  //    
	        //SX127x_init();
		    //Rx_mode(); 
			NRF24L01Int();
			NRFSetRXMode();
            break;
    }
	
}



/****************************************************************
Function:   		void SysInitialize(void)  
Description: 		系统上电/复位初始化函数 
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_INRam_Initialize(INT8U mode)
{
    switch(mode)
    {
        case POWER_ON:
            Proc_sys_data_init();

        break;

        case POWER_OFF:
        default:
      
            break;
    }	
}



/****************************************************************
Function:           void SysInitialize(void)  
Description:            系统上电/复位初始化函数 
Input:			no
Parameters:         	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_Sys_Initialize(void)
{
    Proc_Target_Hard_Initialize(POWER_ON);
    Proc_INRam_Initialize(POWER_ON);
    Lnk_User_Comm_INIT();  

}






/****************************************************************
Function:   		void sys_err(void)
Description: 		系统错误后的看门狗复位处理
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void sys_err(void)
{  
    CLRWDT();

    while(1)
    {
		NOP();
		NOP();
		NOP();
    }  
}



/***************************************************************
*    END
****************************************************************/

