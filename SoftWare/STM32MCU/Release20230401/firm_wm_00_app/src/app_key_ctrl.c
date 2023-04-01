/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app_main_task.h"
#include "app_key_ctrl.h"
#include "app_hx711_ctrl.h"
#include "app_sdwe_ctrl.h"
#include "app_t5l_ctrl.h"
#include "app_modbus_rtu_ctrl.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
SysKeyType SysKey[SYS_KEY_NUM];

/*******************************************************************************
 * Functions
 ******************************************************************************/
//==key init
void key_init(void)
{
	UINT8 i = 0 ;
	SysKeyType *pSysKeyType = &SysKey[0];
	for(i=0;i<SYS_KEY_NUM;i++)
	{
		pSysKeyType[i].type = (enumDiLineType)(SYS_KEY_1+i);
		pSysKeyType[i].count = 0;
		pSysKeyType[i].preSample = SYS_KEY_INVALUED ;
		pSysKeyType[i].curSample = SYS_KEY_INVALUED ;
		pSysKeyType[i].keyOutput = SYS_KEY_INVALUED;
		pSysKeyType[i].initFlag = TRUE;
	}
}
//==key filter
void key_filter()
{
	UINT8 i = 0;
	SysKeyType *pSysKeyType = &SysKey[0];
	//
	for(i=0;i<SYS_KEY_NUM;i++)
	{
		pSysKeyType[i].curSample = hal_di_get(pSysKeyType[i].type);
		if( pSysKeyType[i].preSample == pSysKeyType[i].curSample)
		{
			pSysKeyType[i].count++;
			//output
			if( pSysKeyType[i].count >= SYS_KEY_FILTER_NUM )
			{
				pSysKeyType[i].count = SYS_KEY_FILTER_NUM;
				pSysKeyType[i].keyOutput = pSysKeyType[i].curSample;
			}
		}
		else
		{
			pSysKeyType[i].count = 0 ;
		}
		pSysKeyType[i].preSample = pSysKeyType[i].curSample ;
	}
}
//==key filter out get
UINT8 key_FilterGet(enumDiLineType type)
{
	UINT8 value = SYS_KEY_INVALUED;
	if( (type >= SYS_KEY_1) && (type < (SYS_KEY_1+SYS_KEY_NUM) ) )
	{
		value =  SysKey[type-SYS_KEY_1].keyOutput;
	}
	return value;
}
//==key main function
void key_MainFunction(void)
{
	static UINT8 preRemoveKey=SYS_KEY_INVALUED;
	static UINT8 preHomeAndCalibrateKey=SYS_KEY_INVALUED;
	static UINT8 preHomeAndCalibrateStatus = 0 ;
	key_filter();

	//去皮
	if(preRemoveKey == SYS_KEY_INVALUED)
	{
		if(SYS_KEY_VALUED == key_FilterGet(SYS_KEY_2))
		{
			preRemoveKey = SYS_KEY_VALUED;
			//
			g_T5L.sdweRemoveWeightTriger = TRUE;
			//
			setModbusSelfRemoveFlag(TRUE);
		}
	}
	else
	{
		if(SYS_KEY_INVALUED == key_FilterGet(SYS_KEY_2))
		{
			preRemoveKey = SYS_KEY_INVALUED;
		}
	}

	//主页 和 配平模式来回切
	if(SYS_KEY_INVALUED == preHomeAndCalibrateKey)
	{
		if(SYS_KEY_VALUED == key_FilterGet(SYS_KEY_1))
		{
			preHomeAndCalibrateKey = SYS_KEY_VALUED;
			//
			switch((preHomeAndCalibrateStatus++)%2)
			{
				case 0://切主页
						g_T5L.sdweJumpToHomePage = TRUE;
				break;
				case 1://切配平
						g_T5L.sdweJumpToBanlingPage = TRUE;
				break;
				default:
				break;
			}
		}
	}
	else
	{
		if(SYS_KEY_INVALUED == key_FilterGet(SYS_KEY_1))
		{
			preHomeAndCalibrateKey = SYS_KEY_INVALUED;
		}
	}
}
