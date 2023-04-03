/**
  *******************************************************************
  * @file    hal_delay.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x 延时程序头文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#ifndef __DRV_DELAY_H__
#define __DRV_DELAY_H__

#include "reg_stm32f303_systick.h"


extern void drv_delay_init( void );
extern void drv_delay_us( UINT32 Nus );
extern void drv_delay_ms( UINT32 Nms );
extern void drv_delay( UINT32 DelayTime );


#endif
