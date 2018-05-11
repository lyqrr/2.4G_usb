////////////////////////////////////////////////////////////////////////////////
// ��Ȩ:     ������Ƽ����Źɷ����޹�˾
// �ļ���:   
// �汾��   
// ��������:
// ����:     
// ��������: 
// ����:      
// ����ļ�: 
// �޸���־��
//      ������˵��
////////////////////////////////////////////////////////////////////////////////

#include <MyIncludes_H.h>





//===================================�������===================================================
float G_BandWidthKHz;//���ؼ���Symbol����ʹ��
float G_TsXms;
S_LoRaConfig G_LoRaConfig;//��main�г�ʼ��





INT8U Lnk_SX2176_Intilize(void)
{
     if(SX127x_init() != NORMAL) return FALSE;
     Rx_mode();                        //����RX,׼����������//
     return TRUE;
}


//**********************************************************************************
// �������� : spi��д�Ĵ���
// ������� : unsigned char addr��ַ unsigned char val����
// ���ز��� : 
// ˵��     : Note: don't call it directely use macro SpiWriteReg and SpiWriteReg  to call this routine
//**********************************************************************************
unsigned char LSD_RF_SpiRW_Reg (unsigned char addr, unsigned char val) 
{
    unsigned char rc;
    SX1276SPISetup();
    SPI_CS_LOW()  ;  
    LSD_RF_SpiInOut(addr);
    rc = LSD_RF_SpiInOut(val);
    SPI_CS_HIGH() ;
    return rc;
}

