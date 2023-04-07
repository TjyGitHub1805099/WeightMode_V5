/**
*******************************************************************
* @file    drv_adc.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40xADC模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/


#include "drv_rcc.h"
#include "drv_delay.h"
#include "drv_adc.h"

/**
* @brief  ADC复位
* @retval 无
*/
void drv_adc_deinit( AdcType* pAdc )
{ 
	if(( pAdc == ADC1 ) || ( pAdc == ADC2))
	{
		drv_rcc_ahb_periph_reset_enable( RCC_AHBRSTR_ADC12RST );
		drv_rcc_ahb_periph_reset_disable( RCC_AHBRSTR_ADC12RST );
	}
	else
	{
		if(( pAdc == ADC3 ) || ( pAdc == ADC4 ))
		{
			drv_rcc_ahb_periph_reset_enable( RCC_AHBRSTR_ADC34RST );
			drv_rcc_ahb_periph_reset_disable( RCC_AHBRSTR_ADC34RST );
		}
	}
}

/**
* @brief  ADC初始化
* @param  pAdc: ADC1~ADC3
* @param  pChannel: 通道号数组
* @param  pQueue: 采样顺序数组
* @param  ChannelNumber: 通道数量
* @retval 无
*/
void drv_adc_init( AdcType* pAdc, UINT8 *pChannel, UINT8 *pQueue, UINT8 ChannelNumber )
{
	UINT8 i = 0;
	UINT32 l_Cr;
	
	pAdc->CR.bit.ADVREGEN = 1;			//使能电压调整
	drv_delay_us( 10 );
	pAdc->CR.bit.ADCALDIF = 0;			
	pAdc->CR.bit.ADCAL = 1;				//使能校正
	do{
		l_Cr = (UINT32)pAdc->CR.all;
		l_Cr = l_Cr & 0x80000000;
	}while( l_Cr != 0 );				//等待校正完成
	
	//ADC通用寄存器设置
	if(( pAdc == ADC1 ) || ( pAdc == ADC2 ))
	{
		ADC1_2->CCR.bit.CKMODE	= (UINT16)ADC_ASYN_CLK_MODE;		//异步时钟模式
		ADC1_2->CCR.bit.DUAL	= (UINT16)MULTI_Independent_All;	//ADC独立
		ADC1_2->CCR.bit.MDMA	= 0;		//使能多重ADC DMA
		ADC1_2->CCR.bit.DMACFG	= 0;		
	}
	else
	{
		if(( pAdc == ADC3 ) || ( pAdc == ADC4 ))
		{
			ADC3_4->CCR.bit.CKMODE	= (UINT16)ADC_ASYN_CLK_MODE;	//异步时钟模式
			ADC3_4->CCR.bit.DUAL = (UINT16)MULTI_Independent_All;	//ADC独立
			ADC3_4->CCR.bit.MDMA	= 1;		//使能多重ADC DMA
			ADC3_4->CCR.bit.DMACFG	= 1;		//ADC循环触发
		}
	}
	//ADC初始化
	pAdc->CFGR.bit.JAUTO = 0;		//自动注入组采样禁止
	pAdc->CFGR.bit.CONT = 1;		//连续采样使能
	pAdc->CFGR.bit.OVRMOD = 0;		//过溢时新的值覆盖最后一个值
	pAdc->CFGR.bit.EXTEN = (UINT16)EXTEN_Disable;			//禁止外部触发
	pAdc->CFGR.bit.EXTSEL = 0;
	pAdc->CFGR.bit.ALIGN = (UINT16)ADC_DATA_ALIGH_RIGHT;	//右对齐
	pAdc->CFGR.bit.RES = (UINT16)RES_12;					//12BIT分辨率
	pAdc->CFGR.bit.DMACFG = (UINT16)ADC_DMA_CIRCULAR_MODE;	//ADC循环触发
	pAdc->CFGR.bit.DMAEN = 1;		                        //使能DMA
	pAdc->SQR1.bit.L = (UINT16)ChannelNumber - 1;
	
	for( i = 0; i < ChannelNumber; i++ )
	{
		//采样时间3个周期
		if( pChannel[ i ] > AWDCH_9 )
		{
			pAdc->SMPR2.all &= (UINT32)( ~( 0x00000007 << ( 3 * ( pChannel[ i ] - 10 )) ));
			pAdc->SMPR2.all |= (UINT32)( Channel_Sampling_Clcle_1_5 << ( 3 * ( pChannel[ i ] - 10 )));
		}
		else
		{
			pAdc->SMPR1.all &= (UINT32)( ~( 0x00000007 << ( 3 * pChannel[ i ] ) ));
			pAdc->SMPR1.all |= (UINT32)( Channel_Sampling_Clcle_1_5 << ( 3 * pChannel[ i ] ));
		}
		
		//采样顺序
		if( i < 4 )		//SQR1寄存器,序列1~4  i循环从数组0号元素开始
		{

				pAdc->SQR1.all &= (UINT32)( ~( 0x0000001F << ( 6 * ( i + 1 ))));	//前6位保留
				pAdc->SQR1.all |= (UINT32)( pQueue[ i ] << ( 6 * ( i + 1 ) ));
		}
		else if( i < 9 )					//SQR2寄存器,5~9
		{
			pAdc->SQR2.all &= (UINT32)( ~( 0x0000001F << ( 6 * ( i - 4 ))));
			pAdc->SQR2.all |= (UINT32)( pQueue[ i ] << ( 6 * ( i - 4 )));
		}
		else if( i < 14 )					//SQR3寄存器,10~14
		{
			pAdc->SQR3.all &= (UINT32)( ~( 0x0000001F << ( 6 * ( i - 9 )) ));
			pAdc->SQR3.all |= (UINT32)( pQueue[ i ] << ( 6 * ( i - 9 )) );
		}
		else
		{
			pAdc->SQR4.all &= (UINT32)( ~( 0x0000001F << ( 6 * ( i - 14 )) ));
			pAdc->SQR4.all |= (UINT32)( pQueue[ i ] << ( 6 * ( i - 14 )) );
		}
	}
	
	pAdc->CR.bit.ADEN = 1;			//使能ADC
}

