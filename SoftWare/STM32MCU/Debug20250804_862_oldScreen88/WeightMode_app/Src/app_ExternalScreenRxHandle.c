#ifndef _APP_EXTERNAL_SCREEN_RX_HANDLE_C_
#define _APP_EXTERNAL_SCREEN_RX_HANDLE_C_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app_main_task.h"
#include "app_sdwe_ctrl.h"
#include "app_crc.h"
#include "app_hx711_ctrl.h"
#include "app_crc.h"
#include "hal_delay.h"
#include "app_modbus_rtu_ctrl.h"
#include "app_syspara.h"
#include "app_t5l_ctrl.h"
#include "app_password.h"
#include "app_t5l_cfg.h"

//屏幕语音播报状态
UINT8 g_u8ExternalScreenVoicePrintfStatus = 0XFF;

//
UINT8 externalScreenRxHandle_Version(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_SYS_VERSION_GET_ADD == pSdwe->SetAdd)
	{
		pSdwe->sdwePowerOn = TRUE;//if recived version , indicate allready power on
		t5lDisPlayDataClear();
		matched = TRUE;
	}
	return matched;
}

//
UINT8 externalScreenRxHandle_RemoveWeightTriger(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	T5LType *pSdweSmaller = &g_T5LCtx[ScreenIndex_Smaller];
	if(DMG_FUNC_REMOVE_WEIGHT_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_REMOVE_WEIGHT_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweRemoveWeightTriger = TRUE;
			pSdweSmaller->sdweRemoveWeightTriger = TRUE;
			//
			setModbusSelfRemoveFlag(TRUE);
		}
	}
	return matched;
}

//================================================================================================
//===============================[函数列表：外屏数据接收后的事件处理]================================
//================================================================================================
screenRxTxHandleType externalScreenRxHandle[SCREEN_LARGER_RX_HANDLE_TOTAL_NUM]=
{
	//priority index func_add
	{0,	0, &externalScreenRxHandle_Version},//开机时MCU获取到屏幕版本时，代表屏幕可以正常通讯
	{0,	1, &externalScreenRxHandle_RemoveWeightTriger},//去皮事件触发
};
#endif//end of _APP_EXTERNAL_SCREEN_RX_HANDLE_C_
