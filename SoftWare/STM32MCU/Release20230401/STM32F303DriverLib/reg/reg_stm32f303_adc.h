/**
  *******************************************************************
  * @file    reg_stm32f303_adc.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-21
  * @brief   STM32F303 ADC寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef	__REG_STM32F303_ADC_H__
#define	__REG_STM32F303_ADC_H__


#include "reg_stm32f303_address.h"


/** ADC中断和状态寄存器位定义 */
typedef struct
{
	UINT32	ADRDY			: 1;		/**< Bit0，ADC就绪 */
	UINT32	EOSMP			: 1;		/**< Bit1，采样结束标志 */
	UINT32	EOC				: 1;		/**< Bit2，转换结束标志 */
	UINT32	EOS				: 1;		/**< Bit3，正规序列结束标志 */
	UINT32	OVR				: 1;		/**< Bit4，ADC超时 */
	UINT32	JEOC			: 1;		/**< Bit5，注入通道转换结束标志 */
	UINT32	JEOS			: 1;		/**< Bit6，注入通道序列结束标志 */
	UINT32	AWD1			: 1;		/**< Bit7，模拟量看门狗1标志 */
	UINT32	AWD2			: 1;		/**< Bit8，模拟量看门狗2标志 */
	UINT32	ADD3			: 1;		/**< Bit9，模拟量看门狗3标志 */
	UINT32	JQOVF			: 1;		/**< Bit10，注入队列溢出 */
	UINT32	Rsvd1			: 21;		/**< Bit11~31，保留 */
}AdcIsrBitType;

/** ADC中断和状态寄存器定义 */
typedef union
{
	UINT32	all;
	AdcIsrBitType		bit;
}AdcIsrType;

/** ADC中断使能寄存器位定义 */
typedef	struct
{
	UINT32	ADRDYIE		: 1;		/**< Bit0，ADC就绪中断使能 */
	UINT32	EOSMPIE		: 1;		/**< Bit1，定期转换采样结束中断标志使能 */
	UINT32	EOCIE			: 1;		/**< Bit2，定期转换结束中断使能 */
	UINT32	EOSIE			: 1;		/**< Bit3，正常序列转换结束中断使能 */
	UINT32	VORIE			: 1;		/**< Bit4，超时中断使能 */
	UINT32	JEOCIE		: 1;		/**< Bit5，注入转换结束中断使能 */
	UINT32	JEOSIE		: 1;		/**< Bit6，注入转换顺序结束中断使能 */
	UINT32	AWD1IE		: 1;		/**< Bit7，模拟量看门狗1中断使能 */
	UINT32	AWD2IE		: 1;		/**< Bit8，模拟量看门狗2中断使能 */
	UINT32	AWD3IE		: 1;		/**< Bit9，模拟量看门狗3中断使能 */
	UINT32	JQOVFIE		: 1;		/**< Bit10，注入队列溢出中断使能 */
	UINT32	Rsvd1		: 21;		/**< Bit11~31，保留 */
}AdcIerBitType;

/** ADC中断使能寄存器定义 */
typedef union
{
	UINT32	all;
	AdcIerBitType		bit;
}AdcIerType;

/** ADC 控制寄存器位定义 */
typedef struct
{
	UINT32	ADEN			: 1;			/**< Bit0，ADC使能控制 */
	UINT32	ADDIS			: 1;			/**< Bit1，ADC禁止控制 */
	UINT32	ADSTART			: 1;			/**< Bit2，ADC开始定期转换 */
	UINT32	JADSTART		: 1;			/**< Bit3，ADC快速注入转换 */
	UINT32	ADSTP			: 1;			/**< Bit4，ADC停止定期转换控制 */
	UINT32	JADSTP			: 1;			/**< Bit5，ADC停止注入转换控制 */
	UINT32	Rsvd1			: 22;			/**< Bit6~27，保留 */
	UINT32	ADVREGEN		: 2;			/**< Bit28~29，ADC电压调节器使能 */
	UINT32	ADCALDIF		: 1;			/**< Bit30，微分模式校准 */
	UINT32	ADCAL			: 1;			/**< Bit31，ADC校准 */
}AdcCrBitType;

