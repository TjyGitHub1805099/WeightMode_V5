/**
*******************************************************************
* @file    drv_dac.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x  DAC模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/


#include "drv_dac.h"

/**
* @brief  DAC复位
* @retval 无
*/
void drv_dac_deinit( void )
{
	drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_DACRST );
	drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_DACRST );
}

/**
* @brief  DAC初始化
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道 
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @param  TrigMode: 触发模式 见类型 enumDacTriggerType 
* @retval 无
*/
void drv_adc_init( DacType* pDac, enumDacChannelType Channel, enumDacTriggerType TrigMode )
{
	drv_dac_deinit( );
	if( Channel == DAC_Channel_1 )
	{
		pDac->CR.bit.EN1	= 0;				//禁止DAC
		pDac->CR.bit.TEN1	= 1;				//使能触发
		pDac->CR.bit.TSEL1	= (UINT16)TrigMode;	//选择触发模式
		pDac->CR.bit.WAVE1	= (UINT16)DAC_WaveGeneration_None;	//禁止波形生成
		pDac->CR.bit.BOFF1_OUTEN1 = (UINT16)DAC_BufferSwitch_Disable;	//通道1输出BUFFER禁止
	}
	else
	{
		pDac->CR.bit.EN2	= 0;
		pDac->CR.bit.TEN2	= 1;
		pDac->CR.bit.TSEL2	= (UINT16)TrigMode;
		pDac->CR.bit.WAVE2	= (UINT16)DAC_WaveGeneration_None;
		pDac->CR.bit.BOFF2_OUTEN2 = (UINT16)DAC_BufferSwitch_Disable;
	}
}

/**
* @brief  DAC使能
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @retval 无
*/
void drv_dac_enable( DacType* pDac, enumDacChannelType Channel )
{ 
	if( Channel == DAC_Channel_1 )
	{
		pDac->CR.bit.EN1 = 1;
	}
	else
	{
		pDac->CR.bit.EN2 = 1;
	}
}

/**
* @brief  DAC禁止
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @retval 无
*/
void drv_dac_disable( DacType* pDac, enumDacChannelType Channel )
{
	if( Channel == DAC_Channel_1 )
	{
		pDac->CR.bit.EN1 = 0;
	}
	else
	{
		pDac->CR.bit.EN2 = 0;
	}
}

/**
* @brief  软件触发单通道转换
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @retval 无
*/
void drv_dac_soft_trig_channel( DacType* pDac, enumDacChannelType Channel )
{ 
	if( Channel == DAC_Channel_1 )
	{
		pDac->SWTRIGR.bit.SWTRIG1 = 1;
	}
	else
	{
		pDac->SWTRIGR.bit.SWTRIG2 = 1;
	}
}

/**
* @brief  软件触发双通道转换
* @param  pDac: DAC1~DAC2
* @retval 无
*/
void drv_dac_soft_trig_dual_channel( DacType* pDac )
{
	pDac->SWTRIGR.all |= 0x00000003;
}

/**
* @brief  设置DAC通道1值.
* @param  pDac: DAC1~DAC2
* @param  Align: 对齐方式，可以是下面值的一种:
*            @arg DAC_Align_8b_R: 8位右对齐
*            @arg DAC_Align_12b_L: 12位左对齐
*            @arg DAC_Align_12b_R: 12位右对齐
* @param  Data: 要设置的数据.
* @retval 无
*/
void drv_dac_set_channel1_data( DacType* pDac, enumDacAlignType Align, UINT16 Data )
{
	switch ( Align )
	{
		case DAC_Align_12b_R: 
			pDac->DHR12R1.all = Data;
			break;
		case DAC_Align_12b_L:
			pDac->DHR12L1.all = Data;
			break;
		case DAC_Align_8b_R:
			pDac->DHR8R1.all = Data;
			break;
		default :
			break;
	}
}

/**
* @brief  设置DAC通道2值.
* @param  pDac: DAC1~DAC2
* @note   只用于 DAC1.
* @param  Align: 对齐方式，可以是下面值的一种:
*            @arg DAC_Align_8b_R: 8位右对齐
*            @arg DAC_Align_12b_L: 12位左对齐
*            @arg DAC_Align_12b_R: 12位右对齐
* @param  Data: 要设置的数据.
* @retval 无
*/
void drv_dac_set_channel2_data( DacType* pDac, enumDacAlignType Align, UINT16 Data )
{
	switch ( Align )
	{
		case DAC_Align_12b_R: 
			pDac->DHR12R2.all = Data;
			break;
		case DAC_Align_12b_L:
			pDac->DHR12L2.all = Data;
			break;
		case DAC_Align_8b_R:
			pDac->DHR8R2.all = Data;
			break;
		default :
			break;
	}
}

