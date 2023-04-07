/**
  *******************************************************************
  * @file    reg_stm32f303_spi.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-19
  * @brief   STM32F303	SPI寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#ifndef	__REG_STM32F303_SPI_H__
#define	__REG_STM32F303_SPI_H__

#include "typedefine.h"
#include "reg_stm32f303_address.h"

/** SPI 控制寄存器1位定义 */
typedef struct
{
	UINT32  CPOL_CPHA 	: 2;			    	/**< Bit0~1,SPI时序模式，模式0~模式3 */
	UINT32  MSTR   		: 1;				    /**< Bit2, 主模式选择，1表示主配置 */
	UINT32  BR     		: 3;			      	/**< Bit3~5, 波特率控制 */
	UINT32  SPE    		: 1;					/**< Bit6, SPI 使能，1表示使能外设 */
	UINT32  LSBFIRST	: 1;				  	/**< Bit7, 帧格式，1表示先发送 LSB */
	UINT32  SSI    		: 1;				    /**< Bit8, 内部从器件选择 */
	UINT32  SSM    		: 1;				    /**< Bit9, 软件从设备管理 */
	UINT32  RXONLY 		: 1;				    /**< Bit10, 只接收模式使能，0：全双工（发送和接收）,1：关闭输出（只接收模式） */
	UINT32  CRCL   		: 1;				    /**< Bit11, CRC长度 */	
    UINT32  CRCNEXT		: 1;				  	/**< Bit12, 下一次传输 CRC，0：数据阶段（无 CRC 阶段）,1：下一次传输为 CRC（CRC 阶段） */
	UINT32  CRCEN  		: 1;				    /**< Bit13, 硬件 CRC 计算使能，1表示使能 CRC 计算 */
	UINT32  BIDIOE 		: 1;				    /**< Bit14, 双向通信模式下的输出使能，1表示使能输出（只发送模式） */
	UINT32  BIDIMODE 	: 1;				  	/**< Bit15, 双向通信数据模式使能，1表示选择单线双向通信数据模式，0表示选择双线单向通信数据模式 */
	UINT32	Rsvd1		: 16;					/**< Bit16~31， 保留 */
}SpiCr1BitType;

/** SPI 控制寄存器 1定义 */
typedef union
{	
	UINT32  all;											/**< SPI 控制寄存器 1所有位 */
	SpiCr1BitType  bit;			  				/**< SPI 控制寄存器 1位定义	*/
}SpiCr1Type;

/** SPI 控制寄存器2位定义 */
typedef struct
{
	UINT32  RXDMAEN   : 1;			/**< Bit0, 接收缓冲区 DMA 使能，1表示使能接收缓冲区 DMA */
	UINT32  TXDMAEN   : 1;			/**< Bit1, 发送缓冲区 DMA 使能，1表示使能发送缓冲区 DMA */
	UINT32  SSOE      : 1;			/**< Bit2, SS 输出使能，1表示在主模式下使能 SS 输出，不能在多主模式环境下工作 */
	UINT32	NSSP	  : 1;			/**< BIT3, NSS脉冲管理 */
	UINT32  FRF       : 1;			/**< Bit4, 帧格式，1表示SPI TI 模式 */
	UINT32  ERRIE     : 1;			/**< Bit5, 错误中断使能，1表示使能 RXNE 中断 */
	UINT32  RXNEIE    : 1;			/**< Bit6, 接收缓冲区非空中断使能,1表示使能 RXNE 中断 */
	UINT32  TXEIE     : 1;			/**< Bit7, 发送缓冲区空中断使能，1表示使能 TXE 中断 */
	UINT32	DS		  : 4;			/**<　BIT8~11，数据长度 */
	UINT32	FRXTH	  : 1;			/**< BIT12，FIFO接收阈值 */
	UINT32	LDMA_RX	  : 1;			/**< BIT13，最后一次DMA接收传输，1表示传输的所有数据为奇校验 */
	UINT32	LDMA_TX	  : 1;			/**< BIT14，最后一次DMA发送传输，1表示传输的所有数据为奇校验 */
	UINT32  Rsvd2     : 17;			/**< Bit15~31, 保留 */
}SpiCr2BitType;

/** SPI 控制寄存器 2定义 */
typedef union
{
	UINT32  all;					/**< SPI 控制寄存器 2所有位 */
	SpiCr2BitType  bit;				/**< SPI 控制寄存器 2位定义	*/
}SpiCr2Type;

/** SPI 状态寄存器位定义 */
typedef struct
{ 
	UINT16  RXNE      	: 1;			/**< Bit0, 接收缓冲区非空，1表示接收缓冲区非空 */
	UINT16  TXE       	: 1;			/**< Bit1, 发送缓冲区为空，1表示发送缓冲区为空 */
	UINT16  CHSIDE    	: 1;			/**< Bit2, 通道信息，1表示发送或接收右通道信息 */
	UINT16  UDR       	: 1;			/**< Bit3, 下溢标志，1表示发生下溢 */
	UINT16  CRCERR    	: 1;			/**< Bit4, CRC 错误标志，1表示接收到的 CRC 值与 SPI_RXCRCR 值不匹配 */
	UINT16  MODF      	: 1;			/**< Bit5, 模式故障,1表示发生模式故障 */
	UINT16  OVR       	: 1;			/**< Bit6, 上溢标志，1表示发生上溢 */	
	UINT16  BSY       	: 1;			/**< Bit7, 忙标志，1表示SPI（或 I2S）忙于通信或者发送缓冲区不为空 */
	UINT16  FRE       	: 1;			/**< Bit8, 帧格式错误，1表示出现帧格式错误 */	
	UINT16	FRLVL		: 2;			/**< Bit9~10, FIFO接收级别 */
	UINT16	FTLVL		: 2;			/**< Bit11~12, FIFO发送级别 */
	UINT16  Rsvd1     	: 3;			/**< Bit13~15, 保留 */
}SpiSrBitType;

