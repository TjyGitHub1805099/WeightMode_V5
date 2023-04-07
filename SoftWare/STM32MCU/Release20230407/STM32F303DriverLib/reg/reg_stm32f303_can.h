/**
  *******************************************************************
  * @file    reg_stm32f303_can.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-23
  * @brief   STM32F303 CAN寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#ifndef __REG_STM32F303_CAN_H__
#define	__REG_STM32F303_CAN_H__

#include "typedefine.h"
#include "reg_stm32f303_address.h"


/** CAN 主机控制寄存器位定义 */
typedef struct
{
	UINT32	INRQ		: 1;				/**< Bit0，初始化请求 */
	UINT32	SLEEP		: 1;				/**< Bit1，睡眠模式请求 */
	UINT32	TXFP		: 1;				/**< Bit2，发送FIFO优先级 */
	UINT32	RFLM		: 1;				/**< Bit3，接收FIFO锁定模式 */
	UINT32	NART		: 1;				/**< Bit4，不自动重发 */
	UINT32	AWUM		: 1;				/**< Bit5，自动唤醒模式 */
	UINT32	ABOM		: 1;				/**< Bit6，自动离线管理 */
	UINT32	TTCM		: 1;				/**< Bit7，时间触发通讯模式 */
	UINT32	Rsvd1		: 7;				/**< Bit8~14，保留 */
	UINT32	RESET		: 1;				/**< Bit15，CAN软件主机复位 */
	UINT32	DBF			: 1;				/**< Bit16，调试冻结 */
	UINT32	Rsvd2		: 15;				/**< Bit17~31，保留 */
}CanMcrBitType;

/** CAN 主机控制寄存器定义 */
typedef union
{
	UINT32	all;
	CanMcrBitType		bit;
}CanMcrType;

/** CAN 主机状态寄存器位定义 */
typedef struct
{
	UINT32	INAK		: 1;				/**< Bit0，初始化响应 */
	UINT32	SLAK		: 1;				/**< Bit1，睡眠响应 */
	UINT32	ERRI		: 1;				/**< Bit2，错误中断 */
	UINT32	WKUI		: 1;				/**< Bit3，唤醒中断 */
	UINT32	SLAKI		: 1;				/**< Bit4，睡眠响应中断 */
	UINT32	Rsvd1		: 3;				/**< Bit5~7，保留 */
	UINT32	TXM			: 1;				/**< Bit8，发送模式 */
	UINT32	RXM			: 1;				/**< Bit9，接收模式 */
	UINT32	SAMP		: 1;				/**< Bit10，最后一个采样点 */
	UINT32	RX			: 1;				/**< Bit11，CAN接收信号 */
	UINT32	Rsvd2		: 20;				/**< Bit12~31，保留 */
}CanMsrBitType;

/** CAN 主机状态寄存器定义 */
typedef union
{
	UINT32	all;
	CanMsrBitType		bit;
}CanMsrType;

/** CAN	发送状态寄存器位定义 */
typedef struct
{
	UINT32	RQCP0		: 1;				/**< Bit0，邮箱0请求完成 */
	UINT32	TXOK0		: 1;				/**< Bit1，邮箱0发送完成 */
	UINT32	ALST0		: 1;				/**< Bit2，邮箱0仲裁丢失 */
	UINT32	TERR0		: 1;				/**< Bit3，邮箱0发送错误 */
	UINT32	Rsvd1		: 3;				/**< Bit4~6，保留 */
	UINT32	ABRQ0		: 1;				/**< Bit7，邮箱0终止请求 */
	UINT32	RQCP1		: 1;				/**< Bit8，邮箱1请求完成 */
	UINT32	TXOK1		: 1;				/**< Bit9，邮箱1发送完成 */
	UINT32	ALST1		: 1;				/**< Bit10，邮箱1仲裁丢失 */
	UINT32	TERR1		: 1;				/**< Bit11，邮箱1发送错误 */
	UINT32	Rsvd2		: 3;				/**< Bit12~14，保留 */
	UINT32	ABRQ1		: 1;				/**< Bit15，邮箱1终止请求 */
	UINT32	RQCP2		: 1;				/**< Bit16，邮箱2请求完成 */
	UINT32	TXOK2		: 1;				/**< Bit17，邮箱2发送完成 */
	UINT32	ALST2		: 1;				/**< Bit18，邮箱2仲裁丢失 */
	UINT32	TERR2		: 1;				/**< Bit19，邮箱2发送错误 */
	UINT32	Rsvd3		: 3;				/**< Bit20~22，保留 */
	UINT32	ABRQ2		: 1;				/**< Bit23，邮箱2终止请求 */
	UINT32	CODE		: 2;				/**< Bit24~25，邮箱编码 */
	UINT32	TME0		: 1;				/**< Bit26，邮箱0发送空 */
	UINT32	TME1		: 1;				/**< Bit27，邮箱1发送空 */
	UINT32	TME2		: 1;				/**< Bit28，邮箱2发送空 */
	UINT32	LOW0		: 1;				/**< Bit29，邮箱0最低优先级标志 */
	UINT32	LOW1		: 1;				/**< Bit30，邮箱1最低优先级标志 */
	UINT32	LOW2		: 1;				/**< Bit31，邮箱2最低优先级标志 */
}CanTsrBitType;

