/**
  *******************************************************************
  * @file    drv_nvic.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40xNVIC模块驱动程序头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
  
#ifndef __DRV_NVIC_H__
#define __DRV_NVIC_H__

#include "Stm32F303xC_Vect_Tab.h"
#include "reg_stm32f303_nvic.h"


#define AIRCR_VECTKEY_MASK    		 ((UINT32)0x05FA0000)


#define NVIC_PriorityGroup_0         ((UINT32)0x700) 
#define NVIC_PriorityGroup_1         ((UINT32)0x600) 
#define NVIC_PriorityGroup_2         ((UINT32)0x500) 
#define NVIC_PriorityGroup_3         ((UINT32)0x400) 
#define NVIC_PriorityGroup_4         ((UINT32)0x300) 


extern void drv_nvic_init( UINT8 NvicIrqChannel, UINT8 PreemPriority, UINT8 SubPriority );
extern void drv_nvic_enable(UINT8 IrqChannel);
extern void drv_nvic_disable(UINT8 IrqChannel);


#endif
