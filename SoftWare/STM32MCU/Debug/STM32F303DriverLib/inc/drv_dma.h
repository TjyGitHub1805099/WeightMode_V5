/**
*******************************************************************
* @file    drv_dma.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x DMA模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

#include "reg_stm32f303_dma.h"


#define DMA1_DMA2_FLAG_MASK					((UINT32)0x10000000)		//区别FALG在DMA1 还是 DMA2
#define DMA1_DMA2_IT_MASK					((UINT32)0x80000000)		//区别IT在DMA1 还是 DMA2
#define DMA_CHANNEL_IT_FLAG_MASK			((UINT32)0x70000000)		//区别DMA 具体通道号的中断状态

/** DMA中断源定义 */
#define DMA_IT_TC                         	((UINT32)0x00000002)
#define DMA_IT_HT                         	((UINT32)0x00000004)
#define DMA_IT_TE                         	((UINT32)0x00000008)

/** DMA中断状态定义 */
#define DMA1_IT_GL1                        ((UINT32)0x10000001)
#define DMA1_IT_TC1                        ((UINT32)0x10000002)
#define DMA1_IT_HT1                        ((UINT32)0x10000004)
#define DMA1_IT_TE1                        ((UINT32)0x10000008)
#define DMA1_IT_GL2                        ((UINT32)0x20000010)
#define DMA1_IT_TC2                        ((UINT32)0x20000020)
#define DMA1_IT_HT2                        ((UINT32)0x20000040)
#define DMA1_IT_TE2                        ((UINT32)0x20000080)
#define DMA1_IT_GL3                        ((UINT32)0x30000100)
#define DMA1_IT_TC3                        ((UINT32)0x30000200)
#define DMA1_IT_HT3                        ((UINT32)0x30000400)
#define DMA1_IT_TE3                        ((UINT32)0x30000800)
#define DMA1_IT_GL4                        ((UINT32)0x40001000)
#define DMA1_IT_TC4                        ((UINT32)0x40002000)
#define DMA1_IT_HT4                        ((UINT32)0x40004000)
#define DMA1_IT_TE4                        ((UINT32)0x40008000)
#define DMA1_IT_GL5                        ((UINT32)0x50010000)
#define DMA1_IT_TC5                        ((UINT32)0x50020000)
#define DMA1_IT_HT5                        ((UINT32)0x50040000)
#define DMA1_IT_TE5                        ((UINT32)0x50080000)
#define DMA1_IT_GL6                        ((UINT32)0x60100000)
#define DMA1_IT_TC6                        ((UINT32)0x60200000)
#define DMA1_IT_HT6                        ((UINT32)0x60400000)
#define DMA1_IT_TE6                        ((UINT32)0x60800000)
#define DMA1_IT_GL7                        ((UINT32)0x71000000)
#define DMA1_IT_TC7                        ((UINT32)0x72000000)
#define DMA1_IT_HT7                        ((UINT32)0x74000000)
#define DMA1_IT_TE7                        ((UINT32)0x78000000)

#define DMA2_IT_GL1                        ((UINT32)0x90000001)
#define DMA2_IT_TC1                        ((UINT32)0x90000002)
#define DMA2_IT_HT1                        ((UINT32)0x90000004)
#define DMA2_IT_TE1                        ((UINT32)0x90000008)
#define DMA2_IT_GL2                        ((UINT32)0xA0000010)
#define DMA2_IT_TC2                        ((UINT32)0xA0000020)
#define DMA2_IT_HT2                        ((UINT32)0xA0000040)
#define DMA2_IT_TE2                        ((UINT32)0xA0000080)
#define DMA2_IT_GL3                        ((UINT32)0xB0000100)
#define DMA2_IT_TC3                        ((UINT32)0xB0000200)
#define DMA2_IT_HT3                        ((UINT32)0xB0000400)
#define DMA2_IT_TE3                        ((UINT32)0xB0000800)
#define DMA2_IT_GL4                        ((UINT32)0xC0001000)
#define DMA2_IT_TC4                        ((UINT32)0xC0002000)
#define DMA2_IT_HT4                        ((UINT32)0xC0004000)
#define DMA2_IT_TE4                        ((UINT32)0xC0008000)
#define DMA2_IT_GL5                        ((UINT32)0xD0010000)
#define DMA2_IT_TC5                        ((UINT32)0xD0020000)
#define DMA2_IT_HT5                        ((UINT32)0xD0040000)
#define DMA2_IT_TE5                        ((UINT32)0xD0080000)

