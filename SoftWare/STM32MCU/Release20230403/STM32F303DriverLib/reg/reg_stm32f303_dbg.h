/**
  *******************************************************************
  * @file    reg_stm32f303_dbg.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-23
  * @brief   STM32F303 调试寄存器定义头文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __REG_STM32F303_DBG_H__
#define __REG_STM32F303_DBG_H__


#include "reg_stm32f303_address.h"


/** 调试处理器ID寄存器位定义 */
typedef struct
{
	UINT32	DEV_ID		: 12;		/**< Bit0~11，设备ID */
	UINT32	Rsvd1		: 4;		/**< Bit12~15，保留 */
	UINT32	REV_ID		: 16;		/**< Bit16~31，版本ID */
}DbgmcuIdcodeBitType;

/** 调试处理器ID寄存器定义 */
typedef union
{
	UINT32		all;
	DbgmcuIdcodeBitType		bit;
}DbgmcuIdcodeType;

/** 调试处理器控制寄存器位定义 */
typedef struct
{
	UINT32		DBG_SLEEP		: 1;		/**< Bit0，调试睡眠模式位，0：在睡眠模式中，FCLK开, HCLK关，FCLK由系统时钟提供，1：FCLK关, HCLK开，由系统时钟提供	*/
	UINT32		DBG_STOP		: 1;		/**< Bit1，调试停止模式位，0：在此模式下，FCLK 与 HCLK为0，时钟控制器关闭所有时钟，1：FCLK 与 HCLK由外部时钟提供 */
	UINT32		DBG_STANDBY		: 1;		/**< Bit2，调试待机模式，0：FCLK=Off, HCLK=Off，所以数字部分关闭，1：FCLK=On, HCLK=On */
	UINT32		Rsvd1			: 2;		/**< Bit3~4，保留 */
	UINT32		TRACE_IOEN		: 1;		/**< Bit5，跟踪引脚分配模式使能位，0：失能，1：跟踪引脚分配模式使能 */
	UINT32		TRACE_MODE		: 2;		/**< Bit6~7，跟踪引脚分配模式位，00：异步方式，01:同步方式，数据长度为1，10：数据长度为2,11：数据长度为4 */
	UINT32		Rsvd2			: 24;		/**< Bit8~31，保留 */
}DbgmcuCrBitType;

/** 调试处理器控制寄存器定义 */
typedef union
{
	UINT32		all;
	DbgmcuCrBitType		bit;
}DbgmcuCrType;

