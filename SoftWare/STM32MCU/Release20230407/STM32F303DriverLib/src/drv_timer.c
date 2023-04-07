/**
*******************************************************************
* @file    drv_timer.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x定时器模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#include "drv_rcc.h"
#include "drv_timer.h"

/**
* @brief  复位定时器外设寄存器为默认值.
* @param  pTimer: 要操作的定时器外设，可以是 TIM1 ~ TIM14.
* @retval 无
*/
void drv_timer_deinit( TimerType *pTimer )
{
	if( pTimer == TIM1 )
	{
		drv_rcc_apb2_periph_reset_enable( RCC_APB2RSTR_TIM1RST );
		drv_rcc_apb2_periph_reset_disable( RCC_APB2RSTR_TIM1RST );
	}
	else if( pTimer == TIM2 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_TIM2RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_TIM2RST );
	}
	else if( pTimer == TIM3 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_TIM3RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_TIM3RST );
	}
	else if( pTimer == TIM4 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_TIM4RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_TIM4RST );
	}
	else if( pTimer == TIM6 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_TIM6RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_TIM6RST );
	}
	else if( pTimer == TIM7 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_TIM7RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_TIM7RST );
	}
	else if( pTimer == TIM8 )
	{
		drv_rcc_apb2_periph_reset_enable( RCC_APB2RSTR_TIM8RST );
		drv_rcc_apb2_periph_reset_disable( RCC_APB2RSTR_TIM8RST );
	}
	else if( pTimer == TIM15 )
	{
		drv_rcc_apb2_periph_reset_enable( RCC_APB2RSTR_TIM15RST );
		drv_rcc_apb2_periph_reset_disable( RCC_APB2RSTR_TIM15RST );
	}
	else if( pTimer == TIM16 )
	{
		drv_rcc_apb2_periph_reset_enable( RCC_APB2RSTR_TIM16RST );
		drv_rcc_apb2_periph_reset_disable( RCC_APB2RSTR_TIM16RST );
	}
	else 
	{
		if( pTimer == TIM17 )
		{
			drv_rcc_apb2_periph_reset_enable( RCC_APB2RSTR_TIM17RST );
			drv_rcc_apb2_periph_reset_disable( RCC_APB2RSTR_TIM17RST );
		}
	}
}


/**
* @brief  定时器基本功能初始化
* @param  pTimer: 定时器 TIM1~TIM14
* @param  TimeClk: 定时器计数时钟频率，最低5000Hz，等于0时为不分频
* @param  TimePeriod: 定时器周期
* @param  TimeCntMode: 定时器计数模式，见类型 enumTimeCntModeType
* @retval 无
*
*/
void drv_timer_base_init( TimerType *pTimer, UINT32 TimeClk, UINT32 TimePeriod, enumTimerCntModeType TimeCntMode )
{
	UINT32 l_timer_clk_freq;
	
	if( TimeClk == 0 )
	{
		pTimer->PSC	= 0;		//定时器不分频
	}
	else
	{
		if (( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM15 ) || ( pTimer == TIM16 ) || ( pTimer == TIM17 ))
		{
			l_timer_clk_freq = g_ClockFrequency.Apb2TimerClkFreq;
		}
		else
		{
			l_timer_clk_freq = g_ClockFrequency.Apb1TimerClkFreq;
		}
		pTimer->PSC	= l_timer_clk_freq / TimeClk - 1;		//分频系数
	}

	// 定时器基本参数配置 
    if( pTimer == TIM2 )
    {
	    pTimer->ARR = TimePeriod;						    //重载值
    }
    else
    {
	    pTimer->ARR = (UINT16)TimePeriod;				    //重载值
    }

	pTimer->CR1.bit.CKD = (UINT16)TIM_CKD_DIV1;				//滤波分频
	pTimer->CR1.bit.DIR = (UINT16)TimeCntMode;				//计数模式
	pTimer->SR.all = 0x0000;								//清状态寄存器所有标志位 
	pTimer->CR1.bit.CEN = 0;								//不允许计数 
}

/**
* @brief  设置定时器计数模式.
* @param  pTimer: 定时器，可以是TIM1~5，TIM8.
* @param  CounterMode: 计数模式，见类型 enumTimerCntModeType
* @retval 无
*/
void drv_timer_set_counter_mode( TimerType *pTimer, enumTimerCntModeType CounterMode )
{
	pTimer->CR1.bit.DIR = (UINT16)CounterMode;
}
//
///**
//* @brief  设置定时器计数值
//* @param  pTimer: 定时器 TIM1~TIM14
//* @param  Counter: 要设置的定时器值
//* @retval 无
//*/
//void drv_timer_set_counter( TimerType *pTimer, UINT32 Counter )
//{
//	pTimer->CNT.all = Counter;
//}

/**
* @brief  获取定时器计数值
* @param  pTimer: 定时器 TIM1~TIM14
* @retval 计数器值
*/

UINT32 drv_timer_get_counter( TimerType *pTimer )
{
    TimerCntType l_Cnt;

    l_Cnt.all = pTimer->CNT.all;
    if( pTimer != TIM2 )
    {
        return ((UINT32)(l_Cnt.all));
    }
    else
    {
        return ((UINT32)(l_Cnt.all & 0x7FFFFFFF));
    }
}

/**
* @brief  设置定时器自动装载值
* @param  pTimer: 定时器 TIM1~TIM14
* @param  Period: 自动装载值
* @retval 无
*/
void drv_timer_set_arr( TimerType *pTimer, UINT32 Arr )
{
	if( pTimer == TIM2 )
	{
		pTimer->ARR	= Arr;
	}
	else
	{
		pTimer->ARR = Arr & 0xFFFF;
	}
}

/**
* @brief  设置定时器预分频系数
* @param  pTimer: 定时器 TIM1~TIM14
* @param  Presc: 分频系数理论最大为65535，TimeClock = SysClock / Psc + 1
* @retval 无
*/
void drv_timer_set_psc( TimerType *pTimer, UINT16 Psc )
{
	pTimer->PSC = Psc;
}

/**
* @brief  使能定时器自动重装模式
* @param  pTimer: 定时器 TIM1~TIM14
* @retval 无
*/
void drv_timer_auto_reload_enable( TimerType *pTimer )
{
	pTimer->CR1.bit.ARPE = 1;
}

/**
* @brief  禁止定时器自动重装模式
* @param  pTimer: 定时器 TIM1~TIM14
* @retval 无
*/
void drv_timer_auto_reload_disable( TimerType *pTimer )
{
	pTimer->CR1.bit.ARPE = 0;
}

/**
* @brief  使能定时器更新
* @param  pTimer: 定时器 TIM1~TIM14
* @retval 无
*/
void drv_timer_update_enable( TimerType *pTimer )
{
	pTimer->CR1.bit.UDIS = 0;
}

/**
* @brief  禁止定时器更新
* @param  pTimer: 定时器 TIM1~TIM14
* @retval 无
*/
void drv_timer_update_disable( TimerType *pTimer )
{
	pTimer->CR1.bit.UDIS = 1;
}

/**
* @brief  设置定时器时钟分频值(定时器时钟与滤波器采样时钟比值).
* @param  pTimer: 可以是TIM1~5和TIM8~14.
* @param  Ckd: 分频值，0表示不分频，1表示二分频，2表示四分频，3无效.
* @retval 无
*/
void div_timer_set_div( TimerType *pTimer, UINT16 Ckd )
{
	pTimer->CR1.bit.CKD = Ckd;
}

/**
* @brief  使能定时器.
* @param  pTimer: 定时器 TIM1~TIM14
* @retval 无
*/
void drv_timer_enable( TimerType *pTimer )
{
	pTimer->CR1.bit.CEN = 1;
}

