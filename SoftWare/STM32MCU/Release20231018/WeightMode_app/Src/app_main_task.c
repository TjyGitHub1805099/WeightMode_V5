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
}
//==sys main function
void app_main_task(void)
{
	//feed watch dog
	//drv_iwdg_feed();

	//sys tick add
	g_sys_ms_tick++;

	//app power on init
	app_main_init();

	//KEY sample and filter
	key_MainFunction();

	//HX711 when power on exe senser check and remove weight and calculate avgSampleValue and weight
	hx711_MainFunction();

	//LED control test
	#if (TRUE == LED_CTRL_TEST)
		LedSysTest(g_sys_ms_tick);
	#endif
	
	//i2c test
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

	//data comm contrl mainfunction
	ModbusRtu_MainFunction();
	
	//T5L contrl mainfunction
	sreenT5L_MainFunction();

	//led contrl mainfunction
	led_MainFunction();
}

