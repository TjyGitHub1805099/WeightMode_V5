/*******************************************************************
* @file    drv_dac.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x   DAC模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_DAC_H__
#define __DRV_DAC_H__


#include "drv_rcc.h"
#include "reg_stm32f303_dac.h"


#define DAC_IT_DMAUDR                      ((UINT32)0x00002000)  
#define DAC_FLAG_DMAUDR                    ((UINT32)0x00002000) 


/** DAC通道定义 */
typedef enum DacChannelType
{
	DAC_Channel_1 = 0,
	DAC_Channel_2
}enumDacChannelType;

/** DAC输出BUFFER使能定义 */
typedef enum DacOutputBufferType
{
	DAC_BufferSwitch_Disable = 0,
	DAC_BufferSwitch_Enable
}enumDacOutputBufferType;

/** DAC生成波选择定义 */
typedef enum DacWaveGenerationType
{
	DAC_WaveGeneration_None = 0,
	DAC_WaveGeneration_Noise,
	DAC_WaveGeneration_Triangle
}enumDacWaveGenerationType;

/** DAC触发选择定义 */
typedef enum DacTriggerType
{
	DAC_Trigger_T6_TRGO = 0,
	DAC_Trigger_T3_8_TRGO,
	DAC_Trigger_T7_TRGO,
	DAC_Trigger_T15_TRGO,
	DAC_Trigger_T2_TRGO,
	DAC_Trigger_T4_TRGO,
	DAC_Trigger_Ext_IT9,
	DAC_Trigger_Software
}enumDacTriggerType;

/** DAC字节对齐定义 */
typedef enum DacAlignType
{
	DAC_Align_12b_R = 0,
	DAC_Align_12b_L,
	DAC_Align_8b_R
}enumDacAlignType;


extern void drv_dac_deinit( void );
extern void drv_adc_init( DacType* pDac, enumDacChannelType Channel, enumDacTriggerType TrigMode );
extern void drv_dac_enable( DacType* pDac, enumDacChannelType Channel );
extern void drv_dac_disable( DacType* pDac, enumDacChannelType Channel );
extern void drv_dac_soft_trig_channel( DacType* pDac, enumDacChannelType Channel );
extern void drv_dac_soft_trig_dual_channel( DacType* pDac );
extern void drv_dac_set_channel1_data( DacType* pDac, enumDacAlignType Align, UINT16 Data );
extern void drv_dac_set_channel2_data( DacType* pDac, enumDacAlignType Align, UINT16 Data );
extern void drv_dac_set_dual_channel_data( DacType* pDac, enumDacAlignType Align, UINT16 Data1, UINT16 Data2 );
extern void drv_dac_dma_enable( DacType* pDac, enumDacChannelType Channel );
extern void drv_dac_dma_disable( DacType* pDac, enumDacChannelType Channel );
extern void drv_dac_it_enable( DacType* pDac, enumDacChannelType Channel, UINT32 ItFlag );
extern void drv_dac_it_disable( DacType* pDac, enumDacChannelType Channel, UINT32 ItFlag );
extern FlagStatus drv_dac_get_flag_status( DacType* pDac, enumDacChannelType Channel, UINT32 DacFlag );
extern void drv_dac_clear_flag_status( DacType* pDac, enumDacChannelType Channel, UINT32 DacFlag );
extern ITStatus drv_dac_get_it_status( DacType* pDac, enumDacChannelType Channel, UINT32 ItFlag );
extern void drv_dac_clear_it_pending_bit( DacType* pDac, enumDacChannelType Channel, UINT32 ItFlag );


#endif