/**
* @brief  失能定时器.
* @param  pTimer: 定时器 TIM1~TIM14
* @retval 无
*/
void drv_timer_disable( TimerType *pTimer )
{
	pTimer->CR1.bit.CEN = 0;
}

/**
* @brief  定时器输出通道1初始化
* @param  pTimer: 定时器  做PWM输出使用高级定时器：TIM1 TIM8 TIM20
* @param  TimerOCMode: 输出通道输出模式，见类型 enumTimerOCModeType
* @param  TimerOCPolarity: 输出通道有效极性，见类型 enumTimerOCPolarityType
* @param  TimerOCIdleStatus: 输出通道空闲时状态，类型 enumTimerOCIdleStatusType
* @retval 无
*/
void drv_timer_oc1_init( TimerType *pTimer, enumTimerOCModeType TimerOCMode, enumTimerOCPolarityType TimerOCPolarity, enumTimerOCIdleStatusType TimerOCIdleStatus )
{
	if( ( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM20 ))
	{
		pTimer->BDTR.bit.MOE = 1;					//主输出使能，高级定时器必须配置 
	}
	pTimer->CCMR1.bit_o.OC1PE = 0;					//预装载禁止
	pTimer->CCMR1.bit_o.CC1S = 0;					//配置为输出						
	pTimer->CCMR1.bit_o.OC1M = TimerOCMode;			//输出模式
	pTimer->CR2.bit.OIS1 = TimerOCIdleStatus;		//输出空闲状态
	pTimer->CCER.bit.CC1P = TimerOCPolarity;		//有效极性
	pTimer->CCR1 = 0xFFFF;							//输出比较值
}

/**
* @brief  定时器输出通道1互补通道初始化
* @param  pTimer: 定时器 做PWM输出使用高级定时器：TIM1 TIM8 TIM20
* @param  TimerOCMode: 输出通道输出模式，见类型 enumTimerOCModeType
* @param  TimerOCNPolarity: 互补输出通道有效极性，见类型 enumTimerOCPolarityType
* @param  TimerOCNIdleStatus: 互补通道输出时状态，类型 enumTimerOCIdleStatusType
* @retval 无
*/
void drv_timer_oc1n_init( TimerType *pTimer, enumTimerOCModeType TimerOCNMode, enumTimerOCPolarityType TimerOCNPolarity, enumTimerOCIdleStatusType TimerOCNIdleStatus )
{
	if( ( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM20 ))
	{
		pTimer->BDTR.bit.MOE = 1;					//主输出使能，高级定时器必须配置
	}
	pTimer->CCMR1.bit_o.OC1PE = 0;					//预装载禁止
	pTimer->CCMR1.bit_o.CC1S = 0;					//配置为输出						
	pTimer->CCMR1.bit_o.OC1M = TimerOCNMode;		//输出模式
	pTimer->CR2.bit.OIS1N = TimerOCNIdleStatus;		//输出空闲状态
	pTimer->CCER.bit.CC1NP = TimerOCNPolarity;		//有效极性
	pTimer->CCR1 = 0xFFFF;							//输出比较值
}

/**
* @brief  定时器输出通道2初始化
* @param  pTimer: 定时器  做PWM输出使用高级定时器：TIM1 TIM8 TIM20
* @param  TimerOCMode: 输出通道输出模式，见类型 enumTimerOCModeType
* @param  TimerOCPolarity: 输出通道有效极性，见类型 enumTimerOCPolarityType
* @param  TimerOCIdleStatus: 输出通道空闲时状态，类型 enumTimerOCIdleStatusType
* @retval 无
*/
void drv_timer_oc2_init( TimerType *pTimer, enumTimerOCModeType TimerOCMode, enumTimerOCPolarityType TimerOCPolarity, enumTimerOCIdleStatusType TimerOCIdleStatus )
{
	if( ( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM20 ))
	{
		pTimer->BDTR.bit.MOE = 1;					//主输出使能，高级定时器必须配置 
	}
	pTimer->CCMR1.bit_o.OC2PE = 0;					//预装载禁止
	pTimer->CCMR1.bit_o.CC2S = 0;					//配置为输出						
	pTimer->CCMR1.bit_o.OC2M = TimerOCMode;			//输出模式
	pTimer->CR2.bit.OIS2 = TimerOCIdleStatus;		//输出空闲状态
	pTimer->CCER.bit.CC2P = TimerOCPolarity;		//有效极性
	pTimer->CCR2 = 0xFFFF;							//输出比较值
}

/**
* @brief  定时器输出通道2互补通道初始化
* @param  pTimer: 定时器 做PWM输出使用高级定时器：TIM1 TIM8 TIM20
* @param  TimerOCMode: 输出通道输出模式，见类型 enumTimerOCModeType
* @param  TimerOCNPolarity: 互补输出通道有效极性，见类型 enumTimerOCPolarityType
* @param  TimerOCNIdleStatus: 互补通道输出时状态，类型 enumTimerOCIdleStatusType
* @retval 无
*/
void drv_timer_oc2n_init( TimerType *pTimer, enumTimerOCModeType TimerOCNMode, enumTimerOCPolarityType TimerOCNPolarity, enumTimerOCIdleStatusType TimerOCNIdleStatus )
{
	if( ( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM20 ))
	{
		pTimer->BDTR.bit.MOE = 1;					//主输出使能，高级定时器必须配置
	}
	pTimer->CCMR1.bit_o.OC2PE = 0;					//预装载禁止
	pTimer->CCMR1.bit_o.CC2S = 0;					//配置为输出						
	pTimer->CCMR1.bit_o.OC2M = TimerOCNMode;		//输出模式
	pTimer->CR2.bit.OIS2N = TimerOCNIdleStatus;		//输出空闲状态
	pTimer->CCER.bit.CC2NP = TimerOCNPolarity;		//有效极性
	pTimer->CCR2 = 0xFFFF;							//输出比较值
}

/**
* @brief  定时器输出通道3初始化
* @param  pTimer: 定时器  做PWM输出使用高级定时器：TIM1 TIM8 TIM20
* @param  TimerOCMode: 输出通道输出模式，见类型 enumTimerOCModeType
* @param  TimerOCPolarity: 输出通道有效极性，见类型 enumTimerOCPolarityType
* @param  TimerOCIdleStatus: 输出通道空闲时状态，类型 enumTimerOCIdleStatusType
* @retval 无
*/
void drv_timer_oc3_init( TimerType *pTimer, enumTimerOCModeType TimerOCMode, enumTimerOCPolarityType TimerOCPolarity, enumTimerOCIdleStatusType TimerOCIdleStatus )
{
	if( ( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM20 ))
	{
		pTimer->BDTR.bit.MOE = 1;					//主输出使能，高级定时器必须配置 
	}
	pTimer->CCMR2.bit_o.OC3PE = 0;					//预装载禁止
	pTimer->CCMR2.bit_o.CC3S = 0;					//配置为输出						
	pTimer->CCMR2.bit_o.OC3M = TimerOCMode;			//输出模式
	pTimer->CR2.bit.OIS3 = TimerOCIdleStatus;		//输出空闲状态
	pTimer->CCER.bit.CC3P = TimerOCPolarity;		//有效极性
	pTimer->CCR3 = 0xFFFF;							//输出比较值
}

