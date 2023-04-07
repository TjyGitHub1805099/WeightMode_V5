/**
  *******************************************************************
  * @file    reg_stm32f303_timer.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-21
  * @brief   STM32F303	定时器寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef	__REG_STM32F303_TIMER_H__
#define	__REG_STM32F303_TIMER_H__


#include "reg_stm32f303_address.h"


/** 定时器控制寄存器1位定义 */
typedef struct
{
	UINT32	CEN				: 1;		/**< Bit0，计数器使能 */
	UINT32	UDIS			: 1;		/**< Bit1，更新禁止 */
	UINT32	URS				: 1;		/**< Bit2，更新请求源 */
	UINT32	OPM				: 1;		/**< Bit3，一个脉冲模式 */
	UINT32	DIR				: 1;		/**< Bit4，计数器方向 */
	UINT32	CMS				: 2;		/**< Bit5~6，中央对齐模式选择 */
	UINT32	ARPE			: 1;		/**< Bit7，自动重装载使能 */
	UINT32	CKD				: 2;		/**< Bit8~9，时钟分频 */
	UINT32	Rsvd1			: 1;		/**< Bit10，保留 */
	UINT32	UIFREMAP	    : 1;		/**< Bit11，UIF状态位重映射 */
	UINT32	Rsvd2			: 20;		/**< Bit12~31，保留 */
}TimerCr1BitType;

/** 定时器控制寄存器1定义 */
typedef union
{
	UINT32	all;
	TimerCr1BitType		bit;
}TimerCr1Type;

/** 定时器控制寄存器2位定义 */
typedef struct
{
	UINT32	CCPC		: 1;		/**< Bit0，捕获/比较预装载控制 */
	UINT32	Rsvd1		: 1;		/**< Bit1，保留 */
	UINT32	CCUS		: 1;		/**< Bit2， 捕获/比较控制更新选择 */
	UINT32	CCDS		: 1;		/**< Bit3，捕获/比较DMA选择 */
	UINT32	MMS			: 3;		/**< Bit4~6，主机模式选择 */
	UINT32	TI1S		: 1;		/**< Bit7，TI1选择 */
	UINT32	OIS1		: 1;		/**< Bit8，输出空闲状态1（OC1输出） */
	UINT32	OIS1N		: 1;		/**< Bit9，输出空闲状态1（OC1N输出） */
	UINT32	OIS2		: 1;		/**< Bit10，输出空闲状态2（OC2输出） */
	UINT32	OIS2N		: 1;		/**< Bit11，输出空闲状态2（OC2N输出） */
	UINT32	OIS3		: 1;		/**< Bit12，输出空闲状态3（OC3输出） */
	UINT32	OIS3N		: 1;		/**< Bit13，输出空闲状态3（OC3N输出） */
	UINT32	OIS4		: 1;		/**< Bit14，输出空闲状态4（OC4输出） */
	UINT32	Rsvd2		: 1;		/**< Bit15，保留 */
	UINT32	OIS5		: 1;		/**< Bit16，输出空闲状态5（OC5输出） */
	UINT32	Rsvd3		: 1;		/**< Bit17，保留 */
	UINT32	OIS6		: 1;		/**< Bit18，输出空闲状态6（OC6输出） */
	UINT32	Rsvd4		: 1;		/**< Bit19，保留 */
	UINT32	MMS2		: 4;		/**< Bit20~23，主机模式选择 */
	UINT32	Rsvd5		: 8;		/**< Bit23~31，保留 */
}TimerCr2BitType;

/** 定时器控制寄存器2定义 */
typedef union
{
	UINT32	all;
	TimerCr2BitType		bit;
}TimerCr2Type;

/** 定时器从机模式控制寄存器位定义 */
typedef struct
{
	UINT32	SMS		: 3;		/**< Bit0~2，从机模式选择 */
	UINT32	OCCS	: 1;		/**< Bit3，OCREF清除选择 */
	UINT32	TS		: 3;		/**< Bit4~6，触发选择 */
	UINT32	MSM		: 1;		/**< Bit7，主机/从机模式 */
	UINT32	ETF		: 4;		/**< Bit8~11，外部触发过滤器 */
	UINT32	ETPS	: 2;		/**< Bit12~13，外部触发分频 */
	UINT32	ECE		: 1;		/**< Bit14，外部时钟使能 */
	UINT32	ETP		: 1;		/**< Bit15，外部触发极性 */
	UINT32	SMS_3	: 1;		/**< Bit16，从机模式选择bit3 */
	UINT32	Rsvd1	: 15;		/**< Bit17~31，保留 */
}TimerSmcrBitType;

