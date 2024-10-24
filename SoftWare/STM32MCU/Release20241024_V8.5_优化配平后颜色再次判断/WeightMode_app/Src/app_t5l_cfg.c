/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "typedefine.h"
#include "app_t5l_ctrl.h"
#include "app_syspara.h"
#include "app_t5l_cfg.h"
#include "app_modbus_rtu_ctrl.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

//=====================================================================================================================
//屏幕的描述指针地址范围：(外部大屏才有相关描述指针)
//0x9010~0x9100：重量显示控件
//0x9110~0x9160：帮助信息的差值显示控件
//0x9210~0x9300：托盘序号显示控件
//0x9310~0x9400：托盘背景色显示控件
//=====================================================================================================================



//通过设置单台数量 及是否级联 来决定描述指针
UINT8 appScreenCfgIndexGet(T5LType *pSdwe,UINT8 weight_help_index_color_orther)
{
	appScreenCfg_Enum index = APPSCREEN_WEIGHT_NUM_6;
	switch(gSystemPara.weightNum)
	{
		case 6:
			index = APPSCREEN_WEIGHT_NUM_6;
			if(0 != gSystemPara.isCascade)
			{
				index = APPSCREEN_WEIGHT_NUM_12;
			}
		break;
		case 8:
			index = APPSCREEN_WEIGHT_NUM_8;
			if(0 != gSystemPara.isCascade)
			{
				index = APPSCREEN_WEIGHT_NUM_16;
				//
				#if 0
				if((ModbusAdd_Master == gSystemPara.isCascade) 
					&& ( &g_T5LCtx[ScreenIndex_Smaller] == pSdwe)
					&& (0 == weight_help_index_color_orther))
				{
					index = APPSCREEN_WEIGHT_NUM_8;
				}
				if((ModbusAdd_Master == gSystemPara.isCascade) 
					&& ( &g_T5LCtx[ScreenIndex_Smaller] == pSdwe)
					&& (1 == weight_help_index_color_orther))
				{
					index = APPSCREEN_WEIGHT_NUM_16;
				}
				#else
					if((ModbusAdd_Master == gSystemPara.isCascade) 
					&& ( &g_T5LCtx[ScreenIndex_Smaller] == pSdwe))
					{
						index = APPSCREEN_WEIGHT_NUM_8;//复用8头的
					}
				#endif
				#if 0
				//从机：都用APPSCREEN_WEIGHT_NUM_16 调试OK
				if((ModbusAdd_Slave_1 == gSystemPara.isCascade) 
					&& ( &g_T5LCtx[ScreenIndex_Smaller] == pSdwe)
					&& (2 == weight_help_index_color_orther))
				{
					//从机 托盘序号
					index = APPSCREEN_WEIGHT_NUM_16;
				}
				#endif
			}	
		break;
		default :
			index = APPSCREEN_WEIGHT_NUM_6;
		break;
	}
	return index;
}
