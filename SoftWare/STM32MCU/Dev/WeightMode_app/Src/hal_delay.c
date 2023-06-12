#include "hal_delay.h"
void hal_delay_us(UINT32 us)
{
	UINT32 cnt_us = us*210;//1个机器周期运行 1/210 DMIPS = 4.8ns , 1us = 4.8*210
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
