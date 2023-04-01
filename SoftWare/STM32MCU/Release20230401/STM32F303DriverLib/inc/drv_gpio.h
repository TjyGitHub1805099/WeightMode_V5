/**
*******************************************************************
* @file    drv_gpio.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x GPIO模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include "reg_stm32f303_gpio.h"

/** GPIO端口位定义 */
#define GPIO_PIN_0                 ((UINT16)0x0001)  /* 端口 0 */
#define GPIO_PIN_1                 ((UINT16)0x0002)  /* 端口 1 */
#define GPIO_PIN_2                 ((UINT16)0x0004)  /* 端口 2 */
#define GPIO_PIN_3                 ((UINT16)0x0008)  /* 端口 3 */
#define GPIO_PIN_4                 ((UINT16)0x0010)  /* 端口 4 */
#define GPIO_PIN_5                 ((UINT16)0x0020)  /* 端口 5 */
#define GPIO_PIN_6                 ((UINT16)0x0040)  /* 端口 6 */
#define GPIO_PIN_7                 ((UINT16)0x0080)  /* 端口 7 */
#define GPIO_PIN_8                 ((UINT16)0x0100)  /* 端口 8 */
#define GPIO_PIN_9                 ((UINT16)0x0200)  /* 端口 9 */
#define GPIO_PIN_10                ((UINT16)0x0400)  /* 端口 10 */
#define GPIO_PIN_11                ((UINT16)0x0800)  /* 端口 11 */
#define GPIO_PIN_12                ((UINT16)0x1000)  /* 端口 12 */
#define GPIO_PIN_13                ((UINT16)0x2000)  /* 端口 13 */
#define GPIO_PIN_14                ((UINT16)0x4000)  /* 端口 14 */
#define GPIO_PIN_15                ((UINT16)0x8000)  /* 端口 15 */
#define GPIO_PIN_All               ((UINT16)0xFFFF)  /* 所有 端口 */

#define IS_GPIO_PIN(PIN) ((((PIN) & (UINT16)0x00) == 0x00) && ((PIN) != (UINT16)0x00))
#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_PIN_0) || \
                              ((PIN) == GPIO_PIN_1) || \
                              ((PIN) == GPIO_PIN_2) || \
                              ((PIN) == GPIO_PIN_3) || \
                              ((PIN) == GPIO_PIN_4) || \
                              ((PIN) == GPIO_PIN_5) || \
                              ((PIN) == GPIO_PIN_6) || \
                              ((PIN) == GPIO_PIN_7) || \
                              ((PIN) == GPIO_PIN_8) || \
                              ((PIN) == GPIO_PIN_9) || \
                              ((PIN) == GPIO_PIN_10) || \
                              ((PIN) == GPIO_PIN_11) || \
                              ((PIN) == GPIO_PIN_12) || \
                              ((PIN) == GPIO_PIN_13) || \
                              ((PIN) == GPIO_PIN_14) || \
                              ((PIN) == GPIO_PIN_15))

/** GPIO复用源定义 */
#define GPIO_PINSOURCE0            ((UINT16)0x00)
#define GPIO_PINSOURCE1            ((UINT16)0x01)
#define GPIO_PINSOURCE2            ((UINT16)0x02)
#define GPIO_PINSOURCE3            ((UINT16)0x03)
#define GPIO_PINSOURCE4            ((UINT16)0x04)
#define GPIO_PINSOURCE5            ((UINT16)0x05)
#define GPIO_PINSOURCE6            ((UINT16)0x06)
#define GPIO_PINSOURCE7            ((UINT16)0x07)
#define GPIO_PINSOURCE8            ((UINT16)0x08)
#define GPIO_PINSOURCE9            ((UINT16)0x09)
#define GPIO_PINSOURCE10           ((UINT16)0x0A)
#define GPIO_PINSOURCE11           ((UINT16)0x0B)
#define GPIO_PINSOURCE12           ((UINT16)0x0C)
#define GPIO_PINSOURCE13           ((UINT16)0x0D)
#define GPIO_PINSOURCE14           ((UINT16)0x0E)
#define GPIO_PINSOURCE15           ((UINT16)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PINSOURCE0) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE1) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE2) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE3) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE4) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE5) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE6) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE7) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE8) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE9) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE10) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE11) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE12) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE13) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE14) || \
                                       ((PINSOURCE) == GPIO_PINSOURCE15))

