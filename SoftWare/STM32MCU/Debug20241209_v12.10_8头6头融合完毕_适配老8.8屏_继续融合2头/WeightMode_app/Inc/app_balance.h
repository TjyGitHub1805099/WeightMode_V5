#ifndef __APP_BALANCE_H__
#define __APP_BALANCE_H__
#include "typedefine.h"
#include "app_t5l_ctrl.h"

#define MAX_GROUP_MEM_NUM       (8)
#define INVALID_GROUP_MEM_INDEX (0xFF)
typedef struct sGroupInfoStruct
{
    uint16 grp_Min;
    uint16 grp_Max;
    uint8  grp_MenbNum;
    uint8  grp_MenbArry[MAX_GROUP_MEM_NUM];
    uint8  grp_Color;
    uint8  grp_Enable;
    uint8  grp_EnableColor;
} tGroupInfoStruct;

typedef struct sChannelInfoStruct
{
    int32 chnl_Weight;
    uint8 chnl_Color;
} tChannelInfoStruct;
typedef struct sScaleInfoStruct
{
    //
    uint8 scl_Point;
    uint8 scl_TotalChnlNum;
    uint8 scl_TotalGrpNum;
    uint8 scl_EqlNum;//single group max equal num
    //
    tChannelInfoStruct *pscl_ChnInfo;
    tGroupInfoStruct *pscl_GrpInfo;
    //
    int32 *pscl_SortWeight;
    uint8 *pscl_SortChnnel;
    uint8 scl_SortNum;
    uint16 scl_MinVlu;
    uint16 scl_MaxVlu;
    uint16 scl_RangeVlu;//error range
    uint16 scl_ZeroRangeVlu;//zero point
    //
} tScaleInfoStruct;

#define SCALE_INVALID_VLU           (0xFF)
#define SCALE_INVALID_COLOR         (LED_COLOR_NONE)
#define SCALE_TOTAL_CHANNEL_NUM     (16)
#define SCALE_TOTAL_GROUP_NUM       (SYS_COLOR_GROUP_NUM)
#define SCALE_MAX_EQUAL_NUM         (5)

extern void BalanceInit(void);
extern void ScaleBalance_MainFunction(T5LType *pSdwe,UINT8 chanel_len);
extern void ScaleBalance_GetGroupMembers(uint8 grp_index , uint8 *pMem);

#endif
