/**
  *******************************************************************
  * @file    reg_stm32f303_address.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-18
  * @brief   STM32F303地址定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#ifndef __REG_STM32F303_ADDRESS_H__
#define __REG_STM32F303_ADDRESS_H__

#include "typedefine.h"

#define FLASH_BASE            ((UINT32)0x08000000) /*!< FLASH base address in the alias region */
#define CCM_BASE       		  ((UINT32)0x10000000) /*!< CCM(core coupled memory) data RAM(16 KB) base address in the alias region    */
#define SRAM_BASE             ((UINT32)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((UINT32)0x40000000) /*!< Peripheral base address in the alias region */
#define SRAM_BB_BASE          ((UINT32)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        ((UINT32)0x42000000) /*!< Peripheral base address in the bit-band region */


/** 外设存储器映射 */
#define APB1PERIPH_BASE        PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000)
#define AHB3PERIPH_BASE       (PERIPH_BASE + 0x10000000)

/** APB1 外设地址 */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x00000000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x00000400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x00000800)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x00001000)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x00001400)
#define RTC_BASE              (APB1PERIPH_BASE + 0x00002800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x00002C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x00003000)
#define I2S2ext_BASE          (APB1PERIPH_BASE + 0x00003400)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x00003800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x00003C00)
#define I2S3ext_BASE          (APB1PERIPH_BASE + 0x00004000)
#define USART2_BASE           (APB1PERIPH_BASE + 0x00004400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x00004800)
#define UART4_BASE            (APB1PERIPH_BASE + 0x00004C00)
#define UART5_BASE            (APB1PERIPH_BASE + 0x00005000)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x00005400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x00005800)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x00006400)
#define PWR_BASE              (APB1PERIPH_BASE + 0x00007000)
#define DAC_BASE              (APB1PERIPH_BASE + 0x00007400)

/** APB2 外设地址 */
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x00000000)
#define COMP_BASE             (APB2PERIPH_BASE + 0x0000001C)
#define COMP1_BASE            (APB2PERIPH_BASE + 0x0000001C)
#define COMP2_BASE            (APB2PERIPH_BASE + 0x00000020)
#define COMP3_BASE            (APB2PERIPH_BASE + 0x00000024)
#define COMP4_BASE            (APB2PERIPH_BASE + 0x00000028)
#define COMP5_BASE            (APB2PERIPH_BASE + 0x0000002C)
#define COMP6_BASE            (APB2PERIPH_BASE + 0x00000030)
#define COMP7_BASE            (APB2PERIPH_BASE + 0x00000034)
#define OPAMP_BASE            (APB2PERIPH_BASE + 0x00000038)
#define OPAMP1_BASE           (APB2PERIPH_BASE + 0x00000038)
#define OPAMP2_BASE           (APB2PERIPH_BASE + 0x0000003C)
#define OPAMP3_BASE           (APB2PERIPH_BASE + 0x00000040)
#define OPAMP4_BASE           (APB2PERIPH_BASE + 0x00000044)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x00000400)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x00002C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x00003000)
#define TIM8_BASE             (APB2PERIPH_BASE + 0x00003400)
#define USART1_BASE           (APB2PERIPH_BASE + 0x00003800)
#define TIM15_BASE            (APB2PERIPH_BASE + 0x00004000)
#define TIM16_BASE            (APB2PERIPH_BASE + 0x00004400)
#define TIM17_BASE            (APB2PERIPH_BASE + 0x00004800)
#define TIM20_BASE            (APB2PERIPH_BASE + 0x00005000)

/** AHB1 外设地址 */
#define DMA1_BASE             (AHB1PERIPH_BASE + 0x00000000)
#define DMA1_Channel1_BASE    (AHB1PERIPH_BASE + 0x00000008)
#define DMA1_Channel2_BASE    (AHB1PERIPH_BASE + 0x0000001C)
#define DMA1_Channel3_BASE    (AHB1PERIPH_BASE + 0x00000030)
#define DMA1_Channel4_BASE    (AHB1PERIPH_BASE + 0x00000044)
#define DMA1_Channel5_BASE    (AHB1PERIPH_BASE + 0x00000058)
#define DMA1_Channel6_BASE    (AHB1PERIPH_BASE + 0x0000006C)
#define DMA1_Channel7_BASE    (AHB1PERIPH_BASE + 0x00000080)
#define DMA2_BASE             (AHB1PERIPH_BASE + 0x00000400)
#define DMA2_Channel1_BASE    (AHB1PERIPH_BASE + 0x00000408)
#define DMA2_Channel2_BASE    (AHB1PERIPH_BASE + 0x0000041C)
#define DMA2_Channel3_BASE    (AHB1PERIPH_BASE + 0x00000430)
#define DMA2_Channel4_BASE    (AHB1PERIPH_BASE + 0x00000444)
#define DMA2_Channel5_BASE    (AHB1PERIPH_BASE + 0x00000458)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x00001000)
#define FLASH_R_BASE          (AHB1PERIPH_BASE + 0x00002000) 	/*!< Flash registers base address */
#define OB_BASE               ((UINT32)0x1FFFF800)     			/*!< Flash Option Bytes base address */
#define CRC_BASE              (AHB1PERIPH_BASE + 0x00003000)
#define TSC_BASE              (AHB1PERIPH_BASE + 0x00004000)

/** AHB2 外设地址 */
#define GPIOA_BASE            (AHB2PERIPH_BASE + 0x0000)
#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400)
#define GPIOC_BASE            (AHB2PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (AHB2PERIPH_BASE + 0x0C00)
#define GPIOE_BASE            (AHB2PERIPH_BASE + 0x1000)
#define GPIOF_BASE            (AHB2PERIPH_BASE + 0x1400)

/** AHB3 外设地址 */
#define ADC1_BASE             (AHB3PERIPH_BASE + 0x0000)
#define ADC2_BASE             (AHB3PERIPH_BASE + 0x0100)
#define ADC1_2_BASE           (AHB3PERIPH_BASE + 0x0300)
#define ADC3_BASE             (AHB3PERIPH_BASE + 0x0400)
#define ADC4_BASE             (AHB3PERIPH_BASE + 0x0500)
#define ADC3_4_BASE           (AHB3PERIPH_BASE + 0x0700)

/*!< NVIC 地址定义 */
#define SCS_BASE            (0xE000E000UL)
#define NVIC_BASE           (SCS_BASE +  0x0100UL) 
#define SCB_BASE            (SCS_BASE +  0x0D00UL)  


#define DBGMCU_BASE          ((UINT32)0xE0042000) /*!< Debug MCU registers base address */


#endif