/** 定时器从机模式控制寄存器定义 */
typedef union
{
	UINT32	all;
	TimerSmcrBitType	bit;
}TimerSmcrType;

/** DMA/中断使能寄存器位定义 */
typedef struct
{
	UINT32	UIE		: 1;		/**< Bit0，更新中断使能 */
	UINT32	CC1IE	: 1;		/**< Bit1，捕获/比较1中断使能 */
	UINT32	CC2IE	: 1;		/**< Bit2，捕获/比较2中断使能 */
	UINT32	CC3IE	: 1;		/**< Bit3，捕获/比较3中断使能 */
	UINT32	CC4IE	: 1;		/**< Bit4，捕获/比较4中断使能 */
	UINT32	COMIE	: 1;		/**< Bit5，COM中断使能 */
	UINT32	TIE		: 1;		/**< Bit6，触发中断使能 */
	UINT32	BIE		: 1;		/**< Bit7，断开中断使能 */
	UINT32	UDE		: 1;		/**< Bit8，更新DMA请求使能 */
	UINT32	CC1DE	: 1;		/**< Bit9，捕获/比较1 DMA请求使能 */
	UINT32	CC2DE	: 1;		/**< Bit10，捕获/比较2 DMA请求使能 */
	UINT32	CC3DE	: 1;		/**< Bit11，捕获/比较3 DMA请求使能 */
	UINT32	CC4DE	: 1;		/**< Bit12，捕获/比较4 DMA请求使能 */
	UINT32	COMDE	: 1;		/**< Bit13，COM DMA请求使能 */
	UINT32	TDE		: 1;		/**< Bit14，触发DMA请求使能 */
	UINT32	Rsvd1	: 17;		/**< Bit15~31，保留 */
}TimerDierBitType;

/** DMA/中断使能寄存器定义 */
typedef union
{
	UINT32	all;
	TimerDierBitType	bit;
}TimerDierType;

/** 状态寄存器位定义 */
typedef struct
{
	UINT32	UIF		: 1;		/**< Bit0，更新中断标志 */
	UINT32	CC1IF	: 1;		/**< Bit1，捕获/比较1中断标志 */
	UINT32	CC2IF	: 1;		/**< Bit2，捕获/比较2中断标志 */
	UINT32	CC3IF	: 1;		/**< Bit3，捕获/比较3中断标志 */
	UINT32	CC4IF	: 1;		/**< Bit4，捕获/比较4中断标志 */
	UINT32	COMIF	: 1;		/**< Bit5，COM中断标志 */
	UINT32	TIF		: 1;		/**< Bit6，触发中断标志 */
	UINT32	BIT		: 1;		/**< Bit7，断开中断标志 */
	UINT32	B2IF	: 1;		/**< Bit8，断开2中断标志 */
	UINT32	CC1OF	: 1;		/**< Bit9，捕获/比较1过捕获标志 */
	UINT32	CC2OF	: 1;		/**< Bit10，捕获/比较2过捕获标志 */
	UINT32	CC3OF	: 1;		/**< Bit11，捕获/比较3过捕获标志 */
	UINT32	CC4OF	: 1;		/**< Bit12，捕获/比较4过捕获标志 */
	UINT32	Rsvd1	: 3;		/**< Bit13~15，保留 */
	UINT32	CC5IF	: 1;		/**< Bit16，比较5中断标志 */
	UINT32	CC6IF	: 1;		/**< Bit17，比较6中断标志 */
	UINT32	Rsvd2	: 14;		/**< Bit18~31，保留 */
}TimerSrBitType;

/** 状态寄存器定义 */
typedef union
{
	UINT32	all;
	TimerSrBitType	bit;
}TimerSrType;

