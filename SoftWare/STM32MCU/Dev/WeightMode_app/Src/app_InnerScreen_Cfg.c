/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "typedefine.h"
#include "app_t5l_ctrl.h"
#include "app_InnerScreen_Cfg.h"
#include "app_t5l_cfg.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

//=====================================================================================================================
//屏幕的描述指针地址范围：
//0x9010~0x9080：托盘重量
//0x9110~0x9160：帮助信息的差值
//0x9210~0x9280：托盘序号
//=====================================================================================================================

INT16 IS_WeightVlu_DP_Add[SCREEN_DESCRIBLE_POINT_NUM]  ={0x9011,0x9021,0x9031,0x9041,0x9051,0x9061,0x9071,0x9081,0x9091,0x90A1,0x90B1,0x90C1,0x90D1,0x90E1,0x90F1,0x9101};
INT16 IS_HelpVlue_DP_Add[SCREEN_DESCRIBLE_POINT_NUM]   ={0x9111,0x9121,0x9131,0x9141,0x9151,0x9161,0x9171,0x9181,0x9191,0x91A1,0x91B1,0x91C1,0x91D1,0x91E1,0x91F1,0x9201};
INT16 IS_WeightIndex_DP_Add[SCREEN_DESCRIBLE_POINT_NUM]={0x9211,0x9221,0x9231,0x9241,0x9251,0x9261,0x9271,0x9281,0x9291,0x92A1,0x92B1,0x92C1,0x92D1,0x92E1,0x92F1,0x9301};

//=====================================================================================================================
//=================================================[1.托盘重量的描述指针]================================================
//=====================================================================================================================
//托盘的重量显示：不带小数点显示
appScreenDpCfg_Type IS_8H_WeightVlue_DP_Vlu_WuXiaoShu[8]=
{
//  x坐标    	y坐标  		 颜色      	字库/字体大小	 对齐 位数    小数位数 变量类型
	{0x0056, 	0x0060, 	0x6474,		0x003C,			0x0204,			0x0001},//1
	{0x0056, 	0x0149, 	0x6474,		0x003C,			0x0204,			0x0001},//2
	{0x01DC, 	0x0060, 	0x6474,		0x003C,			0x0204,			0x0001},//3
	{0x01DC, 	0x0149, 	0x6474,		0x003C,			0x0204,			0x0001},//4
	{0x0362, 	0x0060, 	0x6474,		0x003C,			0x0204,			0x0001},//5
	{0x0362, 	0x0149, 	0x6474,		0x003C,			0x0204,			0x0001},//6
	{0x04E8, 	0x0060, 	0x6474,		0x003C,			0x0204,			0x0001},//7
	{0x04E8, 	0x0149, 	0x6474,		0x003C,			0x0204,			0x0001},//8
};
//托盘的重量显示：带小数点显示
appScreenDpCfg_Type IS_8H_WeightVlue_DP_Vlu_YouXiaoShu[8]=
{
//  x坐标    	y坐标  		 颜色      	字库/字体大小	 对齐 位数    小数位数 变量类型
	{0x0056, 	0x0077, 	0x6474,		0x0028,			0x0204,			0x0101},//1
	{0x0056, 	0x0160, 	0x6474,		0x0028,			0x0204,			0x0101},//2
	{0x01DC, 	0x0077, 	0x6474,		0x0028,			0x0204,			0x0101},//3
	{0x01DC, 	0x0160, 	0x6474,		0x0028,			0x0204,			0x0101},//4
	{0x0362, 	0x0077, 	0x6474,		0x0028,			0x0204,			0x0101},//5
	{0x0362, 	0x0160, 	0x6474,		0x0028,			0x0204,			0x0101},//6
	{0x04E8, 	0x0077, 	0x6474,		0x0028,			0x0204,			0x0101},//7
	{0x04E8, 	0x0160, 	0x6474,		0x0028,			0x0204,			0x0101},//8
};