////////////////////////////////////////////////////////////////////////////////
// �������� : RF  ��Ĵ�����ַд1�ֽ�����
// ������� : uint8_t addr,�Ĵ�����ַ uint8_t data����
// ���ز��� : 
// ˵��     :
////////////////////////////////////////////////////////////////////////////////
void SX1276Write( uint8 addr, uint8 temp )    
{
  LSD_RF_SpiRW_Reg(addr|0x80,temp);
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF  ��Ĵ�����ַ��1�ֽ�����
// ������� : uint8_t addr,�Ĵ�����ַ uint8_t *data�����ݴ洢��ַ
// ���ز��� : 
// ˵��     :
////////////////////////////////////////////////////////////////////////////////
#define SX1276Read(addr)               LSD_RF_SpiRW_Reg(addr&0x7F, 0);
////////////////////////////////////////////////////////////////////////////////
// �������� : RF  ��FIFO������
// ������� : uint8_t *buffer,����ָ�� uint8_t size����
// ���ز��� : uint8_t *buffer �洢��ȡ����
// ˵��     :
////////////////////////////////////////////////////////////////////////////////
void  SX1276ReadFifo( uint8 *buffer, uint8 size ) 
{
   SX1276ReadBuffer( 0, buffer, size );
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF  ��Ĵ�����ַ������������
// ������� : uint8_t addr,�Ĵ�����ַ uint8_t *buffer,��������ָ�� uint8_t sizeָ�볤��
// ���ز��� : ��
// ˵��     :
////////////////////////////////////////////////////////////////////////////////
  void SX1276WriteBuffer( uint8 addr, uint8 *buffer, uint8 size )
{
    uint8 i;  
  // LSD_RF_SpiInOut((addr | 0x80));
    for( i = 0; i < size; i++ )
    { 
        SX1276Write(addr ,buffer[i]);                // Send data
    }

}


////////////////////////////////////////////////////////////////////////////////
// �������� : RF  ��Ĵ�����ַ����������
// ������� : uint8_t addr,�Ĵ�����ַ uint8_t *buffer,�洢����ָ�� uint8_t sizeҪ���ĳ���
// ���ز��� : ���ݷ��ص�*buffer��
// ˵��     :
////////////////////////////////////////////////////////////////////////////////
void SX1276ReadBuffer( uint8 addr, uint8 *buffer, uint8 size )
{   
    uint8 i;  
   // SX1276Read((addr));
    for( i = 0; i < size; i++ )
    { 
        buffer[i] = SX1276Read(addr);                // Send data
    }
}


BOOL LoRaConfig_Check()
{
    if((G_LoRaConfig.LoRa_Freq<410000000)||(G_LoRaConfig.LoRa_Freq>1020000000))
        return FALSE;
    if((G_LoRaConfig.LoRa_Freq>525000000)&&(G_LoRaConfig.LoRa_Freq<862000000))
        return FALSE;
    G_LoRaConfig.BandWidth = (t_BandWidth)(G_LoRaConfig.BandWidth&0xF0);
    if(G_LoRaConfig.BandWidth>BW500KHZ)
        return FALSE;
    //����BandWidth
    switch(G_LoRaConfig.BandWidth){
    case BW500KHZ:G_BandWidthKHz = 500.0;break;
    case BW250KHZ:G_BandWidthKHz = 250.0;break;
    case BW125KHZ:G_BandWidthKHz = 125.0;break;
    case BW62_50KHZ:G_BandWidthKHz = 62.5;break;
    case BW41_66KHZ:G_BandWidthKHz = 41.66;break;
    case BW31_25KHZ:G_BandWidthKHz = 31.25;break;
    case BW20_83KHZ:G_BandWidthKHz = 20.83;break;
    case BW15_62KHZ:G_BandWidthKHz = 15.62;break;
    case BW10_41KHZ:G_BandWidthKHz = 10.41;break;
    case BW7_81KHZ:G_BandWidthKHz = 7.81;break;
    }
    G_LoRaConfig.SpreadingFactor = (t_SpreadingFactor)(G_LoRaConfig.SpreadingFactor&0xF0);
    if((G_LoRaConfig.SpreadingFactor>SF12)||(G_LoRaConfig.SpreadingFactor<SF06))
        return FALSE;
    //����LoRa��Ԫ���ڣ���λms
    G_TsXms = (2<<((G_LoRaConfig.SpreadingFactor>>4)-1))/G_BandWidthKHz;
    
    G_LoRaConfig.CodingRate = (t_CodingRate)(G_LoRaConfig.CodingRate&0x0E);
    if((G_LoRaConfig.CodingRate>CR_4_8)||(G_LoRaConfig.CodingRate<CR_4_5))
        return FALSE;
    if(G_LoRaConfig.PowerCfig>15)
        return FALSE;
    if(G_LoRaConfig.PayloadLength>127)
        return FALSE;
    return TRUE;
}
//===================================�Ӻ���===================================================
////////////////////////////////////////////////////////////////////////////////
// �������� : RF��ʼ��
// ������� : tSX127xInitPara initPara  ��������Init_LoRa_0_8K, Init_LoRa_4_8K , Init_LoRa_10k,
// ���ز��� : tSX127xError              ����ö������
// ˵��     :  ��ʼ��ʱ���ŵ���ʼ��Ĭ��Ϊ0�ŵ�
////////////////////////////////////////////////////////////////////////////////

tSX127xError SX127x_init()
{     
     uint8 test = 0;
      //RF ģ��//
    //���ø�������

	
	G_LoRaConfig.LoRa_Freq = 915000000;   //����Ƶ��470MHz
    G_LoRaConfig.BandWidth = BW500KHZ;    //BW = 125KHz
    G_LoRaConfig.SpreadingFactor = SF07;  //SF = 9
    G_LoRaConfig.CodingRate = CR_4_8;     //CR = 4/6
    G_LoRaConfig.PowerCfig = 15;          //19��dBm
    G_LoRaConfig.MaxPowerOn = TRUE;       
    G_LoRaConfig.CRCON = TRUE;            //CRC����
    G_LoRaConfig.ExplicitHeaderOn = TRUE; //Header����
    G_LoRaConfig.PayloadLength = 64;      //���ݰ�����


    if(FALSE==LoRaConfig_Check())   //��������������
    {
        return PARAMETER_INVALID;  //��������
    }
//	return NORMAL;
    SX1276InitIo();                // PAIO�ڳ�ʼ��            
//    return NORMAL;
	SX1276Reset();                 //��λRF
    SX1276SPISetup();              //SPI��ʼ��

    //�л���LoRamode��standby״̬
     SX1276Write( REG_LR_OPMODE, RFLR_OPMODE_SLEEP);            
     SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_SLEEP );       
     SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );
 
    /*------------------------------------------------
    SPI ��֤                   */  
    test = 0;
    SX1276Write( REG_LR_HOPPERIOD,0x91 );//ѡһ���ò����ļĴ���������֤
     test = SX1276Read( REG_LR_HOPPERIOD);
    if( test != 0x91)
        return SPI_READCHECK_WRONG;           

    //Frequency Configuration 
    LSD_RF_FreqSet();    //����Ƶ��
    
    //PA Configuration  
    LSD_RF_PoutSet();
    SX1276Write( REG_LR_PARAMP,RFLR_PARAMP_0250_US);  
    //  ��PA Ramp��ʱ�䣬����û�LDO���ܿ������������������������ʵ�����PA Rampʱ��
    //  �����Rampʱ����̳�����LDO������ʱ������ֽ���TX��ϵͳ����Ϊ�������������RF�źŲ����ֵ�����
    SX1276Write( REG_LR_OCP,0x20|RFLR_OCP_TRIM_240_MA);//�������ر��� Over Current Protection
    
    //PayloadLength ��ʼ��             
    SX1276Write( REG_LR_PAYLOADLENGTH,G_LoRaConfig.PayloadLength); 
    //ע�⣬��ͷģʽ��Implicit Header��ʱ��������ǰ�涨���շ�˫����PL
	
    //BW��CR��Header���ޣ���ʼ��   0x90 0x08 0x01     
    SX1276Write( REG_LR_MODEMCONFIG1,\
        (((uint8)G_LoRaConfig.BandWidth)|((uint8)G_LoRaConfig.CodingRate))|(\
            (TRUE==G_LoRaConfig.ExplicitHeaderOn)?0x00:0x01));
    
    //SF��CRC��ʼ��   0x74               
 /*   SX1276Write( REG_LR_MODEMCONFIG2,\
        ((uint8)G_LoRaConfig.SpreadingFactor)|(\
            (TRUE==G_LoRaConfig.CRCON)?0x04:0x00));
*/
	SX1276Write( REG_LR_MODEMCONFIG2,\
    ((uint8)G_LoRaConfig.SpreadingFactor)|(\
        (TRUE==G_LoRaConfig.CRCON)?0x04:0x00)|0x03);

    if(SF06==G_LoRaConfig.SpreadingFactor){   //����SF = 6����Ҫ�����ú�����
        uint8 temp = 0;
        temp = SX1276Read( 0x31);
        SX1276Write(  0x31,(temp& 0xF8)|0x05);
        SX1276Write(  0x37,0x0C); 
   }
//	SX1276Write(REG_LR_MODEMCONFIG1, ((9<<4)+(0x04<<1)+0x01));//Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
//	SX1276Write(REG_LR_MODEMCONFIG2, ((7<<4)+(0x01<<2)+0x03));

//   �������Ż������Ƿ�����AutoAGCĬ�Ͽ���  
     SX1276Write( REG_LR_MODEMCONFIG3,0x0c);


/*    SX1276Write( REG_LR_MODEMCONFIG3,((G_TsXms>16.0)?\
      RFLR_MODEMCONFIG3_LOWDATARATEOPTIMIZE_ON:RFLR_MODEMCONFIG3_LOWDATARATEOPTIMIZE_OFF\
          )|RFLR_MODEMCONFIG3_AGCAUTO_ON);
 */ 
    return NORMAL;
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF�������ݰ�
// ������� : uint8 *data����������ָ��
// ���ز��� : ��
// ˵��     : ����Ϊ�����ǣ� preamble�Ļ�Ĭ��ֵ
////////////////////////////////////////////////////////////////////////////////
void SX1276_TxPacket(uint8 *temp)
{
   unsigned long int j=16777215;// ��ʱʱ�䡣����..
//   ExInt4IFG&=(~BIT2);
//   EIE&=~BIT2;              //int2 ����ǰ�ر��ж�   // ��ʹ���ж�
//   ExInt4IE&=~BIT2;
    SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );      
    SX1276Write( REG_LR_PREAMBLEMSB,0);
    SX1276Write( REG_LR_PREAMBLELSB,8);
    SX1276Write( REG_LR_PAYLOADLENGTH,G_LoRaConfig.PayloadLength);                    
    SX1276WriteRxTx(TRUE);                                      
    SX1276Write( REG_LR_FIFOADDRPTR,0x80);                      
    SX1276WriteBuffer(REG_LR_FIFO,temp,G_LoRaConfig.PayloadLength);  
    SX1276Write(REG_LR_IRQFLAGS,0xff);                          
    SX1276Write( REG_LR_IRQFLAGSMASK, ~(RFLR_IRQFLAGS_TXDONE)); 
    SX1276Write( REG_LR_DIOMAPPING1, RFLR_DIOMAPPING1_DIO0_01 );
    SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_TRANSMITTER );   
    // while((!LSD4RF_READ_DIO0())&&j)j--;         // packet sent	 
    while((!LSD_RF_READ_DIO0())&&j)j--;         // packet sent	 
	 
