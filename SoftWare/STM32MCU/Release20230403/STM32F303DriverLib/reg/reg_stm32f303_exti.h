/**
  *******************************************************************
  * @file    reg_stm32f303_exti.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-22
  * @brief   STM32F303 EXTI寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef __REG_STM32F303_EXTI_H__
#define __REG_STM32F303_EXTI_H__


#include "reg_stm32f303_address.h"



/** 中断屏蔽寄存器1位定义 */
typedef struct
{
	UINT32	MR0			: 1;				/**< Bit0，屏蔽口线0外部或内部中断 */
	UINT32	MR1			: 1;				/**< Bit1，屏蔽口线1外部或内部中断 */
	UINT32	MR2			: 1;				/**< Bit2，屏蔽口线2外部或内部中断 */
	UINT32	MR3			: 1;				/**< Bit3，屏蔽口线3外部或内部中断 */
	UINT32	MR4			: 1;				/**< Bit4，屏蔽口线4外部或内部中断 */
	UINT32	MR5			: 1;				/**< Bit5，屏蔽口线5外部或内部中断 */
	UINT32	MR6			: 1;				/**< Bit6，屏蔽口线6外部或内部中断 */
	UINT32	MR7			: 1;				/**< Bit7，屏蔽口线7外部或内部中断 */
	UINT32	MR8			: 1;				/**< Bit8，屏蔽口线8外部或内部中断 */
	UINT32	MR9			: 1;				/**< Bit9，屏蔽口线9外部或内部中断 */
	UINT32	MR10		: 1;				/**< Bit10，屏蔽口线10外部或内部中断 */
	UINT32	MR11		: 1;				/**< Bit11，屏蔽口线11外部或内部中断 */
	UINT32	MR12		: 1;				/**< Bit12，屏蔽口线12外部或内部中断 */
	UINT32	MR13		: 1;				/**< Bit13，屏蔽口线13外部或内部中断 */
	UINT32	MR14		: 1;				/**< Bit14，屏蔽口线14外部或内部中断 */
	UINT32	MR15		: 1;				/**< Bit15，屏蔽口线15外部或内部中断 */
	UINT32	MR16		: 1;				/**< Bit16，屏蔽口线16外部或内部中断 */
	UINT32	MR17		: 1;				/**< Bit17，屏蔽口线17外部或内部中断 */
	UINT32	MR18		: 1;				/**< Bit18，屏蔽口线18外部或内部中断 */
	UINT32	MR19		: 1;				/**< Bit19，屏蔽口线19外部或内部中断 */
	UINT32	MR20		: 1;				/**< Bit20，屏蔽口线20外部或内部中断 */
	UINT32	MR21		: 1;				/**< Bit21，屏蔽口线21外部或内部中断 */
	UINT32	MR22		: 1;				/**< Bit22，屏蔽口线22外部或内部中断 */
	UINT32	MR23		: 1;				/**< Bit23，屏蔽口线23外部或内部中断 */
	UINT32	MR24		: 1;				/**< Bit24，屏蔽口线24外部或内部中断 */
	UINT32	MR25		: 1;				/**< Bit25，屏蔽口线25外部或内部中断 */
	UINT32	MR26		: 1;				/**< Bit26，屏蔽口线26外部或内部中断 */
	UINT32	MR27		: 1;				/**< Bit27，屏蔽口线27外部或内部中断 */
	UINT32	MR28		: 1;				/**< Bit28，屏蔽口线28外部或内部中断 */
	UINT32	MR29		: 1;				/**< Bit29，屏蔽口线29外部或内部中断 */
	UINT32	MR30		: 1;				/**< Bit30，屏蔽口线30外部或内部中断 */
	UINT32	MR31		: 1;				/**< Bit31，屏蔽口线31外部或内部中断 */
}ExtiImr1BitType;

/** 中断屏蔽寄存器1定义 */
typedef union
{
	UINT32	all;
	ExtiImr1BitType		bit;
}ExtiImr1Type;

