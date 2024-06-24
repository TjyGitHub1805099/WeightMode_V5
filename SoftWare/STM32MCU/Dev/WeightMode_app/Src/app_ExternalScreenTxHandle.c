#ifndef _APP_EXTERNAL_SCREEN_TX_HANDLE_C_
#define _APP_EXTERNAL_SCREEN_TX_HANDLE_C_
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
#include "app_BalancingDataHandle.h"

//外屏初始化
UINT8 externalScreenTxHandle_Init(T5LType *pSdwe)
{
	UINT8 result = FALSE ;
	INT16 sendData[64],len=0,i;
	switch(pSdwe->sendSysParaDataToDiwenIndex)
	{
		case 0x80://获取系统版本 若获取回则代表 屏已上电
			if(FALSE == pSdwe->sdwePowerOn)
			{
				if(0 == (pSdwe->CurTick %100))//every 500ms send order to get version
				{
					screenPublic_ScreenVersionGet(pSdwe);
				}
			}
			else
			{
				pSdwe->sendSysParaDataToDiwenIndex = 0x81;
			}
		break;
		case 0x81://发送【托盘重量显示的描述指针】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_WeightVlu(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		case 0x82://发送【托盘序号显示的描述指针】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_WeightIndex(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		case 0x83://发送【托盘重量背景色显示的描述指针】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_WeightColor(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		case 0x84://发送【帮组模块显示的描述指针】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_HelpVlu(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		case 0x85://发送【MISC】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_OtherMisc(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;		
		case 0x86:
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{	
				len = T5L_MAX_CHANEL_LEN;
				for(i=0;i<len;i++)
				{
					sendData[i]=i+1;
				}	
				t5lWriteVarible(pSdwe,(0x3901),sendData,len,0);
				pSdwe->sendSysParaDataToDiwenIndex = 0;
			}
		break;

		case 0://send screen light
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				screenPublic_ScreenLight(pSdwe);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 1://send weight data to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<(2*T5L_MAX_CHANEL_LEN);len++)//每个通道是4字节变量
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,sendData,len,0);/**< 通道重量 */
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 2://send back color to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<T5L_MAX_CHANEL_LEN;len++)
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,sendData,len,0);/**< 通道背景色 */  //3100
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 3://send help data to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<DIFF_TO_DIWEN_DATA_LEN;len++)
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS,sendData,len,0);/**< 通道差值，帮助信息 */  //1201
				pSdwe->sendSysParaDataToDiwenIndex = 7;
			}
		break;
		case 7://send 0x1000 单位
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				sendData[len++] = gSystemPara.uint;
				t5lWriteVarible(pSdwe,(0x1000),sendData,len,0);		/**< 单位：ml/g */ 				//1000
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 8://send 0X100A~0X101F 系统参数
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len = 0 ;
				sendData[len++] = gSystemPara.minWeight;		/**< 最小量程 */ 				//100A
				sendData[len++] = gSystemPara.maxWeight;		/**< 最大量程 */ 				//100B
				sendData[len++] = gSystemPara.errRange;			/**< 误差范围 */ 				//100C
				sendData[len++] = gSystemPara.isCascade;		/**< 是否级联 */ 				//100D
				sendData[len++] = gSystemPara.isLedIndicate;  	/**< 是否LED指示 */ 			//100E
				sendData[len++] = gSystemPara.userColorSet[0];	/**< 配平色1 */ 				//100F
				sendData[len++] = gSystemPara.userColorSet[1];	/**< 配平色2 */ 				//1010
				sendData[len++] = gSystemPara.userColorSet[2];	/**< 配平色3 */ 				//1011
				sendData[len++] = gSystemPara.userColorSet[3];	/**< 配平色4 */ 				//1012
				sendData[len++] = gSystemPara.zeroRange;		/**< 零点范围 */ 				//1013
				sendData[len++] = gSystemPara.ScreenLight;		/**< 正常亮度 */ 				//1014
#if 0				
				sendData[len++] = 25;							/**< 待机亮度 */ 				//1015
				sendData[len++] = 300;							/**< 待机时间 */ 				//1016
#else
				sendData[len++] = gSystemPara.VoiceNumTouch;	/**< 音量大小 触控*/ 			//1015
				sendData[len++] = gSystemPara.VoiceNum;			/**< 音量大小 */ 			    //1016
#endif				
				sendData[len++] = gSystemPara.ScreenVoiceSwitch;/**< HX711	语音开关 */ 		//1017
				sendData[len++] = gSystemPara.ScreenCastMode;	/**< HX711	级联显示模式 */ 	//1018
				sendData[len++] = gSystemPara.FlashEraseTimes;	/**< HX711	FLASH 擦写次数 */ 	//1019
				sendData[len++] = MCU_VERSION;					/**< MCU 版本 */ 				//101A
				sendData[len++] = DIWEN_VERSION;				/**< DIVEN 版本 */ 				//101B
				
				sendData[len++] = gSystemPara.xiaoShuXianShi;	/**< 小数显示 0x101c*/			//101C
				sendData[len++] = gSystemPara.mlYugBiLv;		/**< ml与g比率 0x101d*/			//101D
				sendData[len++] = gSystemPara.daPinXianShi;		/**< 大屏显示 0x101e*/			//101E
				sendData[len++] = gSystemPara.weightNum;		/**< 单台数量 0x101f*/			//101F

				t5lWriteVarible(pSdwe,(0x100A),sendData,len,0);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		default:
			if(TRUE == pSdwe->sdweHX711FirstSampleCoplt)
			{
				pSdwe->sdweJumpToBanlingPage = TRUE;//触发跳转至配平界面
				result = TRUE;
			}
		break;
	}
	return result;
}

