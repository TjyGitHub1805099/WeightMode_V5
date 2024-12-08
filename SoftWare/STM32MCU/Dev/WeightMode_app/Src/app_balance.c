/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "app_syspara.h"
#include "app_balance.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
tChannelInfoStruct  gChannelInfo[SCALE_TOTAL_CHANNEL_NUM];
tGroupInfoStruct    gGroupInfo[SCALE_TOTAL_GROUP_NUM];
int32               gSortWeight[SCALE_TOTAL_CHANNEL_NUM];
uint8               gSortChnnel[SCALE_TOTAL_CHANNEL_NUM];
tScaleInfoStruct    gScaleInfo;


/*******************************************************************************
 * Functions
 ******************************************************************************/
void GroupInfoClear(tGroupInfoStruct *pscl_GrpInfo)
{
    uint8 mem_i = 0 ;
    pscl_GrpInfo->grp_Min = 0 ;
    pscl_GrpInfo->grp_Max = 0 ;
    pscl_GrpInfo->grp_MenbNum = 0 ;
    pscl_GrpInfo->grp_Color = SCALE_INVALID_COLOR;
    for(mem_i = 0 ; mem_i < MAX_GROUP_MEM_NUM ; mem_i++)
    {
        pscl_GrpInfo->grp_MenbArry[mem_i] = INVALID_GROUP_MEM_INDEX ;
    }
}

void GroupInfoPutInOrder(tScaleInfoStruct *pContex)
{
    uint8 grp_i = 0;
    uint8 l_grp_putinorder = FALSE;
    tGroupInfoStruct *pGrpInfo;
    //5.group check
    for(grp_i = 0 ; grp_i < pContex->scl_TotalGrpNum ; grp_i++)
    {
        l_grp_putinorder = FALSE;
        pGrpInfo = &pContex->pscl_GrpInfo[grp_i];
        //if group member num larger than scl_EqlNum , clear group info
        if(pGrpInfo->grp_MenbNum > pContex->scl_EqlNum)
        {
            l_grp_putinorder = TRUE;
        }
        //if group member num less than 2 , clear group info
        else if(pGrpInfo->grp_MenbNum < 2)
        {
            l_grp_putinorder = TRUE;
        }
        //if group color was invalid , clear group info
        else if( SCALE_INVALID_COLOR == pGrpInfo->grp_Color )
        {
            l_grp_putinorder = TRUE;
        }  
        //if group min/max was at zeroRange , clear group info
        else if((pGrpInfo->grp_Min < pContex->scl_ZeroRangeVlu) || (pGrpInfo->grp_Max < pContex->scl_ZeroRangeVlu))
        {
            l_grp_putinorder = TRUE;
        }
        //if group min/max was at zeroRange , clear group info
        else if(pGrpInfo->grp_Min > pGrpInfo->grp_Max)
        {
            l_grp_putinorder = TRUE;
        }
        //if need putinorder
        if(TRUE == l_grp_putinorder)
        {
            GroupInfoClear(pGrpInfo);
        }
    }    
}

uint8 ExistGroupDilatation(tScaleInfoStruct *pContex , tGroupInfoStruct *pGrpInfo , tChannelInfoStruct *pChnInfo)
{
    uint8 dilatation = FALSE;
    if( (pGrpInfo->grp_Min <= pContex->scl_ZeroRangeVlu) || 
        (pGrpInfo->grp_Max <= pContex->scl_ZeroRangeVlu) ||
        (pChnInfo->chnl_Weight <= pContex->scl_ZeroRangeVlu))
    {
        //doing nothing
    }
    //if weight at min~max
    else if( (pChnInfo->chnl_Weight >= pGrpInfo->grp_Min) && (pChnInfo->chnl_Weight <= pGrpInfo->grp_Max))
    {
        //remain matched doing nothing
        dilatation = TRUE;
    }
    //if weight larger than group max
    else if(pChnInfo->chnl_Weight > pGrpInfo->grp_Max)
    {
        if((pChnInfo->chnl_Weight - pGrpInfo->grp_Min) <=  pContex->scl_RangeVlu)
        {
            //remain matched doing nothing
            //upgrate grp_Max
            pGrpInfo->grp_Max = pChnInfo->chnl_Weight;
            dilatation = TRUE;
        }
    }
    //1.2.2.2.1.2.if weight less than group min
    else if(pChnInfo->chnl_Weight < pGrpInfo->grp_Min)
    {
        if((pGrpInfo->grp_Max - pChnInfo->chnl_Weight) <=  pContex->scl_RangeVlu)
        {
            //remain matched doing nothing
            //upgrate grp_Min
            pGrpInfo->grp_Min = pChnInfo->chnl_Weight;
            dilatation = TRUE;
        }
    }  
    return dilatation;
}