/** 事件屏蔽寄存器1位定义 */
typedef struct
{
	UINT32	MR0			: 1;			/**< Bit0，屏蔽口线0外部或内部事件 */
	UINT32	MR1			: 1;			/**< Bit1，屏蔽口线1外部或内部事件 */
	UINT32	MR2			: 1;			/**< Bit2，屏蔽口线2外部或内部事件 */
	UINT32	MR3			: 1;			/**< Bit3，屏蔽口线3外部或内部事件 */
	UINT32	MR4			: 1;			/**< Bit4，屏蔽口线4外部或内部事件 */
	UINT32	MR5			: 1;			/**< Bit5，屏蔽口线5外部或内部事件 */
	UINT32	MR6			: 1;			/**< Bit6，屏蔽口线6外部或内部事件 */
	UINT32	MR7			: 1;			/**< Bit7，屏蔽口线7外部或内部事件 */
	UINT32	MR8			: 1;			/**< Bit8，屏蔽口线8外部或内部事件 */
	UINT32	MR9			: 1;			/**< Bit9，屏蔽口线9外部或内部事件 */
	UINT32	MR10		: 1;			/**< Bit10，屏蔽口线10外部或内部事件 */
	UINT32	MR11		: 1;			/**< Bit11，屏蔽口线11外部或内部事件 */
	UINT32	MR12		: 1;			/**< Bit12，屏蔽口线12外部或内部事件 */
	UINT32	MR13		: 1;			/**< Bit13，屏蔽口线13外部或内部事件 */
	UINT32	MR14		: 1;			/**< Bit14，屏蔽口线14外部或内部事件 */
	UINT32	MR15		: 1;			/**< Bit15，屏蔽口线15外部或内部事件 */
	UINT32	MR16		: 1;			/**< Bit16，屏蔽口线16外部或内部事件 */
	UINT32	MR17		: 1;			/**< Bit17，屏蔽口线17外部或内部事件 */
	UINT32	MR18		: 1;			/**< Bit18，屏蔽口线18外部或内部事件 */
	UINT32	MR19		: 1;			/**< Bit19，屏蔽口线19外部或内部事件 */
	UINT32	MR20		: 1;			/**< Bit20，屏蔽口线20外部或内部事件 */
	UINT32	MR21		: 1;			/**< Bit21，屏蔽口线21外部或内部事件 */
	UINT32	MR22		: 1;			/**< Bit22，屏蔽口线22外部或内部事件 */
	UINT32	MR23		: 1;			/**< Bit23，屏蔽口线23外部或内部事件 */
	UINT32	MR24		: 1;			/**< Bit24，屏蔽口线24外部或内部事件 */
	UINT32	MR25		: 1;			/**< Bit25，屏蔽口线25外部或内部事件 */
	UINT32	MR26		: 1;			/**< Bit26，屏蔽口线26外部或内部事件 */
	UINT32	MR27		: 1;			/**< Bit27，屏蔽口线27外部或内部事件 */
	UINT32	MR28		: 1;			/**< Bit28，屏蔽口线28外部或内部事件 */
	UINT32	MR29		: 1;			/**< Bit29，屏蔽口线29外部或内部事件 */
	UINT32	MR30		: 1;			/**< Bit30，屏蔽口线30外部或内部事件 */
	UINT32	MR31		: 1;			/**< Bit31，屏蔽口线31外部或内部事件 */
}ExtiEmr1BitType;

/** 事件屏蔽寄存器1位定义 */
typedef union
{
	UINT32	all;
	ExtiEmr1BitType		bit;
}ExtiEmr1Type;

