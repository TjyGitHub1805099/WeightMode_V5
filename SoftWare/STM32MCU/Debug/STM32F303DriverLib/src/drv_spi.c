/**
*******************************************************************
* @file    drv_spi.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x SPI模块驱动程序
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#include "drv_spi.h"

/*
SPI总线的4种工作模式
模式0：上升沿锁存，然后下降沿移位，即CPHA = 0, CPOL = 0
SCLK __/--\__/--\__/--\__/
|  |
MOSI ----\/----\/----\/---
MISO ____/\____/\____/\___

模式1：上升沿移位，然后下降沿锁存，即CPHA = 1, CPOL = 0
SCLK __/--\__/--\__/--\__/--
|  |
MOSI --\/----\/----\/----\/-
MISO __/\____/\____/\____/\_

模式2：下降沿锁存，然后上升沿移位，即CPHA = 0, CPOL = 1
SCLK --\__/--\__/--\__/--\__/
|  |
MOSI ----\/----\/----\/---
MISO ____/\____/\____/\___

模式3：下降沿移位，然后上升沿锁存，即CPHA = 1, CPOL = 1
SCLK --\__/--\__/--\__/--\__/
|  |
MOSI --\/----\/----\/---\/--
MISO __/\____/\____/\___/\__

*/

#define DRV_SPI_DELAY_MAX               1000000
UINT32 g_SpiDelay;

/**
* @brief  复位SPI模块寄存器为默认值.
* @param  pSpi: 要操作的SPI接口
* @retval 无
*/
void drv_spi_deinit( SpiType *pSpi )
{
	if( pSpi == SPI1 )
	{
		drv_rcc_apb2_periph_reset_enable( RCC_APB2RSTR_SPI1RST );
		drv_rcc_apb2_periph_reset_disable( RCC_APB2RSTR_SPI1RST );
	}
	else if( pSpi == SPI2 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_SPI2RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_SPI2RST );
	}
	else 
	{
		if( pSpi == SPI3 )
		{
			drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_SPI3RST );
			drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_SPI3RST );
		}
	}
}

/**
* @brief  设置SPI模块工作模式.
* @param  pSpi: 要操作的SPI接口
* @param  SpiMode: SPI工作模式
* @retval 无
*/
void drv_spi_set_mode( SpiType *pSpi, enumSpiModeType SpiMode )
{ 
	pSpi->CR1.bit.CPOL_CPHA = (UINT16)SpiMode;
}

/**
* @brief  设置SPI模块波特率.
* @param  pSpi: 要操作的SPI接口
* @param  Baudrate: 波特率分频值
* @retval 无
*/
void drv_spi_set_baudrate( SpiType *pSpi, enumSpiBaudDivType Baudrate )
{
	pSpi->CR1.bit.BR = (UINT16)Baudrate;
}

/**
* @brief  初始化SPI模块.
* @param  pSpi: 要操作的SPI接口
* @param  Baudrate: 波特率分频值
* @param  SpiMode: SPI工作模式
* @retval 无
*/
void drv_spi_init( SpiType *pSpi, enumSpiBaudDivType Baudrate, enumSpiModeType SpiMode, enumSpiNssType piNssMode )
{ 
	drv_spi_deinit( pSpi );
	
	pSpi->CR1.bit.SPE 			= 0;							//禁止SPI
	pSpi->CR1.bit.BIDIMODE 		= 0;							//双线单向模式
	pSpi->CR1.bit.CRCEN 		= 0;							//禁止CRC
    pSpi->CR1.bit.LSBFIRST      = (UINT16)SPI_FIRSTBIT_LSB;// SPI_FIRSTBIT_MSB;		//最先发送MSB
	pSpi->CR1.bit.MSTR 			= (UINT16)SPI_MASTER_MODE;		//主模式 SPI_MASTER_MODE
	pSpi->CR1.bit.SSM 			= (UINT16)piNssMode;			//软件管理
	pSpi->CR1.bit.SSI			= 1;							//仅软件管理从设备有用，硬件模式无效
	pSpi->CR1.bit.CPOL_CPHA 	= (UINT16)SpiMode;				//SPI模式
	pSpi->CR1.bit.BR 			= (UINT16)Baudrate;				//设置分频系数，波特率
	pSpi->CR2.bit.DS 			= (UINT16)SPI_DATA_8BIT;		//8位数据
    pSpi->CR2.bit.FRXTH = 1;                                    // FIFO深度为1
	pSpi->I2SCFGR.bit.I2SMOD 	= (UINT16)PERIPH_SPI_MODE;		//SPI模式
	pSpi->CRCPR 				= 7;							//CRC多项式
	pSpi->CR1.bit.SPE			= 1;							//使能SPI
}