/** 事件产生寄存器位定义 */
typedef struct
{
	UINT32	UG		: 1;		/**< Bit0，更新事件产生 */
	UINT32	CC1G	: 1;		/**< Bit1，捕获/比较1事件产生 */
	UINT32	CC2G	: 1;		/**< Bit2，捕获/比较2事件产生 */
	UINT32	CC3G	: 1;		/**< Bit3，捕获/比较3事件产生 */
	UINT32	CC4G	: 1;		/**< Bit4，捕获/比较4事件产生 */
	UINT32	COMG	: 1;		/**< Bit5，捕获/比较控制更新事件产生 */
	UINT32	TG		: 1;		/**< Bit6，触发事件产生 */
	UINT32	BG		: 1;		/**< Bit7，断开事件产生 */
	UINT32	B2G		: 1;		/**< Bit8，断开2事件产生 */
	UINT32	Rsvd1	: 23;		/**< Bit9~31，保留 */
}TimerEgrBitType;

/** 事件产生寄存器定义 */
typedef union
{
	UINT32	all;
	TimerEgrBitType		bit;
}TimerEgrType;

/** 捕获/比较模式寄存器1作为输出比较模式位定义 */
typedef	struct
{
	UINT32	CC1S		: 2;		/**< Bit0~1，捕获/比较1选择 */
	UINT32	OC1FE		: 1;		/**< Bit2，输出比较1快速使能 */
	UINT32	OC1PE		: 1;		/**< Bit3，输出比较1预装载使能 */
	UINT32	OC1M		: 3;		/**< Bit4~6，输出比较1模式 */
	UINT32	OC1CE		: 1;		/**< Bit7，输出比较1清除使能 */
	UINT32	CC2S		: 2;		/**< Bit8~9，捕获/比较2选择 */
	UINT32	OC2FE		: 1;		/**< Bit10，输出比较2快速使能 */
	UINT32	OC2PE		: 1;		/**< Bit11，输出比较2预装载使能 */
	UINT32	OC2M		: 3;		/**< Bit12~14，输出比较2模式 */
	UINT32	OC2CE		: 1;		/**< Bit15，输出比较2清除使能 */
	UINT32	OC1M_3		: 1;		/**< Bit16，输出比较1模式bit3 */
	UINT32	Rsvd1		: 7;		/**< Bit17~23，保留 */
	UINT32	OC2M_3		: 1;		/**< Bit24，输出比较2模式bit3 */
	UINT32	Rsvd2		: 7;		/**< Bit25~31，保留 */
}TimerCcmr1BitType_Output;

/** 捕获/比较模式寄存器1作为输入捕获模式位定义 */
typedef struct
{
	UINT32	CC1S		: 2;		/**< Bit0~1，捕获/比较1选择 */
	UINT32	IC1PSC	: 2;		/**< Bit2~3，输入捕获1分频 */
	UINT32	IC1F		: 4;		/**< Bit4~7，输入捕获1过滤器 */
	UINT32	CC2S		: 2;		/**< Bit8~9，捕获/比较2选择 */
	UINT32	IC2PSC	: 2;		/**< Bit10~11，输入捕获2分频 */
	UINT32	IC2F		: 2;		/**< Bit12~15，输入捕获2过滤器 */
	UINT32	Rsvd1		: 16;		/**< Bit16~31，保留 */
}TimerCcmr1BitType_Input;

/** 捕获/比较模式寄存器1定义 */
typedef union
{
	UINT32	all;
	TimerCcmr1BitType_Output	bit_o;
	TimerCcmr1BitType_Input		bit_i;
}TimerCcmr1Type;

/** 捕获/比较模式寄存器2作为输出比较模式位定义 */
typedef struct
{
	UINT32	CC3S		: 2;		/**< Bit0~1，捕获/比较3选择 */
	UINT32	OC3FE		: 1;		/**< Bit2，输出比较3快速使能 */
	UINT32	OC3PE		: 1;		/**< Bit3，输出比较3预装载使能 */
	UINT32	OC3M		: 3;		/**< Bit4~6，输出比较3模式 */
	UINT32	OC3CE		: 1;		/**< Bit7，输出比较3清除使能 */
	UINT32	CC4S		: 2;		/**< Bit8~9，捕获/比较4选择 */
	UINT32	OC4FE		: 1;		/**< Bit10，输出比较4快速使能 */
	UINT32	OC4PE		: 1;		/**< Bit11，输出比较4预装载使能 */
	UINT32	OC4M		: 3;		/**< Bit12~14，输出比较4模式 */
	UINT32	OC4CE		: 1;		/**< Bit15，输出比较4清除使能 */
	UINT32	OC3M_3	: 1;		/**< Bit16，输出比较3模式bit3 */
	UINT32	Rsvd1		: 7;		/**< Bit17~23，保留 */
	UINT32	OC4M_3	: 1;		/**< Bit24，输出比较4模式bit3 */
	UINT32	Rsvd2		: 7;		/**< Bit25~31，保留 */
}TimerCcmr2BitType_Output;

