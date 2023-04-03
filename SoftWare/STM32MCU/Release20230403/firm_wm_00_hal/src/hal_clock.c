/**
  *******************************************************************
  * @file    drv_clock.c
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x时钟模块驱动程序C文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
  

#include "drv_rcc.h"
#include "hal_clock.h"

/**
 * @brief  系统时钟初始化
 * @param  VectStartAddress: 中断向量表开始地址，根据具体应用情况设置不同的值
 * @retval 无
 */
void hal_clock_init( UINT32 VectStartAddress )
{
	drv_rcc_init( 0, 8, 72, APB1_PRESC_1, APB2_PRESC_1, VectStartAddress );
}