//0外屏初始化 事件处理
UINT8 externalScreenTxHandle_ScreenInit(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(T5L_INITIAL_COMPLETE != pSdwe->sendSdweInit)
	{
		matched = TRUE;
		if(TRUE == externalScreenTxHandle_Init(pSdwe))
		{
			pSdwe->sendSdweInit = T5L_INITIAL_COMPLETE;
		}
	}
	return matched;
}

//1
UINT8 externalScreenTxHandle_JumpToBanlingPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToBanlingPage)
	{
		matched = TRUE;
		if(0 != gSystemPara.isCascade)
		{
			pSdwe->screenBanlingPageNum = 2;
		}
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenBanlingPageNum))
		{
			pSdwe->sdweJumpToBanlingPage = FALSE;
		}
	}
	return matched;
}

//2
UINT8 externalScreenTxHandle_ChangeDisplayPosition(T5LType *pSdwe)
{
	#if 0
	UINT8 matched = FALSE;
	static UINT8 changeHelpInfoDisp = FALSE;

	//
	if(TRUE == pSdwe->sdweChangeDescriblePoint)
	{
		matched = TRUE;
		if(FALSE == changeHelpInfoDisp)//先修改重量单元的描述指针
		{
			if(0 != screenPublic_FreshDisplayPosition_Of_WeightVlu(pSdwe))
			{
				changeHelpInfoDisp = TRUE;
			}
		}
		else//在修改帮助信息的描述指针
		{
			if(0 != screenPublic_FreshDisplayPosition_Of_HelpVlu(pSdwe))
			{
				changeHelpInfoDisp = FALSE;
				//
				pSdwe->sdweChangeDescriblePoint = FALSE;
				matched = FALSE;
			}
		}
	}
	return matched;
	#endif
		UINT8 matched = FALSE;
	//
	if(TRUE == pSdwe->sdweChangeDescriblePoint)
	{
		matched = TRUE;
		if(0 == pSdwe->freshDP)//先修改重量单元的描述指针
		{
			if(0 != screenPublic_FreshDisplayPosition_Of_WeightVlu(pSdwe))
			{
				pSdwe->freshDP = 1;
			}
		}
		else if(1 == pSdwe->freshDP)//其次修改帮助信息的描述指针
		{
			if(0 != screenPublic_FreshDisplayPosition_Of_HelpVlu(pSdwe))
			{
				pSdwe->freshDP = 2;
			}
			
		}
		else if(2 == pSdwe->freshDP)//其次修改帮助信息的描述指针
		{
			if(0 != screenPublic_FreshDisplayPosition_Of_WeightIndex(pSdwe))
			{
				pSdwe->freshDP = 3;
			}
		}
		else if(3 == pSdwe->freshDP)//修改文本信息： 单位 精度
		{
			if(0 != screenPublic_FreshDisplayPosition_Of_OtherMisc(pSdwe))
			{
				pSdwe->freshDP = 0;
				//
				pSdwe->sdweChangeDescriblePoint = FALSE;
				matched = FALSE;
			}
		}
		else
		{
			/*nothing*/
			pSdwe->freshDP = 0 ;
		}
	}
	return matched;
}

//3
UINT8 externalScreenTxHandle_ScreenWeightAndColorAndHelpHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(g_sysLocked == STM32MCU_UNLOCKED)
	{
		matched = TRUE;
		#if (0 == SCREEN_BALANCINGDATA_HANDLE_MODE)
			screenPublic_sendBalancingWeightAndColor(pSdwe);
			screenPublic_HelpDataMainFunction(pSdwe);
			//screenPublic_VoicePrintfMainfunction(pSdwe);
		#else
			BalancingData_WeightData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
			BalancingData_ColorData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
			BalancingData_HelpData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
			//screenPublic_VoicePrintfMainfunction(pSdwe);
		#endif
	}	
	return matched;
}

//================================================================================================
//===============================[函数列表：外屏初始化+事件处理+周期数据]============================
//================================================================================================
screenRxTxHandleType externalScreenTxHandle[SCREEN_LARGER_TX_HANDLE_TOTAL_NUM]=
{
	//priority index func_add
	{0,	0, &externalScreenTxHandle_ScreenInit},//==send initial data to DIWEN to display
	{0,	1, &externalScreenTxHandle_ChangeDisplayPosition},//==send initial data to DIWEN to display
	{0,	2, &externalScreenTxHandle_JumpToBanlingPage},//==send initial data to DIWEN to display
	{0,	3, &screenPublic_RemoveWeightTrigerHandle},//==B1 event arrive:At Balancing Page , remove weight trigerd
	{0,	4, &externalScreenTxHandle_ScreenWeightAndColorAndHelpHandle},//==send initial data to DIWEN to display
};

#endif// end of _APP_EXTERNAL_SCREEN_TX_HANDLE_C_
