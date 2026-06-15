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
	VoiceTypeYu_17 = 25,
	VoiceTypePeiPin_18 = 26,
	T5L_VoiceTypeNum_0= 0,
	T5L_VoiceTypeNum_1= 1,
	T5L_VoiceTypeNum_2= 2,
	T5L_VoiceTypeNum_3= 3,
	T5L_VoiceTypeNum_4= 4,
	T5L_VoiceTypeNum_5= 5,
	T5L_VoiceTypeNum_6= 6,
	T5L_VoiceTypeNum_7= 7,
	T5L_VoiceTypeNum_8= 8,
	T5L_VoiceTypeNum_9= 9,
	T5L_VoiceTypeNum_10= 10,
	T5L_VoiceTypeNum_11= 11,
	T5L_VoiceTypeNum_12= 12,
	T5L_VoiceTypeNum_13= 13,
	T5L_VoiceTypeNum_14= 14,
	T5L_VoiceTypeNum_15= 15,
	T5L_VoiceTypeNum_16= 16,
	T5L_VoiceTypeNum_17= 17,
	T5L_VoiceTypeNum_18= 18,
	T5L_VoiceTypeNum_19= 19,
	T5L_VoiceTypeNum_20= 20,
	T5L_VoiceTypeNum_21= 21,
	T5L_VoiceTypeNum_22= 22,
	T5L_VoiceTypeNum_23= 23,
	T5L_VoiceTypeNum_24= 24,
	T5L_VoiceTypeNum_25= 25,
	T5L_VoiceTypeNum_26= 26,
	T5L_VoiceTypeNum_27= 27,
	T5L_VoiceTypeNum_28= 28,
	T5L_VoiceTypeNum_29= 29,
	T5L_VoiceTypeNum_30= 30,
	T5L_VoiceTypeNum_31= 31,
	T5L_VoiceTypeNum_32= 32,
	T5L_VoiceTypeNum_33= 33,
	T5L_VoiceTypeNum_34= 34,
	T5L_VoiceTypeNum_35= 35,
	T5L_VoiceTypeNum_36= 36,
	T5L_VoiceTypeNum_37= 37,
	T5L_VoiceTypeNum_38= 38,
	T5L_VoiceTypeNum_39= 39,
	T5L_VoiceTypeNum_40= 40,
	T5L_VoiceTypeNum_41= 41,
	T5L_VoiceTypeNum_42= 42,
	T5L_VoiceTypeNum_43= 43,
	T5L_VoiceTypeNum_44= 44,
	T5L_VoiceTypeNum_45= 45,
	T5L_VoiceTypeNum_46= 46,
	T5L_VoiceTypeNum_47= 47,
	T5L_VoiceTypeNum_48= 48,
	T5L_VoiceTypeNum_49= 49,
	T5L_VoiceTypeNum_50= 50,
	T5L_VoiceTypeNum_51= 51,
	T5L_VoiceTypeNum_52= 52,
	T5L_VoiceTypeNum_53= 53,
	T5L_VoiceTypeNum_54= 54,
	T5L_VoiceTypeNum_55= 55,
	T5L_VoiceTypeNum_56= 56,
	T5L_VoiceTypeNum_57= 57,
	T5L_VoiceTypeNum_58= 58,
	T5L_VoiceTypeNum_59= 59,
	T5L_VoiceTypeNum_60= 60,
	T5L_VoiceTypeNum_61= 61,
	T5L_VoiceTypeNum_62= 62,
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
