/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: Drv_GPIO_H.H
**Author: maji
**date: 
**description:  define for MCU 的GPIO功能模块 驱动层
**note: memer type  SD03A
**--------------------Version History -------------------------------------
** NO.	Date        		Ver    		By     			Description 
**==============================================================
** 1		2015-10-27  		0.1  			sosomj   			1. frist version                             
**
**==============================================================
*/


#ifndef _Drv_GPIO_H
#define _Drv_GPIO_H

//******************************************************************
//              1     立即数预定义                                            
//                      
//******************************************************************
#define GPIO_MODE_OFF     1 // 低功耗 //
#define GPIO_MODE_ON	2 // 正常工作 //
#define GPIO_MODE_RESET	3  // 芯片复位状态 //

//******************************************************************
//               2     数据结构声明                             //
//******************************************************************


//******************************************************************
//              3    变量声明                                    //
//******************************************************************



//******************************************************************
//             4     函数声明                                   //
//******************************************************************
extern void Drv_GPIO_Init(INT8U mode);



//******************************************************************
//             5     其他内容，例如伪指令等              //
//******************************************************************

/*************************************************************
* MCU  PORT DEFINE 
**************************************************************/
/*
mcu= RN8213  B版本  100PIN
包含PA、PB、PC三组GPIO
PA口包含5个P0口、2个P1口、8个P2口、4个P3口
PB口包含8个P4口、8个P5口、8个P6口、8个P7口
PC口包含8个P8口、6个P9口、0个P10口、0个P11口
GPIO是AHB的外设
支持bitband操作
*/

/*
PA PORT  描述  PA口包含5个P0口、2个P1口、8个P2口、4个P3口

P0.0~4   
P00/AIN0/KEY2/RX2:     LED_ALARM_PIN
P01/AIN1/KEY3/TX2:     LED_ALARM1_PIN 
AIN2/CMP1/P02:         N/A
AIN3/CMP2/P03:         LVDIN_PIM
AIN4/LVDIN0/P04/KEY4:  N/A

P1.0~1
P10/KEY0/TC0_N[0]/TCIN:  KEY1_DIS_UP_PIN
P11/KEY1/TC0_P[0]/TCIN:  KEY2_DIS_DOWN_PIN

P2.0
P20/RX0        :N/A 
P21/TX0        :N/A 
P22/RX1        :RXD_IR_PIN 
P23/TX1        :TXD_IR_PIN 
SWDCLK/P24/RX2 :DEBUGE_SWDCLK_PIN
SWDIO/P25/TX2  :DEBUGE_SWDIO_PIN
P26/RX3        :RXD_EMU_RN8207C_PIN 
P27/TX3        :TXD_EMU_RN8207C_PIN 

P3.0,2,6,7
P30/INT0/TCIN            :DEBUGE_ISPCTR_PIN
P32/INT2/RTCOUT/KEY5     :RTC_1HZ_OUT_PIN
P36/INT6/HOSCO			 :  N/A
P37/INT7/HOSCI			 :  N/A
*/

#define LED_ALARM_PIN  (INT32U)0X00000001
#define PinWrite_AlarmLed(x)       ( (x) ? (GPIO->PA |= LED_ALARM_PIN , GPIO->PMA &= ~LED_ALARM_PIN) : (GPIO->PA &= ~LED_ALARM_PIN,GPIO->PMA &= ~LED_ALARM_PIN))	// p0.0
#define LED_ALARM1_PIN  (INT32U)0X00000002
#define PinWrite_Alarm1Led(x)       ( (x) ? (GPIO->PA |= LED_ALARM1_PIN , GPIO->PMA &= ~LED_ALARM1_PIN) : (GPIO->PA &= ~LED_ALARM1_PIN,GPIO->PMA &= ~LED_ALARM1_PIN))	// p0.1

#define KEY1_DIS_UP_PIN  (INT32U)0X00000100
#define PinRead_KeyDisUp()		((GPIO->PA&KEY1_DIS_UP_PIN) ? (0x01) : (0x00))		// p1.0
#define KEY2_DIS_DOWN_PIN  (INT32U)0X00000200
#define PinRead_KeyDisDn()		((GPIO->PA&KEY2_DIS_DOWN_PIN) ? (0x01) : (0x00))		// p1.1

