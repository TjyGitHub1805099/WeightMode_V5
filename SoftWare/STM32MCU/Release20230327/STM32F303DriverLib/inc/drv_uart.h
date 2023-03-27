/**
*******************************************************************
* @file    drv_uart.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x串口模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_UART_H__
#define __DRV_UART_H__


#include "reg_stm32f303_uart.h"


#define USART_CR1_OVER8                     ((UINT32)0x00008000)

#define IT_MASK								((UINT32)0x000000FF)
/* USART中断定义 */
#define USART_IT_WU                          ((UINT32)0x00140316)
#define USART_IT_CM                          ((UINT32)0x0011010E)
#define USART_IT_EOB                         ((UINT32)0x000C011B)
#define USART_IT_RTO                         ((UINT32)0x000B011A)
#define USART_IT_PE                          ((UINT32)0x00000108)
#define USART_IT_TXE                         ((UINT32)0x00070107)
#define USART_IT_TC                          ((UINT32)0x00060106)
#define USART_IT_RXNE                        ((UINT32)0x00050105)
#define USART_IT_IDLE                        ((UINT32)0x00040104)
#define USART_IT_LBD                         ((UINT32)0x00080206)
#define USART_IT_CTS                         ((UINT32)0x0009030A) 
#define USART_IT_ERR                         ((UINT32)0x00000300)
#define USART_IT_ORE                         ((UINT32)0x00030300)
#define USART_IT_NE                          ((UINT32)0x00020300)
#define USART_IT_FE                          ((UINT32)0x00010300)
/* USART标志位定义 */
#define USART_FLAG_PE                        ((UINT32)0x00000001)            /*!< Parity Error */
#define USART_FLAG_FE                        ((UINT32)0x00000002)            /*!< Framing Error */
#define USART_FLAG_NE                        ((UINT32)0x00000004)            /*!< Noise detected Flag */
#define USART_FLAG_ORE                       ((UINT32)0x00000008)            /*!< OverRun Error */
#define USART_FLAG_IDLE                      ((UINT32)0x00000010)            /*!< IDLE line detected */
#define USART_FLAG_RXNE                      ((UINT32)0x00000020)            /*!< Read Data Register Not Empty */
#define USART_FLAG_TC                        ((UINT32)0x00000040)            /*!< Transmission Complete */
#define USART_FLAG_TXE                       ((UINT32)0x00000080)            /*!< Transmit Data Register Empty */
#define USART_FLAG_LBD                       ((UINT32)0x00000100)            /*!< LIN Break Detection Flag */
#define USART_FLAG_CTS                     	 ((UINT32)0x00000200)            /*!< CTS interrupt flag */
#define USART_FLAG_nCTSS                     ((UINT32)0x00000400)            /*!< CTS flag */
#define USART_FLAG_RTO                       ((UINT32)0x00000800)            /*!< Receiver Time Out */
#define USART_FLAG_EOB                       ((UINT32)0x00001000)            /*!< End Of Block Flag */
#define USART_FLAG_ABRE                      ((UINT32)0x00004000)            /*!< Auto-Baud Rate Error */
#define USART_FLAG_ABRF                      ((UINT32)0x00008000)            /*!< Auto-Baud Rate Flag */
#define USART_FLAG_BUSY                      ((UINT32)0x00010000)            /*!< Busy Flag */
#define USART_FLAG_CM                        ((UINT32)0x00020000)            /*!< Character Match Flag */
#define USART_FLAG_SBK                       ((UINT32)0x00040000)            /*!< Send Break Flag */
#define USART_FLAG_RWU                       ((UINT32)0x00080000)            /*!< Receive Wake Up from mute mode Flag */
#define USART_FLAG_WU                        ((UINT32)0x00100000)            /*!< Wake Up from stop mode Flag */
#define USART_FLAG_TEACK                     ((UINT32)0x00200000)            /*!< Transmit Enable Acknowledge Flag */
#define USART_FLAG_REACK                     ((UINT32)0x00400000)            /*!< Receive Enable Acknowledge Flag */

							 
							