/** CAN	发送状态寄存器定义 */
typedef union
{
	UINT32	all;
	CanTsrBitType		bit;
}CanTsrType;

/** 接收FIFO0寄存器位定义 */
typedef struct
{
	UINT32	FMP0		: 2;			/**< Bit0~1，FIFO0消息挂起 */
	UINT32	Rsvd1		: 1;			/**< Bit2，保留 */
	UINT32	FULL0		: 1;			/**< Bit3，FIFO0满 */
	UINT32	FOVR0		: 1;			/**< Bit4，FIFO0溢出 */
	UINT32	RFOM0		: 1;			/**< Bit5，释放FIFO0输出邮箱 */
	UINT32	Rsvd2		: 26;			/**< Bit6~31，保留 */
}CanRf0rBitType;

/** 接收FIFO0寄存器定义 */
typedef union
{
	UINT32	all;
	CanRf0rBitType	bit;
}CanRf0rType;

/** 接收FIFO1寄存器位定义 */
typedef struct
{
	UINT32	FMP1		: 2;			/**< Bit0~1，FIFO1消息挂起 */
	UINT32	Rsvd1		: 1;			/**< Bit2，保留 */
	UINT32	FULL1		: 1;			/**< Bit3，FIFO1满 */
	UINT32	FOVR1		: 1;			/**< Bit4，FIFO1溢出 */
	UINT32	RFOM1		: 1;			/**< Bit5，释放FIFO1输出邮箱 */
	UINT32	Rsvd2		: 26;			/**< Bit6~31，保留 */
}CanRf1rBitType;

/** 接收FIFO1寄存器定义 */
typedef union
{
	UINT32	all;
	CanRf1rBitType	bit;
}CanRf1rType;


/** CAN中断使能寄存器位定义 */
typedef struct
{
	UINT32	TMEIE		: 1;				/**< Bit0，发送邮箱为空中断使能 */
	UINT32	FMPIE0	: 1;				/**< Bit1，FIFO消息挂起中断使能 */
	UINT32	FFIE0		: 1;				/**< Bit2，FIFO满中断使能 */
	UINT32	FOVIE0	: 1;				/**< Bit3，FIFO溢出中断使能 */
	UINT32	FMPIE1	: 1;				/**< Bit4，FIFO消息挂起中断使能 */
	UINT32	FFIE1		: 1;				/**< Bit5，FIFO满中断使能 */
	UINT32	FOVIE1	: 1;				/**< Bit6，FIFO溢出中断使能 */
	UINT32	Rsvd1		: 1;				/**< Bit7，保留 */
	UINT32	EWGIE		: 1;				/**< Bit8，错误警告中断使能 */
	UINT32	EPVIE		: 1;				/**< Bit9，被动错误中断使能 */
	UINT32	BOFIE		: 1;				/**< Bit10，离线中断使能 */
	UINT32	LECIE		: 1;				/**< Bit11，上次错误代码中断使能 */
	UINT32	Rsvd2		: 3;				/**< Bit12~14，保留 */
	UINT32	ERRIE		: 1;				/**< Bit15，错误中断使能 */
	UINT32	WKUIE		: 1;				/**< Bit16唤醒中断使能， */
	UINT32	SLKIE		: 1;				/**< Bit17，睡眠中断使能 */
	UINT32	Rsvd3		: 14;				/**< Bit18~31，保留 */
}CanIerBitType;

