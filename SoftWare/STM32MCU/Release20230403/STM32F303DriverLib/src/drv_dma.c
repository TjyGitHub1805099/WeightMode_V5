/**
*******************************************************************
* @file    drv_dma.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x DMA模块驱动程序
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#include "drv_dma.h"

/**
* @brief  复位DMA流寄存器为默认值.
* @param  pDmaChannel: 要复位的DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @retval 无
*/
void drv_dma_stream_deinit( DmaChannelType *pDmaChannel )
{
	pDmaChannel->CCR.bit.EN = 0;				// 关闭DMA   
	pDmaChannel->CCR.all  = 0;					// 控制寄存器  									
	pDmaChannel->CNDTR.bit.NDT = 0;					// 数据项数寄存器  
	pDmaChannel->CPAR.all  = 0;					// 外设地址寄存器  
	pDmaChannel->CMAR.all = 0;					// 存储器地址寄存器  	
	
	// 清数据流相应标志位，写1清零  
	if( pDmaChannel == DMA1_Channel1 )
	{
		DMA1->IFCR.all = (UINT32)0x0F << 0;							
	}
	else if( pDmaChannel == DMA1_Channel2 )
	{
		DMA1->IFCR.all = (UINT32)0x0F << 4;					
	}
	else if( pDmaChannel == DMA1_Channel3 )
	{
		DMA1->IFCR.all = (UINT32)0x0F << 8;					
	}
	else if( pDmaChannel == DMA1_Channel4 )
	{
		DMA1->IFCR.all = (UINT32)0x0F << 12;					
	}
	else if( pDmaChannel == DMA1_Channel5 )
	{
		DMA1->IFCR.all = (UINT32)0x0F << 16;
	}
	else if( pDmaChannel == DMA1_Channel6 )
	{
		DMA1->IFCR.all = (UINT32)0x0F << 20;
	}
	else if( pDmaChannel == DMA1_Channel7 )
	{
		DMA1->IFCR.all = (UINT32)0x0F << 24;
	}
	else if( pDmaChannel == DMA2_Channel1 )
	{
		DMA2->IFCR.all = (UINT32)0x0F << 0;
	}
	else if( pDmaChannel == DMA2_Channel2 )
	{
		DMA2->IFCR.all = (UINT32)0x0F << 4;
	}
	else if( pDmaChannel == DMA2_Channel3 )
	{
		DMA2->IFCR.all = (UINT32)0x0F << 8;
	}
	else if( pDmaChannel == DMA2_Channel4 )
	{
		DMA2->IFCR.all = (UINT32)0x0F << 12;
	}
	else 
	{
		if( pDmaChannel == DMA2_Channel5 )
		{
			DMA2->IFCR.all = (UINT32)0x0F << 16;
		}
	}
}

/**
* @brief  DMA通道等待可配置
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @retval 0：正常 1：等待超时
*/
UINT8 drv_dma_wait_to_be_set( DmaChannelType *pDmaChannel )
{	
	UINT32 l_DmaStatus = 0xFFFFFFFF, l_DmaWaitTime = 0xFFFFFFFF;
	
	while( l_DmaWaitTime-- )
	{
		l_DmaStatus = pDmaChannel->CCR.all;							 
		l_DmaStatus &= 0x00000001;										 
		if( l_DmaStatus == 0 )
		{
			break;
		}
	
	}
	if( l_DmaWaitTime == 0)
	{
		return 1;			// 等待超时，返回1  
	}
	else
	{
		return 0;				
	}
}