/** ADC 控制寄存器定义 */
typedef union
{
	UINT32	all;
	AdcCrBitType	bit;
}AdcCrType;

/** ADC 配置寄存器位定义 */
typedef struct
{
	UINT32	DMAEN			: 1;			/**< Bit0，DMA使能 */
	UINT32	DMACFG			: 1;			/**< Bit1，DMA配置 */
	UINT32	Rsvd1			: 1;			/**< Bit2，保留 */
	UINT32	RES				: 2;			/**< Bit3~4，数据分辨率 */
	UINT32	ALIGN			: 1;			/**< Bit5，数据对齐 */
	UINT32	EXTSEL			: 4;			/**< Bit6~9，为规则组选择外部触发 */
	UINT32	EXTEN			: 2;			/**< Bit10~11，外部触发使能，并且为常规通道选择极性 */
	UINT32	OVRMOD			: 1;			/**< Bit12，超时模式 */
	UINT32	CONT			: 1;			/**< Bit13，对定期转换的单个转换模式或连续转换模式 */
	UINT32	AUTDLY			: 1;			/**< Bit14，延时转换模式 */
	UINT32	Rsvd2			: 1;			/**< Bit15，保留 */
	UINT32	DISCEN			: 1;			/**< Bit16，常规通道间断模式 */
	UINT32	DISCNUM			: 3;			/**< Bit17~19，通道计数间断模式 */
	UINT32	JDISCEN			: 1;			/**< Bit20，注入通道间断模式 */
	UINT32	JQM				: 1;			/**< Bit21，JSQR队列模式 */
	UINT32	AWD1SGL			: 1;			/**< Bit22，在单通道或所有通道使能看门狗1 */
	UINT32	AWD1EN			: 1;			/**< Bit23，在常规通道使能模拟量看门狗1 */
	UINT32	JAWD1EN			: 1;			/**< Bit24，注入通道使能模拟量看门狗1 */
	UINT32	JAUTO			: 1;			/**< Bit25，自动注入组转换 */
	UINT32	AWD1CH			: 5;			/**< Bit26~30，模拟量看门狗通道选择 */
	UINT32	Rsvd3			: 1;			/**< Bit31，保留 */
}AdcCfgrBitType;

/** ADC 配置寄存器定义 */
typedef union
{
	UINT32	all;
	AdcCfgrBitType	bit;
}AdcCfgrType;

/** ADC采样时间寄存器1位定义 */
typedef struct
{
	UINT32	Rsvd1		:	3;		/**< Bit0~2，  保留 */
	UINT32	SMP1		:	3;		/**< Bit3~5，  通道1采样时间选择 */
	UINT32	SMP2		:	3;		/**< Bit6~8，  通道2采样时间选择 */
	UINT32	SMP3		:	3;		/**< Bit9~11， 通道3采样时间选择 */
	UINT32	SMP4		:	3;		/**< Bit12~14，通道4采样时间选择 */
	UINT32	SMP5		:	3;		/**< Bit15~17，通道5采样时间选择 */
	UINT32	SMP6		:	3;		/**< Bit18~20，通道6采样时间选择 */
	UINT32	SMP7		:	3;		/**< Bit21~23，通道7采样时间选择 */
	UINT32	SMP8		:	3;		/**< Bit24~26，通道8采样时间选择 */
	UINT32	SMP9		:	3;		/**< Bit27~29，通道9采样时间选择 */
	UINT32	Rsvd2		:   2;		/**< Bit30~31，保留 */
}AdcSmpr1BitType;

/** ADC采样数据寄存器1定义 */
typedef union
{
	UINT32	all;
	AdcSmpr1BitType	bit;
}AdcSmpr1Type;

/** ADC采样时间寄存器2位定义 */
typedef struct
{
	UINT32	SMP10		:	3;		/**< Bit0~2，  通道10采样时间选择 */
	UINT32	SMP11		:	3;		/**< Bit3~5，  通道11采样时间选择 */
	UINT32	SMP12		:	3;		/**< Bit6~8，  通道12采样时间选择 */
	UINT32	SMP13		:	3;		/**< Bit9~11， 通道13采样时间选择 */
	UINT32	SMP14		:	3;		/**< Bit12~14，通道14采样时间选择 */
	UINT32	SMP15		:	3;		/**< Bit15~17，通道15采样时间选择 */
	UINT32	SMP16		:	3;		/**< Bit18~20，通道16采样时间选择 */
	UINT32	SMP17		:	3;		/**< Bit21~23，通道17采样时间选择 */
	UINT32	SMP18		:	3;		/**< Bit24~26，通道18采样时间选择 */
	UINT32	Rsvd2		: 2;		/**< Bit27~31，保留 */
}AdcSmpr2BitType;