/** CAN中断使能寄存器定义 */
typedef struct
{
	UINT32	all;
	CanIerBitType		bit;
}CanIerType;

/** CAN错误状态寄存器位定义 */
typedef struct
{
	UINT32	EWGF		: 1;				/**< Bit0，错误警告标志 */
	UINT32	EPVF		: 1;				/**< Bit1，被动错误标志 */
	UINT32	BOFF		: 1;				/**< Bit2，离线标志 */
	UINT32	Rsvd1		: 1;				/**< Bit3，保留 */
	UINT32	LEC			: 3;				/**< Bit4~6，上次错误代码 */
	UINT32	Rsvd2		: 9;				/**< Bit7~15，保留 */
	UINT32	TEC			: 8;				/**< Bit16~23，9位发送错误计数器最低有效字节 */
	UINT32	REC			: 8;				/**< Bit24~31，接收错误计数器 */
}CanEsrBitType;

/** CAN错误状态寄存器定义 */
typedef union
{
	UINT32	all;
	CanEsrBitType		bit;
}CanEsrType;

/** CAN 位时间寄存器位定义 */
typedef struct
{
	UINT32	BRP			: 10;				/**< Bit0~9， 波特率分频 */
	UINT32	Rsvd1		: 6;				/**< Bit10~15，保留 */
	UINT32	TS1			: 4;				/**< Bit16~19，时间段1 */
	UINT32	TS2			: 3;				/**< Bit20~22，时间段2 */
	UINT32	Rsvd2		: 1;				/**< Bit23，保留 */
	UINT32	SJW			: 2;				/**< Bit24~25，同步跳跃宽度 */
	UINT32	Rsvd3		: 4;				/**< Bit26~29，保留 */
	UINT32	LBKM		: 1;				/**< Bit30，回环模式 */
	UINT32	SILM		: 1;				/**< Bit31，静默模式 */
}CanBtrBitType;

/** CAN 位时间寄存器定义 */
typedef union
{
	UINT32	all;
	CanBtrBitType		bit;
}CanBtrType;

/** CAN发送邮箱标识符寄存器按照标准帧位定义 */
typedef struct
{
	UINT32 TXRQ		: 1;
	UINT32 RTR		: 1;
	UINT32 IDE		: 1;
	UINT32 Rsvd		: 18;
	UINT32 STID		: 11;
}CanTirBitType1;

/** CAN发送邮箱标识符寄存器按照扩展帧位定义 */
typedef struct
{
	UINT32 TXRQ		: 1;
	UINT32 RTR			: 1;
	UINT32 IDE			: 1;
	UINT32 EXID		: 29;
}CanTirBitType2;

/** CAN发送邮箱标识符寄存器定义 */
typedef union
{
	UINT32	all;
	CanTirBitType1		bit_st;
	CanTirBitType2		bit_ex;
}CanTirType;

/** CAN 邮箱数据长度控制和时间戳寄存器位定义 */
typedef struct
{
	UINT32	DLC			: 4;				/**< Bit0~3，数据长度代码 */
	UINT32	Rsvd1		: 4;				/**< Bit4~7，保留 */
	UINT32	TGT			: 1;				/**< Bit8，发送全局时间 */
	UINT32	Rsvd2		: 7;				/**< Bit9~15，保留 */
	UINT32	TIME		: 16;				/**< Bit16~31，消息时间戳 */
}CanTdtrBitType;

/** CAN 邮箱数据长度控制和时间戳寄存器定义 */
typedef union
{
	UINT32	all;
	CanTdtrBitType	bit;
}CanTdtrType;

/** CAN 邮箱数据低部分寄存器位定义 */
typedef struct
{
	UINT32	DATA0		: 8;			/**< Bit0~7，数据字节0 */
	UINT32	DATA1		: 8;			/**< Bit8~15，数据字节1  */
	UINT32	DATA2		: 8;			/**< Bit16~23，数据字节2  */
	UINT32	DATA3		: 8;			/**< Bit24~31，数据字节3  */
}CanTdlrBitType;

/** CAN 邮箱数据低部分寄存器定义 */
typedef union
{
	UINT32	all;
	CanTdlrBitType	bit;
}CanTdlrType;

