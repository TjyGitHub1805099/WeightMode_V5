/**
*******************************************************************
* @file    drv_timer.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F303x 定时器模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

#include "reg_stm32f303_timer.h"


/** TIM 时钟分频 */
typedef enum TimerCkdDivType
{
	TIM_CKD_DIV1 = 0,                     				/**< 不分频 */                   
	TIM_CKD_DIV2,                         				/**< 2分频  */ 
	TIM_CKD_DIV4,                        				/**< 4分频  */ 
}enumTimerCkdDivType;


/** 定时器边沿计数模式定义 */
typedef enum TimerEdgeCntModeType
{
	TIM_EDGE_CNT_MODE_UP				= 0,			/**< 边沿计数模式，向上计数 */
	TIM_EDGE_CNT_MODE_DOWN				= 1,			/**< 边沿计数模式，向下计数 */
	TIM_CENTER_CNT_DOWN_VALUE_ONLY		= 2,			/**< 中心对齐模式1,递增和递减计数交替,仅当递减计数时,配置为输出通道的输出比较中断标志才置1 */		
	TIM_CENTER_CNT_UP_VALUE_ONLY		= 4,			/**< 中心对齐模式2,递增和递减计数交替,仅当递增计数时,配置为输出通道的输出比较中断标志才置1 */
	TIM_CENTER_CNT_UP_DOWN_VALUE		= 6				/**< 中心对齐模式3,递增和递减计数交替,递减递减计数时,配置为输出通道的输出比较中断标志都置1 */
}enumTimerCntModeType;

/** 定时器中断源定义 */
typedef enum TimerItSourceType
{
	TIM_IT_NONE		= (UINT16)0x0000,					/**< 非定时器中断源 */
	TIM_IT_Update	= (UINT16)0x0001,					/**< 更新中断 */
	TIM_IT_CC1		= (UINT16)0x0002,					/**< 捕获比较通道1中断 */
	TIM_IT_CC2		= (UINT16)0x0004,					/**< 捕获比较通道2中断 */
	TIM_IT_CC3		= (UINT16)0x0008,					/**< 捕获比较通道3中断 */
	TIM_IT_CC4		= (UINT16)0x0010,					/**< 捕获比较通道4中断 */
	TIM_IT_COM		= (UINT16)0x0020,					/**< COM中断，TIM1,TIM8有效,其他定时器保留 */
	TIM_IT_Trigger	= (UINT16)0x0040,					/**< 触发中断 */
	TIM_IT_Break	= (UINT16)0x0080,					/**< 断路中断,TIM1,TIM8有效,其他定时器保留 */
	TIM_IT_ALL		= (UINT16)0x00FF					/**< 所有中断 */
}enumTimerItSourceType;

/** 定时器中断标志定义 */
typedef enum TimeFlagType
{
	TIM_FLAG_NONE		= (UINT16)0x0000,				/**< 非定时器中断标志 */
	TIM_FLAG_Update		= (UINT16)0x0001,				/**< 上溢中断标志 */
	TIM_FLAG_CC1		= (UINT16)0x0002,				/**< 捕获比较通道1中断标志 */
	TIM_FLAG_CC2		= (UINT16)0x0004,				/**< 捕获比较通道2中断标志 */
	TIM_FLAG_CC3		= (UINT16)0x0008,				/**< 捕获比较通道3中断标志 */
	TIM_FLAG_CC4		= (UINT16)0x0010,				/**< 捕获比较通道4中断标志 */
	TIM_FLAG_COM		= (UINT16)0x0020,				/**< COM中断标志 */
	TIM_FLAG_Trigger	= (UINT16)0x0040,				/**< 触发中断标志 */
	TIM_FLAG_Break		= (UINT16)0x0080,				/**< 断路中断标志 */
	TIM_FLAG_CC1OF		= (UINT16)0x0200,				/**< 捕获比较1重复捕获标志 */
	TIM_FLAG_CC2OF		= (UINT16)0x0400,				/**< 捕获比较2重复捕获标志 */
	TIM_FLAG_CC3OF		= (UINT16)0x0800,				/**< 捕获比较3重复捕获标志 */
	TIM_FLAG_CC4OF		= (UINT16)0x1000,				/**< 捕获比较4重复捕获标志 */
	TIM_FLAG_IT_ALL		= (UINT16)0x00FF,				/**< 全部中断标志有效 */
	TIM_FLAG_ALL		= (UINT16)0x1EFF				/**< 全部标志有效 */
}enumTimeFlagType;

