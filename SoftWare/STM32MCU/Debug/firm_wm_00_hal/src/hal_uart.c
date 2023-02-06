/**
  *******************************************************************
  * @file    hal_uart.c
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40x UART程序C文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#include "hal_irq_priority.h"
#include "hal_delay.h"
#include "hal_uart.h"

  // UART 外设
UsartType* UART_PORT[] = { UART1_PORT, UART2_PORT };
const UINT32 UART_PORT_CLK[] = { UART1_PORT_CLK, UART2_PORT_CLK };
const INT8 UART_PORT_IRQn[] = { UART1_PORT_IRQn, UART2_PORT_IRQn };
const UINT8 UART_PORT_GPIO_AF[] = { UART1_PORT_GPIO_AF, UART2_PORT_GPIO_AF };
// UART 发送引脚
GpioType* UART_TX_GPIO_PORT[] = { UART1_TX_GPIO_PORT, UART2_TX_GPIO_PORT };
const UINT32 UART_TX_GPIO_CLK[] = { UART1_TX_GPIO_CLK, UART2_TX_GPIO_CLK };
const UINT16 UART_TX_GPIO_PIN[] = { UART1_TX_GPIO_PIN, UART2_TX_GPIO_PIN };
const UINT16 UART_TX_PIN_SOURCE[] = { UART1_TX_PIN_SOURCE, UART2_TX_PIN_SOURCE };
// UART 接收引脚
GpioType* UART_RX_GPIO_PORT[] = { UART1_RX_GPIO_PORT, UART2_RX_GPIO_PORT };
const UINT32 UART_RX_GPIO_CLK[] = { UART1_RX_GPIO_CLK, UART2_RX_GPIO_CLK };
const UINT16 UART_RX_GPIO_PIN[] = { UART1_RX_GPIO_PIN, UART2_RX_GPIO_PIN };
const UINT16 UART_RX_PIN_SOURCE[] = { UART1_RX_PIN_SOURCE, UART2_RX_PIN_SOURCE };
// UART 发送使能引脚
GpioType* UART_DEA_GPIO_PORT[] = { UART1_DEA_GPIO_PORT, UART2_DEA_GPIO_PORT };
const UINT32 UART_DEA_GPIO_CLK[] = { UART1_DEA_GPIO_CLK, UART2_DEA_GPIO_CLK };
const UINT16 UART_DEA_GPIO_PIN[] = { UART1_DEA_GPIO_PIN, UART2_DEA_GPIO_PIN };
//// UART 接收使能引脚
//GpioType* UART_REA_GPIO_PORT[] = { UART1_REA_GPIO_PORT };
//const UINT32 UART_REA_GPIO_CLK[] = { UART1_REA_GPIO_CLK };
//const UINT16 UART_REA_GPIO_PIN[] = { UART1_REA_GPIO_PIN };
// UART 发送DMA
DmaType* UART_TX_DMA[] = { UART1_TX_DMA, UART2_TX_DMA };
const UINT32 UART_TX_DMA_CLK[] = { UART1_TX_DMA_CLK, UART2_TX_DMA_CLK };
DmaChannelType* UART_TX_DMA_CHANNEL[] = { UART1_TX_DMA_CHANNEL, UART2_TX_DMA_CHANNEL };
const INT8 UART_TX_DMA_IRQn[] = { UART1_TX_DMA_IRQn, UART2_TX_DMA_IRQn };
const UINT32 UART_TX_DMA_IT_TCIF[] = { UART1_TX_DMA_IT_TCIF, UART2_TX_DMA_IT_TCIF };
//const UINT32 UART_TX_DMA_IT_GIF[] = { UART1_TX_DMA_IT_GIF };
//const UINT32 UART_TX_DMA_FLAG_GIF[] = { UART1_TX_DMA_FLAG_GIF };
// UART 接收DMA
DmaType* UART_RX_DMA[] = { UART1_RX_DMA, UART2_RX_DMA };
DmaChannelType* UART_RX_DMA_CHANNEL[] = { UART1_RX_DMA_CHANNEL, UART2_RX_DMA_CHANNEL };
const UINT32 UART_RX_DMA_CLK[] = { UART1_RX_DMA_CLK, UART2_RX_DMA_CLK };
//const UINT32 UART_RX_DMA_IT_TCIF[] = { UART2_RX_DMA_IT_TCIF, UART3_RX_DMA_IT_TCIF };
//const UINT32 UART_RX_DMA_FLAG_TCIF[] = { UART2_RX_DMA_FLAG_TCIF, UART3_RX_DMA_FLAG_TCIF };
//const UINT32 UART_RX_DMA_FLAG_GIF[] = { UART1_RX_DMA_FLAG_GIF };

const UINT32 g_UartBaudTab[] = { 4800, 9600, 19200, 38400, 57600, 115200, 1000000, 2000000, 3000000, 4000000 };
UartDeviceType	g_UartDevice[UART_NUMBER] = { UartDevice1Default, UartDevice2Default };

extern void app_uart_extern_msg_packet_process( UartDeviceType *pUartDevice );
//extern void hal_3048_msg_packet_process( UartDeviceType *pUartDevice );


/**
 * @brief  UART引脚初始化
 * @param  pUartDevice: 要操作的串口设备
 * @retval 无
 */