/** 串口数据位定义 */
typedef enum UartDataBitType
{
	UART_DATABIT_8 = 0,                             /**< 八个数据位 */
	UART_DATABIT_9,                                 /**< 九个数据位 */
	UART_DATABIT_7									/**< 七个数据位 */
}enumUartDataBitType;

/** 串口停止位定义 */
typedef enum UartStopBitType
{
	UART_STOPBIT_1 = 0,								/**< 一个停止位 */
	UART_STOPBIT_0_5,								/**< 零点五个停止位 */
	UART_STOPBIT_2,                             	/**< 两个停止位 */
	UART_STOPBIT_1_5,								/**< 一点五停止位 */
}enumUartStopBitType;

/** 串口校验位定义 */
typedef enum UartParityBitType
{
	UART_PARITY_NONE = 0,                           /**< 无校验 */
	UART_PARITY_EVEN = 2,                           /**< 偶校验 */
	UART_PARITY_ODD = 3                             /**< 奇校验 */
}enumUartParityBitType;

/**
* @brief  通过串口发送一个字节数据.
* @param  pUart: UART1~UART6
* @param  Data: 要发送的数据.
* @retval 无
*/
void __INLINE drv_uart_tx_byte( UsartType *pUart, UINT8 Data )
{
	pUart->TDR.all = Data;
}

/**
* @brief  从串口接收一个字节数据.
* @param  pUart: UART1~UART6
* @retval 接收到的数据.
*/
UINT8 __INLINE drv_uart_rx_byte( UsartType *pUart )
{
	UsartRdrType l_Rdr;
	l_Rdr.all = pUart->RDR.all;
	
	return ( l_Rdr.all & 0xFF );
}


extern void drv_uart_deinit( UsartType *pUart );
extern void drv_uart_set_baudrate( UsartType *pUart, UINT32 UartBaudrate );
extern void drv_uart_init( UsartType *pUart, UINT32 Baudrate, enumUartDataBitType DataBit, enumUartStopBitType StopBit, enumUartParityBitType Parity );
extern void drv_uart_enable( UsartType *pUart );
extern void drv_uart_disable( UsartType *pUart );
extern void drv_uart_tx_enable( UsartType *pUart );
extern void drv_uart_tx_disable( UsartType *pUart );
extern void drv_uart_rx_enable( UsartType *pUart );
extern void drv_uart_rx_disable( UsartType *pUart );
extern void drv_uart_dma_tx_enable( UsartType *pUart );
extern void drv_uart_dma_tx_disable( UsartType *pUart );
extern void drv_uart_dma_rx_enable( UsartType *pUart );
extern void drv_uart_dma_rx_disable( UsartType *pUart );
extern void drv_uart_it_enable( UsartType *pUart, UINT32 UartIt );
extern void drv_uart_it_disable( UsartType *pUart, UINT32 UartIt );
extern FlagStatus drv_uart_get_flag_status( UsartType *pUart, UINT32 UartFlag );
extern void drv_uart_clear_flag_status( UsartType *pUart, UINT32 UartFlag );
extern ITStatus drv_uart_get_it_status( UsartType *pUart, UINT32 UartItFlag );
extern void drv_uart_clear_it_pending_bit( UsartType *pUart, UINT32 UartItFlag );

extern UINT8 drv_uart_get_error_status( UsartType *pUart );
extern UINT8 drv_uart_get_byte_blocking( UsartType *pUart );
extern UINT8 drv_uart_get_byte_noblocking( UsartType *pUart, UINT8 *pDat );
extern void drv_uart_put_bytes( UsartType *pUart, UINT8 *pDat, UINT32 Length );
extern void drv_uart_put_string( UsartType *pUart, const char *pString );
//extern void __INLINE drv_uart_tx_byte( UsartType *pUart, UINT8 Data );
//extern UINT8 __INLINEdrv_uart_rx_byte( UsartType *pUart );


#endif
