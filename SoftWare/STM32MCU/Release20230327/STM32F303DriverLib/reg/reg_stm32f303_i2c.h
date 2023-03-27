
/**
  *******************************************************************
  * @file    reg_stm32f303_i2c.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-23
  * @brief   STM32f303 I2C寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __REG_STM32F303_I2C_H__
#define __REG_STM32F303_I2C_H__

#include "typedefine.h"
#include "reg_stm32f303_i2c.h"


/** I2C控制寄存器1位定义 */
typedef struct
{
	UINT32	PE        	: 1;      /**< Bit0，I2C准备使能，0：关闭，1：使能 */
	UINT32 	TXIE      	: 1;      /**< Bit1，I2C发送完成位，0：发送完成，1：未发送完 */
	UINT32 	RXIE      	: 1;      /**< Bit2，I2C接收完成位，0：接收完成，1：未接受完 */
	UINT32 	ADDRIE    	: 1;      /**< Bit3，I2C地址匹配位，0：地址匹配，1：地址不匹配 */
	UINT32 	NACKIE    	: 1;      /**< Bit4，I2C无应答信号位，0：收到无应答信号，1：未收到应答信号 */
	UINT32 	STOPIE    	: 1;      /**< Bit5，I2C停止位， 0：停止信号*/
	UINT32 	TCIE      	: 1;      /**< Bit6，I2C传输完成标志位，0；传输未完成，1，传输完成 */
	UINT32 	ERRIE     	: 1;      /**< Bit7，I2C错误寄存器，0：未出现错误，1：出现错误 */
	UINT32 	DNF       	: 4;      /**< Bit8~11，I2C数字滤波寄存器，0000；关闭滤波，0001~1111:1~15倍滤波 */
	UINT32 	ANFOFF    	: 1;      /**< Bit12，模拟滤波关断寄存器，0：开模拟滤波，1：关模拟滤波 */
	UINT32 	Rsvd1     	: 1;      /**< Bit13，空位 */
	UINT32 	TXDMAEN   	: 1;      /**< Bit14，DMA发送寄存器位，0；关闭DMA模式，1：开启DMA模式 */
	UINT32 	RXDMAEN   	: 1;      /**< Bit15，DMA接收寄存器位，0：关闭DMA模式，1：开启DMA模式 */
	UINT32 	SBC       	: 1;      /**< Bit16，隶属模式寄存器，0；隶属模式关闭，1：隶属模式开启 */
	UINT32 	NOSTRETCH 	: 1;      /**< Bit17，时钟延展关闭寄存器，0：开启时钟延展，1：关闭时钟延展 */
	UINT32 	WUPE      	: 1;      /**< Bit18，唤醒模式寄存器，0:不可唤醒，1：唤醒使能 */
	UINT32 	GCEN      	: 1;      /**< Bit19，通用广播寄存器，0:关闭通用广播，0b00000000为无应答地址，1:开启通用广播，0b00000000是应答地址 */
	UINT32 	SMBHEN    	: 1;      /**< Bit20，SMBus主机地址使能寄存器，0：关闭主机地址，0b00000000为无应答地址，1：开启主机地址，0b00000000是应答地址 */
	UINT32 	SMBDEN    	: 1;      /**< Bit21，SMBus默认设备地址寄存器，0：关闭默认地址，1：开启默认地址 */
	UINT32 	ALERTEN   	: 1;      /**< Bit22，SMBus报警寄存器，0：拉高警报引脚，报警地址指针失能，1:拉低报警引脚，报警地址指针使能 */
	UINT32 	PECEN     	: 1;      /**< Bit23，PEC寄存器，0,PEC寄存器失能，1：PEC寄存器使能 */
	UINT32 	Rsvd2     	: 8;      /**< Bit24~31，空位 */
}I2cCr1BitType;

typedef union
{
	UINT32	all;				/**< 控制寄存器1所有位 */
	I2cCr1BitType 	bit;		/**< 控制寄存器1位定义 */
}I2cCr1Type;