/**
* @brief  ADC使能
* @param  pAdc: ADC1~ADC3
* @retval 无
*/
void drv_adc_enable( AdcType* pAdc )
{ 
	pAdc->CR.bit.ADEN = 1;
}

/**
* @brief  ADC禁止
* @param  pAdc: ADC1~ADC3
* @retval 无
*/
void drv_adc_disable( AdcType* pAdc )
{ 
	pAdc->CR.bit.ADDIS = 1;
}

/**
* @brief  ADC使能DMA
* @param  pAdc: ADC1~ADC3
* @retval 无
*/
void drv_adc_dma_enable( AdcType* pAdc )
{
	pAdc->CFGR.bit.DMAEN = 1;
}

/**
* @brief  ADC禁用DMA
* @param  pAdc: ADC1~ADC3
* @retval 无
*/
void drv_adc_dma_disable( AdcType* pAdc )
{ 
	pAdc->CFGR.bit.DMAEN = 0;
}

/**
* @brief  获取ADC采样值
* @param  pAdc: ADC1~ADC3
* @retval 无
*
*/
UINT16 drv_adc_get_value( AdcType* pAdc )
{
	AdcIsrType l_AdcSr;
	
	l_AdcSr.all = pAdc->ISR.all;
	while( l_AdcSr.bit.EOC == 0 )
	{
	}
	
	return ( (UINT16)( pAdc->DR ) );
}

/**
* @brief  ADC开始转换
* @param  pAdc: ADC1~ADC3
* @retval 无
*/
void drv_adc_software_start( AdcType* pAdc )
{
	pAdc->CR.bit.ADSTART = 1;
}

/**
* @brief  ADC停止转换
* @param  pAdc: ADC1~ADC3
* @retval 无
*/
void drv_adc_software_stop( AdcType* pAdc )
{
	pAdc->CR.bit.ADSTP = 1;
}

/**
* @brief  ADC模块中断使能
* @param  pAdc: ADC1~ADC3
* @param  AdcIt: ADC模块中断源,可以是下面值的组合
*            @arg ADC_IT_RDY
*            @arg ADC_IT_EOSMP
*            @arg ADC_IT_EOC
*            @arg ADC_IT_EOS
*            @arg ADC_IT_OVR
*            @arg ADC_IT_JEOC
*            @arg ADC_IT_AWD1
*            @arg ADC_IT_AWD2
*            @arg ADC_IT_AWD3
*            @arg ADC_IT_JQOVF
* @retval 无
*/
void drv_adc_it_enable( AdcType* pAdc, UINT32 AdcIt )
{ 
	pAdc->IER.all |= AdcIt;
}

/**
* @brief  ADC模块中断禁止
* @param  pAdc: ADC1~ADC3
* @param  AdcIt: ADC模块中断源,可以是下面值的组合
*            @arg ADC_IT_RDY
*            @arg ADC_IT_EOSMP
*            @arg ADC_IT_EOC
*            @arg ADC_IT_EOS
*            @arg ADC_IT_OVR
*            @arg ADC_IT_JEOC
*            @arg ADC_IT_AWD1
*            @arg ADC_IT_AWD2
*            @arg ADC_IT_AWD3
*            @arg ADC_IT_JQOVF
* @retval 无
*/
void drv_adc_it_disable( AdcType* pAdc, UINT32 AdcIt )
{ 
	pAdc->IER.all &= (UINT32)~AdcIt;
}

