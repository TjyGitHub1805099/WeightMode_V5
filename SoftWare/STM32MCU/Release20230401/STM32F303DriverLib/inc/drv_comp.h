/**
*******************************************************************
* @file    drv_comp.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x  比较器模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_COMP_H__
#define __DRV_COMP_H__


#include "reg_stm32f303_comp.h"


/** 是否锁定比较器的CSR寄存器 */
typedef enum CompReadWriteType
{
	COMP_CSR_READ_WIRTE = 0,		/*!< 可以读写 */
	COMP_CSR_READ					/*!< 只读，自由在复位后才会清零 */
}enumCompReadWriteType;

/** 比较器输出结果状态 */
typedef enum CompOutputType
{
	COMP_OUTPUT_LOW = 0,			/*!< 同相输入低于反相输入 */
	COMP_OUTPUT_HIGH				/*!< 同相输入高于反相输入 */
}enumCompOutputType;

/** 比较器迟滞特性 */
typedef enum CompHysteresisType
{
	COMP_HYSTERESIS_NONE = 0,		/*!< 无迟滞 */
	COMP_HYSTERESIS_LOW,			/*!< 低迟滞 */
	COMP_HYSTERESIS_MEDIUM,			/*!< 中迟滞 */
	COMP_HYSTERESIS_HIGH			/*!< 高迟滞 */
}enumCompHysteresisType;

/** 比较器输出极性 */
typedef enum CompOutputPolType
{
	COMP_OUTPUT_POL = 0,			/*!< 不反相 */
	COMP_OUTPUT_INV					/*!< 反相 */
}enumCompOutputPolType;

/** 比较器模式 */
typedef enum CompModeType
{
	COMP_Mode_HighSpeed = 0,            /*!< 高速 */
	COMP_Mode_MediumSpeed,				/*!< 中速 */
	COMP_Mode_LowPower,					/*!< 低功耗 */
	COMP_Mode_UltraLowPower				/*!< 超低功耗 */
}enumCompModeType;


// 比较器输出
#define COMP_Output_None                  ((UINT32)0x00000000)   /*!< COMP output isn't connected to other peripherals */

/* Output Redirection common for all comparators COMP1...COMP7 */
#define COMP_Output_TIM1BKIN              ((UINT32)0x00000400)   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_Output_TIM1BKIN2             ((UINT32)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
#define COMP_Output_TIM8BKIN              ((UINT32)0x00000C00)   /*!< COMP output connected to TIM8 Break Input (BKIN) */
#define COMP_Output_TIM8BKIN2             ((UINT32)0x00001000)   /*!< COMP output connected to TIM8 Break Input 2 (BKIN2) */
#define COMP_Output_TIM1BKIN2_TIM8BKIN2   ((UINT32)0x00001400)   /*!< COMP output connected to TIM1 Break Input 2 and TIM8 Break Input 2 */

/* Output Redirection common for COMP1 and COMP2 */
#define COMP_Output_TIM1OCREFCLR          ((UINT32)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_Output_TIM1IC1               ((UINT32)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_Output_TIM2IC4               ((UINT32)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_Output_TIM2OCREFCLR          ((UINT32)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM3IC1               ((UINT32)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_Output_TIM3OCREFCLR          ((UINT32)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */

/* Output Redirection specific to COMP3 */
#define COMP_Output_TIM4IC1               ((UINT32)0x00001C00)   /*!< COMP output connected to TIM4 Input Capture 1 */
#define COMP_Output_TIM3IC2               ((UINT32)0x00002000)   /*!< COMP output connected to TIM3 Input Capture 2 */
#define COMP_Output_TIM15IC1              ((UINT32)0x00002800)   /*!< COMP output connected to TIM15 Input Capture 1 */
#define COMP_Output_TIM15BKIN             ((UINT32)0x00002C00)   /*!< COMP output connected to TIM15 Break Input (BKIN) */

/* Output Redirection specific to COMP4 */
#define COMP_Output_TIM3IC3               ((UINT32)0x00001800)   /*!< COMP output connected to TIM3 Input Capture 3 */
#define COMP_Output_TIM8OCREFCLR          ((UINT32)0x00001C00)   /*!< COMP output connected to TIM8 OCREF Clear */
#define COMP_Output_TIM15IC2              ((UINT32)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_Output_TIM4IC2               ((UINT32)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 2 */
#define COMP_Output_TIM15OCREFCLR         ((UINT32)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */

/* Output Redirection specific to COMP5 */
#define COMP_Output_TIM2IC1               ((UINT32)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 1 */
#define COMP_Output_TIM17IC1              ((UINT32)0x00002000)   /*!< COMP output connected to TIM17 Input Capture 1 */
#define COMP_Output_TIM4IC3               ((UINT32)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 3 */
#define COMP_Output_TIM16BKIN             ((UINT32)0x00002800)   /*!< COMP output connected to TIM16 Break Input (BKIN) */

/* Output Redirection specific to COMP6 */
#define COMP_Output_TIM2IC2               ((UINT32)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_Output_COMP6TIM2OCREFCLR     ((UINT32)0x00002000)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM16OCREFCLR         ((UINT32)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_Output_TIM16IC1              ((UINT32)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */
#define COMP_Output_TIM4IC4               ((UINT32)0x00002C00)   /*!< COMP output connected to TIM4 Input Capture 4 */

