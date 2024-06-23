#ifndef _APP_INNER_SCREEN_RX_HANDLE_C_
#define _APP_INNER_SCREEN_RX_HANDLE_C_

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
UINT8 g_u8InnerScreenVoicePrintfStatus = 0XFF;

//0
UINT8 innerScreenRxHandle_Version(T5LType *pSdwe)
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

//1
UINT8 innerScreenRxHandle_SysPassWord(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(pSdwe->SetAdd == DMG_FUNC_PASSORD_SET_ADDRESS)
	{
		STM32CheckPassWord(pSdwe->SetData);/**< 密码 */
		pSdwe->needStore |= DMG_TRIGER_SAVE_SECOTOR_2 ;
		matched = TRUE;
	}
	return matched;
}

//2
UINT8 innerScreenRxHandle_SysPara(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if((pSdwe->SetAdd >= DMG_FUNC_SET_UNIT_ADDRESS)&&(pSdwe->SetAdd <= (DMG_FUNC_DIWEN_DAPING_ADDRESS)))
	{	
		matched = TRUE;
		switch(pSdwe->SetAdd)
		{
			case DMG_FUNC_SET_UNIT_ADDRESS:		//		(0X1000)//0x1000
				gSystemPara.uint = pSdwe->SetData;/**< 单位 */
			break;
			case DMG_FUNC_SET_MIN_RANGE_ADDRESS://		(0X100A)//0x100A
				gSystemPara.minWeight = pSdwe->SetData;/**< 最小量程 */
			break;
			case  DMG_FUNC_SET_MAX_RANGE_ADDRESS://		(0X100B)//0x100B
				gSystemPara.maxWeight = pSdwe->SetData;/**< 最大量程 */
			break;
			case  DMG_FUNC_SET_ERR_RANGE_ADDRESS://		(0X100C)//0x100C
				gSystemPara.errRange = pSdwe->SetData;/**< 误差范围 */
			break;
			case  DMG_FUNC_SET_isCascade_ADDRESS://		(0X100D)//0x100D
				gSystemPara.isCascade = pSdwe->SetData;/**< 是否级联 */
			break;
			case  DMG_FUNC_SET_isLedIndicate_ADDRESS://	(0X100E)//0x100E
				gSystemPara.isLedIndicate = pSdwe->SetData;/**< 是否LED指示 */
			break;
			case  DMG_FUNC_SET_ZERO_RANGE_ADDRESS://	(0X1013)//0x1013
				gSystemPara.zeroRange = pSdwe->SetData;/**< 零点范围 */
			break;
			case DMG_FUNC_SET_SCREEN_LIGHT_ADDRESS://	(0X1014)//0x1014
				gSystemPara.ScreenLight = pSdwe->SetData;/**< 屏幕背光亮度 */
				pSdwe->sdweFreshScreenLight = TRUE;
			break;
			case DMG_FUNC_SET_VOICE_NUM_TOUCH_ADDRESS://(0X1015)//0x1015
				gSystemPara.VoiceNumTouch = pSdwe->SetData;/**< 语音大小 触控*/
			break;
			case DMG_FUNC_SET_VOICE_NUM_ADDRESS://		(0X1016)//0x1016
				gSystemPara.VoiceNum = pSdwe->SetData;/**< 语音大小 */
			break;				
			case DMG_FUNC_SET_VOICE_SWITCH_ADDRESS://	(0X1017)//0x1017
				gSystemPara.ScreenVoiceSwitch = pSdwe->SetData;/**< HX711	语音开关 */ 
			break;
			case DMG_FUNC_SET_CAST_SWITCH_ADDRESS://	(0X1018)//0x1018
				gSystemPara.ScreenCastMode = pSdwe->SetData;/**< HX711	级联显示模式 */
			break;
			case DMG_FUNC_DIWEN_XIAOSHU_ADDRESS:/**< 小数显示 0x101C*/
				gSystemPara.xiaoShuXianShi = pSdwe->SetData;
				pSdwe->sdweChangeDescriblePoint = TRUE;
				g_T5LCtx[ScreenIndex_Larger].sdweChangeDescriblePoint = TRUE;
			break;
			case DMG_FUNC_DIWEN_BILV_ADDRESS:	/**< ml与g比率 0x101D*/
				gSystemPara.mlYugBiLv = pSdwe->SetData;
			break;
			case DMG_FUNC_DIWEN_DAPING_ADDRESS:/**< 大屏显示 0x101E*/
				gSystemPara.daPinXianShi = pSdwe->SetData;
			break;
			case DMG_FUNC_DIWEN_WEIGHTNUM_ADDRESS:/**< 单台数量 0x101F*/
				gSystemPara.weightNum = pSdwe->SetData;
			break;			
			default:
				if((pSdwe->SetAdd >= DMG_FUNC_SET_COLOR_START_ADDRESS)&&(pSdwe->SetAdd <= (DMG_FUNC_SET_COLOR_END_ADDRESS)))
				{
					gSystemPara.userColorSet[pSdwe->SetAdd-DMG_FUNC_SET_COLOR_START_ADDRESS] = pSdwe->SetData;/**< 颜色1~4 */
				}
			break;
		}
		//
		pSdwe->needStore |= DMG_TRIGER_SAVE_SECOTOR_2 ;
	}
	return matched;
}

