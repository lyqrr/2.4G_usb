#include "..\..\S6_MyIncludes\MyIncludes_H.h"
sbit CE=P3^3;  //RX/TXģʽѡ���
sbit IRQ=P1^1; //�������ж϶�
sbit CSN=P1^0; //SPIƬѡ��//����SS
sbit MOSI=P3^4;	//SPI��������ӻ������
sbit MISO=P3^5;	//SPI��������ӻ������
sbit SCLK=P3^2;	//SPIʱ�Ӷ�
uchar code TxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
uchar code RxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
/*****************״̬��־*****************************************/
uchar bdata sta;   //״̬��־
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;
sbit MAX_RT=sta^4;


void Delay(uint t)
{
  uint x,y;
  for(x=t;x>0;x--)
   for(y=110;y>0;y--);
}

/*****************SPIʱ����******************************************/
uchar NRFSPI(uchar date)
{
    uchar i;
   	for(i=0;i<8;i++)          // ѭ��8��
   	{
	  if(date&0x80)
	    W24_MOSI_HIGH();//MOSI=1;
	  else
	    W24_MOSI_LOW();//MOSI=0;   // byte���λ�����MOSI
   	  date<<=1;             // ��һλ��λ�����λ
   	  W24_CLK_HIGH();//SCLK=1; 
	  W24_MISO_Enable();	
	  if(W24_MISO_JUDGE)               // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   	    date|=0x01;       	// ��MISO��byte���λ
   	  W24_CLK_LOW();//SCLK=0;            	// SCK�õ�
   	}
    return(date);           	// ���ض�����һ�ֽ�
}
/**********************NRF24L01��ʼ������*******************************/
void NRF24L01Int()
{
	
	Delay(2);//��ϵͳʲô������
	W24_CE_LOW();//CE=0; //����ģʽ1   
	W24_CSN_HIGH();//CSN=1;  
	W24_CLK_LOW();//SCLK=0;
	W24_IRQ_HIGH();//IRQ=1;
	//SX1276SPISetup();              //SPI��ʼ��
}
/*****************SPI���Ĵ���һ�ֽں���*********************************/
uchar NRFReadReg(uchar RegAddr)
{
   uchar BackDate;
   W24_CSN_LOW();//CSN=0;//����ʱ��
   gs_uart_drv_var.tx_buff[1] = NRFSPI(RegAddr);//д�Ĵ�����ַ
   BackDate=NRFSPI(0x00);//д����Ĵ���ָ��  
   W24_CSN_HIGH();//CSN=1;
   return(BackDate); //����״̬
}
/*****************SPIд�Ĵ���һ�ֽں���*********************************/
uchar NRFWriteReg(uchar RegAddr,uchar date)
{
   uchar BackDate;
   W24_CSN_LOW();//CSN=0;//����ʱ��
   BackDate=NRFSPI(RegAddr);//д���ַ
   NRFSPI(date);//д��ֵ
   W24_CSN_HIGH();//CSN=1;
   return(BackDate);
}
/*****************SPI��ȡRXFIFO�Ĵ�����ֵ********************************/
uchar NRFReadRxDate(uchar RegAddr,uchar *RxDate,uchar DateLen)
{  //�Ĵ�����ַ//��ȡ���ݴ�ű���//��ȡ���ݳ���//���ڽ���
    uchar BackDate,i;
	W24_CSN_LOW();//CSN=0;//����ʱ��
	BackDate=NRFSPI(RegAddr);//д��Ҫ��ȡ�ļĴ�����ַ
	for(i=0;i<DateLen;i++) //��ȡ����
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    W24_CSN_HIGH();//CSN=1;
   return(BackDate); 
}
/*****************SPIд��TXFIFO�Ĵ�����ֵ**********************************/
uchar NRFWriteTxDate(uchar RegAddr,uchar *TxDate,uchar DateLen)
{ //�Ĵ�����ַ//д�����ݴ�ű���//��ȡ���ݳ���//���ڷ���
   uchar BackDate,i;
   W24_CSN_LOW();//CSN=0;//����ʱ��
   BackDate=NRFSPI(RegAddr);//д��Ҫд��Ĵ����ĵ�ַ
   for(i=0;i<DateLen;i++)//д������
     {
	    NRFSPI(*TxDate++);
	 }   
   W24_CSN_HIGH();//CSN=1;
   return(BackDate);
}
/*****************NRF����Ϊ����ģʽ����������******************************/
void NRFSetTxMode(uchar *TxDate ,uchar len)
{//����ģʽ
    W24_CE_LOW();//CE=0; 
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,TxAddr,TX_ADDR_WITDH);//д�Ĵ���ָ��+���յ�ַʹ��ָ��+���յ�ַ+��ַ���
	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);//Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
//	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//д������ 
	/******�����йؼĴ�������**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);         // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
	NRFWriteReg(W_REGISTER+CONFIG,0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�  
	W24_CE_HIGH();//CE=1;
	Delay(50);//����10us������
}
/*****************NRF����Ϊ����ģʽ����������******************************/
//��Ҫ����ģʽ
void NRFSetRXMode()
{
	W24_CE_LOW();//CE=0;   
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,TxAddr,TX_ADDR_WITDH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);           // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);                 // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������*/
  	NRFWriteReg(W_REGISTER+CONFIG,0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
//	NRFWriteReg(W_REGISTER+STATUS, 0xff);
	W24_CE_HIGH();//CE=1;
	Delay(50);//����10us������     
}
/****************************���Ӧ���ź�******************************/
uchar CheckACK()
{  //���ڷ���
	sta=NRFReadReg(R_REGISTER+STATUS);                    // ����״̬�Ĵ���
	if(TX_DS||MAX_RT) //��������ж�
	{
	   NRFWriteReg(W_REGISTER+STATUS,0xff);  // ���TX_DS��MAX_RT�жϱ�־
	   W24_CSN_LOW();//CSN=0;
	   NRFWriteReg(FLUSH_TX,0);//�������FIFO 
       W24_CSN_HIGH();//CSN=1; 
	   return(0);
	}
	else
	   return(1);

	
}
void NRTxDate(uchar *TxDate)
{
	W24_CE_LOW();//CE=0;
	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//д������
	W24_CE_HIGH();//CE=1;
	while(CheckACK());
}

/******************�ж��Ƿ�����յ����ݣ��ӵ��ʹ�RXȡ��*********************/
//���ڽ���ģʽ
uchar NRFRevDate(uchar *RevDate)
{
   	 uchar RevFlags=0;
	 sta=NRFReadReg(R_REGISTER+STATUS);//�������ݺ��ȡ״̬�Ĵ���
     if(RX_DR)				// �ж��Ƿ���յ�����
	 {
	 	LOAR_DIO0_HIGH();//LORA���յ����ݵ���P1.7 
        gs_sys_run.font_fg |= BIT1_FONT_P17_500MS;
		
		W24_CE_LOW();//CE=0; 			//SPIʹ��
		NRFReadRxDate(R_RX_PAYLOAD,RevDate,RX_DATA_WITDH);// ��RXFIFO��ȡ����
		RevFlags=1;	   //��ȡ������ɱ�־
		NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
	    W24_CSN_LOW();//CSN=0;
	    //NRFSPI(FLUSH_RX);//�������FIFO 
	    W24_CSN_HIGH();//CSN=1;
	  }
	  	 
	 if(RevFlags == 1)
	 {
	 	 //LSD_RF_RxPacket(&gs_uart_drv_var.tx_buff[0]);  //RF��������//
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