/** 捕获/比较模式寄存器2作为输入捕获模式位定义 */
typedef struct
{
	UINT32	CC3S		: 2;		/**< Bit0~1，捕获/比较3选择 */
	UINT32	IC3PSC	: 2;		    /**< Bit2~3，输入捕获3分频 */
	UINT32	IC3F		: 4;		/**< Bit04~7，输入捕获3过滤器 */
	UINT32	CC4S		: 2;		/**< Bit8~9，捕获/比较4选择 */
	UINT32	IC4PSC	: 2;		    /**< Bit10~11，输入捕获4分频 */
	UINT32	IC4F		: 4;		/**< Bit12~15，输入捕获4过滤器 */
	UINT32	Rsvd1		: 16;		/**< Bit16~31，保留 */
}TimerCcmr2BitType_Input;

/** 捕获/比较模式寄存器2定义 */
typedef union
{
	UINT32	all;
	TimerCcmr2BitType_Output	bit_o;
	TimerCcmr2BitType_Input		bit_i;
}TimerCcmr2Type;

/** 捕获/比较使能寄存器位定义 */
typedef struct
{
	UINT32	CC1E		: 1;		/**< Bit0，捕获/比较1输出使能 */
	UINT32	CC1P		: 1;		/**< Bit1，捕获/比较1输出极性 */
	UINT32	CC1NE		: 1;		/**< Bit2，捕获/比较1互补输出使能 */
	UINT32	CC1NP		: 1;		/**< Bit3，捕获/比较1互补输出极性 */
	UINT32	CC2E		: 1;		/**< Bit4，捕获/比较2输出使能 */
	UINT32	CC2P		: 1;		/**< Bit5，捕获/比较2输出极性 */
	UINT32	CC2NE		: 1;		/**< Bit6，捕获/比较2互补输出使能 */
	UINT32	CC2NP		: 1;		/**< Bit7，捕获/比较2互补输出极性 */
	UINT32	CC3E		: 1;		/**< Bit8，捕获/比较3输出使能 */
	UINT32	CC3P		: 1;		/**< Bit9，捕获/比较3输出极性 */
	UINT32	CC3NE		: 1;		/**< Bit10，捕获/比较3互补输出使能 */
	UINT32	CC3NP		: 1;		/**< Bit11，捕获/比较3互补输出极性 */
	UINT32	CC4E		: 1;		/**< Bit12，捕获/比较4输出使能 */
	UINT32	CC4P		: 1;		/**< Bit13，捕获/比较4输出极性 */
	UINT32	Rsv1		: 1;		/**< Bit14，保留 */
	UINT32	CC4NP		: 1;		/**< Bit15，捕获/比较4互补输出极性 */
	UINT32	CC5E		: 1;		/**< Bit16，捕获/比较5输出使能 */
	UINT32	CC5P		: 1;		/**< Bit17，捕获/比较5输出极性 */
	UINT32	Rsvd2		: 2;		/**< Bit18~19，保留 */
	UINT32	CC6E		: 1;		/**< Bit20，捕获/比较6输出使能 */
	UINT32	CC6P		: 1;		/**< Bit21，捕获/比较6输出极性 */
	UINT32	Rsvd3		: 10;		/**< Bit22，保留 */
}TimerCcerBitType;

/** 捕获/比较使能寄存器定义 */
typedef union
{
	UINT32	all;
	TimerCcerBitType	bit;
}TimerCcerType;

