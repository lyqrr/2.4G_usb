/*
*****************Copyright (c)*************************************
**      Hangzhou Xili Watthour Meter Manufacture Co., Ltd. 
**--------------file info--------------------------------------------
**name: includes.H
**Author: maji
**date: 
**description:  define for  all 
**note: memer type  SD03A
**--------------------Version History -------------------------------------
** NO. Date         Ver      By         Description 
**==============================================================
** 1   2015-09-06   v01.00   sosomj     1. frist version                             
**
**==============================================================
*/


#ifndef 	_SYS_MACRO_H
#define	_SYS_MACRO_H



//******************************************************************
//			   		//
//******************************************************************

typedef union
{
    unsigned char       byte8 ;
    struct
    {
        unsigned char   bit0:1 ;
        unsigned char   bit1:1 ;
        unsigned char   bit2:1 ;
        unsigned char   bit3:1 ;
        unsigned char   bit4:1 ;
        unsigned char   bit5:1 ;
        unsigned char   bit6:1 ;
        unsigned char   bit7:1 ;
    }bits8 ;
}bits8_t ;

#define __CODE										code
#define __DATA										data
#define __IDATA										idata
#define __XDATA										xdata
#define __GENERIC									

typedef float										f_t ;
typedef float __XDATA								fx_t ;

typedef bits8_t										b8_t ;
typedef bits8_t __XDATA								b8x_t ;

typedef signed char									s8_t ;
typedef signed char __XDATA							s8x_t ;

typedef signed long									s32_t ;

typedef unsigned char								u8_t ;
typedef unsigned char __DATA						u8d_t ;
typedef unsigned char __XDATA						u8x_t ;
typedef unsigned char __GENERIC						u8g_t ;

typedef unsigned short								u16_t ;
typedef unsigned short __XDATA						u16x_t ;
typedef unsigned short __GENERIC					u16g_t ;

typedef unsigned long								u32_t ;
typedef unsigned long __DATA						u32d_t ;
typedef unsigned long __XDATA						u32x_t ;
typedef unsigned long __GENERIC						u32g_t ;



typedef 	unsigned char  BOOLEAN;
typedef 	unsigned char  BOOL;
typedef 	unsigned char  ErrorStatus; 
typedef		unsigned char  INT8U;
typedef 	unsigned char  uchar;
typedef 	unsigned char  u8;
typedef		unsigned char  uint8;                   //�޷���8λ���ͱ���//

typedef 	signed char	INT8S;
typedef 	signed char	schar;
typedef 	signed char	s8;
typedef signed   char      int8;                    //�з���8λ���ͱ���//

typedef unsigned 	short 	INT16U;
typedef unsigned 	short	uint;
typedef unsigned 	short	u16;
typedef unsigned	short   uint16;                  //�޷���16λ���ͱ��� //


typedef 	signed	short	INT16S;
typedef 	signed	short	sint;
typedef 	signed	short	s16;
typedef		signed   short     int16;                   //�з���16λ���ͱ��� //

typedef unsigned 	long	INT32U;
typedef unsigned 	long	ulong;
typedef unsigned 	long	u32;
typedef unsigned long      uint32;                  //�޷���32λ���ͱ��� //

typedef signed	long	INT32S;
typedef signed	long	slong;
typedef signed	long	s32;
typedef signed   long      int32;                   //�з���32λ���ͱ��� //

typedef	float 		F32;
typedef float              fp32;                    //�����ȸ�������32λ���ȣ�//
typedef double             fp64;                    //˫���ȸ�������64λ���ȣ�//


typedef 	unsigned char BCD8;
typedef 	unsigned short 	BCD16;
typedef 	unsigned long 	BCD32;
typedef unsigned char ASCII;

typedef	bit				         Bit;
typedef	bit				         Bool;
typedef	unsigned char	     Byte;
typedef	unsigned int	     Word;
typedef	unsigned long	     Dword;


