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
#include "app_InnerScreen_Cfg.h"
#include "app_ExternalScreen_Cfg.h"

//=====================================================================================================================
//==================================================[ 配平数据处理 ：判断是否需要发送 ]===================================
//=====================================================================================================================
//32bit判断
UINT16 BalancingData_JudgeINT32_IfNotNeedSend(INT32 *p32JudgeData , INT32 *p32JudgeDataPre ,UINT16 u16JudgeLen)
{
	UINT16 ret = FALSE , offset = 0;
	for(offset = 0 ; offset < u16JudgeLen ; offset++)
	{
		if(p32JudgeData[offset] != p32JudgeDataPre[offset])
		{
			ret = TRUE ;
		}
	}
	return ret;
}

//16bit判断
UINT16 BalancingData_JudgeINT16_IfNotNeedSend(INT16 *p16JudgeData , INT16 *p16JudgeDataPre ,UINT16 u16JudgeLen)
{
	UINT16 ret = FALSE , offset = 0;
	for(offset = 0 ; offset < u16JudgeLen ; offset++)
	{
		if(p16JudgeData[offset] != p16JudgeDataPre[offset])
		{
			ret = TRUE ;
		}
	}
	return ret;
}
//=====================================================================================================================
//==================================================[ 配平数据处理 ：数据发送后置相等 ]===================================
//=====================================================================================================================

//32bit置相等
void BalancingData_Data32_WasSend(INT32 *p32Data , INT32 *p32DataPre ,UINT16 u16Len)
{
	UINT16 offset = 0;
	for(offset = 0 ; offset < u16Len ; offset++)
	{
		p32DataPre[offset] = p32Data[offset];
	}
}

//16bit置相等
void BalancingData_Data16_WasSend(INT16 *p16Data , INT16 *p16DataPre ,UINT16 u16Len)
{
	UINT16 offset = 0;
	for(offset = 0 ; offset < u16Len ; offset++)
	{
		p16DataPre[offset] = p16Data[offset];
	}
}