/** CAN 邮箱数据高部分寄存器位定义 */
typedef struct
{
	UINT32	DATA4		: 8;			/**< Bit0~7，数据字节4 */
	UINT32	DATA5		: 8;			/**< Bit8~15，数据字节5  */
	UINT32	DATA6		: 8;			/**< Bit16~23，数据字节6  */
	UINT32	DATA7		: 8;			/**< Bit24~31，数据字节7  */
}CanTdhrBitType;

/** CAN 邮箱数据高部分寄存器定义 */
typedef union
{
	UINT32	all;
	CanTdhrBitType	bit;
}CanTdhrType;

/** CAN 接收FIFO邮箱标识符寄存器按标准帧位定义 */
typedef struct
{
	UINT32	Rsvd1		: 1;
	UINT32	RTR			: 1;
	UINT32	IDE			: 1;
	UINT32	Rsvd2		: 18;
	UINT32	STID		: 11;
}CanRirBitType1;

/** CAN 接收FIFO邮箱标识符寄存器按扩展帧位定义 */
typedef struct
{
	UINT32	Rsvd1		: 1;
	UINT32	RTR			: 1;
	UINT32	IDE			: 1;
	UINT32	EXID		: 29;
}CanRirBitType2;


/** CAN 接收FIFO邮箱标识符寄存器定义 */
typedef union
{
	UINT32	all;
	CanRirBitType1		bit_st;
	CanRirBitType2		bit_ex;
}CanRirType;

/** CAN接收FIFO邮箱数据长度控制和时间戳寄存器位定义 */
typedef struct
{
	UINT32	DLC			: 4;				/**< Bit0~3，数据长度代码 */
	UINT32	Rsvd1		: 4;				/**< Bit4~7，保留 */
	UINT32	FMI			: 8;				/**< Bit8~15，过滤器匹配指标 */
	UINT32	TIME		: 16;				/**< Bit16~31，消息时间戳 */
}CanRdtrBitType;

/** CAN接收FIFO邮箱数据长度控制和时间戳寄存器定义 */
typedef union
{
	UINT32	all;
	CanRdtrBitType	bit;
}CanRdtrType;

/** CAN接收FIFO邮箱数据低部分寄存器位定义 */
typedef struct
{
	UINT32	DATA0		: 8;			/**< Bit0~7，数据字节0 */
	UINT32	DATA1		: 8;			/**< Bit8~15，数据字节1 */
	UINT32	DATA2		: 8;			/**< Bit16~23，数据字节2 */
	UINT32	DATA3		: 8;			/**< Bit24~31，数据字节3 */
}CanRdlrBitType;

/** CAN接收FIFO邮箱数据低部分寄存器定义 */
typedef union
{
	UINT32	all;
	CanRdlrBitType	bit;
}CanRdlrType;

/** CAN接收FIFO邮箱数据高部分寄存器位定义 */
typedef struct
{
	UINT32	DATA4		: 8;			/**< Bit0~7，数据字节4 */
	UINT32	DATA5		: 8;			/**< Bit8~15，数据字节5 */
	UINT32	DATA6		: 8;			/**< Bit16~23，数据字节6 */
	UINT32	DATA7		: 8;			/**< Bit24~31，数据字节7 */
}CanRdhrBitType;

/** CAN接收FIFO邮箱数据高部分寄存器定义 */
typedef union
{
	UINT32	all;
	CanRdhrBitType	bit;
}CanRdhrType;

/** CAN 过滤器主机寄存器位定义 */
typedef struct
{
	UINT32	FINIT		: 1;			/**< Bit0，过滤器初始化模式 */
	UINT32	Rsvd1		: 31;			/**< Bit1~31，保留 */
}CanFmrBitType;

/** CAN 过滤器主机寄存器定义 */
typedef union
{
	UINT32	all;
	CanFmrBitType		bit;
}CanFmrType;