//3
UINT8 innerScreenRxHandle_JumpToBalancingClearnPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_Balancing_CLEARPAGE_SET_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_Balancing_CLEARPAGE_SET_VALUE == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpBalancing_cleanpagee = TRUE;
		}
	}
	return matched;
}

//4
UINT8 innerScreenRxHandle_JumpToBalancingHomePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_Balancing_HOME_SET_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_Balancing_HOME_SET_VALUE == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpBalancing_home = TRUE;
		}
	}
	return matched;
}

//5
UINT8 innerScreenRxHandle_JumpToBalancingPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_Balancing_SET_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_Balancing_SET_VALUE == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpToBanlingPage = TRUE;
		}
	}
	return matched;
}

//6
UINT8 innerScreenRxHandle_CalibrateChanelSet(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_SET_CHANEL_NUM == pSdwe->SetAdd)
	{
		matched = TRUE;
		pSdwe->ResetTrigerValid = FALSE;/*重新校准取消*/
		if(pSdwe->CalibrateChanel != pSdwe->SetData)
		{
			pSdwe->sdweChanelChanged = TRUE;
			if(pSdwe->SetData <= HX711_CHANEL_NUM)
			{
				pSdwe->CalibrateChanel = pSdwe->SetData;//chanel
			}
		}
	}
	return matched;
}

//7
UINT8 innerScreenRxHandle_CalibrateAddressSet(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_RESET_CALIBRATION_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_RESET_CALIBRATION_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweResetTriger = TRUE;
			pSdwe->ResetTrigerValid = TRUE;
			clearLocalCalibrationRecordData(pSdwe->CalibrateChanel);
			clearLocalCalibrationKAndBAndSample(pSdwe->CalibrateChanel);
		}
	}
	return matched;
}

//8
UINT8 innerScreenRxHandle_JumpToCalibrateOrActivePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_JUNPTO_CALIBRATION_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_JUNPTO_CALIBRATION_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpToCalitrationPage = TRUE;//jump to page 53
		}
		else if(DMG_FUNC_JUNPTO_ACTIVE_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpActivePage = TRUE;//jump to page 56
		}
	}
	return matched;
}

//9
UINT8 innerScreenRxHandle_JumpToSysParaPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_JUNPTO_SYSPAR_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_JUNPTO_SYSPAR_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpToSysParaPage = TRUE;//jump to page 52
		}
	}
	return matched;
}

//10
UINT8 innerScreenRxHandle_RemoveWeightTriger(T5LType *pSdwe)
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

//11
UINT8 innerScreenRxHandle_CalibratePointSet(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	UINT8 i = 0 , point = 0;
	INT32 weight=0;
	if((pSdwe->SetAdd >= DMG_FUNC_SET_CHANEL_POINT_ADDRESS)&&(pSdwe->SetAdd < (DMG_FUNC_SET_CHANEL_POINT_ADDRESS + CHANEL_POINT_NUM )))
	{
		matched = TRUE;
		//
		pSdwe->needStore |= DMG_TRIGER_SAVE_SECOTOR_1 ;
		//point
		pSdwe->CalibratePoint = (pSdwe->SetAdd -DMG_FUNC_SET_CHANEL_POINT_ADDRESS) ;//point
		point = pSdwe->CalibratePoint;
		pSdwe->CalibratePointArry[point] = pSdwe->SetData;
		//weight
		weight = pSdwe->SetData;
	
		if(0 == pSdwe->CalibrateChanel)//all chanel point weight value set
		{
			for(i=0;i<HX711_CHANEL_NUM;i++)//8通道
			{
				setSampleWeightValue(i,point,weight);
				pointWeightTrigerDataSet(i,point,weight);
			}
			pointWeightTrigerDataSet(i,point,weight);
		}
		else//single chanel point weight value set
		{
			setSampleWeightValue((pSdwe->CalibrateChanel-1),point,weight);
			pointWeightTrigerDataSet((pSdwe->CalibrateChanel-1),point,weight);
		}
	}
	return matched;
}

