/**
*******************************************************************
* @file    drv_gpio.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x GPIO模块驱动程序
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_GPIO_C__
#define __DRV_GPIO_C__

#include "drv_gpio.h"


/**
* @brief  GPIO口线设置为输入模式.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Pins: 要操作的位 GPIO_PIN_0 ~ GPIO_PIN_15 的组合
* @param  PullMode : 上拉或下拉模式
* @retval 无
*/
void drv_gpio_input_init( GpioType *pPort, UINT16 Pins, enumGpioPuPdType PullMode )
{
	UINT32 pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
	
	for (pinpos = 0x00; pinpos < 0x10; pinpos++)
	{
		pos = ((UINT32)0x01) << pinpos;
		currentpin = Pins & pos;										// 获得端口PIN的值，GPIO_Pin_9 == 0x0200当 \
																		//pinpos=0x09时得到currentpin ==0x0200  
		if (currentpin == pos)
		{
			pPort->MODER.all &= ~( 0x00000003 << ( pinpos*2 ));			  
			pPort->PUPDR.all &= ~( 0x00000003 << ( pinpos*2 ));
			
			pPort->MODER.all |= ( GPIO_MODE_IN << ( pinpos*2 ));		 			
			pPort->PUPDR.all |= ( PullMode << ( pinpos*2 ));			  				
		}
	}
}

/**
* @brief  配置端口为通用输出方式.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Pins: 要操作的位 GPIO_PIN_0 ~ GPIO_PIN_15 的组合
* @param  PullMode : 上拉或下拉模式
* @param  OutType : 输出方式
* @param  Speed : 速度模式
* @retval 无
*/
void drv_gpio_output_init( GpioType *pPort, UINT16 Pins, enumGpioPuPdType PullMode, enumGpioOutputType OutType, enumGpioSpeedType Speed )
{
	UINT32 pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
	
	for (pinpos = 0x00; pinpos < 0x10; pinpos++)
	{
		pos = ((UINT32)0x01) << pinpos;
		currentpin = Pins & pos;											// 获得端口PIN的值，GPIO_Pin_9 == 0x0200当 \
																			//pinpos=0x09时得到currentpin ==0x0200  
		if (currentpin == pos)
		{
			pPort->MODER.all &= ~( 0x00000003 << ( pinpos*2 ));
			pPort->OTYPER.all &= ~( 0x00000003 << ( pinpos*2 ));		  
			pPort->PUPDR.all &= ~( 0x00000003 << ( pinpos*2 ));
			pPort->OSPEEDR.all &= ~( 0x00000003 << ( pinpos*2 ));
			
			pPort->MODER.all |= ( GPIO_MODE_OUT << ( pinpos*2 ));		  			
			pPort->OTYPER.all |= ( (UINT32)OutType << ( pinpos ));		  				
			pPort->PUPDR.all |= ( (UINT32)PullMode << ( pinpos*2 ));					
			pPort->OSPEEDR.all |= ( (UINT32)Speed << ( pinpos*2 ));		 	
		}
	}
}

/**
* @brief  配置端口为模拟功能.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Pins: 要操作的位 GPIO_PIN_0 ~ GPIO_PIN_15 的组合
* @retval 无
*/
void drv_gpio_analog_init( GpioType *pPort, UINT16 Pins )
{
	UINT32 pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
	
	for (pinpos = 0x00; pinpos < 0x10; pinpos++)
	{
		pos = ((UINT32)0x01) << pinpos;
		currentpin = Pins & pos;										// 获得端口PIN的值，GPIO_Pin_9 == 0x0200当 \
																		pinpos=0x09时得到currentpin ==0x0200  
		if (currentpin == pos)
		{
			pPort->MODER.all &= ~( 0x00000003 << ( pinpos*2 ));			  
			pPort->PUPDR.all &= ~( 0x00000003 << ( pinpos*2 ));
			
			pPort->MODER.all |= ( GPIO_MODE_ANALOG << ( pinpos*2 ));		 			
			pPort->PUPDR.all |= ( GPIO_PUPD_NOPULL << ( pinpos*2 ));	 				
		}
	}
}

/**
* @brief  配置端口为复用功能.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  Pins: 要操作的位 GPIO_PIN_0 ~ GPIO_PIN_15 的组合
* @param  PullMode : 上拉或下拉模式
* @param  OutType : 输出方式
* @param  Speed : 速度模式
* @retval 无
*/
void drv_gpio_alternate_function_init( GpioType *pPort, UINT16 Pins, enumGpioPuPdType PullMode, enumGpioOutputType OutType, enumGpioSpeedType Speed )
{
	UINT32 pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
	
	for (pinpos = 0x00; pinpos < 0x10; pinpos++)
	{
		pos = ((UINT32)0x01) << pinpos;
		currentpin = Pins & pos;											// 获得端口PIN的值，GPIO_Pin_9 == 0x0200当 \
																			//pinpos=0x09时得到currentpin ==0x0200  
		if (currentpin == pos)
		{
			pPort->MODER.all &= ~( 0x00000003 << ( pinpos*2 ));
			pPort->OTYPER.all &= ~( 0x00000003 << ( pinpos*2 ));				 
			pPort->PUPDR.all &= ~( 0x00000003 << ( pinpos*2 ));
			pPort->OSPEEDR.all &= ~( 0x00000003 << ( pinpos*2 ));
			
			pPort->MODER.all |= ( (UINT32)GPIO_MODE_AF << ( pinpos*2 ));					
			pPort->OTYPER.all |= ( (UINT32)OutType << ( pinpos ));				 				
			pPort->PUPDR.all |= ( (UINT32)PullMode << ( pinpos*2 ));			 				
			pPort->OSPEEDR.all |= ( (UINT32)Speed << ( pinpos*2 ));					
		}
	}

}

