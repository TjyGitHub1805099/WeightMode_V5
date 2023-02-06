/**
  *******************************************************************
  * @file    hal_led_flash.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F30X LED闪烁控制程序头文件(抽象层)
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __HAL_LED_FLASH_H__
#define __HAL_LED_FLASH_H__

#include "drv_rcc.h"
#include "drv_nvic.h"
#include "drv_timer.h"
#include "drv_dbgmcu.h"

#define	LED_TIMER_BASE						TIM15
#define	LED_TIMER_BASE_CLK					RCC_APB2ENR_TIM15EN
#define LED_TIMER_BASE_IRQn					TIM1_BRK_TIM15_IRQn
#define LED_TIMER_BASE_DEBUG_STOP			DBGMCU_TIM15_STOP

/* 中断函数定义 */
#define hal_led_timer_isr					TIM1_BRK_TIM15_IRQHandler

typedef enum LedActionType
{
    LED_RED_GREEN_OFF = 0,
    LED_RED_ON,
    LED_GREEN_ON,
    LED_RED_GREEN_ON,
    LED_RED_FLASH,
    LED_GREEN_FLASH,
    LED_RED_GREEN_FLASH
}enumLedActionType;

typedef struct LedFlashType
{
    enumLedActionType   Action;
    UINT32              FlashTime;
    UINT32              FlashCounter;
}structLedFlashType;

extern void hal_led_flash_init( void );
extern void hal_led_flash_ctrl( enumLedActionType LedAction, UINT16 FlashFreq );

#endif