/**
* @brief  定时器输出通道3互补通道初始化
* @param  pTimer: 定时器 做PWM输出使用高级定时器：TIM1 TIM8 TIM20
* @param  TimerOCMode: 输出通道输出模式，见类型 enumTimerOCModeType
* @param  TimerOCNPolarity: 互补输出通道有效极性，见类型 enumTimerOCPolarityType
* @param  TimerOCNIdleStatus: 互补通道输出时状态，类型 enumTimerOCIdleStatusType
* @retval 无
*/
void drv_timer_oc3n_init( TimerType *pTimer, enumTimerOCModeType TimerOCNMode, enumTimerOCPolarityType TimerOCNPolarity, enumTimerOCIdleStatusType TimerOCNIdleStatus )
{
	if( ( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM20 ))
	{
		pTimer->BDTR.bit.MOE = 1;					//主输出使能，高级定时器必须配置
	}
	pTimer->CCMR2.bit_o.OC3PE = 0;					//预装载禁止
	pTimer->CCMR2.bit_o.CC3S = 0;					//配置为输出						
	pTimer->CCMR2.bit_o.OC3M = TimerOCNMode;		//输出模式
	pTimer->CR2.bit.OIS3N = TimerOCNIdleStatus;		//输出空闲状态
	pTimer->CCER.bit.CC3NP = TimerOCNPolarity;		//有效极性
	pTimer->CCR3 = 0xFFFF;							//输出比较值
}

/**
* @brief  定时器输出通道3初始化
* @param  pTimer: 定时器  做PWM输出使用高级定时器：TIM1 TIM8 TIM20
* @param  TimerOCMode: 输出通道输出模式，见类型 enumTimerOCModeType
* @param  TimerOCPolarity: 输出通道有效极性，见类型 enumTimerOCPolarityType
* @param  TimerOCIdleStatus: 输出通道空闲时状态，类型 enumTimerOCIdleStatusType
* @retval 无
*/
void drv_timer_oc4_init( TimerType *pTimer, enumTimerOCModeType TimerOCMode, enumTimerOCPolarityType TimerOCPolarity, enumTimerOCIdleStatusType TimerOCIdleStatus )
{
	if( ( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM20 ))
	{
		pTimer->BDTR.bit.MOE = 1;					//主输出使能，高级定时器必须配置 
	}
	pTimer->CCMR2.bit_o.OC4PE = 0;					//预装载禁止
	pTimer->CCMR2.bit_o.CC4S = 0;					//配置为输出						
	pTimer->CCMR2.bit_o.OC4M = TimerOCMode;			//输出模式
	pTimer->CR2.bit.OIS4 = TimerOCIdleStatus;		//输出空闲状态
	pTimer->CCER.bit.CC4P = TimerOCPolarity;		//有效极性
	pTimer->CCR4 = 0xFFFF;					//输出比较值
}

/**
* @brief  定时器输出通道4互补通道初始化
* @param  pTimer: 定时器 做PWM输出使用高级定时器：TIM1 TIM8 TIM20
* @param  TimerOCMode: 输出通道输出模式，见类型 enumTimerOCModeType
* @param  TimerOCNPolarity: 互补输出通道有效极性，见类型 enumTimerOCPolarityType
* @retval 无
*/
void drv_timer_oc4n_init( TimerType *pTimer, enumTimerOCModeType TimerOCNMode, enumTimerOCPolarityType TimerOCNPolarity )
{
	if( ( pTimer == TIM1 ) || ( pTimer == TIM8 ) || ( pTimer == TIM20 ))
	{
		pTimer->BDTR.bit.MOE = 1;					//主输出使能，高级定时器必须配置
	}
	pTimer->CCMR2.bit_o.OC4PE = 0;					//预装载禁止
	pTimer->CCMR2.bit_o.CC4S = 0;					//配置为输出						
	pTimer->CCMR2.bit_o.OC4M = TimerOCNMode;		//输出模式
	pTimer->CCER.bit.CC4NP = TimerOCNPolarity;		//有效极性
	pTimer->CCR4 = 0xFFFF;							//输出比较值
}
//
///**
//* @brief  设置定时器通道1捕获比较值
//* @param  pTimer: 定时器 TIM1~TIM14
//* @param  Compara1: 捕获比较值
//* @retval 无
//*/
//void drv_timer_set_compara1( TimerType *pTimer, UINT32 Compara1 )
//{
//	pTimer->CCR1 = Compara1;
//}

/**
* @brief  设置定时器通道2捕获比较值
* @param  pTimer: 定时器 TIM1~TIM14
* @param  Compara2: 捕获比较值
* @retval 无
*/
void drv_timer_set_compara2( TimerType *pTimer, UINT32 Compara2 )
{
	pTimer->CCR2 = Compara2;
}

/**
* @brief  设置定时器通道3捕获比较值
* @param  pTimer: 定时器 TIM1~TIM14
* @param  Compara3: 捕获比较值
* @retval 无
*/
void drv_timer_set_compara3( TimerType *pTimer, UINT32 Compara3 )
{
	pTimer->CCR3 = Compara3;
}

/**
* @brief  设置定时器通道4捕获比较值.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  Compara4: 捕获比较值
* @retval 无
*/
void drv_timer_set_compara4( TimerType *pTimer, UINT32 Compara4 )
{
	pTimer->CCR4 = Compara4;
}

/**
* @brief  获取定时器通道1捕获比较值.
* @param  pTimer: 定时器 TIM1~TIM9 TIM14
* @retval 无
*/
UINT32 drv_timer_get_compara1( TimerType *pTimer )
{
	return ( pTimer->CCR1 );
}

/**
* @brief  获取定时器通道2捕获比较值.
* @param  pTimer: 定时器 TIM1~TIM9 TIM14
* @retval 无
*/
UINT32 drv_timer_get_compara2( TimerType *pTimer )
{
	return ( pTimer->CCR2 );
}

/**
* @brief  获取定时器通道3捕获比较值.
* @param  pTimer: 定时器 TIM1~TIM9 TIM14
* @retval 无
*/
UINT32 drv_timer_get_compara3( TimerType *pTimer )
{
	return ( pTimer->CCR3 );
}

/**
* @brief  获取定时器通道4捕获比较值.
* @param  pTimer: 定时器 TIM1~TIM9 TIM14
* @retval 无
*/
UINT32 drv_timer_get_compara4( TimerType *pTimer )
{
	return ( pTimer->CCR4 );
}

/**
* @brief  定时器输出1波形为PWM1模式.
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_set_oc1_pwm1( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC1M = 6;
}

/**
* @brief  定时器输出2波形为PWM1模式.
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_set_oc2_pwm1( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC2M = 6;
}

/**
* @brief  定时器输出3波形为PWM1模式.
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_set_oc3_pwm1( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC3M = 6;
}

/**
* @brief  定时器输出4波形为PWM1模式.
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_set_oc4_pwm1( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC4M = 6;
}
//
///**
//* @brief  强制定时器输出1波形为有效电平(高电平).
//* @param  pTimer: 定时器 TIM1~TIM5 TIM8
//* @retval 无
//*/
//void drv_timer_forced_oc1_active( TimerType* pTimer )
//{
//	pTimer->CCMR1.bit_o.OC1M = 5;
//}

/**
* @brief  强制定时器输出1波形为无效电平(低电平).
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
//void drv_timer_forced_oc1_inactive( TimerType* pTimer )
//{
//	pTimer->CCMR1.bit_o.OC1M = 4;
//}

/**
* @brief  强制定时器输出2波形为有效电平(高电平).
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_forced_oc2_active( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC2M = 5;
}

/**
* @brief  强制定时器输出2波形为无效电平(低电平).
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_forced_oc2_inactive( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC2M = 4;
}

/**
* @brief  强制定时器输出3波形为有效电平(高电平).
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_forced_oc3_active( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC3M = 5;
}

/**
* @brief  强制定时器输出3波形为无效电平(低电平).
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_forced_oc3_inactive( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC3M = 4;
}

/**
* @brief  强制定时器输出4波形为有效电平(高电平).
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_forced_oc4_active( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC4M = 5;
}

/**
* @brief  强制定时器输出4波形为无效电平(低电平).
* @param  pTimer: 定时器 TIM1~TIM5 TIM8
* @retval 无
*/
void drv_timer_forced_oc4_inactive( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC4M = 4;
}

