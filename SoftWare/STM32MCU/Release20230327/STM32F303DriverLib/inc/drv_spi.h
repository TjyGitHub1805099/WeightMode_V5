/**
*******************************************************************
* @file    drv_spi.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x SPI模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include "drv_rcc.h"
#include "reg_stm32f303_spi.h"

/** SPI 工作模式定义 */
typedef enum SpiModeType
{
	SPI_MODE_0 = 0,		/**< SPI 模式0，上升沿锁存，然后下降沿移位 */
	SPI_MODE_1,			/**< SPI 模式1，上升沿移位，然后下降沿锁存 */
	SPI_MODE_2,			/**< SPI 模式2，下降沿锁存，然后上升沿移位 */
	SPI_MODE_3			/**< SPI 模式3，下降沿移位，然后上升沿锁存 */
}enumSpiModeType;

/** SPI 波特率分频值 */
typedef enum SpiBaudDivType
{
	SPI_BAUD_DIV_2 = 0,						/**< 2分频 */
	SPI_BAUD_DIV_4,							/**< 4分频 */
	SPI_BAUD_DIV_8,							/**< 8分频 */
	SPI_BAUD_DIV_16,						/**< 16分频 */
	SPI_BAUD_DIV_32,						/**< 32分频 */
	SPI_BAUD_DIV_64,						/**< 64分频 */
	SPI_BAUD_DIV_128,						/**< 128分频 */
	SPI_BAUD_DIV_256						/**< 256分频 */
}enumSpiBaudDivType;

/** SPI数据起始位定义 */
typedef enum SpiFirstBitType
{
	SPI_FIRSTBIT_MSB = 0,					/**< 最高位 */
	SPI_FIRSTBIT_LSB						/**< 最低位 */
}enumSpiFirstBitType;

/** SPI数据位数定义 */
typedef enum SpiDataBitType
{
	SPI_DATA_4BIT = 3,						/**< 4位数据 */
	SPI_DATA_5BIT,							/**< 5位数据 */
	SPI_DATA_6BIT,							/**< 6位数据 */
	SPI_DATA_7BIT,							/**< 7位数据 */
	SPI_DATA_8BIT,							/**< 8位数据 */
	SPI_DATA_9BIT,							/**< 9位数据 */
	SPI_DATA_10BIT,							/**< 10位数据 */
	SPI_DATA_11BIT,							/**< 11位数据 */
	SPI_DATA_12BIT,							/**< 12位数据 */
	SPI_DATA_13BIT,							/**< 13位数据 */
	SPI_DATA_14BIT,							/**< 14位数据 */
	SPI_DATA_15BIT,							/**< 15位数据 */
	SPI_DATA_16BIT							/**< 16位数据 */
}enumSpiDataBitType;

/** SPI模式定义 */
typedef enum SpiMasterSlaverType
{
	SPI_SLAVER_MODE = 0,					/**< SPI从机 */
	SPI_MASTER_MODE							/**< SPI主机 */
}enumSpiMasterSlaverType;

/** SPI片选模式定义 */
typedef enum SpiNssType
{
	SPI_NSS_HARD = 0,						/**< 片选采用硬件模式 */
	SPI_NSS_SOFT							/**< 片选采用软件管理模式 */
}enumSpiNssType;

/** 外设SPI，I2S模式选择定义 */
typedef enum PeriphSpiI2sType
{
	PERIPH_SPI_MODE = 0,					/**< 外设选择SPI模式 */
	PERIPH_I2S_MODE							/**< 外设选择I2S模式 */
}enumPeriphSpiI2sType;

/* SPI_I2S中断定义 */
#define SPI_I2S_IT_TXE                  ((UINT8)0x71)
#define SPI_I2S_IT_RXNE                 ((UINT8)0x60)
#define SPI_I2S_IT_ERR                  ((UINT8)0x50)

