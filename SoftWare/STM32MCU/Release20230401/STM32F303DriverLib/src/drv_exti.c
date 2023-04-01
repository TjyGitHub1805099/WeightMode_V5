/**
*******************************************************************
* @file    drv_exti.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40xEXTI模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#include "drv_exti.h"

/**
* @brief  EXTI外设寄存器值恢复默认值.
* @retval 无
*/
void drv_exti_deinit( void )
{ 
	EXTI->IMR1.all	= 0x1F800000;
	EXTI->EMR1.all	= 0x00000000;
	EXTI->FTSR1.all	= 0x00000000;
	EXTI->RTSR1.all	= 0x00000000;
	EXTI->SWIER1.all = 0x00000000;
	EXTI->PR1.all	= 0xFFFFFFFF;
	EXTI->IMR2.all	= 0xFFFFFFFC;
	EXTI->EMR2.all	= 0x00000000;
	EXTI->FTSR2.all	= 0x00000000;
	EXTI->RTSR2.all	= 0x00000000;
	EXTI->SWIER2.all = 0x00000000;
	EXTI->PR2.all	= 0x00000003;
}

/**
* @brief  初始化 EXTI 外设
* @param  ExtiLine: 外部中断线
* @param  ExtiMode: 外部中断模式
* @param  ExtiTrigEdge: 外部中断沿
* @retval 无
*/
void drv_exti_init( UINT32 ExtiLine, EnumExtiTrigEdgeType ExtiTrigEdge )
{
	UINT8 l_RegPos = 0;
	
	if(( ExtiLine & 0x10000000 ) != 0 )
	{
		l_RegPos = 1;		//在REG2上
	}
	else
	{
		l_RegPos = 0;
	}
	if( ExtiTrigEdge == EXTI_TRIGGER_RISING_FALLING )
		{								//上升沿 下降沿都触发
		if( l_RegPos == 1 )
		{
			EXTI->FTSR2.all |= ExtiLine;
			EXTI->RTSR2.all |= ExtiLine;
		}
		else
		{
			EXTI->FTSR1.all |= ExtiLine;
			EXTI->RTSR1.all |= ExtiLine;
		}
	}
	else if( ExtiTrigEdge == EXTI_TRIGGER_RISING )
	{									//上升沿触发
		if( l_RegPos == 1 )
		{
			EXTI->RTSR2.all |= ExtiLine;
		}
		else
		{
			EXTI->RTSR1.all |= ExtiLine;
		}
	}
	else
	{									//下降沿触发
		if( l_RegPos == 1 )
		{
			EXTI->FTSR2.all |= ExtiLine;
		}
		else
		{
			EXTI->FTSR1.all |= ExtiLine;
		}
	}
}

/**
* @brief  使能 EXTI 外设中断
* @param  ExtiLine: 外部中断线
* @retval 无
*/
void drv_exti_enable( UINT32 ExtiLine, EnumExtiModeType ExtiMode )
{ 
	UINT8 l_RegPos = 0;
	
	if(( ExtiLine & 0x10000000 ) != 0 )
	{
		l_RegPos = 1;		//在REG2上
	}
	else
	{
		l_RegPos = 0;
	}
	if( ExtiMode == EXTI_MODE_INTERRUPT )
	{
		if( l_RegPos == 1 )
		{
			EXTI->IMR2.all |= ExtiLine;
		}
		else
		{
			EXTI->IMR1.all |= ExtiLine;
		}
	}
	else
	{
		if( l_RegPos == 1 )
		{
			EXTI->EMR2.all |= ExtiLine;
		}
		else
		{
			EXTI->EMR1.all |= ExtiLine;
		}
	}
}

/**
* @brief  禁止 EXTI 外设中断
* @param  ExtiLine: 外部中断线
* @retval 无
*/
void drv_exti_disable( UINT32 ExtiLine, EnumExtiModeType ExtiMode )
{
	UINT8 l_RegPos = 0;
	
	if(( ExtiLine & 0x10000000 ) != 0 )
	{
		l_RegPos = 1;		//在REG2上
	}
	else
	{
		l_RegPos = 0;
	}
	if( ExtiMode == EXTI_MODE_INTERRUPT )
	{
		if( l_RegPos == 1 )
		{
			EXTI->IMR2.all &= (UINT32)~ExtiLine;
		}
		else
		{
			EXTI->IMR1.all &= (UINT32)~ExtiLine;
		}
	}
	else
	{
		if( l_RegPos == 1 )
		{
			EXTI->EMR2.all |= (UINT32)~ExtiLine;
		}
		else
		{
			EXTI->EMR1.all |= (UINT32)~ExtiLine;
		}
	}
}

/**
* @brief  检查外部中断线状态标志.
* @param  ExtiLine: 外部中断线
* @retval 新状态.
*/
FlagStatus drv_exti_get_flag_status( UINT32 ExtiLine )
{
	ExtiPr1Type l_Pr;
	
	if(( ExtiLine & 0x10000000 ) != 0 )
	{	
		l_Pr.all = EXTI->PR2.all;	//在REG2上
	}
	else
	{
		l_Pr.all = EXTI->PR1.all;
	}
	 
	if(( l_Pr.all & ExtiLine ) != 0 )
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清外部中断线状态标志.
* @param  ExtiLine: 外部中断线
* @retval 无
*/
void drv_exti_clear_flag_status( UINT32 ExtiLine )
{ 
	if(( ExtiLine & 0x10000000 ) != 0 )
	{	
		EXTI->PR2.all |= ExtiLine;		//在REG2上	写1清0
	}
	else
	{
		EXTI->PR1.all |= ExtiLine;	
	}
}

/**
* @brief  检查外部中断线中断标志.
* @param  ExtiLine: 外部中断线
* @retval 新状态.
*/
ITStatus drv_exti_get_it_status( UINT32 ExtiLine )
{
	if(( ExtiLine & 0x10000000 ) != 0 )
	{	
		if(( EXTI->PR2.all & ExtiLine ) != 0 )		//在REG2上
		{
			return SET;
		}
		else
		{
			return RESET;
		}
	}
	else
	{
		if(( EXTI->PR2.all & ExtiLine ) != 0 )
		{
			return SET;
		}
		else
		{
			return RESET;
		}
	}
}

/**
* @brief  清外部中断线中断挂起标志.
* @param  ExtiLine: 外部中断线
* @retval 无
*/
void drv_exti_clear_it_pending_bit( UINT32 ExtiLine )
{ 
	if(( ExtiLine & 0x10000000 ) != 0 )
	{	
		EXTI->PR2.all |= ExtiLine;		//在REG2上	写1清0
	}
	else
	{
		EXTI->PR1.all |= ExtiLine;	
	}
}

