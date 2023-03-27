/**
  *******************************************************************
  * @file    reg_stm32f303_syscfg.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-22
  * @brief   STM32F303 SYSCFG寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef __REG_STM32F303_SYSCFG_H__
#define __REG_STM32F303_SYSCFG_H__


#include "reg_stm32f303_address.h"


/** SYSCFG 配置寄存器1位定义 */
typedef struct
{
	UINT32	MEM_MODE								: 3;			/**< Bit0~2，存储区映射选择位 */
	UINT32	Rsvd1										: 2;			/**< Bit3~4，保留 */
	UINT32	USB_IT_RMP							: 1;			/**< Bit5，USB中断重映射 */
	UINT32	TIM1_ITR3_RMP						: 1;			/**< Bit6，定时器1 ITR3选择 */
	UINT32	DAC1_TRIG_RMP						: 1;			/**< Bit7，DAC触发重映射 */
	UINT32	ADC2_DMA_RMP						: 1;			/**< Bit8，ADC2 DMA重映射位 */
	UINT32	Rsvd2										: 2;			/**< Bit9~10，保留 */
	UINT32	TIM16_DMA_RMP						: 1;			/**< Bit11，定时器16 DMA请求重映射 */
	UINT32	TIM17_DMA_RMP						: 1;			/**< Bit12，定时器17 DMA响应重映射 */
	UINT32	TIM6_DAC1_CH1_DMA_RMP		: 1;			/**< Bit13，定时器6和DAC 通道1 DMA重映射 */
	UINT32	TIM7_DAC1_CH2_DMA_RMP		: 1;			/**< Bit14，定时器7和DAC 通道2 DMA重映射 */
	UINT32	DAC2_CH1_DMA_RMP				: 1;			/**< Bit15，DAC2通道1 DMA重映射 */
	UINT32	I2C_PB6_FMP							: 1;			/**< Bit16，PB6 Fm+ 驱动能力激活 */
	UINT32	I2C_PB7_FMP							: 1;			/**< Bit17，PB7 Fm+ 驱动能力激活 */
	UINT32	I2C_PB8_FMP							: 1;			/**< Bit18，PB8 Fm+ 驱动能力激活 */
	UINT32	I2C_PB9_FMP							: 1;			/**< Bit19，PB9 Fm+ 驱动能力激活 */
	UINT32	I2C1_FMP								: 1;			/**< Bit20，I2C1 Fm+驱动能力激活 */
	UINT32	I2C2_FMP								: 1;			/**< Bit21，I2C2 Fm+驱动能力激活 */
	UINT32	ENCODER_MODE						: 2;			/**< Bit22~23，编码器模式 */
	UINT32	I2C3_FMP								: 1;			/**< Bit24，I2C3 Fm+驱动能力激活 */
	UINT32	Rsvd4										: 1;			/**< Bit25，保留 */
	UINT32	FPU_IE									: 6;			/**< Bit26~31，浮点单元中断使能位 */
}SyscfgCfgr1BitType;

/** SYSCFG 配置寄存器1定义 */
typedef union
{
	UINT32	all;
	SyscfgCfgr1BitType	bit;
}SyscfgCfgr1Type;

/** SYSCFG	CCM RAM保护寄存器位定义 */
typedef struct
{
	UINT32	PAGE0_WP		: 1;			/**< Bit0，CCM RAM 第0页写保护位 */
	UINT32	PAGE1_WP		: 1;			/**< Bit1，CCM RAM 第1页写保护位 */
	UINT32	PAGE2_WP		: 1;			/**< Bit2，CCM RAM 第2页写保护位 */
	UINT32	PAGE3_WP		: 1;			/**< Bit3，CCM RAM 第3页写保护位 */
	UINT32	PAGE4_WP		: 1;			/**< Bit4，CCM RAM 第4页写保护位 */
	UINT32	PAGE5_WP		: 1;			/**< Bit5，CCM RAM 第5页写保护位 */
	UINT32	PAGE6_WP		: 1;			/**< Bit6，CCM RAM 第6页写保护位 */
	UINT32	PAGE7_WP		: 1;			/**< Bit7，CCM RAM 第7页写保护位 */
	UINT32	PAGE8_WP		: 1;			/**< Bit8，CCM RAM 第8页写保护位 */
	UINT32	PAGE9_WP		: 1;			/**< Bit9，CCM RAM 第9页写保护位 */
	UINT32	PAGE10_WP		: 1;			/**< Bit10，CCM RAM 第10页写保护位 */
	UINT32	PAGE11_WP		: 1;			/**< Bit11，CCM RAM 第11页写保护位 */
	UINT32	PAGE12_WP		: 1;			/**< Bit12，CCM RAM 第12页写保护位 */
	UINT32	PAGE13_WP		: 1;			/**< Bit13，CCM RAM 第13页写保护位 */
	UINT32	PAGE14_WP		: 1;			/**< Bit14，CCM RAM 第14页写保护位 */
	UINT32	PAGE15_WP		: 1;			/**< Bit15，CCM RAM 第15页写保护位 */
	UINT32	Rsvd1				: 16;			/**< Bit16~31，保留 */
}SyscfgRcrBitType;

