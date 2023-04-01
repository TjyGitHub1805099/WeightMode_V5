/**
  *******************************************************************
  * @file    drv_syscfg.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x系统配置模块驱动程序头文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#ifndef __DRV_SYSCFG_H__
#define __DRV_SYSCFG_H__

#include "reg_stm32f303_syscfg.h"

/** 外部中断GPIOx源定义 */
#define EXTI_GPIO_PORT_A			((UINT8)0x00)
#define EXTI_GPIO_PORT_B			((UINT8)0x01)
#define EXTI_GPIO_PORT_C			((UINT8)0x02)
#define EXTI_GPIO_PORT_D			((UINT8)0x03)
#define EXTI_GPIO_PORT_E			((UINT8)0x04)
#define EXTI_GPIO_PORT_F			((UINT8)0x05)
#define EXTI_GPIO_PORT_G			((UINT8)0x06)
#define EXTI_GPIO_PORT_H			((UINT8)0x07)
#define EXTI_GPIO_PORT_I			((UINT8)0x08)

/** 外部中断LINEx源定义 */
#define EXTI_GPIO_PIN_0				((UINT8)0x00)
#define EXTI_GPIO_PIN_1				((UINT8)0x01)
#define EXTI_GPIO_PIN_2				((UINT8)0x02)
#define EXTI_GPIO_PIN_3				((UINT8)0x03)
#define EXTI_GPIO_PIN_4				((UINT8)0x04)
#define EXTI_GPIO_PIN_5				((UINT8)0x05)
#define EXTI_GPIO_PIN_6				((UINT8)0x06)
#define EXTI_GPIO_PIN_7				((UINT8)0x07)
#define EXTI_GPIO_PIN_8				((UINT8)0x08)
#define EXTI_GPIO_PIN_9				((UINT8)0x09)
#define EXTI_GPIO_PIN_10			((UINT8)0x0A)
#define EXTI_GPIO_PIN_11			((UINT8)0x0B)
#define EXTI_GPIO_PIN_12			((UINT8)0x0C)
#define EXTI_GPIO_PIN_13			((UINT8)0x0D)
#define EXTI_GPIO_PIN_14			((UINT8)0x0E)
#define EXTI_GPIO_PIN_15			((UINT8)0x0F)

#define SYSCFG_DMARemap_TIM17              ((UINT32)0x00001000)        /*!< Remap TIM17 DMA requests from channel1 to channel2 */
#define SYSCFG_DMARemap_TIM16              ((UINT32)0x00000800)        /*!< Remap TIM16 DMA requests from channel3 to channel4 */
#define SYSCFG_DMARemap_ADC2ADC4           ((UINT32)0x00000100)        /*!< Remap ADC2 and ADC4 DMA requests */

#define SYSCFG_DMARemap_TIM6DAC1Ch1        ((UINT32)0x00002000)  		/* Remap TIM6/DAC1 Ch1 DMA requests */
#define SYSCFG_DMARemap_TIM7DAC1Ch2        ((UINT32)0x00004000)  		/* Remap TIM7/DAC1 Ch2 DMA requests */
#define SYSCFG_DMARemap_DAC2Ch1            ((UINT32)0x00008000)      	/* Remap DAC2 Ch1 DMA requests */

#define SYSCFG_DMARemapCh2_SPI1_RX         ((UINT32)0x80000003)            /* Remap SPI1 RX DMA CH2 requests */
#define SYSCFG_DMARemapCh4_SPI1_RX         ((UINT32)0x80000001)            /* Remap SPI1 RX DMA CH4 requests */
#define SYSCFG_DMARemapCh6_SPI1_RX         ((UINT32)0x80000002)            /* Remap SPI1 RX DMA CH6 requests */

#define SYSCFG_DMARemapCh3_SPI1_TX         ((UINT32)0x8000000C)            /* Remap SPI1 TX DMA CH2 requests */
#define SYSCFG_DMARemapCh5_SPI1_TX         ((UINT32)0x80000004)            /* Remap SPI1 TX DMA CH5 requests */
#define SYSCFG_DMARemapCh7_SPI1_TX         ((UINT32)0x80000008)            /* Remap SPI1 TX DMA CH7 requests */

#define SYSCFG_DMARemapCh7_I2C1_RX         ((UINT32)0x80000030)            /* Remap I2C1 RX DMA CH7 requests */
#define SYSCFG_DMARemapCh3_I2C1_RX         ((UINT32)0x80000010)            /* Remap I2C1 RX DMA CH3 requests */
#define SYSCFG_DMARemapCh5_I2C1_RX         ((UINT32)0x80000020)            /* Remap I2C1 RX DMA CH5 requests */

#define SYSCFG_DMARemapCh6_I2C1_TX         ((UINT32)0x800000C0)            /* Remap I2C1 TX DMA CH6 requests */
#define SYSCFG_DMARemapCh2_I2C1_TX         ((UINT32)0x80000040)            /* Remap I2C1 TX DMA CH2 requests */
#define SYSCFG_DMARemapCh4_I2C1_TX         ((UINT32)0x80000080)            /* Remap I2C1 TX DMA CH4 requests */

#define SYSCFG_DMARemapCh4_ADC2            ((UINT32)0x80000300)            /* Remap ADC2 DMA1 Ch4 requests */
#define SYSCFG_DMARemapCh2_ADC2            ((UINT32)0x80000200)            /* Remap ADC2 DMA1 Ch2 requests */


extern void drv_syscfg_deinit( void );
extern void drv_syscfg_exti_line_init( UINT8 ExtiLinePort, UINT8 ExtiLinePin );
void drv_syscfg_dma_channel_remap_enable( UINT32 SystemDmaremap );
void drv_syscfg_dma_channel_remap_disable( UINT32 SystemDmaremap );

#endif