void Balanced_Rejudge(tScaleInfoStruct *pContex)
{
    uint8 chnl_i = 0;
    uint8 grp_i = 0;
    uint8 grp_mem_index_i = 0;
    //uint16 chnl_weight = 0;
    tChannelInfoStruct *pChnInfo;
    tGroupInfoStruct *pGrpInfo;
    uint8 l_continue = FALSE;
    uint8 l_matched = FALSE;
    //1.already balanced rejudge
    for(chnl_i = 0 ; chnl_i < pContex->scl_TotalChnlNum ; chnl_i++)
    {
        l_matched = FALSE;
        pChnInfo = &pContex->pscl_ChnInfo[chnl_i];
        //1.1.if channel color was invalid , jump check
        if(SCALE_INVALID_COLOR == pChnInfo->chnl_Color)
        {
            l_continue = TRUE;
        }
        else
        {
            l_continue = FALSE;
        }
        //1.2.if channel color was valid , continue check
        if(FALSE == l_continue)
        {
            //1.2.1.from group find out the matched color
            for(grp_i = 0 ; grp_i < pContex->scl_TotalGrpNum ; grp_i++)
            {
                pGrpInfo = &pContex->pscl_GrpInfo[grp_i];
                //1.2.1.1.if matched break
                if( pChnInfo->chnl_Color == pGrpInfo->grp_Color )
                {
                    break;
                }                
            }
            //1.2.2.1.if channel color not matched the group(color) clear it 
            if(grp_i >= pContex->scl_TotalGrpNum)
            {
                l_matched = FALSE;
                pChnInfo->chnl_Color = SCALE_INVALID_COLOR; 
            }
            //1.2.2.2.if color was matched , rejudge it
            else
            {
                l_matched = ExistGroupDilatation(pContex,pGrpInfo,pChnInfo);
                //1.2.2.2.2.if channel color matched but weight not equal , minus memnum
                if(FALSE == l_matched)
                {
                    pChnInfo->chnl_Color = SCALE_INVALID_COLOR; 
                    if( pGrpInfo->grp_MenbNum > 0 )
                    {
                        for(grp_mem_index_i = 0 ; grp_mem_index_i < pGrpInfo->grp_MenbNum ; grp_mem_index_i++)
                        {
                            if(pGrpInfo->grp_MenbArry[grp_mem_index_i] == chnl_i)
                            {
                                pGrpInfo->grp_MenbArry[grp_mem_index_i] = INVALID_GROUP_MEM_INDEX ;
                                break;
                            }
                        }     
                        pGrpInfo->grp_MenbNum--;
                        
                    }     
                }
            }
        }
    }
}