/** CAN 过滤器模式寄存器位定义 */
typedef struct
{
	UINT32	FBM0		: 1;			/**< Bit0，过滤器0寄存器模式 */
	UINT32	FBM1		: 1;			/**< Bit1，过滤器1寄存器模式 */
	UINT32	FBM2		: 1;			/**< Bit2，过滤器2寄存器模式 */
	UINT32	FBM3		: 1;			/**< Bit3，过滤器3寄存器模式 */
	UINT32	FBM4		: 1;			/**< Bit4，过滤器4寄存器模式 */
	UINT32	FBM5		: 1;			/**< Bit5，过滤器5寄存器模式 */
	UINT32	FBM6		: 1;			/**< Bit6，过滤器6寄存器模式 */
	UINT32	FBM7		: 1;			/**< Bit7，过滤器7寄存器模式 */
	UINT32	FBM8		: 1;			/**< Bit8，过滤器8寄存器模式 */
	UINT32	FBM9		: 1;			/**< Bit9，过滤器9寄存器模式 */
	UINT32	FBM10		: 1;			/**< Bit10，过滤器10寄存器模式 */
	UINT32	FBM11		: 1;			/**< Bit11，过滤器11寄存器模式 */
	UINT32	FBM12		: 1;			/**< Bit12，过滤器12寄存器模式 */
	UINT32	FBM13		: 1;			/**< Bit13，过滤器13寄存器模式 */
	UINT32	Rsvd1		: 18;			/**< Bit14~31，保留 */
}CanFm1rBitType;

/** CAN 过滤器模式寄存器定义 */
typedef union
{
	UINT32	all;
	CanFm1rBitType	bit;
}CanFm1rType;

/** CAN 过滤器规模寄存器位定义 */
typedef struct
{
	UINT32	FSC0		: 1;				/**< Bit0，过滤器0规模配置 */
	UINT32	FSC1		: 1;				/**< Bit1，过滤器1规模配置 */
	UINT32	FSC2		: 1;				/**< Bit2，过滤器2规模配置 */
	UINT32	FSC3		: 1;				/**< Bit3，过滤器3规模配置 */
	UINT32	FSC4		: 1;				/**< Bit4，过滤器4规模配置 */
	UINT32	FSC5		: 1;				/**< Bit5，过滤器5规模配置 */
	UINT32	FSC6		: 1;				/**< Bit6，过滤器6规模配置 */
	UINT32	FSC7		: 1;				/**< Bit7，过滤器7规模配置 */
	UINT32	FSC8		: 1;				/**< Bit8，过滤器8规模配置 */
	UINT32	FSC9		: 1;				/**< Bit9，过滤器9规模配置 */
	UINT32	FSC10		: 1;				/**< Bit10，过滤器10规模配置 */
	UINT32	FSC11		: 1;				/**< Bit11，过滤器11规模配置 */
	UINT32	FSC12		: 1;				/**< Bit12，过滤器12规模配置 */
	UINT32	FSC13		: 1;				/**< Bit13，过滤器13规模配置 */	
	UINT32	Rsvd1		: 18;				/**< Bit14~31，保留 */
}CanFs1rBitType;

/** CAN 过滤器规模寄存器定义 */
typedef union
{
	UINT32	all;
	CanFs1rBitType	bit;
}CanFs1rType;

/** CAN过滤器FIFO分配寄存器位定义 */
typedef struct
{
	UINT32	FFA0		: 1;				/**< Bit0，过滤器0过滤器FIFO分配 */
	UINT32	FFA1		: 1;				/**< Bit1，过滤器1过滤器FIFO分配 */
	UINT32	FFA2		: 1;				/**< Bit2，过滤器2过滤器FIFO分配 */
	UINT32	FFA3		: 1;				/**< Bit3，过滤器3过滤器FIFO分配 */
	UINT32	FFA4		: 1;				/**< Bit4，过滤器4过滤器FIFO分配 */
	UINT32	FFA5		: 1;				/**< Bit5，过滤器5过滤器FIFO分配 */
	UINT32	FFA6		: 1;				/**< Bit6，过滤器6过滤器FIFO分配 */
	UINT32	FFA7		: 1;				/**< Bit7，过滤器7过滤器FIFO分配 */
	UINT32	FFA8		: 1;				/**< Bit8，过滤器8过滤器FIFO分配 */
	UINT32	FFA9		: 1;				/**< Bit9，过滤器9过滤器FIFO分配 */
	UINT32	FFA10		: 1;				/**< Bit10，过滤器10过滤器FIFO分配 */
	UINT32	FFA11		: 1;				/**< Bit11，过滤器11过滤器FIFO分配 */
	UINT32	FFA12		: 1;				/**< Bit12，过滤器12过滤器FIFO分配 */
	UINT32	FFA13		: 1;				/**< Bit13，过滤器13过滤器FIFO分配 */
	UINT32	Rsvd1		: 18				/**< Bit14~31，保留 */;
}CanFfa1rBitType;