/** I2C控制寄存器2位定义 */
typedef struct
{
    UINT32 	SADD      	: 10;   	/**< Bit0~9，从机地址位，可以是7位或者10位 */
	UINT32 	RD_WRN     	: 1;    	/**< Bit10，传输方向寄存器（主机模式），0：主机读数据，1：主机写数据 */
	UINT32 	ADD10     	: 1;    	/**< Bit11，10位地址模式寄存器，0：主机工作在7位模式下，1：主机工作在10位模式下 */
	UINT32 	HEAD10R   	: 1;    	/**< Bit12，10位地址只读指针寄存器，*/
	UINT32 	START     	: 1;    	/**< Bit13，Start generation，0：No Start generation，1: Restart/Start generation*/
	UINT32 	STOP      	: 1;	  	/**< Bit14，Stop generation (master mode)，0: No Stop generation.1: Stop generation after current byte transfer*/
	UINT32 	NACK      	: 1;	  	/**< Bit15，NACK generation (slave mode)，0: an ACK is sent after current received byte.1: a NACK is sent after current received byte. */
	UINT32 	NBYTES    	: 8;    	/**< Bit16~23，位数寄存器位，传输的位数 */
	UINT32 	RELOAD    	: 1;    	/**< Bit24，NBYTES重装寄存器位，0：NBYTES不重装，传输停止，1：NBYTES重装 */
	UINT32 	AUTOEND   	: 1;    	/**< Bit25，自动结束位，由软件设置和清除，0：软件结束模式，TC标识在NBYTES传输接收时置位，延展SCL低，1：自动结束模式，NBYTES数据传输完成后自动结束 */
	UINT32 	PECBYTE   	: 1;    	/**< Bit26，数据包错误检查位，由软件设置，硬件清除，0：没有PEC传输，1：有PEC传输要求 */
	UINT32 	Rsvd1     	: 5;    	/**< Bit27~31，空位*/
}I2cCr2BitType;

typedef union
{
	UINT32	all;				/**< 控制寄存器2所有位 */
	I2cCr2BitType 	bit;		/**< 控制寄存器2位定义 */
}I2cCr2Type;

/** I2C自有地址寄存器1位定义 */
typedef struct
{
	UINT32 	OA1       : 10;   /**< Bit0~9，广播地址位，可以是7位也可以是10位，7位时首一位与最后两位无关 */
	UINT32 	OA1MODE   : 1;    /**< Bit10，10位自有地址位，0：自有地址为7位，1：自有地址位10位 */
	UINT32 	Rsvd1     : 4;    /**< Bit11~14，空位 */
	UINT32 	OA1EN     : 1;    /**< Bit15，自有地址1使能位，0:自有地址1失能，收到的从机地址OA1为无应答，1：自有地址1使能，收到的从机地址为应答地址 */
	UINT32 	Rsvd2     : 16;   /**< Bit16~31，保留 */
}I2cOar1BitType;

typedef union
{
	UINT32	all;				/**< 自有地址寄存器1所有位 */
	I2cOar1BitType 	bit;	    /**< 自有地址寄存器1位定义 */
}I2cOar1Type;	

/** I2C自有地址寄存器2位定义 */
typedef struct
{
    UINT32 	Rsvd1     : 1;     /**< Bit0，保留 */
	UINT32 	OA2       : 7;     /**< Bit1~7，广播地址2 */
	UINT32 	OA2MSK    : 3;     /**< Bit8~10，自有地址2地址掩码位，000：不掩码，001：OA[1]位被掩，剩下的OA[7:2]位参与比较，010：OA[2：1]位被掩，剩下的OA[7:3]位参与比较，011：OA[3:1]位被掩，剩下的OA[7:4]位参与比较，100：OA[4:1]位被掩，剩下的OA[7:5]位参与比较，,101：OA[5:1]位被掩，剩下的OA[7:6],110：OA[6：1]位被掩，剩下的OA[7]位参与比较，111：OA[7：1]位被掩，不比较 */
	UINT32 	Rsvd2     : 4;     /**< Bit11~14，保留 */
	UINT32 	OA2EN     : 1;     /**< Bit15，OA2使能位，0：自有地址2失能，1：自有地址2使能 */
	UINT32 	Rsvd3     : 16;    /**< Bit16~31，保留 */
}I2cOar2BitType;

typedef union
{
	UINT32	all;					/**< 自有地址寄存器2所有位 */
	I2cOar2BitType 	bit;			/**< 自有地址寄存器2位定义 */
}I2cOar2Type;

/** I2C时钟寄存器位定义 */
typedef struct
{
    UINT32 	SCLL      : 8;  /**< Bit0~7，时钟信号低电平时段位，在主模式下使用tSCLL = (SCLL+1) x tPRESC */
	UINT32 	SCLH      : 8;  /**< Bit8~15，时钟信号高电平时段位，在主模式下实用tSCLH = (SCLH+1) x tPRESC */
	UINT32 	SDADEL    : 4;  /**< Bit16~19，数据保存时间位，传输模式下设定时钟信号与数据信号下降沿间的延时tSDADEL，tSDADEL= SDADEL x tPRESC */
	UINT32 	SCLDEL    : 4;  /**< Bit20~23，数据建立时间位，传输模式下设定时钟信号与数据信号上升沿间的延时tSCLDEL = (SCLDEL+1) x tPRESC */
	UINT32 	Rsvd1     : 4;  /**< Bit24~27，保留 */
	UINT32 	PRESC     : 4;  /**< Bit28~31，时钟分频器位，用于设定tPRESC，tPRESC = (PRESC+1) x tI2CCLK */
}I2cTimingrBitType;

