/**
 *******************************************************************
 * @file    hal_uart.h
 * @author  MKdriver
 * @version V1.0.0
 * @date    9-Oct-2015
 * @brief   STM32F303 UART HAL层程序H文件
 *******************************************************************
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
 *******************************************************************
 */
 
#ifndef __HAL_UART_H__
#define __HAL_UART_H__
 
 
#include "drv_rcc.h"
#include "drv_nvic.h"
#include "drv_gpio.h"
#include "drv_dma.h"
#include "drv_timer.h"
#include "drv_dbgmcu.h"
#include "drv_uart.h"



/* 硬件端口资源定义 */
// UART1 接485总线 , 实际是 STM32F303 UASRT3 , 带DMA功能
#define UART1_PORT							USART3
#define UART1_PORT_CLK						RCC_APB1ENR_USART3EN
#define UART1_PORT_IRQn						USART3_IRQn
#define UART1_PORT_GPIO_AF					GPIO_AF7_USART3

#define UART1_TX_GPIO_PORT					GPIOB
#define UART1_TX_GPIO_CLK					RCC_AHBENR_GPIOBEN
#define UART1_TX_GPIO_PIN					GPIO_PIN_10
#define UART1_TX_PIN_SOURCE					GPIO_PINSOURCE10

#define UART1_RX_GPIO_PORT					GPIOB
#define UART1_RX_GPIO_CLK					RCC_AHBENR_GPIOBEN
#define UART1_RX_GPIO_PIN					GPIO_PIN_11
#define UART1_RX_PIN_SOURCE					GPIO_PINSOURCE11

#define UART1_TX_DMA						DMA1
#define UART1_TX_DMA_CLK					RCC_AHBENR_DMA1EN
#define UART1_TX_DMA_CHANNEL            	DMA1_Channel2
#define UART1_TX_DMA_IRQn              	 	DMA1_Channel2_IRQn
#define UART1_TX_DMA_IT_TCIF				DMA1_IT_TC2

#define UART1_RX_DMA						DMA1
#define UART1_RX_DMA_CLK					RCC_AHBENR_DMA1EN
#define UART1_RX_DMA_CHANNEL            	DMA1_Channel3

/** RS485总线使能口线定义 */
#define UART1_DEA_GPIO_PORT					GPIOB
#define UART1_DEA_GPIO_CLK					RCC_AHBENR_GPIOBEN
#define UART1_DEA_GPIO_PIN					GPIO_PIN_2


// UART2 接DIWEN显示屏 , 实际是 STM32F303 UASRT2 , 带DMA功能
#define UART2_PORT							USART2
#define UART2_PORT_CLK						RCC_APB1ENR_USART2EN
#define UART2_PORT_IRQn						USART2_IRQn
#define UART2_PORT_GPIO_AF					GPIO_AF7_USART2

#define UART2_TX_GPIO_PORT					GPIOA
#define UART2_TX_GPIO_CLK					RCC_AHBENR_GPIOAEN
#define UART2_TX_GPIO_PIN					GPIO_PIN_2
#define UART2_TX_PIN_SOURCE					GPIO_PINSOURCE2

#define UART2_RX_GPIO_PORT					GPIOA
#define UART2_RX_GPIO_CLK					RCC_AHBENR_GPIOAEN
#define UART2_RX_GPIO_PIN					GPIO_PIN_3
#define UART2_RX_PIN_SOURCE					GPIO_PINSOURCE3

#define UART2_TX_DMA						DMA1
#define UART2_TX_DMA_CLK					RCC_AHBENR_DMA1EN
#define UART2_TX_DMA_CHANNEL            	DMA1_Channel7
#define UART2_TX_DMA_IRQn              	 	DMA1_Channel7_IRQn
#define UART2_TX_DMA_IT_TCIF				DMA1_IT_TC7

#define UART2_RX_DMA						DMA1
#define UART2_RX_DMA_CLK					RCC_AHBENR_DMA1EN
#define UART2_RX_DMA_CHANNEL            	DMA1_Channel6

/** RS485总线使能口线定义 */
#define UART2_DEA_GPIO_PORT					(0)//GPIOB
#define UART2_DEA_GPIO_CLK					(0)//RCC_AHBENR_GPIOBEN
#define UART2_DEA_GPIO_PIN					(0)//GPIO_PIN_10

/** 重新定义中断 */
#define uart_com_isr						USART3_IRQHandler
#define uart_com_tx_dma_isr					DMA1_Channel2_IRQHandler