/**
* @brief  读状态标志
* @param  pAdc: ADC1~ADC3
* @param  AdcFlag: 要检查的标志，可以是下面值中的一个
  *     @arg ADC_FLAG_RDY: ADC Ready (ADRDY) flag 
  *     @arg ADC_FLAG_EOSMP: ADC End of Sampling flag 
  *     @arg ADC_FLAG_EOC: ADC End of Regular Conversion flag 
  *     @arg ADC_FLAG_EOS: ADC End of Regular sequence of Conversions flag 
  *     @arg ADC_FLAG_OVR: ADC overrun flag 
  *     @arg ADC_FLAG_JEOC: ADC End of Injected Conversion flag 
  *     @arg ADC_FLAG_JEOS: ADC End of Injected sequence of Conversions flag 
  *     @arg ADC_FLAG_AWD1: ADC Analog watchdog 1 flag 
  *     @arg ADC_FLAG_AWD2: ADC Analog watchdog 2 flag 
  *     @arg ADC_FLAG_AWD3: ADC Analog watchdog 3 flag 
  *     @arg ADC_FLAG_JQOVF: ADC Injected Context Queue Overflow flag 
* @retval 标志状态：SET RESET
*/
FlagStatus drv_adc_get_flag_status( AdcType* pAdc, UINT32 AdcFlag )
{
	AdcIsrType l_Isr;
	
	l_Isr.all = pAdc->ISR.all;
	if(( l_Isr.all & AdcFlag ) != (UINT16)RESET )
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清状态标志
* @param  pAdc: ADC1~ADC3
* @param  AdcFlag: 要检查的标志，可以是下面值中的一个
  *     @arg ADC_FLAG_RDY: ADC Ready (ADRDY) flag 
  *     @arg ADC_FLAG_EOSMP: ADC End of Sampling flag 
  *     @arg ADC_FLAG_EOC: ADC End of Regular Conversion flag 
  *     @arg ADC_FLAG_EOS: ADC End of Regular sequence of Conversions flag 
  *     @arg ADC_FLAG_OVR: ADC overrun flag 
  *     @arg ADC_FLAG_JEOC: ADC End of Injected Conversion flag 
  *     @arg ADC_FLAG_JEOS: ADC End of Injected sequence of Conversions flag 
  *     @arg ADC_FLAG_AWD1: ADC Analog watchdog 1 flag 
  *     @arg ADC_FLAG_AWD2: ADC Analog watchdog 2 flag 
  *     @arg ADC_FLAG_AWD3: ADC Analog watchdog 3 flag 
  *     @arg ADC_FLAG_JQOVF: ADC Injected Context Queue Overflow flag 
* @retval 无
*/
void drv_adc_clear_flag_status( AdcType* pAdc, UINT32 AdcFlag )
{
	pAdc->ISR.all = AdcFlag;		//写1清0 写0无效
}

/**
* @brief  读中断状态
* @param  pAdc: ADC1~ADC3
* @param  ItFlag: 要检查的标志，可以是下面值中的一个
*            @arg ADC_IT_RDY
*            @arg ADC_IT_EOSMP
*            @arg ADC_IT_EOC
*            @arg ADC_IT_EOS
*            @arg ADC_IT_OVR
*            @arg ADC_IT_JEOC
*            @arg ADC_IT_AWD1
*            @arg ADC_IT_AWD2
*            @arg ADC_IT_AWD3
*            @arg ADC_IT_JQOVF
* @retval 无
*/
ITStatus drv_adc_get_it_status( AdcType* pAdc, UINT32 AdcIt )
{
	AdcIerType l_Ier;
	AdcIsrType l_Isr;
	ITStatus l_ItStatus = RESET, l_FlagStatus = RESET;
	
	l_Ier.all = pAdc->IER.all;		//读中断控制寄存器
	l_Isr.all = pAdc->ISR.all;		//读状态寄存器
	if(( l_Ier.all & AdcIt ) != (UINT32)RESET )
	{
		l_ItStatus = SET;			//中断打开
	}
	else
	{
		l_ItStatus = RESET;
	}
	if(( l_Isr.all & AdcIt ) != (UINT32)RESET )
	{
		l_FlagStatus = SET;			//状态位置起
	}
	else
	{
		l_FlagStatus = RESET;
	}
	
	if(( l_ItStatus != RESET ) && ( l_FlagStatus != RESET ))
	{
		return SET;					//该中断为SET状态
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清中断挂起标志
* @param  pAdc: ADC1~ADC3
* @param  ItFlag: 要清的标志，可以是下面值中的一个
*            @arg ADC_IT_RDY
*            @arg ADC_IT_EOSMP
*            @arg ADC_IT_EOC
*            @arg ADC_IT_EOS
*            @arg ADC_IT_OVR
*            @arg ADC_IT_JEOC
*            @arg ADC_IT_AWD1
*            @arg ADC_IT_AWD2
*            @arg ADC_IT_AWD3
*            @arg ADC_IT_JQOVF
* @retval 无
*/
void drv_adc_clear_it_pending_bit( AdcType* pAdc, UINT32 AdcIt )
{
	pAdc->ISR.all = AdcIt;		//写1清0 写0无效
}

