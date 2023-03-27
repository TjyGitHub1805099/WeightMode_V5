/**
*******************************************************************
* @file    drv_adc.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F303x ADC模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include "reg_stm32f303_adc.h"

/* ADC中断定义 */
#define ADC_IT_RDY           ((UINT32)0x0001)  /*!< ADC Ready (ADRDY) interrupt source */
#define ADC_IT_EOSMP         ((UINT32)0x0002)  /*!< ADC End of Sampling interrupt source */
#define ADC_IT_EOC           ((UINT32)0x0004)  /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_EOS           ((UINT32)0x0008)  /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IT_OVR           ((UINT32)0x0010)  /*!< ADC overrun interrupt source */
#define ADC_IT_JEOC          ((UINT32)0x0020)  /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IT_JEOS          ((UINT32)0x0040)  /*!< ADC End of Injected sequence of Conversions interrupt source */
#define ADC_IT_AWD1          ((UINT32)0x0080)  /*!< ADC Analog watchdog 1 interrupt source */
#define ADC_IT_AWD2          ((UINT32)0x0100)  /*!< ADC Analog watchdog 2 interrupt source */
#define ADC_IT_AWD3          ((UINT32)0x0200)  /*!< ADC Analog watchdog 3 interrupt source */
#define ADC_IT_JQOVF         ((UINT32)0x0400)  /*!< ADC Injected Context Queue Overflow interrupt source */
/* ADC标志位定义 */
#define ADC_FLAG_RDY         ((UINT32)0x0001)  /*!< ADC Ready (ADRDY) flag */
#define ADC_FLAG_EOSMP       ((UINT32)0x0002)  /*!< ADC End of Sampling flag */
#define ADC_FLAG_EOC         ((UINT32)0x0004)  /*!< ADC End of Regular Conversion flag */
#define ADC_FLAG_EOS         ((UINT32)0x0008)  /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_FLAG_OVR         ((UINT32)0x0010)  /*!< ADC overrun flag */
#define ADC_FLAG_JEOC        ((UINT32)0x0020)  /*!< ADC End of Injected Conversion flag */
#define ADC_FLAG_JEOS        ((UINT32)0x0040)  /*!< ADC End of Injected sequence of Conversions flag */
#define ADC_FLAG_AWD1        ((UINT32)0x0080)  /*!< ADC Analog watchdog 1 flag */
#define ADC_FLAG_AWD2        ((UINT32)0x0100)  /*!< ADC Analog watchdog 2 flag */
#define ADC_FLAG_AWD3        ((UINT32)0x0200)  /*!< ADC Analog watchdog 3 flag */
#define ADC_FLAG_JQOVF       ((UINT32)0x0400)  /*!< ADC Injected Context Queue Overflow flag */


/**  多重 ADC 模式选择*/
typedef enum AdcMultiModeType							
{
	MULTI_Independent_All = 0,                  /**< 所有 ADC 均独立,独立模式 */
	/**< 多重模式 */
	MULTI_Independent_Regular_Inject = 1,       /**< 规则同时 + 注入同时组合模式 */
	MULTI_Independent_Regular_Altern = 2,       /**< 规则同时 + 交替触发组合模式 */
	MULTI_Independent_Regular_Interleaved = 3,  /**< 规则交叉 + 注入同时组合模式 */
	MULTI_Independent_Inject_Simul = 5,      	/**< 仅注入同时模式式 */
	MULTI_Independent_Regular_Simul = 6,        /**< 仅规则同时模式 */
	MULTI_Independent_Interleaved = 7,          /**< 仅交替模式 */
	MULTI_Independent_Altern_Trigger = 9		/**< 仅交替触发模式 */	
}enumAdcMultiModeType;

/** ADC控制寄存器1 分辨率 */
typedef enum ResolutionType								
{
	RES_12 = 0,                               		/**< 12 位（15 ADCCLK周期）*/
    RES_10,                                 		/**< 10 位（13 ADCCLK周期）*/
	RES_8,                                  		/**< 8  位（11 ADCCLK周期）*/
	RES_6                                   		/**< 6  位（9  ADCCLK周期）*/
}enumResolutionType;

/** ADC 数据对齐定义 */
typedef enum AdcDataAlighType
{
	ADC_DATA_ALIGH_RIGHT = 0,
	ADC_DATA_ALIGH_LEFT
}enumAdcDataAlighType;

/** ADC控制寄存器2  规则通道的外部触发使能*/
typedef enum ExtenType				   					
{
    EXTEN_Disable=0,                   /**< 禁止触发检测 */
	EXTEN_Up,                          /**< 上升沿上的触发检测 */
	EXTEN_Down,                        /**< 下降沿上的触发检测 */
	EXTEN_Up_Down                      /**< 上升沿和下降沿上的触发检测 */	
}enumExtenType;