/** CAN过滤器FIFO分配寄存器定义 */
typedef union
{
	UINT32	all;
	CanFfa1rBitType		bit;
}CanFfa1rType;

/** CAN过滤器激活寄存器位定义 */
typedef struct
{
	UINT32	FACT0	: 1;		/**< Bit0，过滤器0激活 */
	UINT32	FACT1	: 1;		/**< Bit1，过滤器1激活 */
	UINT32	FACT2	: 1;		/**< Bit2，过滤器2激活 */
	UINT32	FACT3	: 1;		/**< Bit3，过滤器3激活 */
	UINT32	FACT4	: 1;		/**< Bit4，过滤器4激活 */
	UINT32	FACT5	: 1;		/**< Bit5，过滤器5激活 */
	UINT32	FACT6	: 1;		/**< Bit6，过滤器6激活 */
	UINT32	FACT7	: 1;		/**< Bit7，过滤器7激活 */
	UINT32	FACT8	: 1;		/**< Bit8，过滤器8激活 */
	UINT32	FACT9	: 1;		/**< Bit9，过滤器9激活 */
	UINT32	FACT10	: 1;		/**< Bit10，过滤器10激活 */
	UINT32	FACT11	: 1;		/**< Bit11，过滤器11激活 */
	UINT32	FACT12	: 1;		/**< Bit12，过滤器12激活 */
	UINT32	FACT13	: 1;		/**< Bit13，过滤器13激活 */
	UINT32	Rsvd1	: 18;		/**< Bit14~31，保留 */
}CanFa1rBitType;

/** CAN过滤器激活寄存器定义 */
typedef union
{
	UINT32	all;
	CanFa1rBitType	bit;
}CanFa1rType;

/** 过滤器组寄存器位定义 */
typedef struct
{
	UINT32	FB0		: 1;			/**< Bit0，过滤器位 */
	UINT32	FB1		: 1;			/**< Bit1，过滤器位 */
	UINT32	FB2		: 1;			/**< Bit2，过滤器位 */
	UINT32	FB3		: 1;			/**< Bit3，过滤器位 */
	UINT32	FB4		: 1;			/**< Bit4，过滤器位 */
	UINT32	FB5		: 1;			/**< Bit5，过滤器位 */
	UINT32	FB6		: 1;			/**< Bit6，过滤器位 */
	UINT32	FB7		: 1;			/**< Bit7，过滤器位 */
	UINT32	FB8		: 1;			/**< Bit8，过滤器位 */
	UINT32	FB9		: 1;			/**< Bit9，过滤器位 */
	UINT32	FB10	: 1;			/**< Bit10，过滤器位 */
	UINT32	FB11	: 1;			/**< Bit11，过滤器位 */
	UINT32	FB12	: 1;			/**< Bit12，过滤器位 */
	UINT32	FB13	: 1;			/**< Bit13，过滤器位 */
	UINT32	FB14	: 1;			/**< Bit14，过滤器位 */
	UINT32	FB15	: 1;			/**< Bit15，过滤器位 */
	UINT32	FB16	: 1;			/**< Bit16，过滤器位 */
	UINT32	FB17	: 1;			/**< Bit17，过滤器位 */
	UINT32	FB18	: 1;			/**< Bit18，过滤器位 */
	UINT32	FB19	: 1;			/**< Bit19，过滤器位 */
	UINT32	FB20	: 1;			/**< Bit20，过滤器位 */
	UINT32	FB21	: 1;			/**< Bit21，过滤器位 */
	UINT32	FB22	: 1;			/**< Bit22，过滤器位 */
	UINT32	FB23	: 1;			/**< Bit23，过滤器位 */
	UINT32	FB24	: 1;			/**< Bit24，过滤器位 */
	UINT32	FB25	: 1;			/**< Bit25，过滤器位 */
	UINT32	FB26	: 1;			/**< Bit26，过滤器位 */
	UINT32	FB27	: 1;			/**< Bit27，过滤器位 */
	UINT32	FB28	: 1;			/**< Bit28，过滤器位 */
	UINT32	FB29	: 1;			/**< Bit29，过滤器位 */
	UINT32	FB30	: 1;			/**< Bit30，过滤器位 */
	UINT32	FB31	: 1;			/**< Bit31，过滤器位 */
}CanFrBitType;