/** 计数器位定义 */
typedef struct
{
	UINT32	CNT			: 16;			/**< Bit0~15，计数值 */
	UINT32	CNT_H		: 15;			/**< Bit16~30，计数值高部分（只在TIM2中才有，其他定时器此处是保留） */
	UINT32	UIFCPY	    : 1;			/**< Bit31，更新中断标志复制 */
}TimerCntBitType;

/** 计数器定义 */
typedef union
{
	UINT32	all;
	TimerCntBitType		bit;
}TimerCntType;

/** 断开和死区时间寄存器位定义 */
typedef struct
{
	UINT32	DTG		: 8;		/**< Bit0~7，死区时间发生器设置 */
	UINT32	LOCK	: 2;		/**< Bit8~9，锁定配置 */
	UINT32	OSSI	: 1;		/**< Bit10，空闲模式关断状态选择 */
	UINT32	OSSR	: 1;		/**< Bit11，运行模式关断状态选择 */
	UINT32	BKE		: 1;		/**< Bit12，断开使能 */
	UINT32	BKP		: 1;		/**< Bit13，断开极性 */
	UINT32	AOE		: 1;		/**< Bit14，中断输出使能 */
	UINT32	MOE		: 1;		/**< Bit15，主输出使能 */
	UINT32	BKF		: 4;		/**< Bit16~19，关断过滤器 */
	UINT32	BK2F	: 4;		/**< Bit20~23，关断2过滤器 */
	UINT32	BK2E	: 1;		/**< Bit24，关断2使能 */
	UINT32	BK2P	: 1;		/**< Bit25，关断2极性 */
	UINT32	Rsvd1	: 6;		/**< Bit26~31，保留 */
}TimerBdtrBitType;

/** 断开和死区时间寄存器定义 */
typedef union
{
	UINT32	all;
	TimerBdtrBitType	bit;
}TimerBdtrType;

/** DMA控制寄存器位定义 */
typedef struct
{
	UINT32 DBA		: 5;		/**< Bit0~4，DMA基本地址 */
	UINT32 Rsvd1	: 3;		/**< Bit5~7，保留 */
	UINT32 DBL		: 5;		/**< Bit8~12，DMA区间长度 */
	UINT32 Rsvd2	: 19;		/**< Bit13~31，保留 */
}TimerDcrBitType;

/** DMA控制寄存器定义 */
typedef union
{
	UINT32	all;
	TimerDcrBitType	bit;
}TimerDcrType;

/** 捕获/比较模式寄存器3位定义 */
typedef struct
{
	UINT32	Rsvd1		: 2;			/**< Bit0~1，保留 */
	UINT32	OC5FE		: 1;			/**< Bit2，输出比较5快速使能 */
	UINT32	OC5PE		: 1;			/**< Bit3，输出比较5预装载使能 */
	UINT32	OC5M		: 3;			/**< Bit4~6，输出比较5模式 */
	UINT32	OC5CE		: 1;			/**< Bit7，输出比较5清零使能 */
	UINT32	Rsvd2		: 2;			/**< Bit8~9，保留	*/
	UINT32	OC6FE		: 1;			/**< Bit10，输出比较6快速使能 */
	UINT32	OC6PE		: 1;			/**< Bit11，输出比较6预装载使能 */
	UINT32	OC6M		: 3;			/**< Bit12~14，输出比较6模式 */
	UINT32	OC6CE		: 1;			/**< Bit15，输出比较6清零使能 */
	UINT32	OC5M_3		: 1;			/**< Bit16，输出比较5模式bit3 */
	UINT32	Rsvd3		: 7;			/**< Bit17~23， 保留 */
	UINT32	OC6M_3		: 1;			/**< Bit24，输出比较6模式bit3 */
	UINT32	Rsvd4		: 7;			/**< Bit25~31，保留 */
}TimerCcmr3BitType;

/** 捕获/比较模式寄存器3定义 */
typedef union
{
	UINT32	all;
	TimerCcmr3BitType		bit;
}TimerCcmr3Type;