//12
UINT8 innerScreenRxHandle_CalibratePointSampleAndSet(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	UINT8 i = 0 , point = 0;
	INT32 avgSampleValue=0;
	if((TRUE == pSdwe->ResetTrigerValid)&&(pSdwe->SetAdd >= DMG_FUNC_SET_CHANEL_POINT_TRIG_ADDRESS)&&(pSdwe->SetAdd < (DMG_FUNC_SET_CHANEL_POINT_TRIG_ADDRESS + CHANEL_POINT_NUM )))
	{
		matched = TRUE;
		//value = 0x12fe
		if(DMG_FUNC_SET_CHANEL_POINT_TRIG_VAL == pSdwe->SetData)
		{
			//	
			pSdwe->sdwePointTriger = TRUE;
			//
			pSdwe->needStore |= DMG_TRIGER_SAVE_SECOTOR_1 ;
			point = ( pSdwe->SetAdd - DMG_FUNC_SET_CHANEL_POINT_TRIG_ADDRESS );
			
			if(0 == pSdwe->CalibrateChanel)//all chanel caculate	K & B
			{
				//avgSampleValue = hx711_getAvgSample(pSdwe->CalibrateChanel)/512;
				for(i=0;i<HX711_CHANEL_NUM;i++)//eight chanel
				{
					avgSampleValue = hx711_getAvgSample((enumHX711ChanelType)i)/512;
					trigerCalcKB(i,point);
					pointTrigerDataSet(i,point,1,avgSampleValue);
				}
				pointTrigerDataSet(HX711_CHANEL_NUM,point,1,avgSampleValue);
				
			}
			else if(HX711_CHANEL_NUM >= pSdwe->CalibrateChanel)//single chanel caculate  K & B
			{
				avgSampleValue = hx711_getAvgSample((enumHX711ChanelType)(pSdwe->CalibrateChanel-1))/512;
				trigerCalcKB((pSdwe->CalibrateChanel-1),point);
				pointTrigerDataSet((pSdwe->CalibrateChanel-1),point,1,avgSampleValue);
			}
			//sdwePointTrigerUpdata(point,1,avgSampleValue);
		}
	}
	return matched;
}

//13
UINT8 innerScreenRxHandle_VoicePrintfStatusFromScreen(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(pSdwe->SetAdd == DMG_SYS_STATUS_OF_VOICE_PRINTF_00A1)
	{
		matched = TRUE;
		g_u8InnerScreenVoicePrintfStatus = pSdwe->SetData;
	}
	return matched;
}

//14
UINT8 innerScreenRxHandle_SystemReset(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(pSdwe->SetAdd == SYS_SOFTWARE_RESET_ADD)
	{
		if(SYS_SOFTWARE_RESET_VLU == pSdwe->SetData)
		{
			HAL_NVIC_SystemReset();
		}
	}
	return matched;
}

//================================================================================================
//===============================[函数列表：内屏数据接收后的事件处理]================================
//================================================================================================
screenRxTxHandleType innerScreenRxHandle[SCREEN_RX_HANDLE_TOTAL_NUM]=
{
	//priority index func_add
	{0,	0, &innerScreenRxHandle_Version},//开机时MCU获取到屏幕版本时，代表屏幕可以正常通讯
	{0,	1, &innerScreenRxHandle_SysPassWord},//密码管理
	{0,	2 ,&innerScreenRxHandle_SysPara},//系统参数管理
	{0,	3, &innerScreenRxHandle_JumpToBalancingClearnPage},//配平清爽界面
	{0,	4, &innerScreenRxHandle_JumpToBalancingHomePage},//配平主界面界面 ， 它与清爽界面来会切换，当点击屏幕时
	{0,	5, &innerScreenRxHandle_JumpToBalancingPage},//配平界面 ， 其他界面跳回配平界面时用
	{0,	6, &innerScreenRxHandle_CalibrateChanelSet},//校准界面 ，通道号设置
	{0,	7 ,&innerScreenRxHandle_CalibrateAddressSet},//校准界面 ，地址设置
	{0,	8 ,&innerScreenRxHandle_JumpToCalibrateOrActivePage},//跳转校准界面
	{0,	9, &innerScreenRxHandle_JumpToSysParaPage},//跳转系统参数设置界面
	{0,	10,&innerScreenRxHandle_RemoveWeightTriger},//去皮事件触发
	{0,	11,&innerScreenRxHandle_CalibratePointSet},//校准界面，校准点参考值设置
	{0,	12,&innerScreenRxHandle_CalibratePointSampleAndSet},//校准界面，校准点采样及设置
	{0,	13,&innerScreenRxHandle_VoicePrintfStatusFromScreen},//屏幕语音控制后状态返回
	{0,	14,&innerScreenRxHandle_SystemReset},//屏幕语音控制后状态返回
};

#endif//end of _APP_INNER_SCREEN_RX_HANDLE_C_