/** 定时器输出捕获通道1方向 */
typedef enum TimerOC1DirectionType
{
	TIM_OC1_DIR_OUT = 0,								/**< 配置为输出 */
	TIM_OC1_DIR_IN_TI1,								/**< 配置为输入，映射到TI1上 */
	TIM_OC1_DIR_IN_TI2,								/**< 配置为输入，映射到TI2上 */
	TIM_OC1_DIR_IN_TRC									/**< 配置为输入，映射到TRC上 */
}enumTimerOC1DirectionType;

/** 定时器输出捕获通道2方向 */
typedef enum TimerOC2DirectionType
{
	TIM_OC2_DIR_OUT = 0,								/**< 配置为输出 */
	TIM_OC2_DIR_IN_TI2,								/**< 配置为输入，映射到TI2上 */
	TIM_OC2_DIR_IN_TI1,								/**< 配置为输入，映射到TI1上 */
	TIM_OC2_DIR_IN_TRC									/**< 配置为输入，映射到TRC上 */
}enumTimerOC2DirectionType;

/** 定时器输出捕获通道3方向 */
typedef enum TimerOC3DirectionType
{
	TIM_OC3_DIR_OUT = 0,								/**< 配置为输出 */
	TIM_OC3_DIR_IN_TI3,								/**< 配置为输入，映射到TI3上 */
	TIM_OC3_DIR_IN_TI4,								/**< 配置为输入，映射到TI4上 */
	TIM_OC3_DIR_IN_TRC									/**< 配置为输入，映射到TRC上 */
}enumTimerOC3DirectionType;

/** 定时器输出捕获通道4方向 */
typedef enum TimerOC4DirectionType
{
	TIM_OC4_DIR_OUT = 0,							/**< 配置为输出 */
	TIM_OC4_DIR_IN_TI4,								/**< 配置为输入，映射到TI4上 */
	TIM_OC4_DIR_IN_TI3,								/**< 配置为输入，映射到TI3上 */
	TIM_OC4_DIR_IN_TRC								/**< 配置为输入，映射到TRC上 */
}enumTimerOC4DirectionType;

/** 定时器输出通道模式定义 */
typedef enum TimerOCModeType
{
	TIM_OC_MODE_0 = 0,									/**< 冻结––输出比较寄存器 TIMx_CCR1 与计数器 TIMx_CNT 进行比较不会对输出造成任何影响 */
	TIM_OC_MODE_1,										/**< 将通道 1 设置为匹配时输出有效电平 */
	TIM_OC_MODE_2,										/**< 将通道 1 设置为匹配时输出无效电平 */
	TIM_OC_MODE_3,										/**< 翻转––TIMx_CNT=TIMx_CCR1 时，OC1REF 发生翻转 */
	TIM_OC_MODE_4,										/**< 强制变为无效电平––OC1REF 强制变为低电平 */
	TIM_OC_MODE_5,										/**< 强制变为有效电平––OC1REF 强制变为高电平 */
	TIM_OC_MODE_6,										/**< PWM 模式 1 */
	TIM_OC_MODE_7										/**< PWM 模式 2 */
}enumTimerOCModeType;