//=====================================================================================================================
//==================================================[ 配平数据处理 ：重量信息 ]==========================================
//=====================================================================================================================
//20240623：【1.1】【重量】【准备及判断】是否需要发送给屏幕（内屏外屏兼容）
UINT16 BalancingData_WeightData_Handle_PrepareAndJudgeIfNotNeedSend(T5LType *pSdwe)
{
	UINT16 ret = FALSE , i;
	//INT32 tempData32;
	//INT16 tempData16;
	T5LType *pSdweOther;
	switch(gSystemPara.isCascade)
	{
		case 0://非级联 单台设备
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 从HX711获取重量
			{
				screenPublic_CurrentDevice_WeightDataPrepare(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataSendToDiWen);
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取重量
			{
				pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
				for(i=0;i<HX711_CHANEL_NUM;i++)
				{
					pSdwe->screenCycle.pData[i] = pSdweOther->screenCycle.pData[i];
					pSdwe->screenCycle.pDataSendToDiWen[2*i+0] = pSdweOther->screenCycle.pDataSendToDiWen[2*i+0]; 
					pSdwe->screenCycle.pDataSendToDiWen[2*i+1] = pSdweOther->screenCycle.pDataSendToDiWen[2*i+1]; 
				}
			}
			//判断前 HX711_CHANEL_NUM 个数据是否需要发送
			ret = BalancingData_JudgeINT32_IfNotNeedSend(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataPre,HX711_CHANEL_NUM);
		break;

		case ModbusAdd_Master://级联 主设备
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 从HX711获取主机重量+从MODBUS获取从机重量
			{
				screenPublic_CurrentDevice_WeightDataPrepare(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataSendToDiWen);
				screenPublic_OtherDevice_WeightDataPrepare(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataSendToDiWen,ModbusAdd_Slave_1);
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取重量
			{
				pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
				for(i=0;i<2*HX711_CHANEL_NUM;i++)
				{
					pSdwe->screenCycle.pData[i] = pSdweOther->screenCycle.pData[i];
					pSdwe->screenCycle.pDataSendToDiWen[2*i+0] = pSdweOther->screenCycle.pDataSendToDiWen[2*i+0]; 
					pSdwe->screenCycle.pDataSendToDiWen[2*i+1] = pSdweOther->screenCycle.pDataSendToDiWen[2*i+1]; 
				}
			}
			//判断前 2*HX711_CHANEL_NUM 个数据是否需要发送
			ret = BalancingData_JudgeINT32_IfNotNeedSend(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataPre,(2*HX711_CHANEL_NUM));
		break;

		case ModbusAdd_Slave_1://级联 从设备
			//模式1 从MODBUS上获取主设备和从设备重量
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 从MODBUS获取主机+从机重量
			{
				#if 1
					screenPublic_OtherDevice_WeightDataPrepare(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataSendToDiWen,ModbusAdd_Master);
					screenPublic_OtherDevice_WeightDataPrepare(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataSendToDiWen,ModbusAdd_Slave_1);
				#else 
					//bug处理：因为从机显示时也是显示8头的 然后地址复用master的
					for(i=0;i<HX711_CHANEL_NUM;i++)
					{
						tempData32 = pSdwe->screenCycle.pData[i];
						pSdwe->screenCycle.pData[i] = pSdwe->screenCycle.pData[HX711_CHANEL_NUM+i];
						pSdwe->screenCycle.pData[HX711_CHANEL_NUM+i] = tempData32;
						//
						tempData16 = pSdwe->screenCycle.pDataSendToDiWen[2*(i)+0];
						pSdwe->screenCycle.pDataSendToDiWen[2*(i)+0] = pSdwe->screenCycle.pDataSendToDiWen[2*(HX711_CHANEL_NUM+i)+0];
						pSdwe->screenCycle.pDataSendToDiWen[2*(HX711_CHANEL_NUM+i)+0] = tempData16;
						//
						tempData16 = pSdwe->screenCycle.pDataSendToDiWen[2*(i)+1];
						pSdwe->screenCycle.pDataSendToDiWen[2*(i)+1] = pSdwe->screenCycle.pDataSendToDiWen[2*(HX711_CHANEL_NUM+i)+1];
						pSdwe->screenCycle.pDataSendToDiWen[2*(HX711_CHANEL_NUM+i)+1] = tempData16;					
					}
				#endif
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取重量
			{
				#if 1
					pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
					for(i=0;i<2*HX711_CHANEL_NUM;i++)
					{
						pSdwe->screenCycle.pData[i] = pSdweOther->screenCycle.pData[i];
						pSdwe->screenCycle.pDataSendToDiWen[2*i+0] = pSdweOther->screenCycle.pDataSendToDiWen[2*i+0]; 
						pSdwe->screenCycle.pDataSendToDiWen[2*i+1] = pSdweOther->screenCycle.pDataSendToDiWen[2*i+1]; 
					}
				#else
					screenPublic_OtherDevice_WeightDataPrepare(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataSendToDiWen,ModbusAdd_Master);
					screenPublic_OtherDevice_WeightDataPrepare(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataSendToDiWen,ModbusAdd_Slave_1);
				#endif
			}
			//判断前 2*HX711_CHANEL_NUM 个数据是否需要发送
			ret = BalancingData_JudgeINT32_IfNotNeedSend(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataPre,(2*HX711_CHANEL_NUM));
		break;

		default:
		break;
	}
	return ret;
}

//20240623：【1.2】【重量】【发送】信息给屏幕（内屏外屏兼容）
void BalancingData_WeightData_Handle_PrepareAndJudgeAndSendToScreen(T5LType *pSdwe)
{
	switch(pSdwe->screenWeightHandleStatus)
	{
		case 0://判断【重量】是否需要发送
			if(TRUE == BalancingData_WeightData_Handle_PrepareAndJudgeIfNotNeedSend(pSdwe))
			{
				pSdwe->screenWeightHandleStatus = 1;//【重量】：判断->发送
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：等待
				pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：等待
			}
			else
			{
				pSdwe->screenWeightHandleHoldOn++;
				if(pSdwe->screenWeightHandleHoldOn >= DMG_DATA_HOLD_TIME)//if weight not changed then check if color need send
				{
					pSdwe->screenWeightHandleHoldOn = 0;
					//
					pSdwe->screenWeightHandleStatus = 0XFE;//【重量】：判断->等待
					pSdwe->screenColorHandleStatus = 0;//【背景色】：等待->判断
					pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：等待
				}
			}
		break;

		case 1://发送【重量】数据给屏幕
			if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pSdwe->screenCycle.pDataSendToDiWen,(2*(2*HX711_CHANEL_NUM)),0));//2*chanel_len:because each data type was 4 byte
			{
				//设置pDataPre=pData
				BalancingData_Data32_WasSend(pSdwe->screenCycle.pData,pSdwe->screenCycle.pDataPre,(2*HX711_CHANEL_NUM));
				//继续跳回判断数据是否相等
				pSdwe->screenWeightHandleHoldOn = 0 ;
				//
				pSdwe->screenWeightHandleStatus = 0;//【重量】：判断->发送
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：等待
				pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：等待
			}
		break;

		case 0xFE://等待【颜色】 【帮组信息】都已处理
			pSdwe->screenWeightHandleHoldOn++;
			if(pSdwe->screenWeightHandleHoldOn >= DMG_WAIT_COLOR_HELP_SEND_TIME)
			{
				//超时等待
				pSdwe->screenWeightHandleHoldOn = 0;
				//
				pSdwe->screenWeightHandleStatus = 0;//【重量】：等待->判断
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：等待
				pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：等待
			}
		break;

		default:
				//其他
				pSdwe->screenWeightHandleStatus = 0;//【重量】：判断->发送
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：等待
				pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：等待
		break;
	}
}

//=====================================================================================================================
//==================================================[ 配平数据处理 ：背景色信息 ]========================================
//=====================================================================================================================
//20240623：准备【2.1】【背景色】信息（内屏外屏兼容）
void BalancingData_ColorData_Handle_Prepare(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 release = FALSE;
	UINT8 sortArry_num = 0 ,chn_self = 0 , chn_other = 0 , chn_i = 0;
	//weight use pDataPre
	INT32 *pData = pSdwe->screenCycle.pDataPre;
	//color data
	INT16 *pColor = pSdwe->screenCycle.pColor;
	//INT16 *pColorPre = pSdwe->screenCycle.pColorPre;
	INT16 *pColorOtherCh = pSdwe->screenCycle.pColorOtherCh;
	//sort need data
	float *sortWeight = pSdwe->screenCycle.pSortWeight;//&g_fDataBuffCaculate[0];
	INT16 *sortArry = pSdwe->screenCycle.pSortArry;//&g_i16OtherChanelCaculate[0];
	//
	UINT8 compare_i = 0 ;
	//
	float judge_errRange = gSystemPara.errRange,judge_zeroRange = gSystemPara.zeroRange;
 
	enumLedColorType colorVld = LED_COLOR_NONE;
 
	//有小数点时，判断范围乘以10
	if(1 == gSystemPara.xiaoShuXianShi)
	{
		judge_errRange = gSystemPara.errRange*10;
		judge_zeroRange = gSystemPara.zeroRange*10;
	}
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		//1.judge the equal chanle again
		for(chn_i=0;chn_i<chanel_len;chn_i++)
		{
			release = FALSE;//dit not release channel display color
			//
			chn_self = chn_i;//self chanel
			chn_other = (UINT8)pColorOtherCh[chn_self];//other chanel
			//other chanel matched
			if(chn_other < chanel_len)
			{
				if(((pData[chn_self] - pData[chn_other]) >= -judge_errRange) && ((pData[chn_self] - pData[chn_other]) <= judge_errRange) )
				{
					//self and other chanel weight equal again
					if(((pData[chn_self] > -judge_zeroRange) && (pData[chn_self] < judge_zeroRange)) ||	
						((pData[chn_other] > -judge_zeroRange) && (pData[chn_other] < judge_zeroRange)))
					{
						//1.3 someone weight at zero range , need release
						release = TRUE;
					}
					else
					{
						if(pColor[chn_self] != pColor[chn_other])
						{
							//1.2 weight equal but color not equal or someone was NONE color, need release
							release = TRUE;
						}
					}
				}
				else
				{
					//1.1 weight not equal again , need release
					release = TRUE;
				}
			}
			else
			{
				//1.0 other channel not match , need release
				release = TRUE;
			}

			if(LED_COLOR_NONE != pColor[chn_self])
			{
				//接近相等
				if(((pData[chn_self] - pData[chn_other]) >= -judge_errRange) && ((pData[chn_self] - pData[chn_other]) <= judge_errRange) )
				{
					if(((pData[chn_self] > -judge_zeroRange) && (pData[chn_self] < judge_zeroRange)) ||	
						((pData[chn_other] > -judge_zeroRange) && (pData[chn_other] < judge_zeroRange)))
					{
						release = TRUE;
					}
				}
				else
				{
					release = TRUE;
				}
			}
 
			//if need release , must release self and other
			if(TRUE == release)
			{
				//clear the self other chanel = Invalid
				if(T5L_CHANEL_WEIGHT_NOT_EQUAL != pColorOtherCh[chn_self])
				{
					pColorOtherCh[chn_self] = T5L_CHANEL_WEIGHT_NOT_EQUAL;
				}
				//clear the other chanel = Invalid
				if((chn_other < T5L_MAX_CHANEL_LEN) && (T5L_CHANEL_WEIGHT_NOT_EQUAL != pColorOtherCh[chn_other]))
				{
					pColorOtherCh[chn_other] = T5L_CHANEL_WEIGHT_NOT_EQUAL;
				}
				//release self color
				if(LED_COLOR_NONE != pColor[chn_self])
				{
					releaseSysColor((enumLedColorType)pColor[chn_self]);//release used color
					LedDataSet((enumLedSeqType)chn_self, LED_COLOR_NONE);//LED : display
					pColor[chn_self] = LED_COLOR_NONE;//clear chn_self color
				}
				//release other color
				if((chn_other < T5L_MAX_CHANEL_LEN) && (LED_COLOR_NONE != pColor[chn_other]))
				{
					releaseSysColor((enumLedColorType)pColor[chn_other]);//release used color
					LedDataSet((enumLedSeqType)chn_other, LED_COLOR_NONE);//LED : display
					pColor[chn_other] = LED_COLOR_NONE;//clear chn_other color
				}
			}
		}
		//2.use pColor ==  LED_COLOR_NONE , to triger need judge weight
		sortArry_num = 0 ;
		for(chn_i=0;chn_i<chanel_len;chn_i++)
		{
			//no color and weight was need match outof zero
			if((LED_COLOR_NONE == pColor[chn_i]) &&
			((pData[chn_i] < -judge_zeroRange) || (pData[chn_i] > judge_zeroRange)))
			{
				sortWeight[sortArry_num] = pData[chn_i];
				sortArry[sortArry_num] = chn_i;
				sortArry_num++;
			}
		}
		//3.use weight Sort
		BubbleSort(sortWeight,sortArry,sortArry_num);
		//4.user sorted weight , set color
		for(compare_i=0;compare_i<(sortArry_num-1);compare_i++)
		{
			chn_self = sortArry[compare_i];
			chn_other = sortArry[compare_i+1];
			if(( chn_self < chanel_len) && ( chn_other < chanel_len) )
			{
				//is equal
				if( ((pData[chn_self] < -judge_zeroRange) || (pData[chn_self] > judge_zeroRange)) &&
					((pData[chn_other] < -judge_zeroRange) || (pData[chn_other] > judge_zeroRange)) &&
					(((pData[chn_self] - pData[chn_other]) >= -judge_errRange) && ((pData[chn_self] - pData[chn_other]) <= judge_errRange) ) )
				{
					//screen : set the same color
					colorVld = getSysColorWhichUsable();
					pColor[chn_self] = colorVld;
					pColor[chn_other] = colorVld;
					//otherChn recode
					pColorOtherCh[chn_self] = chn_other;
					pColorOtherCh[chn_other] = chn_self;
					
					//screen : voice pritf
					if(LED_COLOR_NONE != colorVld)//bug : case weight equal but colot was LED_COLOR_NONE
					{
						sdwe_VoicePrintfPush((tT5LVoinceType)(chn_self+1),(tT5LVoinceType)(chn_other+1));
					}
					//LED : display
					LedDataSet((enumLedSeqType)chn_self, colorVld);
					LedDataSet((enumLedSeqType)chn_other, colorVld);
 
					//
					compare_i++;//!!!!! must add it !!!!!
				}
			}
		}
	}
}

