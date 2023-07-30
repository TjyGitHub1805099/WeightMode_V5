/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "hal_gpio.h"
#include "app_led_ctrl.h"
#include "app_hx711_ctrl.h"
#include "app_main_task.h"
#include "app_key_ctrl.h"
#include "app_sdwe_ctrl.h"
#include "app_modbus_rtu_ctrl.h"
#include "app_t5l_ctrl.h"
#include "app_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
//sys main task status
UINT32 g_sys_ms_tick = 0 ;

/*******************************************************************************
 * Functions
 ******************************************************************************/
//==sys main init function
void app_main_init(void)
{
	//after power up 3.3 seconds clear all weight
	static UINT8 removeWeight = TRUE;
	if((TRUE == removeWeight)&&(g_sys_ms_tick >= SYS_REMOVE_WEIGHT_TIME))
	{
		removeWeight = FALSE;
		hx711_setAllRemoveWeight();
		t5lDisPlayDataClear();
	}
}
//==sys main function
void app_main_task(void)
{
	static UINT8 test = 0 ;
	UINT8 hx711DataUpgrade = 0 ;
	(void)hx711DataUpgrade;

	//feed watch dog
	//drv_iwdg_feed();

	//sys tick add
	g_sys_ms_tick++;

	//app power on init
	app_main_init();

	//KEY sample and filter
	key_MainFunction();

	//HX711 sanple and calculate avgSampleValue and weight
	if(1 == hx711_SenserCheck())
	{
		hx711DataUpgrade = hx711_MainFunction();
	}
	
	//LED control test
	#if (TRUE == LED_CTRL_TEST)
		LedSysTest(g_sys_ms_tick);
	#endif
	
	#ifdef EXT_EEPROM_TEST_EN
		app_i2c_test();
	#endif

	//T5L Screen Voice Pritf test
	#if (TRUE == T5L_VOICE_PRITF_TEST)
		T5L_VoicePritfTest(g_sys_ms_tick);
	#endif

	#if (TRUE == T5L_WEIGHT_COLOR_TEST)
		sdwe_MainFunctionTest();
	#endif
#if 1
	//data comm contrl mainfunction
	ModbusRtu_MainFunction();
	
	//T5L contrl mainfunction
	sreenT5L_MainFunction();
#endif
	//led contrl mainfunction
	led_MainFunction();
	




	//if(g_sys_ms_tick%1000 ==0)
	if(get_SysTick_ByTimer()%1000 ==0)
	{
		if(test)
		{
			test = 0 ;
			hal_gpio_set_do_high( (enumDoLineType)(SYS_RUN0) );
			test = 0 ;
		}
		else
		{
			hal_gpio_set_do_low( (enumDoLineType)(SYS_RUN0) );
			test = 1;
		}
	}

}

