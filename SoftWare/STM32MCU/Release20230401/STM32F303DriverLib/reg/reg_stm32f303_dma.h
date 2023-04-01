/**
  *******************************************************************
  * @file    reg_stm32f303_dma.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-18
  * @brief   STM32F303 DMA寄存器定义头文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
  
#ifndef __REG_STM32F303_DMA_H__
#define __REG_STM32F303_DMA_H__


#include "reg_stm32f303_address.h"


/** DMA中断状态寄存器位定义 */
typedef struct{
	UINT32 GIF1  : 1;  /**< 通道1全局中断标识位，0:通道1中无以下所有中断发送发生，1:通道1中发送了以下所有中断 */
	UINT32 TCIF1 : 1;  /**< 通道1传输完成标志位，0：通道1中传输完成，1：通道1中传输未完成 */
	UINT32 HTIF1 : 1;  /**< 通道1半传输标志位，0：通道1中没有完成半传输，1:通道1中完成了一次半传输 */
	UINT32 TEIF1 : 1;  /**< 通道1传输错误标识位，0:通道1中无传输错误发生，1:通道1中发送传输错误 */
    UINT32 GIF2  : 1;  /**< 通道1全局中断标识位，0:通道2中无以下所有中断发送发生，2:通道1中发送了以下所有中断 */
	UINT32 TCIF2 : 1;  /**< 通道1传输完成标志位，0：通道2中传输完成，1：通道2中传输未完成 */
	UINT32 HTIF2 : 1;  /**< 通道1半传输标志位，0：通道2中没有完成半传输，1:通道2中完成了一次半传输 */
	UINT32 TEIF2 : 1;  /**< 通道1传输错误标识位，0:通道2中无传输错误发生，1:通道2中发送传输错误 */
	UINT32 GIF3  : 1;  /**< 通道1全局中断标识位，0:通道3中无以下所有中断发送发生，1:通道3中发送了以下所有中断 */
	UINT32 TCIF3 : 1;  /**< 通道1传输完成标志位，0：通道3中传输完成，1：通道3中传输未完成 */
	UINT32 HTIF3 : 1;  /**< 通道1半传输标志位，0：通道3中没有完成半传输，1:通道3中完成了一次半传输 */
	UINT32 TEIF3 : 1;  /**< 通道1传输错误标识位，0:通道3中无传输错误发生，1:通道3中发送传输错误*/
	UINT32 GIF4  : 1;  /**< 通道1全局中断标识位，0:通道4中无以下所有中断发送发生，1:通道4中发送了以下所有中断 */
	UINT32 TCIF4 : 1;  /**< 通道1传输完成标志位，0：通道4中传输完成，1：通道4中传输未完成 */
	UINT32 HTIF4 : 1;  /**< 通道1半传输标志位，0：通道4中没有完成半传输，1:通道4中完成了一次半传输 */
	UINT32 TEIF4 : 1;  /**< 通道1传输错误标识位，0:通道4中无传输错误发生，1:通道4中发送传输错误 */
	UINT32 GIF5  : 1;  /**< 通道1全局中断标识位，0:通道5中无以下所有中断发送发生，1:通道5中发送了以下所有中断 */
	UINT32 TCIF5 : 1;  /**< 通道1传输完成标志位，0：通道5中传输完成，1：通道5中传输未完成 */
	UINT32 HTIF5 : 1;  /**< 通道1半传输标志位，0：通道5中没有完成半传输，1:通道5中完成了一次半传输 */
	UINT32 TEIF5 : 1;  /**< 通道1传输错误标识位，0:通道5中无传输错误发生，1:通道5中发送传输错误 */
	UINT32 GIF6  : 1;  /**< 通道1全局中断标识位，0:通道6中无以下所有中断发送发生，1:通道6中发送了以下所有中断 */
	UINT32 TCIF6 : 1;  /**< 通道1传输完成标志位，0：通道6中传输完成，1：通道6中传输未完成 */
	UINT32 HTIF6 : 1;  /**< 通道1半传输标志位，0：通道6中没有完成半传输，1:通道6中完成了一次半传输 */
	UINT32 TEIF6 : 1;  /**< 通道1传输错误标识位，0:通道6中无传输错误发生，1:通道6中发送传输错误 */
	UINT32 GIF7  : 1;  /**< 通道1全局中断标识位，0:通道7中无以下所有中断发送发生，1:通道7中发送了以下所有中断 */
	UINT32 TCIF7 : 1;  /**< 通道1传输完成标志位，0：通道7中传输完成，1：通道7中传输未完成 */
	UINT32 HTIF7 : 1;  /**< 通道1半传输标志位，0：通道7中没有完成半传输，1:通道7中完成了一次半传输 */
	UINT32 TEIF7 : 1;  /**< 通道1传输错误标识位，0:通道7中无传输错误发生，1:通道7中发送传输错误 */
}DmaIsrBitType;

