/**
  *******************************************************************
  * @file    reg_stm32f303_dac.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-22
  * @brief   STM32F303 DAC寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef __REG_STM32F303_DAC_H__
#define	__REG_STM32F303_DAC_H__

#include "typedefine.h"
#include "reg_stm32f303_address.h"


/** DAC 控制寄存器位定义 */
typedef struct
{
	UINT32	EN1						: 1;			/**< Bit0，DAC通道1使能 */
	UINT32	BOFF1_OUTEN1			: 1;			/**< Bit1，在DAC1：DAC通道1输出缓冲禁止，在DAC2（只有STM32F303x6/8，STM32F328x8才有）：DAC通道1输出切换使能 */
	UINT32	TEN1					: 1;			/**< Bit2，DAC通道1触发使能 */
	UINT32	TSEL1					: 3;			/**< Bit3~5，DAC通道1触发选择 */
	UINT32	WAVE1					: 2;			/**< Bit6~7，DAC通道1噪音/三角波产生使能 */
	UINT32	MAMP1					: 4;			/**< Bit8~11，DAC通道1掩码/振幅选择器 */
	UINT32	DMAEN1					: 1;			/**< Bit12，DAC通道1DMA使能 */
	UINT32	DMAUDRIE1				: 1;			/**< Bit13，DAC通道1拖载中断使能 */
	UINT32	Rsvd1					: 2;			/**< Bit14~15，保留 */
	UINT32	EN2						: 1;			/**< Bit16，DAC通道2使能 */
	UINT32	BOFF2_OUTEN2			: 1;			/**< Bit17，在DAC1：DAC通道2输出缓冲禁止，在DAC2（只有STM32F303x6/8，STM32F328x8才有）：DAC通道2输出切换使能 */
	UINT32	TEN2					: 1;			/**< Bit18，DAC通道2触发使能 */
	UINT32	TSEL2					: 3;			/**< Bit19~21，DAC通道2触发器选择 */
	UINT32	WAVE2					: 2;			/**< Bit22~23，DAC通道2噪音/三角波发生器使能 */
	UINT32	MAMP2					: 4;			/**< Bit24~27，DAC通道2掩码/振幅选择器 */
	UINT32	DMAEN2					: 1;			/**< Bit28，DAC通道2DMA使能 */
	UINT32	DMAUDRIE2				: 1;			/**< Bit29，DAC通道2拖载中断使能 */
	UINT32	Rsvd2					: 2;			/**< Bit30~31，保留 */
}DacCrBitType;

/** DAC控制寄存器定义 */
typedef union
{
	UINT32	all;
	DacCrBitType	bit;
}DacCrType;

/** DAC软件触发寄存器位定义 */
typedef struct
{
	UINT32	SWTRIG1		: 1;			/**< Bit0，DAC通道1软件触发 */
	UINT32	SWTRIG2		: 1;			/**< Bit1，DAC通道2软件触发 */
	UINT32	Rsvd1			: 30;			/**< Bit2~31，保留 */
}DacSwtrigrBitType;

/** DAC软件触发寄存器定义 */
typedef union
{
	UINT32	all;
	DacSwtrigrBitType		bit;
}DacSwtrigrType;

/** DAC通道1 12位右对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32 DACC1DHR		: 12;			/**< Bit0~11，DAC通道1 12位右对齐数据 */
	UINT32 Rsvd1		: 20;			/**< Bit12~31，保留 */
}DacDhr12r1BitType;

/** DAC通道1 12位右对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr12r1BitType		bit;
}DacDhr12r1Type;

/** DAC通道1 12位左对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32 Rsvd1				: 4;			/**< Bit0~3，保留 */
	UINT32 DACC1DHR		: 12;			/**< Bit4~15，DAC通道1 12位左对齐数据 */
	UINT32 Rsvd2				: 16;			/**< Bit16~31，保留 */
}DacDhr12l1BitType;

/** DAC通道1 12位左对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr12l1BitType		bit;
}DacDhr12l1Type;

/** DAC通道1 8位右对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32 DACC1DHR		: 8;			/**< Bit0~7，DAC通道1 8位右对齐数据 */
	UINT32 Rsvd1				: 24;			/**< Bit8~31，保留 */
}DacDhr8r1BitType;

/** DAC通道1 8位右对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr8r1BitType		bit;
}DacDhr8r1Type;

/** DAC通道2 12位右对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32 DACC2DHR		: 12;			/**< Bit0~11，DAC通道2 12位右对齐数据 */
	UINT32 Rsvd1				: 20;			/**< Bit12~31，保留 */
}DacDhr12r2BitType;

/** DAC通道2 12位右对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr12r2BitType		bit;
}DacDhr12r2Type;

/** DAC通道2 12位左对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32 Rsvd1				: 4;			/**< Bit0~3，保留 */
	UINT32 DACC2DHR		: 12;			/**< Bit4~15，DAC通道2 12位左对齐数据 */
	UINT32 Rsvd2				: 16;			/**< Bit16~31，保留 */
}DacDhr12l2BitType;

/** DAC通道2 12位左对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr12l2BitType		bit;
}DacDhr12l2Type;

/** DAC通道2 8位右对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32 DACC2DHR		: 8;			/**< Bit0~7，DAC通道2 8位右对齐数据 */
	UINT32 Rsvd1				: 24;			/**< Bit8~31，保留 */
}DacDhr8r2BitType;

