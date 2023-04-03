/**
  *******************************************************************
  * @file    reg_stm32f303_comp.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-22
  * @brief   STM32F303 Comparator寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef	__REG_STM32F303_COMP_H__
#define __REG_STM32F303_COMP_H__


#include "reg_stm32f303_address.h"



/** COMP 控制和状态寄存器位定义 */
typedef struct
{
	UINT32	COMPEN			: 1;			/**< Bit0，比较器使能 */
	UINT32	COMP_INP_DAC	: 1;			/**< Bit1，比较器1不反相输入连接到DAC输出，其他比较器此处为保留 */
	UINT32	COMPMODE		: 2;			/**< Bit2~3，比较器模式 */
	UINT32	COMPINMSEL		: 3;			/**< Bit4~6，比较器反相输入选择 */
	UINT32	COMPINPSEL		: 1;			/**< Bit7，比较器同相输入选择 */
	UINT32	Rsvd2			: 1;			/**< Bit8，保留 */
	UINT32	COMPWINMODE		: 1;			/**< Bit9，比较器窗口模式 */
	UINT32	COMPOUTSEL		: 4;			/**< Bit10~13，比较器输出选择 */
	UINT32	Rsvd3			: 1;			/**< Bit14，保留 */
	UINT32	COMPPOL			: 1;			/**< Bit15，比较器输出极性 */
	UINT32	COMPHYST		: 2;			/**< Bit16~17，比较器滞后 */
	UINT32	COMP_BLANKING	: 3;			/**< Bit18~20，比较器输出关断源 */
	UINT32	Rsvd4			: 1;			/**< Bit21，保留 */
	UINT32	COMPINMSEL_3	: 1;			/**< Bit22，比较器反相输入选择 */
	UINT32	Rsvd5			: 7;			/**< Bit23~29，保留 */
	UINT32	COMPOUT			: 1;			/**< Bit30，比较器输出 */
	UINT32	COMPLOCK		: 1;			/**< Bit31，比较器锁定 */
}CompCsrBitType;


/** COMP 控制和状态寄存器定义 */
typedef union
{
	UINT32	all;
	CompCsrBitType	bit;
}CompCsrType;


/** COMP 寄存器 */
typedef struct
{
	CompCsrType		CSR;
}CompType;



/** COMP 模块定义 */
#define	COMP		((CompType *) COMP_BASE)
#define	COMP1		((CompType *) COMP1_BASE)
#define	COMP2		((CompType *) COMP2_BASE)
#define	COMP3		((CompType *) COMP3_BASE)
#define	COMP4		((CompType *) COMP4_BASE)
#define	COMP5		((CompType *) COMP5_BASE)
#define	COMP6		((CompType *) COMP6_BASE)
#define	COMP7		((CompType *) COMP7_BASE)


#endif