#define uart_extern_isr						USART2_IRQHandler
#define uart_extern_tx_dma_isr				DMA1_Channel7_IRQHandler

/** UART硬件端口定义 */
typedef enum UartPortType
{
	UART_COM = 0,
	UART_EXTERN,
	UART_NUMBER
}enumUartPortType;

/** 串口波特率值定义 */
typedef enum UartBaudType
{
	UART_BAUD_4800 = 0,            /**< 波特率 4800 */
	UART_BAUD_9600,                /**< 波特率 9600 */
	UART_BAUD_19200,               /**< 波特率 19200 */
	UART_BAUD_38400,               /**< 波特率 38400 */
	UART_BAUD_57600,               /**< 波特率 57600 */
	UART_BAUD_115200,              /**< 波特率 115200 */
	UART_BAUD_1M,                  /**< 波特率 1M */
	UART_BAUD_2M,                  /**< 波特率 2M */
	UART_BAUD_3M,                  /**< 波特率 3M */
	UART_BAUD_4M,                  /**< 波特率 4M */
	UART_BAUD_END
}enumUartBaudType;

/** 串口通信方式定义 */	
typedef enum UartLinkType
{
	UART_LINK_RX_ONLY = 0,          /**< 只能接收 */
	UART_LINK_RX_ONLY_ENABE,        /**< 只能接收，带使能控制 */
	UART_LINK_TX_ONLY,              /**< 只能发送 */
	UART_LINK_TX_ONLY_ENABE,        /**< 只能发送，带使能控制 */
	UART_LINK_RX_TX_HALF,           /**< 接收和发送半双工 */
	UART_LINK_RX_TX_HALF_ENABE,     /**< 接收和发送半双工，带使能控制 */
	UART_LINK_RX_TX_FULL,           /**< 接收和发送全双工 */
	UART_LINK_RX_TX_FULL_ENABE,     /**< 接收和发送全双工，带使能控制 */
}enumUartLinkType;

/** 串口发送方式定义 */
typedef enum UartRxTxModeType
{
	UART_RX_TX_MODE_POLL = 0,       /**< 查询方式发送 */
	UART_RX_TX_MODE_INTERRUPT,      /**< 中断方式发送 */
	UART_RX_TX_MODE_DMA             /**< DMA方式发送 */
}enumUartRxTxModeType;


/** 定义从机串口设备类型 */
typedef struct structUartDeviceType
{
    enumUartPortType        Port;						/**< 串口数据位 */
	enumUartLinkType		LinkType;					/**< 链路层类型 */
	enumUartBaudType		Baudrate;					/**< 串口比特率 */
	enumUartDataBitType		DataBit;					/**< 串口数据位 */
	enumUartStopBitType		StopBit;					/**< 串口停止位 */
	enumUartParityBitType	Parity;						/**< 串口奇偶校验 */
	enumUartRxTxModeType	RxTxMode;					/**< 串口接收发送方式 */
	UINT8                   TxBusyFlag;					/**< 发送忙标志 */
	UINT16                  TxLength;					/**< 发送字节数 */
	UINT16                  TxCounter;					/**< 发送字节数计数器 */
	UINT16                  *pRxLength;					/**< 接收字节数 */
	UINT8                   *pRxFinishFlag;				/**< 接收完成标志 */
	UINT8                   *pTxBuffer;					/**< 发送缓冲区 */
	UINT8                   *pRxBuffer;					/**< 接收缓冲区 */
	UINT16					RxBytesMax;					/**< 最多接收字节数，用在DMA接收模式下计算实际接收字节数量 */
	void( *init )( struct structUartDeviceType *pUartDevice );
	void( *set_braudrate )( struct structUartDeviceType *pUartDevice, enumUartBaudType Baudrate );
	void( *set_timeout )( struct structUartDeviceType *pUartDevice );
	UINT8( *tx_bytes )( struct structUartDeviceType *pUartDevice, UINT8 *pTxData, UINT16 TxLength );
	void( *irq_enable )( struct structUartDeviceType *pUartDevice );
	void( *irq_disable )( struct structUartDeviceType *pUartDevice );
}UartDeviceType;

#define UartDevice1Default { \
    UART_COM, \
	UART_LINK_RX_TX_HALF_ENABE, \
	UART_BAUD_115200, \
	UART_DATABIT_8, \
	UART_STOPBIT_1, \
	UART_PARITY_NONE, \
	UART_RX_TX_MODE_DMA, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	4096, \
	hal_uart_port_init, \
	hal_uart_set_braudrate, \
	hal_uart_set_timeout, \
	hal_uart_tx_bytes, \
	hal_uart_rx_irq_enable, \
	hal_uart_rx_irq_disable \
}

