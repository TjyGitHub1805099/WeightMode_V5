#ifndef _APP_INNER_SCREEN_TX_HANDLE_C_
#define _APP_INNER_SCREEN_TX_HANDLE_C_
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

//0.0内屏初始化
UINT8 innerScreenTxHandle_Init(T5LType *pSdwe)
{
	INT16 sendData[64],len=0;
	UINT8 result = FALSE ;
	static INT16 curPage = 0 ,  curPageDelay_offset = 80;
	//
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
		case 0x81:
			if(0 == (pSdwe->CurTick %curPageDelay_offset))//every 500ms send order to get version
			{	
				if(TRUE ==screenPublic_PageJump(pSdwe,curPage))//触发屏幕播放开机动画
				{
					if(curPage++ >= 25)
					{
						pSdwe->sendSysParaDataToDiwenIndex = 0x82;
					}				
				}			
			}
		break;
		case 0x82://发送配平页面的数据 规整为0 等待HX711采集到一轮完整数据后在继续往后
			if(TRUE == pSdwe->sdweHX711FirstSampleCoplt)
			{
				pSdwe->sendSysParaDataToDiwenIndex = 0 ;//准备配平页面的数据 后在发送相关参数
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
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 4://小数显示相关描述指针变量发送，托盘重量显示相关
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_WeightVlu(pSdwe))//根据小数是否打开 发送相关数据
				{
					pSdwe->sendSysParaDataToDiwenIndex=41;
				}
			}
		break;
		case 41://小数显示相关描述指针变量发送，帮组信息相关
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_HelpVlu(pSdwe))//根据小数是否打开 发送相关数据
				{
					pSdwe->sendSysParaDataToDiwenIndex = 42;
				}
			}
		break;
		case 42://背景色
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_WeightColor(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex = 5;
				}
			}
		break;
		case 5://changed at 20220119 , FuncA Module special , send num
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				#if 0
				switch(gSystemPara.isCascade)
				{
					case 0://1-8
						for(len = 0 ; len < HX711_CHANEL_NUM ; len++)
						{
							sendData[len] = len + 1;
						}	
						t5lWriteVarible(pSdwe,(0x3901),sendData,len,0);						
					break;

					case ModbusAdd_Master://1-8
						for(len = 0 ; len < HX711_CHANEL_NUM ; len++)
						{
							sendData[len] = len + 1;
						}	
						t5lWriteVarible(pSdwe,(0x3901),sendData,len,0);						
					break;

					case ModbusAdd_Slave_1://9-16
						for(len = 0 ; len < HX711_CHANEL_NUM ; len++)
						{
							sendData[len] = HX711_CHANEL_NUM + len + 1;
						}		
						t5lWriteVarible(pSdwe,(0x3909),sendData,len,0);						
					break;
					default:
					break;
				}
				#else
					for(len = 0 ; len < 2*HX711_CHANEL_NUM ; len++)
					{
						sendData[len] = len + 1;
					}		
					t5lWriteVarible(pSdwe,(0x3901),sendData,len,0);						
				#endif
				//
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 6://jump to Banling page
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				screenPublic_PageJump(pSdwe,pSdwe->screenBanlingPageNum);
				pSdwe->sendSysParaDataToDiwenIndex++;
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
				sendData[len++] = gSystemPara.mlYugBiLv;		/**< ml与g比率 0x101d*/			//101Df
				sendData[len++] = gSystemPara.daPinXianShi;		/**< 大屏显示 0x101e*/			//101E
				sendData[len++] = gSystemPara.weightNum;		/**< 单台数量 0x101f*/			//101F

				t5lWriteVarible(pSdwe,(0x100A),sendData,len,0);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 9://send 2100 DMG_FUNC_SET_CHANEL_NUM
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				sendData[len++] = pSdwe->CalibrateChanel;
				t5lWriteVarible(pSdwe,DMG_FUNC_SET_CHANEL_NUM,sendData,len,0);/**< 校准的通道号 */  //2100
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 10://send voice info to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				screenT5L_OutputVoice(pSdwe,VoiceTypeMax);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 11://序号显示相关描述指针变量发送
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenPublic_FreshDisplayPosition_Of_WeightIndex(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
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

//0内屏初始化 事件处理
UINT8 innerScreenTxHandle_ScreenInit(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(T5L_INITIAL_COMPLETE != pSdwe->sendSdweInit)
	{
		matched = TRUE;
		if(TRUE == innerScreenTxHandle_Init(pSdwe))
		{
			pSdwe->sendSdweInit = T5L_INITIAL_COMPLETE;
		}
	}
	return matched;
}

//1
UINT8 innerScreenTxHandle_JumpToHomePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToHomePage)
	{
		matched = TRUE;
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenHomePageNum))
		{
			pSdwe->sdweJumpToHomePage = FALSE;
		}
	}
	return matched;
}

//2
UINT8 innerScreenTxHandle_JumpToBanlingPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToBanlingPage)
	{
		matched = TRUE;
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenBanlingPageNum))
		{
			pSdwe->sdweJumpToBanlingPage = FALSE;
		}
	}
	return matched;
}

//3
UINT8 innerScreenTxHandle_JumpToCalibrationPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToCalitrationPage)
	{
		matched = TRUE;
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenCalibrationPage))
		{
			pSdwe->sdweJumpToCalitrationPage = FALSE;
		}
	}
	return matched;
}

