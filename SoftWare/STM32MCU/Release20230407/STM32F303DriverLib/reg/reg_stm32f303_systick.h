/**
  *******************************************************************
  * @file    reg_stm32f303_systick.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40xSYSTICK寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __REG_STM32F407_SYSTICK_H__
#define __REG_STM32F407_SYSTICK_H__

#include "typedefine.h"

/** SysTick控制及状态寄存器位定义 */
typedef struct
{
	UINT32  ENABLE     : 1;			      /**< Bit0, SysTick 定时器的使能位,1表示使能计数 */
	UINT32  TICKINT    : 1;			      /**< Bit1, 异常请求使能，1表示SysTick倒数到0 时产生SysTick 异常请求 */
	UINT32  CLKSOURCE  : 1;			      /**< Bit2, 时钟源，1表示内核时钟(FCLK)，0表示外部时钟源(STCLK) */
	UINT32  Rsvd1      : 13;			  /**< Bit3~15, 保留 */
	UINT32  COUNTFLAG  : 1;			      /**< Bit16, 计数标志，如果在上次读取本寄存器后，SysTick 已经数到了0，则该位为1。如果读取该位，该位将自动清零 */
	UINT32  Rsvd2      : 15;			  /**< Bit17~31, 保留 */
}SysTickCTRLRegBitType;

/** SysTick控制及状态寄存器定义 */
typedef union
{
	SysTickCTRLRegBitType  bit;			  /**< SysTick控制及状态寄存器 位定义 */
	UINT32  all;						  /**< SysTick控制及状态寄存器 所有位 */
}SysTickCTRLRegType;

/** SysTick校准数值寄存器位定义 */
typedef struct
{
	UINT32  TENMS      : 24;			  /**< Bit0~23, 10ms 的时间内倒计数的格数 */
	UINT32  Rsvd1      : 6;			      /**< Bit24~29, 保留 */
	UINT32  SKEW       : 1;			      /**< Bit30, 1表示1=校准值不是准确的10ms，0表示校准值是准确的10ms */
	UINT32  NOREF      : 1;			      /**< Bit31, 1表示没有外部参考时钟（STCLK 不可用），0表示外部参考时钟可用 */
}SysTickCALIRegBitType;

/** SysTick校准数值寄存器定义 */
typedef union
{
	SysTickCALIRegBitType  bit;			  /**< SysTick校准数值寄存器 位定义 */
	UINT32  all;						  /**< SysTick校准数值寄存器 所有位 */
}SysTickCALIRegType;

/** SysTick寄存器 */
typedef struct
{
  SysTickCTRLRegType   CTRL;              /**< Offset: 0x000 (R/W)  SysTick 控制及状态寄存器 */
  UINT32               LOAD;              /**< Offset: 0x004 (R/W)  SysTick 重装载数值寄存器 */
  UINT32               VAL;               /**< Offset: 0x008 (R/W)  SysTick 当前数值寄存器   */
  SysTickCALIRegType   CALIB;             /**< Offset: 0x00C (R/ )  SysTick 校准数值寄存器   */
} SysTick_Type;

#define SCS_BASE            (0xE000E000UL)                            
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    
#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )  


#endif