union Union_ByteDef
{
	struct
	{ 
		unsigned char b0:1;
		unsigned char b1:1;
		unsigned char b2:1;
		unsigned char b3:1;
		unsigned char b4:1;
		unsigned char b5:1;
		unsigned char b6:1;
		unsigned char b7:1;
	}BIT;
	unsigned char BYTE;
};

union Union_WordDef
{
	unsigned short WORD;
	unsigned char BYTE[2];
};
union Union_DWordDef
{
	signed long   DWORD;
	unsigned long  UDWORD;
	unsigned short WORD[2];
	unsigned char BYTE[4];
};




//******************************************************************
//			     	//
//******************************************************************
//G80F903A //

#define NOP()     _nop_()   //__ASM ("NOP")
#define nop()	  NOP()
#define DisableINT()   	IEN0 &= ~BIT7
#define EnableINT() 	IEN0 |= BIT7	
#define CLRWDT()      	RSTSTAT=0x00;		/* restart watch dog timer */     
#define RESTET_WDT()    RSTSTAT = 0x07


//******************************************************************
//	���ݴ�С�˶��壬
//   C51Ϊ��ˣ�32λ���ݸ�8�ֽڴ洢�ڵ�ַ[0]	//
//   MDK�е�M0ΪС�ˣ�32λ���ݵ�8�ֽڴ洢�ڵ�ַ[0]	
//******************************************************************
#define LITTLE_END      //  С�˶���,Ĭ�ϲ��ô��//




//******************************************************************
//			     	 				//
//******************************************************************
#define	FALSE				0
#define	TRUE				1
#define	false				 0
#define	true					1
#define	ON					0
#define	OFF					1
#define	SUCCESS			1
#define	FAIL				0
#define ERROR         0
#define	IO_DIR_IN			1
#define	IO_DIR_OUT		0
#define	IO_OUT_HIGH		1
#define	IO_OUT_LOW		0
#define	IO_INPUT_HIGH		1
#define	IO_INPUT_LOW		0

#define 	RESULT_TRUE			TRUE
#define 	RESULT_FALSE			FALSE

#define 	RETURN_SUCCESS		return(SUCCESS)
#define 	RETURN_FAIL			return(FAIL)

// ��̬�����ʶ //
#define LOW           0  //  //
#define HIGH          1
#define MID            2


//******************************************************************
//	  ȡ �ṹ���ڲ�Ԫ�صĳ��Ⱥ�ƫ����αָ��		//
//******************************************************************
#define ST_MB_LEN(ST,MB) ((unsigned int)(sizeof(((ST *)0)->MB)))            //�ṹ���Ա�ĳ���  //
#define ST_MB_OFFSET(ST,MB) (unsigned int)(&(((ST *)0)->MB))                //�ṹ���Ա��ƫ�Ƶ�ַ  //


//******************************************************************
//			     	STANDARD BITS			 				//
//******************************************************************
#define BIT0                (0x01)
#define BIT1                (0x02)
#define BIT2                (0x04)
#define BIT3                (0x08)
#define BIT4                (0x10)
#define BIT5                (0x20)
#define BIT6                (0x40)
#define BIT7                (0x80)



/********************************/
/*      ϵͳ�ֽں�������        */										
/********************************/
#define	      MAKEWORD(v1,v2)	       (((Word)(v1)<<8) + (Word)(v2))
#define	      HIBYTE(v1)		           ((Byte)((v1)>>8))
#define	      LOBYTE(v1)		           ((Byte)((v1)&0xff))

#define       LongToBin(n) \
      (                    \
      ((n >> 21) & 0x80) | \
      ((n >> 18) & 0x40) | \
      ((n >> 15) & 0x20) | \
      ((n >> 12) & 0x10) | \
      ((n >>  9) & 0x08) | \
      ((n >>  6) & 0x04) | \
      ((n >>  3) & 0x02) | \
      ((n      ) & 0x01)   \
      )
#define       Bin(n)                 LongToBin(0x##n##l)	//write binary charactor set,exsample : Bin(11111111) = 0xff





#endif

/***************************************************************
*    END
****************************************************************/