/* Output Redirection specific to COMP7 */
#define COMP_Output_TIM2IC3               ((UINT32)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 3 */
#define COMP_Output_TIM1IC2               ((UINT32)0x00002400)   /*!< COMP output connected to TIM1 Input Capture 2 */
#define COMP_Output_TIM17OCREFCLR         ((UINT32)0x00002800)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_Output_TIM17BKIN             ((UINT32)0x00002C00)   /*!< COMP output connected to TIM16 Break Input (BKIN) */

//比较器闪烁控制信号源 
/* No blanking source can be selected for all comparators */
#define COMP_BlankingSrce_None                   ((UINT32)0x00000000)    /*!< No blanking source */

/* Blanking source common for COMP1, COMP2, COMP3 and COMP7 */
#define COMP_BlankingSrce_TIM1OC5                ((UINT32)0x00040000)  /*!< TIM1 OC5 selected as blanking source for compartor */

/* Blanking source common for COMP1 and COMP2 */
#define COMP_BlankingSrce_TIM2OC3                ((UINT32)0x00080000)  /*!< TIM2 OC5 selected as blanking source for compartor */

/* Blanking source common for COMP1, COMP2 and COMP5 */
#define COMP_BlankingSrce_TIM3OC3                ((UINT32)0x000C0000)    /*!< TIM2 OC3 selected as blanking source for compartor */

/* Blanking source common for COMP3 and COMP6 */
#define COMP_BlankingSrce_TIM2OC4                ((UINT32)0x000C0000)  /*!< TIM2 OC4 selected as blanking source for compartor */

/* Blanking source common for COMP4, COMP5, COMP6 and COMP7 */
#define COMP_BlankingSrce_TIM8OC5                ((UINT32)0x00080000)  /*!< TIM8 OC5 selected as blanking source for compartor */

/* Blanking source for COMP4 */
#define COMP_BlankingSrce_TIM3OC4                ((UINT32)0x00040000)  /*!< TIM3 OC4 selected as blanking source for compartor */
#define COMP_BlankingSrce_TIM15OC1               ((UINT32)0x000C0000)    /*!< TIM15 OC1 selected as blanking source for compartor */

/* Blanking source common for COMP6 and COMP7 */
#define COMP_BlankingSrce_TIM15OC2               ((UINT32)0x00100000)    /*!< TIM15 OC2 selected as blanking source for compartor */

// 比较器同相输入定义
#define COMP1_POS_INPUT_PA1					0x00
#define COMP2_POS_INPUT_PA7					0x00
#define COMP3_POS_INPUT_PB14				0x00
#define COMP4_POS_INPUT_PB0					0x00
#define COMP5_POS_INPUT_PD12				0x00
#define COMP6_POS_INPUT_PD11				0x00
#define COMP7_POS_INPUT_PA0					0x00

#define COMP1_POS_INPUT_DAC					0x01
#define COMP2_POS_INPUT_PA3					0x01
#define COMP3_POS_INPUT_PD14				0x01
#define COMP4_POS_INPUT_PE7					0x01
#define COMP5_POS_INPUT_PB13				0x01
#define COMP6_POS_INPUT_PB11				0x01
#define COMP7_POS_INPUT_PC1					0x01

//比较器反相端输入类型
#define COMP_INV_INPUT_1_4VREFINT			0x00	/*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_INV_INPUT_1_2VREFINT			0x01	/*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_INV_INPUT_3_4VREFINT			0x02	/*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_INV_INPUT_VREFINT				0x03	/*!< VREFINT connected to comparator inverting input */
#define COMP_INV_INPUT_DAC1					0x04	/*!< DAC1_OUT (PA4) connected to comparator inverting input */
#define COMP_INV_INPUT_DAC2					0x05	/*!< DAC2_OUT (PA5) connected to comparator inverting input */
#define COMP1_INV_INPUT_PA0					0x06
#define COMP2_INV_INPUT_PA2					0x06
#define COMP3_INV_INPUT_PD15				0x06
#define COMP3_INV_INPUT_PB12				0x07
#define COMP4_INV_INPUT_PE8					0x06
#define COMP4_INV_INPUT_PB2					0x07
#define COMP5_INV_INPUT_PD13				0x06
#define COMP5_INV_INPUT_PB10				0x07
#define COMP6_INV_INPUT_PD10				0x06
#define COMP6_INV_INPUT_PB15				0x07
#define COMP7_INV_INPUT_PC0					0x06

extern void drv_comp_init( CompType *pComp, UINT8 InvInput, UINT8 PosInput, enumCompHysteresisType Hysteresis, 
							enumCompOutputPolType Pol, enumCompModeType Mode, UINT32 OutputSel, UINT32 BlinkSrc );
extern void drv_comp_enable( CompType *pComp  );
extern void drv_comp_disable( CompType *pComp  );
extern LevelState drv_comp_get_status( CompType *pComp  );
extern void drv_comp_window_enable( CompType *pComp  );
extern void drv_comp_window_disable( CompType *pComp  );


#endif