/** 捕获/比较寄存器5位定义 */
typedef struct
{
	UINT32	CCR5		: 16;			/**< Bit0~15，捕获/比较5值 */
	UINT32	Rsvd1		: 13;			/**< Bit16~28，保留 */
	UINT32	GC5C1		: 1;			/**< Bit29，组和通道5和通道1 */
	UINT32	GC5C2		: 1;			/**< Bit30，组合通道5和通道2 */
	UINT32	GC5C3		: 1;			/**< Bit31，组合通道5和通道3 */
}TimerCcr5BitType;

/** 捕获/比较寄存器5定义 */
typedef union
{
	UINT32	all;
	TimerCcr5BitType	bit;
}TimerCcr5Type;

/** 选项寄存器位定义 */
typedef struct
{
	UINT32 TIMx_ETR_ADCx_RMP1		: 2;		/**< Bit0~1，TIM1_ETR_ADC1_RMP , TIM8_ETR_ADC2_RMP , TIM20_ETR_ADC3_RMP	重映射能力 */
	UINT32 TIMx_ETR_ADCx_RMP2		: 2;		/**< Bit2~3，TIM1_ETR_ADC4_RMP , TIM8_ETR_ADC3_RMP , TIM20_ETR_ADC4_RMP	重映射能力 */
	UINT32 Rsvd1					: 28;		/**< Bit4~31，保留 */
}TimerOrBitType;

/** 选项寄存器定义 */
typedef union
{
	UINT32	all;
	TimerOrBitType	bit;
}TimerOrType;

/** 定时器寄存器 */
typedef struct
{
	TimerCr1Type		CR1;			/**< 偏移地址0x00 */
	TimerCr2Type		CR2;			/**< 偏移地址0x04 */
	TimerSmcrType		SMCR;			/**< 偏移地址0x08 */
	TimerDierType		DIER;			/**< 偏移地址0x0C */
	TimerSrType			SR;				/**< 偏移地址0x10 */
	TimerEgrType		EGR;			/**< 偏移地址0x14 */
	TimerCcmr1Type		CCMR1;			/**< 偏移地址0x18 */
	TimerCcmr2Type		CCMR2;			/**< 偏移地址0x1C */
	TimerCcerType		CCER;			/**< 偏移地址0x20 */
	TimerCntType		CNT;			/**< 偏移地址0x24 */
	UINT16				PSC;			/**< 偏移地址0x28 */
	UINT16				Rsvd2;		
	UINT32				ARR;			/**< 偏移地址0x2C */
	UINT16				RCR;			/**< 偏移地址0x30 */
	UINT16				Rsvd4;		
	UINT32				CCR1;			/**< 偏移地址0x34 */
	UINT32				CCR2;			/**< 偏移地址0x38 */
	UINT32				CCR3;			/**< 偏移地址0x3C */
	UINT32				CCR4;			/**< 偏移地址0x40 */
	TimerBdtrType		BDTR;			/**< 偏移地址0x44 */
	TimerDcrType		DCR;			/**< 偏移地址0x48 */
	UINT16				DMAR;			/**< 偏移地址0x4C */
	UINT16				Rsvd9;		
	TimerOrType			OR;				/**< 偏移地址0x50 ,此处和手册上定义顺序不同，只有TIM16的OR在此处，其他定时器OR地址为0x60，但库函数是这样写的，暂且这样写吧 */
	TimerCcmr3Type		CCMR3;			/**< 偏移地址0x54 */
	UINT16				CCR5;			/**< 偏移地址0x58 */
	UINT16				Rsvd10;		
	UINT16				CCR6;			/**< 偏移地址0x5C */
	UINT16				Rsvd11;		
}TimerType;


/** 定时器寄存器地址 */
#define	TIM1		((TimerType *) TIM1_BASE)		//高级定时器
#define	TIM2		((TimerType *) TIM2_BASE)
#define	TIM3		((TimerType *) TIM3_BASE)
#define	TIM4		((TimerType *) TIM4_BASE)
#define	TIM6		((TimerType *) TIM6_BASE)
#define	TIM7		((TimerType *) TIM7_BASE)
#define	TIM8		((TimerType *) TIM8_BASE)		//高级定时器
#define	TIM15		((TimerType *) TIM15_BASE)
#define	TIM16		((TimerType *) TIM16_BASE)
#define	TIM17		((TimerType *) TIM17_BASE)
#define	TIM20		((TimerType *) TIM20_BASE)		//高级定时器 D/E




#endif









