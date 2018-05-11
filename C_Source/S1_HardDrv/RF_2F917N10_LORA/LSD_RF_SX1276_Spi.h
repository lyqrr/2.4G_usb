/*******************************************************************
* Copyright (c) 2009,     HXGROUP
* All rights reserved.
* 
* 文件名称：spiSoft.h
* 摘    要：      soft spi 函数模块声明
*            
* 应用系统：
*
* 版本号：    1.0   作者：zwk  
*完成日期：2009.02.16
****************************************************************/
			/*
			P3.2  CLK     CLK
			P3.3  NSS	  MOSO
			p3.4  MOSI    MOSI
			P3.5  MOSO    RST
			P3.7  RST	  NSS
			*/

// LSD4RF MODULE PORT DEFINE  //
#define PIN_LSD4RF_SPI_NSS  BIT3    // P3.3
#define PIN_LSD4RF_SPI_SCLK  BIT2    // P3.2
#define PIN_LSD4RF_SPI_SDO  BIT4    // P3.4
#define PIN_LSD4RF_SPI_SDI  BIT5    // P3.5
#define PIN_LSD4RF_RESET  BIT7    // P3.7

#define PIN_LSD4RF_DIO0  BIT0    // P1.0
#define PIN_LSD4RF_DIO1  BIT1    // P1.1
#define PIN_LSD4RF_DIO3  BIT6    // P1.6

// RFSI
#define SPI_D0_HIGH()      do{P3M0 &= ~PIN_LSD4RF_SPI_SDO; P3M1 |= PIN_LSD4RF_SPI_SDO; P3 |= PIN_LSD4RF_SPI_SDO;}while(0)    
#define SPI_D0_LOW()       do {P3M0 &= ~PIN_LSD4RF_SPI_SDO; P3M1 |= PIN_LSD4RF_SPI_SDO;P3 &= ~PIN_LSD4RF_SPI_SDO;}while(0)

//RFSCK
#define SPI_CLK_HIGH()    do {P3M0 &= ~PIN_LSD4RF_SPI_SCLK; P3M1 |= PIN_LSD4RF_SPI_SCLK;P3 |= PIN_LSD4RF_SPI_SCLK;}  while(0)  //DIR_OUT ENABLE, DIR_IN DISABLE  //while(0)
#define SPI_CLK_LOW()     do {P3M0 &= ~PIN_LSD4RF_SPI_SCLK; P3M1 |= PIN_LSD4RF_SPI_SCLK;P3 &= ~PIN_LSD4RF_SPI_SCLK;} while(0)

//RFNSS
#define SPI_CS_HIGH()    do{P3M0 &= ~PIN_LSD4RF_SPI_NSS; P3M1 |= PIN_LSD4RF_SPI_NSS;P3 |= PIN_LSD4RF_SPI_NSS;} while(0)
#define SPI_CS_LOW()     do{P3M0 &= ~PIN_LSD4RF_SPI_NSS; P3M1 |= PIN_LSD4RF_SPI_NSS;P3 &= ~PIN_LSD4RF_SPI_NSS;} while(0)