/** 定时器主模式触发输出选择定义 */
typedef enum TimerMasterTriggerSourceType
{
	TIM_TRGOSource_Reset	= 0,						/**< 复位（EGR中UG位）作触发输出TRGO */
	TIM_TRGOSource_Enable,								/**< 使能（EN）作触发输出TRGO */
	TIM_TRGOSource_Update,								/**< 更新事件作触发输出TRGO */
	TIM_TRGOSource_OC1,									/**< 比较脉冲，一但发生输入捕获或者比较匹配作触发输出TRGO */
	TIM_TRGOSource_OC1Ref,								/**< 比较，OC1REF信号作触发输出TRGO */
	TIM_TRGOSource_OC2Ref,								/**< 比较，OC2REF信号作触发输出TRGO */
	TIM_TRGOSource_OC3Ref,								/**< 比较，OC3REF信号作触发输出TRGO */
	TIM_TRGOSource_OC4Ref								/**< 比较，OC4REF信号作触发输出TRGO */
}enumTimerMasterTriggerSourceType;

/** 定时器从模式触发选择定义 */
typedef enum TimerSlaveTriggerSeletcionType
{
	TIM_TS_ITR0	= 0,									/**< 内部触发0 */
	TIM_TS_ITR1,										/**< 内部触发1 */
	TIM_TS_ITR2,										/**< 内部触发2 */
	TIM_TS_ITR3,										/**< 内部触发3 */
	TIM_TS_TI1F_ED,										/**< TI1边沿检测器 */
	TIM_TS_TI1FP1,										/**< 滤波后的定时器输入1(TI1FP1) */
	TIM_TS_TI2FP2,										/**< 滤波后的定时器输入2(TI1FP2) */
	TIM_TS_ETRF											/**< 外部触发输入 */
}enumTimerSlaveTriggerSeletcionType;

/** 定时器从模式定义 */
typedef enum TimerSlaveModeType
{
	TIM_SLAVE_MODE_DISALE = 0,							/**< 禁止从模式 */
	TIM_SLAVE_MODE_EQEP_1,								/**< 编码器模式1 */
	TIM_SLAVE_MODE_EQEP_2,								/**< 编码器模式2 */
	TIM_SLAVE_MODE_EQEP_3,								/**< 编码器模式3 */
	TIM_SLAVE_MODE_RESET,								/**< 复位模式 */
	TIM_SLAVE_MODE_GATED,								/**< 门控模式 */
	TIM_SLAVE_MODE_TRIGGER,								/**< 触发模式 */
	TIM_SLAVE_MODE_EXTCLK								/**< 外部时钟模式 */
}enumTimerSlaveModeType;

/** 定时器输出通道极性定义 */
typedef enum TimerOCPolarityType
{
	TIM_OC_POLARITY_SET = 0,							/**< 高电平有效 */
	TIM_OC_POLARITY_RESET							    /**< 低电平有效 */
}enumTimerOCPolarityType;

/** 定时器输出通道空闲状态定义 */
typedef enum TimerOCIdleStatusType
{
	TIM_OC_IDLE_STATUS_RESET = 0,						/**< 空闲状态为低电平*/
	TIM_OC_IDLE_STATUS_SET								/**< 空闲状态为高电平*/
}enumTimerOCIdleStatusType;

/** 定时器输入捕获通道定义 */
typedef enum TimerIcChannelType
{
	TIM_IC_CHANNEL_1 = 0,								/**< 定时器输入通道1 */
	TIM_IC_CHANNEL_2,									/**< 定时器输入通道2 */
	TIM_IC_CHANNEL_3,									/**< 定时器输入通道3 */
	TIM_IC_CHANNEL_4									/**< 定时器输入通道4 */
}enumTimerIcChannelType;

/** 定时器输入捕获极性定义 */
typedef enum TimerIcPolarityType
{
	TIM_IC_POLARITY_RISING = 0,							/**< 上升沿触发，P=0,N=0 */
	TIM_IC_POLARITY_FALLING,							/**< 下降沿触发，P=1,N=0 */
	TIM_IC_POLARITY_BOTHEDGE							/**< 上升沿和下降沿都触发，P=1,N=1 */
}enumTimerIcPolarityType;