/** DMA标志状态定义 */
#define DMA1_FLAG_GL1                      ((UINT32)0x00000001)
#define DMA1_FLAG_TC1                      ((UINT32)0x00000002)
#define DMA1_FLAG_HT1                      ((UINT32)0x00000004)
#define DMA1_FLAG_TE1                      ((UINT32)0x00000008)
#define DMA1_FLAG_GL2                      ((UINT32)0x00000010)
#define DMA1_FLAG_TC2                      ((UINT32)0x00000020)
#define DMA1_FLAG_HT2                      ((UINT32)0x00000040)
#define DMA1_FLAG_TE2                      ((UINT32)0x00000080)
#define DMA1_FLAG_GL3                      ((UINT32)0x00000100)
#define DMA1_FLAG_TC3                      ((UINT32)0x00000200)
#define DMA1_FLAG_HT3                      ((UINT32)0x00000400)
#define DMA1_FLAG_TE3                      ((UINT32)0x00000800)
#define DMA1_FLAG_GL4                      ((UINT32)0x00001000)
#define DMA1_FLAG_TC4                      ((UINT32)0x00002000)
#define DMA1_FLAG_HT4                      ((UINT32)0x00004000)
#define DMA1_FLAG_TE4                      ((UINT32)0x00008000)
#define DMA1_FLAG_GL5                      ((UINT32)0x00010000)
#define DMA1_FLAG_TC5                      ((UINT32)0x00020000)
#define DMA1_FLAG_HT5                      ((UINT32)0x00040000)
#define DMA1_FLAG_TE5                      ((UINT32)0x00080000)
#define DMA1_FLAG_GL6                      ((UINT32)0x00100000)
#define DMA1_FLAG_TC6                      ((UINT32)0x00200000)
#define DMA1_FLAG_HT6                      ((UINT32)0x00400000)
#define DMA1_FLAG_TE6                      ((UINT32)0x00800000)
#define DMA1_FLAG_GL7                      ((UINT32)0x01000000)
#define DMA1_FLAG_TC7                      ((UINT32)0x02000000)
#define DMA1_FLAG_HT7                      ((UINT32)0x04000000)
#define DMA1_FLAG_TE7                      ((UINT32)0x08000000)

#define DMA2_FLAG_GL1                      ((UINT32)0x10000001)
#define DMA2_FLAG_TC1                      ((UINT32)0x10000002)
#define DMA2_FLAG_HT1                      ((UINT32)0x10000004)
#define DMA2_FLAG_TE1                      ((UINT32)0x10000008)
#define DMA2_FLAG_GL2                      ((UINT32)0x10000010)
#define DMA2_FLAG_TC2                      ((UINT32)0x10000020)
#define DMA2_FLAG_HT2                      ((UINT32)0x10000040)
#define DMA2_FLAG_TE2                      ((UINT32)0x10000080)
#define DMA2_FLAG_GL3                      ((UINT32)0x10000100)
#define DMA2_FLAG_TC3                      ((UINT32)0x10000200)
#define DMA2_FLAG_HT3                      ((UINT32)0x10000400)
#define DMA2_FLAG_TE3                      ((UINT32)0x10000800)
#define DMA2_FLAG_GL4                      ((UINT32)0x10001000)
#define DMA2_FLAG_TC4                      ((UINT32)0x10002000)
#define DMA2_FLAG_HT4                      ((UINT32)0x10004000)
#define DMA2_FLAG_TE4                      ((UINT32)0x10008000)
#define DMA2_FLAG_GL5                      ((UINT32)0x10010000)
#define DMA2_FLAG_TC5                      ((UINT32)0x10020000)
#define DMA2_FLAG_HT5                      ((UINT32)0x10040000)
#define DMA2_FLAG_TE5                      ((UINT32)0x10080000)