//     while ((RF_send())&&j) j--;   //���//
  //  while( ExInt4IFG&BIT2);
 //   P1OE|=(BIT1);        //INT ��ֹ���
 //   P1IE|=(BIT1);        //INT ��������
  //  P11FS=0x04;         //   INT
   // ExInt4IFG&=(~BIT2);
 //   EIE|=BIT2;              //int2�ж�
//    ExInt4IE|=BIT2;
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF�������״̬
// ������� : 
// ���ز��� : ��
// ˵��     : ������պ�preamble���û�Ĭ��ֵΪ
////////////////////////////////////////////////////////////////////////////////
void Rx_mode()
{ 
    SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );      
    SX1276Write( REG_LR_PREAMBLEMSB,0);
    SX1276Write( REG_LR_PREAMBLELSB,8);
    SX1276Write( REG_LR_PAYLOADLENGTH,G_LoRaConfig.PayloadLength);
    SX1276Write( REG_LR_IRQFLAGSMASK, ~(RFLR_IRQFLAGS_RXDONE)); 
    SX1276Write( REG_LR_DIOMAPPING1, RFLR_DIOMAPPING1_DIO0_00 );
    SX1276WriteRxTx(FALSE);                                     
    SX1276Write( REG_LR_FIFOADDRPTR,0x00);                      
    SX1276Write(REG_LR_IRQFLAGS,0xff);                          
    SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_RECEIVER ); 