typedef union
{
	UINT32	all;						/**< 时钟控制寄存器所有位 */
	I2cTimingrBitType 	bit;			/**< 时钟控制寄存器位定义 */
}I2cTimingrType;

/** I2C状态寄存器1位定义 */
typedef struct
{
    UINT32 	TIMAOUTA  : 12;  /**< Bit0~11，总线超时A寄存器位，TIDLE=1，时tTIMEOUT= (TIMEOUTA+1) x 2048 x tI2CCLK，TIDLE=0时，tIDLE= (TIMEOUTA+1) x 4 x tI2CCLK*/
	UINT32 	TIDLE     : 1;   /**< Bit12，空闲时钟超时检测位，0：TIMAOUT用于检测SCL低电平超时，1：TIMAOUT用于检测SCL和SDA高电平超时 */
	UINT32 	Rsvd1     : 2;   /**< Bit13~14，保留 */
	UINT32 	TIMOUTEN  : 1;   /**< Bit15，时钟超时使能位，0: SCL超时检测失能，1：SCl超时检测使能 */
	UINT32 	TIMEOUTB  : 12;  /**< Bit16~27，总线超时B寄存器位 ，用于设定累计的延伸时间超时，tLOW:EXT= (TIMEOUTB+1) x 2048 x tI2CCLK */
	UINT32 	Rsvd2     : 3;   /**< Bit28~30，保留 */
	UINT32 	TEXTEN    : 1;   /**< Bit31，延展时钟超时使能位，0：超时检测失能，1：超时检测使能 */
}I2cTimeoutrBitType;

/** I2C状态寄存器1定义 */
typedef union
{
	UINT32	all;			 	/**< 超时寄存器所有位 */
	I2cTimeoutrBitType 	bit;   	/**< 超时寄存器位定义 */
}I2cTimeoutrType;

/** I2C状态寄存器位定义 */
typedef struct
{
	UINT32 	TXE       : 1; /**< Bit0，数据传输寄存器空标志位，由机器写入，可以由软件写入1以刷掉数据传输寄存器中的数据 */
	UINT32 	TXIS      : 1; /**< Bit1，传输中断状态位，数据传输寄存器空置位，下次数据来时清零，可以由软件写入1，仅当NOSTRETCH=1，来设置一次传输中断事件*/
	UINT32 	RXNE      : 1; /**< Bit2，数据接收寄存器非空位，数据存入数据接收寄存器时置位，数据被读出时清零 */
	UINT32 	ADDR      : 1; /**< Bit3，地址匹配位（从模式），当从机地址配对时置位，当设置ADDRCF位时由软件清零 */
	UINT32 	NACKF     : 1; /**< Bit4，无应答接收标志位，接收到NACK数据后置位，由设置NACKCF位时软件清零 */
	UINT32 	STOPF     : 1; /**< Bit5，停止检测位，总线上发送停止状况时由硬件置位，由STOPCF清零 */
	UINT32 	TC        : 1; /**< Bit6，传输完成标志位，当RELOAD=0, AUTOEND=0且传输完成时硬件置位，START或STOP位清零 */
	UINT32 	TCR       : 1; /**< Bit7，传输完成重装标志位，RELOAD=1且NBYTES数据传输完成后置位，NBYTES写入非零值清零 */
	UINT32 	BERR      : 1; /**< Bit8，总线错误标志位*/
	UINT32 	ARLO      : 1; /**< Bit9，仲裁遗失位，仲裁遗失时硬件置位 */
	UINT32 	OVR       : 1; /**< Bit10，溢出标志位，0：未发生上溢/下溢，1：上溢或下溢 */
	UINT32 	PECERR	  : 1; /**< Bit11，接收期间PEC错误，0：无PEC错误，接收器在接收PEC后返回ACK,1：PEC错误，接收器在接收PEC后返回NACK */
	UINT32 	TIMEOUT   : 1; /**< Bit12，超时或TLOW错误,0:无超时错误，1：SCL低电平时长25ms */
	UINT32 	ALERT     : 1; /**< Bit13，SMBus警报位，SMBHEN=1，ALERTEN=1时置位，ALERTCF清零 */
	UINT32 	Rsvd1     : 1; /**< Bit14，保留 */
	UINT32 	BUSY      : 1; /**< Bit15，总线忙碌标志位，START置位，Stop或PE=0时清零 */
	UINT32 	DIR       : 1; /**< Bit16，传输检测位，0，从模式进入接收模式，1:从模式进入写模式 */
	UINT32 	ADDCODE   : 7; /**< Bit17~23，地址匹配代码位 */
	UINT32 	Rsvd2     : 8; /**< Bit24~31，保留 */
}I2cIsrBitType;