/**
* @brief  DMA数据流初始化
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @param  DmaDirection: 数据流数据方向
* @param  MemAddr: 内存地址，对于使用时要重新设置地址的，可以配置为0
* @param  PeriphAddr: 外设地址
* @param  Length: 传输数据个数，对于使用时要重新设置长度的，可以配置为0
* @param  DataWidth: 传输数据宽度
* @param  CircMode: 循环模式
* @param  DmaChannelPriority 通道优先级
* @retval 无
*/
void drv_dma_stream_init( DmaChannelType *pDmaChannel, UINT32 MemAddr, UINT32 PeriphAddr, UINT16 Length, enumDmaCircModeType CircMode,
						  enumDmaChannelPriorityType DmaChannelPriority, enumDmaDirType DmaDirection, enumDmaDataWidthType DataWidth )
{
	drv_dma_stream_deinit( pDmaChannel );
	// 配置DMA基本参数  
	pDmaChannel->CCR.bit.MEM2MEM = (UINT16)DMA_MEM_TO_MEM_DISALE;	//禁止内存到内存模式
	pDmaChannel->CCR.bit.CIRC = (UINT16)CircMode;					//循环模式配置
	pDmaChannel->CCR.bit.DIR = (UINT16)DmaDirection;				//数据方向				
	pDmaChannel->CCR.bit.MINC = (UINT16)DMA_ADDR_INC_ENABLE;		//内存地址递增
	pDmaChannel->CCR.bit.PINC = (UINT16)DMA_ADDR_INC_DISABLE;		//外设地址禁止递增
	pDmaChannel->CCR.bit.MSIZE = (UINT16)DataWidth;					//内存数据宽度配置
	pDmaChannel->CCR.bit.PSIZE = (UINT16)DataWidth;					//外设数据宽度
	pDmaChannel->CCR.bit.PL = (UINT16)DmaChannelPriority;			//通道优先级
	
	pDmaChannel->CNDTR.bit.NDT = Length;		//数据个数
	pDmaChannel->CMAR.all = MemAddr;		//内存地址
	pDmaChannel->CPAR.all = PeriphAddr;		//外设地址
}

/**
* @brief  使能DMA流.
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @note   这个函数可以用于暂停操作。
* @note   配置DMA流并使能流后，推荐检查下DMA流是否真的被使能。如果配置参数错误，
*		  流将维持禁止状态。禁止DMA流后，推荐检查是否真的被禁止，因为要等到当前
*		  一个数据的传输完成。
* @retval 无
*/
void drv_dma_stream_enable( DmaChannelType *pDmaChannel )
{ 
	pDmaChannel->CCR.bit.EN = 1;			// 使能DMA流
}

/**
* @brief  使能DMA流.
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @note   这个函数可以用于暂停操作。
* @note   配置DMA流并使能流后，推荐检查下DMA流是否真的被使能。如果配置参数错误，
*		  流将维持禁止状态。禁止DMA流后，推荐检查是否真的被禁止，因为要等到当前
*		  一个数据的传输完成。
* @retval 无
*/
void drv_dma_stream_disable( DmaChannelType *pDmaChannel )
{ 
	pDmaChannel->CCR.bit.EN = 0;			// 禁止DMA流
}

/**
* @brief  DMA内存地址和传输长度设置
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @param  MemAddr: 内存地址，对于使用时要重新设置地址的，可以配置为0
* @param  Length: 传输数据个数，对于使用时要重新设置长度的，可以配置为0
* @retval 无
*/
void drv_dma_set_mem_addr_length( DmaChannelType *pDmaChannel, UINT32 MemAddr, UINT16 Length )
{
    pDmaChannel->CNDTR.bit.NDT = Length;		//数据个数
    pDmaChannel->CMAR.all = MemAddr;		//内存地址
}

/**
* @brief  获取DMA流使能或禁止状态.
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @retval 使能或禁止状态.
*/
FuncState drv_dma_stream_get_enable_status( DmaChannelType *pDmaChannel )
{
	UINT32 l_DmaCcrStaus = 0;
	
	l_DmaCcrStaus = pDmaChannel->CCR.all;
	l_DmaCcrStaus &= 0x00000001;
	if( l_DmaCcrStaus == 1 )
	{
		return ENABLE;
	}
	else
	{
		return DISABLE;
	}
}

/**
* @brief  启动DMA数据传输.
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @param  DstAddress: 数据目标地址.
* @param  Length: 数据长度，传输数据个数.
* @retval 无
*/
void drv_dma_stream_start_periph_to_mem( DmaChannelType *pDmaChannel, UINT32 DstAddress, UINT16 Length )
{
    DmaCcrType l_CcrReg;
    pDmaChannel->CCR.bit.EN = 0;
    while (1)
    {
        l_CcrReg.all = pDmaChannel->CCR.all;
        if (l_CcrReg.bit.EN == 0)
        {
            break;
        }
    }

    pDmaChannel->CMAR.all = DstAddress;
	pDmaChannel->CNDTR.bit.NDT = Length;					
	pDmaChannel->CCR.bit.EN = 1;
}