/** SYSCFG	CCM RAM保护寄存器定义 */
typedef union
{
	UINT32	all;
	SyscfgRcrBitType	bit;
}SyscfgRcrType;

/** SYSCFG	外部中断配置寄存器1位定义 */
typedef struct
{
	UINT32	EXTI0		: 4;				/**< Bit0~3，外部中断0配置位 */
	UINT32	EXTI1		: 4;				/**< Bit4~7，外部中断1配置位 */
	UINT32	EXTI2		: 4;				/**< Bit8~11，外部中断2配置位 */
	UINT32	EXTI3		: 4;				/**< Bit12~15，外部中断3配置位 */
	UINT32	Rsvd1		: 16;				/**< Bit16~31，保留*/
}SyscfgExticr1BitType;

/** SYSCFG	外部中断配置寄存器1定义 */
typedef union
{
	UINT32	all;
	SyscfgExticr1BitType	bit;
}SyscfgExticr1Type;

/** SYSCFG	外部中断配置寄存器2位定义 */
typedef struct
{
	UINT32	EXTI4		: 4;				/**< Bit0~3，外部中断4配置位 */
	UINT32	EXTI5		: 4;				/**< Bit4~7，外部中断5配置位 */
	UINT32	EXTI6		: 4;				/**< Bit8~11，外部中断6配置位 */
	UINT32	EXTI7		: 4;				/**< Bit12~15，外部中断7配置位 */
	UINT32	Rsvd1		: 16;				/**< Bit16~31，保留*/
}SyscfgExticr2BitType;

/** SYSCFG	外部中断配置寄存器2定义 */
typedef union
{
	UINT32	all;
	SyscfgExticr2BitType	bit;
}SyscfgExticr2Type;

/** SYSCFG	外部中断配置寄存器3位定义 */
typedef struct
{
	UINT32	EXTI8		: 4;				/**< Bit0~3，外部中断8配置位 */
	UINT32	EXTI9		: 4;				/**< Bit4~7，外部中断9配置位 */
	UINT32	EXTI10	: 4;				/**< Bit8~11，外部中断10配置位 */
	UINT32	EXTI11	: 4;				/**< Bit12~15，外部中断11配置位 */
	UINT32	Rsvd1		: 16;				/**< Bit16~31，保留*/
}SyscfgExticr3BitType;

/** SYSCFG	外部中断配置寄存器3定义 */
typedef union
{
	UINT32	all;
	SyscfgExticr3BitType	bit;
}SyscfgExticr3Type;

/** SYSCFG	外部中断配置寄存器4位定义 */
typedef struct
{
	UINT32	EXTI12	: 4;				/**< Bit0~3，外部中断12配置位 */
	UINT32	EXTI13	: 4;				/**< Bit4~7，外部中断13配置位 */
	UINT32	EXTI14	: 4;				/**< Bit8~11，外部中断14配置位 */
	UINT32	EXTI15	: 4;				/**< Bit12~15，外部中断15配置位 */
	UINT32	Rsvd1		: 16;				/**< Bit16~31，保留*/
}SyscfgExticr4BitType;

/** SYSCFG	外部中断配置寄存器4定义 */
typedef union
{
	UINT32	all;
	SyscfgExticr4BitType	bit;
}SyscfgExticr4Type;

/** SYSCFG	配置寄存器2位定义 */
typedef struct
{
	UINT32	LOCKUP_LOCK						: 1;			/**< Bit0，Cotex M4 锁住输出使能 */
	UINT32	SRAM_PARITY_LOCK			: 1;			/**< Bit1，SRAM 奇偶校验锁定位 */
	UINT32	PVD_LOCK							: 1;			/**< Bit2，PVD锁定使能位 */
	UINT32	Rsvd1									: 1;			/**< Bit3，保留 */
	UINT32	BYP_ADDR_PAR					: 1;			/**< Bit4，奇偶校验计算时绕过地址bit29 */
	UINT32	Rsvd2									: 3;			/**< Bit5~7，保留 */
	UINT32	SRAM_PEF							: 1;			/**< Bit8，SRAM	奇偶校验错误标志 */
	UINT32	Rsvd3									: 23;			/**< Bit9~31，保留 */
}SyscfgCfgr2BitType;

/** SYSCFG	配置寄存器2定义 */
typedef union
{
	UINT32	all;
	SyscfgCfgr2BitType	bit;
}SyscfgCfgr2Type;

