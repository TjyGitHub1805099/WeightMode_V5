/**
  *******************************************************************
  * @file    reg_stm32f303_uart.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-21
  * @brief   STM32F303	串口寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
	
#ifndef __REG_STM32F303_H__
#define	__REG_STM32F303_H__


/** 串口控制寄存器1位定义 */
typedef struct
{
	UINT32	UE				: 1;	/**< Bit0，串口使能 */
	UINT32	UEM				: 1;	/**< Bit1，串口使能在停止模式 */
	UINT32	RE				: 1;	/**< Bit2，串口接收使能 */
	UINT32	TE				: 1;	/**< Bit3，串口发送使能 */
	UINT32	IDLEIE			: 1;	/**< Bit4，串口idle中断使能 */
	UINT32	RXNEIE			: 1;	/**< Bit5，串口接收缓冲非空中断使能 */
	UINT32	TCIE			: 1;	/**< Bit6，串口发送完成中断使能 */
	UINT32	TXEIE			: 1;	/**< Bit7，串口发送缓冲空中断使能 */
	UINT32	PEIE			: 1;	/**< Bit8，串口奇偶校验错误中断使能 */
	UINT32	PARITY			: 2;	/**< Bit9，串口奇偶校 */
//	UINT32	PCE				: 1;	/**< Bit10，串口奇偶校验控制使能 */
	UINT32	WAKE			: 1;	/**< Bit11，串口接收唤醒使能 */
	UINT32	M0				: 1;	/**< Bit12，串口字长 */
	UINT32	MME				: 1;	/**< Bit13，串口静音模式使能 */
	UINT32	CMIE			: 1;	/**< Bit14，串口字符匹配中断使能 */
	UINT32	OVER8			: 1;	/**< Bit15，串口过采样模式 */
	UINT32	DEDT			: 5;	/**< Bit16~20，串口驱动使能de-assertion时间 */
	UINT32	DEAT			: 5;	/**< Bit21~25，串口驱动使能assertion时间 */
	UINT32	RTOIE			: 1;	/**< Bit26，串口接收超时中断使能 */
	UINT32	EOBIE			: 1;	/**< Bit27，串口块结束中断使能 */
	UINT32	M1				: 1;	/**< Bit28，串口字长 */
	UINT32	Rsvd1			: 3;	/**< 保留 */
}UsartCr1BitType;

/** 串口控制寄存器1定义 */
typedef union
{
	UINT32		all;
	UsartCr1BitType		bit;
}UsartCr1Type;

/** 串口控制寄存器2位定义 */
typedef struct
{
	UINT32		Rsvd1			: 4;		/**< Bit0~3，保留 */
	UINT32		ADDM7			: 1;		/**< Bit4，7位地址检测/4位地址检测 */
	UINT32		LBDL			: 1;		/**< Bit5，LIN断开检测长度 */
	UINT32		LBDIE			: 1;		/**< Bit6，LIN断开检测中断使能 */
	UINT32		Rsvd2			: 1;		/**< Bit7，保留 */
	UINT32		LBCL			: 1;		/**< Bit8，最后一位时钟脉冲 */
	UINT32		CPHA			: 1;		/**< Bit9，时钟脉冲 */
	UINT32		CPOL			: 1;		/**< Bit10，时钟极性 */
	UINT32		CLKEN			: 1;		/**< Bit11，时钟使能 */
	UINT32		STOP			: 2;		/**< Bit12~13，停止位 */
	UINT32		LINEN			: 1;		/**< Bit14，LIN模式使能 */
	UINT32		SWAP			: 1;		/**< Bit15，接收发送引脚交换 */
	UINT32		RXINV			: 1;		/**< Bit16，接收引脚激活级别倒置 */
	UINT32		TXINV			: 1;		/**< Bit17，发送引脚激活级别倒置 */
	UINT32		DATAINV			: 1;		/**< Bit18，二进制数据倒置 */
	UINT32		MSBFIRST		: 1;		/**< Bit19，数据高位在前 */
	UINT32		ABREN			: 1;		/**< Bit20，自动波特率使能 */
	UINT32		ABRMOD			: 2;		/**< Bit21~22，中断波特率模式 */
	UINT32		RTOEN			: 1;		/**< Bit23，接收超时使能 */
	UINT32		ADD1			: 4;		/**< Bit24~27，串口节点地址1 */
	UINT32		ADD2			: 4;		/**< Bit28~31，串口节点地址2 */
}UsartCr2BitType;

/** 串口控制寄存器2定义 */
typedef union
{
	UINT32	all;
	UsartCr2BitType		bit;
}UsartCr2Type;