/** ADC采样数据寄存器2定义 */
typedef union
{
	UINT32	all;
	AdcSmpr2BitType	bit;
}AdcSmpr2Type;

/** 看门狗阈值寄存器1位定义 */
typedef struct
{
	UINT32	LT1		: 12;			/**< Bit0~11，模拟量看门狗1阈值低部分 */
	UINT32	Rsvd1	: 4;			/**< Bit12~15，保留 */
	UINT32	HT1		: 12;			/**< Bit16~27，模拟量看门狗1阈值高部分 */
	UINT32	Rsvd2	: 4;			/**< Bit28~31，保留 */
}AdcTr1BitType;

/** 看门狗阈值寄存器1定义 */
typedef union
{
	UINT32	all;
	AdcTr1BitType		bit;
}AdcTr1Type;

/** 看门狗阈值寄存器2位定义 */
typedef struct
{
	UINT32	LT2		: 8;			/**< Bit0~7，模拟量看门狗2阈值低部分 */
	UINT32	Rsvd1	: 8;			/**< Bit8~15，保留 */
	UINT32	HT2		: 8;			/**< Bit16~23，模拟量看门狗2阈值高部分 */
	UINT32	Rsvd2	: 8;			/**< Bit24~31，保留 */
}AdcTr2BitType;

/** 看门狗阈值寄存器2定义 */
typedef union
{
	UINT32	all;
	AdcTr2BitType		bit;
}AdcTr2Type;

/** 看门狗阈值寄存器3位定义 */
typedef struct
{
	UINT32	LT3		: 8;			/**< Bit0~7，模拟量看门狗3阈值低部分 */
	UINT32	Rsvd1	: 8;			/**< Bit8~15，保留 */
	UINT32	HT3		: 8;			/**< Bit16~23，模拟量看门狗3阈值高部分 */
	UINT32	Rsvd2	: 8;			/**< Bit24~31，保留 */
}AdcTr3BitType;

/** 看门狗阈值寄存器3定义 */
typedef union
{
	UINT32	all;
	AdcTr3BitType		bit;
}AdcTr3Type;

/** 常规序列寄存器1位定义 */
typedef struct
{
	UINT32	L		: 4;			/**< Bit0~3，常规通道序列长度 */
	UINT32	Rsvd1	: 2;			/**< Bit4~5，保留 */
	UINT32	SQ1		: 5;			/**< Bit6~10，第一个转换的常规通道 */
	UINT32	Rsvd2	: 1;			/**< Bit11，保留 */
	UINT32	SQ2		: 5;			/**< Bit12~16，第二个转换的常规通道 */
	UINT32	RsvD3	: 1;			/**< Bit17，保留 */
	UINT32	SQ3		: 5;			/**< Bit18~22，第三个转换的常规通道 */
	UINT32	Rsvd4	: 1;			/**< Bit23，保留 */
	UINT32	SQ4		: 5;			/**< Bit24~28，第四个转换的常规通道 */
	UINT32	Rsvd5	: 3;			/**< Bit29~31，保留 */
}AdcSqr1BitType;

/** 常规序列寄存器1定义 */
typedef union
{
	UINT32	all;
	AdcSqr1BitType	bit;
}AdcSqr1Type;

