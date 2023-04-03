/**
*******************************************************************
* @file    drv_iwdg.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x IWDG模块驱动程序
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#include "drv_iwdg.h"

/**
* @brief  初始化IWDG看门狗.
* @note   初始化后即被启动.
* @param  MsTime: 毫秒级定时周期，最大值4095(bit0~bit11)
* @retval 无
*/
void drv_iwdg_init( UINT32 MsTime )
{
	
	IWDG->KR = IWDG_ACESS_VALUE;					// 允许寄存器访问权限
	IWDG->PR.bit.PR = IWDG_PR_PRESCAL_32;			// 32分频，1ms计数一次 
	IWDG->RLR.all = MsTime;							// 喂狗最大周期 
	IWDG->KR = IWDG_ENABLE_VALUE;					// 启动看门狗 
}