/** 上升沿触发选择寄存器1位定义 */
typedef	struct
{
	UINT32	TR0			: 1;			/**< Bit0，口线0上升沿触发事件配置位 */
	UINT32	TR1			: 1;			/**< Bit1，口线1上升沿触发事件配置位 */
	UINT32	TR2			: 1;			/**< Bit2，口线2上升沿触发事件配置位 */
	UINT32	TR3			: 1;			/**< Bit3，口线3上升沿触发事件配置位 */
	UINT32	TR4			: 1;			/**< Bit4，口线4上升沿触发事件配置位 */
	UINT32	TR5			: 1;			/**< Bit5，口线5上升沿触发事件配置位 */
	UINT32	TR6			: 1;			/**< Bit6，口线6上升沿触发事件配置位 */
	UINT32	TR7			: 1;			/**< Bit7，口线7上升沿触发事件配置位 */
	UINT32	TR8			: 1;			/**< Bit8，口线8上升沿触发事件配置位 */
	UINT32	TR9			: 1;			/**< Bit9，口线9上升沿触发事件配置位 */
	UINT32	TR10		: 1;			/**< Bit10，口线10上升沿触发事件配置位 */
	UINT32	TR11		: 1;			/**< Bit11，口线11上升沿触发事件配置位 */
	UINT32	TR12		: 1;			/**< Bit12，口线12上升沿触发事件配置位 */
	UINT32	TR13		: 1;			/**< Bit13，口线13上升沿触发事件配置位 */
	UINT32	TR14		: 1;			/**< Bit14，口线14上升沿触发事件配置位 */
	UINT32	TR15		: 1;			/**< Bit15，口线15上升沿触发事件配置位 */
	UINT32	TR16		: 1;			/**< Bit16，口线16上升沿触发事件配置位 */
	UINT32	TR17		: 1;			/**< Bit17，口线17上升沿触发事件配置位 */
	UINT32	TR18		: 1;			/**< Bit18，口线18上升沿触发事件配置位 */
	UINT32	TR19		: 1;			/**< Bit19，口线19上升沿触发事件配置位 */
	UINT32	TR20		: 1;			/**< Bit20，口线20上升沿触发事件配置位 */
	UINT32	TR21		: 1;			/**< Bit21，口线21上升沿触发事件配置位 */
	UINT32	TR22		: 1;			/**< Bit22，口线22上升沿触发事件配置位 */
	UINT32	Rsvd1		: 6;			/**< Bit23~28，保留 */
	UINT32	TR29		: 1;			/**< Bit29，口线29上升沿触发事件配置位 */
	UINT32	TR30		: 1;			/**< Bit30，口线30上升沿触发事件配置位 */
	UINT32	TR31		: 1;			/**< Bit31，口线31上升沿触发事件配置位 */
}ExtiRtsr1BitType;

/** 上升沿触发选择寄存器1定义 */
typedef union
{
	UINT32	all;
	ExtiRtsr1BitType		bit;
}ExtiRtsr1Type;

/** 下降沿触发选择寄存器1位定义 */
typedef struct
{
	UINT32	TR0			: 1;			/**< Bit0，口线0下降沿触发事件配置位 */
	UINT32	TR1			: 1;			/**< Bit1，口线1下降沿触发事件配置位 */
	UINT32	TR2			: 1;			/**< Bit2，口线2下降沿触发事件配置位 */
	UINT32	TR3			: 1;			/**< Bit3，口线3下降沿触发事件配置位 */
	UINT32	TR4			: 1;			/**< Bit4，口线4下降沿触发事件配置位 */
	UINT32	TR5			: 1;			/**< Bit5，口线5下降沿触发事件配置位 */
	UINT32	TR6			: 1;			/**< Bit6，口线6下降沿触发事件配置位 */
	UINT32	TR7			: 1;			/**< Bit7，口线7下降沿触发事件配置位 */
	UINT32	TR8			: 1;			/**< Bit8，口线8下降沿触发事件配置位 */
	UINT32	TR9			: 1;			/**< Bit9，口线9下降沿触发事件配置位 */
	UINT32	TR10		: 1;			/**< Bit10，口线10下降沿触发事件配置位 */
	UINT32	TR11		: 1;			/**< Bit11，口线11下降沿触发事件配置位 */
	UINT32	TR12		: 1;			/**< Bit12，口线12下降沿触发事件配置位 */
	UINT32	TR13		: 1;			/**< Bit13，口线13下降沿触发事件配置位 */
	UINT32	TR14		: 1;			/**< Bit14，口线14下降沿触发事件配置位 */
	UINT32	TR15		: 1;			/**< Bit15，口线15下降沿触发事件配置位 */
	UINT32	TR16		: 1;			/**< Bit16，口线16下降沿触发事件配置位 */
	UINT32	TR17		: 1;			/**< Bit17，口线17下降沿触发事件配置位 */
	UINT32	TR18		: 1;			/**< Bit18，口线18下降沿触发事件配置位 */
	UINT32	TR19		: 1;			/**< Bit19，口线19下降沿触发事件配置位 */
	UINT32	TR20		: 1;			/**< Bit20，口线20下降沿触发事件配置位 */
	UINT32	TR21		: 1;			/**< Bit21，口线21下降沿触发事件配置位 */
	UINT32	TR22		: 1;			/**< Bit22，口线22下降沿触发事件配置位 */
	UINT32	Rsvd1		: 6;			/**< Bit23~28，保留 */
	UINT32	TR29		: 1;			/**< Bit29，口线29下降沿触发事件配置位 */
	UINT32	TR30		: 1;			/**< Bit30，口线30下降沿触发事件配置位 */
	UINT32	TR31		: 1;			/**< Bit31，口线31下降沿触发事件配置位 */
}ExtiFtsr1BitType;