/** 复用功能定义 */
//AF0 JTCK-SWCLK, JTDI, JTDO/TRACESW0, JTMS-SWDAT, MCO, NJTRST, TRACED, TRACECK 
#define GPIO_AF0_JTDI					((UINT8)0x00)
#define GPIO_AF0_JTDO					((UINT8)0x00)
#define GPIO_AF0_TRACESW0				((UINT8)0x00)
#define GPIO_AF0_JTMS_SWDAT				((UINT8)0x00)
#define GPIO_AF0_MCO					((UINT8)0x00)
#define GPIO_AF0_NTTRST					((UINT8)0x00)
#define GPIO_AF0_TRACED					((UINT8)0x00)
#define GPIO_AF0_TRACECK				((UINT8)0x00)
#define GPIO_AF0_JTCK_SWCLK 			((UINT8)0x00)           
//AF1 OUT, TIM2, TIM15, TIM16, TIM17
#define GPIO_AF1_OUT            		((UINT8)0x01)
#define GPIO_AF1_TIM2            		((UINT8)0x01) 
#define GPIO_AF1_TIM15            		((UINT8)0x01) 
#define GPIO_AF1_TIM16            		((UINT8)0x01) 
#define GPIO_AF1_TIM17            		((UINT8)0x01) 
//AF2 COMP1_OUT, TIM1, TIM2, TIM3, TIM4, TIM8, TIM15, TIM16
#define GPIO_AF2_COMP1            		((UINT8)0x02) 
#define GPIO_AF2_TIM1            		((UINT8)0x02)
#define GPIO_AF2_TIM2            		((UINT8)0x02)
#define GPIO_AF2_TIM3            		((UINT8)0x02)
#define GPIO_AF2_TIM4            		((UINT8)0x02)
#define GPIO_AF2_TIM8            		((UINT8)0x02)
#define GPIO_AF2_TIM15            		((UINT8)0x02)
#define GPIO_AF2_TIM16            		((UINT8)0x02)
//AF3 COMP7_OUT, TIM8, TIM15, Touch, HRTIM1
#define GPIO_AF3_COMP7            		((UINT8)0x03)
#define GPIO_AF3_TIM8            		((UINT8)0x03)
#define GPIO_AF3_TIM15            		((UINT8)0x03)
#define GPIO_AF3_TOUCH            		((UINT8)0x03)
#define GPIO_AF3_HRTIM1            		((UINT8)0x03)
//AF4 I2C1, I2C2, TIM1, TIM8, TIM16, TIM17
#define GPIO_AF4_I2C1            		((UINT8)0x04)
#define GPIO_AF4_I2C2            		((UINT8)0x04)
#define GPIO_AF4_TIM1            		((UINT8)0x04)
#define GPIO_AF4_TIM8            		((UINT8)0x04)
#define GPIO_AF4_TIM16            		((UINT8)0x04)
#define GPIO_AF4_TIM17            		((UINT8)0x04)
//AF5 IR_OUT, I2S2, I2S3, SPI1, SPI2, TIM8, USART4, USART5 
#define GPIO_AF5_IR_OUT            		((UINT8)0x05) 
#define GPIO_AF5_I2S2            		((UINT8)0x05) 
#define GPIO_AF5_I2S3            		((UINT8)0x05) 
#define GPIO_AF5_SPI1            		((UINT8)0x05) 
#define GPIO_AF5_SPI2            		((UINT8)0x05) 
#define GPIO_AF5_TIM8            		((UINT8)0x05) 
#define GPIO_AF5_USART4            		((UINT8)0x05) 
#define GPIO_AF5_USART5            		((UINT8)0x05) 
//AF6 IR_OUT, I2S2, I2S3, SPI2, SPI3, TIM1, TIM8 
#define GPIO_AF6_IR_OUT            		((UINT8)0x06) 
#define GPIO_AF6_I2S2            		((UINT8)0x06)
#define GPIO_AF6_I2S3            		((UINT8)0x06)
#define GPIO_AF6_SPI2            		((UINT8)0x06)
#define GPIO_AF6_SPI3            		((UINT8)0x06)
#define GPIO_AF6_TIM1            		((UINT8)0x06)
#define GPIO_AF6_TIM8            		((UINT8)0x06)
//AF7 AOP2_OUT, CAN, COMP3_OUT, COMP5_OUT, COMP6_OUT, USART1, USART2, USART3
#define GPIO_AF7_AOP2_OUT            	((UINT8)0x07)
#define GPIO_AF7_COMP3_OUT            	((UINT8)0x07)
#define GPIO_AF7_COMP5_OUT            	((UINT8)0x07)
#define GPIO_AF7_COMP6_OUT            	((UINT8)0x07)
#define GPIO_AF7_CAN            		((UINT8)0x07)
#define GPIO_AF7_USART1            		((UINT8)0x07)
#define GPIO_AF7_USART2            		((UINT8)0x07)
#define GPIO_AF7_USART3            		((UINT8)0x07)
//AF8 COMP1_OUT, COMP2_OUT, COMP3_OUT, COMP4_OUT, COMP5_OUT, COMP6_OUT 
#define GPIO_AF8_COMP1_OUT            	((UINT8)0x08)
#define GPIO_AF8_COMP2_OUT            	((UINT8)0x08)
#define GPIO_AF8_COMP3_OUT            	((UINT8)0x08)
#define GPIO_AF8_COMP4_OUT            	((UINT8)0x08)
#define GPIO_AF8_COMP5_OUT            	((UINT8)0x08)
#define GPIO_AF8_COMP6_OUT            	((UINT8)0x08)
//AF9 AOP4_OUT, CAN, TIM1, TIM8, TIM15
#define GPIO_AF9_AOP4_OUT            	((UINT8)0x09)
#define GPIO_AF9_CAN            		((UINT8)0x09)
#define GPIO_AF9_TIM1            		((UINT8)0x09)
#define GPIO_AF9_TIM8            		((UINT8)0x09)
#define GPIO_AF9_TIM15            		((UINT8)0x09)
//AF10 AOP1_OUT, AOP3_OUT, TIM2, TIM3, TIM4, TIM8, TIM17
#define GPIO_AF10_AOP1_OUT            	((UINT8)0x0A)
#define GPIO_AF10_AOP3_OUT            	((UINT8)0x0A)
#define GPIO_AF10_TIM2            		((UINT8)0x0A)
#define GPIO_AF10_TIM3            		((UINT8)0x0A)
#define GPIO_AF10_TIM4            		((UINT8)0x0A)
#define GPIO_AF10_TIM8            		((UINT8)0x0A)
#define GPIO_AF10_TIM17            		((UINT8)0x0A)
//AF11 TIM1, TIM8
#define GPIO_AF11_TIM1           		((UINT8)0x0B)
#define GPIO_AF11_TIM8           		((UINT8)0x0B)
//AF12 TIM1, HRTIM1
#define GPIO_AF12_TIM1            		((UINT8)0x0C)
#define GPIO_AF12_HRTIM1            	((UINT8)0x0C)
//AF13 HRTIM1, AOP2_OUT
#define GPIO_AF13_HRTIM1            	((UINT8)0x0D)
#define GPIO_AF13_AOP2_OUT            	((UINT8)0x0D)
//AF14 USBDM, USBDP
#define GPIO_AF14_USBDM            		((UINT8)0x0E)
#define GPIO_AF14_USBDP            		((UINT8)0x0E)
//AF15 OUT
#define GPIO_AF15_OUT            		((UINT8)0x0F) 


