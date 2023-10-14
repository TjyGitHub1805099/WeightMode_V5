#ifndef __APP_MAIN_TASK_H__
#define __APP_MAIN_TASK_H__

#include "typedefine.h"
#include "app_led_ctrl.h"
#include "stm32f4xx_it.h"

#define SYS_HX711_ONLINE_CHECK_TIME	(2000)//when power on 2000ms start check HX711  , total 3 times
#define MCU_VERSION			        (80)//2023.09.19
#define DIWEN_VERSION		        (80)//2023.09.19


extern UINT32 get_SysTick_ByTimer(void);
extern void app_main_task(void);

/*
//version 8.0 & 8.0

	
*/
#endif
