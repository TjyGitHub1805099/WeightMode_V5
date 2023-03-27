/**
  *******************************************************************
  * @file    hal_delay.c
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x延时程序C文件
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


static UINT16 g_DelayUsFac;
static UINT16 g_DelayMsFac;

/**
 * \brief  延时模块初始化
 * \return 无
 */
void drv_delay_init( void )
{
	SysTick->CTRL.bit.CLKSOURCE = 0;												// 选择外部时钟源  
	g_DelayUsFac = (UINT16)( ( g_ClockFrequency.AhbFreq / 1000000 ) / 8 ); 			// 1US计算的脉冲个数  
	g_DelayMsFac = (UINT16)( g_DelayUsFac * 1000 );									// 1MS计算的脉冲个数  
}

/**
* \brief  US级延时函数
* \param  Nus: 延时US数最多838000us
* \return 无
*/
void drv_delay_us( UINT32 Nus )
{
	UINT32 l_Temp;
	SysTick->LOAD = Nus * g_DelayUsFac;											// 装载值   
	SysTick->VAL = 0x00;														// 清当前计数器  
	SysTick->CTRL.bit.ENABLE = 1;												// 使能，开始计数  
	do
	{
		l_Temp = SysTick->CTRL.all;

	} while( ( l_Temp & 0x01 ) && ( !( l_Temp & 0x00010000 ) ) );				// (Bit0 == 1 && Bit16 != 1),等待Bit16 == 1时间到  

	SysTick->CTRL.all = 0x00;													// 清控制寄存器  
	SysTick->VAL = 0x00;														// 清计数器寄存器  
}

/**
* \brief  MS级延时函数
* \param  Nms: 延时MS数,最多838ms
* \return 无
*/
void drv_delay_ms( UINT32 Nms )
{
	UINT32 l_Temp;
	SysTick->LOAD = Nms * g_DelayMsFac;											// 装载值   
	SysTick->VAL = 0x00;														// 清当前计数器  
	SysTick->CTRL.bit.ENABLE = 1;												// 使能，开始计数  
	do
	{
		l_Temp = SysTick->CTRL.all;

	} while( ( l_Temp & 0x01 ) && ( !( l_Temp & 0x00010000 ) ) );				// (Bit0 == 1 && Bit16 != 1),等待Bit16 == 1时间到  

	SysTick->CTRL.all = 0x00;													// 清控制寄存器  
	SysTick->VAL = 0x00;														// 清计数器寄存器  
}

/**
* \brief  自由延时
* \param  DelayTime: 延时周期
* \return 无
*/
void drv_delay( UINT32 DelayTime )
{
	while( DelayTime-- );
}
