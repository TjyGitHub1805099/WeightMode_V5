/**
*******************************************************************
* @file    drv_opamp.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F303 OPAMP模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/


#include "drv_opamp.h"


/**
* @brief  复位
* @param  pComp: 放大器 OPAMP1~OPAMP4
* @retval 无
*/
void drv_opamp_deinit( OpampType *pOpamp )
{
	pOpamp->CSR.all = 0x00000000;
}

/**
* @brief  初始化
* @param  pComp: 放大器 OPAMP1~OPAMP4
* @param  InvInput: 反向输入端选择 可以是下面的一个：
*            @arg OPAMP_InvInput_IO1
*            @arg OPAMP_InvInput_IO1
*            @arg OPAMP_InvInput_PGA
*            @arg OPAMP_InvInput_Vout
* @param  PosInput: 反向输入端选择 可以是下面的一个：
*            @arg OPAMP_PosInput_IO1
*            @arg OPAMP_PosInput_IO2
*            @arg OPAMP_PosInput_IO3
*            @arg OPAMP_PosInput_IO4
* @retval 无
*/
void drv_opamp_init( OpampType *pOpamp, enumInvInputType InvInput, enumPosInputType PosInput )
{
	pOpamp->CSR.bit.VM_SEL = (UINT16)InvInput;
	pOpamp->CSR.bit.VP_SEL = (UINT16)PosInput;
}

/**
* @brief  使能
* @param  pComp: 放大器 OPAMP1~OPAMP4
* @retval 无
*/
void drv_opamp_enale( OpampType *pOpamp )
{
	pOpamp->CSR.bit.OPAMPEN = 1;
}

/**
* @brief  禁止
* @param  pComp: 放大器 OPAMP1~OPAMP4
* @retval 无
*/
void drv_opamp_disable( OpampType *pOpamp )
{
	pOpamp->CSR.bit.OPAMPEN = 0;
}

/**
* @brief  设置放大器增益
* @param  pComp: 放大器 OPAMP1~OPAMP4
* @retval 无
*/
void drv_opamp_pag_gain( OpampType *pOpamp, enumPagGainType PagGain )
{
	pOpamp->CSR.bit.PGA_GAIN = (UINT16)PagGain;
}

/**
* @brief  获取放大器输出状态
* @param  pComp: 放大器 OPAMP1~OPAMP4
* @retval 无
*/
LevelState drv_opamp_get_output_status( OpampType *pOpamp )
{
	OpampCsrType l_Csr;
	
	l_Csr.all = pOpamp->CSR.all;
	if( l_Csr.bit.OUTCAL == 1 )
	{
		return HIGH;
	}
	else
	{
		return LOW;
	}
}
