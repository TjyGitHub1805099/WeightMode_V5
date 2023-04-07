/**
  *******************************************************************
  * @file    hal_gpio.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   GPIO头文件(抽象层)
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include "drv_gpio.h"

//test
#define TEST_GPIO_PORT				GPIOB
#define TEST_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define TEST_GPIO_PIN				GPIO_PIN_8

//=============================================LED DO口线配置 (uodate to v5:2023.02.06)
//LED_SER0
#define DO0_GPIO_PORT				GPIOC
#define DO0_GPIO_CLK				RCC_AHBENR_GPIOCEN
#define DO0_GPIO_PIN				GPIO_PIN_7

//LED_OE
#define DO1_GPIO_PORT				GPIOB
#define DO1_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DO1_GPIO_PIN				GPIO_PIN_14

//LED_RCLK
#define DO2_GPIO_PORT				GPIOB
#define DO2_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DO2_GPIO_PIN				GPIO_PIN_15

//LED_SRCLK
#define DO3_GPIO_PORT				GPIOB
#define DO3_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DO3_GPIO_PIN				GPIO_PIN_12

//LED_SRCLR
#define DO4_GPIO_PORT				GPIOB
#define DO4_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DO4_GPIO_PIN				GPIO_PIN_13

//=============================================HX711 CLK DO口线配置 (uodate to v5:2023.03.06)
//HX711_CLK_1
#define DO5_GPIO_PORT				GPIOA
#define DO5_GPIO_CLK				RCC_AHBENR_GPIOAEN
#define DO5_GPIO_PIN				GPIO_PIN_15

//HX711_CLK_2
#define DO6_GPIO_PORT				GPIOD
#define DO6_GPIO_CLK				RCC_AHBENR_GPIODEN
#define DO6_GPIO_PIN				GPIO_PIN_2

//HX711_CLK_3
#define DO7_GPIO_PORT				GPIOB
#define DO7_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DO7_GPIO_PIN				GPIO_PIN_6

//HX711_CLK_4
#define DO8_GPIO_PORT				GPIOB
#define DO8_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DO8_GPIO_PIN				GPIO_PIN_4

//HX711_CLK_5
#define DO9_GPIO_PORT				GPIOA
#define DO9_GPIO_CLK				RCC_AHBENR_GPIOAEN
#define DO9_GPIO_PIN				GPIO_PIN_6

//HX711_CLK_6
#define DO10_GPIO_PORT				GPIOA
#define DO10_GPIO_CLK				RCC_AHBENR_GPIOAEN
#define DO10_GPIO_PIN				GPIO_PIN_4

//HX711_CLK_7
#define DO11_GPIO_PORT				GPIOC
#define DO11_GPIO_CLK				RCC_AHBENR_GPIOCEN
#define DO11_GPIO_PIN				GPIO_PIN_8

//HX711_CLK_8
#define DO12_GPIO_PORT				GPIOB
#define DO12_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DO12_GPIO_PIN				GPIO_PIN_0

//hx711 minus from 8->6,and add 2 len RUN 
//=============================================SYS_RUN DO口线配置 (uodate to v5:2023.02.06)
//SYS RUN0
#define DO13_GPIO_PORT				GPIOA
#define DO13_GPIO_CLK				RCC_AHBENR_GPIOAEN
#define DO13_GPIO_PIN				GPIO_PIN_0


//=============================================LED_QH3 DI口线配置 (uodate to v5:2023.02.06)
//LED_QH3
#define DI0_GPIO_PORT				GPIOC
#define DI0_GPIO_CLK				RCC_AHBENR_GPIOCEN
#define DI0_GPIO_PIN				GPIO_PIN_6

//=============================================HX711 DATA DI口线配置(uodate to v5:2023.02.06)
//HX711_DATA_1
#define DI1_GPIO_PORT				GPIOC
#define DI1_GPIO_CLK				RCC_AHBENR_GPIOCEN
#define DI1_GPIO_PIN				GPIO_PIN_12

//HX711_DATA_2
#define DI2_GPIO_PORT				GPIOB
#define DI2_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DI2_GPIO_PIN				GPIO_PIN_3

//HX711_DATA_3
#define DI3_GPIO_PORT				GPIOB
#define DI3_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DI3_GPIO_PIN				GPIO_PIN_7

//HX711_DATA_4
#define DI4_GPIO_PORT				GPIOB
#define DI4_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DI4_GPIO_PIN				GPIO_PIN_5

//HX711_DATA_5
#define DI5_GPIO_PORT				GPIOA
#define DI5_GPIO_CLK				RCC_AHBENR_GPIOAEN
#define DI5_GPIO_PIN				GPIO_PIN_7

//HX711_DATA_6
#define DI6_GPIO_PORT				GPIOA
#define DI6_GPIO_CLK				RCC_AHBENR_GPIOAEN
#define DI6_GPIO_PIN				GPIO_PIN_5

//HX711_DATA_7
#define DI7_GPIO_PORT				GPIOC
#define DI7_GPIO_CLK				RCC_AHBENR_GPIOCEN
#define DI7_GPIO_PIN				GPIO_PIN_9

//HX711_DATA_8
#define DI8_GPIO_PORT				GPIOB
#define DI8_GPIO_CLK				RCC_AHBENR_GPIOBEN
#define DI8_GPIO_PIN				GPIO_PIN_1

//=============================================KEY (uodate to v3:2021.03.26)
//KEY1
#define DI9_GPIO_PORT				GPIOC
#define DI9_GPIO_CLK				RCC_AHBENR_GPIOCEN
#define DI9_GPIO_PIN				GPIO_PIN_0

//KEY2
#define DI10_GPIO_PORT				GPIOC
#define DI10_GPIO_CLK				RCC_AHBENR_GPIOCEN
#define DI10_GPIO_PIN				GPIO_PIN_1

//output gpio type (uodate to v5:2023.02.06)
typedef enum DoLineType
{
		LED_DO_SER0=0,
		LED_DO_OE,
		LED_DO_RCLK,
		LED_DO_SRCLK,
		LED_DO_SRCLR,
		HX711_CLK_1,
		HX711_CLK_2,
		HX711_CLK_3,
		HX711_CLK_4,
		HX711_CLK_5,
		HX711_CLK_6,
		HX711_CLK_7,
		HX711_CLK_8,
		SYS_RUN0,
		DO_GPIO_NUMBER
}enumDoLineType;

//input gpio type (uodate to v5:2023.02.06)
typedef enum DiLineType
{
		LED_DI_QH3 = 0,       /**< LED数据输入 */
		HX711_DATA_1,
		HX711_DATA_2,
		HX711_DATA_3,
		HX711_DATA_4,
		HX711_DATA_5,
		HX711_DATA_6,
		HX711_DATA_7,
		HX711_DATA_8,
		SYS_KEY_1,//主页 配平模式
		SYS_KEY_2,//去皮
		DI_GPIO_NUMBER
}enumDiLineType;

typedef struct
{
    UINT16 PulseModeL : 1;
    UINT16 PulseModeH : 1;
    UINT16 ExtPulseDir : 1;
    UINT16 SelectUartCan : 1;
    UINT16 SelectRs485Rs422 : 1;
    UINT16 SelectEzEqepZ : 1;
    UINT16 EqeqDir : 1;
    UINT16 Warn : 1;
    UINT16 Fan : 1;
    UINT16 Res : 7;
}structDoStatusType;

typedef union
{
    structDoStatusType bits;
    UINT16 all;
}DoStatusType;


extern void wm_hal_gpio_init( void );
extern UINT8 hal_di_get( UINT8 offset );
extern void hal_gpio_set_do_high( enumDoLineType Do );
extern void hal_gpio_set_do_low( enumDoLineType Do );
#endif
