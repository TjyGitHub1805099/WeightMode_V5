/**
  *******************************************************************
  * @file    hal_timer.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x 定时器头文件(抽象层)
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __HAL_TIMER_H__
#define __HAL_TIMER_H__

#include "drv_rcc.h"
#include "drv_nvic.h"
#include "drv_timer.h"
#include "drv_dbgmcu.h"

#define	TIMER_BASE						TIM6
#define	TIMER_BASE_CLK					RCC_APB1ENR_TIM6EN
#define TIMER_BASE_IRQn					TIM6_DAC_IRQn
#define TIMER_BASE_DEBUG_STOP			DBGMCU_TIM6_STOP


#define	MEASURE_TIMER_BASE				TIM7
#define	MEASURE_TIMER_BASE_CLK			RCC_APB1ENR_TIM7EN
#define MEASURE_TIMER_BASE_IRQn			TIM7_IRQn
#define MEASURE_TIMER_BASE_DEBUG_STOP	DBGMCU_TIM7_STOP

/* 中断函数定义 */
#define hal_timer_isr					TIM6_DAC_IRQHandler

extern void hal_timer_init( UINT16 us );
extern void hal_timer_start( void );
extern void hal_timer_stop( void );
extern void hal_measure_timer_init( void );
extern UINT16 hal_measure_timer_get_counter( void );
extern void hal_measure_timer_clear_counter( void );


#endif