/** SYSCFG	配置寄存器3位定义 */
typedef struct
{
	UINT32	SPI1_RX_DMA_RMP		: 2;				/**< Bit0~1，SPI1_RX DMA重映射位 */
	UINT32	SPI1_TX_DMA_RMP		: 2;				/**< Bit2~3，SPI1_TX DMA重映射位 */
	UINT32	I2C1_RX_DMA_RMP		: 2;				/**< Bit4~5，I2C1_RX DMA重映射位 */
	UINT32	I2C1_TX_DMA_RMP		: 2;				/**< Bit6~7，I2C1_TX DMA重映射位 */
	UINT32	ADC2_DMA_RMP			: 2;				/**< Bit8~9，ADC2 DMA通道重映射位 */
	UINT32	Rsvd1							: 22;				/**< Bit10~31，保留 */
}SyscfgCfgr3BitType;

/** SYSCFG	配置寄存器3定义 */
typedef union
{
	UINT32	all;
	SyscfgCfgr3BitType	bit;
}SyscfgCfgr3Type;

/** SYSCFG	配置寄存器4位定义 */
typedef struct
{
	UINT32	ADC12_EXT2_RMP		: 1;			/**< Bit0，控制ADC12常规通道输入触发EXT2 */
	UINT32	ADC12_EXT3_RMP		: 1;			/**< Bit1，控制ADC12常规通道输入触发EXT3 */
	UINT32	ADC12_EXT5_RMP		: 1;			/**< Bit2，控制ADC12常规通道输入触发EXT5 */
	UINT32	ADC12_EXT13_RMP		: 1;			/**< Bit3，控制ADC12常规通道输入触发EXT13 */
	UINT32	ADC12_EXT15_RMP		: 1;			/**< Bit4，控制ADC12常规通道输入触发EXT15 */
	UINT32	ADC12_JEXT3_RMP		: 1;			/**< Bit5，控制ADC12注入通道输入触发EXT3 */
	UINT32	ADC12_JEXT6_RMP		: 1;			/**< Bit6，控制ADC12注入通道输入触发EXT6 */
	UINT32	ADC12_JEXT13_RMP	: 1;			/**< Bit7，控制ADC12注入通道输入触发EXT13 */
	UINT32	ADC34_EXT5_RMP		: 1;			/**< Bit8，控制ADC34常规通道输入触发EXT5 */
	UINT32	ADC34_EXT6_RMP		: 1;			/**< Bit9，控制ADC34常规通道输入触发EXT6 */
	UINT32	ADC34_EXT15_RMP		: 1;			/**< Bit10，控制ADC34常规通道输入触发EXT15 */
	UINT32	ADC34_JEXT5_RMP		: 1;			/**< Bit11，控制ADC34注入通道输入触发EXT5 */
	UINT32	ADC34_JEXT11_RMP	: 1;			/**< Bit12，控制ADC34注入通道输入触发EXT11 */
	UINT32	ADC34_JEXT14_RMP	: 1;			/**< Bit13，控制ADC34注入通道输入触发EXT14 */
	UINT32	Rsvd1							: 18;			/**< Bit14~31，保留 */
}SyscfgCfgr4BitType;

/** SYSCFG	配置寄存器4定义 */
typedef union
{
	UINT32	all;
	SyscfgCfgr4BitType	bit;
}SyscfgCfgr4Type;


/** SYSCFG 寄存器 */
typedef struct
{
	SyscfgCfgr1Type			CFGR1;					/**< SYSCFG配置寄存器1 ，偏移地址0x00 */
	SyscfgRcrType			RCR;					/**< CCM RAM 保护寄存器 ，偏移地址0x04 */
	SyscfgExticr1Type		EXTICR1;				/**< SYSCFG外部中断配置寄存器1 ，偏移地址0x08 */
	SyscfgExticr2Type		EXTICR2;				/**< SYSCFG外部中断配置寄存器2 ，偏移地址0x0c */
	SyscfgExticr3Type		EXTICR3;				/**< SYSCFG外部中断配置寄存器3 ，偏移地址0x10 */
	SyscfgExticr4Type		EXTICR4;				/**< SYSCFG外部中断配置寄存器4 ，偏移地址0x14 */
	SyscfgCfgr2Type			CFGR2;					/**< SYSCFG配置寄存器2 ，偏移地址0x18 */
	UINT32							Rsvd1[11];			/**< 保留 ，偏移地址0x1c~0x44 */
	SyscfgCfgr4Type			CFGR4;					/**< SYSCFG配置寄存器4 ，偏移地址0x48 */
	UINT32							Rsvd2;					/**< 保留，偏移地址0x4c */
	SyscfgCfgr3Type			CFGR3;					/**< SYSCFG配置寄存器3 ，偏移地址0x50 */
}SyscfgType;



/** SYSCFG 寄存器地址 */
#define SYSCFG	((SyscfgType *) SYSCFG_BASE)


#endif
