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

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */

#define UART1_printf_Tr(...) HAL_UART_Transmit(&huart3,\
											  (uint8_t *)u_buf,\
											   sprintf((char*)u_buf,__VA_ARGS__),\
											   0xffff)

#define UART1_printf_DMA(...) HAL_UART_Transmit_DMA(&huart3,\
												   (uint8_t *)u_buf,\
												    sprintf((char*)u_buf,__VA_ARGS__))
																				 
#define UART1_printf_IT(...) HAL_UART_Transmit_IT(&huart3,\
												 (uint8_t *)u_buf,\
												  sprintf((char*)u_buf,__VA_ARGS__))

/* 构建用于UART数据接收的结构体USART_RECEIVETYPE */
#define RECEIVELEN 1024  
#define USART_DMA_SENDING 1//发生未完成
#define USART_DMA_SENDOVER 0//发生完成 

typedef struct  
{  
  uint8_t receive_flag:1;//空闲接收完成 
  uint8_t dmaSend_flag:1;//发送完成  
  uint16_t rx_len;//接收长度	
  uint8_t usartDMA_rxBuf[RECEIVELEN];//DMA接收缓存  
}USART_RECEIVETYPE;  
   
extern USART_RECEIVETYPE UsartType1;
extern uint8_t u_buf[256];
extern uint8_t Rx_buff[50];

/* USER CODE END Private defines */

void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