/**
* @brief  启动DMA数据传输.
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @param  SrcAddress: 数据源地址.
* @param  Length: 数据长度，传输数据个数.
* @retval 无
*/
void drv_dma_stream_start_mem_to_periph( DmaChannelType *pDmaChannel, UINT32 SrcAddress, UINT16 Length )
{ 
    DmaCcrType l_CcrReg;
    pDmaChannel->CCR.bit.EN = 0;
    while (1)
    {
        l_CcrReg.all = pDmaChannel->CCR.all;
        if (l_CcrReg.bit.EN == 0)
        {
            break;
        }
    }

    pDmaChannel->CMAR.all = SrcAddress;
	pDmaChannel->CNDTR.bit.NDT = Length;					
	pDmaChannel->CCR.bit.EN = 1;
}

/**
* @brief  读取DMA传输剩余数据个数.
* @param  pDmaChannel: DMA通道，可以是下面的一个.
*            @arg DMA1_Channel1
*            @arg DMA1_Channel2
*            @arg DMA1_Channel3
*            @arg DMA1_Channel4
*            @arg DMA1_Channel5
*            @arg DMA1_Channel6
*            @arg DMA1_Channel7
*            @arg DMA2_Channel1
*            @arg DMA2_Channel2
*            @arg DMA2_Channel3
*            @arg DMA2_Channel4
*            @arg DMA2_Channel5
* @retval 剩余没有传输的数据个数.
*/
UINT16 drv_dma_stream_get_left_length( DmaChannelType *pDmaChannel )
{
	DmaCndtrType l_ReturnValue;
	
	 l_ReturnValue.all= pDmaChannel->CNDTR.all;
	return ( (UINT16)l_ReturnValue.bit.NDT );
}