void BalanceRemainChannelToExistGroup(tScaleInfoStruct *pContex)
{
    uint8 chnl_i = 0;
    uint8 grp_i = 0;
    uint8 grp_mem_index_i = 0;
    //uint16 chnl_weight = 0;
    tChannelInfoStruct *pChnInfo;
    tGroupInfoStruct *pGrpInfo;
    uint8 l_continue = FALSE;
    uint8 l_matched = FALSE;
    //1.remain channel balance to exist group
    for(chnl_i = 0 ; chnl_i < pContex->scl_TotalChnlNum ; chnl_i++)
    {
        l_continue = FALSE;
        pChnInfo = &pContex->pscl_ChnInfo[chnl_i];
        if(SCALE_INVALID_COLOR != pChnInfo->chnl_Color)
        {
            l_continue = TRUE;
        }
        else
        {
            l_continue = FALSE;
        }
        if(FALSE == l_continue)
        {
            l_matched = FALSE;
            for(grp_i = 0 ; grp_i < pContex->scl_TotalGrpNum ; grp_i++)
            {
                l_continue = FALSE;
                pGrpInfo = &pContex->pscl_GrpInfo[grp_i];
                //
                if(pGrpInfo->grp_MenbNum >= pContex->scl_EqlNum)
                {
                    l_continue = TRUE;
                }
                else
                {
                    l_continue = FALSE;
                }
                if(FALSE == l_continue)
                {
                    l_matched = ExistGroupDilatation(pContex,pGrpInfo,pChnInfo);
                    //
                    if(TRUE == l_matched)
                    {
                        for(grp_mem_index_i = 0 ; grp_mem_index_i < MAX_GROUP_MEM_NUM ; grp_mem_index_i++)
                        {
                            if(pGrpInfo->grp_MenbArry[grp_mem_index_i] == INVALID_GROUP_MEM_INDEX)
                            {
                                pGrpInfo->grp_MenbArry[grp_mem_index_i] = chnl_i ;
                                break;
                            }
                        } 
                        //pGrpInfo->grp_MenbArry[pGrpInfo->grp_MenbNum] = chnl_i ;
                        pGrpInfo->grp_MenbNum = pGrpInfo->grp_MenbNum + 1;
                        pChnInfo->chnl_Color = pGrpInfo->grp_Color;
                        break;
                    }
                }
            }
        }
    }
}

void BalancBubbleSort(int32 chn_weight[], uint8 chn_index[] ,int len)
{
    int i, j;
    int32 temp_chn_weight;
    uint8 temp_chn_index;
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - 1 - i; j++)
        {
            if (chn_weight[j] > chn_weight[j + 1]) 
            {
                temp_chn_weight = chn_weight[j];
                chn_weight[j] = chn_weight[j + 1];
                chn_weight[j + 1] = temp_chn_weight;
                //
                temp_chn_index = chn_index[j];
                chn_index[j] = chn_index[j + 1];
                chn_index[j + 1] = temp_chn_index;               
            }
        }
    }   
}

uint8 BalancGetUseGroup(tScaleInfoStruct *pContex)
{
    //get used group , if grp_Enable = enable  and grp_EnableColor not SCALE_INVALID_COLOR and grp_Color was SCALE_INVALID_COLOR
    uint8 ret_grp_index = SCALE_INVALID_VLU;
    uint8 grp_i = 0;
    tGroupInfoStruct *pGrpInfo;
    //
    for(grp_i = 0 ; grp_i < pContex->scl_TotalGrpNum ; grp_i++)
    {
        pGrpInfo = &pContex->pscl_GrpInfo[grp_i];
        if((1 == pGrpInfo->grp_Enable) && 
           (SCALE_INVALID_COLOR != pGrpInfo->grp_EnableColor) &&
           (SCALE_INVALID_COLOR == pGrpInfo->grp_Color))
        {
            GroupInfoClear(pGrpInfo);
            break;
        }
    }
    //
    if(grp_i < pContex->scl_TotalGrpNum)
    {
        ret_grp_index = grp_i;
    }
    //
    return ret_grp_index;
}

