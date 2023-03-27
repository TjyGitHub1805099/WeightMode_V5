/**
  *******************************************************************
  * @file    reg_stm32f303_flash.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-21
  * @brief   STM32F303	FLASH寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef	__REG_STM32F303_FLASH_H__
#define	__REG_STM32F303_FLASH_H__

#include "typedefine.h"
#include "reg_stm32f303_address.h"


/** FLASH访问控制寄存器位定义 */
typedef struct
{
	UINT32	LATENCY		: 3;		/**< Bit0~2，延迟 */
	UINT32	HLFCYA		: 1;		/**< Bit3，flash半周期访问使能 */
	UINT32	PRFTBE		: 1;		/**< Bit4，预读取缓冲使能 */
	UINT32	PRFTBS		: 1;		/**< Bit5，预读取缓冲状态 */
	UINT32	Rsvd1		: 26;		/**< Bit6~31，保留 */
}FlashAcrBitType;

/** FLASH访问控制寄存器定义 */
typedef union
{
	UINT32	all;
	FlashAcrBitType		bit;
}FlashAcrType;

/** FLASH	状态寄存器位定义 */
typedef struct
{
	UINT32	BSY				: 1;		/**< Bit0，忙 */
	UINT32	Rsvd1			: 1;		/**< Bit1，保留 */
	UINT32	PGERR			: 1;		/**< Bit2，编程错误 */
	UINT32	Rsvd2			: 1;		/**< Bit3，保留 */
	UINT32	WRPRTERR		: 1;			/**< Bit4，写保护错误 */
	UINT32	EOP				: 1;		/**< Bit5，操作结束 */
	UINT32	Rsvd3			: 26;		/**< Bit6~31，保留 */
}FlashSrBitType;

/** FLASH状态寄存器定义 */
typedef	union
{
	UINT32	all;
	FlashSrBitType	bit;
}FlashSrType;

/** FLASH控制寄存器位定义 */
typedef struct
{
	UINT32	PG					: 1;		/**< Bit0，编程选择的flash */
	UINT32	PER					: 1;		/**< Bit1，擦除选择的页 */
	UINT32	MER					: 1;		/**< Bit2，擦除所有用户选择的页 */
	UINT32	Rsvd1				: 1;		/**< Bit3，保留 */
	UINT32	OPTPG				: 1;		/**< Bit4，选项字节编程 */
	UINT32	OPTER				: 1;		/**< Bit5，选项字节擦除 */
	UINT32	STRT				: 1;		/**< Bit6，开始擦除操作 */
	UINT32	LOCK				: 1;		/**< Bit7，锁定 */
	UINT32	Rsvd2				: 1;		/**< Bit8，保留 */
	UINT32	OPTWRE			    : 1;		/**< Bit9，选项字节写使能 */
	UINT32	ERRIE				: 1;		/**< Bit10，错误中断使能 */
	UINT32	Rsvd3				: 1;		/**< Bit11，保留 */
	UINT32	EOPIE				: 1;		/**< Bit12，编程接收中断使能 */
	UINT32	OBL_LAUNCH	        : 1;		/**< Bit13，强制选项字节载入 */
	UINT32	Rsvd4				: 18;		/**< Bit14~31，保留 */
}FlashCrBitType;

/** FLASH控制寄存器定义 */
typedef union
{
	UINT32	all;
	FlashCrBitType	bit;
}FlashCrType;

/** 选项字节寄存器位定义 */
typedef struct
{
	UINT32	OPTERR	    : 1;		/**< Bit0，选项字节载入错误 */
	UINT32	RDPRT		: 2;		/**< Bit1~2，读保护级别状态 */
	UINT32	Rsvd1		: 5;		/**< Bit3~7，保留 */
	UINT32	OBR			: 8;		/**< Bit8~15，用户选项字节 */
	UINT32	DATA0		: 8;		/**< Bit16~23，数据0 */
	UINT32	DATA1		: 8;		/**< Bit24~31，数据1 */
}FlashObrBitType;

/** 选项字节寄存器定义 */
typedef union
{
	UINT32	all;
	FlashObrBitType		bit;
}FlashObrType;

/** FLASH 寄存器 */
typedef struct
{
	FlashAcrType		ACR;			/**< 偏移地址0x00 */
	UINT32				KEYR			/**< 偏移地址0x04 */;
	UINT32				OPTKEYR;		/**< 偏移地址0x08 */
	FlashSrType			SR;				/**< 偏移地址0x0c */
	FlashCrType			CR;				/**< 偏移地址0x10 */
	UINT32				AR;				/**< 偏移地址0x14 */
	UINT32				Rsvd1;			/**< 偏移地址0x18 */
	FlashObrType		OBR;			/**< 偏移地址0x1c */
	UINT32				WRPR;			/**< 偏移地址0x20 */
}FlashType;



/** FLASH 寄存器地址 */
#define	FLASH		((FlashType *) FLASH_R_BASE )



#endif