#define I2S_IT_UDR                      ((UINT8)0x53)
#define SPI_I2S_IT_TIFRFE               ((UINT8)0x58)
#define SPI_I2S_IT_OVR                  ((UINT8)0x56)
#define SPI_IT_MODF                     ((UINT8)0x55)
#define SPI_IT_CRCERR                   ((UINT8)0x54)
/* SPI_I2S标志定义 */
#define SPI_I2S_FLAG_RXNE               ((UINT16)0x0001)
#define SPI_I2S_FLAG_TXE                ((UINT16)0x0002)
#define I2S_FLAG_CHSIDE                 ((UINT16)0x0004)
#define I2S_FLAG_UDR                    ((UINT16)0x0008)
#define SPI_FLAG_CRCERR                 ((UINT16)0x0010)
#define SPI_FLAG_MODF                   ((UINT16)0x0020)
#define SPI_I2S_FLAG_OVR                ((UINT16)0x0040)
#define SPI_I2S_FLAG_BSY                ((UINT16)0x0080)
#define SPI_I2S_FLAG_FRE                ((UINT16)0x0100)


/**
 * @brief  等待发送缓冲区空
 * @param  pSpi: 要操作的SPI接口
 * @retval 无
 */
void __INLINE drv_spi_wait_tx_buffer_empty( SpiType *pSpi )
{
//	SpiSrType l_Sr;
	UINT32 Temp = 0;

	do{
//		Temp = ( UINT32)pSpi->SR.all;
		Temp = ( UINT32)pSpi->SR;
		Temp = Temp & 0x00000002;
	}while( Temp == 0 );
}

/**
 * @brief  等待接收缓冲区非空
 * @param  pSpi: 要操作的SPI接口
 * @retval 无
 */
void __INLINE drv_spi_wait_rx_buffer_not_empty( SpiType *pSpi )
{
//	SpiSrType l_Sr;
	UINT32 Temp = 0;

	do{
		Temp = (UINT32)pSpi->SR;
		Temp = Temp & 0x00000001;
	}while( Temp == 0 );
}

/**
 * @brief  SPI发送一个字节
 * @param  pSpi: 要操作的SPI接口
 * @retval 无
 */
void __INLINE drv_spi_tx_byte( SpiType *pSpi, UINT8 Byte )
{
	pSpi->DR = Byte;
}

/**
 * @brief  SPI接收一个字节
 * @param  pSpi: 要操作的SPI接口
 * @retval 无
 */
void __INLINE drv_spi_rx_byte( SpiType *pSpi, UINT8 *pByte )
{
	*pByte = pSpi->DR;
}



extern void drv_spi_deinit( SpiType *pSpi );
extern void drv_spi_init( SpiType *pSpi, enumSpiBaudDivType Baudrate, enumSpiModeType SpiMode, enumSpiNssType piNssMode );
extern void drv_spi_set_mode( SpiType *pSpi, enumSpiModeType SpiMode );
extern void drv_spi_set_baudrate( SpiType *pSpi, enumSpiBaudDivType Baudrate );
//extern UINT8 drv_spi_rx_tx_byte( SpiType *pSpi, UINT8 TxData );
extern void drv_spi_rx_tx_byte( SpiType *pSpi, UINT8 TxData, UINT8 *pRxData );
extern void drv_spi_tx_dma_enable( SpiType *pSpi );
extern void drv_spi_tx_dma_disable( SpiType *pSpi );
extern void drv_spi_rx_dma_enable( SpiType *pSpi );
extern void drv_spi_rx_dma_disable( SpiType *pSpi );
extern void drv_spi_it_enable( SpiType *pSpi, UINT8 SpiIt );
extern void drv_spi_it_disable( SpiType *pSpi, UINT8 SpiIt );
extern FlagStatus drv_spi_get_flag_status( SpiType *pSpi, UINT16 SpiFlag );
extern void drv_spi_clear_flag_status( SpiType *pSpi, UINT8 SpiFlag );
extern ITStatus drv_spi_get_it_status( SpiType *pSpi, UINT8 SpiIt );
extern void drv_spi_clear_it_pending_bit( SpiType *pSpi, UINT8 SpiIt );
extern void __INLINE drv_spi_wait_tx_buffer_empty( SpiType *pSpi );
extern void __INLINE drv_spi_wait_rx_buffer_not_empty( SpiType *pSpi );
extern void __INLINE drv_spi_tx_byte( SpiType *pSpi, UINT8 Byte );
extern void __INLINE drv_spi_rx_byte( SpiType *pSpi, UINT8 *pByte );

extern void drv_spi_read_fifo( SpiType *pSpi, UINT8 *pData, UINT8 Len );

#endif
