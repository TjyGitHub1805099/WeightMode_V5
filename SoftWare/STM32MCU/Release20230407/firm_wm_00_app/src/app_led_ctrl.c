/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "hal_gpio.h"
#include "app_led_ctrl.h"
#include "app_hx711_ctrl.h"
#include "app_sdwe_ctrl.h"
#include "app_main_task.h"
#include "app_crc.h"
#include "app_syspara.h"
#include "app_t5l_ctrl.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
UINT8 g_led_ctrl_data[LED_CTRL_DATA_LEN]={0};

/*******************************************************************************
 * Functions
 ******************************************************************************/
//==led delay
void Led_delay( UINT32 TIME )
{
	while(TIME>0)
	{
		TIME--;
	}
}
//==led send pulse
void LedCtrlSendPulse(enumDoLineType offset,UINT8 type)
{
		UINT8 TIME = 100;
		if(1==type)//rising
		{
			hal_gpio_set_do_low( offset );
			Led_delay( TIME );
			hal_gpio_set_do_high( offset );
			Led_delay( TIME );
			hal_gpio_set_do_low( offset );
			Led_delay( TIME );
		}
		else//falling
		{
			hal_gpio_set_do_high( offset );
			Led_delay( TIME );
			hal_gpio_set_do_low( offset );
			Led_delay( TIME );
			hal_gpio_set_do_high( offset );
			Led_delay( TIME );
		}
}
//==led mode init
void led_init(void)
{
	//default LED output
	hal_gpio_set_do_high( LED_DO_SER0 );
	hal_gpio_set_do_high( LED_DO_OE );//disable LED OUT
	hal_gpio_set_do_low( LED_DO_RCLK );//init CLK = high
	hal_gpio_set_do_low( LED_DO_SRCLK );//init LOCK CLK = high
	hal_gpio_set_do_low( LED_DO_SRCLR );//clear ALL LED shift regester

	//1rd:disable LED output
	hal_gpio_set_do_high( LED_DO_OE );

	//2nd:clear all shift reg = 0
	LedCtrlSendPulse(LED_DO_SRCLR,0);

	//2rd:lock data form shift reg to store reg
	LedCtrlSendPulse(LED_DO_RCLK,1);

	//4th:enable LED output
	hal_gpio_set_do_low( LED_DO_OE );
}
//==set LED light 
UINT8 LedDataSet(enumLedSeqType seq , enumLedColorType color)
{	
	UINT8 ret = 0 ;//1:success
	UINT8 cloorData = 0 ;
	UINT8 offset = 0 ;//数组偏移
	UINT8 lsb_flag = 0;//低4位 or 高4位
	UINT8 l_data = 0;
	
	//color judge
	switch(color)
	{
		case LED_COLOR_REG:		cloorData = 0x01;/**< LED 红 控制 */
		break;
		case LED_COLOR_WHITE:	cloorData = 0x08;/**< LED 白 控制 */
		break;
		case LED_COLOR_BLUE:	cloorData = 0x04;/**< LED 蓝 控制 */
		break;
		case LED_COLOR_GREEN:	cloorData = 0x02;/**< LED 绿 控制 */	
		break;
		default :			 	cloorData = 0x00;/**< LED    控制 */
		break;
	}
	
	//data change
	if(seq<LED_SEQ_NUM)
	{
		//arry offset
		offset = (LED_SEQ_NUM - 1 - seq)/2;
		l_data = g_led_ctrl_data[offset];
		
		if( offset < LED_CTRL_DATA_LEN )
		{
			//lsb or msb
			lsb_flag = 	(LED_SEQ_NUM - 1 - seq)%2;

			if(0 == lsb_flag)//low 4 bits
			{
				l_data &= 0xf0;
				l_data |= cloorData;
			}
			else//high 4 bits
			{
				l_data &= 0x0f;
				l_data |= ((cloorData<<4)&0xf0);
			}
			
			//
			g_led_ctrl_data[offset] = l_data;
			ret = 1;
		}
	}
	return ret;
}
void balaningColorClear(void)
{
	UINT8 color_i = 0 ;
	for(color_i=0;color_i<LED_SEQ_NUM;color_i++)
	{
		LedDataSet((enumLedSeqType)color_i,LED_COLOR_NONE);
	}
}

//==led cycle contrl
void led_MainFunction(void)
{
	static UINT8 led_data[LED_CTRL_DATA_LEN]={0};
	UINT8 *pData=&g_led_ctrl_data[0];
	UINT8 i = 0,j = 0,set = 0,l_data = 0;
	//led indicate was open
	if(1 == gSystemPara.isLedIndicate)
	{
		//if weight data changed
		//if(1 == hx711DataUpgrade)
		{	
			//check data change and store g_led_ctrl_data
			for(i=0;i<LED_CTRL_DATA_LEN;i++)
			{
				if(led_data[i] != pData[i])
				{
					led_data[i] = pData[i];
					set = 1;
				}
			}
			
			//if data changed
			if(1 == set)
			{
				for(i=0;i<LED_CTRL_DATA_LEN;i++)//byte
				{
					l_data = led_data[i];	
					for(j=0;j<8;j++)//8 bit
					{		
						//set SER
						if(0x01 == (l_data&0x01))
						{
							hal_gpio_set_do_high( LED_DO_SER0 );
						}
						else
						{
							hal_gpio_set_do_low( LED_DO_SER0 );
						}
						l_data>>=1;
			
						//send SCK shift data
						LedCtrlSendPulse( LED_DO_SRCLK ,1); 
					}		
				}
				
				//send RCK lock data
				LedCtrlSendPulse( LED_DO_RCLK ,1);	
			}
		}
	}
}