/** 常规序列寄存器2位定义 */
typedef struct
{
	UINT32	SQ5		: 4;			/**< Bit0~4，第5个转换的常规通道 */
	UINT32	Rsvd1	: 2;			/**< Bit5，保留 */
	UINT32	SQ6		: 5;			/**< Bit6~10，第6个转换的常规通道 */
	UINT32	Rsvd2	: 1;			/**< Bit11，保留 */
	UINT32	SQ7		: 5;			/**< Bit12~16，第7个转换的常规通道 */
	UINT32	RsvD3	: 1;			/**< Bit17，保留 */
	UINT32	SQ8		: 5;			/**< Bit18~22，第8个转换的常规通道 */
	UINT32	Rsvd4	: 1;			/**< Bit23，保留 */
	UINT32	SQ9		: 5;			/**< Bit24~28，第9个转换的常规通道 */
	UINT32	Rsvd5	: 3;			/**< Bit29~31，保留 */
}AdcSqr2BitType;

/** 常规序列寄存器2定义 */
typedef union
{
	UINT32	all;
	AdcSqr2BitType	bit;
}AdcSqr2Type;

/** 常规序列寄存器3位定义 */
typedef struct
{
	UINT32	SQ10	: 4;			/**< Bit0~4，第10个转换的常规通道 */
	UINT32	Rsvd1	: 2;			/**< Bit5，保留 */
	UINT32	SQ11	: 5;			/**< Bit6~10，第11个转换的常规通道 */
	UINT32	Rsvd2	: 1;			/**< Bit11，保留 */
	UINT32	SQ12	: 5;			/**< Bit12~16，第12个转换的常规通道 */
	UINT32	RsvD3	: 1;			/**< Bit17，保留 */
	UINT32	SQ13	: 5;			/**< Bit18~22，第13个转换的常规通道 */
	UINT32	Rsvd4	: 1;			/**< Bit23，保留 */
	UINT32	SQ14	: 5;			/**< Bit24~28，第14个转换的常规通道 */
	UINT32	Rsvd5	: 3;			/**< Bit29~31，保留 */
}AdcSqr3BitType;

/** 常规序列寄存器3定义 */
typedef union
{
	UINT32	all;
	AdcSqr3BitType	bit;
}AdcSqr3Type;

/** 常规序列寄存器4位定义 */
typedef struct
{
	UINT32	SQ15	: 4;			/**< Bit0~4，第15个转换的常规通道 */
	UINT32	Rsvd1	: 2;			/**< Bit5，保留 */
	UINT32	SQ16	: 5;			/**< Bit6~10，第16个转换的常规通道 */
	UINT32	Rsvd2	: 21;			/**< Bit11~31，保留 */
}AdcSqr4BitType;

/** 常规序列寄存器4定义 */
typedef union
{
	UINT32	all;
	AdcSqr4BitType	bit;
}AdcSqr4Type;

/** 注入次序寄存器位定义 */
typedef struct
{
	UINT32	JL				: 2;		/**< Bit0~1，注入通道次序长度 */
	UINT32	JEXTSEL		: 4;		/**< Bit2~5，注入组外部触发选择 */
	UINT32	JEXTEN		: 2;		/**< Bit6~7，注入通道外部触发使能和极性选择 */
	UINT32	JSQ1			: 5;		/**< Bit8~12，注入顺序中的第一个转换通道 */
	UINT32	Rsvd1			: 1;		/**< Bit13，保留 */
	UINT32	JSQ2			: 5;		/**< Bit14~18，注入顺序中的第二个转换通道 */
	UINT32	Rsvd2			: 1;		/**< Bit19，保留 */
	UINT32	JSQ3			: 5;		/**< Bit20~24，注入顺序中的第三个转换通道 */
	UINT32	Rsvd3			: 1;		/**< Bit25，保留 */
	UINT32	JSQ4			: 5;		/**< Bit26~30，注入顺序中的第四个转换通道 */
	UINT32	Rsvd4			: 1;		/**< Bit31，保留 */
}AdcJsqrBitType;

/** 注入次序寄存器定义 */
typedef union
{
	UINT32	all;
	AdcJsqrBitType	bit;
}AdcJsqrType;

/** 偏移寄存器位定义 */
typedef struct
{
	UINT32	OFFSET			: 12;			/**< Bit0~11，通道数据偏移y被写进OFFSETy_CH[4：0] */
	UINT32	Rsvd1			: 14;			/**< Bit12~25，保留 */
	UINT32	OFFSET_CH		: 5;			/**< Bit26~30，选择的通道数据偏移y */
	UINT32	OFFSET_EN		: 1;			/**< Bit31，偏移y使能 */
}AdcOfrBitType;