/** DMA数据传输方向 */
typedef enum DmaDirType
{
	DMA_DIR_PERIPH_TO_MEM = 0,			/**< 外设到内存 */
	DMA_DIR_MEM_TO_PERIPH				/**< 内存到外设 */
}enumDmaDirType;

/** 内存到内存模式定义 */
typedef enum DmaMemToMemType
{
	DMA_MEM_TO_MEM_DISALE = 0,			/**< 内存到内存模式禁止 */
	DMA_MEM_TO_MEM_ENABLE				/**< 内存到内存模式使能 */
}enumDmaMemToMemType;

/** DMA传输数据流数据宽度定义 */
typedef enum DmaDataWidthType
{
	DMA_DATA_WIDTH_BYTE = 0,			/**< 字节传输 */
	DMA_DATA_WIDTH_HALF_WORD,			/**< 半字传输 */
	DMA_DATA_WIDTH_WORD					/**< 字传输 */
}enumDmaDataWidthType;

/** DMA循环模式定义 */
typedef enum DmaCircModeType
{
	DMA_CIRC_MODE_DISABLE = 0,			/**< 禁止循环模式 */
	DMA_CIRC_MODE_ENABLE				/**< 使能循环模式 */
}enumDmaCircModeType;

/** MDA通道优先级定义 */
typedef enum DmaChannelPriorityType
{
	DMA_CHANNEL_PRIORITY_LOW	= 0,	/**< 低优先级 */
	DMA_CHANNEL_PRIORITY_MEDIUM,		/**< 中优先级 */
	DMA_CHANNEL_PRIORITY_HIGH,			/**< 高优先级 */
	DMA_CHANNEL_PRIORITY_VERY_HIGH		/**< 非常高优先级 */
}enumDmaChannelPriorityType;

/** 内存和外设地址递增定义 */
typedef enum DmaAddrIncType
{
	DMA_ADDR_INC_DISABLE = 0,			/** 禁止地址递增 */
	DMA_ADDR_INC_ENABLE					/** 使能地址递增 */
}enumDmaAddrIncType;


extern void drv_dma_stream_deinit( DmaChannelType *pDmaChannel );
extern void drv_dma_stream_init( DmaChannelType *pDmaChannel, UINT32 MemAddr, UINT32 PeriphAddr, UINT16 Length, enumDmaCircModeType CircMode,
						  enumDmaChannelPriorityType DmaChannelPriority, enumDmaDirType DmaDirection, enumDmaDataWidthType DataWidth );
extern void drv_dma_stream_enable( DmaChannelType *pDmaChannel );
extern void drv_dma_stream_disable( DmaChannelType *pDmaChannel );
extern void drv_dma_stream_it_enable( DmaChannelType *pDmaChannel, UINT32 DmaIt );
extern void drv_dma_stream_it_disable( DmaChannelType *pDmaChannel, UINT32 DmaIt );
extern void drv_dma_stream_start_periph_to_mem( DmaChannelType *pDmaChannel, UINT32 DstAddress, UINT16 Length );
extern void drv_dma_stream_start_mem_to_periph( DmaChannelType *pDmaChannel, UINT32 SrcAddress, UINT16 Length );
extern UINT16 drv_dma_stream_get_left_length( DmaChannelType *pDmaChannel );
extern FuncState drv_dma_stream_get_enable_status( DmaChannelType *pDmaChannel );
extern FlagStatus drv_dma_stream_get_flag_status( UINT32 DmaFlag );
extern ITStatus drv_dma_stream_get_it_status( DmaChannelType *pDmaChannel, UINT32 DmaItStatus );
extern void drv_dma_stream_clear_flag_status( UINT32 DmaFlag );
extern void drv_dma_stream_clear_it_pending_bit( UINT32 DmaIt );
extern UINT8 drv_dma_wait_to_be_set( DmaChannelType *pDmaChannel );
extern void drv_dma_set_mem_addr_length( DmaChannelType *pDmaChannel, UINT32 MemAddr, UINT16 Length );


#endif