/** 定时器输入捕获预分频器 */
typedef enum TimerIcPresclarType
{
	TIM_IC_PSC_DIV_1 = 0,								/**< 无预分频器，捕获输入每检测到一个边沿就执行捕获 */
	TIM_IC_PSC_DIV_2,									/**< 每发生2个事件便执行一次捕获 */
	TIM_IC_PSC_DIV_4,									/**< 每发生4个事件便执行一次捕获 */
	TIM_IC_PSC_DIV_8									/**< 每发生8个事件便执行一次捕获 */
}enumTimerIcPresclarType;

/** 定时器输入捕获x选择 */
typedef enum TimerIcSelectionType
{
	TIM_IC_SELECTION_1 = 1,								/**< 输入，ICx映射到TIx上 */
	TIM_IC_SELECTION_2,									/**< 输入，ICx映射到TIx +（-）上，如IC1映射到TI2,IC2映射到TI1,IC3映射到TI4,IC4映射到TI3 */
	TIM_IC_SELECTION_3									/**< 输入，映射到TRC上 */
}enumTimerIcSelectionType;

/** 输入捕获x滤波器 */
typedef enum TimerIcFilterType
{
	Filter_NO = 0,										/**< 无滤波器，按fDTS频率进行采样 */
	ICxF_CK_INT_N2,										/**< fSAMPLING=fCK_INT，N=2 */
	ICxF_CK_INT_N4,										/**< fSAMPLING=fCK_INT，N=4 */
	ICxF_CK_INT_N8,										/**< fSAMPLING=fCK_INT，N=8 */

	ICxF_DTS_2_N6,										/**< fSAMPLING=fDTS/2，N=6 */
	ICxF_DTS_2_N8,										/**< fSAMPLING=fDTS/2，N=8 */
	ICxF_DTS_4_N6,										/**< fSAMPLING=fDTS/4，N=6 */
	ICxF_DTS_4_N8,										/**< fSAMPLING=fDTS/4，N=8 */
	ICxF_DTS_8_N6,										/**< fSAMPLING=fDTS/8，N=6 */
	ICxF_DTS_8_N8,										/**< fSAMPLING=fDTS/8，N=8  */
	ICxF_DTS_16_N5,										/**< fSAMPLING=fDTS/16，N=5 */
	ICxF_DTS_16_N6,										/**< fSAMPLING=fDTS/16，N=6 */
	ICxF_DTS_16_N8,										/**< fSAMPLING=fDTS/16，N=8 */

	ICxF_DTS_32_N5,										/**< fSAMPLING=fDTS/32，N=5 */
	ICxF_DTS_32_N6,										/**< fSAMPLING=fDTS/32，N=6 */
	ICxF_DTS_32_N8										/**< fSAMPLING=fDTS/32，N=8 */
}enumTimerIcFilterType;



extern void drv_timer_deinit( TimerType *pTimer );
extern void drv_timer_base_init( TimerType *pTimer, UINT32 TimeClk, UINT32 TimePeriod, enumTimerCntModeType enumTimeCntMode );
extern void drv_timer_set_counter_mode( TimerType *pTimer, enumTimerCntModeType CounterMode );
//extern void drv_timer_set_counter( TimerType *pTimer, UINT32 Counter );


/**
* @brief  设置定时器计数值
* @param  pTimer: 定时器 TIM1~TIM14
* @param  Counter: 要设置的定时器值
* @retval 无
*/
__INLINE void drv_timer_set_counter( TimerType *pTimer, UINT32 Counter )
{
    pTimer->CNT.all = Counter;
}