/**
* @brief  配置端口连接到复用功能引脚.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @param  GpioPinSource: 要操作的位 GPIO_PINSOURCE0 ~ GPIO_PINSOURCE15
* @param  GpioAf : 复用功能，可以是下面值中的一个
*            @arg GPIO_AF_RTC_50Hz: 连接 RTC_50Hz 到 AF0 (默认)
*            @arg GPIO_AF_MCO: 连接 MCO (MCO1 和 MCO2) 到 AF0 (默认)
*            @arg GPIO_AF_TAMPER: 连接 TAMPER (TAMPER_1 和 TAMPER_2) 到 AF0 (默认)
*            @arg GPIO_AF_SWJ: 连接 SWJ (SWD 和 JTAG) 到 AF0 (默认)
*            @arg GPIO_AF_TRACE: 连接 TRACE 到 AF0 (默认)
*            @arg GPIO_AF_TIM1: 连接 TIM1 到 AF1
*            @arg GPIO_AF_TIM2: 连接 TIM2 到 AF1
*            @arg GPIO_AF_TIM3: 连接 TIM3 到 AF2
*            @arg GPIO_AF_TIM4: 连接 TIM4 到 AF2
*            @arg GPIO_AF_TIM5: 连接 TIM5 到 AF2
*            @arg GPIO_AF_TIM8: 连接 TIM8 到 AF3
*            @arg GPIO_AF_TIM9: 连接 TIM9 到 AF3
*            @arg GPIO_AF_TIM10: 连接 TIM10 到 AF3
*            @arg GPIO_AF_TIM11: 连接 TIM11 到 AF3
*            @arg GPIO_AF_I2C1: 连接 I2C1 到 AF4
*            @arg GPIO_AF_I2C2: 连接 I2C2 到 AF4
*            @arg GPIO_AF_I2C3: 连接 I2C3 到 AF4
*            @arg GPIO_AF_SPI1: 连接 SPI1 到 AF5
*            @arg GPIO_AF_SPI2: 连接 SPI2/I2S2 到 AF5
*            @arg GPIO_AF_SPI4: 连接 SPI4 到 AF5
*            @arg GPIO_AF_SPI5: 连接 SPI5 到 AF5
*            @arg GPIO_AF_SPI6: 连接 SPI6 到 AF5
*            @arg GPIO_AF_SPI3: 连接 SPI3/I2S3 到 AF6
*            @arg GPIO_AF_I2S3ext: 连接 I2S3ext 到 AF7
*            @arg GPIO_AF_USART1: 连接 USART1 到 AF7
*            @arg GPIO_AF_USART2: 连接 USART2 到 AF7
*            @arg GPIO_AF_USART3: 连接 USART3 到 AF7
*            @arg GPIO_AF_UART4: 连接 UART4 到 AF8
*            @arg GPIO_AF_UART5: 连接 UART5 到 AF8
*            @arg GPIO_AF_USART6: 连接 USART6 到 AF8
*            @arg GPIO_AF_UART7: 连接 UART7 到 AF8
*            @arg GPIO_AF_UART8: 连接 UART8 到 AF8
*            @arg GPIO_AF_CAN1: 连接 CAN1 到 AF9
*            @arg GPIO_AF_CAN2: 连接 CAN2 到 AF9
*            @arg GPIO_AF_TIM12: 连接 TIM12 到 AF9
*            @arg GPIO_AF_TIM13: 连接 TIM13 到 AF9
*            @arg GPIO_AF_TIM14: 连接 TIM14 到 AF9
*            @arg GPIO_AF_OTG_FS: 连接 OTG_FS 到 AF10
*            @arg GPIO_AF_OTG_HS: 连接 OTG_HS 到 AF10
*            @arg GPIO_AF_ETH: 连接 ETHERNET 到 AF11
*            @arg GPIO_AF_FSMC: 连接 FSMC 到 AF12
*            @arg GPIO_AF_OTG_HS_FS: 连接 OTG HS (configured in FS) 到 AF12
*            @arg GPIO_AF_SDIO: 连接 SDIO 到 AF12
*            @arg GPIO_AF_DCMI: 连接 DCMI 到 AF13
*            @arg GPIO_AF_EVENTOUT: 连接 EVENTOUT 到 AF15
* @retval 无
*/
void drv_gpio_alternate_function_connect( GpioType *pPort, UINT16 GpioPinSource, UINT8 GpioAf )
{
	UINT32 temp = 0x00, temp_2 = 0x00;

	temp = (( UINT32 )( GpioAf ) << (( UINT32 )(( UINT32 )GpioPinSource & ( UINT32 )0x07 ) * 4 ));
	if (GpioPinSource < 8)
	{
		pPort->AFRL.all &= ~(( UINT32 )0xF << (( UINT32 )(( UINT32 )GpioPinSource & ( UINT32 )0x07 ) * 4 ));
		temp_2 = pPort->AFRL.all | temp;
		pPort->AFRL.all = temp_2;						 
	}
	else
	{
		pPort->AFRH.all &= ~(( UINT32 )0xF << (( UINT32 )(( UINT32 )GpioPinSource & ( UINT32 )0x07 ) * 4 ));
		temp_2 = pPort->AFRH.all | temp;
		pPort->AFRH.all = temp_2;												  
	}

}


/**
* @brief  读指定端口所有位电平状态.
* @param  pPort: 可以是 GPIOA ~ GPIOH
* @retval 端口所有位当前状态
*/
UINT16 drv_gpio_get_port_value( GpioType *pPort )
{
	return (( UINT16 )pPort->IDR.all );
}

#endif
