#ifndef __APP_VOICEPRINTF_C__
#define __APP_VOICEPRINTF_C__
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app_syspara.h"
#include "app_balance.h"
#include "app_VoicePrintf.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
tVoiceInfoStruct g_VoinceInfo;

/*******************************************************************************
 * Functions
 ******************************************************************************/
//需要播报语音的语音序号入队
#if 0
void sdwe_VoicePrintfPush(tT5LVoinceType u8Voice1 ,tT5LVoinceType u8Voice2)
{
	if(u8T5LVoiceBuffStoreNum == 0)
	{
		g_T5L_VoiceBuff[u8T5LVoiceBuffPush_i][0] = u8Voice1;
		g_T5L_VoiceBuff[u8T5LVoiceBuffPush_i][1] = u8Voice2;
		g_T5L_VoiceBuff[u8T5LVoiceBuffPush_i][2] = VoiceTypePeiPin_18;
		u8T5LVoiceBuffPush_i = (u8T5LVoiceBuffPush_i+1)%T5L_VOICE_MAX_GROUP_NUM;
		//
		u8T5LVoiceBuffStoreNum++;
	}
}
#else
void sdwe_VoicePrintfPush(tVoiceArryStruct *pVoice,UINT8 num)
{
	tVoiceInfoStruct *pComtex = &g_VoinceInfo;
	if((pComtex->u8TotalNum < T5L_VOICE_MAX_GROUP_NUM) && (num < (T5L_VOICE_MAX_MEMBR_NUM-1)))
	{
		pComtex->voiceGroup[pComtex->u8Push_i] = *pVoice;
		pComtex->voiceGroup[pComtex->u8Push_i].voice[num] = VoiceTypePeiPin_18;
		pComtex->voiceGroup[pComtex->u8Push_i].voice[num+1] = VoiceTypeMax;
		pComtex->voiceGroup[pComtex->u8Push_i].num = num+2;
		//
		pComtex->u8Push_i = (pComtex->u8Push_i+1)%T5L_VOICE_MAX_GROUP_NUM;
		pComtex->u8TotalNum++;
	}
}

#endif

//需要播报语音的语音序号出队
#if 0
UINT8 sdwe_VoicePrintfPop(tT5LVoinceType *u8Voice1 , tT5LVoinceType *u8Voice2 , tT5LVoinceType *u8Voice3)
{
	UINT8 ret = FALSE;
	if(u8T5LVoiceBuffStoreNum > 0)
	{
		u8T5LVoiceBuffStoreNum--;
		//
		*u8Voice1 = g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][0];
		g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][0] =T5L_VoiceTypeNum_0;
		*u8Voice2 = g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][1];
		g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][1] = T5L_VoiceTypeNum_0;
		*u8Voice3 = g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][2];
		g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][2] = T5L_VoiceTypeNum_0;
		
		//add u8T5LVoiceBuffPop_i
		u8T5LVoiceBuffPop_i = (u8T5LVoiceBuffPop_i+1)%T5L_VOICE_MAX_GROUP_NUM;
		//
		if(((T5L_VoiceTypeNum_1 <= *u8Voice1) && (T5L_VoiceTypeNum_16 >= *u8Voice1)) &&
			((T5L_VoiceTypeNum_1 <= *u8Voice2) && (T5L_VoiceTypeNum_16 >= *u8Voice2)) &&
			(VoiceTypePeiPin_18 == *u8Voice3) )
		{
			ret = TRUE;
		}
	}
	//
	return ret;
}
#else
UINT8 sdwe_VoicePrintfPop(tVoiceArryStruct *pVoice)
{
	UINT8 ret = FALSE;
	tVoiceInfoStruct *pComtex = &g_VoinceInfo;
	if(pComtex->u8TotalNum > 0)
	{
		*pVoice = pComtex->voiceGroup[pComtex->u8Pop_i];
		//
		pComtex->u8Pop_i = (pComtex->u8Pop_i+1)%T5L_VOICE_MAX_GROUP_NUM;
		pComtex->u8TotalNum--;
		ret = TRUE;
	}
	return ret;
}

