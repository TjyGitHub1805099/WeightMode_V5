/**
  *******************************************************************
  * @file    hal_irq_priority.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x 板上资源中断优先级头文件(抽象层)
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __HAL_IRQ_PRIORITY_H__
#define __HAL_IRQ_PRIORITY_H__

enum UartPriorityType
{
    PRIO_PD_OUTPUT = 0,
	PRIO_UART_DMA_TX,
    PRIO_EQEPZ,
	PRIO_UART_RX_TX,
	PRIO_UART_TIMER,
	PRIO_ADC,
	PRIO_CAN,
	PRIO_MAIN_TASK,
    PRIO_LED_FLASH,
};

enum SpiPriorityType
{
	PRIO_SPI_DMA_RX_TX = 0,
	PRIO_SPI_RX_TX
};

#endif
