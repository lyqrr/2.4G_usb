/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Main.c
**Author: maji
**date: 
**description: c code for main function
**note: memer type  "G80F903A_LSD4RF_2F717N01"
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2016-03-21   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/

#include <MyIncludes_H.h>

int i = 0;

/****************************************************************
Function:  		void main(void)   
Description: 		系统主函数
Input:
Parameters:     
Returns:                                
Others:         
****************************************************************/
void main(void)
{
	
    NOP();
    CLRWDT();     
    DisableINT();    				// disable interrupt function  //
    Proc_Sys_Initialize();  
    EnableINT();
    NOP();
    while(1)
    {
        CLRWDT();
        if(gs_sys_run.font_fg & BIT0_FONT_FG_10MS )
        {
            Drv_UART_10ms_run();
		//	NRF_Check();
			if(1){
			    NRFSetRXMode();
				NRFRevDate(&gs_uart_drv_var.tx_buff[0]);//接收数据
			}
			
		    if((gs_uart_iec_app_var.tx_ready_10ms ==0)&&(gs_uart_iec_app_var.tx_delay_flg ==TRUE))
		    {   
		        //数据准备发送   //
		        gs_uart_iec_app_var.tx_delay_flg =FALSE;
                Drv_UART_tx(gs_uart_drv_var.tx_buff[0]);       //    数据发送   // 
				//NRFSetRXMode(); 
		    }
            gs_sys_run.font_fg &=(~BIT0_FONT_FG_10MS) ;   
        }


//            LOAR_DIO0_HIGH();//LORA接收到数据点亮P1.7 
//            gs_sys_run.font_fg |= BIT1_FONT_P17_500MS;
			

		
//        if(LSD_RF_READ_DIO0()!=0)
//        {
//         LOAR_DIO0_HIGH();//LORA接收到数据点亮P1.7 
//         gs_sys_run.font_fg |= BIT1_FONT_P17_500MS;
//		 
//         LSD_RF_RxPacket(&gs_uart_drv_var.tx_buff[0]);  //RF接收数据//
//         gs_uart_drv_var.tx_len = G_LoRaConfig.PayloadLength ; 
//		 if((gs_uart_drv_var.tx_len==1)&&(gs_uart_drv_var.tx_buff[0]!=0x06))
//		 {
//	      CLRWDT();
//		 }
//		 gs_uart_iec_app_var.tx_ready_10ms =3;
// 		 gs_uart_iec_app_var.tx_delay_flg =TRUE;
//        }


    }

}




/***************************************************************
*    END
****************************************************************/

