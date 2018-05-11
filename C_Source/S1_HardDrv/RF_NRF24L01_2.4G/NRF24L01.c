#include "..\..\S6_MyIncludes\MyIncludes_H.h"
sbit CE=P3^3;  //RX/TX模式选择端
sbit IRQ=P1^1; //可屏蔽中断端
sbit CSN=P1^0; //SPI片选端//就是SS
sbit MOSI=P3^4;	//SPI主机输出从机输入端
sbit MISO=P3^5;	//SPI主机输出从机输出端
sbit SCLK=P3^2;	//SPI时钟端
uchar code TxAddr[]={0x34,0x43,0x10,0x10,0x01};//发送地址
uchar code RxAddr[]={0x34,0x43,0x10,0x10,0x01};//发送地址
/*****************状态标志*****************************************/
uchar bdata sta;   //状态标志
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;
sbit MAX_RT=sta^4;


void Delay(uint t)
{
  uint x,y;
  for(x=t;x>0;x--)
   for(y=110;y>0;y--);
}

/*****************SPI时序函数******************************************/
uchar NRFSPI(uchar date)
{
    uchar i;
   	for(i=0;i<8;i++)          // 循环8次
   	{
	  if(date&0x80)
	    W24_MOSI_HIGH();//MOSI=1;
	  else
	    W24_MOSI_LOW();//MOSI=0;   // byte最高位输出到MOSI
   	  date<<=1;             // 低一位移位到最高位
   	  W24_CLK_HIGH();//SCLK=1; 
	  W24_MISO_Enable();	
	  if(W24_MISO_JUDGE)               // 拉高SCK，nRF24L01从MOSI读入1位数据，同时从MISO输出1位数据
   	    date|=0x01;       	// 读MISO到byte最低位
   	  W24_CLK_LOW();//SCLK=0;            	// SCK置低
   	}
    return(date);           	// 返回读出的一字节
}
/**********************NRF24L01初始化函数*******************************/
void NRF24L01Int()
{
	
	Delay(2);//让系统什么都不干
	W24_CE_LOW();//CE=0; //待机模式1   
	W24_CSN_HIGH();//CSN=1;  
	W24_CLK_LOW();//SCLK=0;
	W24_IRQ_HIGH();//IRQ=1;
	//SX1276SPISetup();              //SPI初始化
}
/*****************SPI读寄存器一字节函数*********************************/
uchar NRFReadReg(uchar RegAddr)
{
   uchar BackDate;
   W24_CSN_LOW();//CSN=0;//启动时序
   gs_uart_drv_var.tx_buff[1] = NRFSPI(RegAddr);//写寄存器地址
   BackDate=NRFSPI(0x00);//写入读寄存器指令  
   W24_CSN_HIGH();//CSN=1;
   return(BackDate); //返回状态
}
/*****************SPI写寄存器一字节函数*********************************/
uchar NRFWriteReg(uchar RegAddr,uchar date)
{
   uchar BackDate;
   W24_CSN_LOW();//CSN=0;//启动时序
   BackDate=NRFSPI(RegAddr);//写入地址
   NRFSPI(date);//写入值
   W24_CSN_HIGH();//CSN=1;
   return(BackDate);
}
/*****************SPI读取RXFIFO寄存器的值********************************/
uchar NRFReadRxDate(uchar RegAddr,uchar *RxDate,uchar DateLen)
{  //寄存器地址//读取数据存放变量//读取数据长度//用于接收
    uchar BackDate,i;
	W24_CSN_LOW();//CSN=0;//启动时序
	BackDate=NRFSPI(RegAddr);//写入要读取的寄存器地址
	for(i=0;i<DateLen;i++) //读取数据
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    W24_CSN_HIGH();//CSN=1;
   return(BackDate); 
}
/*****************SPI写入TXFIFO寄存器的值**********************************/
uchar NRFWriteTxDate(uchar RegAddr,uchar *TxDate,uchar DateLen)
{ //寄存器地址//写入数据存放变量//读取数据长度//用于发送
   uchar BackDate,i;
   W24_CSN_LOW();//CSN=0;//启动时序
   BackDate=NRFSPI(RegAddr);//写入要写入寄存器的地址
   for(i=0;i<DateLen;i++)//写入数据
     {
	    NRFSPI(*TxDate++);
	 }   
   W24_CSN_HIGH();//CSN=1;
   return(BackDate);
}
/*****************NRF设置为发送模式并发送数据******************************/
void NRFSetTxMode(uchar *TxDate ,uchar len)
{//发送模式
    W24_CE_LOW();//CE=0; 
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//写寄存器指令+接收地址使能指令+接收地址+地址宽度
	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//为了应答接收设备，接收通道0地址和发送地址相同
//	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//写入数据 
	/******下面有关寄存器配置**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // 使能接收通道0自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // 使能接收通道0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // 自动重发延时等待250us+86us，自动重发10次
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);         // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);    // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	NRFWriteReg(W_REGISTER+CONFIG,0x0e);      // CRC使能，16位CRC校验，上电  
	W24_CE_HIGH();//CE=1;
	Delay(50);//保持10us秒以上
}
/*****************NRF设置为接收模式并接收数据******************************/
//主要接收模式
void NRFSetRXMode()
{
	W24_CE_LOW();//CE=0;   
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // 接收设备接收通道0使用和发送设备相同的发送地址
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);               // 使能接收通道0自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // 使能接收通道0
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);                 // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // 接收通道0选择和发送通道相同有效数据宽度
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益*/
  	NRFWriteReg(W_REGISTER+CONFIG,0x0f);              // CRC使能，16位CRC校验，上电，接收模式
