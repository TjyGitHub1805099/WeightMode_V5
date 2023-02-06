/**
*******************************************************************
* @file    drv_comp.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40xADC模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/


#include "drv_comp.h"

/**
* @brief  复位
* @param  pComp: 比较器，可以是 COMP1 ~ COMP7
* @retval 无
*/
void drv_comp_deinit( CompType *pComp )
{
	pComp->CSR.all = 0x00000000;
}

/**
* @brief  初始化
* @param  pComp: 比较器，可以是 COMP1 ~ COMP7
* @param  InvInput: 反相输入信号
*            @arg  COMP_INV_INPUT_1_4VREFINT: 1/4 VREFINT connected to comparator inverting input
*            @arg  COMP_INV_INPUT_1_2VREFINT: 1/2 VREFINT connected to comparator inverting input
*			 @arg  COMP_INV_INPUT_3_4VREFINT: 3/4 VREFINT connected to comparator inverting input
*			 @arg  COMP_INV_INPUT_VREFINT: VREFINT connected to comparator inverting input
*			 @arg  COMP_INV_INPUT_DAC1: DAC1_OUT (PA4) connected to comparator inverting input
*			 @arg  COMP_INV_INPUT_DAC2: DAC2_OUT (PA5) connected to comparator inverting input
*			 @arg  COMP1_INV_INPUT_PA0: 
*			 @arg  COMP2_INV_INPUT_PA2: 
*			 @arg  COMP3_INV_INPUT_PD15: 
*		 	 @arg  COMP3_INV_INPUT_PB12: 
*			 @arg  COMP4_INV_INPUT_PE8: 
*			 @arg  COMP4_INV_INPUT_PB2: 
*			 @arg  COMP5_INV_INPUT_PD13: 
*			 @arg  COMP5_INV_INPUT_PB10: 
*			 @arg  COMP6_INV_INPUT_PD10: 
*			 @arg  COMP6_INV_INPUT_PB15: 
*			 @arg  COMP7_INV_INPUT_PC0: 
* @param  PosInput : 同相输入信号
*            @arg COMP1_POS_INPUT_PA1: 比较器1同相输入端为PA1
*            @arg COMP1_POS_INPUT_DAC: 比较器1同相输入端为DAC，PA4
*            @arg COMP2_POS_INPUT_PA7: 比较器2同相输入端为PA1
*            @arg COMP2_POS_INPUT_PA3: 比较器2同相输入端为PA3
*            @arg COMP3_POS_INPUT_PB14: 比较器3同相输入端为PB14
*            @arg COMP3_POS_INPUT_PD14: 比较器3同相输入端为PD14
*            @arg COMP4_POS_INPUT_PB0: 比较器4同相输入端为PB0
*            @arg COMP4_POS_INPUT_PE7: 比较器4同相输入端为PE7
*            @arg COMP5_POS_INPUT_PD12: 比较器5同相输入端为PD12
*            @arg COMP5_POS_INPUT_PB13: 比较器5同相输入端为PB13
*            @arg COMP6_POS_INPUT_PD11: 比较器6同相输入端为PD11
*            @arg COMP6_POS_INPUT_PB11: 比较器6同相输入端为PB11
*            @arg COMP7_POS_INPUT_PA0: 比较器7同相输入端为PA0
*            @arg COMP7_POS_INPUT_PC1: 比较器7同相输入端为PC1
* @param  Hysteresis: 迟滞效果
* @param  Pol: 输出极性
* @param  Mode: 比较器模式
* @param  OutputSel: 输出连接到定时器
* @param  BlinkSrc: 闪烁控制信号源
* @retval 无
*/
void drv_comp_init( CompType *pComp, UINT8 InvInput, UINT8 PosInput, enumCompHysteresisType Hysteresis, 
					enumCompOutputPolType Pol, enumCompModeType Mode, UINT32 OutputSel, UINT32 BlinkSrc )
{
	drv_comp_deinit( pComp );
	pComp->CSR.bit.COMPEN	  = 0;					//关闭比较器
	pComp->CSR.bit.COMPINMSEL = (UINT16)InvInput;	//反向输入信号
	pComp->CSR.bit.COMPINPSEL = (UINT16)PosInput;	//同向输入信号
	pComp->CSR.bit.COMPHYST	  = (UINT16)Hysteresis;	//迟滞
	pComp->CSR.bit.COMPPOL	  = (UINT16)Pol;		//极性
	pComp->CSR.bit.COMPMODE   = (UINT16)Mode;		//模式
	pComp->CSR.bit.COMPOUTSEL = (UINT16)OutputSel;	//输出选择
	pComp->CSR.bit.COMP_BLANKING = BlinkSrc;		//闪烁控制信号
}

/**
* @brief  使能
* @param  pComp: 比较器，可以是 COMP1 ~ COMP7
* @retval 无
*/
void drv_comp_enable( CompType *pComp )
{ 
	pComp->CSR.bit.COMPEN = 1;
}

/**
* @brief  禁止
* @param  pComp: 比较器，可以是 COMP1 ~ COMP7
* @retval 无
*/
void drv_comp_disable( CompType *pComp )
{
	pComp->CSR.bit.COMPEN = 0;
}

/**
* @brief  读比较器输出状态
* @param  pComp: 比较器，可以是 COMP1 ~ COMP7
* @retval 输出状态
*/
LevelState drv_comp_get_status( CompType *pComp  )
{
	CompCsrType l_Csr;
	
	l_Csr.all = pComp->CSR.all;
	if( l_Csr.bit.COMPOUT != 0 )
	{
		return HIGH;
	}
	else
	{
		return LOW;
	}
}

/**
* @brief  使能比较器窗口模式
* @param  pComp: 比较器，可以是 COMP1 ~ COMP7
* @retval 无
*/
void drv_comp_window_enable( CompType *pComp  )
{ 
	pComp->CSR.bit.COMPWINMODE = 1;
}

/**
* @brief  禁止比较器窗口模式
* @param  pComp: 比较器，可以是 COMP1 ~ COMP7
* @retval 无
*/
void drv_comp_window_disable( CompType *pComp  )
{
	pComp->CSR.bit.COMPWINMODE = 0;
}