/**
* @brief  使能定时器CCR1预装载.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_ccr1_preload_enable( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC1PE = 1;
    //pTimer->CCMR1.bit_o.OC1FE = 1;
}

/**
* @brief  禁止定时器CCR1预装载.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_ccr1_preload_disable( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC1PE = 0;
}

/**
* @brief  使能定时器CCR2预装载.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_ccr2_preload_enable( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC2PE = 1;
}

/**
* @brief  禁止定时器CCR2预装载.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_ccr2_preload_disable( TimerType* pTimer )
{
	pTimer->CCMR1.bit_o.OC2PE = 0;
}

/**
* @brief  使能定时器CCR3预装载.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_ccr3_preload_enable( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC3PE = 1;
}

/**
* @brief  禁止定时器CCR3预装载.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_ccr3_preload_disable( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC3PE = 0;
}

/**
* @brief  使能定时器CCR4预装载.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_ccr4_preload_enable( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC4PE = 1;
}

/**
* @brief  禁止定时器CCR4预装载.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_ccr4_preload_disable( TimerType* pTimer )
{
	pTimer->CCMR2.bit_o.OC4PE = 0;
}

/**
* @brief  配置定时器输出通道1输出极性为高电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc1_polarity_high( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1P = 1;
}

/**
* @brief  配置定时器输出通道1输出极性为低电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc1_polarity_low( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1P = 0;
}

/**
* @brief  配置定时器输出通道1N输出极性为高电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc1n_polarity_high( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1NP = 1;
}

/**
* @brief  配置定时器输出通道1N输出极性为低电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc1n_polarity_low( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1NP = 0;
}

/**
* @brief  配置定时器输出通道2输出极性为高电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc2_polarity_high( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2P = 1;
}

/**
* @brief  配置定时器输出通道2输出极性为低电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc2_polarity_low( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2P = 0;
}

/**
* @brief  配置定时器输出通道2N输出极性为高电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc2n_polarity_high( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2NP = 1;
}

/**
* @brief  配置定时器输出通道2N输出极性为低电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc2n_polarity_low( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2NP = 0;
}

/**
* @brief  配置定时器输出通道3输出极性为高电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc3_polarity_high( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3P = 1;
}

/**
* @brief  配置定时器输出通道3输出极性为低电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc3_polarity_low( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3P = 0;
}

/**
* @brief  配置定时器输出通道3N输出极性为高电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc3n_polarity_high( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3NP = 1;
}

/**
* @brief  配置定时器输出通道3N输出极性为低电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc3n_polarity_low( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3NP = 0;
}

/**
* @brief  配置定时器输出通道4输出极性为高电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc4_polarity_high( TimerType* pTimer )
{
	pTimer->CCER.bit.CC4P = 1;
}

/**
* @brief  配置定时器输出通道4输出极性为低电平有效.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @retval 无
*/
void drv_timer_set_oc4_polarity_low( TimerType* pTimer )
{
	pTimer->CCER.bit.CC4P = 0;
}

/**
* @brief  使能定时器捕获比较通道1
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx1_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1E = 1;
}

/**
* @brief  定时定时器捕获比较通道1
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx1_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1E = 0;
}

/**
* @brief  使能定时器捕获比较通道2
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx2_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2E = 1;
}

/**
* @brief  定时定时器捕获比较通道2
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx2_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2E = 0;
}


/**
* @brief  使能定时器捕获比较通道3
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx3_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3E = 1;
}

/**
* @brief  定时定时器捕获比较通道3
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx3_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3E = 0;
}

/**
* @brief  使能定时器捕获比较通道4
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx4_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC4E = 1;
}

/**
* @brief  定时定时器捕获比较通道4
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx4_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC4E = 0;
}

/**
* @brief  使能定时器捕获比较通道1N
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx1n_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1NE = 1;
}

/**
* @brief  定时定时器捕获比较通道1N
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx1n_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1NE = 0;
}

/**
* @brief  使能定时器捕获比较通道2N
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx2n_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2NE = 1;
}

/**
* @brief  定时定时器捕获比较通道2N
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx2n_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2NE = 0;
}

/**
* @brief  使能定时器捕获比较通道3N
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx3n_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3NE = 1;
}

/**
* @brief  定时定时器捕获比较通道3N
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @retval 无
*/
void drv_timer_ccx3n_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3NE = 0;
}

/**
* @brief  定时器输入通道1初始化
* @param  pTimer: 定时器 
* @param  TimerIcPolarity: 输入通道捕获触发极性，见类型 enumTimerIcPolarityType
* @param  TimerIcPresclar: 输入通道捕分频，见类型 enumTimerIcPresclarType
* @param  TimerIcSelection: 输入通道捕获映射选择，见类型 enumTimerIcSelectionType
* @param  TimerIcFilter: 输入通道捕获滤波器，见类型 enumTimerIcFilterType
* @retval  无
*/
void drv_timer_ic1_init( TimerType *pTimer, enumTimerIcPolarityType TimerIcPolarity, 
	enumTimerIcPresclarType TimerIcPresclar, enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter )
{

	pTimer->CCMR1.bit_i.CC1S = TimerIcSelection;		//输入映射选择
	pTimer->CCMR1.bit_i.IC1PSC = TimerIcPresclar;		//输入捕获预分频，N次事件执行一次捕获
	pTimer->CCMR1.bit_i.IC1F = TimerIcFilter;			//滤波器频率设置

	switch ( TimerIcPolarity )							//触发边沿设置
	{
		case TIM_IC_POLARITY_RISING:
			pTimer->CCER.bit.CC1P = 0; 
			pTimer->CCER.bit.CC1NP = 0;break;
		case TIM_IC_POLARITY_FALLING: 
			pTimer->CCER.bit.CC1P = 1; 
			pTimer->CCER.bit.CC1NP = 0; break;
		case TIM_IC_POLARITY_BOTHEDGE: 
			pTimer->CCER.bit.CC1P = 1; 
			pTimer->CCER.bit.CC1NP = 1; break;
		default: break;
	}
}

/**
* @brief  定时器输入通道2初始化
* @param  TimerIcPolarity: 输入通道捕获触发极性，见类型 enumTimerIcPolarityType
* @param  TimerIcPresclar: 输入通道捕分频，见类型 enumTimerIcPresclarType
* @param  TimerIcSelection: 输入通道捕获映射选择，见类型 enumTimerIcSelectionType
* @param  TimerIcFilter: 输入通道捕获滤波器，见类型 enumTimerIcFilterType
* @retval  无
*/
void drv_timer_ic2_init( TimerType *pTimer, enumTimerIcPolarityType TimerIcPolarity, enumTimerIcPresclarType TimerIcPresclar, 
						enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter )
{
	pTimer->CCMR1.bit_i.CC2S = TimerIcSelection;
	pTimer->CCMR1.bit_i.IC2PSC = TimerIcPresclar;
	pTimer->CCMR1.bit_i.IC2F = TimerIcFilter;

	switch ( TimerIcPolarity )
	{
	case TIM_IC_POLARITY_RISING: 
		pTimer->CCER.bit.CC2P = 0; 
		pTimer->CCER.bit.CC2NP = 0; break;
	case TIM_IC_POLARITY_FALLING: 
		pTimer->CCER.bit.CC2P = 1; 
		pTimer->CCER.bit.CC2NP = 0; break;
	case TIM_IC_POLARITY_BOTHEDGE: 
		pTimer->CCER.bit.CC2P = 1; 
		pTimer->CCER.bit.CC2NP = 1; break;
	default: break;
	}
}