//20240623：发送【2.2】【背景色】是否需要发送给屏幕（内屏及外屏）
UINT16 BalancingData_ColorData_Handle_PrepareAndJudgeIfNotNeedSend(T5LType *pSdwe)
{
	UINT16 ret = FALSE , i;
	T5LType *pSdweOther;

	static UINT32 lastSendCnt = 0 , diff_time = 2000; // trigger send each 2s
	
	switch(gSystemPara.isCascade)
	{
		case 0://非级联 单台设备
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 依据重量信息计算背景色
			{
				BalancingData_ColorData_Handle_Prepare(pSdwe,HX711_CHANEL_NUM);
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取背景色
			{
				pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
				for(i=0;i<2*HX711_CHANEL_NUM;i++)
				{
					pSdwe->screenCycle.pColor[i] = pSdweOther->screenCycle.pColor[i];
				}
			}
			//判断前 HX711_CHANEL_NUM 个背景色信息是否需要发送
			ret = BalancingData_JudgeINT16_IfNotNeedSend(pSdwe->screenCycle.pColor,pSdwe->screenCycle.pColorPre,HX711_CHANEL_NUM);
		break;

		case ModbusAdd_Master://级联 主设备
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 依据重量信息计算背景色
			{
				BalancingData_ColorData_Handle_Prepare(pSdwe,(2*HX711_CHANEL_NUM));		
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取背景色
			{
				pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
				for(i=0;i<2*HX711_CHANEL_NUM;i++)
				{
					pSdwe->screenCycle.pColor[i] = pSdweOther->screenCycle.pColor[i];
				}
			}
			//判断前 2*HX711_CHANEL_NUM 个背景色信息是否需要发送
			ret = BalancingData_JudgeINT16_IfNotNeedSend(pSdwe->screenCycle.pColor,pSdwe->screenCycle.pColorPre,(2*HX711_CHANEL_NUM));
		break;

		case ModbusAdd_Slave_1://级联 从设备
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 依据重量信息计算背景色
			{
				//小屏 背景色 直接从MODBUS获取	
				for(i=0;i<HX711_CHANEL_NUM;i++)
				{
					LedDataSet((enumLedSeqType)i, (enumLedColorType)g_i16ColorBuff[HX711_CHANEL_NUM+i]);//LED : display
				}
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取背景色
			{
				pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
				for(i=0;i<2*HX711_CHANEL_NUM;i++)
				{
					pSdwe->screenCycle.pColor[i] = pSdweOther->screenCycle.pColor[i];
				}
			}			
			//判断前 2*HX711_CHANEL_NUM 个背景色信息是否需要发送
			ret = BalancingData_JudgeINT16_IfNotNeedSend(pSdwe->screenCycle.pColor,pSdwe->screenCycle.pColorPre,(2*HX711_CHANEL_NUM));
		break;

		default:
		break;
	}

	
	if(lastSendCnt != (pSdwe->CurTick/diff_time))
	{
		lastSendCnt = pSdwe->CurTick/diff_time;
		ret = TRUE;
	}

	return ret;
}

//20240623：发送【2.3】【背景色】信息给屏幕（内屏及外屏兼容）
void BalancingData_ColorData_Handle_PrepareAndJudgeAndSendToScreen(T5LType *pSdwe)
{
	switch(pSdwe->screenColorHandleStatus)
	{
		case 0://判断【背景色】是否需要发送
			if(TRUE == BalancingData_ColorData_Handle_PrepareAndJudgeIfNotNeedSend(pSdwe))
			{
				pSdwe->screenWeightHandleStatus = 0xFE;//【重量】：等待
				pSdwe->screenColorHandleStatus = 1;//【背景色】：判断->发送
				pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：等待
			}
			else
			{
				pSdwe->screenWeightHandleStatus = 0xFE;//【重量】：等待
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：判断->等待
				pSdwe->screenHelpHandleStatus = 0;//【帮助信息】：等待->判断
			}
		break;

		case 1://发送【背景色】给屏幕
			if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pSdwe->screenCycle.pColor,(2*HX711_CHANEL_NUM),0));
			{
				BalancingData_Data16_WasSend(pSdwe->screenCycle.pColor,pSdwe->screenCycle.pColorPre,(2*HX711_CHANEL_NUM));
				pSdwe->screenWeightHandleStatus = 0xFE;//【重量】：等待
				pSdwe->screenColorHandleStatus = 0;//【背景色】：发送->判断
				pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：等待
			}		
		break;

		case 0xFE://等待
			//wait

		break;

		default:
				pSdwe->screenWeightHandleStatus = 0xFE;//【重量】：等待
				pSdwe->screenColorHandleStatus = 0;//【背景色】：xx->判断
				pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：等待
		break;
	}
}

//=====================================================================================================================
//==================================================[ 配平数据处理 ：帮助信息 ]==========================================
//=====================================================================================================================
//20240623：准备【3.1】【帮助信息】（内屏及外屏兼容）
UINT8 BalancingData_HelpData_Handle_Prepare(T5LType *pSdwe,UINT16 chanel_len)
{
	UINT8 localStatus = 0;
	//
	INT32 *pData = pSdwe->screenCycle.pData;
	INT16 *pColorOtherCh = pSdwe->screenCycle.pColorOtherCh;
	//
	float *sortWeight = pSdwe->screenCycle.pSortWeight;
	INT16 *sortArry = pSdwe->screenCycle.pSortArry;
	//
	INT16 i16Minus = 0 , minPos_i = 0xff ,minPos_j=0xff;
	UINT8 help_i = 0;
	//
	INT16 *pOutData = pSdwe->screenCycle.pHelp;
	//
	UINT8 sortArry_num = 0 ,chn_i = 0 , chn_j = 0;

	//==use (LED_COLOR_NONE == pColor) : pre need sort weight
	sortArry_num = 0 ;
	for(chn_i=0;chn_i<chanel_len;chn_i++)
	{
		if(T5L_CHANEL_WEIGHT_NOT_EQUAL == pColorOtherCh[chn_i])
		{
			sortWeight[sortArry_num] = pData[chn_i];
			sortArry[sortArry_num] = chn_i;
			sortArry_num++;
		}
	}

	//==sort weight : from min to max
	if(sortArry_num > 1)
	{	
		BubbleSort((float *)sortWeight,sortArry,sortArry_num);
	}

	//==caculate help data
	for(help_i=0;help_i < DIFF_JUDGE_GROUP_NUM_SLAVE1;)
	{
		i16Minus = 0x7FFF ;
		minPos_i = 0xff;
		minPos_j = 0xff;
		//find chn_i
		for(chn_i=0;chn_i<sortArry_num;chn_i++)
		{
			if((sortWeight[chn_i] >= gSystemPara.zeroRange) || 
				(sortWeight[chn_i] <= -gSystemPara.zeroRange) )
			{
				//find chn_j
				for(chn_j=(chn_i+1);chn_j<sortArry_num;chn_j++)
				{
					//if chn_j larger than zero
					if((sortWeight[chn_j] >= gSystemPara.zeroRange) || 
						(sortWeight[chn_j] <= -gSystemPara.zeroRange) )
					{
						break;
					}
				}
				//==out the least value of diff 
				if((chn_i < sortArry_num) && (chn_j < sortArry_num))
				{
					if((sortWeight[chn_j] - sortWeight[chn_i]) < i16Minus)
					{
						i16Minus = sortWeight[chn_j] - sortWeight[chn_i];
						minPos_j = chn_j;
						minPos_i = chn_i;
					}
				}
			}	
		}
		//==qunene the least value of diff
		if((i16Minus != 0x7FFF) && (0xff != minPos_i) && (0xff != minPos_j))
		{
			if(help_i < DIFF_JUDGE_GROUP_NUM_SLAVE1)
			{
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 0] = sortArry[minPos_j]+1;
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 1] = sortArry[minPos_i]+1;
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 2] = i16Minus;
				help_i++;
			}
			sortWeight[minPos_j] = 0 ;
			sortWeight[minPos_i] = 0 ;
		}
		else
		{
			break;
		}
	}
	
	//==the remain help data set to 0
	for(;help_i<(DIFF_JUDGE_GROUP_NUM_SLAVE1);help_i++)
	{
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 0] = 0;
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 1] = 0;
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 2] = 0;
	}
	
	return localStatus;
}

