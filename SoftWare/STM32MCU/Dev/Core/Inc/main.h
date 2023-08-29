/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M_HX711_CLK_1_Pin GPIO_PIN_2
#define M_HX711_CLK_1_GPIO_Port GPIOE
#define M_HX711_CLK_2_Pin GPIO_PIN_3
#define M_HX711_CLK_2_GPIO_Port GPIOE
#define M_HX711_CLK_3_Pin GPIO_PIN_4
#define M_HX711_CLK_3_GPIO_Port GPIOE
#define M_HX711_CLK_4_Pin GPIO_PIN_5
#define M_HX711_CLK_4_GPIO_Port GPIOE
#define M_HX711_CLK_5_Pin GPIO_PIN_6
#define M_HX711_CLK_5_GPIO_Port GPIOE
#define M_HX711_CLK_6_Pin GPIO_PIN_13
#define M_HX711_CLK_6_GPIO_Port GPIOC
#define M_HX711_CLK_7_Pin GPIO_PIN_0
#define M_HX711_CLK_7_GPIO_Port GPIOC
#define M_HX711_CLK_8_Pin GPIO_PIN_2
#define M_HX711_CLK_8_GPIO_Port GPIOC
#define EPS_RST_Pin GPIO_PIN_3
#define EPS_RST_GPIO_Port GPIOC
#define STM32_KEY_1_Pin GPIO_PIN_3
#define STM32_KEY_1_GPIO_Port GPIOA
#define STM32_KEY_2_Pin GPIO_PIN_4
#define STM32_KEY_2_GPIO_Port GPIOA
#define M_LED_QH3_Pin GPIO_PIN_10
#define M_LED_QH3_GPIO_Port GPIOE
#define M_LED_ALL_RCLK_Pin GPIO_PIN_11
#define M_LED_ALL_RCLK_GPIO_Port GPIOE
#define M_LED_SER0_Pin GPIO_PIN_12
#define M_LED_SER0_GPIO_Port GPIOE
#define M_LED_ALL_OE_Pin GPIO_PIN_13
#define M_LED_ALL_OE_GPIO_Port GPIOE
#define M_LED_ALL_SRCLR_Pin GPIO_PIN_14
#define M_LED_ALL_SRCLR_GPIO_Port GPIOE
#define M_LED_ALL_SRCLK_Pin GPIO_PIN_15
#define M_LED_ALL_SRCLK_GPIO_Port GPIOE
#define UART4_TX_SMQ1_RX_Pin GPIO_PIN_8
#define UART4_TX_SMQ1_RX_GPIO_Port GPIOD
#define UART4_RX_SMQ1_TX_Pin GPIO_PIN_9
#define UART4_RX_SMQ1_TX_GPIO_Port GPIOD
#define LED_RUN0_Pin GPIO_PIN_15
#define LED_RUN0_GPIO_Port GPIOD
#define USART6_TX_WX_RX_Pin GPIO_PIN_6
#define USART6_TX_WX_RX_GPIO_Port GPIOC
#define USART6_RX_WX_TX_Pin GPIO_PIN_7
#define USART6_RX_WX_TX_GPIO_Port GPIOC
#define STM32_RS485_EN_Pin GPIO_PIN_10
#define STM32_RS485_EN_GPIO_Port GPIOA
#define M_HX711_DATA_1_Pin GPIO_PIN_0
#define M_HX711_DATA_1_GPIO_Port GPIOD
#define M_HX711_DATA_2_Pin GPIO_PIN_1
#define M_HX711_DATA_2_GPIO_Port GPIOD
#define M_HX711_DATA_3_Pin GPIO_PIN_2
#define M_HX711_DATA_3_GPIO_Port GPIOD
#define M_HX711_DATA_4_Pin GPIO_PIN_3
#define M_HX711_DATA_4_GPIO_Port GPIOD
#define M_HX711_DATA_5_Pin GPIO_PIN_4
#define M_HX711_DATA_5_GPIO_Port GPIOD
#define M_HX711_DATA_6_Pin GPIO_PIN_7
#define M_HX711_DATA_6_GPIO_Port GPIOD
#define STM32_I2C1_WP_Pin GPIO_PIN_5
#define STM32_I2C1_WP_GPIO_Port GPIOB
#define USART1_TX_SCREEN1_RX_Pin GPIO_PIN_6
#define USART1_TX_SCREEN1_RX_GPIO_Port GPIOB
#define USART1_RX_SCREEN1_TX_Pin GPIO_PIN_7
#define USART1_RX_SCREEN1_TX_GPIO_Port GPIOB
#define M_HX711_DATA_7_Pin GPIO_PIN_0
#define M_HX711_DATA_7_GPIO_Port GPIOE
#define M_HX711_DATA_8_Pin GPIO_PIN_1
#define M_HX711_DATA_8_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
