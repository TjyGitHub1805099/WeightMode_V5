#include "hal_delay.h"
#include "stm32f4xx_it.h"
#include "app_main_task.h"
void hal_delay_us(UINT32 us)
{
	UINT32 cnt_us = us*40;//1个机器周期运行 1/210 DMIPS = 4.8ns , 1us = 4.8*210
	while(cnt_us > 0)
	{
    	cnt_us--;
	}
}
void hal_delay_ms( UINT32 Nms )
{
	while(Nms > 0)
	{
		Nms--;
		hal_delay_us(1000);
	}
}
void hal_delay_ms_use_sys_tick(UINT32 Nms)
{
	volatile UINT32 curMs = get_SysTick_ByTimer();
	while((get_SysTick_ByTimer() - curMs) < Nms)
	{
		curMs = get_SysTick_ByTimer();
	}
}