/** 偏移寄存器定义 */
typedef union
{
	UINT32	all;
	AdcOfrBitType		bit;
}AdcOfrType;

/** 模拟量看门狗2配置寄存器位定义 */
typedef struct
{
	UINT32	Rsvd1			: 1;		/**< Bit0，保留 */
	UINT32	AWD2CH			: 18;		/**< Bit1~18，模拟量看门狗2通道选择 */
	UINT32	Rsvd2			: 13;		/**< Bit19~31，保留 */
}AdcAwd2crBitType;

/** 模拟量看门狗2配置寄存器定义 */
typedef union
{
	UINT32	all;
	AdcAwd2crBitType	bit;
}AdcAwd2crType;

/** 模拟量看门狗3配置寄存器位定义 */
typedef struct
{
	UINT32	Rsvd1			: 1;		/**< Bit0，保留 */
	UINT32	AWD3CH			: 18;		/**< Bit1~18，模拟量看门狗3通道选择 */
	UINT32	Rsvd2			: 13;		/**< Bit19~31，保留 */
}AdcAwd3crBitType;

/** 模拟量看门狗3配置寄存器定义 */
typedef union
{
	UINT32	all;
	AdcAwd3crBitType	bit;
}AdcAwd3crType;

/** ADC微分模式选择寄存器位定义 */
typedef struct
{
	UINT32 Rsvd1	: 1;		/**< Bit0，保留 */
	UINT32 DIFSEL	: 18		/**< Bit1~18，通道差分模式 */;
	UINT32 Rsvd2	: 13;		/**< Bit19~31，保留 */
}AdcDifselBitType;

/** ADC差分模式选择寄存器定义 */
typedef union
{
	UINT32	all;
	AdcDifselBitType	bit;
}AdcDifselType;

/** ADC校准因子位定义 */
typedef struct
{
	UINT32	CALFACT_S		: 7;			/**< Bit0~6，单端模式校准因子 */
	UINT32	Rsvd1				: 9;			/**< Bit7~15，保留 */
	UINT32	CALFACT_D		: 7;			/**< Bit16~22，差分模式校准因子 */
	UINT32	Rsvd2				: 9;			/**< Bit23~31，保留 */
}AdcCalfactBitType;

/** ADC校准因子定义 */
typedef union
{
	UINT32	all;
	AdcCalfactBitType		bit;
}AdcCalfactType;

/** ADC共同状态寄存器位定义 */
typedef struct
{
	UINT32	ADRDY_MST		: 1;			/**< Bit0，主ADC就绪 */
	UINT32	EOSMP_MST		: 1;			/**< Bit1，主ADC采样相位结束标志 */
	UINT32	EOC_MST			: 1;			/**< Bit2，主ADC定期转换结束 */
	UINT32	EOS_MST			: 1;			/**< Bit3，主ADC定期顺序结束标志 */
	UINT32	OVR_MST			: 1;			/**< Bit4，主ADC超时标志 */
	UINT32	JEOC_MST		: 1;			/**< Bit5，主ADC注入转换结束标志 */
	UINT32	JEOS_MST		: 1;			/**< Bit6，主ADC注入顺序结束标志 */
	UINT32	AWD1_MST		: 1;			/**< Bit7，主ADC模拟量看门狗1标志 */
	UINT32	AWD2_MST		: 1;			/**< Bit8，主ADC模拟量看门狗2标志 */
	UINT32	AWD3_MST		: 1;			/**< Bit9，主ADC模拟量看门狗3标志 */
	UINT32	JQOVF_MST		: 1;			/**< Bit10，主ADC注入队列溢出标志 */
	UINT32	Rsvd1			: 5;			/**< Bit11~15，保留 */
	UINT32	ADRDY_SLV		: 1;			/**< Bit16，从ADC就绪 */
	UINT32	EOSMP_SLV		: 1;			/**< Bit17，从ADC采样相位结束标志 */
	UINT32	EOC_SLV			: 1;			/**< Bit18，从ADC定期转换结束 */
	UINT32	EOS_SLV			: 1;			/**< Bit19，从ADC定期顺序结束标志 */
	UINT32	OVR_SLV			: 1;			/**< Bit20，从ADC超时标志 */
	UINT32	JEOC_SLV		: 1;			/**< Bit21，从ADC注入转换结束标志 */
	UINT32	JEOS_SLV		: 1;			/**< Bit22，从ADC注入顺序结束标志 */
	UINT32	AWD1_SLV		: 1;			/**< Bit23，从ADC模拟量看门狗1标志 */
	UINT32	AWD2_SLV		: 1;			/**< Bit24，从ADC模拟量看门狗2标志 */
	UINT32	AWD3_SLV		: 1;			/**< Bit25，从ADC模拟量看门狗3标志 */
	UINT32	JQOVF_SLV		: 1;			/**< Bit26，从ADC注入队列溢出标志 */
	UINT32	Rsvd2			: 5;			/**< Bit27~31，保留 */
}AdcCsrBitType;

