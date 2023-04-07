/**
  *******************************************************************
  * @file    reg_stm32f303_opamp.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-22
  * @brief   STM32F303 OPAMP寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef __REG_STM32F303_OPAMP_H__
#define __REG_STM32F303_OPAMP_H__

#include "typedefine.h"
#include "reg_stm32f303_address.h"


/** OPMAMP控制寄存器位定义 */
typedef struct
{
	UINT32    OPAMPEN    	: 1 ;		/**< Bit0，	OPAMP使能位，0：失能，1：使能 */
	UINT32    FORCE_VP    	: 1 ;		/**< Bit1， 强制校准参考电压位，0：正常运放模式，1:校准模式 */
	UINT32    VP_SEL      	: 2 ;		/**< Bit2~3， 通向输入端选择位，00：PA7作为同向端输入，01：PA5作为同向端输入，10：PA3作为同向端输入，11：PA1作为同向端输入 */
	UINT32    Rsvd1        	: 1 ;      	/**< Bit4， 保留位 */
	UINT32	  VM_SEL        : 2 ;       /**< Bit5~6， 反向输入的选择位，00：PC5作为反向端输入，01：PA3作为反向端输入，10:PGA模式，11，跟随模式 */
	UINT32    TCM_EN      	: 1 ;		/**< Bit7， 计时器控制多路复用模式位，用于在默认模式与次要模式间切换 */
	UINT32    VMS_SEL     	: 1 ;       /**< Bit8， 反向输入第二模式位，TCM_EN为一时有效，0：PC5作为反向输入，1：PA3作为反向输入 */
	UINT32    VPS_SEL     	: 2 ;       /**< Bit9~10， 同相输入第二模式位，TCM_EN为一时有效，00：PA7作为同向端输入，01：PA5作为同向端输入，10：PA3作为同向端输入，11：PA1作为同向端输入 */
	UINT32    CALON       	: 1 ;       /**< Bit11， 校准模式使能位，0：关校准模式，1：开校准模式 */
	UINT32    CALSEL      	: 2 ;       /**< Bit12~13， 校准选择位，00：参考电压位3.3%的Vdd，01：参考电压位10%的Vdd，10：参考电压位50%的Vdd，11：参考电压位90%的Vdd */
	UINT32    PGA_GAIN    	: 4 ;       /**< Bit14~17， 放大器增益设置位 ，2——16倍 */
	UINT32    USER_TRIM   	: 1 ;       /**< Bit18， 用户调整使能位，0:失能，1：使能 */
	UINT32    TRIMOFFSETP 	: 5 ;       /**< Bit19~23， PMOS端偏移调整值 */
	UINT32    TRIMOFFSETN 	: 5 ;       /**< Bit24~28， SMOS端偏移调整值 */
	UINT32    TSTREF      	: 1 ;       /**< Bit29， 内部参考电压输出位，0：输出VREFOPAMP，1：不输出VREFOPAMP */
	UINT32    OUTCAL      	: 1 ;       /**< Bit30， 比较器输出位，0：同向端大于反向端，1：反向端大于同向端 */
	UINT32    LOCK        	: 1 ;       /**< Bit31， 寄存器写入锁定位，0:可读可写，1：只能读 */
}OpampCsrBitType;

/** OPMAMP控制寄存器定义 */
typedef union
{
	UINT32	all;
	OpampCsrBitType	bit;
}OpampCsrType;

typedef struct
{
	OpampCsrType		CSR;
}OpampType;


///** OPAMP寄存器 */
//typedef struct
//{
//	OpampCsrType	OPAMP1CSR; /**< Opamp1控制寄存器，偏移地址0x38 */
//	OpampCsrType	OPAMP2CSR; /**< Opamp2控制寄存器，偏移地址0x3c */
//	OpampCsrType	OPAMP3CSR; /**< Opamp3控制寄存器，偏移地址0x40 */
//	OpampCsrType	OPAMP4CSR; /**< Opamp4控制寄存器，偏移地址0x44 */
//}OpampType;



/** OPAMP 模块定义 */
//#define OPAMP		((OpampType *) OPAMP_BASE)
#define OPAMP1		(( OpampType *) OPAMP1_BASE)
#define OPAMP2		(( OpampType *) OPAMP2_BASE)
#define OPAMP3		(( OpampType *) OPAMP3_BASE)
#define OPAMP4		(( OpampType *) OPAMP4_BASE)

	
#endif
