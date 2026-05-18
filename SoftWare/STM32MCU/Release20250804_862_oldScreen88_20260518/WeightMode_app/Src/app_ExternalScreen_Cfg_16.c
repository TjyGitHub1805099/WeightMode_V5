/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "typedefine.h"
#include "app_t5l_ctrl.h"
#include "app_ExternalScreen_Cfg.h"
#include "app_t5l_cfg.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

//======================================================================================================================
/*
屏幕的描述指针地址分配原则：地址不能重复（可以先占满具体使用更具具体值来）
--------------------------------------------------------------------------------------------------------------------
0、托盘数量		|		6头      	|		 8头      	|		 12头     	|		 16头        |		2头     	
--------------------------------------------------------------------------------------------------------------------
1、托盘重量		|	0x9010~0x90F0	|	0x9410~0x94F0	|	0x9810~0x98F0	|	0x9C10~0x9CF0   |	0xA010~0xA0F0	
--------------------------------------------------------------------------------------------------------------------
2、帮助信息		|	0x9110~0x91F0	|	0x9510~0x95F0	|	0x9910~0x99F0	|	0x9D10~0x9DF0   |	0xA110~0xA1F0	
--------------------------------------------------------------------------------------------------------------------
3、托盘序号		|	0x9210~0x92F0	|	0x9610~0x96F0	|	0x9A10~0x9AF0	|	0x9E10~0x9EF0   |	0xA210~0xA2F0	
--------------------------------------------------------------------------------------------------------------------
4、托盘背景		|	0x9310~0x93F0	|	0x9710~0x97F0	|	0x9B10~0x9BF0	|	0x9F10~0x9FF0   |	0xA310~0xA3F0	
--------------------------------------------------------------------------------------------------------------------
*/

/*
数据变量显示指令存储格式表：描述指针使用（详见2.7.1 描述指针的含义与理解）
------------------------------------------------------------------------------------------------------------------------
地址 	|	SP描述指针偏移量 	|	定义 				 数据长度(字节) 	|	说明 
------------------------------------------------------------------------------------------------------------------------
0x06 	|	0x00				|	*VP 			|			2 			|	变量指针 
------------------------------------------------------------------------------------------------------------------------
0x07 	|	0x01				|	X,Y 			|			2 			|	X起始显示位置，显示字符串左上角坐标。 
------------------------------------------------------------------------------------------------------------------------
0x08 	|	0x02				|	X,Y 			|			2 			|	Y起始显示位置，显示字符串左上角坐标。 
------------------------------------------------------------------------------------------------------------------------
0x0C 	|	0x03				|	COLOR 			|			2 			|	显示颜色 
------------------------------------------------------------------------------------------------------------------------
0x0E 	|	0x04:H				|	Lib_ID 			|			1 			|	ASCII 字库位置 
------------------------------------------------------------------------------------------------------------------------
0x0F 	|	0x04:L				|	字体大小 		|			1 			|	字符 x 方向点阵数 
------------------------------------------------------------------------------------------------------------------------
0x10 	|	0x05:H				|	对齐方式 		|			1 			|	0x00=左对齐 0x01=右对齐 0x02=居中 
------------------------------------------------------------------------------------------------------------------------
0x11 	|	0x05:L				|	整数位数 		|			1 			|	显示整数位。整数位数和小数位数之和不能超过 20。 
------------------------------------------------------------------------------------------------------------------------
0x12 	|	0x06:H				|	小数位数 		|			1 			|	显示整数位。整数位数和小数位数之和不能超过 20。
------------------------------------------------------------------------------------------------------------------------ 
0x13 	|	0x06:L				|	变量数据类型 	|			1           |	 0x00=整数（2 字节），范围为-32768 到 32767 
																				0x01=长整数（4 字节），范围为-2147483648 到 2147483647 
																				0x02=*VP 高字节，无符号数，范围 0 到 255 
																				0x03=*VP 低字节，无符号数，范围 0 到 255 
																				0x04= 超 长 整 数 （ 8 字 节 ） ， 9223372036854775807 
																				0x05=无符号整数（2 字节），范围为 0 到 65535 
																				0x06=无符号长整数（4 字节），范围为 0 到 4294967295 
------------------------------------------------------------------------------------------------------------------------ 
*/