/**
* @brief  发送并接收一个字节.
* @param  pSpi: 要操作的SPI接口
* @param  TxData: 发送数据
* @retval 接收数据
*/
void drv_spi_rx_tx_byte( SpiType *pSpi, UINT8 TxData, UINT8 *pRxData )
{
    //UINT8 l_RxData;
    SpiSrType l_Sr;
	
//    UINT32 l_SpiBase = (UINT32)pSpi + 0x0C;

    g_SpiDelay = DRV_SPI_DELAY_MAX;
	do
	{
		l_Sr.all = pSpi->SR;
        if( --g_SpiDelay == 0 )
        {
            break;
        }
	}while(l_Sr.bit.TXE == 0);

    pSpi->DR = TxData;

//	while(0 == (pSpi->SR & 0x0001));
	
    g_SpiDelay = DRV_SPI_DELAY_MAX;
	do
	{
		l_Sr.all = pSpi->SR;
        if( --g_SpiDelay == 0 )
        {
            break;
        }
	}while(l_Sr.bit.RXNE == 0);

//    l_RxData = pSpi->DR & 0xFF;
    *pRxData = pSpi->DR & 0xFF;
//    *pRxData = *(volatile UINT8 *)l_SpiBase;

    //return l_RxData;
}

void drv_spi_read_fifo(SpiType *pSpi, UINT8 *pData, UINT8 Len)
{
	SpiSrType l_Sr;
    UINT8 i;

	l_Sr.all = pSpi->SR;
	
    if( Len <= l_Sr.bit.FRLVL )
    {
        for( i = 0; i < Len; i++ )
        {
            pData[i] = pSpi->DR & 0xFF;
        }
    }

}

/**
* @brief  使能SPI DMA发送缓冲区.
* @param  pSpi: 要操作的SPI接口
* @retval 无
*/
void drv_spi_tx_dma_enable( SpiType *pSpi )
{
	pSpi->CR2.bit.TXDMAEN = 1;
}

/**
* @brief  禁止 SPI DMA 发送缓冲区.
* @param  pSpi: 要操作的SPI接口
* @retval 无
*/
void drv_spi_tx_dma_disable( SpiType *pSpi )
{
	pSpi->CR2.bit.TXDMAEN = 0;
}

/**
* @brief  使能SPI DMA接收缓冲区.
* @param  pSpi: 要操作的SPI接口
* @retval 无
*/
void drv_spi_rx_dma_enable( SpiType *pSpi )
{
	pSpi->CR2.bit.RXDMAEN = 1;
}

/**
* @brief  禁止 SPI DMA 接收缓冲区.
* @param  pSpi: 要操作的SPI接口
* @retval 无
*/
void drv_spi_rx_dma_disable( SpiType *pSpi )
{
	pSpi->CR2.bit.RXDMAEN = 0;
}

/**
* @brief  使能指定中断.
* @param  pSpi: 要操作的SPI接口
* @param  SpiIt: 要使能的中断源，可以是下面值的一个:
*            @arg SPI_I2S_IT_TXE: 发送缓冲区空
*            @arg SPI_I2S_IT_RXNE: 接收缓冲区不空
*            @arg SPI_I2S_IT_ERR: 错误
* @retval 无
*/
void drv_spi_it_enable( SpiType *pSpi, UINT8 SpiIt )
{
	UINT16 l_SpiItPosition = 0;
	
	l_SpiItPosition = (UINT16)( SpiIt >> 0x04 );
	pSpi->CR2.all |= (UINT16)0x01 << l_SpiItPosition;
}

/**
* @brief  禁止指定中断.
* @param  pSpi: 要操作的SPI接口
* @param  SpiIt: 要禁止的中断源，可以是下面值的一个:
*            @arg SPI_I2S_IT_TXE: 发送缓冲区空
*            @arg SPI_I2S_IT_RXNE: 接收缓冲区不空
*            @arg SPI_I2S_IT_ERR: 错误
* @retval 无
*/
void drv_spi_it_disable( SpiType *pSpi, UINT8 SpiIt )
{
	UINT16 l_SpiItPosition = 0;
	
	l_SpiItPosition = (UINT16)( SpiIt >> 4 );
	pSpi->CR2.all &= (UINT16)( ~((UINT16)0x01 << l_SpiItPosition ));
}

