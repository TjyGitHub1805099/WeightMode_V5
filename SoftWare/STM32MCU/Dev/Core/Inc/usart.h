/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart6;

/* USER CODE BEGIN Private defines */
#define UART1_printf_Tr(...) HAL_UART_Transmit(&huart3,\
											  (uint8_t *)u_SprintfBuf,\
											   sprintf((char*)u_SprintfBuf,__VA_ARGS__),\
											   0xffff)

#define UART1_printf_DMA(...) HAL_UART_Transmit_DMA(&huart3,\
												   (uint8_t *)u_SprintfBuf,\
												    sprintf((char*)u_SprintfBuf,__VA_ARGS__))
																				 
#define UART1_printf_IT(...) HAL_UART_Transmit_IT(&huart3,\
												 (uint8_t *)u_SprintfBuf,\
												  sprintf((char*)u_SprintfBuf,__VA_ARGS__))

#define RECEIVELEN          (1024) 
#define USART_DMA_SENDING   (1)
#define USART_DMA_SENDOVER  (0) 

typedef struct  
{  
  uint8_t receive_flag:1;
  uint8_t dmaSend_flag:1;
  uint16_t rx_len;
  uint8_t usartDMA_rxBuf[RECEIVELEN];  
}USART_RECEIVETYPE;  
   
extern USART_RECEIVETYPE Usart1AsScreen1Type;
extern uint8_t u_SprintfBuf[256];//用于sprintf函数存放字符串数据

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void Usart1AsScreen1SendData_DMA(uint8_t *pdata, uint16_t Length);
void Usart1AsScreen1Receive_IDLE(UART_HandleTypeDef *huart);
void Usart2AsScreen2Receive_IDLE(UART_HandleTypeDef *huart);
void Usart3WithRS485Receive_IDLE(UART_HandleTypeDef *huart);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