/*
PB PORT  描述 PB口包含8个P4口、8个P5口、8个P6口、8个P7口
P4.0~7 
P40/7816CLK/INT1:       N/A
P41/78160_IO/INT3:      N/A
P42/78161_IO/INT4:     COVER_TEST_PIN
P43/78161_I/INT5:      TERMI_TEST_PIN
P44/SPI_SCSN/KEY6:     SPI_CS_PIN
P45/SPI_SCLK/KEY7:     SPI_CLK_PIN   
P46/SPI_MISO/RX4:      SPI_SDO_PIN
P47/SPI_MOSI/TX4:      SPI_SDI_PIN

P5.0~7 
P50/PF/RTCOUT/SF/QF:     AC_PLUSE_OUT_PIN
P51/QF/RTCOUT/PF/SF:     RE_PLUSE_OUT_PIN
P52/SCL/TCIN/TC0_N[1]:   I2C_BUS1_CLK_PIN
P53/SDA/TCIN/TC0_P[1]:   I2C_BUS2_SDA_PIN    //CAT24C256
P54/RX5/TCIN/TC1_N[0]:   I2C_BUS1_SDA_PIN   //FM24CL16 
P55/TX5/TCIN/TC1_P[0]:   N/A 
P56/ZXOUT/TCIN/TC1_N[1]: N/A
P57/SF/TCIN/TC1_P[1]:    N/A

P6.0~7 
P60/SEG4:   LCD_SEG_PIN
P61/SEG5:   LCD_SEG_PIN
P62/SEG6:   LCD_SEG_PIN
P63/SEG7:   LCD_SEG_PIN
P64/SEG8:   LCD_SEG_PIN
P65/SEG9:   LCD_SEG_PIN
P66/SEG10:  LCD_SEG_PIN
P67/SEG11:  LCD_SEG_PIN 

P7.0~7
P70/SEG12:   LCD_SEG_PIN
P71/SEG13:   LCD_SEG_PIN
P72/SEG14:   LCD_SEG_PIN
P73/SEG15:   LCD_SEG_PIN
P74/SEG16:   LCD_SEG_PIN
P75/SEG17:   LCD_SEG_PIN
P76/SEG18:   LCD_SEG_PIN
P77/SEG19:   LCD_SEG_PIN
*/

#define MAG_TEST_PIN  (INT32U)0X00000002
#define PinRead_TestMag()		((GPIO->PB&MAG_TEST_PIN) ? (0x01) : (0x00))		// p4.1
#define COVER_TEST_PIN  (INT32U)0X00000004
#define PinRead_TestCover()		((GPIO->PB&COVER_TEST_PIN) ? (0x01) : (0x00))		// p4.2
#define TERMI_TEST_PIN  (INT32U)0X00000008
#define PinRead_TestTemri()		((GPIO->PB&TERMI_TEST_PIN) ? (0x01) : (0x00))		// p4.3

#define AC_PLUSE_OUT_PIN  (INT32U)0X00000100
#define PinWrite_AcPluse(x)   ( (x) ? (GPIO->PB |= AC_PLUSE_OUT_PIN, GPIO->PMB &= ~AC_PLUSE_OUT_PIN) : (GPIO->PB &= ~AC_PLUSE_OUT_PIN,GPIO->PMB &= ~AC_PLUSE_OUT_PIN))	// p5.0
#define RE_PLUSE_OUT_PIN  (INT32U)0X00000200
#define PinWrite_RePluse(x)   ( (x) ? (GPIO->PB |= RE_PLUSE_OUT_PIN, GPIO->PMB &= ~RE_PLUSE_OUT_PIN) : (GPIO->PB &= ~RE_PLUSE_OUT_PIN,GPIO->PMB &= ~RE_PLUSE_OUT_PIN))	// p5.1

/*
PC PORT  描述 PC口包含8个P8口、6个P9口、0个P10口、0个P11口
P8.0~7
P80/SEG20:   LCD_SEG_PIN
P81/SEG21:   LCD_SEG_PIN
P82/SEG22:   LCD_SEG_PIN
P83/SEG23:   LCD_SEG_PIN
P84/SEG24:   N/A
P85/SEG25:   N/A
P86/SEG26:   N/A
P87/SEG27:   N/A

P9.0~5
P90/SEG28:   N/A
P91/SEG29:   N/A
P92/SEG30:   N/A
P93/SEG31:   N/A
P94/SEG32:   N/A
P95/SEG33:   CON_ADJB_PIN

*/

#define CON_ADJB_PIN  0X00002000
#define PinRead_ConAdjB()		((GPIO->PC&CON_ADJB_PIN) ? (0x01) : (0x00))		// p9.5



#endif

/***************************************************************
*    END
****************************************************************/