/** 串口控制寄存器3位定义 */
typedef struct
{
	UINT32	EIE			: 1;		/**< Bit0，错误中断使能 */
	UINT32	IREN		: 1;		/**< Bit1，IrDA	模式使能 */
	UINT32	IRLP		: 1;		/**< Bit2，IrDA	低店模式 */
	UINT32	HDSEL		: 1;		/**< Bit3，半双工选择 */
	UINT32	NACK		: 1;		/**< Bit4，智能卡NACK使能 */
	UINT32	SCEN		: 1;		/**< Bit5，智能卡模式使能 */
	UINT32	DMAR		: 1;		/**< Bit6，DMA使能接收 */
	UINT32	DMAT		: 1;		/**< Bit7，DMA使能发送 */
	UINT32	RTSE		: 1;		/**< Bit8，RTS 使能 */
	UINT32	CTSE		: 1;		/**< Bit9，CTS 使能 */
	UINT32	CTSIE		: 1;		/**< Bit10，CTS中断使能 */
	UINT32	ONEBIT	    : 1;		/**< Bit11，一个采样位方法使能 */
	UINT32	OVRDIS	    : 1;		/**< Bit12，溢出禁止 */
	UINT32	DDRE		: 1;		/**< Bit13，DMA禁止接收错误 */
	UINT32	DEM			: 1;		/**< Bit14，驱动使能模式 */
	UINT32	DEP			: 1;		/**< Bit15，驱动使能奇偶校验选择 */
	UINT32	Rsvd1		: 1; 		/**< Bit16，保留 */
	UINT32	SCARCNT	    : 3;		/**< Bit17~19，智能卡自动重试计数 */
	UINT32	WUS			: 2;		/**< Bit20~21，从停机模式唤醒中断标志选择 */
	UINT32	WUFIE		: 1;		/**< Bit22，从停机模式唤醒中断使能 */
	UINT32	Rsvd2		: 9;		/**< Bit23~31，保留 */
}UsartCr3BitType;

/** 串口控制寄存器3定义 */
typedef union
{
	UINT32	all;
	UsartCr3BitType		bit;
}UsartCr3Type;

/** 串口波特率寄存器位定义 */
typedef struct
{
	UINT32	BRR		: 16;		/**< Bit0~15，USART_DIV */
	UINT32	Rsvd1	: 16;   /**< Bit16~31，保留 */
}UsartBrrBitType;

/** 串口波特率寄存器定义 */
typedef	union
{
	UINT32	all;
	UsartBrrBitType		bit;
}UsartBrrType;

/** 串口引导时间和分频寄存器位定义 */
typedef struct
{
	UINT32	PSC		: 8;		/**< Bit0~7，分频值 */
	UINT32	GT		: 8;		/**< Bit8~15，引导时间值 */
	UINT32	Rsvd1	: 16;		/**< Bit16~31，保留 */
}UsartGtprBitType;

/** 串口引导时间和分频寄存器定义 */
typedef union
{
	UINT32	all;
	UsartGtprBitType	bit;
}UsartGtprType;

/** 接收超时寄存器位定义 */
typedef struct
{
	UINT32	RTO		: 24;		/**< Bit0~23，接收超时值 */
	UINT32	BLEN	: 8;		/**< Bit24~31，块长度 */
}UsartRtorBitType;

/** 接收超时寄存器定义 */
typedef union
{
	UINT32	all;
	UsartRtorBitType		bit;
}UsartRtorType;

/** 响应寄存器位定义 */
typedef struct
{
	UINT32	ABRRQ		: 1;		/**< Bit0，自动波特率响应 */	
	UINT32	SBKRQ		: 1;		/**< Bit1，发送断开响应 */
	UINT32	MMRQ		: 1;		/**< Bit2，静音模式响应 */
	UINT32	RXFRQ		: 1;		/**< Bit3，接收数据冲洗响应 */
	UINT32	TXFRQ		: 1;		/**< Bit4，发送数据冲洗响应 */
	UINT32	Rsvd1		: 27;		/**< Bit5~31，保留 */
}UsartRqrBitType;

/** 响应寄存器定义 */
typedef union
{
	UINT32	all;
	UsartRqrBitType		bit;
}UsartRqrType;

