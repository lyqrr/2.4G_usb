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
Description: 		ϵͳ�ϵ�/��λ��ʼ������ 
Input:			no
Parameters:     	no
Returns:			no                        
Others:         
****************************************************************/
void Proc_Target_Hard_Initialize(INT8U mode)
{

    //0 ��λ���MCU�����ʼ��  //
    switch(mode)
    {
        case POWER_OFF:             // �͹�������Ӳ����ʼ��  //

        break;


        case POWER_RESET:           //��λ���Ӳ�������ʼ��  //


            break;

        case POWER_ON:
        default:
            Drv_MainClock_Init();  // ��ʼ��ʱ�� //
            Drv_GPIO_Init(GPIO_MODE_ON);    // ��ʼ��IO�� //
            Drv_Timer_Init();   //��ʱ����ʼ��  //    
	        //SX127x_init();
		    //Rx_mode(); 
			NRF24L01Int();
			NRFSetRXMode();
            break;
    }
	
}



/****************************************************************
Function:   		void SysInitialize(void)  
Description: 		ϵͳ�ϵ�/��λ��ʼ������ 
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
Description:            ϵͳ�ϵ�/��λ��ʼ������ 
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
Description: 		ϵͳ�����Ŀ��Ź���λ����
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

