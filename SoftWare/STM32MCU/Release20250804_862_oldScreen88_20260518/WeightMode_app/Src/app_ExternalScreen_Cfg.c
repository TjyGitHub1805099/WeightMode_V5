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
INT16 ES_8H_WeightVlu_DP_Add[16]  ={0x9401,0x9411,0x9421,0x9431,0x9441,0x9451,0x9461,0x9471,0x9481,0x9491,0x94A1,0x94B1,0x94C1,0x94D1,0x94E1,0x94F1};
INT16 ES_8H_HelpVlu_DP_Add[16]    ={0x9501,0x9511,0x9521,0x9531,0x9541,0x9551,0x9561,0x9571,0x9581,0x9591,0x95A1,0x95B1,0x95C1,0x95D1,0x95E1,0x95F1};
INT16 ES_8H_WeightIndex_DP_Add[16]={0x9601,0x9611,0x9621,0x9631,0x9641,0x9651,0x9661,0x9671,0x9681,0x9691,0x96A1,0x96B1,0x96C1,0x96D1,0x96E1,0x96F1};
INT16 ES_8H_WeightColor_DP_Add[16]={0x9701,0x9711,0x9721,0x9731,0x9741,0x9751,0x9761,0x9771,0x9781,0x9791,0x97A1,0x97B1,0x97C1,0x97D1,0x97E1,0x97F1};
INT16 ES_8H_Misc_Add[2]  	 	  ={0xB101,0xB111};

//=====================================================================================================================
//=============================================[8头]===[1.托盘重量的描述指针]============================================
//=====================================================================================================================
//托盘的重量显示：不带小数点显示
//                              左边框 单个宽度   单个间距	  (8+8)分块间距
#define L8_WEIGHT_VLU_DIS_Y(I) 	(183 + I*(180) + (I/1)*12   + 0)//Y position
#define L8_WEIGHT_VLU_DIS_COLOR	(0x6474)//蓝色(0x041F)//color
#define L8_WEIGHT_VLU_DIS_SIZE	(0x0040)//字库(00:0号字库)+字体大小(20:32大小)
#define L8_WEIGHT_VLU_DIS_DQZWS	(0x0204)//对齐(00:左对齐，01:右对齐，02:居中) + 整数位数(04:4位整数)
#define L8_WEIGHT_VLU_DIS_XWSLX	(0x0001)//小数位数(00:无小数，01:1位小数)+变量类型(01:长整型4字节)
appScreenDpCfg_Type ES_8H_WeightVlue_DP_Vlu_WuXiaoShu[8]=//已调试[2024-06-24]
{
//  x    					y      					颜色      				字库+字体大小			 对齐+整数位数    			   小数位数 变量类型
	{48,	L8_WEIGHT_VLU_DIS_Y(0),	L8_WEIGHT_VLU_DIS_COLOR,	L8_WEIGHT_VLU_DIS_SIZE,	L8_WEIGHT_VLU_DIS_DQZWS,		L8_WEIGHT_VLU_DIS_XWSLX},
	{48,	L8_WEIGHT_VLU_DIS_Y(1),	L8_WEIGHT_VLU_DIS_COLOR,	L8_WEIGHT_VLU_DIS_SIZE,	L8_WEIGHT_VLU_DIS_DQZWS,		L8_WEIGHT_VLU_DIS_XWSLX},
	{385,	L8_WEIGHT_VLU_DIS_Y(0),	L8_WEIGHT_VLU_DIS_COLOR,	L8_WEIGHT_VLU_DIS_SIZE,	L8_WEIGHT_VLU_DIS_DQZWS,		L8_WEIGHT_VLU_DIS_XWSLX},
	{385,	L8_WEIGHT_VLU_DIS_Y(1),	L8_WEIGHT_VLU_DIS_COLOR,	L8_WEIGHT_VLU_DIS_SIZE,	L8_WEIGHT_VLU_DIS_DQZWS,		L8_WEIGHT_VLU_DIS_XWSLX},
	{722,	L8_WEIGHT_VLU_DIS_Y(0),	L8_WEIGHT_VLU_DIS_COLOR,	L8_WEIGHT_VLU_DIS_SIZE,	L8_WEIGHT_VLU_DIS_DQZWS,		L8_WEIGHT_VLU_DIS_XWSLX},
	{722,	L8_WEIGHT_VLU_DIS_Y(1),	L8_WEIGHT_VLU_DIS_COLOR,	L8_WEIGHT_VLU_DIS_SIZE,	L8_WEIGHT_VLU_DIS_DQZWS,		L8_WEIGHT_VLU_DIS_XWSLX},
	{1058,	L8_WEIGHT_VLU_DIS_Y(0),	L8_WEIGHT_VLU_DIS_COLOR,	L8_WEIGHT_VLU_DIS_SIZE,	L8_WEIGHT_VLU_DIS_DQZWS,		L8_WEIGHT_VLU_DIS_XWSLX},
	{1058,	L8_WEIGHT_VLU_DIS_Y(1),	L8_WEIGHT_VLU_DIS_COLOR,	L8_WEIGHT_VLU_DIS_SIZE,	L8_WEIGHT_VLU_DIS_DQZWS,		L8_WEIGHT_VLU_DIS_XWSLX},
};