/** 下降沿触发选择寄存器1位定义 */
typedef union
{
	UINT32	all;
	ExtiFtsr1BitType bit;
}ExtiFtsr1Type;

/** 软件中断事件寄存器1位定义 */
typedef struct
{
	UINT32	SWIER0		: 1;		/**< Bit0，口线0软件中断 */
	UINT32	SWIER1		: 1;		/**< Bit1，口线1软件中断 */
	UINT32	SWIER2		: 1;		/**< Bit2，口线2软件中断 */
	UINT32	SWIER3		: 1;		/**< Bit3，口线3软件中断 */
	UINT32	SWIER4		: 1;		/**< Bit4，口线4软件中断 */
	UINT32	SWIER5		: 1;		/**< Bit5，口线5软件中断 */
	UINT32	SWIER6		: 1;		/**< Bit6，口线6软件中断 */
	UINT32	SWIER7		: 1;		/**< Bit7，口线7软件中断 */
	UINT32	SWIER8		: 1;		/**< Bit8，口线8软件中断 */
	UINT32	SWIER9		: 1;		/**< Bit9，口线9软件中断 */
	UINT32	SWIER10		: 1;		/**< Bit10，口线10软件中断 */
	UINT32	SWIER11		: 1;		/**< Bit11，口线11软件中断 */
	UINT32	SWIER12		: 1;		/**< Bit12，口线12软件中断 */
	UINT32	SWIER13		: 1;		/**< Bit13，口线13软件中断 */
	UINT32	SWIER14		: 1;		/**< Bit14，口线14软件中断 */
	UINT32	SWIER15		: 1;		/**< Bit15，口线15软件中断 */
	UINT32	SWIER16		: 1;		/**< Bit16，口线16软件中断 */
	UINT32	SWIER17		: 1;		/**< Bit17，口线17软件中断 */
	UINT32	SWIER18		: 1;		/**< Bit18，口线18软件中断 */
	UINT32	SWIER19		: 1;		/**< Bit19，口线19软件中断 */
	UINT32	SWIER20		: 1;		/**< Bit20，口线20软件中断 */
	UINT32	SWIER21		: 1;		/**< Bit21，口线21软件中断 */
	UINT32	SWIER22		: 1;		/**< Bit22，口线22软件中断 */
	UINT32	Rsvd1			: 6;		/**< Bit23~28，保留 */
	UINT32	SWIER29		: 1;		/**< Bit29，口线29软件中断 */
	UINT32	SWIER30		: 1;		/**< Bit30，口线30软件中断 */
	UINT32	SWIER31		: 1;		/**< Bit31，口线31软件中断 */
}ExtiSwier1BitType;