/*
文本变量显示指令存储格式表：描述指针使用（详见7.3.2.1文本显示指令存储格式）
------------------------------------------------------------------------------------------------------------------------
地址 	|	SP描述指针偏移量 	|	定义 				 数据长度(字节) 	|	说明 
------------------------------------------------------------------------------------------------------------------------
0x06 	|	0x00				|	*VP 			|			2 			|	变量指针 
------------------------------------------------------------------------------------------------------------------------
0x08 	|	0x01				|	X   			|			2 			|	X起始显示位置，显示字符串左上角坐标。 
------------------------------------------------------------------------------------------------------------------------
0x0A 	|	0x02				|	Y   			|			2 			|	Y起始显示位置，显示字符串左上角坐标。 
------------------------------------------------------------------------------------------------------------------------
0x0C 	|	0x03				|	COLOR 			|			2 			|	显示颜色 
------------------------------------------------------------------------------------------------------------------------
剩余暂时不用
------------------------------------------------------------------------------------------------------------------------ 
*/

//=====================================================================================================================
INT16 ES_16H_WeightVlu_DP_Add[16]  ={0x9C01,0x9C11,0x9C21,0x9C31,0x9C41,0x9C51,0x9C61,0x9C71,0x9C81,0x9C91,0x9CA1,0x9CB1,0x9CC1,0x9CD1,0x9CE1,0x9CF1};
INT16 ES_16H_HelpVlu_DP_Add[18]    ={0xA001,0xA011,0xA021,0xA031,0xA041,0xA051,0xA061,0xA071,0xA081,0xA091,0xA0A1,0xA0B1,0xA0C1,0xA0D1,0xA0E1,0xA0F1,0xA101,0xA111};
INT16 ES_16H_WeightIndex_DP_Add[16]={0x9E01,0x9E11,0x9E21,0x9E31,0x9E41,0x9E51,0x9E61,0x9E71,0x9E81,0x9E91,0x9EA1,0x9EB1,0x9EC1,0x9ED1,0x9EE1,0x9EF1};
INT16 ES_16H_WeightColor_DP_Add[16]={0x9F01,0x9F11,0x9F21,0x9F31,0x9F41,0x9F51,0x9F61,0x9F71,0x9F81,0x9F91,0x9FA1,0x9FB1,0x9FC1,0x9FD1,0x9FE1,0x9FF1};
INT16 ES_16H_Misc_Add[2]  	  	   ={0xB301,0xB311};