//	NRFWriteReg(W_REGISTER+STATUS, 0xff);
	W24_CE_HIGH();//CE=1;
	Delay(50);//保持10us秒以上     
}
/****************************检测应答信号******************************/
uchar CheckACK()
{  //用于发射
	sta=NRFReadReg(R_REGISTER+STATUS);                    // 返回状态寄存器
	if(TX_DS||MAX_RT) //发送完毕中断
	{
	   NRFWriteReg(W_REGISTER+STATUS,0xff);  // 清除TX_DS或MAX_RT中断标志
	   W24_CSN_LOW();//CSN=0;
	   NRFWriteReg(FLUSH_TX,0);//用于清空FIFO 
       W24_CSN_HIGH();//CSN=1; 
	   return(0);
	}
	else
	   return(1);

	
}
void NRTxDate(uchar *TxDate)
{
	W24_CE_LOW();//CE=0;
	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//写入数据
	W24_CE_HIGH();//CE=1;
	while(CheckACK());
}

/******************判断是否接收收到数据，接到就从RX取出*********************/
//用于接收模式
uchar NRFRevDate(uchar *RevDate)
{
   	 uchar RevFlags=0;
	 sta=NRFReadReg(R_REGISTER+STATUS);//发送数据后读取状态寄存器
     if(RX_DR)				// 判断是否接收到数据
	 {
	 	LOAR_DIO0_HIGH();//LORA接收到数据点亮P1.7 
        gs_sys_run.font_fg |= BIT1_FONT_P17_500MS;
		
		W24_CE_LOW();//CE=0; 			//SPI使能
		NRFReadRxDate(R_RX_PAYLOAD,RevDate,RX_DATA_WITDH);// 从RXFIFO读取数据
		RevFlags=1;	   //读取数据完成标志
		NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标
	    W24_CSN_LOW();//CSN=0;
	    //NRFSPI(FLUSH_RX);//用于清空FIFO 
	    W24_CSN_HIGH();//CSN=1;
	  }
	  	 
	 if(RevFlags == 1)
	 {
	 	 //LSD_RF_RxPacket(&gs_uart_drv_var.tx_buff[0]);  //RF接收数据//
         //gs_uart_drv_var.tx_len = 1; 
		 if((gs_uart_drv_var.tx_len==1)&&(gs_uart_drv_var.tx_buff[0]!=0x06))
		 {
	      CLRWDT();
		 }
		 gs_uart_iec_app_var.tx_ready_10ms =3;
 		 gs_uart_iec_app_var.tx_delay_flg =TRUE;
	 }	 
         
	 return(RevFlags);
}

