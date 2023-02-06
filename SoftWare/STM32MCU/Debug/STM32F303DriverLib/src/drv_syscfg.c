/**
  *******************************************************************
  * @file    drv_syscfg.c
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x系统配置模块驱动程序C文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#include "drv_rcc.h"
#include "drv_syscfg.h"

/**
 * @brief  SYSCFG模块复位
 * @retval 无
 */
void drv_syscfg_deinit( void )
{
	drv_rcc_apb2_periph_reset_enable( RCC_APB2RSTR_SYSCFGRST );
	drv_rcc_apb2_periph_reset_disable( RCC_APB2RSTR_SYSCFGRST );
}

/**
 * @brief  SYSCFG外部中断初始化
 * @param  ExtiLinePort: 外部源输入GOPIO口 EXTI_GPIO_PORT_A~EXTI_GPIO_PORT_I
 * @param  ExtiLinePin: 外部源输入PIN EXTI_GPIO_PIN_0~EXTI_GPIO_PIN_15
 * @retval 无
 */
void drv_syscfg_exti_line_init( UINT8 ExtiLinePort, UINT8 ExtiLinePin )
{
	if (ExtiLinePin < 4)
	{
		SYSCFG->EXTICR1.all &= (UINT32)( ~( (UINT32)0x0F << ( 4 * ExtiLinePin ) ) );
		SYSCFG->EXTICR1.all |= (UINT32)( (UINT32)ExtiLinePort << ( 4 * ExtiLinePin ) );
	}
	else if (ExtiLinePin < 8)
	{
		SYSCFG->EXTICR2.all &= (UINT32)( ~( (UINT32)0x0F << ( 4 * ( ExtiLinePin - 4 ) ) ) );
		SYSCFG->EXTICR2.all |= (UINT32)( (UINT32)ExtiLinePort << ( 4 * ( ExtiLinePin - 4 ) ) );
	}
	else if (ExtiLinePin < 12)
	{
		SYSCFG->EXTICR3.all &= (UINT32)( ~( (UINT32)0x0F << ( 4 * ( ExtiLinePin - 8 ) ) ) );
		SYSCFG->EXTICR3.all |= (UINT32)( (UINT32)ExtiLinePort << ( 4 * ( ExtiLinePin - 8 ) ) );
	}
	else
	{
		if (ExtiLinePin < 15)
		{
			SYSCFG->EXTICR4.all &= (UINT32)( ~( (UINT32)0x0F << ( 4 * ( ExtiLinePin - 12 ) ) ) );
			SYSCFG->EXTICR4.all |= (UINT32)( (UINT32)ExtiLinePort << ( 4 * ( ExtiLinePin - 12 ) ) );
		}
	}
}

/**
  * @brief  DMA通道重映射使能.
  * @param  SystemDmaremap: DMA通道:可以是下面的一个.
  *     @arg SYSCFG_DMARemap_TIM17: Remap TIM17 DMA requests from DMA1 channel1 to channel2
  *     @arg SYSCFG_DMARemap_TIM16: Remap TIM16 DMA requests from DMA1 channel3 to channel4
  *     @arg SYSCFG_DMARemap_TIM6DAC1Ch1: Remap TIM6/DAC1 DMA requests from DMA2 channel 3 to DMA1 channel 3
  *     @arg SYSCFG_DMARemap_TIM7DAC1Ch2: Remap TIM7/DAC2 DMA requests from DMA2 channel 4 to DMA1 channel 4
  *     @arg SYSCFG_DMARemap_ADC2ADC4: Remap ADC2 and ADC4 DMA requests from DMA2 channel1/channel3 to channel3/channel4
  *     @arg SYSCFG_DMARemap_DAC2Ch1: Remap DAC2 DMA requests to DMA1 channel5
  *     @arg SYSCFG_DMARemapCh2_SPI1_RX: Remap SPI1 RX DMA1 CH2 requests
  *     @arg SYSCFG_DMARemapCh4_SPI1_RX: Remap SPI1 RX DMA CH4 requests        
  *     @arg SYSCFG_DMARemapCh6_SPI1_RX: Remap SPI1 RX DMA CH6 requests       
  *     @arg SYSCFG_DMARemapCh3_SPI1_TX: Remap SPI1 TX DMA CH2 requests      
  *     @arg SYSCFG_DMARemapCh5_SPI1_TX: Remap SPI1 TX DMA CH5 requests       
  *     @arg SYSCFG_DMARemapCh7_SPI1_TX: Remap SPI1 TX DMA CH7 requests       
  *     @arg SYSCFG_DMARemapCh7_I2C1_RX: Remap I2C1 RX DMA CH7 requests
  *     @arg SYSCFG_DMARemapCh3_I2C1_RX: Remap I2C1 RX DMA CH3 requests       
  *     @arg SYSCFG_DMARemapCh5_I2C1_RX: Remap I2C1 RX DMA CH5 requests      
  *     @arg SYSCFG_DMARemapCh6_I2C1_TX: Remap I2C1 TX DMA CH6 requests       
  *     @arg SYSCFG_DMARemapCh2_I2C1_TX: Remap I2C1 TX DMA CH2 requests       
  *     @arg SYSCFG_DMARemapCh4_I2C1_TX: Remap I2C1 TX DMA CH4 requests   
  *     @arg SYSCFG_DMARemapCh4_ADC2: Remap ADC2 DMA1 Ch4 requests    
  *     @arg SYSCFG_DMARemapCh2_ADC2: Remap ADC2 DMA1 Ch2 requests
  * @note   When enabled, DMA channel of the selected peripheral is remapped
  * @note   When disabled, Default DMA channel is mapped to the selected peripheral
  * @note
  *           By default TIM17 DMA requests is mapped to channel 1
  *           use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Enable)
  *           to remap TIM17 DMA requests to DMA1 channel 2
  *           use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Disable)
  *           to map TIM17 DMA requests to DMA1 channel 1 (default mapping)
  * @retval None
  */
void drv_syscfg_dma_channel_remap_enable( UINT32 SystemDmaremap )
{
  if ((SystemDmaremap & 0x80000000)!= 0x80000000)
  {
      SYSCFG->CFGR1.all |= (UINT32)SystemDmaremap;
  }
  else
  {
      SYSCFG->CFGR3.all |= (UINT32)SystemDmaremap;
  }
}

/**
  * @brief  DMA通道重映射使能.
  * @param  SystemDmaremap: DMA通道:见使能函数说明
  * @note   When enabled, DMA channel of the selected peripheral is remapped
  * @note   When disabled, Default DMA channel is mapped to the selected peripheral
  * @note
  *           By default TIM17 DMA requests is mapped to channel 1
  *           use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Enable)
  *           to remap TIM17 DMA requests to DMA1 channel 2
  *           use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Disable)
  *           to map TIM17 DMA requests to DMA1 channel 1 (default mapping)
  * @retval None
  */
void drv_syscfg_dma_channel_remap_disable( UINT32 SystemDmaremap )
{
  if ((SystemDmaremap & 0x80000000)!= 0x80000000)
  {
      SYSCFG->CFGR1.all &= (UINT32)(~SystemDmaremap);
  }
  else
  {
      SYSCFG->CFGR3.all &= (UINT32)(~SystemDmaremap);
  }
}