//=====================================================================================================================
//=================================================[2.帮助信息的描述指针]================================================
//=====================================================================================================================
#define DESCRIBLE_POINT_HELP_COLOR			(0XF810)//红色
#define DESCRIBLE_POINT_HELP_X_POS			(0X06E4)//1764
#define DESCRIBLE_POINT_HELP_WU_XIAOSHU		(0X001A)//0号字库 字体大小26
#define DESCRIBLE_POINT_HELP_YOU_XIAOSHU	(0X0014)//0号字库 字体大小20
//帮助信息：不带小数显示
appScreenDpCfg_Type IS_8H_HelpVlue_DP_Vlu_WuXiaoShu[4]=
{
//       x    	y      		颜色      	字库/字体大小	 对齐 整数位数    小数位数 变量类型
	{DESCRIBLE_POINT_HELP_X_POS, 	97, 	DESCRIBLE_POINT_HELP_COLOR,		DESCRIBLE_POINT_HELP_WU_XIAOSHU,			0x0204,			0x0000},
	{DESCRIBLE_POINT_HELP_X_POS, 	167, 	DESCRIBLE_POINT_HELP_COLOR,		DESCRIBLE_POINT_HELP_WU_XIAOSHU,			0x0204,			0x0000},
	{DESCRIBLE_POINT_HELP_X_POS, 	232, 	DESCRIBLE_POINT_HELP_COLOR,		DESCRIBLE_POINT_HELP_WU_XIAOSHU,			0x0204,			0x0000},
	{DESCRIBLE_POINT_HELP_X_POS, 	303, 	DESCRIBLE_POINT_HELP_COLOR,		DESCRIBLE_POINT_HELP_WU_XIAOSHU,			0x0204,			0x0000},
};
//帮助信息：带小数显示
appScreenDpCfg_Type IS_8H_HelpVlue_DP_Vlu_YouXiaoShu[4]=
{
//       x    	y      		颜色      	字库/字体大小	 对齐 整数位数    小数位数 变量类型
	{DESCRIBLE_POINT_HELP_X_POS, 	105, 	DESCRIBLE_POINT_HELP_COLOR,		DESCRIBLE_POINT_HELP_YOU_XIAOSHU,			0x0204,			0x0100},
	{DESCRIBLE_POINT_HELP_X_POS, 	175, 	DESCRIBLE_POINT_HELP_COLOR,		DESCRIBLE_POINT_HELP_YOU_XIAOSHU,			0x0204,			0x0100},
	{DESCRIBLE_POINT_HELP_X_POS, 	240, 	DESCRIBLE_POINT_HELP_COLOR,		DESCRIBLE_POINT_HELP_YOU_XIAOSHU,			0x0204,			0x0100},
	{DESCRIBLE_POINT_HELP_X_POS, 	310, 	DESCRIBLE_POINT_HELP_COLOR,		DESCRIBLE_POINT_HELP_YOU_XIAOSHU,			0x0204,			0x0100},
};

//=====================================================================================================================
//=================================================[3.托盘序号的描述指针]================================================
//=====================================================================================================================
appScreenDpCfg_Type IS_8H_WeightIndex_DP_Vlu[8]=
{
//  x坐标    	y坐标  		 颜色      	字库/字体大小	 对齐 位数    小数位数 变量类型
	{0x00BC, 	0x0017, 	0x6474,		0x003C,			0x0204,			0x0001},
	{0x00BC, 	0x0109, 	0x6474,		0x003C,			0x0204,			0x0001},
	{0x0241, 	0x0017, 	0x6474,		0x003C,			0x0204,			0x0001},
	{0x0241, 	0x0109, 	0x6474,		0x003C,			0x0204,			0x0001},
	{0x03C7, 	0x0017, 	0x6474,		0x003C,			0x0204,			0x0001},
	{0x03C7, 	0x0109, 	0x6474,		0x003C,			0x0204,			0x0001},
	{0x054D, 	0x0017, 	0x6474,		0x003C,			0x0204,			0x0001},
	{0x054D, 	0x0109, 	0x6474,		0x003C,			0x0204,			0x0001},
};

//
appScreenCfg_Type innerScreenCfg[APPSCREEN_WEIGHT_NUM_MAX]={
	//APPSCREEN_WEIGHT_NUM_6
	{
		6,
		IS_WeightVlu_DP_Add,
		IS_8H_WeightVlue_DP_Vlu_WuXiaoShu,
		IS_8H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		4,
		IS_HelpVlue_DP_Add,
		IS_8H_HelpVlue_DP_Vlu_WuXiaoShu,
		IS_8H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		6,
		IS_WeightIndex_DP_Add,
		IS_8H_WeightIndex_DP_Vlu,
		\
		0,//小屏目前没有对背景色添加描述指针
		0,
		0,
	},

	//APPSCREEN_WEIGHT_NUM_8
	{
		8,
		IS_WeightVlu_DP_Add,
		IS_8H_WeightVlue_DP_Vlu_WuXiaoShu,
		IS_8H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		4,
		IS_HelpVlue_DP_Add,
		IS_8H_HelpVlue_DP_Vlu_WuXiaoShu,
		IS_8H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		8,
		IS_WeightIndex_DP_Add,
		IS_8H_WeightIndex_DP_Vlu,
		\
		0,
		0,
		0,
	},

	//APPSCREEN_WEIGHT_NUM_12
	{
		12,
		IS_WeightVlu_DP_Add,
		IS_8H_WeightVlue_DP_Vlu_WuXiaoShu,
		IS_8H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		4,
		IS_HelpVlue_DP_Add,
		IS_8H_HelpVlue_DP_Vlu_WuXiaoShu,
		IS_8H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		12,
		IS_WeightIndex_DP_Add,
		IS_8H_WeightIndex_DP_Vlu,
		\
		0,
		0,
		0,
	},

	//APPSCREEN_WEIGHT_NUM_16
	{
		16,
		IS_WeightVlu_DP_Add,
		IS_8H_WeightVlue_DP_Vlu_WuXiaoShu,
		IS_8H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		4,
		IS_HelpVlue_DP_Add,
		IS_8H_HelpVlue_DP_Vlu_WuXiaoShu,
		IS_8H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		16,
		IS_WeightIndex_DP_Add,
		IS_8H_WeightIndex_DP_Vlu,
		\
		0,
		0,
		0,
	},
};