/** DMA中断状态寄存器定义 */
typedef union
{
	UINT32 all;
	DmaIsrBitType bit;
}DmaIsrType;

/** DMA中断状态清除寄存器位定义 */
typedef struct
{
	UINT32 CGIF1   : 1;  /**< 通道1全局中断标志清除位，写1清除通道1全局中断标志 */
	UINT32 CTCIF1  : 1;  /**< 通道1传输完成中断标志清除位，写1清零清除通道1传输完成中断标志 */
	UINT32 CHTIF1  : 1;  /**< 通道1半传中断标志清除位，写1清零通道1半传中断标志 */
	UINT32 CTEIF1  : 1;  /**< 通道1传输错误中断标志清除位，写1清零通道1传输错误中断标志 */
	UINT32 CGIF2   : 1;  /**< 通道2全局中断标志清除位，写1清除通道2全局中断标志 */
	UINT32 CTCIF2  : 1;  /**< 通道2传输完成中断标志清除位，写1清零清除通道2传输完成中断标志 */
	UINT32 CHTIF2  : 1;  /**< 通道2半传中断标志清除位，写1清零通道2半传中断标志 */
	UINT32 CTEIF2  : 1;  /**< 通道2传输错误中断标志清除位，写1清零通道2传输错误中断标志 */
	UINT32 CGIF3   : 1;  /**< 通道3全局中断标志清除位，写1清除通道3全局中断标志 */
	UINT32 CTCIF3  : 1;  /**< 通道3传输完成中断标志清除位，写1清零清除通道3传输完成中断标志 */
	UINT32 CHTIF3  : 1;  /**< 通道3半传中断标志清除位，写1清零通道3半传中断标志 */
	UINT32 CTEIF3  : 1;  /**< 通道3传输错误中断标志清除位，写1清零通道3传输错误中断标志 */
	UINT32 CGIF4   : 1;  /**< 通道4全局中断标志清除位，写1清除通道4全局中断标志 */
	UINT32 CTCIF4  : 1;  /**< 通道4传输完成中断标志清除位，写1清零清除通道4传输完成中断标志 */
	UINT32 CHTIF4  : 1;  /**< 通道4半传中断标志清除位，写1清零通道4半传中断标志 */
	UINT32 CTEIF4  : 1;  /**< 通道4传输错误中断标志清除位，写1清零通道4传输错误中断标志 */
	UINT32 CGIF5   : 1;  /**< 通道5全局中断标志清除位，写1清除通道5全局中断标志 */
	UINT32 CTCIF5  : 1;  /**< 通道5传输完成中断标志清除位，写1清零清除通道5传输完成中断标志 */
	UINT32 CHTIF5  : 1;  /**< 通道5半传中断标志清除位，写1清零通道5半传中断标志 */
	UINT32 CTEIF5  : 1;  /**< 通道5传输错误中断标志清除位，写1清零通道5传输错误中断标志 */
	UINT32 CGIF6   : 1;  /**< 通道6全局中断标志清除位，写1清除通道6全局中断标志 */
	UINT32 CTCIF6  : 1;  /**< 通道6传输完成中断标志清除位，写1清零清除通道6传输完成中断标志 */
	UINT32 CHTIF6  : 1;  /**< 通道6半传中断标志清除位，写1清零通道6半传中断标志 */
	UINT32 CTEIF6  : 1;  /**< 通道6传输错误中断标志清除位，写1清零通道6传输错误中断标志 */
	UINT32 CGIF7   : 1;  /**< 通道7全局中断标志清除位，写1清除通道7全局中断标志 */
	UINT32 CTCIF7  : 1;  /**< 通道7传输完成中断标志清除位，写1清零清除通道7传输完成中断标志 */
	UINT32 CHTIF7  : 1;  /**< 通道7半传中断标志清除位，写1清零通道7半传中断标志 */
	UINT32 CTEIF7  : 1;  /**< 通道7传输错误中断标志清除位，写1清零通道7传输错误中断标志 */
}DmaIfcrBitType;

/** DMA中断状态清除寄存器位定义 */
typedef union
{
	UINT32 all;
	DmaIfcrBitType bit;
}DmaIfcrType;