/** ADC时钟模式定义 */
typedef enum AdcClkModeType							
{
	ADC_ASYN_CLK_MODE =0,				/**< 异步时钟模式 */
	ADC_SYN_CLK_MODE_DIV1,				/**< 同步时钟模式，1分频 */
	ADC_SYN_CLK_MODE_DIV2,				/**< 同步时钟模式，2分频 */                                     
	ADC_SYN_CLK_MODE_DIV4				/**< 同步时钟模式，4分频 */                              
}enumAdcPresclarType;

/** ADC DMA采样模式定义 */
typedef enum AdcDmaModeType
{
	ADC_DMA_ONE_SHOT_MODE = 0,			/** DMA单触发模式 */
	ADC_DMA_CIRCULAR_MODE				/** DMA循环触发模式 */
}enumAdcDmaModeType;

/** ADC控制寄存器1 模拟看门狗通道选择位 */
typedef enum AnalogWatchDogChanelType					
{
	AWDCH_1 = 1,									/**< ADC模拟输入通道1 */
	AWDCH_2 ,										/**< ADC模拟输入通道2 */
	AWDCH_3 ,										/**< ADC模拟输入通道3 */
	AWDCH_4 ,										/**< ADC模拟输入通道4 */
	AWDCH_5 ,										/**< ADC模拟输入通道5 */
	AWDCH_6 ,										/**< ADC模拟输入通道6 */
	AWDCH_7 ,										/**< ADC模拟输入通道7 */
	AWDCH_8 ,										/**< ADC模拟输入通道8 */
	AWDCH_9 ,										/**< ADC模拟输入通道9 */
	AWDCH_10 ,										/**< ADC模拟输入通道10 */
	AWDCH_11 ,										/**< ADC模拟输入通道11 */
	AWDCH_12 ,										/**< ADC模拟输入通道12 */
	AWDCH_13 ,										/**< ADC模拟输入通道13 */
	AWDCH_14 ,										/**< ADC模拟输入通道14 */
	AWDCH_15 ,										/**< ADC模拟输入通道15 */
	AWDCH_16 ,										/**< ADC模拟输入通道16 */
	AWDCH_17 ,										/**< ADC模拟输入通道17 */
	AWDCH_18 										/**< ADC模拟输入通道18 */
}enumAnalogWatchDogChanelType;

/** ADC控制寄存器1 不连续采样模式通道计数 */
typedef enum DisContinusModeChanelCountType				
{
	DISCNUM_1 = 0,                           		/**< 1个通道 */
	DISCNUM_2,							   			/**< 2个通道 */
	DISCNUM_3,							   			/**< 3个通道 */
	DISCNUM_4,                             			/**< 4个通道 */
	DISCNUM_5,							   			/**< 5个通道 */
	DISCNUM_6,							   			/**< 6个通道 */
	DISCNUM_7,							   			/**< 7个通道 */
	DISCNUM_8,							   			/**< 8个通道 */
}enumDisContinusModeChanelCountType;

/** ADC控制寄存器2  为注入组选择外部事件 */
typedef enum JextselType								
{
	JEXTSEL_TIM1_CC4 =0,                   			/**< 定时器 1 CC4事件 */
	JEXTSEL_TIM1_TRGO,                     			/**< 定时器 1 TRGO 事件 */
	JEXTSEL_TIM2_CC4,                      			/**< 定时器 2 CC1 事件 */
	JEXTSEL_TIM2_TRGO,                     			/**< 定时器 2 TRGO 事件 */
	JEXTSEL_TIM3_CC2,                      			/**< 定时器 3 CC2 事件 */
	JEXTSEL_TIM3_CC4,                      			/**< 定时器 3 CC4 事件 */
	JEXTSEL_TIM4_CC1,                      			/**< 定时器 4 CC1 事件 */
	JEXTSEL_TIM4_CC2,                      			/**< 定时器 4 CC2 事件 */
	JEXTSEL_TIM4_CC3,                      			/**< 定时器 4 CC3 事件 */
	JEXTSEL_TIM4_TRGO,                     			/**< 定时器 4 TRGO 事件 */
	JEXTSEL_TIM5_CC4,                      			/**< 定时器 5 CC4 事件 */
	JEXTSEL_TIM5_TRGO,                     			/**< 定时器 5 TRGO 事件 */
	JEXTSEL_TIM8_CC2,                      			/**< 定时器 8 CC2 事件 */
	JEXTSEL_TIM8_CC3,                      			/**< 定时器 8 CC3 事件 */
	JEXTSEL_TIM8_CC4,                      			/**< 定时器 8 CC4 事件 */
	JEXTSEL_EXTI_15                        			/**< EXTI 线 15 */
}enumJextselType;

/** ADC控制寄存器2  注入通道的外部触发使能*/
typedef enum JextenType						   			
{
	JEXTEN_Disable=0,                      			/**<禁止触发检测 */
	JEXTEN_Up,                             			/**<上升沿上的触发检测 */
	JEXTEN_Down,                           			/**<下降沿上的触发检测 */
	JEXTEN_Up_Down,                        			/**<上升沿和下降沿上的触发检测 */
}enumJextenType;

