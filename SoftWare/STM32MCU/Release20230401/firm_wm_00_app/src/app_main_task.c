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
#include "drv_iwdg.h"

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
void app_main_task()
{
	UINT8 hx711DataUpgrade = 0 ;
	(void)hx711DataUpgrade;
	
	drv_iwdg_feed();

	
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
	
	#if (TRUE == COLOR_ALT_20210328_DEFINE)
		useWeightUpdataOutColor(hx711DataUpgrade);
	#endif	
	
	#if (TRUE == COLOR_ALT_20210414_DEFINE)
		useWeightUpdataOutColor_20210414(hx711DataUpgrade);
	#endif

	#if (TRUE == COLOR_ALT_20210606_DEFINE)
		useWeightUpdataOutColor_20210606(hx711DataUpgrade);
	#endif

	//LED control test
	#if (TRUE == LED_CTRL_TEST)
		LedSysTest(g_sys_ms_tick);
	#endif

	//T5L Screen Voice Pritf test
	#if (TRUE == T5L_VOICE_PRITF_TEST)
		T5L_VoicePritfTest(g_sys_ms_tick);
	#endif

	#if (TRUE == T5L_WEIGHT_COLOR_TEST)
		sdwe_MainFunctionTest();
	#endif

	//data comm contrl mainfunction
	ModbusRtu_MainFunction();
	
	//T5L contrl mainfunction
	sreenT5L_MainFunction();

	//led contrl mainfunction
	led_MainFunction();
	
}