/**
* @brief  检查SPI标志状态.
* @param  pSpi: 要操作的SPI接口
* @param  SpiFlag: 要检查的标志，可以是下面值的一个:
  *     @arg SPI_I2S_FLAG_TXE: Transmit buffer empty flag.
  *     @arg SPI_I2S_FLAG_RXNE: Receive buffer not empty flag.
  *     @arg SPI_I2S_FLAG_BSY: Busy flag.
  *     @arg SPI_I2S_FLAG_OVR: Overrun flag.
  *     @arg SPI_I2S_FLAG_MODF: Mode Fault flag.
  *     @arg SPI_I2S_FLAG_CRCERR: CRC Error flag.
  *     @arg SPI_I2S_FLAG_FRE: TI frame format error flag.
  *     @arg I2S_FLAG_UDR: Underrun Error flag.
  *     @arg I2S_FLAG_CHSIDE: Channel Side flag. 
* @retval 当前状态值.
*/
FlagStatus drv_spi_get_flag_status( SpiType *pSpi, UINT16 SpiFlag )
{
	if(( pSpi->SR & SpiFlag ) != (UINT16)RESET )
	{
		return SET;
	}
	else
	{
		return  RESET;
	}
}

/**
* @brief  清 CRC 错误标志.
* @param  pSpi: 要操作的SPI接口
* @param  SpiFlag: 要清的错误标志，只能是下面的值.
*            @arg SPI_FLAG_CRCERR: CRC Error flag.
* @note   OVR (OverRun error) flag is cleared by software sequence: a read
*          operation to SPI_DR register (SPI_I2S_ReceiveData()) followed by a read
*          operation to SPI_SR register (SPI_I2S_GetFlagStatus()).
* @note   UDR (UnderRun error) flag is cleared by a read operation to
*          SPI_SR register (SPI_I2S_GetFlagStatus()).
* @note   MODF (Mode Fault) flag is cleared by software sequence: a read/write
*          operation to SPI_SR register (SPI_I2S_GetFlagStatus()) followed by a
*          write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
* @retval 无
*/
void drv_spi_clear_flag_status( SpiType *pSpi, UINT8 SpiFlag )
{
	SpiSrType l_sr;
	
	l_sr.all = pSpi->SR;
	l_sr.bit.CRCERR = 0;
	pSpi->SR = l_sr.all;
}

/**
* @brief  检查中断标志.
* @param  pSpi: 要操作的SPI接口
* @param  SpiIt: 中断源，可以是下面值的一个:
  *     @arg SPI_I2S_IT_TXE: Transmit buffer empty interrupt.
  *     @arg SPI_I2S_IT_RXNE: Receive buffer not empty interrupt.
  *     @arg SPI_IT_MODF: Mode Fault interrupt.
  *     @arg SPI_I2S_IT_OVR: Overrun interrupt.
  *     @arg I2S_IT_UDR: Underrun interrupt.  
  *     @arg SPI_I2S_IT_FRE: Format Error interrupt.
* @retval 当前状态值.
*/
ITStatus drv_spi_get_it_status( SpiType *pSpi, UINT8 SpiIt )
{
	UINT16 l_SpiFlagPosition = 0, l_SpiItPosition = 0;
	
	l_SpiFlagPosition	= (UINT16)0x01 << ( SpiIt & 0x0F );
	l_SpiItPosition		= (UINT16)0x01 << ( SpiIt >> 4 );
	
	if((( pSpi->SR & l_SpiFlagPosition ) != (UINT16)RESET ) && (( pSpi->CR2.all & l_SpiItPosition ) != (UINT16)RESET ))
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清中断挂起标志位.
* @param  pSpi: 要操作的SPI接口
* @param  SpiIt: 这里只能清CRC中断挂起标志.
*            @arg SPI_IT_CRCERR: CRC Error interrupt.
*
* @note   OVR (OverRun Error) interrupt pending bit is cleared by software
*          sequence: a read operation to SPI_DR register (SPI_I2S_ReceiveData())
*          followed by a read operation to SPI_SR register (SPI_I2S_GetITStatus()).
* @note   UDR (UnderRun Error) interrupt pending bit is cleared by a read
*          operation to SPI_SR register (SPI_I2S_GetITStatus()).
* @note   MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
*          a read/write operation to SPI_SR register (SPI_I2S_GetITStatus())
*          followed by a write operation to SPI_CR1 register (SPI_Cmd() to enable
*          the SPI).
* @retval 无
*/
void drv_spi_clear_it_pending_bit( SpiType *pSpi, UINT8 SpiIt )
{
	UINT16 l_SpiItPendingBit = 0;
	
	l_SpiItPendingBit = (UINT16)0x01 << ( SpiIt & 0x0F );
	pSpi->SR &= (UINT16)( ~l_SpiItPendingBit );
}