void hal_uart_gpio_init( UartDeviceType *pUartDevice )
{
	switch( pUartDevice->LinkType )
	{
		case UART_LINK_RX_ONLY:
		// 使能口线时钟
		drv_rcc_ahb1_clk_enable( UART_RX_GPIO_CLK[pUartDevice->Port] );
		// 配置引脚为复用功能
		drv_gpio_alternate_function_init( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		// 连接到串口引脚
		drv_gpio_alternate_function_connect( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		break;
		case UART_LINK_RX_ONLY_ENABE:
		// 使能口线时钟
		drv_rcc_ahb1_clk_enable( UART_RX_GPIO_CLK[pUartDevice->Port] );
		//			drv_rcc_ahb1_clk_enable( UART_REA_GPIO_CLK[ pUartDevice->Port] );
					// 配置使能控制脚为输出
		//			drv_gpio_output_init( UART_REA_GPIO_PORT[pUartDevice->Port], UART_REA_GPIO_PIN[ pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
					// 配置引脚为复用功能
		drv_gpio_alternate_function_init( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		// 连接到串口引脚
		drv_gpio_alternate_function_connect( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		// 设置使能模式为接收方式
		hal_uart_set_rx_mode( pUartDevice );
		break;
		case UART_LINK_TX_ONLY:
		// 使能口线时钟
		drv_rcc_ahb1_clk_enable( UART_TX_GPIO_CLK[pUartDevice->Port] );
		// 配置引脚为复用功能
		drv_gpio_alternate_function_init( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		// 连接到串口引脚
		drv_gpio_alternate_function_connect( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		break;
		case UART_LINK_TX_ONLY_ENABE:
		// 使能口线时钟
		drv_rcc_ahb1_clk_enable( UART_TX_GPIO_CLK[pUartDevice->Port] );
		drv_rcc_ahb1_clk_enable( UART_DEA_GPIO_CLK[pUartDevice->Port] );
		// 配置使能控制脚为输出
		drv_gpio_output_init( UART_DEA_GPIO_PORT[pUartDevice->Port], UART_DEA_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		// 配置引脚为复用功能
		drv_gpio_alternate_function_init( UART_RX_GPIO_PORT[pUartDevice->Port], UART_TX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		// 连接到串口引脚
		drv_gpio_alternate_function_connect( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		// 设置使能模式为发送方式
		hal_uart_set_tx_mode( pUartDevice );
		break;
		case UART_LINK_RX_TX_HALF:
		case UART_LINK_RX_TX_HALF_ENABE:
		// 使能口线时钟
		drv_rcc_ahb1_clk_enable( UART_TX_GPIO_CLK[pUartDevice->Port] );
		drv_rcc_ahb1_clk_enable( UART_RX_GPIO_CLK[pUartDevice->Port] );
		drv_rcc_ahb1_clk_enable( UART_DEA_GPIO_CLK[pUartDevice->Port] );
		//			drv_rcc_ahb1_clk_enable( UART_REA_GPIO_CLK[ pUartDevice->Port] );
					// 配置使能控制脚为输出
		drv_gpio_output_init( UART_DEA_GPIO_PORT[pUartDevice->Port], UART_DEA_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		//			drv_gpio_output_init( UART_REA_GPIO_PORT[pUartDevice->Port], UART_REA_GPIO_PIN[ pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
					// 配置引脚为复用功能
		drv_gpio_alternate_function_init( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		drv_gpio_alternate_function_init( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		// 连接到串口引脚
		drv_gpio_alternate_function_connect( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		drv_gpio_alternate_function_connect( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		// 设置使能模式为接收方式
		hal_uart_set_rx_mode( pUartDevice );
		break;
		case UART_LINK_RX_TX_FULL:
		// 使能口线时钟
		drv_rcc_ahb1_clk_enable( UART_TX_GPIO_CLK[pUartDevice->Port] );
		drv_rcc_ahb1_clk_enable( UART_RX_GPIO_CLK[pUartDevice->Port] );
		// 配置引脚为复用功能
		drv_gpio_alternate_function_init( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		drv_gpio_alternate_function_init( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		// 连接到串口引脚
		drv_gpio_alternate_function_connect( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		drv_gpio_alternate_function_connect( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		break;
		case UART_LINK_RX_TX_FULL_ENABE:
		// 使能口线时钟
		drv_rcc_ahb1_clk_enable( UART_TX_GPIO_CLK[pUartDevice->Port] );
		drv_rcc_ahb1_clk_enable( UART_RX_GPIO_CLK[pUartDevice->Port] );
		drv_rcc_ahb1_clk_enable( UART_DEA_GPIO_CLK[pUartDevice->Port] );
		//			drv_rcc_ahb1_clk_enable( UART_REA_GPIO_CLK[ pUartDevice->Port] );
					// 配置使能控制脚为输出
		drv_gpio_output_init( UART_DEA_GPIO_PORT[pUartDevice->Port], UART_DEA_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		//			drv_gpio_output_init( UART_REA_GPIO_PORT[pUartDevice->Port], UART_REA_GPIO_PIN[ pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
					// 配置引脚为复用功能
		drv_gpio_alternate_function_init( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		drv_gpio_alternate_function_init( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_GPIO_PIN[pUartDevice->Port], GPIO_PUPD_PULL, GPIO_OTYPE_PP, GPIO_SPEED_MID );
		// 连接到串口引脚
		drv_gpio_alternate_function_connect( UART_TX_GPIO_PORT[pUartDevice->Port], UART_TX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		drv_gpio_alternate_function_connect( UART_RX_GPIO_PORT[pUartDevice->Port], UART_RX_PIN_SOURCE[pUartDevice->Port], UART_PORT_GPIO_AF[pUartDevice->Port] );
		// 设置使能模式为同时接收和发送方式
		hal_uart_set_rx_tx_mode( pUartDevice );
		break;
		default:
		break;
	}
}

/**
 * @brief  UART端口初始化
 * @param  pUartDevice: 要操作的串口设备
 * @retval 0：正常	1：参数传入错误	2：发送DMA等待可配置超时·3：接收DMA等待可配置超时
 */
void hal_uart_port_init( UartDeviceType *pUartDevice )
{
	// UART外设引脚配置  
	hal_uart_gpio_init( pUartDevice );

	// 使能UART外设时钟，复位 
	if( UART_PORT[pUartDevice->Port] == USART1 )
	{
		drv_rcc_apb2_clk_enable( UART_PORT_CLK[pUartDevice->Port] );
		//		drv_rcc_apb2_periph_reset_enable(UART_PORT_CLK[pUartDevice->Port]);
		//		drv_rcc_apb2_periph_reset_disable(UART_PORT_CLK[pUartDevice->Port]);
	}
	else
	{
		drv_rcc_apb1_clk_enable( UART_PORT_CLK[pUartDevice->Port] );
		//		drv_rcc_apb1_periph_reset_enable(UART_PORT_CLK[pUartDevice->Port]);
		//		drv_rcc_apb1_periph_reset_disable(UART_PORT_CLK[pUartDevice->Port]);
	}

	drv_uart_deinit( UART_PORT[pUartDevice->Port] );

	// 初始化UART 
	drv_uart_init( UART_PORT[pUartDevice->Port], g_UartBaudTab[pUartDevice->Baudrate], pUartDevice->DataBit, pUartDevice->StopBit, pUartDevice->Parity );

	if( pUartDevice->LinkType != UART_LINK_RX_ONLY )
	{
		if( pUartDevice->RxTxMode == UART_RX_TX_MODE_DMA )
		{
			//使能DMA时钟
			drv_rcc_ahb1_clk_enable( UART_TX_DMA_CLK[pUartDevice->Port] );
			// 初始化UART发送DMA
			drv_dma_stream_init( UART_TX_DMA_CHANNEL[pUartDevice->Port], (UINT32)(pUartDevice->pTxBuffer), (UINT32)(&(UART_PORT[pUartDevice->Port]->TDR)),
				0, DMA_CIRC_MODE_DISABLE, DMA_CHANNEL_PRIORITY_HIGH, DMA_DIR_MEM_TO_PERIPH, DMA_DATA_WIDTH_BYTE );
			drv_uart_dma_tx_enable( UART_PORT[pUartDevice->Port] );
			// 配置DMA发送完成中断
			drv_dma_stream_clear_it_pending_bit( UART_TX_DMA_IT_TCIF[pUartDevice->Port] );
			drv_nvic_init( UART_TX_DMA_IRQn[pUartDevice->Port], 0, PRIO_UART_DMA_TX );
			drv_nvic_enable( UART_TX_DMA_IRQn[pUartDevice->Port] );
			drv_dma_stream_it_enable( UART_TX_DMA_CHANNEL[pUartDevice->Port], DMA_IT_TC );
		}
		else if( pUartDevice->RxTxMode == UART_RX_TX_MODE_INTERRUPT )
		{
			// 配置发送缓冲区空中断
			drv_nvic_init( UART_PORT_IRQn[pUartDevice->Port], 0, 0 );
			drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_TXE );
			drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_TXE );
		}
	}

	if( pUartDevice->LinkType != UART_LINK_TX_ONLY )
	{
		if( pUartDevice->RxTxMode == UART_RX_TX_MODE_DMA )
		{
			//使能DMA时钟
			drv_rcc_ahb1_clk_enable( UART_RX_DMA_CLK[pUartDevice->Port] );
			// 初始化UART接收DMA
			drv_dma_stream_init( UART_RX_DMA_CHANNEL[pUartDevice->Port], (UINT32)(pUartDevice->pRxBuffer), (UINT32)(&(UART_PORT[pUartDevice->Port]->RDR)),
				0, DMA_CIRC_MODE_DISABLE, DMA_CHANNEL_PRIORITY_HIGH, DMA_DIR_PERIPH_TO_MEM, DMA_DATA_WIDTH_BYTE );
			drv_uart_dma_rx_enable( UART_PORT[pUartDevice->Port] );
			// 启动DMA接收
			hal_uart_dma_rx_start( pUartDevice, pUartDevice->pRxBuffer, pUartDevice->RxBytesMax );
			// 配置接收超时中断
			drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_RTO );
			drv_nvic_init( UART_PORT_IRQn[pUartDevice->Port], 0, PRIO_UART_DMA_TX );
			drv_nvic_enable( UART_PORT_IRQn[pUartDevice->Port] );
			//开UART超时中断
			drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_RTO );
			// 开启错误中断
			//drv_uart_clear_it_pending_bit(UART_PORT[pUartDevice->Port], USART_IT_LBD);
			drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_ERR );
			//drv_uart_it_enable(UART_PORT[pUartDevice->Port], USART_IT_LBD);
			drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_ERR );
		}
		else if( pUartDevice->RxTxMode == UART_RX_TX_MODE_INTERRUPT )
		{
			drv_nvic_init( UART_PORT_IRQn[pUartDevice->Port], 0, PRIO_UART_DMA_TX );
			drv_nvic_enable( UART_PORT_IRQn[pUartDevice->Port] );
			drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_RXNE );
			drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_RTO );
			drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_RXNE );
			drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_RTO );
			// 开启错误中断
			//drv_uart_clear_it_pending_bit(UART_PORT[pUartDevice->Port], USART_IT_LBD);
			drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_ERR );
			//drv_uart_it_enable(UART_PORT[pUartDevice->Port], USART_IT_LBD);
			drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_ERR );
		}
	}
}

/**
* @brief  UART设置波特率
* @param  pUartDevice: 要操作的串口设备
* @retval 无
*/
void hal_uart_set_braudrate( UartDeviceType *pUartDevice, enumUartBaudType Baudrate )
{
	if( Baudrate < UART_BAUD_END )
	{
		pUartDevice->Baudrate = Baudrate;
		drv_uart_set_baudrate( UART_PORT[pUartDevice->Port], g_UartBaudTab[pUartDevice->Baudrate] );
	}
}

/**
* @brief  UART设置接收超时时间
* @param  pUartDevice: 要操作的串口设备
* @retval 无
*/
void hal_uart_set_timeout( UartDeviceType *pUartDevice )
{

}

/**
* @brief  UART发送
* @param  pUartDevice: 要操作的串口设备
* @param  pTxData: 要发送的数据
* @param  TxLength: 数据字节数
* @retval 0: 正常发送完成，1: 忙
*/
UINT8 hal_uart_tx_bytes( UartDeviceType *pUartDevice, UINT8 *pTxData, UINT16 TxLength )
{
	// 检查上次发送是否完成
	if( pUartDevice->TxBusyFlag == 1 )
	{
		if( 0 != drv_dma_stream_get_left_length( UART_TX_DMA_CHANNEL[pUartDevice->Port] ) )
		{
			return 1;
		}
	}

	// 根据配置使能输出
	if( (pUartDevice->LinkType == UART_LINK_RX_TX_HALF) || (pUartDevice->LinkType == UART_LINK_RX_TX_HALF_ENABE) )
	{
		hal_uart_set_tx_mode( pUartDevice );
	}

	if( pUartDevice->RxTxMode == UART_RX_TX_MODE_POLL )				// 查询方式发送
	{
		pUartDevice->TxBusyFlag = 1;
		// 发送数据
		drv_uart_put_bytes( UART_PORT[pUartDevice->Port], pTxData, TxLength );

		// 发送完成切换到接收模式
		if( (pUartDevice->LinkType == UART_LINK_RX_TX_HALF) || (pUartDevice->LinkType == UART_LINK_RX_TX_HALF_ENABE) )
		{
			while( RESET != drv_uart_get_flag_status( UART_PORT[pUartDevice->Port], USART_FLAG_TC ) );
			hal_uart_set_rx_mode( pUartDevice );
			drv_uart_clear_flag_status( UART_PORT[pUartDevice->Port], USART_FLAG_TC );
		}
		pUartDevice->TxBusyFlag = 0;
	}
	else if( pUartDevice->RxTxMode == UART_RX_TX_MODE_INTERRUPT )		// 中断方式发送
	{
		// 发送前的准备
		pUartDevice->TxCounter = 0;
		pUartDevice->TxLength = TxLength;
		if( pUartDevice->pTxBuffer != pTxData )
		{
			pUartDevice->pTxBuffer = pTxData;
		}
		// 启动中断发送
		drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_TXE );
		drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_TXE );
		pUartDevice->TxBusyFlag = 1;
	}
	else															// DMA方式发送
	{
		drv_dma_stream_clear_flag_status( UART_TX_DMA_IT_TCIF[pUartDevice->Port] );
		if( pTxData == 0 )
		{
			drv_dma_stream_start_mem_to_periph( UART_TX_DMA_CHANNEL[pUartDevice->Port], (UINT32)pUartDevice->pTxBuffer, pUartDevice->TxLength );
		}
		else
		{
			drv_dma_stream_start_mem_to_periph( UART_TX_DMA_CHANNEL[pUartDevice->Port], (UINT32)pTxData, TxLength );
		}
		pUartDevice->TxBusyFlag = 1;
	}

	return 0;
}

/**
* @brief  UART使用DMA接收
* @param  pUartDevice: 要操作的串口设备
* @param  pRxData: 接收数据缓冲区
* @param  RxLength: 数据字节数
* @retval 无
*/
void hal_uart_dma_rx_start( UartDeviceType *pUartDevice, UINT8 *pRxData, UINT16 RxLength )
{
	//drv_dma_stream_disable( UART_RX_DMA_CHANNEL[pUartDevice->Port] );
	// 清中断标志
	drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_RTO );
	drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_LBD );
	drv_uart_clear_it_pending_bit( UART_PORT[pUartDevice->Port], USART_IT_ERR );
	//使能DMA 使能前清楚标志位
	//drv_dma_stream_clear_flag_status( UART_RX_DMA_FLAG_GIF[ pUartDevice->Port ] );
	drv_dma_stream_start_periph_to_mem( UART_RX_DMA_CHANNEL[pUartDevice->Port], (UINT32)(pRxData), RxLength );
}

///**
//* @brief  UART重新启动DMA接收
//* @param  pUartDevice: 要操作的串口设备
//* @retval 无
//*/
//void hal_uart_dma_rx_restart( UartDeviceType *pUartDevice )
//{
//    *pUartDevice->pRxFinishFlag = 0;
//    *pUartDevice->pRxLength = 0;
//
//    // 重新设置接收地址和长度，并启动DMA接收
//    drv_dma_set_mem_addr_length( UART_RX_DMA_CHANNEL[pUartDevice->Port], (UINT32)pUartDevice->pRxBuffer, pUartDevice->RxBytesMax );
//    drv_dma_stream_enable( UART_RX_DMA_CHANNEL[pUartDevice->Port] );
//}

/**
* @brief  串口接收中断使能
* @note   在主任务进行关键数据计算的时候使用
* @param  pUartDevice: 要操作的串口设备
* @retval 无
*/
void hal_uart_rx_irq_enable( UartDeviceType *pUartDevice )
{
	if( pUartDevice->RxTxMode == UART_RX_TX_MODE_INTERRUPT )
	{
		// 使能串口接收中断
		drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_RXNE );
	}
	else if( pUartDevice->RxTxMode == UART_RX_TX_MODE_DMA )
	{
		drv_uart_it_enable( UART_PORT[pUartDevice->Port], USART_IT_RTO );
	}
}

/**
* @brief  串口接收中断禁止
* @note   在主任务进行关键数据计算的时候使用
* @param  pUartDevice: 要操作的串口设备
* @retval 无
*/
void hal_uart_rx_irq_disable( UartDeviceType *pUartDevice )
{
	if( pUartDevice->RxTxMode == UART_RX_TX_MODE_INTERRUPT )
	{
		// 使能串口接收中断
		drv_uart_it_disable( UART_PORT[pUartDevice->Port], USART_IT_RXNE );
	}
	else if( pUartDevice->RxTxMode == UART_RX_TX_MODE_DMA )
	{
		drv_uart_it_disable( UART_PORT[pUartDevice->Port], USART_IT_RTO );
	}
}

///**
//* @brief  串口等待方式接收一个字节
//* @param  pUartDevice: 要操作的串口设备
//* @param  pDat: 接收的字节
//* @param  TimeOut: 超时时间，单位us
//* @retval 0：成功 1：失败
//*/
//UINT8 hal_uart_get_byte_with_timeout( UartDeviceType *pUartDevice, UINT8 *pDat, UINT32 TimeOut )
//{
//	UsartIsrType Sr;
//	while (TimeOut--)
//	{
//		Sr.all = UART_PORT[pUartDevice->Port]->ISR.all;
//		if (Sr.bit.RXNE != RESET)
//		{
//			*pDat = (UINT8)(UART_PORT[pUartDevice->Port]->RDR.all & 0xFF);
//			return 0;
//		}
//		hal_delay_us(1);
//	}
//	return 1;
//}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////																													////////
/////////										/** 中断服务函数 */															////////
/////////																													////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
* @brief  串口1 DMA发送中断服务函数
* @retval 无
*/
void uart_com_tx_dma_isr()
{
	if( drv_dma_stream_get_it_status( UART_TX_DMA_CHANNEL[UART_COM], UART_TX_DMA_IT_TCIF[UART_COM] ) )
	{
		drv_dma_stream_disable( UART_TX_DMA_CHANNEL[UART_COM] );
		drv_uart_it_enable( UART_PORT[UART_COM], USART_IT_TC );
		drv_dma_stream_clear_it_pending_bit( UART_TX_DMA_IT_TCIF[UART_COM] );
	}
}

/**
* @brief  串口1中断服务函数
* @retval 无
*/
void uart_com_isr( void )
{
	UsartIsrType l_Sr;
	l_Sr.all = UART_PORT[UART_COM]->ISR.all;

	if( l_Sr.bit.RTOF == 1 )		//接收超时中断
	{
		drv_uart_clear_it_pending_bit( UART_PORT[UART_COM], USART_IT_RTO );
		drv_dma_stream_disable( UART_RX_DMA_CHANNEL[UART_COM] );

		// 处理数据
		*g_UartDevice[UART_COM].pRxLength = g_UartDevice[UART_COM].RxBytesMax - drv_dma_stream_get_left_length( UART_RX_DMA_CHANNEL[UART_COM] );
		*(g_UartDevice[UART_COM].pRxFinishFlag) = 1;
		//      hal_3048_msg_packet_process( &g_UartDevice[UART_COM] );
			  //*g_UartDevice[ UART_COM ].pRxFinishFlag = 0;
			  //*g_UartDevice[ UART_COM ].pRxLength = 0;

			  // 重新设置接收地址和长度，并启动DMA接收
		drv_dma_set_mem_addr_length( UART_RX_DMA_CHANNEL[UART_COM], (UINT32)g_UartDevice[UART_COM].pRxBuffer, g_UartDevice[UART_COM].RxBytesMax );
		drv_dma_stream_enable( UART_RX_DMA_CHANNEL[UART_COM] );
	}
	else if( l_Sr.bit.RXNE == 1 )	// 接收数据中断
	{
		drv_uart_clear_it_pending_bit( UART_PORT[UART_COM], USART_IT_RXNE );
		g_UartDevice[UART_COM].pRxBuffer[*g_UartDevice[UART_COM].pRxLength++] = drv_uart_rx_byte( UART_PORT[UART_COM] );

		//drv_uart_it_enable(UART_PORT[ UART_COM ], USART_IT_RTO );
	}
	else if( (l_Sr.bit.TXE == 1) || (l_Sr.bit.TC == 1) )
	{
		if( l_Sr.bit.TC == 1 )
		{
			drv_uart_clear_it_pending_bit( UART_PORT[UART_COM], USART_IT_TC );
			g_UartDevice[UART_COM].TxBusyFlag = 0;
			// 方式完成，根据配置切换到接收模式
			if( (g_UartDevice[UART_COM].LinkType == UART_LINK_RX_TX_HALF) || (g_UartDevice[UART_COM].LinkType == UART_LINK_RX_TX_HALF_ENABE) )
			{
				hal_uart_set_rx_mode( &(g_UartDevice[UART_COM]) );
			}
		}
		else if( l_Sr.bit.TXE == 1 )
		{
			drv_uart_clear_it_pending_bit( UART_PORT[UART_COM], USART_IT_TXE );
			if( g_UartDevice[UART_COM].TxCounter >= g_UartDevice[UART_COM].TxLength )
			{
				drv_uart_it_disable( UART_PORT[UART_COM], USART_IT_TXE );
				// 清发送完成中断标志，并打开发送完成中断
				drv_uart_clear_it_pending_bit( UART_PORT[UART_COM], USART_IT_TC );
				drv_uart_it_enable( UART_PORT[UART_COM], USART_IT_TC );
			}
			else
			{
				drv_uart_tx_byte( UART_PORT[UART_COM], g_UartDevice[UART_COM].pTxBuffer[g_UartDevice[UART_COM].TxCounter++] );
			}
		}
	}
	else if( (l_Sr.bit.PE == 1) || (l_Sr.bit.FE == 1) || (l_Sr.bit.NF == 1) || (l_Sr.bit.ORE == 1) || (l_Sr.bit.LBDF == 1) )
	{
		//错误处理
		hal_uart_port_init( &g_UartDevice[UART_COM] );
	}
}


/**
* @brief  串口2 DMA发送中断服务函数
* @retval 无
*/
void uart_extern_tx_dma_isr()
{
	if( drv_dma_stream_get_it_status( UART_TX_DMA_CHANNEL[UART_EXTERN], UART_TX_DMA_IT_TCIF[UART_EXTERN] ) )
	{
		drv_dma_stream_disable( UART_TX_DMA_CHANNEL[UART_EXTERN] );
		drv_uart_it_enable( UART_PORT[UART_EXTERN], USART_IT_TC );
		drv_dma_stream_clear_it_pending_bit( UART_TX_DMA_IT_TCIF[UART_EXTERN] );
	}
}

/**
* @brief  串口2中断服务函数
* @retval 无
*/
void uart_extern_isr( void )
{
	volatile UsartIsrType l_Sr;
	UsartCr1Type l_Cr1;

	l_Sr.all = UART_PORT[UART_EXTERN]->ISR.all;
	l_Cr1.all = UART_PORT[UART_EXTERN]->CR1.all;

	if( l_Sr.bit.RTOF == 1 )		//接收超时中断
	{
		if( l_Cr1.bit.RTOIE == 1 )
		{
			drv_uart_clear_it_pending_bit( UART_PORT[UART_EXTERN], USART_IT_RTO );
			drv_dma_stream_disable( UART_RX_DMA_CHANNEL[UART_EXTERN] );

			// 处理数据
			*g_UartDevice[UART_EXTERN].pRxLength = g_UartDevice[UART_EXTERN].RxBytesMax - drv_dma_stream_get_left_length( UART_RX_DMA_CHANNEL[UART_EXTERN] );
			*(g_UartDevice[UART_EXTERN].pRxFinishFlag) = 1;
			app_uart_extern_msg_packet_process( &g_UartDevice[UART_EXTERN] );
			// 重新设置接收地址和长度，并启动DMA接收
			drv_dma_set_mem_addr_length( UART_RX_DMA_CHANNEL[UART_EXTERN], (UINT32)g_UartDevice[UART_EXTERN].pRxBuffer, g_UartDevice[UART_EXTERN].RxBytesMax );
			drv_dma_stream_enable( UART_RX_DMA_CHANNEL[UART_EXTERN] );
		}
	}
	//else if (l_Sr.bit.RXNE == 1)	// 接收数据中断
	//{
 //       if( l_Cr1.bit.RXNEIE == 1 )
 //       {
 //           drv_uart_clear_it_pending_bit( UART_PORT[UART_EXTERN], USART_IT_RXNE );
 //           g_UartDevice[UART_EXTERN].pRxBuffer[*g_UartDevice[UART_EXTERN].pRxLength++] = drv_uart_rx_byte( UART_PORT[UART_EXTERN] );
	//	    //drv_uart_it_enable(UART_PORT[ UART_COM ], USART_IT_RTO );
 //       }
	//}
//	else if( ( l_Sr.bit.TXE == 1 ) || ( l_Sr.bit.TC == 1 ) )
//	{
	if( l_Cr1.bit.TCIE == 1 )
	{
		if( l_Sr.bit.TC == 1 )
		{
			drv_uart_clear_it_pending_bit( UART_PORT[UART_EXTERN], USART_IT_TC );
			g_UartDevice[UART_EXTERN].TxBusyFlag = 0;
			// 方式完成，根据配置切换到接收模式
			if( (g_UartDevice[UART_EXTERN].LinkType == UART_LINK_RX_TX_HALF) || (g_UartDevice[UART_EXTERN].LinkType == UART_LINK_RX_TX_HALF_ENABE) )
			{
				hal_uart_set_rx_mode( &(g_UartDevice[UART_EXTERN]) );
			}
		}
	}
	//		else if( l_Sr.bit.TXE == 1 )
	//		{
	//            if( l_Cr1.bit.TXEIE == 1 )
	//            {
	//                drv_uart_clear_it_pending_bit( UART_PORT[UART_EXTERN], USART_IT_TXE );
	//                if( g_UartDevice[UART_EXTERN].TxCounter >= g_UartDevice[UART_EXTERN].TxLength )
	//                {
	//                    drv_uart_it_disable( UART_PORT[UART_EXTERN], USART_IT_TXE );
	//                    // 清发送完成中断标志，并打开发送完成中断
	//                    drv_uart_clear_it_pending_bit( UART_PORT[UART_EXTERN], USART_IT_TC );
	//                    drv_uart_it_enable( UART_PORT[UART_EXTERN], USART_IT_TC );
	//                }
	//                else
	//                {
	//                    drv_uart_tx_byte( UART_PORT[UART_EXTERN], g_UartDevice[UART_EXTERN].pTxBuffer[g_UartDevice[UART_EXTERN].TxCounter++] );
	//                }
	//            }
	//		}		
	//	}

	if( (l_Sr.bit.PE == 1) || (l_Sr.bit.FE == 1) || (l_Sr.bit.NF == 1) || (l_Sr.bit.ORE == 1) || (l_Sr.bit.LBDF == 1) )
	{
		//错误处理
		hal_uart_port_init( &g_UartDevice[UART_EXTERN] );
	}
}