/** GPIO模式定义 */
typedef enum enumGpioModeType
{
	GPIO_MODE_IN = 0,							/**< GPIO输入模式 */
	GPIO_MODE_OUT = 1,							/**< GPIO输出模式 */
	GPIO_MODE_AF = 2,							/**< GPIO复用模式 */
	GPIO_MODE_ANALOG = 3						/**< GPIO模拟模式 */
}enumGpioModeType;

/** GPIO输出类型定义 */
typedef enum GpioOutputType
{
	GPIO_OTYPE_PP = 0,							/**< GPIO推挽输出 */
	GPIO_OTYPE_OD = 1							/**< GPIO开漏输出 */
}enumGpioOutputType;

/** GPIO输出速度定义 */
typedef enum GpioSpeedType
{
	GPIO_SPEED_LOW = 0,							/**< GPIO输出速度 低速 */
	GPIO_SPEED_MID = 1,							/**< GPIO输出速度 中速 */
	GPIO_SPEED_HIGH = 3							/**< GPIO输出速度 高速 */
}enumGpioSpeedType;

/** GPIO上拉下拉定义 */
typedef enum GpioPuPdType
{
	GPIO_PUPD_NOPULL = 0,						/**< GPIO无上拉下拉 */
	GPIO_PUPD_PULL = 1,							/**< GPIO上拉 */
	GPIO_PUPD_DOWN = 2							/**< GPIO下拉 */
}enumGpioPuPdType;