//20240622：判断【3.2】【帮助信息】是否需要发送（内屏及外屏兼容）
UINT16 BalancingData_HelpData_Handle_PrepareAndJudgeIfNotNeedSend(T5LType *pSdwe)
{
	UINT16 ret = FALSE , i;
	T5LType *pSdweOther;
	switch(gSystemPara.isCascade)
	{
		case 0://非级联 单台设备
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 使用重量计算帮助信息
			{
				BalancingData_HelpData_Handle_Prepare(pSdwe,HX711_CHANEL_NUM);
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取帮助信息
			{
				pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
				for(i=0;i<DIFF_TO_DIWEN_DATA_LEN;i++)
				{
					pSdwe->screenCycle.pHelp[i] = pSdweOther->screenCycle.pHelp[i];
				}
			}
		break;

		case ModbusAdd_Master://级联 主设备
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 使用重量计算帮助信息
			{
				BalancingData_HelpData_Handle_Prepare(pSdwe,(2*HX711_CHANEL_NUM));
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取帮助信息
			{
				pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
				for(i=0;i<DIFF_TO_DIWEN_DATA_LEN;i++)
				{
					pSdwe->screenCycle.pHelp[i] = pSdweOther->screenCycle.pHelp[i];
				}
			}
		break;

		case ModbusAdd_Slave_1://级联 从设备
			//模式1 从MODBUS上获取主设备和从设备重量
			if((&g_T5LCtx[ScreenIndex_Smaller] == pSdwe))//小屏 从MODBUS获取主机+从机重量
			{
				//无需准备，来源于MODBUS，已经把值放在了pSdwe->screenCycle.pHelp
			}
			else if((&g_T5LCtx[ScreenIndex_Larger] == pSdwe))//大屏 从小屏获取帮助信息
			{
				pSdweOther = &g_T5LCtx[ScreenIndex_Smaller];
				for(i=0;i<DIFF_TO_DIWEN_DATA_LEN;i++)
				{
					pSdwe->screenCycle.pHelp[i] = pSdweOther->screenCycle.pHelp[i];
				}
			}
		break;

		default:
		break;
	}
	//判断前 2*HX711_CHANEL_NUM 个数据是否需要发送
	ret = BalancingData_JudgeINT16_IfNotNeedSend(pSdwe->screenCycle.pHelp,pSdwe->screenCycle.pHelpPre,DIFF_TO_DIWEN_DATA_LEN);
	return ret;

}

//20240623：发送【3.3】【帮助信息】给屏幕（内屏及外屏兼容）
void BalancingData_HelpData_Handle_PrepareAndJudgeAndSendToScreen(T5LType *pSdwe)
{
	switch(pSdwe->screenHelpHandleStatus)
	{
		case 0://判断【帮组信息】是否需要发送
			if(TRUE == BalancingData_HelpData_Handle_PrepareAndJudgeIfNotNeedSend(pSdwe))
			{
				pSdwe->screenWeightHandleStatus = 0xFE;//【重量】：等待
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：等待
				pSdwe->screenHelpHandleStatus = 1;//【帮助信息】：判断->发送
			}
			else
			{	
				pSdwe->screenWeightHandleStatus = 0;//【重量】：等待->判断
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：xx->等待
				pSdwe->screenHelpHandleStatus = 0xFE;//【帮助信息】：xx->等待
			}
		break;
		
		case 1://发送【帮助信息】给屏幕 
			if(TRUE == t5lWriteData(pSdwe,DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS,pSdwe->screenCycle.pHelp,(DIFF_TO_DIWEN_DATA_LEN),0))
			{
				BalancingData_Data16_WasSend(pSdwe->screenCycle.pHelp,pSdwe->screenCycle.pHelpPre,DIFF_TO_DIWEN_DATA_LEN);
				pSdwe->screenWeightHandleStatus = 0xFE;//【重量】：等待->判断
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：xx->等待
				pSdwe->screenHelpHandleStatus = 0;//【帮助信息】：发送->判断
			}
		break;

		case 0xFE://等待
			//wait

		break;

		default:
				pSdwe->screenWeightHandleStatus = 0xFE;//【重量】：等待->判断
				pSdwe->screenColorHandleStatus = 0xFE;//【背景色】：xx->等待
				pSdwe->screenHelpHandleStatus = 0;//【帮助信息】：发送->判断
		break;
	}
}

#if 0
//20240623：发送【重量】 【背景色】【帮助信息】给屏幕（内屏外屏兼容）
UINT16 System_WeightColorAndHelpData_SendToScreen_Handle(T5LType *pSdwe)
{
	BalancingData_WeightData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
	BalancingData_ColorData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
	BalancingData_HelpData_Handle_PrepareAndJudgeAndSendToScreen(pSdwe);
}
#endif

