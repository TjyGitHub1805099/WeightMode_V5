/**
  *******************************************************************
  * @file    hal_gpio.c
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   GPIO程序C文件(抽象层)
  *******************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
  
#include "typedefine.h"
#include "hal_gpio.h"

/*
	OUTPUT
*/
GPIO_TypeDef* 		DO_GPIO_PORT[] = { \
DO0_GPIO_PORT, \
DO1_GPIO_PORT, \
DO2_GPIO_PORT, \
DO3_GPIO_PORT, \
DO4_GPIO_PORT, \
DO5_GPIO_PORT, \
DO6_GPIO_PORT, \
DO7_GPIO_PORT, \
DO8_GPIO_PORT, \
DO9_GPIO_PORT, \
DO10_GPIO_PORT, \
DO11_GPIO_PORT, \
DO12_GPIO_PORT, \
DO13_GPIO_PORT, \
};

const UINT16  DO_GPIO_PIN[]  = { \
DO0_GPIO_PIN, \
DO1_GPIO_PIN, \
DO2_GPIO_PIN, \
DO3_GPIO_PIN, \
DO4_GPIO_PIN, \
DO5_GPIO_PIN, \
DO6_GPIO_PIN, \
DO7_GPIO_PIN, \
DO8_GPIO_PIN, \
DO9_GPIO_PIN, \
DO10_GPIO_PIN, \
DO11_GPIO_PIN, \
DO12_GPIO_PIN, \
DO13_GPIO_PIN, \
};
/*
	INPUT
*/
GPIO_TypeDef* 		DI_GPIO_PORT[] = { \
DI0_GPIO_PORT, \
DI1_GPIO_PORT, \
DI2_GPIO_PORT, \
DI3_GPIO_PORT, \
DI4_GPIO_PORT, \
DI5_GPIO_PORT, \
DI6_GPIO_PORT, \
DI7_GPIO_PORT, \
DI8_GPIO_PORT, \
DI9_GPIO_PORT, \
DI10_GPIO_PORT, \
};

const UINT16  DI_GPIO_PIN[]  = { \
DI0_GPIO_PIN, \
DI1_GPIO_PIN, \
DI2_GPIO_PIN, \
DI3_GPIO_PIN, \
DI4_GPIO_PIN, \
DI5_GPIO_PIN, \
DI6_GPIO_PIN, \
DI7_GPIO_PIN, \
DI8_GPIO_PIN, \
DI9_GPIO_PIN, \
DI10_GPIO_PIN, \
};

/**
* @brief  DI输人采样
* @param  offset: 要采样的口线
* @retval UINT8 : 高/低
*/
UINT8 hal_di_get( UINT8 offset )
{
		//if ( 0 == drv_gpio_get_pin_status( DI_GPIO_PORT[ offset ], DI_GPIO_PIN[ offset ] ) )
		if ( 0 == HAL_GPIO_ReadPin( DI_GPIO_PORT[ offset ], DI_GPIO_PIN[ offset ] ) )
		{
			return 0;
		}
		else
		{
			return 1;
		}
		
}

/**
* @brief  DO输出高电平
* @param  Do: 要设置的口线
* @retval 无
*/
void hal_gpio_set_do_high( enumDoLineType Do )
{
    //drv_gpio_set_pins_high( DO_GPIO_PORT[Do], DO_GPIO_PIN[Do] );
	HAL_GPIO_WritePin(DO_GPIO_PORT[Do] ,  DO_GPIO_PIN[Do] , GPIO_PIN_SET);
}

/**
* @brief  DO输出低电平
* @param  Do: 要设置的口线
* @retval 无
*/
void hal_gpio_set_do_low( enumDoLineType Do )
{
    //drv_gpio_set_pins_low( DO_GPIO_PORT[Do], DO_GPIO_PIN[Do] );
	HAL_GPIO_WritePin(DO_GPIO_PORT[Do] ,  DO_GPIO_PIN[Do] , GPIO_PIN_RESET);
}