/** SPI 状态寄存器定义 */
typedef union
{	
	UINT16  all;				/**< SPI 状态寄存器所有位 */
	SpiSrBitType  bit;			/**< SPI 状态寄存器位定义	*/		   
}SpiSrType;

/** SPI 数据寄存器位定义 */
typedef struct
{ 
	UINT16  DR      : 16;			/**< Bit0~15, 数据寄存器 */
	UINT32	Rsvd1	: 16;			/**< Bit16~31，保留 */
}SpiDrBitType;

/** SPI 数据寄存器定义 */
typedef union
{	
	UINT16  all;				/**< SPI 数据寄存器所有位 */
	SpiDrBitType  bit;			/**< SPI 数据寄存器位定义	*/
}SpiDrType;

/** SPI RX CRC 寄存器位定义 */
typedef struct
{ 
	UINT32  RXCRC       : 16;		/**< Bit0~15, 接收 CRC 寄存器 */
	UINT32	Rsvd1		: 16;		/**< Bit16~31，保留 */
}SpiRxcrcrBitType;

/** SPI RX CRC 寄存器定义 */
typedef union
{
	UINT32  all;						/**< SPI RX CRC 寄存器所有位 */
	SpiRxcrcrBitType  bit;			   	/**< SPI RX CRC 寄存器位定义	*/
}SpiRxcrcrType;

/** SPI TX CRC 寄存器位定义 */
typedef struct
{ 
	UINT32  TXCRC       : 16;			/**< Bit0~15, 发送 CRC 寄存器 */
	UINT32	Rsvd1		: 16;			/**< Bit16~31，保留 */
}SpiTxcrcrBitType;

/** SPI TX CRC 寄存器定义 */
typedef union
{
	UINT32  all;						/**< SPI TX CRC 寄存器所有位 */
	SpiTxcrcrBitType  bit;	            /**< SPI TX CRC 寄存器位定义	*/
}SpiTxcrcrType;

/** SPI_I2S 配置寄存器位定义 */
typedef struct
{ 
	UINT32  CHLEN      : 1;			    	 /**< Bit0, 通道长度，0：16 位,1：32 位 */
	UINT32  DATLEN     : 2;				 	 /**< Bit1~2, 传输的数据长度 */
	UINT32  CKPOL      : 1;					 /**< Bit3, 空闲状态的时钟电平，1表示空闲状态时钟为高电平 */
	UINT32  I2SSTD     : 2;			   		 /**< Bit4~5, I2S 标准选择 */
	UINT32  Rsvd1      : 1;			   		 /**< Bit6, 保留 */
	UINT32  PCMSYNC    : 1;				 	 /**< Bit7, PCM 帧同步,1表示长帧同步 */
	UINT32  I2SCFG     : 2;				 	 /**< Bit8~9, I2S 配置模式 */	
	UINT32  I2SE       : 1;				 	 /**< Bit10, I2S 使能，1表示使能 I2S 外设 */
	UINT32  I2SMOD     : 1;				 	 /**< Bit11, I2S 模式选择，1表示选择 I2S 模式 */	
	UINT32  Rsvd2      : 20;			 	 /**< Bit12~31, 保留 */
}SpiI2scfgrBitType;

/** SPI_I2S 配置寄存器定义 */
typedef union
{
	SpiI2scfgrBitType  bit;	/**< SPI_I2S 配置寄存器位定义	*/
	UINT32  all;						/**< SPI_I2S 配置寄存器所有位 */
}SpiI2scfgrType;

/** SPI_I2S 预分频器寄存器位定义 */
typedef struct
{ 
	UINT32  I2SDIV      : 8;			  /**< Bit0~7, I2S 线性预分频器 */
	UINT32  ODD         : 1;			  /**< Bit8, 预分频器的奇数因子 */
	UINT32  MCKOE       : 1;			  /**< Bit9, 主时钟输出使能，1表示主时钟输出使能 */
	UINT32  Rsvd1       : 22;			  /**< Bit10~31, 保留 */
}SpiI2sprBitType;

/** SPI_I2S 预分频器寄存器定义 */
typedef union
{
	SpiI2sprBitType  bit;			 /**< SPI_I2S 预分频器寄存器位定义	*/
	UINT32  all;						   /**< SPI_I2S 预分频器寄存器所有位 */
}SpiI2sprType;

/** SPI寄存器 */
typedef struct
{
	SpiCr1Type			CR1;
	SpiCr2Type			CR2;

//	volatile SpiSrType	SR;
	volatile UINT16		SR;
    UINT16              res3;

	volatile UINT16		DR;
    UINT16              res4;

	UINT16				CRCPR;
	UINT16				Resvd0;
	SpiRxcrcrType		RXCRCR;
	SpiTxcrcrType		TXCRCR;
	SpiI2scfgrType	    I2SCFGR;
	SpiI2sprType		I2SPR;
}SpiType;

/** SPI寄存器地址 */
#define SPI1		((SpiType *) SPI1_BASE)
#define SPI2		((SpiType *) SPI2_BASE)
#define SPI3		((SpiType *) SPI3_BASE)




#endif