/** 软件中断事件寄存器1位定义 */
typedef union
{
	UINT32	all;
	ExtiSwier1BitType		bit;
}ExtiSwier1Type;

/** 挂起寄存器1位定义 */
typedef struct
{
	UINT32	PR0			: 1;			/**< Bit0，口线0挂起位 */
	UINT32	PR1			: 1;			/**< Bit1，口线1挂起位 */
	UINT32	PR2			: 1;			/**< Bit2，口线2挂起位 */
	UINT32	PR3			: 1;			/**< Bit3，口线3挂起位 */
	UINT32	PR4			: 1;			/**< Bit4，口线4挂起位 */
	UINT32	PR5			: 1;			/**< Bit5，口线5挂起位 */
	UINT32	PR6			: 1;			/**< Bit6，口线6挂起位 */
	UINT32	PR7			: 1;			/**< Bit7，口线7挂起位 */
	UINT32	PR8			: 1;			/**< Bit8，口线8挂起位 */
	UINT32	PR9			: 1;			/**< Bit9，口线9挂起位 */
	UINT32	PR10		: 1;			/**< Bit10，口线10挂起位 */
	UINT32	PR11		: 1;			/**< Bit11，口线11挂起位 */
	UINT32	PR12		: 1;			/**< Bit12，口线12挂起位 */
	UINT32	PR13		: 1;			/**< Bit13，口线13挂起位 */
	UINT32	PR14		: 1;			/**< Bit14，口线14挂起位 */
	UINT32	PR15		: 1;			/**< Bit15，口线15挂起位 */
	UINT32	PR16		: 1;			/**< Bit16，口线16挂起位 */
	UINT32	PR17		: 1;			/**< Bit17，口线17挂起位 */
	UINT32	PR18		: 1;			/**< Bit18，口线18挂起位 */
	UINT32	PR19		: 1;			/**< Bit19，口线19挂起位 */
	UINT32	PR20		: 1;			/**< Bit20，口线20挂起位 */
	UINT32	PR21		: 1;			/**< Bit21，口线21挂起位 */
	UINT32	PR22		: 1;			/**< Bit22，口线22挂起位 */
	UINT32	Rsvd1		: 6;			/**< Bit23~28，保留 */
	UINT32	PR29		: 1;			/**< Bit29，口线29挂起位 */
	UINT32	PR30		: 1;			/**< Bit30，口线30挂起位 */
	UINT32	PR31		: 1;			/**< Bit31，口线31挂起位 */
}ExtiPr1BitType;

/** 挂起寄存器1定义 */
typedef union
{
	UINT32	all;
	ExtiPr1BitType	bit;
}ExtiPr1Type;

/** 中断屏蔽寄存器2位定义 */
typedef struct
{
	UINT32	MR32		: 1;			/**< Bit0，口线32内部或外部中断屏蔽 */
	UINT32	MR33		: 1;			/**< Bit1，口线33内部或外部中断屏蔽 */
	UINT32	MR34		: 1;			/**< Bit2，口线34内部或外部中断屏蔽 */
	UINT32	MR35		: 1;			/**< Bit3，口线35内部或外部中断屏蔽 */
	UINT32	Rsvd1		: 28;			/**< Bit4~31，保留 */
}ExtiImr2BitType;

/** 中断屏蔽寄存器2定义 */
typedef union
{
	UINT32	all;
	ExtiImr2BitType		bit;
}ExtiImr2Type;

/** 事件屏蔽寄存器2位定义 */
typedef struct
{
	UINT32	MR32		: 1;			/**< Bit0，口线32外部或内部事件屏蔽 */
	UINT32	MR33		: 1;			/**< Bit1，口线33外部或内部事件屏蔽 */
	UINT32	MR34		: 1;			/**< Bit2，口线34外部或内部事件屏蔽 */
	UINT32	MR35		: 1;			/**< Bit3，口线35外部或内部事件屏蔽 */
	UINT32	Rsvd1		: 28;			/**< Bit4~31，保留 */
}ExtiEmr2BitType;