/**
* @brief  获取DMA流标志状态.
* @param  DmaFlag: 要获取的标志，可以是下面值中的一个: x:1~7 y:1~5
*            @arg DMA1_FLAG_GLx
*            @arg DMA1_FLAG_TCx
*            @arg DMA1_FLAG_HTx
*            @arg DMA1_FLAG_TEx
*            @arg DMA2_FLAG_GLy
*            @arg DMA2_FLAG_TCy
*            @arg DMA2_FLAG_HTy
*            @arg DMA2_FLAG_TEy
* @retval 新状态.
*/
FlagStatus drv_dma_stream_get_flag_status( UINT32 DmaFlag )
{
	UINT8 l_FlagRegPos = 0;
	UINT32 l_Temp = 0;
	
	l_Temp = DmaFlag & 0x10000000;		//BIT28为DMA1 DMA2判断位
	if( l_Temp != 0 )
	{
		l_FlagRegPos = 1;		//DMA2
	}
	else
	{
		l_FlagRegPos = 0;		//DMA1
	}
	if( l_FlagRegPos != 0 )
	{
		l_FlagRegPos = DMA2->ISR.all;	//读状态寄存器
	}
	else
	{
		l_FlagRegPos = DMA1->ISR.all;
	}
	if(( l_FlagRegPos & DmaFlag ) != (UINT16)RESET )
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清DMA流挂起标志.
* @param  DmaFlag: 要获取的标志，可以是下面值中的一个: x:1~7 y:1~5
*            @arg DMA1_FLAG_GLx
*            @arg DMA1_FLAG_TCx
*            @arg DMA1_FLAG_HTx
*            @arg DMA1_FLAG_TEx
*            @arg DMA2_FLAG_GLy
*            @arg DMA2_FLAG_TCy
*            @arg DMA2_FLAG_HTy
*            @arg DMA2_FLAG_TEy
* @retval 无
*/
void drv_dma_stream_clear_flag_status( UINT32 DmaFlag )
{ 
	UINT8 l_FlagRegPos = 0;
	UINT32 l_Temp = 0;
	
	l_Temp = DmaFlag & 0x10000000;		//BIT28为DMA1 DMA2判断位
	if( l_Temp != 0 )
	{
		l_FlagRegPos = 1;		//DMA2
	}
	else
	{
		l_FlagRegPos = 0;		//DMA1
	}
	if( l_FlagRegPos != 0 )
	{
		DMA2->IFCR.all = DmaFlag;		//写1清0 写0无效
	}
	else
	{
		DMA1->IFCR.all = DmaFlag;
	}
}

/**
* @brief  DMA流中断使能.
* @param  pDmaChannel: 要控制的DMA流.
* @param  DmaIt: 要使能或禁止的中断源，可以是下面值的组合:
*     			@arg DMA_IT_TC: Transfer complete interrupt mask
*     			@arg DMA_IT_HT: Half transfer interrupt mask
*     			@arg DMA_IT_TE: Transfer error interrupt mask
* @retval 无
*/
void drv_dma_stream_it_enable( DmaChannelType *pDmaChannel, UINT32 DmaIt )
{
	pDmaChannel->CCR.all |= DmaIt;
}

/**
* @brief  DMA流中断禁止.
* @param  pDmaChannel: 要控制的DMA流.
* @param  DmaIt: 要使能或禁止的中断源，可以是下面值的组合:
*     			@arg DMA_IT_TC: Transfer complete interrupt mask
*     			@arg DMA_IT_HT: Half transfer interrupt mask
*     			@arg DMA_IT_TE: Transfer error interrupt mask
* @retval 无
*/
void drv_dma_stream_it_disable( DmaChannelType *pDmaChannel, UINT32 DmaIt )
{
	pDmaChannel->CCR.all &= (UINT32)~DmaIt;
}

/**
  * @brief  获取DMA流中断状态.
  * @param  DmaItStatus: DMA中断源，可以是下面值中的一个:
  *     @arg DMA1_IT_GL1: DMA1 Channel1 global interrupt.
  *     @arg DMA1_IT_TC1: DMA1 Channel1 transfer complete interrupt.
  *     @arg DMA1_IT_HT1: DMA1 Channel1 half transfer interrupt.
  *     @arg DMA1_IT_TE1: DMA1 Channel1 transfer error interrupt.
  *     @arg DMA1_IT_GL2: DMA1 Channel2 global interrupt.
  *     @arg DMA1_IT_TC2: DMA1 Channel2 transfer complete interrupt.
  *     @arg DMA1_IT_HT2: DMA1 Channel2 half transfer interrupt.
  *     @arg DMA1_IT_TE2: DMA1 Channel2 transfer error interrupt.
  *     @arg DMA1_IT_GL3: DMA1 Channel3 global interrupt.
  *     @arg DMA1_IT_TC3: DMA1 Channel3 transfer complete interrupt.
  *     @arg DMA1_IT_HT3: DMA1 Channel3 half transfer interrupt.
  *     @arg DMA1_IT_TE3: DMA1 Channel3 transfer error interrupt.
  *     @arg DMA1_IT_GL4: DMA1 Channel4 global interrupt.
  *     @arg DMA1_IT_TC4: DMA1 Channel4 transfer complete interrupt.
  *     @arg DMA1_IT_HT4: DMA1 Channel4 half transfer interrupt.
  *     @arg DMA1_IT_TE4: DMA1 Channel4 transfer error interrupt.
  *     @arg DMA1_IT_GL5: DMA1 Channel5 global interrupt.
  *     @arg DMA1_IT_TC5: DMA1 Channel5 transfer complete interrupt.
  *     @arg DMA1_IT_HT5: DMA1 Channel5 half transfer interrupt.
  *     @arg DMA1_IT_TE5: DMA1 Channel5 transfer error interrupt.
  *     @arg DMA1_IT_GL6: DMA1 Channel6 global interrupt.
  *     @arg DMA1_IT_TC6: DMA1 Channel6 transfer complete interrupt.
  *     @arg DMA1_IT_HT6: DMA1 Channel6 half transfer interrupt.
  *     @arg DMA1_IT_TE6: DMA1 Channel6 transfer error interrupt.
  *     @arg DMA1_IT_GL7: DMA1 Channel7 global interrupt.
  *     @arg DMA1_IT_TC7: DMA1 Channel7 transfer complete interrupt.
  *     @arg DMA1_IT_HT7: DMA1 Channel7 half transfer interrupt.
  *     @arg DMA1_IT_TE7: DMA1 Channel7 transfer error interrupt.
  *     @arg DMA2_IT_GL1: DMA2 Channel1 global interrupt.
  *     @arg DMA2_IT_TC1: DMA2 Channel1 transfer complete interrupt.
  *     @arg DMA2_IT_HT1: DMA2 Channel1 half transfer interrupt.
  *     @arg DMA2_IT_TE1: DMA2 Channel1 transfer error interrupt.
  *     @arg DMA2_IT_GL2: DMA2 Channel2 global interrupt.
  *     @arg DMA2_IT_TC2: DMA2 Channel2 transfer complete interrupt.
  *     @arg DMA2_IT_HT2: DMA2 Channel2 half transfer interrupt.
  *     @arg DMA2_IT_TE2: DMA2 Channel2 transfer error interrupt.
  *     @arg DMA2_IT_GL3: DMA2 Channel3 global interrupt.
  *     @arg DMA2_IT_TC3: DMA2 Channel3 transfer complete interrupt.
  *     @arg DMA2_IT_HT3: DMA2 Channel3 half transfer interrupt.
  *     @arg DMA2_IT_TE3: DMA2 Channel3 transfer error interrupt.
  *     @arg DMA2_IT_GL4: DMA2 Channel4 global interrupt.
  *     @arg DMA2_IT_TC4: DMA2 Channel4 transfer complete interrupt.
  *     @arg DMA2_IT_HT4: DMA2 Channel4 half transfer interrupt.
  *     @arg DMA2_IT_TE4: DMA2 Channel4 transfer error interrupt.
  *     @arg DMA2_IT_GL5: DMA2 Channel5 global interrupt.
  *     @arg DMA2_IT_TC5: DMA2 Channel5 transfer complete interrupt.
  *     @arg DMA2_IT_HT5: DMA2 Channel5 half transfer interrupt.
  *     @arg DMA2_IT_TE5: DMA2 Channel5 transfer error interrupt.
  * @retval 新的状态.
*/
ITStatus drv_dma_stream_get_it_status( DmaChannelType *pDmaChannel, UINT32 DmaItStatus )
{
	DmaType* DMAy;
	UINT32 l_DmaPos = 0, l_ChannelSourcePos = 0, l_DmaCcrStatus = 0;	//DMAx标志，DMACHANNEL标志，CCR状态用于读出CCR中使能的中断
	UINT8 l_FlagStatus = 0, l_ItStatus = 0;			//标志位状态，中断状态

	l_DmaPos = DmaItStatus & DMA1_DMA2_IT_MASK;		//若结果不为0，则查询的是属于DMA2的中断状态，反之为DMA1
	l_ChannelSourcePos = ( DMA_CHANNEL_IT_FLAG_MASK & DmaItStatus ) >> 28;	//BIT28~BIT30为通道号
	//判断标志位
	if( l_DmaPos != 0 )
	{
		DMAy = DMA2;		//属于DMA2
	}
	else
	{
		DMAy = DMA1;		//属于DMA1
	}
	l_DmaPos = DMAy->ISR.all;
	if(( l_DmaPos & DmaItStatus ) != (UINT32)RESET )
	{
		l_FlagStatus = 1;		//查询到标志位已经置起
	}
	else
	{
		l_FlagStatus = 0;
	}
	//判断中断
	DmaItStatus = DmaItStatus >> ( ( l_ChannelSourcePos - 1 ) * 4 );	
	l_DmaCcrStatus = pDmaChannel->CCR.all;
	l_DmaCcrStatus &= 0x0000000E;								//EN位屏蔽掉
	if(( DmaItStatus & l_DmaCcrStatus ) != (UINT32)RESET )
	{
		l_ItStatus = 1;			//查询到相应的中断也打开
	}
	else
	{
		l_ItStatus = 0;
	}
	
	if(( l_ItStatus == 1 ) && ( l_FlagStatus == 1 ))
	{
		return SET;				//中断打开 且标志位置起
	}
	else
	{
		return RESET;
	}
}

/**
  * @brief  清中断挂起位.
  * @param  pDmaChannel: 要控制的DMA流.
  * @param  DmaIt: 要清除的中断挂起位，可以是下面值的组合：
  *     @arg DMA1_IT_GL1: DMA1 Channel1 global interrupt.
  *     @arg DMA1_IT_TC1: DMA1 Channel1 transfer complete interrupt.
  *     @arg DMA1_IT_HT1: DMA1 Channel1 half transfer interrupt.
  *     @arg DMA1_IT_TE1: DMA1 Channel1 transfer error interrupt.
  *     @arg DMA1_IT_GL2: DMA1 Channel2 global interrupt.
  *     @arg DMA1_IT_TC2: DMA1 Channel2 transfer complete interrupt.
  *     @arg DMA1_IT_HT2: DMA1 Channel2 half transfer interrupt.
  *     @arg DMA1_IT_TE2: DMA1 Channel2 transfer error interrupt.
  *     @arg DMA1_IT_GL3: DMA1 Channel3 global interrupt.
  *     @arg DMA1_IT_TC3: DMA1 Channel3 transfer complete interrupt.
  *     @arg DMA1_IT_HT3: DMA1 Channel3 half transfer interrupt.
  *     @arg DMA1_IT_TE3: DMA1 Channel3 transfer error interrupt.
  *     @arg DMA1_IT_GL4: DMA1 Channel4 global interrupt.
  *     @arg DMA1_IT_TC4: DMA1 Channel4 transfer complete interrupt.
  *     @arg DMA1_IT_HT4: DMA1 Channel4 half transfer interrupt.
  *     @arg DMA1_IT_TE4: DMA1 Channel4 transfer error interrupt.
  *     @arg DMA1_IT_GL5: DMA1 Channel5 global interrupt.
  *     @arg DMA1_IT_TC5: DMA1 Channel5 transfer complete interrupt.
  *     @arg DMA1_IT_HT5: DMA1 Channel5 half transfer interrupt.
  *     @arg DMA1_IT_TE5: DMA1 Channel5 transfer error interrupt.
  *     @arg DMA1_IT_GL6: DMA1 Channel6 global interrupt.
  *     @arg DMA1_IT_TC6: DMA1 Channel6 transfer complete interrupt.
  *     @arg DMA1_IT_HT6: DMA1 Channel6 half transfer interrupt.
  *     @arg DMA1_IT_TE6: DMA1 Channel6 transfer error interrupt.
  *     @arg DMA1_IT_GL7: DMA1 Channel7 global interrupt.
  *     @arg DMA1_IT_TC7: DMA1 Channel7 transfer complete interrupt.
  *     @arg DMA1_IT_HT7: DMA1 Channel7 half transfer interrupt.
  *     @arg DMA1_IT_TE7: DMA1 Channel7 transfer error interrupt.
  *     @arg DMA2_IT_GL1: DMA2 Channel1 global interrupt.
  *     @arg DMA2_IT_TC1: DMA2 Channel1 transfer complete interrupt.
  *     @arg DMA2_IT_HT1: DMA2 Channel1 half transfer interrupt.
  *     @arg DMA2_IT_TE1: DMA2 Channel1 transfer error interrupt.
  *     @arg DMA2_IT_GL2: DMA2 Channel2 global interrupt.
  *     @arg DMA2_IT_TC2: DMA2 Channel2 transfer complete interrupt.
  *     @arg DMA2_IT_HT2: DMA2 Channel2 half transfer interrupt.
  *     @arg DMA2_IT_TE2: DMA2 Channel2 transfer error interrupt.
  *     @arg DMA2_IT_GL3: DMA2 Channel3 global interrupt.
  *     @arg DMA2_IT_TC3: DMA2 Channel3 transfer complete interrupt.
  *     @arg DMA2_IT_HT3: DMA2 Channel3 half transfer interrupt.
  *     @arg DMA2_IT_TE3: DMA2 Channel3 transfer error interrupt.
  *     @arg DMA2_IT_GL4: DMA2 Channel4 global interrupt.
  *     @arg DMA2_IT_TC4: DMA2 Channel4 transfer complete interrupt.
  *     @arg DMA2_IT_HT4: DMA2 Channel4 half transfer interrupt.
  *     @arg DMA2_IT_TE4: DMA2 Channel4 transfer error interrupt.
  *     @arg DMA2_IT_GL5: DMA2 Channel5 global interrupt.
  *     @arg DMA2_IT_TC5: DMA2 Channel5 transfer complete interrupt.
  *     @arg DMA2_IT_HT5: DMA2 Channel5 half transfer interrupt.
  *     @arg DMA2_IT_TE5: DMA2 Channel5 transfer error interrupt.
  * @retval 无
*/
void drv_dma_stream_clear_it_pending_bit( UINT32 DmaIt )
{
	DmaType* DMAy;
	UINT32 l_DmaPos = 0;
	
	l_DmaPos = DmaIt & DMA1_DMA2_IT_MASK;
	if( l_DmaPos != 0 )
	{
		DMAy = DMA2;		//属于DMA2
	}
	else
	{
		DMAy = DMA1;		//属于DMA1
	}
	
	DMAy->IFCR.all = DmaIt;
}