/** ADC共同状态寄存器定义 */
typedef union
{
	UINT32	all;
	AdcCsrBitType		bit;
}AdcCsrType;

/** ADC共同控制寄存器位定义 */
typedef struct
{
	UINT32	DUAL		: 5;		/**< Bit0~4，双ADC模式选择 */
	UINT32	Rsvd1		: 3;		/**< Bit5~7，保留 */
	UINT32	DELAY		: 4;		/**< Bit8~11，2个采样相位之间的延时 */
	UINT32	Rsvd2		: 1;		/**< Bit12，保留 */
	UINT32	DMACFG		: 1;		/**< Bit13，双ADC模式时DMA配置 */
	UINT32	MDMA		: 2;		/**< Bit14~15，双ADC模式时的DMA模式 */
	UINT32	CKMODE		: 2;		/**< Bit16~17，ADC时钟模式 */
	UINT32	Rscd3		: 4;		/**< Bit18~21，保留 */
	UINT32	VREFEN		: 1;		/**< Bit22，Vrefint使能 */
	UINT32	TSEN		: 1;		/**< Bit23，温度传感器使能 */
	UINT32	VBATEN		: 1;		/**< Bit24，Vbat使能 */
	UINT32	Rsvd4		: 7;		/**< Bit25~31，保留 */
}AdcCcrBitType;

/** ADC共同控制寄存器定义 */
typedef union
{
	UINT32	all;
	AdcCcrBitType		bit;
}AdcCcrType;

/** ADC共有的双路模式常规数据寄存器位定义 */
typedef struct
{
	UINT32 RDATA_MST		: 16;			/**< Bit0~15，主ADC常规数据 */
	UINT32 RDATA_SLV		: 16;			/**< Bit16~31，从ADC常规数据 */
}AdcCdrBitType;

/** ADC共有的双路模式常规数据寄存器定义 */
typedef union
{
	UINT32	all;
	AdcCdrBitType		bit;
}AdcCdrType;