#define W24_CSN_HIGH()	 do{P1M0 &= ~BIT0; P1M1 |= BIT0;P1 |= BIT0;} while(0)    //P1.0
#define W24_CSN_LOW()	 do{P1M0 &= ~BIT0; P1M1 |= BIT0;P1 &= ~ BIT0;} while(0)  //P1.0
#define W24_IRQ_HIGH()    do{P1M0 &= ~BIT1; P1M1 |= BIT1;P1 |= BIT1;} while(0)    //P1.1
#define W24_IRQ_LOW()     do{P1M0 &= ~BIT1; P1M1 |= BIT1;P1 &= ~ BIT1;} while(0)  //P1.1
#define W24_CLK_HIGH()    do {P3M0 &= ~PIN_LSD4RF_SPI_SCLK; P3M1 |= PIN_LSD4RF_SPI_SCLK;P3 |= PIN_LSD4RF_SPI_SCLK;}  while(0)//P3.2
#define W24_CLK_LOW()     do {P3M0 &= ~PIN_LSD4RF_SPI_SCLK; P3M1 |= PIN_LSD4RF_SPI_SCLK;P3 &= ~PIN_LSD4RF_SPI_SCLK;} while(0)
#define W24_CE_HIGH()     do{P3M0 &= ~BIT3; P3M1 |= BIT3;P3 |= BIT3;} while(0)  //P3.3
#define W24_CE_LOW()     do{P3M0 &= ~BIT3; P3M1 |= BIT3;P3 &= ~ BIT3;} while(0)  //P3.3
#define W24_MOSI_HIGH()      do{P3M0 &= ~PIN_LSD4RF_SPI_SDO; P3M1 |= PIN_LSD4RF_SPI_SDO; P3 |= PIN_LSD4RF_SPI_SDO;}while(0) //P3.4   
#define W24_MOSI_LOW()       do {P3M0 &= ~PIN_LSD4RF_SPI_SDO; P3M1 |= PIN_LSD4RF_SPI_SDO;P3 &= ~PIN_LSD4RF_SPI_SDO;}while(0)//P3.4
#define W24_MISO_Enable()   do {P3M0 |= PIN_LSD4RF_SPI_SDI; P3M1 &= ~ PIN_LSD4RF_SPI_SDI;}while(0) //P3.5
#define W24_MISO_JUDGE       (P3&PIN_LSD4RF_SPI_SDI) 											  //P3.5

//RFSO
#define   SPI_DI_Enable()   do {P3M0 |= PIN_LSD4RF_SPI_SDI; P3M1 &= ~ PIN_LSD4RF_SPI_SDI;}while(0) 
#define   SPI_DI_JUDGE       (P3&PIN_LSD4RF_SPI_SDI)          


//RFRST
#define LSD_RF_SXRESET_HIGH()   do {P3M0 &= ~PIN_LSD4RF_RESET; P3M1 |= PIN_LSD4RF_RESET;P3 |= PIN_LSD4RF_RESET;}    while(0)
#define LSD_RF_SXRESET_LOW()    do {P3M0 &= ~PIN_LSD4RF_RESET; P3M1 |= PIN_LSD4RF_RESET;P3 &= ~PIN_LSD4RF_RESET;}   while(0)


#define LSD_RF_SET_DIO0_DIR_IN()  {P1M0 |= PIN_LSD4RF_DIO0; P1M1 &= ~PIN_LSD4RF_DIO0;}    //DIR_IN ENABLE, DIR_OUT DISABLE  //
#define LSD_RF_READ_DIO0()   (P1&PIN_LSD4RF_DIO0)

#define LSD_RF_SPI_SET_DIO1_DIR_IN()  {P1M0 |= PIN_LSD4RF_DIO1; P1M1 &= ~ PIN_LSD4RF_DIO1;}    //DIR_IN ENABLE, DIR_OUT DISABLE  //
#define LSD_RF_READ_DIO1()   (P1&PIN_LSD4RF_DIO1)
#define LSD_RF_SPI_SET_DIO3_DIR_IN()  {P1M0 |= PIN_LSD4RF_DIO3; P1M1 &= ~ PIN_LSD4RF_DIO3;}    //DIR_IN ENABLE, DIR_OUT DISABLE  //
#define LSD_RF_READ_DIO3()   (P1&PIN_LSD4RF_DIO3)

//#define RF_send()       (P1ID&BIT1)                       

 unsigned char LSD_RF_SpiInOut (unsigned char mosi) ;




#define PIN_DIO0_p17  BIT7    // P1.7

#define LOAR_DIO0_LOW()    do{P1M0 &= ~PIN_DIO0_p17; P1M1 |= PIN_DIO0_p17;P1 |= PIN_DIO0_p17;} while(0)
#define LOAR_DIO0_HIGH()     do{P1M0 &= ~PIN_DIO0_p17; P1M1 |= PIN_DIO0_p17;P1 &= ~PIN_DIO0_p17;} while(0)
