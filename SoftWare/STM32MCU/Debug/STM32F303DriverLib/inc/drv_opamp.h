/**
*******************************************************************
* @file    drv_opamp.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F303 OPAMP模块驱动程序H文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_OPAMP_H__
#define __DRV_OPAMP_H__


#include "reg_stm32f303_opamp.h"

/** 放大器反向输入选择定义 */
typedef enum InvInputType
{
	OPAMP_InvInput_IO1 = 0,		/**< IO1,PC5到OPAMP1和2，PB10到OPAMP3和4 */
	OPAMP_InvInput_IO2,			/**< IO2,PA3到OPAMP1,PA5到OPAMP2,PB2到OPAMP3,PD8到OPAMP4 */
	OPAMP_InvInput_PGA,			/**< PGA模式 */
	OPAMP_InvInput_Vout			/**< 跟随模式 */
}enumInvInputType;

/** 放大器同向输入选择定义 */
typedef enum PosInputType
{
	OPAMP_PosInput_IO1 = 0,		/**< IO1,PA7到OPAMP1,PD14到OPAMP2,PB13到APAMP3,PD11到OPAMP4 */
	OPAMP_PosInput_IO2,			/**< IO2,PA5到OPAMP1,PB14到OPAMP2,PA5到OPAMP3,PB11到OPAMP4 */
	OPAMP_PosInput_IO3,			/**< IO3,PA3到OPAMP1,PB0到OPAMP2,PA1到OPAMP3,PA4到OPAMP4 */
	OPAMP_PosInput_IO4			/**< IO4,PA1到OPAMP1,PA7到OPAMP2,PB0到OPAMP3,PB13到OPAMP4 */
}enumPosInputType;

/** 放大器增益定义 */
typedef enum PagGainType
{
	OPAMP_PagGain_2 = 0,
	OPAMP_PagGain_4,
	OPAMP_PagGain_8,
	OPAMP_PagGain_16,
	OPAMP_PagGain_2_VM0 = 8,
	OPAMP_PagGain_4_VM0,
	OPAMP_PagGain_8_VM0,
	OPAMP_PagGain_16_VM0,
	OPAMP_PagGain_2_VM1,
	OPAMP_PagGain_4_VM1,
	OPAMP_PagGain_8_VM1,
	OPAMP_PagGain_16_VM1
}enumPagGainType;


extern void drv_opamp_deinit( OpampType *pOpamp );
extern void drv_opamp_init( OpampType *pOpamp, enumInvInputType InvInput, enumPosInputType PosInput );
extern void drv_opamp_enale( OpampType *pOpamp );
extern void drv_opamp_disable( OpampType *pOpamp );
extern void drv_opamp_pag_gain( OpampType *pOpamp, enumPagGainType PagGain );
extern LevelState drv_opamp_get_output_status( OpampType *pOpamp );



#endif