/**
* @brief  设置DAC两个通道值.
* @param  pDac: DAC1~DAC2
* @note   只用于 DAC1.
* @param  Align: 对齐方式，可以是下面值的一种:
*            @arg DAC_Align_8b_R: 8位右对齐
*            @arg DAC_Align_12b_L: 12位左对齐
*            @arg DAC_Align_12b_R: 12位右对齐
* @param  Data1: 要设置到通道1的数据.
* @param  Data2: 要设置到通道2的数据.
* @note   在双通道模式，要同时设置两个通道的值.
* @retval 无
*/
void drv_dac_set_dual_channel_data( DacType* pDac, enumDacAlignType Align, UINT16 Data1, UINT16 Data2 )
{
	switch ( Align )
	{
		case DAC_Align_12b_R: 
			pDac->DHR12R1.all = Data1;
			pDac->DHR12R2.all = Data2;
			break;
		case DAC_Align_12b_L:
			pDac->DHR12L1.all = Data1;
			pDac->DHR12L2.all = Data2;
			break;
		case DAC_Align_8b_R:
			pDac->DHR8R1.all = Data1;
			pDac->DHR8R2.all = Data2;
			break;
		default :
			break;
	}
}

/**
* @brief  使能指定通道的DMA请求
* @note	  DAC 通道1 (通道2) 映射到 DMA1 通道3 (通道4)
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @retval 无
*/
void drv_dac_dma_enable( DacType* pDac, enumDacChannelType Channel )
{
	if( Channel == DAC_Channel_1 )
	{
		pDac->CR.bit.DMAEN1 = 1;
	}
	else
	{
		pDac->CR.bit.DMAEN2 = 1;
	}
}

/**
* @brief  禁止指定通道的DMA请求
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @retval 无
*/
void drv_dac_dma_disable( DacType* pDac, enumDacChannelType Channel )
{
	if( Channel == DAC_Channel_1 )
	{
		pDac->CR.bit.DMAEN1 = 0;
	}
	else
	{
		pDac->CR.bit.DMAEN2 = 0;
	}
}

/**
* @brief  中断使能
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @param  ItFlag: DAC中断源.可以是下面值：
*            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
* @retval 无
*/
void drv_dac_it_enable( DacType* pDac, enumDacChannelType Channel, UINT32 ItFlag )
{
	if( Channel == DAC_Channel_2 )
	{
		ItFlag = ItFlag << 16;
	}
	pDac->CR.all |= ItFlag;
}

/**
* @brief  中断禁止
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @param  ItFlag: DAC中断源.可以是下面值：
*            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
* @retval 无
*/
void drv_dac_it_disable( DacType* pDac, enumDacChannelType Channel, UINT32 ItFlag )
{
	if( Channel == DAC_Channel_2 )
	{
		ItFlag = ItFlag << 16;
	}
	pDac->CR.all &= (UINT32)~ItFlag;
}

/**
* @brief  读状态标志
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @param  DacFlag: 标志位
*            @arg DAC_FLAG_DMAUDR
* @retval 无
*/
FlagStatus drv_dac_get_flag_status( DacType* pDac, enumDacChannelType Channel, UINT32 DacFlag )
{
	DacSrType l_Sr;
	
	l_Sr.all = pDac->SR.all;
	if( Channel == DAC_Channel_2 )
	{
		DacFlag = DacFlag << 16;
	}
	if(( l_Sr.all & DacFlag ) != (UINT32)RESET )
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
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @param  DacFlag: 要清除的标志，可以是下面的值：
*            @arg DAC_FLAG_DMAUDR: DMA underrun flag
* @retval 无
*/
void drv_dac_clear_flag_status( DacType* pDac, enumDacChannelType Channel, UINT32 DacFlag )
{
	if( Channel == DAC_Channel_2 )
	{
		DacFlag = DacFlag << 16;
	}
	pDac->SR.all = DacFlag;			//写1清0
}

/**
* @brief  读中断状态
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @param  ItFlag: DAC中断源.可以是下面值：
*            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
* @retval 无
*/
ITStatus drv_dac_get_it_status( DacType* pDac, enumDacChannelType Channel, UINT32 ItFlag )
{
	DacSrType l_Sr;
	DacCrType l_Cr;
	
	l_Sr.all = pDac->SR.all;
	l_Cr.all = pDac->CR.all;
	if( Channel == DAC_Channel_2 )
	{
		ItFlag = ItFlag << 16;
	}
	if((( l_Sr.all & ItFlag ) != (UINT32)RESET ) && (( l_Cr.all & ItFlag ) != (UINT32)RESET ))
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清中断挂起标志
* @param  pDac: DAC1~DAC2
* @param  Channel: 通道
*            @arg DAC_Channel_1: 通道1
*            @arg DAC_Channel_2: 通道2
* @param  ItFlag: DAC中断源.可以是下面值：
*            @arg DAC_IT_DMAUDR: DMA underrun interrupt mask
* @retval 无
*/
void drv_dac_clear_it_pending_bit( DacType* pDac, enumDacChannelType Channel, UINT32 ItFlag )
{
	if( Channel == DAC_Channel_2 )
	{
		ItFlag = ItFlag << 16;
	}
	pDac->SR.all = ItFlag;		//写1清0
}