/** 事件屏蔽寄存器2位定义 */
typedef union
{
	UINT32	all;
	ExtiEmr2BitType		bit;
}ExtiEmr2Type;

/** 上升沿触发选择寄存器2位定义 */
typedef struct
{
	UINT32	TR32		: 1;		/**< Bit0，口线32上升沿触发事件配置位 */
	UINT32	TR33		: 1;		/**< Bit1，口线33上升沿触发事件配置位 */
	UINT32	Rsvd1		: 30;		/**< Bit2~31，保留 */
}ExtiRtsr2BitType;

/** 上升沿触发选择寄存器2定义 */
typedef union
{
	UINT32	all;
	ExtiRtsr2BitType		bit;
}ExtiRtsr2Type;

/** 下降沿触发选择寄存器2位定义 */
typedef struct
{
	UINT32	TR32		: 1;		/**< Bit0，口线32下降沿触发事件配置位 */
	UINT32	TR33		: 1;		/**< Bit1，口线33下降沿触发事件配置位 */
	UINT32	Rsvd1		: 30;		/**< Bit2~31，保留 */
}ExtiFtsr2BitType;

/** 下降沿触发选择寄存器2定义 */
typedef union
{
	UINT32	all;
	ExtiFtsr2BitType	bit;
}ExtiFtsr2Type;

/** 软件中断事件寄存器2位定义 */
typedef struct
{
	UINT32	SWIER32		: 1;		/**< Bit0，口线32软件中断 */
	UINT32	SWIER33		: 1;		/**< Bit1，口线33软件中断 */
	UINT32	Rsvd1			: 30;		/**< Bit2~31，保留 */
}ExtiSwier2BitType;

/** 软件中断事件寄存器2位定义 */
typedef union
{
	UINT32	all;
	ExtiSwier2BitType		bit;
}ExtiSwier2Type;

/** 挂起寄存器2位定义 */
typedef struct
{
	UINT32	PR32		: 1;			/**< Bit0，口线32挂起位 */
	UINT32	PR33		: 1;			/**< Bit1，口线33挂起位 */
	UINT32	Rsvd1		: 30;			/**< Bit2~31，保留 */	
}ExtiPr2BitType;

/** 挂起寄存器2定义 */
typedef union
{
	UINT32	all;
	ExtiPr2BitType	bit;
}ExtiPr2Type;


/** EXTI寄存器 */
typedef struct
{
	ExtiImr1Type		IMR1;					/**< 中断屏蔽寄存器1，偏移地址0x00 */
	ExtiEmr1Type		EMR1;					/**< 事件屏蔽寄存器1，偏移地址0x04 */
	ExtiRtsr1Type		RTSR1;				/**< 上升沿触发选择寄存器1，偏移地址0x08 */
	ExtiFtsr1Type		FTSR1;				/**< 下降沿触发选择寄存器1，偏移地址0x0c */
	ExtiSwier1Type		SWIER1;				/**< 软件中断事件寄存器1，偏移地址0x10 */
	ExtiPr1Type			PR1;					/**< 挂起寄存器1，偏移地址0x14 */
	UINT32				Rsvd1[2];			/**< 保留，偏移地址0x18~0x1c */
	ExtiImr2Type		IMR2;					/**< 中断屏蔽寄存器2，偏移地址0x20 */
	ExtiEmr2Type		EMR2;					/**< 事件屏蔽寄存器2，偏移地址0x24 */
	ExtiRtsr2Type		RTSR2;				/**< 上升沿触发选择寄存器2，偏移地址0x28 */
	ExtiFtsr2Type		FTSR2;				/**< 下降沿触发选择寄存器2，偏移地址0x2c */
	ExtiSwier2Type	SWIER2;					/**< 软件中断事件寄存器2，偏移地址0x30 */
	ExtiPr2Type			PR2;					/**< 挂起寄存器2，偏移地址0x34 */
}ExtiType;



/** EXTI寄存器地址 */
#define	EXTI		((ExtiType *) EXTI_BASE)



#endif
