#ifndef __APP_SYSTEST_H__
#define __APP_SYSTEST_H__
#include "typedefine.h"

//============================================================================================
//========================================LED TEST START======================================
//============================================================================================
#define LED_CTRL_TEST		(FALSE)//0:close test 1:open test
extern void LedSysTest(UINT32 ms_tick);
//============================================================================================
//========================================LED TEST END======================================
//============================================================================================


//============================================================================================
//========================================T5L TEST START======================================
//============================================================================================
#define T5L_VOICE_PRITF_TEST		(FALSE)//0:close test 1:open test
#if T5L_VOICE_PRITF_TEST
extern void T5L_VoicePritfTest(UINT32 sysTick);
#endif

#define T5L_WEIGHT_COLOR_TEST		(FALSE)
#if T5L_WEIGHT_COLOR_TEST
extern void sdwe_MainFunctionTest(void)
#endif

//============================================================================================
//========================================T5L TEST END======================================
//============================================================================================

#endif