void BalanceRemainChannelToEmptyGroup(tScaleInfoStruct *pContex)
{
    uint8 i = 0 ;
    uint8 chnl_i = 0;
    //uint8 grp_i = 0;
    //uint16 chnl_weight = 0;
    tChannelInfoStruct *pChnInfo;
    tGroupInfoStruct *pGrpInfo;
    uint8 l_continue = FALSE;
    //uint8 l_matched = FALSE;
    uint8 l_emptGroupId = SCALE_INVALID_VLU;
    uint8 srt_i = 0 ,srt_j = 0;
    uint8 grp_l_MenbNum = 0;
    //1.remain channel upgrate pscl_SortWeight and pscl_SortChnnel
    pContex->scl_SortNum = 0 ;
    for(chnl_i = 0 ; chnl_i < pContex->scl_TotalChnlNum ; chnl_i++)
    {
        l_continue = FALSE;
        pChnInfo = &pContex->pscl_ChnInfo[chnl_i];
        if(SCALE_INVALID_COLOR != pChnInfo->chnl_Color)
        {
            l_continue = TRUE;
        }
        else
        {
            l_continue = FALSE;
        }
        if((FALSE == l_continue) && (pChnInfo->chnl_Weight > pContex->scl_ZeroRangeVlu))
        {
            //sort remain
            pContex->pscl_SortWeight[pContex->scl_SortNum] = pChnInfo->chnl_Weight;
            pContex->pscl_SortChnnel[pContex->scl_SortNum] = chnl_i;
            pContex->scl_SortNum++;
        }
    }
    //clear not used sort arry
    for(srt_i = pContex->scl_SortNum ; srt_i<pContex->scl_TotalChnlNum; srt_i++)
    {
        pContex->pscl_SortWeight[srt_i] = 0;
        pContex->pscl_SortChnnel[srt_i] = SCALE_INVALID_VLU;
    }
    //get useable group
    l_emptGroupId = BalancGetUseGroup(pContex);
    //2.if group useable and srt num larger than 2
    if((pContex->scl_SortNum >= 2) && (SCALE_INVALID_VLU != l_emptGroupId))
    {
        //2.1.sort pscl_SortWeight and extend pscl_SortChnnel
        BalancBubbleSort(&pContex->pscl_SortWeight[0],&pContex->pscl_SortChnnel[0],pContex->scl_SortNum);
        //2.2.findout the channel which at error range 
        for(srt_i = 0 ; srt_i < pContex->scl_SortNum ; srt_i++)//from srt_i
        {
            l_continue = FALSE;
            grp_l_MenbNum = 1 ;
            if(pContex->pscl_SortWeight[srt_i] >= pContex->scl_ZeroRangeVlu)//larger than zero range
            {
                for(srt_j = (srt_i+1); srt_j < pContex->scl_SortNum ; srt_j++)//to srt_j
                {
                    if(pContex->pscl_SortWeight[srt_j] - pContex->pscl_SortWeight[srt_i] <= pContex->scl_RangeVlu)//at error range
                    {
                        grp_l_MenbNum++;
                        if(grp_l_MenbNum >= pContex->scl_EqlNum)//if grp_MenbNum larger than set mum scl_EqlNum , break
                        {
                            break;
                        }
                    }
                    else//outof error range , break
                    {
                        break;
                    }
                }
                //findout num larger than 2
                if(grp_l_MenbNum >= 2)
                {
                    l_emptGroupId = BalancGetUseGroup(pContex);
                    if(SCALE_INVALID_VLU != l_emptGroupId)
                    {
                        pGrpInfo = &pContex->pscl_GrpInfo[l_emptGroupId%pContex->scl_TotalGrpNum];
                        //upgrate pGrpInfo : grp_Min , grp_Max , grp_MenbNum and color
                        pGrpInfo->grp_Min = pContex->pscl_SortWeight[srt_i] ;
                        pGrpInfo->grp_Max = pContex->pscl_SortWeight[srt_i + grp_l_MenbNum - 1] ;
                        pGrpInfo->grp_MenbNum = grp_l_MenbNum ;
                        pGrpInfo->grp_Color = pGrpInfo->grp_EnableColor;
                        //upgrate pChnInfo : chnl_Color
                        for(i = 0 ; i < grp_l_MenbNum ; i++)
                        {
                            chnl_i = pContex->pscl_SortChnnel[i];//reget channel index use sortChannel
                            pGrpInfo->grp_MenbArry[i] = chnl_i ;
                            pChnInfo = &pContex->pscl_ChnInfo[chnl_i];
                            pChnInfo->chnl_Color = pGrpInfo->grp_Color;
                        }
                    }
                }
            }
            //
            srt_i = srt_i + grp_l_MenbNum - 1;
            //if not useable group , break
            if(SCALE_INVALID_VLU == l_emptGroupId)
            {
                break;
            }
        }
    }
}

void UpgrateChannelColor(tScaleInfoStruct *pContex , T5LType *pSdwe)
{
    uint8 chnl_i = 0;
    uint8 color = SCALE_INVALID_COLOR;
    tChannelInfoStruct *pChnInfo;
    INT16 *pColor = pSdwe->screenCycle.pColor;
    for(chnl_i = 0 ; chnl_i < pContex->scl_TotalChnlNum ; chnl_i++)
    {
        pChnInfo = &pContex->pscl_ChnInfo[chnl_i];
        color = pChnInfo->chnl_Color;
        pColor[chnl_i] = color;
        //set color to hw : LED and ScreenBlackColor
    }
}