//    P1OE|=(BIT1);        //INT ��ֹ���
//    P1IE|=(BIT1);        //INT ��������
//    P11FS=0x04;         //   INT
//    ExInt4IFG&=(~BIT2);
//    EIE|=BIT2;              //int2�ж�
//    ExInt4IE|=BIT2;
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF�������ݰ�
// ������� : uint8*cbuf��������ָ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_RxPacket(uint8 *cbuf)
{
   // if(true==G_LoRaConfig.ExplicitHeaderOn){
        //��ͷ��ô�ӼĴ����ж���������G_LoRaConfig���ó��ȶ�ȡFIFO
      
         G_LoRaConfig.PayloadLength = SX1276Read(REG_LR_NBRXBYTES);
          SX1276Write( REG_LR_FIFOADDRPTR,0x00);
  //  }
    SX1276ReadFifo(cbuf,G_LoRaConfig.PayloadLength);   
    SX1276Write(REG_LR_IRQFLAGS,0xff);        
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF����SLEEP״̬
// ������� : ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_SleepMode(void)
{
    SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );      
    SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_SLEEP );     
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF����standby״̬
// ������� : ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_StandbyMode(void)
{
    SX1276Write( REG_LR_OPMODE, 0x80|RFLR_OPMODE_STANDBY );       
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF����Ƶ��
// ������� : ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
tSX127xError LSD_RF_FreqSet()
{
    uint32 freq_reg;
	uint8  test_FRFMSB,test_FRFMID,test_FRFLSB;
    if((G_LoRaConfig.LoRa_Freq<410000000)||(G_LoRaConfig.LoRa_Freq>1020000000))
        return FALSE;
    if((G_LoRaConfig.LoRa_Freq>525000000)&&(G_LoRaConfig.LoRa_Freq<862000000))
        return FALSE;
     freq_reg = (uint32)(G_LoRaConfig.LoRa_Freq/FREQ_STEP);
     test_FRFMSB = 0;
	 test_FRFMID=0;
	 test_FRFLSB=0;
    LSD_RF_StandbyMode();
    // FREQ = 474.6MHz
    SX1276Write( REG_LR_FRFMSB, (uint8 )(freq_reg>>16));//Carrier Freq 470M
    SX1276Write( REG_LR_FRFMID, (uint8 )(freq_reg>>8) );
    SX1276Write( REG_LR_FRFLSB, (uint8 )(freq_reg) );
    
    test_FRFMSB = SX1276Read(REG_LR_FRFMSB);
    test_FRFMID = SX1276Read(REG_LR_FRFMID);
    test_FRFLSB = SX1276Read(REG_LR_FRFLSB);
    
    if(test_FRFMSB != (uint8 )(freq_reg>>16))
        return SPI_READCHECK_WRONG;
    if(test_FRFMID != (uint8 )(freq_reg>>8))
        return SPI_READCHECK_WRONG;
    if(test_FRFLSB != (uint8 )(freq_reg))
        return SPI_READCHECK_WRONG;
    return NORMAL;
}
////////////////////////////////////////////////////////////////////////////////
// �������� : RF���ù���
// ������� : ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
tSX127xError LSD_RF_PoutSet()
{
uint8 test;
    if(G_LoRaConfig.PowerCfig>15)
        return PARAMETER_INVALID;
    LSD_RF_StandbyMode();
    SX1276Write( REG_LR_PACONFIG, 0xf0|G_LoRaConfig.PowerCfig);
    test = 0;
    test = SX1276Read(REG_LR_PACONFIG);
    if((0xf0|G_LoRaConfig.PowerCfig)!=test)
        return SPI_READCHECK_WRONG;
    if(TRUE==G_LoRaConfig.MaxPowerOn)
        SX1276Write( REG_LR_PADAC, 0x80|RFLR_PADAC_20DBM_ON );  
    if (TRUE !=G_LoRaConfig.MaxPowerOn)
        SX1276Write( REG_LR_PADAC, 0x80|RFLR_PADAC_20DBM_OFF );
   
    return NORMAL;
}



