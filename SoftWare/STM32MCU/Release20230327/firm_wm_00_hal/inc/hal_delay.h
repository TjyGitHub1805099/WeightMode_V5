/**
 *******************************************************************
 * @file    hal_delay.h
 * @author  MKdriver
 * @version V1.0.0
 * @date    9-Oct-2015
 * @brief   STM32F303 延时程序头文件
 *******************************************************************
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
 *******************************************************************
 */
 
#ifndef __HAL_DELAY_H__
#define __HAL_DELAY_H__
 
#include "drv_delay.h"


/**
* \brief  US级延时函数
* \param  Nus: 延时US数最多838000us
* \return 无
*/
void __INLINE hal_delay_us( UINT32 Nus )
{
	drv_delay_us( Nus );
}

/**
* \brief  MS级延时函数
* \param  Nus: 延时US数最多838000us
* \return 无
*/
void __INLINE hal_delay_ms( UINT32 Nms )
{
	drv_delay_ms( Nms );
}

/**
* \brief  自由延时
* \param  DelayTime: 延时周期
* \return 无
*/

void __INLINE hal_delay( UINT32 DelayTime )
{
	drv_delay( DelayTime );
}


extern void hal_delay_init( void );

#endif