void BalanceInit(void)
{
    tScaleInfoStruct *pContex = &gScaleInfo;
    uint8 chnl_i = 0;
    uint8 grp_i = 0;
    tChannelInfoStruct *pChnInfo;
    tGroupInfoStruct *pGrpInfo;
    //
    pContex->scl_TotalChnlNum = SCALE_TOTAL_CHANNEL_NUM;
    pContex->scl_TotalGrpNum = SCALE_TOTAL_GROUP_NUM;
    pContex->scl_EqlNum = ONLINE_CHANNEL_NUM;
    if(0 == gSystemPara.EqualBanance)
    {
        pContex->scl_EqlNum = 2;
    }

    pContex->pscl_ChnInfo = &gChannelInfo[0];
    pContex->pscl_GrpInfo = &gGroupInfo[0];
    pContex->pscl_SortWeight = &gSortWeight[0];
    pContex->pscl_SortChnnel = &gSortChnnel[0];

    pContex->scl_MinVlu = gSystemPara.minWeight;
    pContex->scl_MaxVlu = gSystemPara.maxWeight;
    pContex->scl_RangeVlu = gSystemPara.errRange;
    pContex->scl_ZeroRangeVlu = gSystemPara.zeroRange;
    if(1 == gSystemPara.xiaoShuXianShi)
    {
        pContex->scl_MinVlu = 10*gSystemPara.minWeight;
        pContex->scl_MaxVlu = 10*gSystemPara.maxWeight;
        pContex->scl_RangeVlu = 10*gSystemPara.errRange;
        pContex->scl_ZeroRangeVlu =10*gSystemPara.zeroRange;
    }

    //
    for(chnl_i = 0 ; chnl_i < pContex->scl_TotalChnlNum ; chnl_i++)
    {
        pChnInfo = &pContex->pscl_ChnInfo[chnl_i];
        //
        pChnInfo->chnl_Color = SCALE_INVALID_COLOR;
    }

    //
    for(grp_i = 0 ; grp_i < pContex->scl_TotalGrpNum ; grp_i++)
    {
        pGrpInfo = &pContex->pscl_GrpInfo[grp_i];
        //
        GroupInfoClear(pGrpInfo);
        //
        pGrpInfo->grp_Enable = 1;
        pGrpInfo->grp_EnableColor = gSystemPara.userColorSet[grp_i];
    }
}

void PushWeightIn_ScaleBalance(tScaleInfoStruct *pContex , T5LType *pSdwe,UINT8 chanel_len)
{
    uint8 chnl_i = 0;
    tChannelInfoStruct *pChnInfo;
    INT32 *pData = pSdwe->screenCycle.pData;
    if(chanel_len <= pContex->scl_TotalChnlNum)
    {
        pContex->scl_TotalChnlNum = chanel_len;
        for(chnl_i = 0 ; chnl_i < pContex->scl_TotalChnlNum ; chnl_i++)
        {
            pChnInfo = &pContex->pscl_ChnInfo[chnl_i];
            //
            pChnInfo->chnl_Weight = pData[chnl_i];
        }
    }
}
void ScaleBalance_GetGroupMembers(uint8 grp_index , uint8 *pMem)
{
    tScaleInfoStruct *pContex = &gScaleInfo;
    memcpy(pMem,&pContex->pscl_GrpInfo[grp_index].grp_MenbArry[0],MAX_GROUP_MEM_NUM);
}

void ScaleBalance_MainFunction(T5LType *pSdwe,UINT8 chanel_len)
{
    tScaleInfoStruct *pContex = &gScaleInfo;
    //push weight to pscl_ChnInfo and set scl_TotalChnlNum
    PushWeightIn_ScaleBalance(pContex,pSdwe,chanel_len);
    //1.group info put in order
    GroupInfoPutInOrder(pContex);
    //2.equal channel balance again
    Balanced_Rejudge(pContex);
    //3.remain channel balance to exist group
    BalanceRemainChannelToExistGroup(pContex);
    //4.remain channel balance to empty group
    BalanceRemainChannelToEmptyGroup(pContex);
    //5.upgrate channel color
    UpgrateChannelColor(pContex,pSdwe);
}

