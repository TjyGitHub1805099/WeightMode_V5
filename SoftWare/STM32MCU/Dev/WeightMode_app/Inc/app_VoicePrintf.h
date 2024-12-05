#ifndef __APP_VOICEPRINTF_H__
#define __APP_VOICEPRINTF_H__
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "typedefine.h"
#include "app_t5l_ctrl.h"
#include "app_balance.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
//语音队列：深度
#define T5L_VOICE_MAX_GROUP_NUM		(6)
#define T5L_VOICE_MAX_MEMBR_NUM		(8)

//语音序号
typedef enum VoinceType
{
	T5L_VoiceTypeNum_0 = 0,
	T5L_VoiceTypeNum_1 = 1,
	T5L_VoiceTypeNum_2 = 2,
	T5L_VoiceTypeNum_3 = 3,
	T5L_VoiceTypeNum_4 = 4,
	T5L_VoiceTypeNum_5 = 5,
	T5L_VoiceTypeNum_6 = 6,
	T5L_VoiceTypeNum_7 = 7,
	T5L_VoiceTypeNum_8 = 8,
	T5L_VoiceTypeNum_9 = 9,
	T5L_VoiceTypeNum_10 = 10,
	T5L_VoiceTypeNum_11 = 11,
	T5L_VoiceTypeNum_12 = 12,
	T5L_VoiceTypeNum_13 = 13,
	T5L_VoiceTypeNum_14 = 14,
	T5L_VoiceTypeNum_15 = 15,
	T5L_VoiceTypeNum_16 = 16,
	VoiceTypeYu_17 = 17,
	VoiceTypePeiPin_18 = 18,
	VoiceTypeMax,
}tT5LVoinceType;

typedef struct sVoiceArryStruct
{
    tT5LVoinceType voice[T5L_VOICE_MAX_MEMBR_NUM+2];//配平成功 + max
	UINT8 num;
} tVoiceArryStruct;

typedef struct sVoiceInfoStruct
{
	tVoiceArryStruct voiceGroup[T5L_VOICE_MAX_GROUP_NUM];
	uint8 grp_MenbArry[SCALE_TOTAL_GROUP_NUM][MAX_GROUP_MEM_NUM];
	uint16 grp_FilterDelay[SCALE_TOTAL_GROUP_NUM];
	uint8 needPushed[SCALE_TOTAL_GROUP_NUM];
	uint8 printCplt[SCALE_TOTAL_GROUP_NUM][2];
	UINT8 u8Push_i;
	UINT8 u8Pop_i;
	UINT8 u8TotalNum;
} tVoiceInfoStruct;

/*******************************************************************************
 * Functions
 ******************************************************************************/
extern UINT8 screenT5L_OutputVoice(T5LType *pSdwe,UINT8 voiceId);
extern void sdwe_VoicePrintfPush(tVoiceArryStruct *pVoice,UINT8 num);
extern UINT8 screenPublic_VoicePrintfMainfunction(T5LType *pSdwe);

#endif
