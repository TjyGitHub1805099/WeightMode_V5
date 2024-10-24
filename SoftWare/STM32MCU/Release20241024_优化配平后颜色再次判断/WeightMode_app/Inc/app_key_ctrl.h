#ifndef __APP_KEY_CTRL_H__
#define __APP_KEY_CTRL_H__

#include "typedefine.h"
#include "hal_gpio.h"

#define SYS_KEY_NUM			(SYS_KEY_2-SYS_KEY_1+1)	
#define SYS_KEY_FILTER_NUM	(50)//50ms

#define SYS_KEY_VALUED		(1)
#define SYS_KEY_INVALUED	(0)

typedef struct
{
	enumDiLineType type;
	UINT8 	initFlag;
	UINT8	count;
	UINT8	preSample;
	UINT8	curSample;
	UINT8	keyOutput;
} SysKeyType;

void key_init(void);
void key_MainFunction(void);
UINT8 key_FilterGet(enumDiLineType type);

#endif
