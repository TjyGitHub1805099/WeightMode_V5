/**
*******************************************************************
* @file    drv_dbgmcu.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x DBGMCU模块驱动程序
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/


#include "drv_dbgmcu.h"


/**
* @brief  调试时APB1外设停止.
* @param  Periph: 要控制的APB1外设，可以是下面值的组合
*     @arg DBGMCU_TIM2_STOP
*     @arg DBGMCU_TIM3_STOP
*     @arg DBGMCU_TIM4_STOP
*     @arg DBGMCU_TIM6_STOP
*     @arg DBGMCU_TIM7_STOP
*     @arg DBGMCU_RTC_STOP
*     @arg DBGMCU_WWDG_STOP
*     @arg DBGMCU_IWDG_STOP
*     @arg DBGMCU_I2C1_SMBUS_TIMEOUT
*     @arg DBGMCU_I2C2_SMBUS_TIMEOUT
*     @arg DBGMCU_CAN1_STOP
*     @arg DBGMCU_I2C3_SMBUS_TIMEOUT
* @retval 无
*/
void drv_debug_apb1_stop( UINT32 Periph )
{
	DBGMCU->APB1FZ.all |= Periph;
}

/**
* @brief  调试时APB1外设工作.
* @param  Periph: 要控制的APB1外设，参考 drv_debug_apb1_stop 说明
* @retval 无
*/
void drv_debug_apb1_run( UINT32 Periph )
{
	DBGMCU->APB1FZ.all &= (UINT32)~Periph;
}

/**
* @brief  调试时APB2外设停止.
* @param  Periph: 要控制的APB2外设，可以是下面值的组合
*     @arg DBGMCU_TIM1_STOP
*     @arg DBGMCU_TIM8_STOP
*     @arg DBGMCU_TIM15_STOP
*     @arg DBGMCU_TIM16_STOP
*     @arg DBGMCU_TIM17_STOP
*     @arg DBGMCU_TIM20_STOP
* @retval 无
*/
void drv_debug_apb2_stop( UINT32 Periph )
{ 
	DBGMCU->APB2FZ.all |= Periph;
}

/**
* @brief  调试时APB2外设运行.
* @param  Periph: 要控制的APB2外设，参考 drv_debug_apb2_stop 说明
* @retval 无
*/
void drv_debug_apb2_run( UINT32 Periph )
{ 
	DBGMCU->APB2FZ.all &= (UINT32)~Periph;
}