#endif
//触发屏幕语音播报
UINT8 screenT5L_OutputVoice(T5LType *pSdwe,UINT8 voiceId)
{
	UINT8 result = 0 ;
	//5A A5 07 82 00A0 3101 4000
	INT16 pageChangeOrderAndData[2]={0x3101,0X6400};//0x40=64 音量100 00速度

	if((gSystemPara.VoiceNum > 0) && (gSystemPara.VoiceNum <= 100) )
	{
		pageChangeOrderAndData[1] &= 0x00ff;
		pageChangeOrderAndData[1] |= (0xff00&(gSystemPara.VoiceNum<<8)); 
	}
	if(voiceId == VoiceTypeMax)
	{
		pageChangeOrderAndData[1] &= 0x00ff;
		pageChangeOrderAndData[1] |= (0xff00&(gSystemPara.VoiceNumTouch<<8)); 
	}
	//
	pageChangeOrderAndData[0] = ((voiceId%VoiceTypeMax)<<8)+(1);//音乐序号 1：整段音乐
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X00A0),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}



void screenPublic_VoiceScan(T5LType *pSdwe)
{
	uint8 grp_i = 0,mem_i = 0 ;
	uint8 *pGrp;
	uint8 grp_mem[MAX_GROUP_MEM_NUM];
	uint16 grp_mem_add , num = 0;
	tVoiceInfoStruct *pComtex = &g_VoinceInfo;
	tVoiceArryStruct s_Voice;
	for(grp_i = 0 ; grp_i < SCALE_TOTAL_GROUP_NUM ; grp_i++)
	{
		pGrp = &pComtex->grp_MenbArry[grp_i][0];
		ScaleBalance_GetGroupMembers(grp_i,&grp_mem[0]);
		//
		num = 0;
		grp_mem_add = 0 ;
		for(mem_i = 0 ; mem_i < MAX_GROUP_MEM_NUM ; mem_i++)
		{
			if(grp_mem[mem_i] != pGrp[mem_i])
			{
				pGrp[mem_i] = grp_mem[mem_i];
				pComtex->grp_FilterDelay[grp_i] = 0 ;
				pComtex->needPushed[grp_i] = 1;
			}
			if(grp_mem[mem_i] != INVALID_GROUP_MEM_INDEX)
			{
				s_Voice.voice[num++] = (tT5LVoinceType)(grp_mem[mem_i]+1);
			}
			grp_mem_add += grp_mem[mem_i];
		}
		if((4 == grp_mem_add) || (8 == grp_mem_add))
		{
			s_Voice.voice[5] = pGrp[mem_i];
		}

		if((grp_mem_add != (MAX_GROUP_MEM_NUM*INVALID_GROUP_MEM_INDEX)) && (1 == pComtex->needPushed[grp_i]))
		{
			pComtex->grp_FilterDelay[grp_i]++;
			if(pComtex->grp_FilterDelay[grp_i] >= 500)
			{
				pComtex->grp_FilterDelay[grp_i] = 0 ;
				sdwe_VoicePrintfPush(&s_Voice,num);
				//push
				pComtex->needPushed[grp_i] = 0;
			}
		}
		else
		{
			pComtex->grp_FilterDelay[grp_i] = 0 ;
		}
	}
}


//公共函数：发送 语音提示 给屏幕
UINT8 screenPublic_VoicePrintfMainfunction(T5LType *pSdwe)
{
	static UINT8 u8Vstatus = 0 , voice_i = 0;
	static tVoiceArryStruct s_Voice;
	static UINT32 u32Ticks = 0 ,tickOffset = 900;
	UINT8 localStatus = FALSE;
	//
	if(FALSE == gSystemPara.ScreenVoiceSwitch)
	{
		return localStatus;
	}
	screenPublic_VoiceScan(pSdwe);
	switch(u8Vstatus)
	{
		//pop
		case 0:
			if(TRUE == sdwe_VoicePrintfPop(&s_Voice))
			{
				voice_i = 0;
				u8Vstatus = 1;//start 
			}
			else
			{
				localStatus = TRUE;//special handle , no anly voice need printf return TRUE
			}
		break;
		
		//===========voice_i start
		case 1://printf V1
			if(TRUE == screenT5L_OutputVoice(pSdwe,s_Voice.voice[voice_i]))
			{
				voice_i++;
				u8Vstatus = 2;
				u32Ticks = pSdwe->CurTick ;
			}				
		break;
		//===========voice_i wait time
		case 2:
			if(voice_i == s_Voice.num-1)
			{
				tickOffset = 1200;//配平成功
			}
			else
			{
				tickOffset = 900;
			}

			if(pSdwe->CurTick >= (u32Ticks + tickOffset))
			{
				u8Vstatus=3;
			}
		break;
		//===========voice_i end check
		case 3:
			if(voice_i < s_Voice.num)
			{
				u8Vstatus = 1;
			}
			else
			{
				u8Vstatus = 0;
			}
		break;
		//
		default:
			u8Vstatus = 0 ;
			localStatus = TRUE;
		break;
	}
	return localStatus;
}

#endif //endof file
