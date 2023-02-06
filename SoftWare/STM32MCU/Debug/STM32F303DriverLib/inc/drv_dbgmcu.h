/**
*******************************************************************
* @file    drv_dbgmcu.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x DBGMCU模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_DGBMCU_H__
#define __DRV_DGBMCU_H__

#include "reg_stm32f303_dbg.h"


//APB1
#define DBGMCU_TIM2_STOP             ((UINT32)0x00000001)
#define DBGMCU_TIM3_STOP             ((UINT32)0x00000002)
#define DBGMCU_TIM4_STOP             ((UINT32)0x00000004)
#define DBGMCU_TIM6_STOP             ((UINT32)0x00000010)
#define DBGMCU_TIM7_STOP             ((UINT32)0x00000020)
#define DBGMCU_RTC_STOP              ((UINT32)0x00000400)
#define DBGMCU_WWDG_STOP             ((UINT32)0x00000800)
#define DBGMCU_IWDG_STOP             ((UINT32)0x00001000)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((UINT32)0x00200000)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((UINT32)0x00400000)
#define DBGMCU_CAN1_STOP             ((UINT32)0x02000000)
#define DBGMCU_I2C3_SMBUS_TIMEOUT    ((UINT32)0x40000000)

//APB2
#define DBGMCU_TIM1_STOP             ((UINT32)0x00000001)
#define DBGMCU_TIM8_STOP             ((UINT32)0x00000002)
#define DBGMCU_TIM15_STOP            ((UINT32)0x00000004)
#define DBGMCU_TIM16_STOP            ((UINT32)0x00000008)
#define DBGMCU_TIM17_STOP            ((UINT32)0x00000010)
#define DBGMCU_TIM20_STOP            ((UINT32)0x00000020)



extern void drv_debug_apb1_stop( UINT32 Periph );
extern void drv_debug_apb1_run( UINT32 Periph );
extern void drv_debug_apb2_stop( UINT32 Periph );
extern void drv_debug_apb2_run( UINT32 Periph );

#endif