//托盘的重量显示：带小数点显示
//                              	左边框 单个宽度   单个间距	  (8+8)分块间距
#define L8_WEIGHT_VLU_DIS_XS_X(I) 	(46  + I*(325) + I/1*12     +(I/4)*0)//X position
#define L8_WEIGHT_VLU_DIS_XS_Y(I) 	(197 + I*(180) + (I/1)*12   + 0)//Y position
#define L8_WEIGHT_VLU_DIS_XS_COLOR	(0x6474)//颜色
#define L8_WEIGHT_VLU_DIS_XS_SIZE	(0x0028)//字库+字体大小
#define L8_WEIGHT_VLU_DIS_XS_DQZWS	(0x0204)//对齐+整数位数
#define L8_WEIGHT_VLU_DIS_XS_XWSLX	(0x0101)//小数位数+变量类型
appScreenDpCfg_Type ES_8H_WeightVlue_DP_Vlu_YouXiaoShu[8]=//已调试[2024-06-21]
{
//  x    					y      						颜色      				  字库+字体大小				 对齐+整数位数    			  小数位数 变量类型
	{L8_WEIGHT_VLU_DIS_XS_X(0),L8_WEIGHT_VLU_DIS_XS_Y(0),	L8_WEIGHT_VLU_DIS_XS_COLOR,L8_WEIGHT_VLU_DIS_XS_SIZE,	L8_WEIGHT_VLU_DIS_XS_DQZWS,	L8_WEIGHT_VLU_DIS_XS_XWSLX},
	{L8_WEIGHT_VLU_DIS_XS_X(0),L8_WEIGHT_VLU_DIS_XS_Y(1),	L8_WEIGHT_VLU_DIS_XS_COLOR,L8_WEIGHT_VLU_DIS_XS_SIZE,	L8_WEIGHT_VLU_DIS_XS_DQZWS,	L8_WEIGHT_VLU_DIS_XS_XWSLX},
	{L8_WEIGHT_VLU_DIS_XS_X(1),L8_WEIGHT_VLU_DIS_XS_Y(0),	L8_WEIGHT_VLU_DIS_XS_COLOR,L8_WEIGHT_VLU_DIS_XS_SIZE,	L8_WEIGHT_VLU_DIS_XS_DQZWS,	L8_WEIGHT_VLU_DIS_XS_XWSLX},
	{L8_WEIGHT_VLU_DIS_XS_X(1),L8_WEIGHT_VLU_DIS_XS_Y(1),	L8_WEIGHT_VLU_DIS_XS_COLOR,L8_WEIGHT_VLU_DIS_XS_SIZE,	L8_WEIGHT_VLU_DIS_XS_DQZWS,	L8_WEIGHT_VLU_DIS_XS_XWSLX},
	{L8_WEIGHT_VLU_DIS_XS_X(2),L8_WEIGHT_VLU_DIS_XS_Y(0),	L8_WEIGHT_VLU_DIS_XS_COLOR,L8_WEIGHT_VLU_DIS_XS_SIZE,	L8_WEIGHT_VLU_DIS_XS_DQZWS,	L8_WEIGHT_VLU_DIS_XS_XWSLX},
	{L8_WEIGHT_VLU_DIS_XS_X(2),L8_WEIGHT_VLU_DIS_XS_Y(1),	L8_WEIGHT_VLU_DIS_XS_COLOR,L8_WEIGHT_VLU_DIS_XS_SIZE,	L8_WEIGHT_VLU_DIS_XS_DQZWS,	L8_WEIGHT_VLU_DIS_XS_XWSLX},
	{L8_WEIGHT_VLU_DIS_XS_X(3),L8_WEIGHT_VLU_DIS_XS_Y(0),	L8_WEIGHT_VLU_DIS_XS_COLOR,L8_WEIGHT_VLU_DIS_XS_SIZE,	L8_WEIGHT_VLU_DIS_XS_DQZWS,	L8_WEIGHT_VLU_DIS_XS_XWSLX},
	{L8_WEIGHT_VLU_DIS_XS_X(3),L8_WEIGHT_VLU_DIS_XS_Y(1),	L8_WEIGHT_VLU_DIS_XS_COLOR,L8_WEIGHT_VLU_DIS_XS_SIZE,	L8_WEIGHT_VLU_DIS_XS_DQZWS,	L8_WEIGHT_VLU_DIS_XS_XWSLX},
};