extern UINT32 drv_timer_get_counter( TimerType *pTimer );
extern void drv_timer_set_arr( TimerType *pTimer, UINT32 Arr );
extern void drv_timer_set_psc( TimerType *pTimer, UINT16 Psc );
extern void drv_timer_auto_reload_enable( TimerType *pTimer );
extern void drv_timer_auto_reload_disable( TimerType *pTimer );
extern void drv_timer_update_enable( TimerType *pTimer );
extern void drv_timer_update_disable( TimerType *pTimer );
extern void div_timer_set_div( TimerType *pTimer, UINT16 Ckd );
extern void drv_timer_enable( TimerType *pTimer );
extern void drv_timer_disable( TimerType *pTimer );

extern void drv_timer_oc1_init( TimerType *pTimer, enumTimerOCModeType TimerOCMode, enumTimerOCPolarityType TimerOCPolarity, enumTimerOCIdleStatusType TimerOCIdleStatus );
extern void drv_timer_oc1n_init( TimerType *pTimer, enumTimerOCModeType TimerOCNMode, enumTimerOCPolarityType TimerOCNPolarity, enumTimerOCIdleStatusType TimerOCNIdleStatus );
extern void drv_timer_oc2_init( TimerType *pTimer, enumTimerOCModeType TimerOCMode, enumTimerOCPolarityType TimerOCPolarity, enumTimerOCIdleStatusType TimerOCIdleStatus );
extern void drv_timer_oc2n_init( TimerType *pTimer, enumTimerOCModeType TimerOCNMode, enumTimerOCPolarityType TimerOCNPolarity, enumTimerOCIdleStatusType TimerOCNIdleStatus );
extern void drv_timer_oc3_init( TimerType *pTimer, enumTimerOCModeType TimerOCMode, enumTimerOCPolarityType TimerOCPolarity, enumTimerOCIdleStatusType TimerOCIdleStatus );
extern void drv_timer_oc3n_init( TimerType *pTimer, enumTimerOCModeType TimerOCNMode, enumTimerOCPolarityType TimerOCNPolarity, enumTimerOCIdleStatusType TimerOCNIdleStatus );
extern void drv_timer_oc4_init( TimerType *pTimer, enumTimerOCModeType TimerOCMode, enumTimerOCPolarityType TimerOCPolarity, enumTimerOCIdleStatusType TimerOCIdleStatus );
extern void drv_timer_oc4n_init( TimerType *pTimer, enumTimerOCModeType TimerOCNMode, enumTimerOCPolarityType TimerOCNPolarity );

extern void drv_timer_ccx1_enable( TimerType* pTimer );
extern void drv_timer_ccx1_disable( TimerType* pTimer );
extern void drv_timer_ccx2_enable( TimerType* pTimer );
extern void drv_timer_ccx2_disable( TimerType* pTimer );
extern void drv_timer_ccx3_enable( TimerType* pTimer );
extern void drv_timer_ccx3_disable( TimerType* pTimer );
extern void drv_timer_ccx4_enable( TimerType* pTimer );
extern void drv_timer_ccx4_disable( TimerType* pTimer );

extern void drv_timer_ccx1n_enable( TimerType* pTimer );
extern void drv_timer_ccx1n_disable( TimerType* pTimer );
extern void drv_timer_ccx2n_enable( TimerType* pTimer );
extern void drv_timer_ccx2n_disable( TimerType* pTimer );
extern void drv_timer_ccx3n_enable( TimerType* pTimer );
extern void drv_timer_ccx3n_disable( TimerType* pTimer );

extern void drv_timer_pwm_output_enable( TimerType *pTimer );
extern void drv_timer_pwm_output_disable( TimerType *pTimer );

//extern void drv_timer_set_compara1( TimerType *pTimer, UINT32 Compara1 );
extern void drv_timer_set_compara2( TimerType *pTimer, UINT32 Compara2 );
extern void drv_timer_set_compara3( TimerType *pTimer, UINT32 Compara3 );
extern void drv_timer_set_compara4( TimerType *pTimer, UINT32 Compara4 );


/**
* @brief  设置定时器通道1捕获比较值
* @param  pTimer: 定时器 TIM1~TIM14
* @param  Compara1: 捕获比较值
* @retval 无
*/
__INLINE void drv_timer_set_compara1( TimerType *pTimer, UINT32 Compara1 )
{
    pTimer->CCR1 = Compara1;
}