/** 调试处理器APB1冻结寄存器位定义 */
typedef struct
{
	UINT32		DBG_TIM2_STOP			: 1;		/**< Bit0，TIM2计数器停止位，0：内核停止时继续喂TIM2，1：内核停止时停止TIM2 */
	UINT32		DBG_TIM3_STOP			: 1;		/**< Bit1，TIM3计数器停止位，0：内核停止时继续喂TIM3，1：内核停止时停止TIM3 */
	UINT32		DBG_TIM4_STOP			: 1;		/**< Bit2，TIM4计数器停止位，0：内核停止时继续喂TIM4，1：内核停止时停止TIM4 */
	UINT32		Rsvd1					: 1;		/**< Bit3，保留 */
	UINT32		DBG_TIM6_STOP			: 1;		/**< Bit4，TIM6计数器停止位，0：内核停止时继续喂TIM6，1：内核停止时停止TIM6 */
	UINT32		DBG_TIM7_STOP			: 1;		/**< Bit5，TIM7计数器停止位，0：内核停止时继续喂TIM7，1：内核停止时停止TIM7 */
	UINT32		Rsvd2					: 4;		/**< Bit6~9，保留 */
	UINT32		DBG_RTC_STOP			: 1;		/**< Bit10，RTC停止位，0：内核停止时继续喂RTC计数器，1：内核停止时RTC计数器停止 */
	UINT32		DBG_WWDG_STOP			: 1;		/**< Bit11，窗口看门狗停止位，0：内核停止时窗口看门狗计数器继续运行，1:内核停止时窗口看门狗计数器停止运行 */
	UINT32		DBG_IWDG_STOP			: 1;		/**< Bit12，独立看门狗停止位，0：内核停止时独立看门狗计数器继续运行，1:内核停止时独立看门狗计数器停止运行 */
	UINT32		Rsvd3					: 8;		/**< Bit13~20，保留 */
	UINT32		DBG_I2C1_SMBUS_TIMEOUT	: 1;		/**< Bit21，I2C1SMBUS超时位，0：与正常一样，1：停止SMBUS超时模式 */
	UINT32		DBG_I2C2_SMBUS_TIMEOUT	: 1;		/**< Bit22，I2C2SMBUS超时位，0：与正常一样，1：停止SMBUS超时模式 */
	UINT32		Rsvd4					: 2;		/**< Bit23~24，保留 */
	UINT32		DBG_CAN_STOP			: 1;		/**< Bit25，调试总线停止位，0：与正常一样，1：CAN2接受寄存器冻结 */
	UINT32		Rsvd5					: 4;		/**< Bit26~29，保留 */
	UINT32		DBG_I2C3_SMBUS_TIMEOUT	: 1;		/**< Bit30，I2C2SMBUS超时位，0：与正常一样，1：停止SMBUS超时模式 */
	UINT32		Rsvd6					: 1;		/**< Bit31，保留 */
}DbgmcuApb1FzBitType;

/** APB1冻结寄存器定义 */
typedef union
{
	UINT32		all;
	DbgmcuApb1FzBitType		bit;
}DbgmcuApb1FzType;

/** APB2冻结寄存器位定义 */
typedef struct
{
	UINT32	DBG_TIM1_STOP		: 1;		/**< Bit0，TIM1计数器停止位，0：内核停止时继续喂TIM1，1：内核停止时停止TIM1 */
	UINT32	DBG_TIM8_STOP		: 1;		/**< Bit1，TIM8计数器停止位，0：内核停止时继续喂TIM8，1：内核停止时停止TIM8 */
	UINT32	DBG_TIM15_STOP		: 1;		/**< Bit2，TIM15计数器停止位，0：内核停止时继续喂TIM15，1：内核停止时停止TIM15 */
	UINT32	DBG_TIM16_STOP		: 1;		/**< Bit3，TIM16计数器停止位，0：内核停止时继续喂TIM16，1：内核停止时停止TIM16 */
	UINT32	DBG_TIM17_STOP		: 1;		/**< Bit4，TIM17计数器停止位，0：内核停止时继续喂TIM17，1：内核停止时停止TIM17 */
	UINT32	DBG_TIM20_STOP		: 1;		/**< Bit5，TIM20计数器停止位，0：内核停止时继续喂TIM20，1：内核停止时停止TIM20 */
	UINT32	Rsvd1				: 26;		/**< Bit6~31，保留 */
}DbgmcuApb2FzBitType;

/** APB2冻结寄存器定义 */
typedef union
{
	UINT32		all;
	DbgmcuApb2FzBitType		bit;
}DbgmcuApb2FzType;


/** DBG寄存器 */
typedef struct
{
	DbgmcuIdcodeType		IDCODE;			/** DBGMCU	ID寄存器 ，偏移地址0x00*/
	DbgmcuCrType			CR;				/** DBGMCU	控制寄存器，偏移地址0x04 */
	DbgmcuApb1FzType		APB1FZ;			/** DBGMCU	APB1冻结寄存器，偏移地址0x08 */
	DbgmcuApb2FzType		APB2FZ;			/** DBGMCU	APB2冻结寄存器，偏移地址0x0c */
}DbgmcuType;



/** DBG寄存器地址 */
#define	DBGMCU		((DbgmcuType *) DBGMCU_BASE)


#endif	
