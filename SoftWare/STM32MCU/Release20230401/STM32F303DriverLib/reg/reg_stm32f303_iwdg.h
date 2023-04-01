/**
  *******************************************************************
  * @file    reg_stm32f303_iwdg.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-23
  * @brief   STM32F303 IWDG寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __REG_STM32F303_IWDG_H__
#define __REG_STM32F303_IWDG_H__

#include "reg_stm32f303_address.h"



/**< 看门狗分频寄存器位定义 */
typedef struct
{
    UINT32	PR		: 3;             /**< Bit0~2， 预分频寄存器预分频因子位，000预分频因子=4，001预分频因子=8，010预分频因子=16，011预分频因子=32，100预分频因子=64，101预分频因子=128，110预分频因子=256 111预分频因子=256 */
	UINT32	Rsvd1	: 29;            /**< Bit3~31，保留 */
}IwdgPrBitType;

/**< 看门狗分频寄存器定义 */
typedef union
{
	UINT32	all;						/**< 看门狗分频寄存器所有位 */
	IwdgPrBitType	bit;				/**< 看门狗分频寄存器位定义 */
}IwdgPrType;

/**< 看门狗计数器重装寄存器位定义 */
typedef struct
{
	UINT32	RL		: 12;            /**< Bit0~11，看门狗计数器重装寄存器位 */
	UINT32	RSVD1	: 20;            /**< Bit12~31，保留 */
}IwdgRlrBitType;

/**< 看门狗计数器重装寄存器定义 */
typedef union
{
	UINT32	all;						/**< 看门狗重装寄存器所有位 */
	IwdgRlrBitType	bit;				/**< 看门狗重装寄存器位定义 */
}IwdgRlrType;

/**< 看门狗状态寄存器定义 */
typedef struct
{
	UINT32	PVU		: 1;                /**< Bit0，看门狗预分频值更新位，硬件置1或清零 */
	UINT32	RVU		: 1;                /**< Bit1，看门狗计数器重装载值更新位，硬件置1或清零 */
	UINT32	WVU		: 1;                /**< Bit2，窗口看门狗计数器值更新位，硬件置1或清零 */ 
	UINT32	Rsvd1	: 29;				/**< Bit3~31，保留 */
}IwdgSrBitType;

/**< 看门狗状态寄存器定义 */
typedef union
{
	UINT32	all;						/**< 看门狗状态寄存器所有位 */
	IwdgSrBitType	bit;				/**< 看门狗状态寄存器位定义 */
}IwdgSrType;

/**< 看门狗窗口寄存器位定义 */
typedef struct
{
	UINT32	WIN		: 12;               /**< Bit0~11，看门狗计数器窗口值*/
	UINT32	Rsvd1	: 20;               /**< Bit12~31，保留*/
}IwdgWinrBitType;

/**< 看门狗窗口寄存器定义 */
typedef union
{
	UINT32		all;                 	/**< 窗口看门狗计数器值所有位 */   
	IwdgWinrBitType		bit;         	/**< 窗口看门狗计数器值位定义 */
}IwdgWinrType; 

/** IWDG寄存器 */
typedef struct
{   
	UINT16			KR;          	/**< 键值寄存器，偏移地址：0x00 */
	UINT16			Rsvd1;			/**< 保留 */
	IwdgPrType		PR;          	/**< 预分频寄存器，偏移地址：0x04 */
	IwdgRlrType		RLR;          	/**< 看门狗计数器重装寄存器，偏移地址：0x08 */
	IwdgSrType		SR;          	/**< 看门狗状态寄存器，偏移地址：0x0C */
	IwdgWinrType	WINR;        	/**< 窗口看门狗寄存器，偏移地址：0x10 */
}IwdgType;


/** IWDG寄存器地址 */
#define	IWDG	((IwdgType *) IWDG_BASE) 
	


#endif
