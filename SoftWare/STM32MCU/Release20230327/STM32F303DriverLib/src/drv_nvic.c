/**
  *******************************************************************
  * @file    drv_nvic.c
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40xNVIC模块驱动程序C文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#include "drv_nvic.h"

/**
  * @brief  NVIC配置函数
  * @param  IrqChannel: 配置的中断矢量
  * @param  PreemPriority: 抢占优先级
  * @param  SubPriority: 响应优先级
  * @retval 无
  */
void drv_nvic_init( UINT8 IrqChannel, UINT8 PreemPriority, UINT8 SubPriority )
{
	UINT8 tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

	tmppriority = ( 0x700 - ( ( SCB->AIRCR ) & (UINT32)0x700 ) ) >> 0x08;
	tmppre = ( 0x4 - tmppriority );
	tmpsub = tmpsub >> tmppriority;

	tmppriority = PreemPriority << tmppre;
	tmppriority |= (UINT8)( SubPriority & tmpsub );

	tmppriority = tmppriority << 0x04;

	NVIC->IP[IrqChannel] = tmppriority;
}

/**
* @brief  NVIC使能
* @param  IrqChannel: 配置的中断矢量
* @retval 无
*/
void drv_nvic_enable( UINT8 IrqChannel )
{
	NVIC->ISER[IrqChannel >> 0x05].all = (UINT32)0x01 << ( IrqChannel & (UINT8)0x1F );
}

/**
* @brief  NVIC禁止
* @param  IrqChannel: 配置的中断矢量
* @retval 无
*/
void drv_nvic_disable( UINT8 IrqChannel )
{
	NVIC->ICER[IrqChannel >> 0x05].all = (UINT32)0x01 << ( IrqChannel & (UINT8)0x1F );
}