/** 中断和状态寄存器位定义 */
typedef struct
{
	UINT32	PE		: 1;		/**< Bit0，奇偶校验错误 */
	UINT32	FE		: 1;		/**< Bit1，帧错误 */
	UINT32	NF		: 1;		/**< Bit2，起始位噪音检测标志 */
	UINT32	ORE		: 1;		/**< Bit3，溢出错误 */
	UINT32	IDLE	: 1;		/**< Bit4，空闲线检测 */
	UINT32	RXNE	: 1;		/**< Bit5，接收数据寄存器非空 */
	UINT32	TC		: 1;		/**< Bit6，发送完成 */
	UINT32	TXE		: 1;		/**< Bit7，发送数据寄存器空 */
	UINT32	LBDF	: 1;		/**< Bit8，LIN断开检测标志 */
	UINT32	CTSIF	: 1;		/**< Bit9，CTS中断标志 */
	UINT32	CTS		: 1;		/**< Bit10，CTS标志 */
	UINT32	RTOF	: 1;		/**< Bit11，接收超时 */
	UINT32	EOBF	: 1;		/**< Bit12，块结束标志 */
	UINT32	Rsvd1	: 1;		/**< Bit13，保留 */
	UINT32	ABRE	: 1;		/**< Bit14，自动波特率错误 */
	UINT32	ABRF	: 1;		/**< Bit15，自动波特率标志 */
	UINT32	BUSY	: 1;		/**< Bit16，忙标志 */
	UINT32	CMF		: 1;		/**< Bit17，字符匹配标志 */
	UINT32	SBKF	: 1;		/**< Bit18，发送断开标志 */
	UINT32	RWU		: 1;		/**< Bit19，从静音模式接收唤醒 */
	UINT32	WUF		: 1;		/**< Bit20，从停止模式唤醒标志 */
	UINT32	TEACK	: 1;		/**< Bit21，发送使能应答标志 */
	UINT32	REACK	: 1;		/**< Bit22，接收使能应答标志 */
	UINT32	Rsvd2	: 9;		/**< Bit23~31，保留 */
}UsartIsrBitType;

/** 中断和状态寄存器定义 */
typedef union
{
	UINT32	all;
	UsartIsrBitType		bit;
}UsartIsrType;

/** 中断标志清除寄存器位定义 */
typedef struct
{
	UINT32	PECF		: 1;		/**< Bit0，奇偶校验错误清零 */
	UINT32	FECF		: 1;		/**< Bit1，帧错误标志清零 */
	UINT32	NCF			: 1;		/**< Bit2，噪音检测标志清零 */
	UINT32	ORECF		: 1;		/**< Bit3，溢出错误标志清零 */
	UINT32	IDLECF	    : 1;		/**< Bit4，空闲线检测标志清零 */
	UINT32	Rsvd1		: 1;		/**< Bit5，保留 */
	UINT32	TCCF		: 1;		/**< Bit6，发送完成标志清零 */
	UINT32	Rsvd2		: 1;		/**< Bit7，保留 */
	UINT32	LBDCF		: 1;		/**< Bit8，LIN断开检测标志清零 */
	UINT32	CTSCF		: 1;		/**< Bit9，CTS标志清零 */
	UINT32	Rsvd3		: 1;		/**< Bit10，保留 */
	UINT32	RTOCF		: 1;		/**< Bit11，接收超时标志清零 */
	UINT32	EOBCF		: 1;		/**< Bit12，块接收标志清零 */
	UINT32	Rsvd6		: 4;		/**< Bit13~16，保留 */
	UINT32	CMCF		: 1;		/**< Bit17，字符匹配标志清零 */
	UINT32	Rsvd4		: 2;		/**< Bit18~19，保留 */
	UINT32	WUCF		: 1;		/**< Bit20，从停机模式唤醒标志清零 */
	UINT32	Rsvd5		: 11;		/**< Bit21~31，保留 */
}UsartIcrBitType;

/** 中断标志清除寄存器定义 */
typedef union
{
	UINT32	all;
	UsartIcrBitType		bit;
}UsartIcrType;

/** 接收数据寄存器位定义 */
typedef struct
{
	UINT32	RDR		: 9;		/**< Bit0~8，接收数据值 */
	UINT32	Rsvd1	: 23;		/**< Bit9~31，保留 */
}UsartRdrBitType;

/** 接收数据寄存器定义 */
typedef union
{
	UINT32	all;
	UsartRdrBitType		bit;
}UsartRdrType;

/** 发送数据寄存器位定义 */
typedef struct
{
	UINT32	TDR		: 9;		/**< Bit0~8，发送数据值 */
	UINT32	Rsvd1	: 23;		/**< Bit9~31，保留 */
}UsartTdrBitType;

/** 发送数据寄存器定义 */
typedef union
{
	UINT32	all;
	UsartTdrBitType		bit;
}UsartTdrType;

/** 串口寄存器 */
typedef struct
{
	UsartCr1Type		CR1;
	UsartCr2Type		CR2;
	UsartCr3Type		CR3;
	UsartBrrType		BRR;
	UsartGtprType		GTPR;
	UsartRtorType		RTOR;
	UsartRqrType		RQR;
	UsartIsrType		ISR;
	UsartIcrType		ICR;
	UsartRdrType		RDR;
	UsartTdrType		TDR;
}UsartType;


/** 串口寄存器地址 */
#define USART1		((UsartType *) USART1_BASE)
#define USART2		((UsartType *) USART2_BASE)
#define USART3		((UsartType *) USART3_BASE)
#define UART4		((UsartType *) UART4_BASE)
#define UART5		((UsartType *) UART5_BASE)



#endif
	
