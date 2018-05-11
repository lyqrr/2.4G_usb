
#ifndef LSD_RF_SX1276_H
#define LSD_RF_SX1276_H
//===================================����===================================================

typedef enum
{
    NORMAL,                //����      
    PARAMETER_INVALID,    //����������
    SPI_READCHECK_WRONG,  //SPI����
}tSX127xError;           //�������ö��

typedef enum
{
  // LORA [0: 7.8 kHz, 1: 10.4 kHz, 2: 15.6 kHz, 3: 20.8 kHz, 4: 31.2 kHz,
        // 5: 41.6 kHz, 6: 62.5 kHz, 7: 125 kHz, 8: 250 kHz, 9: 500 kHz, other: Reserved]
    BW500KHZ = 0x90,      
    BW250KHZ = 0x80,
    BW125KHZ = 0x70,
    BW62_50KHZ = 0x60,
    BW41_66KHZ = 0x50,
    BW31_25KHZ = 0x40,
    BW20_83KHZ = 0x30,
    BW15_62KHZ = 0x20,
    BW10_41KHZ = 0x10,
    BW7_81KHZ = 0x00,
}t_BandWidth;      //�������ö��
typedef enum{
    // LORA [6: 64, 7: 128, 8: 256, 9: 512, 10: 1024, 11: 2048, 12: 4096  chips]
    SF12 = 0xC0,
    SF11 = 0xB0,
    SF10 = 0xA0,
    SF09 = 0x90,
    SF08 = 0x80,
    SF07 = 0x70,
    SF06 = 0x60,
}t_SpreadingFactor;
typedef enum{
    // LORA [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8] 
    CR_4_8 = 0x08,
    CR_4_7 = 0x06,
    CR_4_6 = 0x04,
    CR_4_5 = 0x02,
}t_CodingRate;
typedef struct S_LoRaConfig
{
    uint32 LoRa_Freq;
    t_BandWidth BandWidth;                     
    t_SpreadingFactor SpreadingFactor;            
    t_CodingRate CodingRate;
    uint8 PowerCfig; //0~15,������� = 2+PowerReg,����ο������ֲ�
                     //�������MaxPower��PowerReg = 15ʱ��������� = 19��1dBm
    BOOL MaxPowerOn;                    // [false: OFF, true: ON]
    BOOL CRCON;                         // [false: OFF, true: ON]
    BOOL ExplicitHeaderOn;              // [false: OFF, true: ON]
    uint8 PayloadLength;              //1~127
}S_LoRaConfig;

extern S_LoRaConfig G_LoRaConfig;
extern float G_BandWidthKHz;//����Symbol����ʹ��
extern float G_TsXms;//Symbol���ڣ���λms

//===================================��������===================================================
////////////////////////////////////////////////////////////////////////////////
// �������� : RF��ʼ��
// ������� : 
// ���ز��� : tSX127xError              ����ö������
// ˵��     : ��ʼ��ʱ������ȫ�ֱ���G_LoRaConfig
////////////////////////////////////////////////////////////////////////////////
tSX127xError SX127x_init();
////////////////////////////////////////////////////////////////////////////////
// �������� : RF�������ݰ�
// ������� : uint8_t*data����������ָ�룬uint8_t size�������ݳ���
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
void SX1276_TxPacket(uint8 *temp);
void SX1276_Process(void);
////////////////////////////////////////////////////////////////////////////////
// �������� : RF�������״̬
// ������� : 
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
void Rx_mode(void);
////////////////////////////////////////////////////////////////////////////////
// �������� : RF���տɱ����ݰ�
// ������� : uint8_t*cbuf��������ָ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_RxPacket(uint8 *cbuf);
////////////////////////////////////////////////////////////////////////////////
// �������� : RF����SLEEP״̬
// ������� : ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_SleepMode(void);
////////////////////////////////////////////////////////////////////////////////
// �������� : RF����standby״̬
// ������� : ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
void LSD_RF_StandbyMode(void);
////////////////////////////////////////////////////////////////////////////////
// �������� : RF����Ƶ��
// ������� : ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
tSX127xError LSD_RF_FreqSet();
////////////////////////////////////////////////////////////////////////////////
// �������� : RF���ù���
// ������� : ��
// ���ز��� : ��
// ˵��     : 
////////////////////////////////////////////////////////////////////////////////
tSX127xError LSD_RF_PoutSet();
//*****************************************************************************************

void SX1276WriteFifo( uint8 *buffer, uint8 size );
void SX1276Write( uint8 addr, uint8 temp );
void SX1276InitIo( void );
void SX1276SPISetup(void);
void SX1276WriteBuffer( uint8 addr, uint8 *buffer, uint8 size );
void SX1276ReadBuffer( uint8 addr, uint8 *buffer, uint8 size );
void SX1276WriteFifo( uint8 *buffer, uint8 size );
void SX1276ReadFifo( uint8 *buffer, uint8 size );
void SX1276Reset();
void SX1276WriteRxTx( BOOL txEnable );
INT8U Lnk_SX2176_Intilize(void);
INT8U Lnk_sx1276_rx_data(INT8U *rx_ptr, INT8U *rx_len);

#endif
