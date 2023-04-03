#ifndef __APP_PASSWORD_H__
#define __APP_PASSWORD_H__
#include "typedefine.h"

#define STM32MCU_LOCKED		(0X10CD)
#define STM32MCU_UNLOCKED	(0X20CD)


typedef enum{
STM32F0,
STM32F1,
STM32F2,
STM32F3,
STM32F4,
STM32F7,
STM32L0,
STM32L1,
STM32L4,
STM32H7,
}MCUTypedef;
extern INT32 g_passWordId;
extern INT32 g_passWordStore;
extern INT32 g_sysLocked;
extern UINT32 STM32McuId[3];
extern void STM32MCUIDGet(UINT32 *id,MCUTypedef type);
extern UINT8 STM32CheckPassWord(INT32 passwordIn);

#endif