//4
UINT8 innerScreenTxHandle_JumpToActivePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpActivePage)
	{
		matched = TRUE;
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenActivePage))
		{
			pSdwe->sdweJumpActivePage = FALSE;
		}
	}
	return matched;
}

//5
UINT8 innerScreenTxHandle_JumpToSysParaPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToSysParaPage)
	{
		matched = TRUE;
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenSysParaPage))
		{
			pSdwe->sdweJumpToSysParaPage = FALSE;
		}
	}
	return matched;
}

//6
UINT8 innerScreenTxHandle_JumpToBanlingMainPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpBalancingMainPage)
	{
		matched = TRUE;
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenBalancingMainPage))
		{
			pSdwe->sdweJumpBalancingMainPage = FALSE;
		}
	}
	return matched;
}
//7
UINT8 innerScreenTxHandle_JumpToBalancingCleanPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpBalancing_cleanpagee)
	{
		matched = TRUE;
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenBalancingCleanPage))
		{
			pSdwe->sdweJumpBalancing_cleanpagee = FALSE;
		}
	}
	return matched;
}

//8
UINT8 innerScreenTxHandle_JumpToBalancingHomePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpBalancing_home)
	{
		matched = TRUE;
		if(0 != screenPublic_PageJump(pSdwe,pSdwe->screenBalancingMainPage))
		{
			pSdwe->sdweJumpBalancing_home = FALSE;
		}
	}
	return matched;
}

//9
UINT8 innerScreenTxHandle_FreshScreenLight(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweFreshScreenLight)
	{
		matched = TRUE;
		if(0 != screenPublic_ScreenLight(pSdwe))
		{
			pSdwe->sdweFreshScreenLight = FALSE;
		}
	}
	return matched;
}

//10
UINT8 innerScreenTxHandle_ChangeDisplayPosition(T5LType *pSdwe)
{
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

//公共函数：校准时 单点触发 处理
UINT8 innerScreenTxHandle_IsCascadTriggerHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	static UINT8 stepIndex = 0;

	if(TRUE == pSdwe->isCascadTrigger)
	{
		matched = TRUE;
		if(0 == stepIndex)
		{
			if(0 != screenPublic_WriteIndexHandle(pSdwe))
			{
				stepIndex = 0 ;
				pSdwe->isCascadTrigger = FALSE;
			}
		}
	}
	return matched;
}

//
UINT8 innerScreenTxHandle_ScreenWeightAndColorAndHelpAndVoiceHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(g_sysLocked == STM32MCU_UNLOCKED)
	{
		matched = TRUE;
		#if (0 == SCREEN_BALANCINGDATA_HANDLE_MODE)
			screenPublic_sendBalancingWeightAndColor(pSdwe);
			screenPublic_HelpDataMainFunction(pSdwe);
			screenPublic_VoicePrintfMainfunction(pSdwe);
		#else
			BalancingData_WeightData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
			BalancingData_ColorData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
			BalancingData_HelpData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
			screenPublic_VoicePrintfMainfunction(pSdwe);
		#endif
	}	
	return matched;
}

//================================================================================================
//===============================[函数列表：内屏初始化+事件处理+周期数据]============================
//================================================================================================
screenRxTxHandleType innerScreenTxHandle[SCREEN_TX_HANDLE_TOTAL_NUM]=
{
	//priority index func_add
	{0,	0, &innerScreenTxHandle_ScreenInit},//==send initial data to DIWEN to display
	{0,	1, &innerScreenTxHandle_ChangeDisplayPosition},//==M7 event arrive:修改小数点
	{0,	2, &innerScreenTxHandle_JumpToHomePage},//==M1 event arrive:jump to HOME Page 
	{0,	3, &innerScreenTxHandle_JumpToBanlingPage},//==M2 event arrive:jump to BALANCING Page , Physical keying trigger
	{0,	4, &innerScreenTxHandle_JumpToCalibrationPage},//==M3 event arrive:jump to CALITRATION Page
	{0,	5, &innerScreenTxHandle_JumpToActivePage},//==M4 event arrive:jump to ACTIVE Page
	{0,	6, &innerScreenTxHandle_JumpToSysParaPage},//==M5 event arrive:jump to SYSPARA Page
	{0,	7, &innerScreenTxHandle_JumpToBanlingMainPage},//==配平模式的主要界面
	{0,	8, &innerScreenTxHandle_JumpToBalancingCleanPage},//==M2-2 event arrive:jump to BALANCING (clean)page
	{0,	9, &innerScreenTxHandle_JumpToBalancingHomePage},//==M2-3 event arrive:jump to BALANCING (home)page
	{0,	10, &innerScreenTxHandle_FreshScreenLight},//==M6 event arrive:fresh sreen light
	{0,	11, &screenPublic_ChanelChangedTrigerHandle},	//==C1 event arrive:At Calibration Page , chanel changed trigerd
	{0,	12, &screenPublic_ResetCalibrationTrigerHandle},//==C2 event arrive:At Calibration Page , calibration reset trigerd 
	{0,	13, &screenPublic_PointTrigerHandle},//==C3 event arrive:At Calibration Page , point trigerd
	{0,	14, &screenPublic_RemoveWeightTrigerHandle},//==B1 event arrive:At Balancing Page , remove weight trigerd
	{0,	15, &innerScreenTxHandle_IsCascadTriggerHandle},//级联触发按钮
	{0,	16, &innerScreenTxHandle_ScreenWeightAndColorAndHelpAndVoiceHandle},//normaly weight color voice handle
};

#endif// end of _APP_INNER_SCREEN_TX_HANDLE_C_
