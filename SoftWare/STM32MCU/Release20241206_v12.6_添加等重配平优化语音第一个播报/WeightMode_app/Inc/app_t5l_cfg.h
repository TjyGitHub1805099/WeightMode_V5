#ifndef __APP_T5L_CFG_H__
#define __APP_T5L_CFG_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "typedefine.h"
#include "app_t5l_ctrl.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

//=====================================================================================================================
//屏幕的描述指针地址范围：
//0x9010~0x9100：重量显
//0x9110~0x9160：帮助信息的差值
//0x9210~0x9300：托盘序号
//0x9310~0x9400：托盘背景色
//=====================================================================================================================

typedef struct app_Screen_DpCfg
{
    //  x坐标    	y坐标  		 颜色      	字库/字体大小	 对齐 位数    小数位数 变量类型
    INT16 positionX;
    INT16 positionY;
    INT16 color;
    INT16 size;
    INT16 dnum;
    INT16 fnum;
}appScreenDpCfg_Type;

typedef struct app_Screen_DpColorCfg
{
    //  x坐标    	y坐标
    INT16 positionX;
    INT16 positionY;
}appScreenDpColorCfg_Type;

typedef struct appScreenDpMiscCfg
{
    //  x坐标    	y坐标  		 颜色
    INT16 positionX;//x坐标 2byte
    INT16 positionY;//y坐标 2byte
    INT16 color;//颜色 2byte
}appScreenDpMiscCfg_Type;

typedef struct app_Screen_Cfg
{
    //托盘重量描述指针
    UINT16 weightVluNum;
    INT16 *dpParaAdd_WeightVlu;
    appScreenDpCfg_Type *dpParaVlu_WeightVlu_WXS;//无小数
    appScreenDpCfg_Type *dpParaVlu_WeightVlu_YXS;//小数

    //托盘重量描述指针
    UINT16 helpVluNum;
    INT16 *dpParaAdd_HelpVlu;
    appScreenDpCfg_Type *dpParaVlu_HelpVlu_WXS;//无小数
    appScreenDpCfg_Type *dpParaVlu_HelpVlu_YXS;//小数

    //托盘序号描述指针
    UINT16 weightIndexNum;
    INT16 *dpParaAdd_WeightIndex;
    appScreenDpCfg_Type *dpParaVlu_WeightIndex;

    //托盘颜色描述指针color
    UINT16 weightColorNum;
    INT16 *dpParaAdd_WeightColor;
    appScreenDpColorCfg_Type *dpParaVlu_WeightColor;

    //其他描述指针：X Y 颜色
    UINT16 miscNum;
    INT16 *dpParaAdd_Misc;
    appScreenDpMiscCfg_Type *dpParaVlu_Misc;
}appScreenCfg_Type;

typedef enum app_Screen_enum
{
    APPSCREEN_WEIGHT_NUM_6=0,
    APPSCREEN_WEIGHT_NUM_8,
    APPSCREEN_WEIGHT_NUM_12,
    APPSCREEN_WEIGHT_NUM_16,
    APPSCREEN_WEIGHT_NUM_MAX,
}appScreenCfg_Enum;


#endif