#define UartDevice2Default { \
    UART_EXTERN, \
	UART_LINK_RX_TX_FULL, \
	UART_BAUD_115200, \
	UART_DATABIT_8, \
	UART_STOPBIT_1, \
	UART_PARITY_NONE, \
	UART_RX_TX_MODE_DMA, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	0, \
	4096, \
	hal_uart_port_init, \
	hal_uart_set_braudrate, \
	hal_uart_set_timeout, \
	hal_uart_tx_bytes, \
	hal_uart_rx_irq_enable, \
	hal_uart_rx_irq_disable \
}

extern UsartType* UART_PORT[];
extern GpioType* UART_DEA_GPIO_PORT[];
extern const UINT16 UART_DEA_GPIO_PIN[];
//extern GpioType* UART_REA_GPIO_PORT[];
//extern const UINT16 UART_REA_GPIO_PIN[];

/**
* @brief  设置串口为发送模式
* @param  UartPort: UART设备端口号
* @retval 无
*/
void __INLINE hal_uart_set_tx_mode( UartDeviceType *pUartDevice )
{
//	drv_gpio_set_pins_high( UART_REA_GPIO_PORT[ pUartDevice->Port ], UART_REA_GPIO_PIN[ pUartDevice->Port ] );
	drv_gpio_set_pins_high( UART_DEA_GPIO_PORT[ pUartDevice->Port ], UART_DEA_GPIO_PIN[ pUartDevice->Port ] );
}

/**
* @brief  设置串口为接收模式
* @param  UartPort: UART设备端口号
* @retval 无
*/
void __INLINE hal_uart_set_rx_mode( UartDeviceType *pUartDevice )
{
//	drv_gpio_set_pins_low( UART_REA_GPIO_PORT[ pUartDevice->Port ], UART_REA_GPIO_PIN[ pUartDevice->Port ] );
	drv_gpio_set_pins_low( UART_DEA_GPIO_PORT[ pUartDevice->Port ], UART_DEA_GPIO_PIN[ pUartDevice->Port ] );
}

/**
* @brief  设置串口为同时接收和发送模式
* @param  UartPort: UART设备端口号
* @retval 无
*/
void __INLINE hal_uart_set_rx_tx_mode( UartDeviceType *pUartDevice )
{
//	drv_gpio_set_pins_low( UART_REA_GPIO_PORT[ pUartDevice->Port ], UART_REA_GPIO_PIN[ pUartDevice->Port ] );
	drv_gpio_set_pins_high( UART_DEA_GPIO_PORT[ pUartDevice->Port ], UART_DEA_GPIO_PIN[ pUartDevice->Port ] );
}

/**
* @brief  串口接收使能
* @param  pUartDevice: 要操作的串口设备
* @retval 无
*/
__INLINE void hal_uart_rx_enable( UartDeviceType *pUartDevice )
{
    drv_uart_rx_enable( UART_PORT[pUartDevice->Port] );
}

/**
* @brief  串口接收禁止
* @param  pUartDevice: 要操作的串口设备
* @retval 无
*/
__INLINE void hal_uart_rx_disable( UartDeviceType *pUartDevice )
{
    drv_uart_rx_disable( UART_PORT[pUartDevice->Port] );
}


extern UartDeviceType	g_UartDevice[];

extern void hal_uart_init( void );
extern void hal_uart_port_init( UartDeviceType *pUartDevice );
extern void hal_uart_set_braudrate( UartDeviceType *pUartDevice, enumUartBaudType Baudrate );
extern UINT8 hal_uart_tx_bytes( UartDeviceType *pUartDevice, UINT8 *pTxData, UINT16 TxLength );
extern void hal_uart_dma_rx_start( UartDeviceType *pUartDevice, UINT8 *pRxData, UINT16 RxLength );
//extern void hal_uart_dma_rx_restart( UartDeviceType *pUartDevice );
extern void hal_uart_rx_irq_enable(UartDeviceType *pUartDevice);
extern void hal_uart_rx_irq_disable(UartDeviceType *pUartDevice);
extern UINT8 hal_uart_get_byte_with_timeout(UartDeviceType *pUartDevice, UINT8 *pDat, UINT32 TimeOut);
extern void hal_uart_set_timeout( UartDeviceType *pUartDevice );

#endif

	
	