/** 通道配置寄存器位定义 */
typedef struct
{
	UINT32 EN      : 1;  /**< 开启通道位，0，通道失能，1，通道使能 */
	UINT32 TCEE    : 1;  /**< 传输完成通道中断位，0：TC中断失能，1:TC中断使能 */
	UINT32 HTIE    : 1;  /**< 半传中断位，0:HT中断失能，1:HT中断使能 */
	UINT32 TEIE    : 1;  /**< 传输错误中断位，0：传输错误中断失能，1：传输错误中断使能 */
	UINT32 DIR     : 1;  /**< 数据传输方向控制位，0：从外部设备读取，1：从存储器读取 */
	UINT32 CIRC    : 1;  /**< 循环模式位，0：关闭循环模式，1：开启循环模式 */
	UINT32 PINC    : 1;  /**< 外设地址增量模式位，0：关外设地址增量模式，1：开外设地址增量模式 */
	UINT32 MINC    : 1;  /**< 存储器地址增量模式位，0:关存储器地址增量模式，0：开存储器地址增量模式 */
	UINT32 PSIZE   : 2;  /**< 外设数据位数位，00: 8-bits，01: 16-bits，10: 32-bits */
    UINT32 MSIZE   : 2;  /**< 存储器数据位数位，同上 */
	UINT32 PL      : 2;  /**< 通道优先权位，00：低，01：中，10：高，11:特别高 */
	UINT32 MEM2MEM : 1;  /**< 内存到内存模式，0：关闭MEM2MEM模式，1：开启MEM2MEM模式 */
	UINT32 RSVD1   : 17; /**< 保留 */
}DmaCcrBitType;

/** 通道配置寄存器定义 */
typedef union
{
	UINT32 all;
	DmaCcrBitType bit;
}DmaCcrType;


/** DMA通道数据寄存器位定义 */
typedef struct
{
	UINT32 NDT    : 16;  /**< 数据数量传输位 */
	UINT32 RSVD1  : 16;  /**< 保留 */
}DmaCndtrBitType;

/** DMA通道数据寄存器定义 */
typedef union
{
	UINT32          all;  
	DmaCndtrBitType bit;
}DmaCndtrType;
	
/** DMA通道外设地址寄存器位定义 */
typedef struct
{
	UINT32 PA  	: 32;   /**< 外设地址位，PSIZE为01时，PA为一字长的地址，为10时，PA位半字长的地址 */
}DmaCparBitType;

/** DMA通道外设地址寄存器定义 */
typedef union
{
	UINT32 all;  
	DmaCparBitType bit;
}DmaCparType;

/** DMA通道内存地址寄存器位定义 */
typedef struct
{
	UINT32 MA  	: 32;   /**< 内存地址位，MSIZE为01时，MA为一字长的地址，为10时，MA位半字长的地址 */
}DmaCmarBitType;

/** DMA通道内存地址寄存器定义 */
typedef union
{
	UINT32 all;  
	DmaCmarBitType bit;
}DmaCmarType;

/** DMA屏道寄存器定义 */
typedef struct
{
    DmaCcrType                CCR;   /**< DMA通道配置寄存器 */
	DmaCndtrType		      CNDTR; /**< DMA通道数据数量寄存器 */
	DmaCparType               CPAR;  /**< DMA通道外设地址寄存器 */
	DmaCmarType               CMAR;  /**< DMA通道内存地址寄存器 */
}DmaChannelType;
/** DMA中断与清零寄存器定义 */
typedef struct
{
	DmaIsrType                ISR;   /**<DMA中断状态寄存器 */
	DmaIfcrType               IFCR;  /**<DMA中断状态清除寄存器 */
}DmaType;



#define DMA1					(( DmaType *) DMA1_BASE )
#define DMA1_Channel1			(( DmaChannelType *) DMA1_Channel1_BASE )
#define DMA1_Channel2			(( DmaChannelType *) DMA1_Channel2_BASE )
#define DMA1_Channel3			(( DmaChannelType *) DMA1_Channel3_BASE )
#define DMA1_Channel4			(( DmaChannelType *) DMA1_Channel4_BASE )
#define DMA1_Channel5			(( DmaChannelType *) DMA1_Channel5_BASE )
#define DMA1_Channel6			(( DmaChannelType *) DMA1_Channel6_BASE )
#define DMA1_Channel7			(( DmaChannelType *) DMA1_Channel7_BASE )
#define DMA2					(( DmaType *) DMA2_BASE )
#define DMA2_Channel1			(( DmaChannelType *) DMA2_Channel1_BASE )
#define DMA2_Channel2			(( DmaChannelType *) DMA2_Channel2_BASE )
#define DMA2_Channel3			(( DmaChannelType *) DMA2_Channel3_BASE )
#define DMA2_Channel4			(( DmaChannelType *) DMA2_Channel4_BASE )
#define DMA2_Channel5			(( DmaChannelType *) DMA2_Channel5_BASE )

#endif	