/**
* @brief  定时器输入通道3初始化
* @param  pTimer: 定时器 
* @param  TimerIcPolarity: 输入通道捕获触发极性，见类型 enumTimerIcPolarityType
* @param  TimerIcPresclar: 输入通道捕分频，见类型 enumTimerIcPresclarType
* @param  TimerIcSelection: 输入通道捕获映射选择，见类型 enumTimerIcSelectionType
* @param  TimerIcFilter: 输入通道捕获滤波器，见类型 enumTimerIcFilterType
* @retval  无
*/
void drv_timer_ic3_init( TimerType *pTimer, enumTimerIcPolarityType TimerIcPolarity, enumTimerIcPresclarType TimerIcPresclar, 
						enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter )
{
	pTimer->CCMR2.bit_i.CC3S = TimerIcSelection;
	pTimer->CCMR2.bit_i.IC3PSC = TimerIcPresclar;
	pTimer->CCMR2.bit_i.IC3F = TimerIcFilter;

	switch ( TimerIcPolarity )
	{
	case TIM_IC_POLARITY_RISING: 
		pTimer->CCER.bit.CC3P = 0; 
		pTimer->CCER.bit.CC3NP = 0; break;
	case TIM_IC_POLARITY_FALLING: 
		pTimer->CCER.bit.CC3P = 1; 
		pTimer->CCER.bit.CC3NP = 0; break;
	case TIM_IC_POLARITY_BOTHEDGE:
		pTimer->CCER.bit.CC3P = 1; 
		pTimer->CCER.bit.CC3NP = 1; break;
	default: break;
	}
}

/**
* @brief  定时器输入通道4初始化
* @param  pTimer: 定时器 
* @param  TimerIcPolarity: 输入通道捕获触发极性，见类型 enumTimerIcPolarityType
* @param  TimerIcPresclar: 输入通道捕分频，见类型 enumTimerIcPresclarType
* @param  TimerIcSelection: 输入通道捕获映射选择，见类型 enumTimerIcSelectionType
* @param  TimerIcFilter: 输入通道捕获滤波器，见类型 enumTimerIcFilterType
* @retval  无
*/
void drv_timer_ic4_init( TimerType *pTimer, enumTimerIcPolarityType TimerIcPolarity, enumTimerIcPresclarType TimerIcPresclar, 
						enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter )
{
	pTimer->CCMR2.bit_i.CC4S = TimerIcSelection;
	pTimer->CCMR2.bit_i.IC4PSC = TimerIcPresclar;
	pTimer->CCMR2.bit_i.IC4F = TimerIcFilter;

	switch ( TimerIcPolarity )
	{
	case TIM_IC_POLARITY_RISING: pTimer->CCER.bit.CC4P = 0; break;
	case TIM_IC_POLARITY_FALLING: pTimer->CCER.bit.CC4P = 1; break;
	case TIM_IC_POLARITY_BOTHEDGE: pTimer->CCER.bit.CC4P = 1; break;
	default: break;
	}
}

/**
* @brief  定时器输入通道1使能
* @param  pTimer: 定时器 
* @retval  无
*/
void drv_timer_ic1_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1E = 1;				
}

/**
* @brief  定时器输入通道1禁止
* @param  pTimer: 定时器 
* @retval  无
*/
void drv_timer_ic1_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC1E = 0;				
}

/**
* @brief  定时器输入通道2使能
* @param  pTimer: 定时器 
* @retval  无
*/
void drv_timer_ic2_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2E = 1;				
}

/**
* @brief  定时器输入通道2禁止
* @param  pTimer: 定时器 
* @retval  无
*/
void drv_timer_ic2_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC2E = 0;				
}

/**
* @brief  定时器输入通道3使能
* @param  pTimer: 定时器 
* @retval  无
*/
void drv_timer_ic3_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3E = 1;				
}

/**
* @brief  定时器输入通道3禁止
* @param  pTimer: 定时器 
* @retval  无
*/
void drv_timer_ic3_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC3E = 0;				
}

/**
* @brief  定时器输入通道4使能
* @param  pTimer: 定时器 
* @retval  无
*/
void drv_timer_ic4_enable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC4E = 1;				
}

/**
* @brief  定时器输入通道4禁止
* @param  pTimer: 定时器 
* @retval  无
*/
void drv_timer_ic4_disable( TimerType* pTimer )
{
	pTimer->CCER.bit.CC4E = 0;				
}

/**
* @brief  设置定时器死区时间控制参数.
* @param  pTimer: 只能是TIM1和TIM8.
* @param  DeadTime: 要设置的死区时间值，需要根据实际需要计算.
* @retval 无
*/
void drv_timer_set_deadtime( TimerType* pTimer, UINT16 DeadTime )
{
	pTimer->BDTR.bit.DTG = DeadTime;
}

/**
* @brief  设置定时器在运行模式下关闭后的输出状态为无效电平状态.
* @param  pTimer: 只能是TIM1和TIM8.
* @retval 无
*/
void drv_timer_set_run_off_inactive( TimerType* pTimer )
{
	pTimer->BDTR.bit.OSSR = 1;
}

/**
* @brief  使能定时器主输出.
* @param  pTimer: 只能是TIM1和TIM8.
* @retval 无
*/
void drv_timer_pwm_output_enable( TimerType *pTimer )
{
	pTimer->BDTR.bit.MOE = 1;
}

/**
* @brief  使能定时器主输出.
* @param  pTimer: 只能是TIM1和TIM8.
* @retval 无
*/
void drv_timer_pwm_output_disable( TimerType *pTimer )
{
	pTimer->BDTR.bit.MOE = 0;
}


/**
* @brief  使能定时器中断.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  TimerIt: 要使能的中断源，可以是下面值的组合:
*            @arg TIM_IT_Update: TIM update Interrupt source
*            @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
*            @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
*            @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
*            @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
*            @arg TIM_IT_COM: TIM Commutation Interrupt source
*            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
*            @arg TIM_IT_Break: TIM Break Interrupt source
* @note   对 TIM6 和 TIM7 只能使用 TIM_IT_Update 中断
* @note   对 TIM9 和 TIM12 只能使用: TIM_IT_Update, TIM_IT_CC1, TIM_IT_CC2 or TIM_IT_Trigger.
* @note   对 TIM10, TIM11, TIM13 和 TIM14 只能使用: TIM_IT_Update or TIM_IT_CC1
* @note   TIM_IT_COM 和 TIM_IT_Break 只能用于 TIM1 和 TIM8
* @retval 无
*/
void drv_timer_it_enable( TimerType *pTimer, UINT16 TimerIt )
{
	pTimer->DIER.all |= TimerIt;
}

/**
* @brief  禁止定时器中断.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  TimerIt: 要禁止的中断源，可以是下面值的中的一个:
*            @arg TIM_IT_Update: TIM update Interrupt source
*            @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
*            @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
*            @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
*            @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
*            @arg TIM_IT_COM: TIM Commutation Interrupt source
*            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
*            @arg TIM_IT_Break: TIM Break Interrupt source
* @note   对 TIM6 和 TIM7 只能使用 TIM_IT_Update 中断
* @note   对 TIM9 和 TIM12 只能使用: TIM_IT_Update, TIM_IT_CC1, TIM_IT_CC2 or TIM_IT_Trigger.
* @note   对 TIM10, TIM11, TIM13 和 TIM14 只能使用: TIM_IT_Update or TIM_IT_CC1
* @note   TIM_IT_COM 和 TIM_IT_Break 只能用于 TIM1 和 TIM8
* @retval 无
*/
void drv_timer_it_disable( TimerType *pTimer, UINT16 TimerIt )
{
	pTimer->DIER.all &= ~(UINT16)TimerIt;
}