extern UINT32 drv_timer_get_compara1( TimerType *pTimer );
extern UINT32 drv_timer_get_compara2( TimerType *pTimer );
extern UINT32 drv_timer_get_compara3( TimerType *pTimer );
extern UINT32 drv_timer_get_compara4( TimerType *pTimer );

extern void drv_timer_set_oc1_pwm1( TimerType* pTimer );
extern void drv_timer_set_oc2_pwm1( TimerType* pTimer );
extern void drv_timer_set_oc3_pwm1( TimerType* pTimer );
extern void drv_timer_set_oc4_pwm1( TimerType* pTimer );

__INLINE void drv_timer_forced_oc1_inactive( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC1M = 4;
}

/**
* @brief  强制定时器输出1波形为有效电平(高电平).
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
__INLINE void drv_timer_forced_oc1_active( TimerType* pTimer )
{
    pTimer->CCMR1.bit_o.OC1M = 5;
}

__INLINE void drv_timer_set_oc1_toggle( TimerType* pTimer )
{
    pTimer->CCMR1.bit_o.OC1M = 3;
}


//extern void drv_timer_forced_oc1_active( TimerType* pTimer );
//extern void drv_timer_forced_oc1_inactive( TimerType* pTimer );
extern void drv_timer_forced_oc2_active( TimerType* pTimer );
extern void drv_timer_forced_oc2_inactive( TimerType* pTimer );
extern void drv_timer_forced_oc3_active( TimerType* pTimer );
extern void drv_timer_forced_oc3_inactive( TimerType* pTimer );
extern void drv_timer_forced_oc4_active( TimerType* pTimer );
extern void drv_timer_forced_oc4_inactive( TimerType* pTimer );

extern void drv_timer_ccr1_preload_enable( TimerType* pTimer );
extern void drv_timer_ccr1_preload_disable( TimerType* pTimer );
extern void drv_timer_ccr2_preload_enable( TimerType* pTimer );
extern void drv_timer_ccr2_preload_disable( TimerType* pTimer );
extern void drv_timer_ccr3_preload_enable( TimerType* pTimer );
extern void drv_timer_ccr3_preload_disable( TimerType* pTimer );
extern void drv_timer_ccr4_preload_enable( TimerType* pTimer );
extern void drv_timer_ccr4_preload_disable( TimerType* pTimer );

extern void drv_timer_set_oc1_polarity_high( TimerType* pTimer );
extern void drv_timer_set_oc1_polarity_low( TimerType* pTimer );
extern void drv_timer_set_oc1n_polarity_high( TimerType* pTimer );
extern void drv_timer_set_oc1n_polarity_low( TimerType* pTimer );
extern void drv_timer_set_oc2_polarity_high( TimerType* pTimer );
extern void drv_timer_set_oc2_polarity_low( TimerType* pTimer );
extern void drv_timer_set_oc2n_polarity_high( TimerType* pTimer );
extern void drv_timer_set_oc2n_polarity_low( TimerType* pTimer );
extern void drv_timer_set_oc3_polarity_high( TimerType* pTimer );
extern void drv_timer_set_oc3_polarity_low( TimerType* pTimer );
extern void drv_timer_set_oc3n_polarity_high( TimerType* pTimer );
extern void drv_timer_set_oc3n_polarity_low( TimerType* pTimer );
extern void drv_timer_set_oc4_polarity_high( TimerType* pTimer );
extern void drv_timer_set_oc4_polarity_low( TimerType* pTimer );

extern void drv_timer_ic1_init( TimerType *pTimer, enumTimerIcPolarityType TimerIcPolarity, enumTimerIcPresclarType TimerIcPresclar, 
								enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter );
extern void drv_timer_ic2_init( TimerType *pTimer, enumTimerIcPolarityType TimerIcPolarity, enumTimerIcPresclarType TimerIcPresclar, 
								enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter );
extern void drv_timer_ic3_init( TimerType *pTimer, enumTimerIcPolarityType TimerIcPolarity, enumTimerIcPresclarType TimerIcPresclar, 
								enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter );
extern void drv_timer_ic4_init( TimerType *pTimer, enumTimerIcPolarityType TimerIcPolarity, enumTimerIcPresclarType TimerIcPresclar, 
								enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter );

extern void drv_timer_ic1_enable( TimerType* pTimer );
extern void drv_timer_ic1_disable( TimerType* pTimer );
extern void drv_timer_ic2_enable( TimerType* pTimer );
extern void drv_timer_ic2_disable( TimerType* pTimer );
extern void drv_timer_ic3_enable( TimerType* pTimer );
extern void drv_timer_ic3_disable( TimerType* pTimer );
extern void drv_timer_ic4_enable( TimerType* pTimer );
extern void drv_timer_ic4_disable( TimerType* pTimer );

extern void drv_timer_set_deadtime( TimerType* pTimer, UINT16 DeadTime );
extern void drv_timer_set_run_off_inactive( TimerType* pTimer );
extern void drv_timer_it_enable( TimerType *pTimer, UINT16 TimerIt );
extern void drv_timer_it_disable( TimerType *pTimer, UINT16 TimerIt );

extern FlagStatus drv_timer_get_flag_status( TimerType *pTimer, UINT16 TimerFlag );
extern void drv_timer_clear_flag_status( TimerType *pTimer, UINT16 TimerFlag );
extern ITStatus drv_timer_get_it_status( TimerType *pTimer, UINT16 TimerIt );
extern void drv_timer_clear_it_pending_bit( TimerType *pTimer, UINT16 TimerIt );

extern void drv_timer_set_ic1_psc( TimerType* pTimer, UINT16 IcPsc );
extern void drv_timer_set_ic2_psc( TimerType* pTimer, UINT16 IcPsc );
extern void drv_timer_set_ic3_psc( TimerType* pTimer, UINT16 IcPsc );
extern void drv_timer_set_ic4_psc( TimerType* pTimer, UINT16 IcPsc );

extern void drv_timer_select_input_trigger( TimerType* pTimer, enumTimerSlaveTriggerSeletcionType InTrigger );
extern void drv_timer_select_output_trigger( TimerType* pTimer, enumTimerMasterTriggerSourceType OutTrigger );
extern void drv_timer_select_slave_mode( TimerType *pTimer, enumTimerSlaveModeType SlaveMode );
extern void drv_timer_slave_mode_enable( TimerType* pTimer );
extern void drv_timer_slave_mode_disable( TimerType* pTimer );
extern void drv_timer_set_etr( TimerType* pTimer, UINT16 EtrPsc, UINT16 EtrPolarity, UINT16 EtrFilter );
extern void drv_timer_encoder_init( TimerType* pTimer, UINT16 EncoderMode, UINT16 Ic1Polarity, UINT16 Ic2Polarity );

extern void drv_timer_set_ic1_input( TimerType* pTimer, UINT16 IcPolarity, enumTimerIcFilterType IcFilter );
extern void drv_timer_set_ic2_input( TimerType* pTimer, UINT16 IcPolarity, enumTimerIcFilterType IcFilter );
extern void drv_timer_set_ic3_input( TimerType* pTimer, UINT16 IcPolarity, enumTimerIcFilterType IcFilter );
extern void drv_timer_set_ic4_input( TimerType* pTimer, UINT16 IcPolarity, enumTimerIcFilterType IcFilter );
extern void drv_timer_pwm_ic_init( TimerType *pTimer, enumTimerIcChannelType TimerIcChannel, enumTimerIcPolarityType TimerIcPolarity, 
									enumTimerIcPresclarType TimerIcPresclar, enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter );
extern void drv_timer_set_filter_frequency( TimerType *pTimer, UINT32 FilterDiv );




#endif
