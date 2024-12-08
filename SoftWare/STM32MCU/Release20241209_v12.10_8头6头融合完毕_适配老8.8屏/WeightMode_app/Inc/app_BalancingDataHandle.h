#ifndef _APP_BALANCINGDATA_HANDLE_H_
#define _APP_BALANCINGDATA_HANDLE_H_

#include "app_sdwe_ctrl.h"
#include "hal_uart.h"
#include "app_hx711_ctrl.h"
#include "app_InnerScreen_Cfg.h"
#include "app_ExternalScreen_Cfg.h"

extern void BalancingData_WeightData_Handle_PrepareAndJudgeAndSendToScreen(T5LType *pSdwe);
extern void BalancingData_ColorData_Handle_PrepareAndJudgeAndSendToScreen(T5LType *pSdwe);
extern UINT16 BalancingData_HelpData_Handle_PrepareAndJudgeAndSendToScreen(T5LType *pSdwe);

#endif