/**
* @brief  检查定时器标志状态.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  TimerFlag: 要检查的标志，可以是下面值中的一个:
*            @arg TIM_FLAG_Update: TIM update Flag
*            @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
*            @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
*            @arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
*            @arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
*            @arg TIM_FLAG_COM: TIM Commutation Flag
*            @arg TIM_FLAG_Trigger: TIM Trigger Flag
*            @arg TIM_FLAG_Break: TIM Break Flag
*            @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 over capture Flag
*            @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 over capture Flag
*            @arg TIM_FLAG_CC3OF: TIM Capture Compare 3 over capture Flag
*            @arg TIM_FLAG_CC4OF: TIM Capture Compare 4 over capture Flag
* @note   TIM6 和 TIM7 只有TIM_FLAG_Update标志.
* @note   TIM_FLAG_COM 和 TIM_FLAG_Break 只用于 TIM1 和 TIM8.
* @retval 新的标志状态
*/
FlagStatus drv_timer_get_flag_status( TimerType *pTimer, UINT16 TimerFlag )
{
	if (( pTimer->SR.all & TimerFlag ) != (UINT16)RESET)
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清定时器标志挂起状态.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  TimerFlag: 要清除的标志，可以是下面值和组合:
*            @arg TIM_FLAG_Update: TIM update Flag
*            @arg TIM_FLAG_CC1: TIM Capture Compare 1 Flag
*            @arg TIM_FLAG_CC2: TIM Capture Compare 2 Flag
*            @arg TIM_FLAG_CC3: TIM Capture Compare 3 Flag
*            @arg TIM_FLAG_CC4: TIM Capture Compare 4 Flag
*            @arg TIM_FLAG_COM: TIM Commutation Flag
*            @arg TIM_FLAG_Trigger: TIM Trigger Flag
*            @arg TIM_FLAG_Break: TIM Break Flag
*            @arg TIM_FLAG_CC1OF: TIM Capture Compare 1 over capture Flag
*            @arg TIM_FLAG_CC2OF: TIM Capture Compare 2 over capture Flag
*            @arg TIM_FLAG_CC3OF: TIM Capture Compare 3 over capture Flag
*            @arg TIM_FLAG_CC4OF: TIM Capture Compare 4 over capture Flag
* @note   TIM6 和 TIM7 只有TIM_FLAG_Update标志.
* @note   TIM_FLAG_COM 和 TIM_FLAG_Break 只用于 TIM1 和 TIM8.
* @retval 无
*/
void drv_timer_clear_flag_status( TimerType *pTimer, UINT16 TimerFlag )
{
	pTimer->SR.all = (UINT16)~TimerFlag;
}

/**
* @brief  检查定时器中断状态.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  TimerIt: 要检查的中断源，可以是下面值的一个:
*            @arg TIM_IT_Update: TIM update Interrupt source
*            @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
*            @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
*            @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
*            @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
*            @arg TIM_IT_COM: TIM Commutation Interrupt source
*            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
*            @arg TIM_IT_Break: TIM Break Interrupt source
* @note   TIM6 和 TIM7 只产生TIM_IT_Update中断.
* @note   TIM_IT_COM 和 TIM_IT_Break 只用于 TIM1 和 TIM8.
* @retval 当前状态
*/
ITStatus drv_timer_get_it_status( TimerType *pTimer, UINT16 TimerIt )
{
	UINT16 itstatus = 0x00, itenable = 0x00;

	itstatus = pTimer->SR.all & TimerIt;
	itenable = pTimer->DIER.all & TimerIt;
	
	if (( itstatus != (UINT16)RESET ) && ( itenable != (UINT16)RESET ))
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清定时器中断挂起位.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  TimerIt: 要检查的中断源，可以是下面值的组合:
*            @arg TIM_IT_Update: TIM1 update Interrupt source
*            @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
*            @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
*            @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
*            @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
*            @arg TIM_IT_COM: TIM Commutation Interrupt source
*            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
*            @arg TIM_IT_Break: TIM Break Interrupt source
* @note   TIM6 和 TIM7 只产生TIM_IT_Update中断.
* @note   TIM_IT_COM 和 TIM_IT_Break 只用于 TIM1 和 TIM8.
* @retval 无
*/
void drv_timer_clear_it_pending_bit( TimerType *pTimer, UINT16 TimerIt )
{
	pTimer->SR.all = (UINT16)~TimerIt;
}

/**
* @brief  设置定时器输入捕获1预分频器.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  IcPsc: 0~~3分别代表每1、2、4、8次事件执行一次捕获
* @retval 无
*/
void drv_timer_set_ic1_psc( TimerType* pTimer, UINT16 IcPsc )
{
	pTimer->CCMR1.bit_i.IC1PSC = IcPsc;
}

/**
* @brief  设置定时器输入捕获2预分频器.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  IcPsc: 0~~3分别代表每1、2、4、8次事件执行一次捕获
* @retval 无
*/
void drv_timer_set_ic2_psc( TimerType* pTimer, UINT16 IcPsc )
{
	pTimer->CCMR1.bit_i.IC2PSC = IcPsc;
}

/**
* @brief  设置定时器输入捕获3预分频器.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  IcPsc: 0~~3分别代表每1、2、4、8次事件执行一次捕获
* @retval 无
*/
void drv_timer_set_ic3_psc( TimerType* pTimer, UINT16 IcPsc )
{
	pTimer->CCMR2.bit_i.IC3PSC = IcPsc;
}

/**
* @brief  设置定时器输入捕获4预分频器.
* @param  pTimer: 定时器 TIM1~TIM14
* @param  IcPsc: 0~~3分别代表每1、2、4、8次事件执行一次捕获
* @retval 无
*/
void drv_timer_set_ic4_psc( TimerType* pTimer, UINT16 IcPsc )
{
	pTimer->CCMR2.bit_i.IC4PSC = IcPsc;
}

/**
* @brief  选择从模式输入触发源
* @param  pTimer: 定时器 TIM1~TIM5 TIM8~TIM14
* @param  InTrigger: 输入触发源，见enumTimerSlaveTriggerSeletcionType，可以是下面值的一个:
*            @arg TIM_TS_ITR0: Internal Trigger 0
*            @arg TIM_TS_ITR1: Internal Trigger 1
*            @arg TIM_TS_ITR2: Internal Trigger 2
*            @arg TIM_TS_ITR3: Internal Trigger 3
*            @arg TIM_TS_TI1F_ED: TI1 Edge Detector
*            @arg TIM_TS_TI1FP1: Filtered Timer Input 1
*            @arg TIM_TS_TI2FP2: Filtered Timer Input 2
*            @arg TIM_TS_ETRF: External Trigger input
* @retval 无
*/
void drv_timer_select_input_trigger( TimerType* pTimer, enumTimerSlaveTriggerSeletcionType InTrigger )
{
	pTimer->SMCR.bit.TS = (UINT16)InTrigger;
}

/**
* @brief  选择主模式输出触发源
* @param  pTimer: 定时器 TIM1~TIM8
* @param  OutTrigger: 输出触发源，见enumTimerMasterTriggerSourceType，可以是下面值的一个:
*  - For all TIMx
*            @arg TIM_TRGOSource_Reset:  The UG bit in the TIM_EGR register is used as the trigger output(TRGO)
*            @arg TIM_TRGOSource_Enable: The Counter Enable CEN is used as the trigger output(TRGO)
*            @arg TIM_TRGOSource_Update: The update event is selected as the trigger output(TRGO)
*
*  - For all TIMx except TIM6 and TIM7
*            @arg TIM_TRGOSource_OC1: The trigger output sends a positive pulse when the CC1IF flag
*                                     is to be set, as soon as a capture or compare match occurs(TRGO)
*            @arg TIM_TRGOSource_OC1Ref: OC1REF signal is used as the trigger output(TRGO)
*            @arg TIM_TRGOSource_OC2Ref: OC2REF signal is used as the trigger output(TRGO)
*            @arg TIM_TRGOSource_OC3Ref: OC3REF signal is used as the trigger output(TRGO)
*            @arg TIM_TRGOSource_OC4Ref: OC4REF signal is used as the trigger output(TRGO)
*
* @retval 无
*/
void drv_timer_select_output_trigger( TimerType* pTimer, enumTimerMasterTriggerSourceType OutTrigger )
{
	pTimer->CR2.bit.MMS = (UINT16)OutTrigger;
}

/**
* @brief  定时器从模式选择
* @param  pTimer: 定时器 TIM1~TIM5, TIM8~TIM9, TIM12
* @param  SlaveMode: 定时器从模式，见类型 enumTimerSlaveModeType
* @retval 无
*/
void drv_timer_select_slave_mode( TimerType *pTimer, enumTimerSlaveModeType SlaveMode )
{
	pTimer->SMCR.bit.SMS = (UINT8)SlaveMode;
}

/**
* @brief  使能定时器主从模式.
* @param  pTimer: 定时器 TIM1~TIM5, TIM8~TIM9, TIM12
* @retval 无
*/
void drv_timer_slave_mode_enable( TimerType* pTimer )
{
	pTimer->SMCR.bit.MSM = 1;
}

/**
* @brief  禁止定时器主从模式.
* @param  pTimer: 定时器 TIM1~TIM5, TIM8~TIM9, TIM12
* @retval 无
*/
void drv_timer_slave_mode_disable( TimerType* pTimer )
{
	pTimer->SMCR.bit.MSM = 0;
}

/**
* @brief  配置定时器外部触发器(ETR).
* @param  pTimer: 定时器 TIM1~TIM5, TIM8
* @param  EtrPsc: 外部触发预分频，0~3分别代表不分频、2分频、4分频和8分频
* @param  EtrPolarity: 外部触发信号极性，0表示未反相（高电平或上升沿有效），1表示反相（低电平或下降沿有效）
* @param  EtrFilter: 外部触发器滤波，可以是0~15
* @retval 无
*/
void drv_timer_set_etr( TimerType* pTimer, UINT16 EtrPsc, UINT16 EtrPolarity, UINT16 EtrFilter )
{
	pTimer->SMCR.bit.ETPS = EtrPsc;
	pTimer->SMCR.bit.ETP = EtrPolarity;
	pTimer->SMCR.bit.ETF = EtrFilter;
}

/**
* @brief  定时器编码器接口初始化.
* @param  pTimer: 定时器 TIM1~TIM5, TIM8~TIM9, TIM12
* @param  EncoderMode: 编码器接口模式，1表示TI2FP2电平在TI1FP1边沿计数，2表示TI1FP1电平在TI2FP2边沿计数，3表示在TI1FP1和TI2FP2边沿计数
* @param  Ic1Polarity: IC1信号极性，0为上升沿触发，1为下降沿触发
* @param  Ic2Polarity: IC2信号极性，0为上升沿触发，1为下降沿触发
* @retval 无
*/
void drv_timer_encoder_init( TimerType* pTimer, UINT16 EncoderMode, UINT16 Ic1Polarity, UINT16 Ic2Polarity )
{
	pTimer->SMCR.bit.SMS = EncoderMode;					//编码器模式1~3
	pTimer->CCMR1.bit_i.CC1S = 1;						//ICx映射到对应的TIx上
	pTimer->CCMR1.bit_i.CC2S = 1;
	pTimer->CCER.bit.CC1P = Ic1Polarity;				//输入捕获极性CCxNP默认为0
	pTimer->CCER.bit.CC2P = Ic2Polarity;				
}

/**
* @brief  配置TI1为输入.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @param  IcPolarity : 输入极性，0表示上升沿，1表示下降沿，3表示双边沿
* @param  IcFilter: 输入捕获滤波器，见类型 enumTimerIcFilterType
* @retval None
*/
void drv_timer_set_ic1_input( TimerType* pTimer, UINT16 IcPolarity, enumTimerIcFilterType IcFilter )
{
	if (IcPolarity > 1)
	{
		pTimer->CCER.bit.CC1NP = 1;
		pTimer->CCER.bit.CC1P = 1;
	}
	else
	{
		pTimer->CCER.bit.CC1NP = 0;
		pTimer->CCER.bit.CC1P = IcPolarity;
	}

	pTimer->CCMR1.bit_i.IC1F = (UINT16)IcFilter;
}

/**
* @brief  配置TI2为输入.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @param  IcPolarity : 输入极性，0表示上升沿，1表示下降沿，3表示双边沿
* @param  IcFilter: 输入捕获滤波器，见类型 enumTimerIcFilterType
* @retval None
*/
void drv_timer_set_ic2_input( TimerType* pTimer, UINT16 IcPolarity, enumTimerIcFilterType IcFilter )
{
	if (IcPolarity > 1)
	{
		pTimer->CCER.bit.CC2NP = 1;
		pTimer->CCER.bit.CC2P = 1;
	}
	else
	{
		pTimer->CCER.bit.CC2NP = 0;
		pTimer->CCER.bit.CC2P = IcPolarity;
	}

	pTimer->CCMR1.bit_i.IC2F = (UINT16)IcFilter;
}

/**
* @brief  配置TI3为输入.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @param  IcPolarity : 输入极性，0表示上升沿，1表示下降沿，3表示双边沿
* @param  IcFilter: 输入捕获滤波器，见类型 enumTimerIcFilterType
* @retval None
*/
void drv_timer_set_ic3_input( TimerType* pTimer, UINT16 IcPolarity, enumTimerIcFilterType IcFilter )
{
	if (IcPolarity > 1)
	{
		pTimer->CCER.bit.CC3NP = 1;
		pTimer->CCER.bit.CC3P = 1;
	}
	else
	{
		pTimer->CCER.bit.CC3NP = 0;
		pTimer->CCER.bit.CC3P = IcPolarity;
	}

	pTimer->CCMR2.bit_i.IC3F = (UINT16)IcFilter;
}

/**
* @brief  配置TI4为输入.
* @param  pTimer: 定时器TIM1~TIM5和TIM8~TIM14.
* @param  IcPolarity : 输入极性，0表示上升沿，1表示下降沿
* @param  IcFilter: 输入捕获滤波器，见类型 enumTimerIcFilterType
* @retval None
*/
void drv_timer_set_ic4_input( TimerType* pTimer, UINT16 IcPolarity, enumTimerIcFilterType IcFilter )
{
	pTimer->CCER.bit.CC4P = IcPolarity;
	pTimer->CCMR2.bit_i.IC4F = (UINT16)IcFilter;
}




/**
* @brief  定时器输入捕获初始化
* @param  pTimer: 定时器 TIM1~TIM14
* @param  TimerIcChannel: 输入通道
* @param  TimerIcPolarity: 输入通道捕获触发极性，见类型 enumTimerIcPolarityType
* @param  TimerIcPresclar: 输入通道捕分频，见类型 enumTimerIcPresclarType
* @param  TimerIcSelection: 输入通道捕获映射选择，见类型 enumTimerIcSelectionType
* @param  TimerIcFilter: 输入通道捕获滤波器，见类型 enumTimerIcFilterType
* @retval  无
*/
void drv_timer_pwm_ic_init( TimerType *pTimer, enumTimerIcChannelType TimerIcChannel, enumTimerIcPolarityType TimerIcPolarity, 
	enumTimerIcPresclarType TimerIcPresclar, enumTimerIcSelectionType TimerIcSelection, enumTimerIcFilterType TimerIcFilter )
{
	UINT16 icoppositepolarity = TIM_IC_POLARITY_RISING;
	UINT16 icoppositeselection = TIM_IC_SELECTION_1;


	if (TimerIcPolarity == TIM_IC_POLARITY_RISING)
	{
		icoppositepolarity = TIM_IC_POLARITY_FALLING;
	}
	else
	{
		icoppositepolarity = TIM_IC_POLARITY_RISING;
	}

	if (TimerIcSelection == TIM_IC_SELECTION_1)
	{
		icoppositeselection = TIM_IC_SELECTION_2;
	}
	else
	{
		icoppositeselection = TIM_IC_SELECTION_1;
	}
	if (TimerIcChannel == TIM_IC_CHANNEL_1)
	{
		pTimer->CCMR1.bit_i.CC1S = TimerIcSelection;
		pTimer->CCMR1.bit_i.IC1PSC = TimerIcPresclar;
		pTimer->CCMR1.bit_i.IC1F = TimerIcFilter;
		pTimer->CCER.bit.CC1E = 1;
		switch ((UINT8)( TimerIcPolarity ))
		{
		case 0: pTimer->CCER.bit.CC1P = 0; pTimer->CCER.bit.CC1NP = 0; break;
		case 1: pTimer->CCER.bit.CC1P = 1; pTimer->CCER.bit.CC1NP = 0; break;
		case 2: pTimer->CCER.bit.CC1P = 1; pTimer->CCER.bit.CC1NP = 1; break;
		default: break;
		}

		pTimer->CCMR1.bit_i.CC2S = icoppositeselection;
		pTimer->CCMR1.bit_i.IC2PSC = TimerIcPresclar;
		pTimer->CCMR1.bit_i.IC2F = TimerIcFilter;
		pTimer->CCER.bit.CC2E = 1;
		switch ((UINT8)( icoppositepolarity ))
		{
		case 0: pTimer->CCER.bit.CC2P = 0; pTimer->CCER.bit.CC2NP = 0; break;
		case 1: pTimer->CCER.bit.CC2P = 1; pTimer->CCER.bit.CC2NP = 0; break;
		case 2: pTimer->CCER.bit.CC2P = 1; pTimer->CCER.bit.CC2NP = 1; break;
		default: break;
		}

	}
	else
	{
		pTimer->CCMR1.bit_i.CC2S = TimerIcSelection;
		pTimer->CCMR1.bit_i.IC2PSC = TimerIcPresclar;
		pTimer->CCMR1.bit_i.IC2F = TimerIcFilter;
		pTimer->CCER.bit.CC2E = 1;
		switch ((UINT8)( TimerIcPolarity ))
		{
		case 0: pTimer->CCER.bit.CC2P = 0; pTimer->CCER.bit.CC2NP = 0; break;
		case 1: pTimer->CCER.bit.CC2P = 1; pTimer->CCER.bit.CC2NP = 0; break;
		case 2: pTimer->CCER.bit.CC2P = 1; pTimer->CCER.bit.CC2NP = 1; break;
		default: break;
		}

		pTimer->CCMR1.bit_i.CC1S = icoppositeselection;
		pTimer->CCMR1.bit_i.IC1PSC = TimerIcPresclar;
		pTimer->CCMR1.bit_i.IC1F = TimerIcFilter;
		pTimer->CCER.bit.CC1E = 1;
		switch ((UINT8)( icoppositepolarity ))
		{
		case 0: pTimer->CCER.bit.CC1P = 0; pTimer->CCER.bit.CC2NP = 0; break;
		case 1: pTimer->CCER.bit.CC1P = 1; pTimer->CCER.bit.CC2NP = 0; break;
		case 2: pTimer->CCER.bit.CC1P = 1; pTimer->CCER.bit.CC2NP = 1; break;
		default: break;
		}
	}
}

/**
* @brief  设置定时器滤波器频率
* @param  pTimer: 定时器 TIM1~TIM14
* @retval FilterDiv: 滤波器分频系数
*/
void drv_timer_set_filter_frequency( TimerType *pTimer, UINT32 FilterDiv )
{
	//超过512 4分频
	if (FilterDiv > 1024)
	{
		pTimer->CR1.bit.CKD = TIM_CKD_DIV4;
		pTimer->CCMR1.bit_i.IC1F = 0x0F;
		pTimer->CCMR1.bit_i.IC2F = 0x0F;
	}
	else if (FilterDiv >= 768)
	{
		pTimer->CR1.bit.CKD = TIM_CKD_DIV4;
		pTimer->CCMR1.bit_i.IC1F = 0x0E;
		pTimer->CCMR1.bit_i.IC2F = 0x0E;
	}
	else if (FilterDiv >= 640)
	{
		pTimer->CR1.bit.CKD = TIM_CKD_DIV4;
		pTimer->CCMR1.bit_i.IC1F = 0x0D;
		pTimer->CCMR1.bit_i.IC2F = 0x0D;
	}
	else if (FilterDiv >= 512)
	{
		pTimer->CR1.bit.CKD = TIM_CKD_DIV4;
		pTimer->CCMR1.bit_i.IC1F = 0x0C;
		pTimer->CCMR1.bit_i.IC2F = 0x0C;
	}
	else if (FilterDiv >= 384)							// 超过256小于512时需要2分频
	{
		pTimer->CR1.bit.CKD = TIM_CKD_DIV2;
		pTimer->CCMR1.bit_i.IC1F = 0x0E;
		pTimer->CCMR1.bit_i.IC2F = 0x0E;
	}
	else if (FilterDiv >= 320)
	{
		pTimer->CR1.bit.CKD = TIM_CKD_DIV2;
		pTimer->CCMR1.bit_i.IC1F = 0x0D;
		pTimer->CCMR1.bit_i.IC2F = 0x0D;
	}
	else if (FilterDiv >= 256)
	{
		pTimer->CR1.bit.CKD = TIM_CKD_DIV2;
		pTimer->CCMR1.bit_i.IC1F = 0x0C;
		pTimer->CCMR1.bit_i.IC2F = 0x0C;
	}
	else if (FilterDiv >= 192)							// 小于256时不需要分频
	{
		pTimer->CCMR1.bit_i.IC1F = 0x0E;
		pTimer->CCMR1.bit_i.IC2F = 0x0E;
	}
	else if (FilterDiv >= 160)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x0D;
		pTimer->CCMR1.bit_i.IC2F = 0x0D;
	}
	else if (FilterDiv >= 128)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x0C;
		pTimer->CCMR1.bit_i.IC2F = 0x0C;
	}
	else if (FilterDiv >= 96)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x0B;
		pTimer->CCMR1.bit_i.IC2F = 0x0B;
	}
	else if (FilterDiv >= 80)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x0A;
		pTimer->CCMR1.bit_i.IC2F = 0x0A;
	}
	else if (FilterDiv >= 64)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x09;
		pTimer->CCMR1.bit_i.IC2F = 0x09;
	}
	else if (FilterDiv >= 48)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x08;
		pTimer->CCMR1.bit_i.IC2F = 0x08;
	}
	else if (FilterDiv >= 32)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x07;
		pTimer->CCMR1.bit_i.IC2F = 0x07;
	}
	else if (FilterDiv >= 24)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x06;
		pTimer->CCMR1.bit_i.IC2F = 0x06;
	}
	else if (FilterDiv >= 16)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x05;
		pTimer->CCMR1.bit_i.IC2F = 0x05;
	}
	else if (FilterDiv >= 12)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x04;
		pTimer->CCMR1.bit_i.IC2F = 0x04;
	}
	else if (FilterDiv >= 8)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x03;
		pTimer->CCMR1.bit_i.IC2F = 0x03;
	}
	else if (FilterDiv >= 4)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x02;
		pTimer->CCMR1.bit_i.IC2F = 0x02;
	}
	else if (FilterDiv >= 2)
	{
		pTimer->CCMR1.bit_i.IC1F = 0x01;
		pTimer->CCMR1.bit_i.IC2F = 0x01;
	}
	else
	{
		pTimer->CCMR1.bit_i.IC1F = 0x00;
		pTimer->CCMR1.bit_i.IC2F = 0x00;
	}
}

