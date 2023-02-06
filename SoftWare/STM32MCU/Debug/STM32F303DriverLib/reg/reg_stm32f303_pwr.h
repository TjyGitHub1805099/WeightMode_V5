/**
  *******************************************************************
  * @file    reg_stm32f303_pwr.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-23
  * @brief   STM32F303 电源控制寄存器定义头文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
  
#ifndef __REG_STM32F303_PWR_H__
#define __REG_STM32F303_PWR_H__

#include "typedefine.h"
#include "reg_stm32f303_pwr.h"


/** 电源控制寄存器位定义 */ 
typedef struct
{
	UINT32	LPDS	: 1;		/**< Bit0，低功耗深眠模式位，0:在停止模式下电源稳压器开，1：在停止模式下稳压器处于低电压模式 */
	UINT32	PDDS	: 1;		/**< Bit1，深眠模式关闭位，0：CPU进入深眠时选择关闭模式，1：进入睡眠时选择待机模式 */
	UINT32	CWUF	: 1;		/**< Bit2，清除唤醒标志位，0：无影响，1：2系统周期后清除唤醒标志 */
	UINT32	CSBF	: 1;		/**< Bit3，清除待命模式标识位，0：无影响，1：清除待命模式标志 */
	UINT32	PVDE	: 1;		/**< Bit4，电源电压检测器使能位，0:关闭PVD，1：打开PVD */
	UINT32	PLS		: 3;		/**< Bit5~7，电源检测器门限电压设定位，000: 2.2V，001: 2.3V，010: 2.4V，011: 2.5V，100: 2.6V，101: 2.7V，110: 2.8V ，111: 2.9V */
	UINT32	DBP		: 1;		/**< Bit8，RTC写保护失能位，0，无RTC与备份寄存器权限；1，获得RTC与备份寄存器权限 */
	UINT32	Rsvd1	: 23;		/**< Bit9~31，保留位 */
}PwrCrBitType;

/** 电源控制寄存器定义 */ 
typedef union
{
	UINT32	all;
	PwrCrBitType  bit;
}PwrCrType;

/** 电源控制与状态寄存器位定义 */
typedef struct
{
	UINT32	WUF				: 1;		/**< Bit0，唤醒标志位，0：没有唤醒事件发生，1：发生了唤醒事件 */
	UINT32	SBF				: 1;		/**< Bit1，待机模式标志位，0：不在待机模式，1：在待机模式 */
	UINT32	PVDO			: 1;		/**< Bit2，PVD输出位，PVD模式开启下有效，0：Vdd比设置的门限电源高，1：Vdd比设置的门限电源低 */
	UINT32	VREFINTRDYF		: 1;		/**< Bit3，内部参考电压就绪位，就绪时置位，电源稳定中重置 */
	UINT32	RSVD1			: 4;		/**< Bit4~7，保留 */
	UINT32	EWUP1			: 1;		/**< Bit8，使能WKUP1引脚，0：WKUP1引脚作为一个通用IO口，WKUP1引脚的事件不能从待机中唤醒设备，1：WKUP1引脚唤醒设备，并且强制输入低阻态 */
	UINT32	EWUP2			: 1;		/**< Bit9，使能WKUP2引脚，0：WKUP2引脚作为一个通用IO口，WKUP2引脚的事件不能从待机中唤醒设备，1：WKUP2引脚唤醒设备，并且强制输入低阻态 */
	UINT32	EWUP3			: 1;		/**< Bit10，使能WKUP3引脚，0：WKUP3引脚作为一个通用IO口，WKUP3引脚的事件不能从待机中唤醒设备，1：WKUP3引脚唤醒设备，并且强制输入低阻态 */
	UINT32	RSVD2			: 21;		/**< Bit11~31，保留 */
}PwrCsrBitType;

/** 电源控制与状态寄存器定义 */
typedef  union
{
	UINT32	all;
	PwrCsrBitType	bit;
}PwrCsrType;


/** PWR寄存器 */
typedef  struct
{
	PwrCrType		CR;			/**< 电源控制寄存器位定义，偏移地址0x00 */ 
	PwrScrType		CSR;		/**< 电源控制与状态寄存器位定义，偏移地址0x04 */
}PwrType;


/** PWR模块定义 */
#define  PWR	((PwrType *) PWR_BASE)




#endif

	