typedef union
{
	UINT32	all;				/**< 中断与状态寄存器所有位 */
	I2cIsrBitType 	bit;		/**< 中断与状态寄存器位定义 */
}I2cIsrType;

/** I2C中断清除寄存器位定义 */
typedef struct
{
    UINT32 	Rsvd1     	: 3;              /**< Bit0~2，保留 */
	UINT32 	ADDRCF    	: 1;              /**< Bit3，地址匹配标志位清零位 */
	UINT32 	NACKCF    	: 1;              /**< Bit4，未承认标志清零位 */
	UINT32 	STOPCF    	: 1;              /**< Bit5，停止检测标志清零位 */
	UINT32 	Rsvd2     	: 2;              /**< Bit6~7，保留 */
	UINT32 	BERRCF    	: 1;              /**< Bit8，总线错误标志清零位 */
	UINT32 	ARLOCF    	: 1;              /**< Bit9，仲裁丢失标志清零位 */
	UINT32 	OVRCF     	: 1;              /**< Bit10，溢出标志清零位 */
	UINT32 	PECCF     	: 1;              /**< Bit11，PEC错误标志清零位 */
	UINT32 	TIMOUTCF  	: 1;              /**< Bit12，超时检测标准清零位 */
	UINT32 	ALERTCF   	: 1;              /**< Bit13，警报标志清零位 */
	UINT32 	Rsvd3		: 18;             /**< Bit14~31，保留 */
}I2cIcrBitType;

typedef union
{
	UINT32	all;					 	/**< 中断与清零寄存器所有位 */
	I2cIcrBitType 	bit;				/**< 中断与清零寄存器位定义 */
}I2cIcrType;

/** I2CPECR寄存器位定义 */
typedef struct
{
	UINT32 	PEC     	: 8;            /**< Bit0~7，数据包错误检查寄存器位*/
	UINT32 	Rsvd1    	: 24;           /**< Bit8~31，保留*/
}I2cPecrBitType;

typedef union
{
	UINT32	all;						/**< I2CPEC寄存器所有位 */
	I2cPecrBitType 	bit;				/**< I2CPEC寄存器位定义 */
}I2cPecrType;

/** I2C输入寄存器位定义 */
typedef struct
{
    UINT32 	RXDATA  : 8;           /**< Bit0~7，接收数据寄存器位 */
	UINT32 	Rsvd1   : 24;          /**< Bit8~31，保留 */
}I2cRxdrBitType;

typedef union
{
	UINT32	all;						/**< 输入控制寄存器所有位 */
	I2cRxdrBitType 	bit;			    /**< 输入控制寄存器位定义 */
}I2cRxdrType;

/** I2C输出寄存器位定义 */
typedef struct
{
    UINT32 	TXDATA   : 8;           /**< Bit0~7，输出数据寄存器位 */
	UINT32 	Rsvd1    : 24;          /**< Bit8~31，保留 */
}I2cTxdrBitType;

typedef union
{
	UINT32	all;						/**< 输出控制寄存器所有位 */
	I2cTxdrBitType 	bit;				/**< 输出控制寄存器位定义 */
}I2cTxdrType;



/** I2C寄存器 */
typedef struct
{
	I2cCr1Type 			CR1;						/**< 控制寄存器1,		偏移地址：0x00 */
	I2cCr2Type			CR2;						/**< 控制寄存器2,		偏移地址：0x04 */
	I2cOar1Type			OAR1;						/**< 自身地址寄存器1,	偏移地址：0x08 */
	I2cOar2Type			OAR2;						/**< 自身地址寄存器2,	偏移地址：0x0C */
	I2cTimingrType		TIMINGR;					/**< 时钟寄存器,		偏移地址：0x10 */
	I2cTimeoutrType	    TIMEOUTR;				    /**< 超时寄存器,		偏移地址：0x14 */
	I2cIsrType			ISR;						/**< 中断与状态寄存器,	偏移地址：0x18 */
	I2cIcrType			ICR;						/**< 中断与清零寄存器,	偏移地址：0x1C */
	I2cPecrType			PECR;						/**< PEC寄存器,			偏移地址：0x20 */
	I2cRxdrType			RXDR;						/**< 输入寄存器,		偏移地址：0x24 */
	I2cTxdrType         TXDR;                       /**< 输出寄存器， 		偏移地址：0x28*/
}I2cType;



/** I2C模块定义 */
#define I2C1	((I2cType *) I2C1_BASE)
#define I2C2	((I2cType *) I2C2_BASE)



#endif