/** ADC寄存器 */
typedef struct
{
	AdcIsrType			ISR;				/**< ADC中断和状态寄存器 ，偏移地址 0x00*/
	AdcIerType			IER;				/**< ADC中断使能寄存器 ，偏移地址0x04 */
	AdcCrType			CR;					/**< ADC地址寄存器 ，偏移地址 0x08*/
	AdcCfgrType			CFGR;				/**< ADC配置寄存器 ，偏移地址 0x0c*/
	UINT32				Rsvd1;				/**< 保留 ，偏移地址 0x10*/
	AdcSmpr1Type		SMPR1;				/**< ADC采样时间寄存器1 ，偏移地址 0x14*/
	AdcSmpr2Type		SMPR2;				/**< ADC采样时间寄存器2 ，偏移地址 0x18*/
	UINT32				Rsvd2;				/**< 保留 ，偏移地址 0x1c*/
	AdcTr1Type			TR1;				/**< 看门狗阈值寄存器1 ，偏移地址 0x20*/
	AdcTr2Type			TR2;				/**< 看门狗阈值寄存器2 ，偏移地址 0x24*/
	AdcTr3Type			TR3;				/**< 看门狗阈值寄存器3 ，偏移地址 0x28*/
	UINT32				Rsvd3;				/**< 保留 ，偏移地址 0x2c*/
	AdcSqr1Type			SQR1;				/**< ADC常规顺序寄存器1 ，偏移地址 0x30*/
	AdcSqr2Type			SQR2;				/**< ADC常规顺序寄存器2 ，偏移地址 0x34*/
	AdcSqr3Type			SQR3;				/**< ADC常规顺序寄存器3 ，偏移地址 0x38*/
	AdcSqr4Type			SQR4;				/**< ADC常规顺序寄存器4 ，偏移地址 0x3c*/
	UINT16				DR;					/**< ADC常规数据寄存器 ，偏移地址 0x40*/
	UINT16				Rsvd4;				
	UINT32				Rsvd5;				/**< 保留 ，偏移地址 0x44~0x48*/
	UINT32				Rsvd6;				
	AdcJsqrType			JSQR;				/**< ADC注入顺序寄存器 ，偏移地址 0x4c*/
	UINT32				Rsvd7;				/**< 保留 ，偏移地址 0x50~0x5c*/
	UINT32				Rsvd8;				
	UINT32				Rsvd9;				
	UINT32				Rsvd10;				
	AdcOfrType			OFR1;				/**< ADC偏移寄存器1 ，偏移地址 0x60*/
	AdcOfrType			OFR2;				/**< ADC偏移寄存器2 ，偏移地址 0x64*/
	AdcOfrType			OFR3;				/**< ADC偏移寄存器3 ，偏移地址 0x68*/
	AdcOfrType			OFR4;				/**< ADC偏移寄存器4 ，偏移地址 0x6c*/
	UINT32				Rsvd11;				/**< 保留 ，偏移地址 0x70~0x7c*/
	UINT32				Rsvd12;				
	UINT32				Rsvd13;				
	UINT32				Rsvd14;				
	UINT16				JDR1;				/**< ADC注入数据寄存器1 ，偏移地址 0x80*/
	UINT16				Rsvd15;				
	UINT16				JDR2;				/**< ADC注入数据寄存器2 ，偏移地址 0x84*/
	UINT16				Rsvd16;				
	UINT16				JDR3;				/**< ADC注入数据寄存器3 ，偏移地址 0x88*/
	UINT16				Rsvd17;				
	UINT16				JDR4;				/**< ADC注入数据寄存器4 ，偏移地址 0x8c*/
	UINT16				Rsvd18;				
	UINT32				Rsvd19;				/**< 保留 ，偏移地址 0x90~0x9c*/
	UINT32				Rsvd20;				
	UINT32				Rsvd21;				
	UINT32				Rsvd22;				
	UINT16				AWD2CR;				/**< ADC模拟量看门狗2配置寄存器 ，偏移地址 0xa0*/
	UINT16				Rsvd23;				
	UINT16				AWD3CR;				/**< ADC模拟量看门狗3配置寄存器 ，偏移地址 0xa4*/
	UINT16				Rsvd24;				
	UINT32				Rsvd25;				/**< 保留 ，偏移地址 0xa8~0xac*/
	UINT32				Rsvd26;				
	UINT16				DIFSEL;				/**< ADC差分模式选择寄存器 ，偏移地址 0xb0*/
	UINT16				Rsvd27;				
	AdcCalfactType	CALFACT;				/**< ADC校准因子寄存器 ， 偏移地址 0xb4 */
}AdcType;


/** ADC共同寄存器 */
typedef struct
{
	AdcCsrType		CSR;			/**< ADC共同状态寄存器，偏移地址0x00 */
	UINT32			Rsvd1;			/**< 保留，偏移地址 0x04 */
	AdcCcrType		CCR;			/**< ADC共同控制寄存器，偏移地址0x08 */
	AdcCdrType		CDR;			/**< ADC双路模式共同常规数据寄存器，偏移地址0x0c */
}AdcCommonType;



/** ADC 模块定义 */
#define ADC1		((AdcType	*) ADC1_BASE)
#define ADC2		((AdcType	*) ADC2_BASE)
#define ADC3		((AdcType	*) ADC3_BASE)
#define ADC4		((AdcType	*) ADC4_BASE)

#define	ADC1_2	((AdcCommonType	*) ADC1_2_BASE)
#define	ADC3_4	((AdcCommonType	*) ADC3_4_BASE)


#endif