//=====================================================================================================================
//=========================================[8头]===[2.帮助信息的描述指针]================================================
//=====================================================================================================================
//帮助信息：不带小数点显示
//                              左边框 	单个宽度   	   单个间距	  	  (8+8)分块间距
#define L8_HELP_VLU_DIS_X(I) 	(0  + (I%3)*(100) 	+ (I%3)/2*60    +(I/3)*443)//X
#define L8_HELP_VLU_DIS_Y(I) 	(552 + I*(85) + (I/1)*(15)   	+ 0)//Y
#define L8_HELP_VLU_DIS_COLOR	(0xF810)//差值颜色
#define L8_HELP_VLU_DIS_COLOR_S	(0x0000)//被减数序号颜色
#define L8_HELP_VLU_DIS_COLOR_S2 (0x041F)//减数序号颜色
#define L8_HELP_VLU_DIS_SIZE	(0x0022)//字库+字体大小
#define L8_HELP_VLU_DIS_DQZWS	(0x0204)//对齐+整数位数
#define L8_HELP_VLU_DIS_XWSLX	(0x0000)//小数位数+变量类型
appScreenDpCfg_Type ES_8H_HelpVlue_DP_Vlu_WuXiaoShu[12]=//已调试[2024-06-21]
{
//  x    					y      					颜色      				字库+字体大小			  对齐+整数位数    		  小数位数 变量类型
	{15,	L8_HELP_VLU_DIS_Y(0),	L8_HELP_VLU_DIS_COLOR_S,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{150,	L8_HELP_VLU_DIS_Y(0),	L8_HELP_VLU_DIS_COLOR_S2,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{340,	L8_HELP_VLU_DIS_Y(0),	L8_HELP_VLU_DIS_COLOR,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{15,	L8_HELP_VLU_DIS_Y(1),	L8_HELP_VLU_DIS_COLOR_S,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{150,	L8_HELP_VLU_DIS_Y(1),	L8_HELP_VLU_DIS_COLOR_S2,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{340,	L8_HELP_VLU_DIS_Y(1),	L8_HELP_VLU_DIS_COLOR,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{525,	L8_HELP_VLU_DIS_Y(0),	L8_HELP_VLU_DIS_COLOR_S,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{650,	L8_HELP_VLU_DIS_Y(0),	L8_HELP_VLU_DIS_COLOR_S2,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{840,	L8_HELP_VLU_DIS_Y(0),	L8_HELP_VLU_DIS_COLOR,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{525,	L8_HELP_VLU_DIS_Y(1),	L8_HELP_VLU_DIS_COLOR_S,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{650,	L8_HELP_VLU_DIS_Y(1),	L8_HELP_VLU_DIS_COLOR_S2,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
	{840,	L8_HELP_VLU_DIS_Y(1),	L8_HELP_VLU_DIS_COLOR,	L8_HELP_VLU_DIS_SIZE,	L8_HELP_VLU_DIS_DQZWS,	L8_HELP_VLU_DIS_XWSLX},
};

//帮助信息：带小数点显示
//                              	左边框 	单个宽度   	   单个间距	  	  (8+8)分块间距
#define L8_HELP_VLU_DIS_XS_X(I) 	(5  +  (I%6==1)*110 + (I%6==2)*250 + (I%6==3)*450 + (I%6==4)*560 + (I%6==5)*700)
#define L8_HELP_VLU_DIS_XS_Y(I) 	(552 + I*(85) + (I/1)*(15)   	+ 0)//Y
#define L8_HELP_VLU_DIS_XS_COLOR	(0xF810)//差值颜色
#define L8_HELP_VLU_DIS_XS_COLOR_S	(0x0000)//被减数序号颜色
#define L8_HELP_VLU_DIS_XS_COLOR_S2 (0x041F)//减数序号颜色
#define L8_HELP_VLU_DIS_XS_SIZE		(0x001C)//字库+字体大小
#define L8_HELP_VLU_DIS_XS_SIZE_S	(0x001C)//字库+字体大小
#define L8_HELP_VLU_DIS_XS_DQZWS	(0x0204)//对齐+整数位数
#define L8_HELP_VLU_DIS_XS_XWSLX1	(0x0000)//小数位数+变量类型
#define L8_HELP_VLU_DIS_XS_XWSLX	(0x0100)//小数位数+变量类型
appScreenDpCfg_Type ES_8H_HelpVlue_DP_Vlu_YouXiaoShu[12]=//已调试[2024-06-21]
{
//  x    					y      					颜色      				字库+字体大小			  对齐+整数位数    		  小数位数 变量类型
	{20,	L8_HELP_VLU_DIS_XS_Y(0),	L8_HELP_VLU_DIS_XS_COLOR_S,	L8_HELP_VLU_DIS_XS_SIZE,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX1},
	{155,	L8_HELP_VLU_DIS_XS_Y(0),	L8_HELP_VLU_DIS_XS_COLOR_S2,	L8_HELP_VLU_DIS_XS_SIZE,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX1},
	{330,	L8_HELP_VLU_DIS_XS_Y(0),	L8_HELP_VLU_DIS_XS_COLOR,	L8_HELP_VLU_DIS_XS_SIZE_S,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX},
	{20,	L8_HELP_VLU_DIS_XS_Y(1),	L8_HELP_VLU_DIS_XS_COLOR_S,	L8_HELP_VLU_DIS_XS_SIZE,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX1},
	{155,	L8_HELP_VLU_DIS_XS_Y(1),	L8_HELP_VLU_DIS_XS_COLOR_S2,	L8_HELP_VLU_DIS_XS_SIZE,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX1},
	{330,	L8_HELP_VLU_DIS_XS_Y(1),	L8_HELP_VLU_DIS_XS_COLOR,	L8_HELP_VLU_DIS_XS_SIZE_S,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX},
	{530,	L8_HELP_VLU_DIS_XS_Y(0),	L8_HELP_VLU_DIS_XS_COLOR_S,	L8_HELP_VLU_DIS_XS_SIZE,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX1},
	{660,	L8_HELP_VLU_DIS_XS_Y(0),	L8_HELP_VLU_DIS_XS_COLOR_S2,	L8_HELP_VLU_DIS_XS_SIZE,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX1},
	{830,	L8_HELP_VLU_DIS_XS_Y(0),	L8_HELP_VLU_DIS_XS_COLOR,	L8_HELP_VLU_DIS_XS_SIZE_S,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX},
	{530,	L8_HELP_VLU_DIS_XS_Y(1),	L8_HELP_VLU_DIS_XS_COLOR_S,	L8_HELP_VLU_DIS_XS_SIZE,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX1},
	{660,	L8_HELP_VLU_DIS_XS_Y(1),	L8_HELP_VLU_DIS_XS_COLOR_S2,	L8_HELP_VLU_DIS_XS_SIZE,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX1},
	{830,	L8_HELP_VLU_DIS_XS_Y(1),	L8_HELP_VLU_DIS_XS_COLOR,	L8_HELP_VLU_DIS_XS_SIZE_S,	L8_HELP_VLU_DIS_XS_DQZWS,	L8_HELP_VLU_DIS_XS_XWSLX},
};

//=====================================================================================================================
//=========================================[8头]===[3.托盘序号的描述指针]================================================
//=====================================================================================================================
//                              		左边框 单个宽度   单个间距	  (8+8)分块间距
#define L8_WEIGHT_VLU_INDEX_DIS_X(I) 	(160  + I*(325) + I/1*12     +(I/4)*0)//X
#define L8_WEIGHT_VLU_INDEX_DIS_Y(I) 	(139 + I*(180) + (I/1)*12   + 0)//Y
#define L8_WEIGHT_VLU_INDEX_DIS_COLOR	(0x0000)//颜色0x6494
#define L8_WEIGHT_VLU_INDEX_DIS_SIZE	(0x0012)//字库+字体大小
#define L8_WEIGHT_VLU_INDEX_DIS_DQZWS	(0x0202)//对齐+整数位数
#define L8_WEIGHT_VLU_INDEX_DIS_XWSLX	(0x0000)//小数位数+变量类型
appScreenDpCfg_Type ES_8H_WeightIndex_DP_Vlu[8]=//已调试[2024-06-21]
{
//  x    							y      							颜色      						字库+字体大小					 对齐+整数位数    				  小数位数 变量类型(00:整数2字节，01:长整数4字节)
	{L8_WEIGHT_VLU_INDEX_DIS_X(0),	L8_WEIGHT_VLU_INDEX_DIS_Y(0),	L8_WEIGHT_VLU_INDEX_DIS_COLOR,	L8_WEIGHT_VLU_INDEX_DIS_SIZE,	L8_WEIGHT_VLU_INDEX_DIS_DQZWS,	L8_WEIGHT_VLU_INDEX_DIS_XWSLX},
	{L8_WEIGHT_VLU_INDEX_DIS_X(0),	L8_WEIGHT_VLU_INDEX_DIS_Y(1),	L8_WEIGHT_VLU_INDEX_DIS_COLOR,	L8_WEIGHT_VLU_INDEX_DIS_SIZE,	L8_WEIGHT_VLU_INDEX_DIS_DQZWS,	L8_WEIGHT_VLU_INDEX_DIS_XWSLX},
	{L8_WEIGHT_VLU_INDEX_DIS_X(1),	L8_WEIGHT_VLU_INDEX_DIS_Y(0),	L8_WEIGHT_VLU_INDEX_DIS_COLOR,	L8_WEIGHT_VLU_INDEX_DIS_SIZE,	L8_WEIGHT_VLU_INDEX_DIS_DQZWS,	L8_WEIGHT_VLU_INDEX_DIS_XWSLX},
	{L8_WEIGHT_VLU_INDEX_DIS_X(1),	L8_WEIGHT_VLU_INDEX_DIS_Y(1),	L8_WEIGHT_VLU_INDEX_DIS_COLOR,	L8_WEIGHT_VLU_INDEX_DIS_SIZE,	L8_WEIGHT_VLU_INDEX_DIS_DQZWS,	L8_WEIGHT_VLU_INDEX_DIS_XWSLX},
	{L8_WEIGHT_VLU_INDEX_DIS_X(2),	L8_WEIGHT_VLU_INDEX_DIS_Y(0),	L8_WEIGHT_VLU_INDEX_DIS_COLOR,	L8_WEIGHT_VLU_INDEX_DIS_SIZE,	L8_WEIGHT_VLU_INDEX_DIS_DQZWS,	L8_WEIGHT_VLU_INDEX_DIS_XWSLX},
	{L8_WEIGHT_VLU_INDEX_DIS_X(2),	L8_WEIGHT_VLU_INDEX_DIS_Y(1),	L8_WEIGHT_VLU_INDEX_DIS_COLOR,	L8_WEIGHT_VLU_INDEX_DIS_SIZE,	L8_WEIGHT_VLU_INDEX_DIS_DQZWS,	L8_WEIGHT_VLU_INDEX_DIS_XWSLX},
	{L8_WEIGHT_VLU_INDEX_DIS_X(3),	L8_WEIGHT_VLU_INDEX_DIS_Y(0),	L8_WEIGHT_VLU_INDEX_DIS_COLOR,	L8_WEIGHT_VLU_INDEX_DIS_SIZE,	L8_WEIGHT_VLU_INDEX_DIS_DQZWS,	L8_WEIGHT_VLU_INDEX_DIS_XWSLX},
	{L8_WEIGHT_VLU_INDEX_DIS_X(3),	L8_WEIGHT_VLU_INDEX_DIS_Y(1),	L8_WEIGHT_VLU_INDEX_DIS_COLOR,	L8_WEIGHT_VLU_INDEX_DIS_SIZE,	L8_WEIGHT_VLU_INDEX_DIS_DQZWS,	L8_WEIGHT_VLU_INDEX_DIS_XWSLX},
};

//=====================================================================================================================
//=========================================[8头]===[4.托盘背景色的描述指针]==============================================
//=====================================================================================================================
//                              	左边框 单个宽度   单个间距	  (8+8)分块间距
#define L8_WEIGHT_COLOR_DIS_X(I) 	(16 + I*(325) + I/1*12 	 +(I/4)*0)//X
#define L8_WEIGHT_COLOR_DIS_Y(I) 	(126 + I*(180) + (I/1)*12 + 0)//Y
appScreenDpColorCfg_Type ES_8H_WeightColor_DP_Vlu[8]=//已调试[2024-06-21]
{
//  x    						y      					   	
	{L8_WEIGHT_COLOR_DIS_X(0),	L8_WEIGHT_COLOR_DIS_Y(0)},
	{L8_WEIGHT_COLOR_DIS_X(0),	L8_WEIGHT_COLOR_DIS_Y(1)},
	{L8_WEIGHT_COLOR_DIS_X(1),	L8_WEIGHT_COLOR_DIS_Y(0)},
	{L8_WEIGHT_COLOR_DIS_X(1),	L8_WEIGHT_COLOR_DIS_Y(1)},
	{L8_WEIGHT_COLOR_DIS_X(2),	L8_WEIGHT_COLOR_DIS_Y(0)},
	{L8_WEIGHT_COLOR_DIS_X(2),	L8_WEIGHT_COLOR_DIS_Y(1)},
	{L8_WEIGHT_COLOR_DIS_X(3),	L8_WEIGHT_COLOR_DIS_Y(0)},
	{L8_WEIGHT_COLOR_DIS_X(3),	L8_WEIGHT_COLOR_DIS_Y(1)},
};

//=====================================================================================================================
//========================================[8头]===[5其他的描述指针][2024-06-22]========================================
//=====================================================================================================================

appScreenDpMiscCfg_Type ES_8H_Misc_DP_Vlu[2]=//已调试[2026-05-14]
{
//  x坐标   y坐标   背景颜色      字库/字体大小	  对齐 位数    小数位数 变量类型
	{1288,	45,		0x6494,		0X0014,			0x0202,			0x0000},//1 精度 数字变量 描述指针B100
	{62,	356,	0x6494,		0X0010,			0x0204,			0x0000},//2 精度 数字变量 描述指针B110 目前不需要调整
};

//
appScreenCfg_Type externalScreenCfg[APPSCREEN_WEIGHT_NUM_MAX]={
	//APPSCREEN_WEIGHT_NUM_2   未调试 
	{
		2,
		ES_2H_WeightVlu_DP_Add,
		ES_2H_WeightVlue_DP_Vlu_WuXiaoShu,
		ES_2H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		3,
		ES_2H_HelpVlu_DP_Add,
		ES_2H_HelpVlue_DP_Vlu_WuXiaoShu,
		ES_2H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		2,
		ES_2H_WeightIndex_DP_Add,
		ES_2H_WeightIndex_DP_Vlu,
		\
		2,
		ES_2H_WeightColor_DP_Add,
		ES_2H_WeightColor_DP_Vlu,
		\
		1,\
		ES_2H_Misc_Add,\
		ES_2H_Misc_DP_Vlu,\
	},

	//APPSCREEN_WEIGHT_NUM_6   未调试
	{
		6,
		ES_6H_WeightVlu_DP_Add,
		ES_6H_WeightVlue_DP_Vlu_WuXiaoShu,
		ES_6H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		9,
		ES_6H_HelpVlu_DP_Add,
		ES_6H_HelpVlue_DP_Vlu_WuXiaoShu,
		ES_6H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		6,
		ES_6H_WeightIndex_DP_Add,
		ES_6H_WeightIndex_DP_Vlu,
		\
		6,
		ES_6H_WeightColor_DP_Add,
		ES_6H_WeightColor_DP_Vlu,
		\
		1,\
		ES_6H_Misc_Add,\
		ES_6H_Misc_DP_Vlu,\
	},

	//APPSCREEN_WEIGHT_NUM_8 //已调试[2024-06-21]
	{
		8,
		ES_8H_WeightVlu_DP_Add,
		ES_8H_WeightVlue_DP_Vlu_WuXiaoShu,
		ES_8H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		12,
		ES_8H_HelpVlu_DP_Add,
		ES_8H_HelpVlue_DP_Vlu_WuXiaoShu,
		ES_8H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		8,
		ES_8H_WeightIndex_DP_Add,
		ES_8H_WeightIndex_DP_Vlu,
		\
		8,
		ES_8H_WeightColor_DP_Add,
		ES_8H_WeightColor_DP_Vlu,
		1,\
		ES_8H_Misc_Add,\
		ES_8H_Misc_DP_Vlu,\
	},

	//APPSCREEN_WEIGHT_NUM_12   未调试
	{
		12,
		ES_12H_WeightVlu_DP_Add,
		ES_12H_WeightVlue_DP_Vlu_WuXiaoShu,
		ES_12H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		16,
		ES_12H_HelpVlu_DP_Add,
		ES_12H_HelpVlue_DP_Vlu_WuXiaoShu,
		ES_12H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		12,
		ES_12H_WeightIndex_DP_Add,
		ES_12H_WeightIndex_DP_Vlu,
		\
		12,
		ES_12H_WeightColor_DP_Add,
		ES_12H_WeightColor_DP_Vlu,
		1,\
		ES_12H_Misc_Add,\
		ES_12H_Misc_DP_Vlu,\
	},

	//APPSCREEN_WEIGHT_NUM_16   //已调试[2024-06-21]
	{
		16,
		ES_16H_WeightVlu_DP_Add,
		ES_16H_WeightVlue_DP_Vlu_WuXiaoShu,
		ES_16H_WeightVlue_DP_Vlu_YouXiaoShu,
		\
		18,
		ES_16H_HelpVlu_DP_Add,
		ES_16H_HelpVlue_DP_Vlu_WuXiaoShu,
		ES_16H_HelpVlue_DP_Vlu_YouXiaoShu,
		\
		16,
		ES_16H_WeightIndex_DP_Add,
		ES_16H_WeightIndex_DP_Vlu,
		\
		16,
		ES_16H_WeightColor_DP_Add,
		ES_16H_WeightColor_DP_Vlu,
		1,\
		ES_16H_Misc_Add,\
		ES_16H_Misc_DP_Vlu,\
	},
};