/** DAC通道2 8位右对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr8r2BitType		bit;
}DacDhr8r2Type;

/**　双重DAC 12位右对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32	DACC1DHR		: 12;				/**< Bit0~11，DAC通道1 12位右对齐数据 */
	UINT32	Rsvd1				: 4;				/**< Bit12~15，保留 */
	UINT32	DACC2DHR		: 12;				/**< Bit16~27，DAC通道2 12位右对齐数据 */
	UINT32	Rsvd2				: 4;				/**< Bit28~31，保留 */
}DacDhr12rdBitType;

/** 双重DAC 12位右对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr12rdBitType		bit;
}DacDhr12rdType;

/**　双重DAC 12位对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32	Rsvd1				: 4;				/**< Bit0~3，保留 */
	UINT32	DACC1DHR		: 12;				/**< Bit4~15，DAC通道1 12位左对齐数据 */
	UINT32	Rsvd2				: 4;				/**< Bit16~19，保留 */
	UINT32	DACC2DHR		: 12;				/**< Bit20~31，DAC通道2 12位左对齐数据 */
}DacDhr12ldBitType;

/** 双重DAC 12位左对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr12ldBitType		bit;
}DacDhr12ldType;

/**　双重DAC 8位右对齐数据保持寄存器位定义 */
typedef struct
{
	UINT32	DACC1DHR		: 8;				/**< Bit0~7，DAC通道1 8位右对齐数据 */
	UINT32	DACC2DHR		: 8;				/**< Bit8~15，DAC通道2 8位右对齐数据 */
	UINT32	Rsvd1				: 16;				/**< Bit28~31，保留 */
}DacDhr8rdBitType;

/** 双重DAC 8位右对齐数据保持寄存器定义 */
typedef union
{
	UINT32	all;
	DacDhr8rdBitType		bit;
}DacDhr8rdType;

/** DAC通道1数据输出寄存器位定义 */
typedef struct
{
	UINT32	DACC1DOR		: 12;			/**< Bit0~11，DAC通道1数据输出 */
	UINT32	Rsvd1				: 20;			/**< Bit12~31，保留 */
}DacDor1BitType;

/** DAC通道1数据输出寄存器定义 */
typedef union
{
	UINT32	all;
	DacDor1BitType	bit;
}DacDor1Type;

/** DAC通道2数据输出寄存器位定义 */
typedef struct
{
	UINT32	DACC2DOR		: 12;			/**< Bit0~11，DAC通道2数据输出 */
	UINT32	Rsvd1				: 20;			/**< Bit12~31，保留 */
}DacDor2BitType;

/** DAC通道2数据输出寄存器定义 */
typedef union
{
	UINT32	all;
	DacDor2BitType	bit;
}DacDor2Type;

/** DAC状态寄存器位定义 */
typedef struct
{
	UINT32	Rsvd1			: 13;			/**< Bit0~12，保留 */
	UINT32	DMAUDR1		: 1;			/**< Bit13，DAC通道1 DMA拖载标志 */
	UINT32	Rsvd2			: 15;			/**< Bit14~28，保留 */
	UINT32	DMAUDR2		: 1;			/**< Bit29，DAC通道2 DMA拖载标志 */
	UINT32	Rsvd3			: 2;			/**< Bit30，保留 */
}DacSrBitType;

/** DAC状态寄存器定义 */
typedef union
{
	UINT32	all;
	DacSrBitType	bit;
}DacSrType;


/** DAC寄存器 */
typedef struct
{
	DacCrType			CR;								/**< DAC控制寄存器 ，偏移地址 0x00*/
	DacSwtrigrType		SWTRIGR;					/**< DAC软件触发寄存器 ，偏移地址 0x04*/
	DacDhr12r1Type		DHR12R1;					/**< DAC通道1 12位右对齐数据保持寄存器 ，偏移地址 0x08*/
	DacDhr12l1Type		DHR12L1;					/**< DAC通道1 12位左对齐数据保持寄存器 ，偏移地址 0x0c*/
	DacDhr8r1Type		DHR8R1;						/**< DAC通道1 8位右对齐数据保持寄存器 ，偏移地址 0x10*/
	DacDhr12r2Type		DHR12R2;					/**< DAC通道2 12位右对齐数据保持寄存器 ，偏移地址 0x14*/
	DacDhr12l2Type		DHR12L2;					/**< DAC通道2 12位左对齐数据保持寄存器 ，偏移地址 0x18*/
	DacDhr8r2Type		DHR8R2;						/**< DAC通道2 8位右对齐数据保持寄存器 ，偏移地址 0x1c*/
	DacDhr12rdType		DHR12RD;					/**< 双重DAC 12位右对齐数据保持寄存器 ，偏移地址 0x20*/
	DacDhr12ldType		DHR12LD;					/**< 双重DAC 12位左对齐数据保持寄存器 ，偏移地址 0x24*/
	DacDhr8rdType		DHR8RD;						/**< 双重DAC 8位右对齐数据保持寄存器 ，偏移地址 0x28*/
	DacDor1Type			DOR1;							/**< DAC通道1数据输出寄存器 ，偏移地址 0x2c*/
	DacDor2Type			DOR2;							/**< DAC通道2数据输出寄存器 ，偏移地址 0x30*/
	DacSrType			SR;								/**< DAC状态寄存器 ，偏移地址 0x34*/
}DacType;




/** DAC 模块定义 */
#define	DAC		((DacType	*) DAC_BASE)



#endif
	
	
	
