#include "typedefine.h"
#include "app_syspara.h"
#include "app_password.h"

INT32 g_passWordId = 0;
INT32 g_passWordStore = 0;
INT32 g_sysLocked = STM32MCU_LOCKED;

/*获取MCU的唯一ID*/
UINT32 STM32McuId[3];


 
UINT32 idAddr[]={0x1FFFF7AC,/*STM32F0唯一ID起始地址*/
0x1FFFF7E8,/*STM32F1唯一ID起始地址*/
0x1FFF7A10,/*STM32F2唯一ID起始地址*/
0x1FFFF7AC,/*STM32F3唯一ID起始地址*/
0x1FFF7A10,/*STM32F4唯一ID起始地址*/
0x1FF0F420,/*STM32F7唯一ID起始地址*/
0x1FF80050,/*STM32L0唯一ID起始地址*/
0x1FF80050,/*STM32L1唯一ID起始地址*/
0x1FFF7590,/*STM32L4唯一ID起始地址*/
0x1FF0F420};/*STM32H7唯一ID起始地址*/
 
void STM32MCUIDGet(UINT32 *id,MCUTypedef type)
{
	if(id!=0)
	{
		id[0]=*(UINT32*)(idAddr[type]);
		id[1]=*(UINT32*)(idAddr[type]+4);
		id[2]=*(UINT32*)(idAddr[type]+8);
	}
}


UINT8 STM32CheckPassWord(INT32 passwordIn)
{
	UINT8 ret = FALSE;
	INT32 passwordBase=(STM32McuId[0]+STM32McuId[1]+STM32McuId[2])&0xffff;
	//
	g_passWordId = passwordBase;//display at screen
	//
	passwordBase = (passwordBase * 2021 ) &0xfff;
	if(passwordIn == passwordBase)
	{
		g_passWordStore = passwordIn;
		g_sysLocked = STM32MCU_UNLOCKED;
		ret = TRUE;
	}
	return ret;
}