/** 过滤器组寄存器定义 */
typedef union
{
	UINT32	all;
	CanFrBitType	bit;
}CanFrType;

/** CAN发送邮箱定义 */
typedef struct
{
	CanTirType		TIR;			/**< CAN发送邮箱0标识符寄存器*/
	CanTdtrType		TDTR;			/**< CAN邮箱数据长度控制和时间戳寄存器*/
	CanTdlrType		TDLR;			/**< CAN邮箱数据低部分寄存器*/
	CanTdhrType		TDHR;			/**< CAN邮箱数据高部分寄存器*/
}CanTxMailBoxType;

/** CAN接收FIFO邮箱定义 */
typedef struct
{
	CanRirType		RIR;			/**< CAN接收FIFO邮箱标识符寄存器 */
	CanRdtrType		RDTR;			/**< CAN接收FIFO邮箱数据长度控制和时间戳寄存器 */
	CanRdlrType		RDLR;			/**< CAN接收FIFO邮箱数据低部分寄存器 */
	CanRdhrType		RDHR;			/**< CAN接收FIFO邮箱数据高部分寄存器 */
}CanRxFifoMailBoxType;

/** CAN 过滤器定义 */
typedef struct
{
	CanFrType		FR1;			/**< 过滤器组寄存器 */
	CanFrType		FR2;			/**< 过滤器组寄存器 */
}CanFilterType;

/** CAN 寄存器 */
typedef struct
{
	CanMcrType				MCR;					/**< CAN主机控制寄存器，		偏移地址0x000 */
	CanMsrType				MSR;					/**< CAN主机状态寄存器，		偏移地址0x004 */
	CanTsrType				TSR;					/**< CAN发送状态寄存器，		偏移地址0x008 */
	CanRf0rType				RF0R;					/**< CAN接收FIFO0寄存器，		偏移地址0x00c */
	CanRf1rType				RF1R;					/**< CAN接收FIFO1寄存器，		偏移地址0x010 */
	CanIerType				IER;					/**< CAN中断使能寄存器，		偏移地址0x014 */
	CanEsrType				ESR;					/**< CAN错误状态寄存器，		偏移地址0x018 */
	CanBtrType				BTR;					/**< CAN位时间寄存器，			偏移地址0x01c */
	UINT32					Rsvd1[88];				/**< 保留，						偏移地址0x020~0x17f */
	CanTxMailBoxType			TxMailBox[3];		/**< CAN发送邮箱，				偏移地址0x180~0x1ac */
	CanRxFifoMailBoxType	RxFifoMailBox[2];		/**< CAN接收FIFO邮箱，			偏移地址0x1b0~0x1cc */
	UINT32					Rsvd2[12];				/**< 保留，						偏移地址0x1d0~0x1ff */
	CanFmrType				FMR;					/**< CAN过滤器主机寄存器，		偏移地址0x200 */
	CanFm1rType				FM1R;					/**< CAN过滤器模式寄存器，		偏移地址0x204 */
	UINT32					Rsvd3;					/**< 保留，						偏移地址0x208 */
	CanFs1rType				FS1R;					/**< CAN过滤器规模寄存器，		偏移地址0x20c */
	UINT32					Rsvd4;					/**< 保留，						偏移地址0x210 */
	CanFfa1rType			FFA1R;					/**< CAN过滤器FIFO分配寄存器，	偏移地址0x214 */
	UINT32					Rsvd5;					/**< 保留，						偏移地址0x218 */
	CanFa1rType				FA1R;					/**< CAN过滤器激活寄存器，		偏移地址0x21c */
	UINT32					Rsvd6[8];				/**< 保留，						偏移地址0x220~0x23f */
	CanFilterType			Filter[28];				/**< 过滤器，					偏移地址0x240~0x31c */
}CanType;



/** CAN 模块定义*/
#define CAN1	((CanType *) CAN1_BASE)



#endif