/**
* @brief  设置指定端口的某些位为高电平.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Pins: 要操作的位 GPIO_PIN_0 ~ GPIO_PIN_15 的组合
* @retval 无
*/
void __INLINE drv_gpio_set_pins_high( GpioType *pPort, UINT16 Pins )
{
	pPort->BSRRL.all |= Pins;
}

/**
* @brief  设置指定端口的某些位为低电平.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Pins: 要操作的位 GPIO_PIN_0 ~ GPIO_PIN_15 的组合
* @retval 无
*/
void __INLINE drv_gpio_set_pins_low( GpioType *pPort, UINT16 Pins )
{
	pPort->BSRRH.all |= Pins;
}

/**
* @brief  设置指定端口所有位状态.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Value: 端口所有位值
* @retval 无
*/
void __INLINE drv_gpio_set_port_value( GpioType *pPort, UINT16 Value )
{
	pPort->ODR.all = Value;
}

/**
* @brief  将指定端口指定位状态翻转.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Pins 要操作的位 GPIO_PIN_0 ~ GPIO_PIN_15
* @retval 无
*/
void __INLINE drv_gpio_toggle_pin( GpioType *pPort, UINT16 Pin )
{
	pPort->ODR.all ^= Pin;
}

/**
* @brief  读指定端口指定位的状态.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Pin: 要操作的位 GPIO_PIN_0 ~ GPIO_PIN_15
* @retval 0表示低电平，1为高电平
*/
__INLINE UINT8 drv_gpio_get_pin_status( GpioType *pPort, UINT16 Pin )
{
    if( (pPort->IDR.all & Pin) != 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

extern void drv_gpio_input_init( GpioType *pPort, UINT16 Pins, enumGpioPuPdType PullMode );
extern void drv_gpio_output_init( GpioType *pPort, UINT16 Pins, enumGpioPuPdType PullMode, enumGpioOutputType OutType, enumGpioSpeedType Speed );
extern void drv_gpio_analog_init( GpioType *pPort, UINT16 Pins );
extern void drv_gpio_alternate_function_init( GpioType *pPort, UINT16 Pins, enumGpioPuPdType PullMode, enumGpioOutputType OutType, enumGpioSpeedType Speed );
extern void drv_gpio_alternate_function_connect( GpioType *pPort, UINT16 GpioPinSource, UINT8 GpioAf );
extern UINT16 drv_gpio_get_port_value( GpioType *pPort );



#endif