/** ADC控制寄存器2  为规则组选择外部事件*/
typedef enum ExtselType									
{
    EXTSEL_TIM1_CC1 =0,            /**< 定时器 1 CC1 事件 */
	EXTSEL_TIM1_CC2,               /**< 定时器 1 CC2 事件 */
	EXTSEL_TIM1_CC3,               /**< 定时器 1 CC3 事件 */
	EXTSEL_TIM2_CC2,               /**< 定时器 2 CC2 事件 */
	EXTSEL_TIM2_CC3,               /**< 定时器 2 CC3 事件 */
	EXTSEL_TIM2_CC4,               /**< 定时器 2 CC4 事件 */
	EXTSEL_TIM2_TRGO,              /**< 定时器 2 TRGO 事件 */
	EXTSEL_TIM3_CC1,               /**< 定时器 3 CC1 事件 */
	EXTSEL_TIM3_TRGO,              /**< 定时器 3 TRGO 事件 */
	EXTSEL_TIM4_CC4,               /**< 定时器 4 CC4 事件 */
	EXTSEL_TIM5_CC1,               /**< 定时器 5 CC1 事件 */
	EXTSEL_TIM5_CC2,               /**< 定时器 5 CC2 事件 */
	EXTSEL_TIM5_CC3,               /**< 定时器 5 CC3 事件 */
	EXTSEL_TIM8_CC1,               /**< 定时器 8 CC1 事件 */
	EXTSEL_TIM8_TRGO,              /**< 定时器 8 TRGO 事件 */
	EXTSEL_EXTI_11                 /**< EXTI 线 11 */	
}enumExtselType;

/** ADC采样周期 */
typedef enum SampleCycleType							
{
	Channel_Sampling_Clcle_1_5=0,  /**< 1.5  个周期 */
	Channel_Sampling_Clcle_2_5,    /**< 2.5  个周期 */
	Channel_Sampling_Clcle_4_5,    /**< 4.5  个周期 */
	Channel_Sampling_Clcle_7_5,    /**< 7.5  个周期 */
	Channel_Sampling_Clcle_19_5,              		/**< 19.5 个周期 */
	Channel_Sampling_Clcle_61_5,             		/**< 61.5 个周期 */
	Channel_Sampling_Clcle_181_5,             		/**< 181.5 个周期 */
	Channel_Sampling_Clcle_601_5              		/**< 601.5 个周期 */
}enumSampleCycleType;

/** 2 个采样阶段之间的延迟*/
typedef enum AdcSampleDelayType							
{
	DELAY_5 = 0,                                    /**<5 x TADCCLK*/
	DELAY_6,                                        /**<6 x TADCCLK*/
	DELAY_7,                                        /**<7 x TADCCLK*/
	DELAY_8,                                        /**<8 x TADCCLK*/
	DELAY_9,                                        /**<9 x TADCCLK*/
	DELAY_10,                                       /**<10 x TADCCLK*/
	DELAY_11,                                       /**<11 x TADCCLK*/
	DELAY_12,                                       /**<12 x TADCCLK*/
	DELAY_13,                                       /**<13 x TADCCLK*/
	DELAY_14,                                       /**<14 x TADCCLK*/
	DELAY_15,                                       /**<15 x TADCCLK*/
	DELAY_16,                                       /**<16 x TADCCLK*/
	DELAY_17,                                       /**<17 x TADCCLK*/
	DELAY_18,                                       /**<18 x TADCCLK*/
	DELAY_19,                                       /**<19 x TADCCLK*/
	DELAY_20                                        /**<20 x TADCCLK*/
}enumAdcSampleDelayType;


extern void drv_adc_deinit( AdcType* pAdc );
extern void drv_adc_init( AdcType* pAdc, UINT8 *pChannel, UINT8 *pQueue, UINT8 ChannelNumber );
extern void drv_adc_enable( AdcType* pAdc );
extern void drv_adc_disable( AdcType* pAdc );
extern void drv_adc_dma_enable( AdcType* pAdc );
extern void drv_adc_dma_disable( AdcType* pAdc );
extern UINT16 drv_adc_get_value( AdcType* pAdc );
extern void drv_adc_software_start( AdcType* pAdc );
extern void drv_adc_software_stop( AdcType* pAdc );
extern void drv_adc_it_enable( AdcType* pAdc, UINT32 AdcIt );
extern void drv_adc_it_disable( AdcType* pAdc, UINT32 AdcIt );
extern FlagStatus drv_adc_get_flag_status( AdcType* pAdc, UINT32 AdcFlag );
extern void drv_adc_clear_flag_status( AdcType* pAdc, UINT32 AdcFlag );
extern ITStatus drv_adc_get_it_status( AdcType* pAdc, UINT32 AdcIt );
extern void drv_adc_clear_it_pending_bit( AdcType* pAdc, UINT32 AdcIt );

#endif