//=====================================================================================================================
//============================================[16头]===[1.托盘重量的描述指针][2024-06-21]================================
//=====================================================================================================================
//托盘的重量显示：不带小数点显示
//                              左边框 单个宽度   单个间距	  (8+8)分块间距
#define L_WEIGHT_VLU_DIS_X(I) 	(19  + I*(150) + I/1*18     +(I/4)*18)//X position
#define L_WEIGHT_VLU_DIS_Y(I) 	((I%2 == 0)*231 + (I%2 == 1)*441)//Y position
#define L_WEIGHT_VLU_DIS_COLOR	(0x6474)//color
#define L_WEIGHT_VLU_DIS_SIZE	(0x0020)//字库(00:0号字库)+字体大小(20:32大小)
#define L_WEIGHT_VLU_DIS_DQZWS	(0x0204)//对齐(00:左对齐，01:右对齐，02:居中) + 整数位数(04:4位整数)
#define L_WEIGHT_VLU_DIS_XWSLX	(0x0001)//小数位数(00:无小数，01:1位小数)+变量类型(01:长整型4字节)
appScreenDpCfg_Type ES_16H_WeightVlue_DP_Vlu_WuXiaoShu[16]=//已调试2024-06-21
{
//  x坐标    				y坐标      				 背景颜色      			 字库+字体大小			  对齐+整数位数    			   小数位数+变量类型
	{L_WEIGHT_VLU_DIS_X(0),	L_WEIGHT_VLU_DIS_Y(0),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(0),	L_WEIGHT_VLU_DIS_Y(1),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(1),	L_WEIGHT_VLU_DIS_Y(0),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(1),	L_WEIGHT_VLU_DIS_Y(1),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(2),	L_WEIGHT_VLU_DIS_Y(0),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(2),	L_WEIGHT_VLU_DIS_Y(1),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(3),	L_WEIGHT_VLU_DIS_Y(0),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(3),	L_WEIGHT_VLU_DIS_Y(1),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(4),	L_WEIGHT_VLU_DIS_Y(0),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(4),	L_WEIGHT_VLU_DIS_Y(1),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(5),	L_WEIGHT_VLU_DIS_Y(0),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(5),	L_WEIGHT_VLU_DIS_Y(1),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(6),	L_WEIGHT_VLU_DIS_Y(0),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(6),	L_WEIGHT_VLU_DIS_Y(1),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(7),	L_WEIGHT_VLU_DIS_Y(0),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
	{L_WEIGHT_VLU_DIS_X(7),	L_WEIGHT_VLU_DIS_Y(1),	L_WEIGHT_VLU_DIS_COLOR,	L_WEIGHT_VLU_DIS_SIZE,	L_WEIGHT_VLU_DIS_DQZWS,		L_WEIGHT_VLU_DIS_XWSLX},
};
//托盘的重量显示：带小数点显示
#define L_WEIGHT_VLU_DIS_XS_X(I) 	(19  + I*(150) + I/1*18     +(I/4)*18)//X position
#define L_WEIGHT_VLU_DIS_XS_Y(I) 	((I%2 == 0)*210 + (I%2 == 1)*451)//Y position
#define L_WEIGHT_VLU_DIS_XS_COLOR	(0x6474)//颜色
#define L_WEIGHT_VLU_DIS_XS_SIZE	(0x0016)//字库+字体大小
#define L_WEIGHT_VLU_DIS_XS_DQZWS	(0x0204)//对齐+整数位数
#define L_WEIGHT_VLU_DIS_XS_XWSLX	(0x0101)//小数位数+变量类型
appScreenDpCfg_Type ES_16H_WeightVlue_DP_Vlu_YouXiaoShu[16]=//已调试[2024-06-21]
{
//  x坐标    				y坐标      				     背景颜色      			   字库+字体大小			  对齐+整数位数    			   小数位数+变量类型
	{L_WEIGHT_VLU_DIS_XS_X(0),L_WEIGHT_VLU_DIS_XS_Y(0),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(0),L_WEIGHT_VLU_DIS_XS_Y(1),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(1),L_WEIGHT_VLU_DIS_XS_Y(0),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(1),L_WEIGHT_VLU_DIS_XS_Y(1),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(2),L_WEIGHT_VLU_DIS_XS_Y(0),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(2),L_WEIGHT_VLU_DIS_XS_Y(1),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(3),L_WEIGHT_VLU_DIS_XS_Y(0),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(3),L_WEIGHT_VLU_DIS_XS_Y(1),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},

	{L_WEIGHT_VLU_DIS_XS_X(4),L_WEIGHT_VLU_DIS_XS_Y(0),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(4),L_WEIGHT_VLU_DIS_XS_Y(1),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(5),L_WEIGHT_VLU_DIS_XS_Y(0),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(5),L_WEIGHT_VLU_DIS_XS_Y(1),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(6),L_WEIGHT_VLU_DIS_XS_Y(0),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(6),L_WEIGHT_VLU_DIS_XS_Y(1),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(7),L_WEIGHT_VLU_DIS_XS_Y(0),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
	{L_WEIGHT_VLU_DIS_XS_X(7),L_WEIGHT_VLU_DIS_XS_Y(1),	L_WEIGHT_VLU_DIS_XS_COLOR,L_WEIGHT_VLU_DIS_XS_SIZE,	L_WEIGHT_VLU_DIS_XS_DQZWS,	L_WEIGHT_VLU_DIS_XS_XWSLX},
};

//=====================================================================================================================
//========================================[16头]===[2.帮助信息的描述指针][2024-06-21]====================================
//帮助信息：不带小数点显示
appScreenDpCfg_Type ES_16H_HelpVlue_DP_Vlu_WuXiaoShu[18]=//已调试[2024-06-24]
{
//  	x坐标   y坐标   背景颜色    字库+字体大小	  对齐+整数位数    小数位数+变量类型
	{	45,		573,	0x0000,		0x001A,			0x0202,			0x0000},
	{	175,	573,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	345,	573,	0xF810,		0x001A,			0x0204,			0x0000},
			
	{	45,		638,	0x0000,		0x001A,			0x0202,			0x0000},
	{	175,	638,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	345,	638,	0xF810,		0x001A,			0x0204,			0x0000},
		
	{	45,		703,	0x0000,		0x001A,			0x0202,			0x0000},
	{	175,	703,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	345,	703,	0xF810,		0x001A,			0x0204,			0x0000},
		
	{	555,	573,	0x0000,		0x001A,			0x0202,			0x0000},
	{	685,	573,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	840,	573,	0xF810,		0x001A,			0x0204,			0x0000},
		
	{	555,	638,	0x0000,		0x001A,			0x0202,			0x0000},
	{	685,	638,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	840,	638,	0xF810,		0x001A,			0x0204,			0x0000},
		
	{	555,	703,	0x0000,		0x001A,			0x0202,			0x0000},
	{	685,	703,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	840,	703,	0xF810,		0x001A,			0x0204,			0x0000},
};

//帮助信息：带小数点显示 
appScreenDpCfg_Type ES_16H_HelpVlue_DP_Vlu_YouXiaoShu[18]=//已调试[2024-06-24]
{
//  	x坐标   y坐标   背景颜色    字库+字体大小	  对齐+整数位数    小数位数+变量类型
	{	45,		573,	0x0000,		0x001A,			0x0202,			0x0000},
	{	175,	573,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	340,	580,	0xF810,		0x0014,			0x0204,			0x0100},
			
	{	45,		638,	0x0000,		0x001A,			0x0202,			0x0000},
	{	175,	638,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	340,	645,	0xF810,		0x0014,			0x0204,			0x0100},
		
	{	45,		703,	0x0000,		0x001A,			0x0202,			0x0000},
	{	175,	703,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	340,	710,	0xF810,		0x0014,			0x0204,			0x0100},
		
	{	555,	573,	0x0000,		0x001A,			0x0202,			0x0000},
	{	685,	573,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	840,	580,	0xF810,		0x0014,			0x0204,			0x0100},
		
	{	555,	638,	0x0000,		0x001A,			0x0202,			0x0000},
	{	685,	638,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	840,	645,	0xF810,		0x0014,			0x0204,			0x0100},
		
	{	555,	703,	0x0000,		0x001A,			0x0202,			0x0000},
	{	685,	703,	0x00FF,		0x001A,			0x0202,			0x0000},
	{	840,	710,	0xF810,		0x0014,			0x0204,			0x0100},
};

//=====================================================================================================================
//========================================[16头]===[3.托盘序号的描述指针][2024-06-21]====================================
//=====================================================================================================================
appScreenDpCfg_Type ES_16H_WeightIndex_DP_Vlu[16]=//已调试[2024-06-21]
{
//  x坐标   y坐标   背景颜色   	字库+字体大小	对齐+整数位数   小数位数+变量类型
	{62,	115,	0x6494,		0x0016,			0x0202,			0x0000},//1
	{62,	356,	0x6494,		0x0016,			0x0202,			0x0000},//2
	{230,	115,	0x6494,		0x0016,			0x0202,			0x0000},//3
	{230,	356,	0x6494,		0x0016,			0x0202,			0x0000},//4
	{398,	115,	0x6494,		0x0016,			0x0202,			0x0000},//5
	{398,	356,	0x6494,		0x0016,			0x0202,			0x0000},//6
	{566,	115,	0x6494,		0x0016,			0x0202,			0x0000},//7
	{566,	356,	0x6494,		0x0016,			0x0202,			0x0000},//8
	
	{753,	115,	0x6494,		0x0016,			0x0202,			0x0000},//9
	{753,	356,	0x6494,		0x0016,			0x0202,			0x0000},//10
	{921,	115,	0x6494,		0x0016,			0x0202,			0x0000},//11
	{921,	356,	0x6494,		0x0016,			0x0202,			0x0000},//12
	{1089,	115,	0x6494,		0x0016,			0x0202,			0x0000},//13
	{1089,	356,	0x6494,		0x0016,			0x0202,			0x0000},//14
	{1257,	115,	0x6494,		0x0016,			0x0202,			0x0000},//15
	{1257,	356,	0x6494,		0x0016,			0x0202,			0x0000},//16
};

//=====================================================================================================================
//========================================[16头]===[4.托盘背景色的描述指针][2024-06-21]==================================
//=====================================================================================================================
//                              	左边框 单个宽度   单个间距	  (8+8)分块间距
#define L_WEIGHT_COLOR_DIS_X(I) 	(11 + I*(150) + I/1*18 	 +(I/4)*18)//X
#define L_WEIGHT_COLOR_DIS_Y(I) 	(95 + I*(210) + (I/1)*31 + 0)//Y
appScreenDpColorCfg_Type ES_16H_WeightColor_DP_Vlu[16]=//已调试[2024-06-21]
{
//  x坐标    					y坐标      					   	
	{L_WEIGHT_COLOR_DIS_X(0),	L_WEIGHT_COLOR_DIS_Y(0)},
	{L_WEIGHT_COLOR_DIS_X(0),	L_WEIGHT_COLOR_DIS_Y(1)},
	{L_WEIGHT_COLOR_DIS_X(1),	L_WEIGHT_COLOR_DIS_Y(0)},
	{L_WEIGHT_COLOR_DIS_X(1),	L_WEIGHT_COLOR_DIS_Y(1)},
	{L_WEIGHT_COLOR_DIS_X(2),	L_WEIGHT_COLOR_DIS_Y(0)},
	{L_WEIGHT_COLOR_DIS_X(2),	L_WEIGHT_COLOR_DIS_Y(1)},
	{L_WEIGHT_COLOR_DIS_X(3),	L_WEIGHT_COLOR_DIS_Y(0)},
	{L_WEIGHT_COLOR_DIS_X(3),	L_WEIGHT_COLOR_DIS_Y(1)},
	{L_WEIGHT_COLOR_DIS_X(4),	L_WEIGHT_COLOR_DIS_Y(0)},
	{L_WEIGHT_COLOR_DIS_X(4),	L_WEIGHT_COLOR_DIS_Y(1)},
	{L_WEIGHT_COLOR_DIS_X(5),	L_WEIGHT_COLOR_DIS_Y(0)},
	{L_WEIGHT_COLOR_DIS_X(5),	L_WEIGHT_COLOR_DIS_Y(1)},
	{L_WEIGHT_COLOR_DIS_X(6),	L_WEIGHT_COLOR_DIS_Y(0)},
	{L_WEIGHT_COLOR_DIS_X(6),	L_WEIGHT_COLOR_DIS_Y(1)},
	{L_WEIGHT_COLOR_DIS_X(7),	L_WEIGHT_COLOR_DIS_Y(0)},
	{L_WEIGHT_COLOR_DIS_X(7),	L_WEIGHT_COLOR_DIS_Y(1)},
};

//=====================================================================================================================
//========================================[16头]===[5其他的描述指针][2024-06-22]========================================
//=====================================================================================================================
appScreenDpMiscCfg_Type ES_16H_Misc_DP_Vlu[2]=//已调试[2024-06-24]
{
//  x坐标   y坐标   背景颜色
	{1288,	30,		0x6494,		0X0016,			0x0202,			0x0000},//1 精度 数字变量 描述指针B300
	{62,	356,	0x6494,		0X0010,			0x0204,			0x0000},//2 精度 数字变量 描述指针B110 目前不需要调整
};

