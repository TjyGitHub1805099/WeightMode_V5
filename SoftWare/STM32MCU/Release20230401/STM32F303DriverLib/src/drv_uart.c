/**
*******************************************************************
* @file    drv_uart.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x串口模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/


#include "drv_rcc.h"
#include "drv_uart.h"



/**
* @brief  串口寄存器恢复为默认值
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_deinit( UsartType *pUart )
{
	if( pUart == USART1 )
	{
		drv_rcc_apb2_periph_reset_enable( RCC_APB2RSTR_USART1RST );
		drv_rcc_apb2_periph_reset_disable( RCC_APB2RSTR_USART1RST );
	}
	else if( pUart == USART2 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_USART2RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_USART2RST );
	}
	else if( pUart == USART3 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_USART3RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_USART3RST );
	}
	else if( pUart == UART4 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_UART4RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_UART4RST );
	}
	else 
	{
		if( pUart == UART5 )
		{
			drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_UART5RST );
			drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_UART5RST );
		}
	}
}

/**
* @brief  设置串口波特率(常用波特率)
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @param  UartBaudrate: 波特率
* @retval 无
*/
void drv_uart_set_baudrate(UsartType *pUart, UINT32 UartBaudrate)
{
	UINT32 apbclock = 0, divider = 0, tmpreg = 0;

	pUart->CR1.bit.UE = 0;		//禁止串口外设
	if( pUart == USART1 )
	{
		apbclock = g_ClockFrequency.Apb2Freq;
	}
	else
	{
		apbclock = g_ClockFrequency.Apb1Freq;
	}
	if( pUart->CR1.bit.OVER8 != 0 )		//8倍过采
	{
		divider = (UINT32)(( 2 * apbclock) / UartBaudrate );
		tmpreg  = (UINT32)(( 2 * apbclock) % UartBaudrate );
	}
	else 	//16倍过采
	{
		divider = (UINT32)((apbclock) / UartBaudrate );
		tmpreg  = (UINT32)((apbclock) % UartBaudrate );
	}
	if( tmpreg >= UartBaudrate / 2)
	{
		divider++;
	} 
	if( pUart->CR1.bit.OVER8 != 0 )
	{	// BRR[15:4] = DIV[15:4]
		// OVER = 0, BRR[3:0] = DIV[3:0]
		// OVER = 1, BRR[3:0] = DIV[3:0] >> 1,BRR[3] = 0;
		tmpreg = (divider & (UINT16)0x000F) >> 1;
		divider = (divider & (UINT16)0xFFF0) | tmpreg;
	}
	
	pUart->BRR.all = (UINT16)divider;
	pUart->CR1.bit.UE = 1;			//使能串口外设
}

/**
* @brief  串口初始化
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @param  UartBaudrate: 串口波特率
* @param  UartDataBit: 串口数据位数
* @param  UartStopBit: 串口停止位数
* @param  UartParity: 串口校验
* @retval 无
*/
void drv_uart_init(UsartType *pUart, UINT32 Baudrate, enumUartDataBitType DataBit, enumUartStopBitType StopBit, enumUartParityBitType Parity )
{ 
	pUart->CR1.bit.UE		= 0; 				// 关闭串口
	pUart->CR3.all			= 0;				// 无硬件流控制 
	pUart->CR2.bit.STOP		= (UINT16)StopBit;	// 停止位 
	pUart->CR1.bit.PARITY	= (UINT16)Parity;	// 奇偶校验
	pUart->CR1.bit.RE		= 1;				// 接收使能 
	pUart->CR1.bit.TE		= 1;				// 发送使能 
	pUart->CR2.bit.RTOEN	= 1;				//使能超时模式
	pUart->RTOR.bit.RTO		= 35;				//接收超时
	switch( DataBit )							//停止位
	{
		case UART_DATABIT_7 : pUart->CR1.bit.M0 = 0; pUart->CR1.bit.M1 = 1; break;
		case UART_DATABIT_8 : pUart->CR1.bit.M0 = 0; pUart->CR1.bit.M1 = 0; break;
		case UART_DATABIT_9 : pUart->CR1.bit.M0 = 1; pUart->CR1.bit.M1 = 0; break;
		default : break;
	}
	drv_uart_set_baudrate( pUart, Baudrate );	// 波特率设置     
	pUart->ICR.all			= 0xFFFFFFFF;
	pUart->CR1.bit.UE		= 1;				// 使能串口
}

/**
* @brief  串口使能
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_enable( UsartType *pUart )
{
	pUart->CR1.bit.UE = 1;
}

/**
* @brief  串口禁止
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_disable( UsartType *pUart )
{
	pUart->CR1.bit.UE = 0;
}

/**
* @brief  串口发送使能
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_tx_enable( UsartType *pUart )
{
	pUart->CR1.bit.TE = 1;
}

/**
* @brief  串口发送禁止
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_tx_disable( UsartType *pUart )
{
	pUart->CR1.bit.TE = 0;
}

/**
* @brief  串口接收使能
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_rx_enable( UsartType *pUart )
{
	pUart->CR1.bit.RE = 1;
}

/**
* @brief  串口接收禁止
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_rx_disable( UsartType *pUart )
{
	pUart->CR1.bit.RE = 0;
}

/**
* @brief  串口发送DMA使能
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_dma_tx_enable( UsartType *pUart )
{
	pUart->CR3.bit.DMAT = 1;
}

/**
* @brief  串口发送DMA禁止
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_dma_tx_disable( UsartType *pUart )
{
	pUart->CR3.bit.DMAT = 0;
}

/**
* @brief  串口接收DMA使能
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_dma_rx_enable( UsartType *pUart )
{
	pUart->CR3.bit.DMAR = 1;
}

/**
* @brief  串口接收DMA禁止
* @param  pUart: USART1 USART2 USART3 UART4 UART5
* @retval 无
*/
void drv_uart_dma_rx_disable( UsartType *pUart )
{
	pUart->CR3.bit.DMAR= 0;
}

/**
* @brief  使能指定串口中断.
* @param  pUart: UART1~UART6
* @param  UartIt: 指定的串口中断源，可以是下面值的一个:
  *         @arg USART_IT_WU:  Wake up interrupt.
  *         @arg USART_IT_CM:  Character match interrupt.
  *         @arg USART_IT_EOB:  End of block interrupt.
  *         @arg USART_IT_RTO:  Receive time out interrupt.
  *         @arg USART_IT_CTS:  CTS change interrupt.
  *         @arg USART_IT_LBD:  LIN Break detection interrupt.
  *         @arg USART_IT_TXE:  Transmit Data Register empty interrupt.
  *         @arg USART_IT_TC:  Transmission complete interrupt.
  *         @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
  *         @arg USART_IT_IDLE:  Idle line detection interrupt.
  *         @arg USART_IT_PE:  Parity Error interrupt.
  *         @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
* @retval 无
*/
void drv_uart_it_enable( UsartType *pUart, UINT32 UartIt )
{
	UINT32 l_UsartRegsiter = 0x00, l_UsartItPosition = 0x00, l_UsartItMask = 0x00;

	l_UsartRegsiter = ( ( (UINT16)UartIt ) >> 0x08 );
	l_UsartItPosition = UartIt & IT_MASK;
	l_UsartItMask = ( ( (UINT32)0x01 ) << l_UsartItPosition );

	if ( l_UsartRegsiter == 0x02 ) //CR2
	{
		pUart->CR2.all |= l_UsartItMask;
	}
	else if ( l_UsartRegsiter == 0x03 ) //CR3
	{
		pUart->CR3.all |= l_UsartItMask;
	}
	else 	//CR1
	{
		pUart->CR1.all |= l_UsartItMask;
	}
}

/**
* @brief  禁止指定串口中断.
* @param  pUart: UART1~UART6
* @param  UartIt: 指定的串口中断源，可以是下面值的一个:
  *         @arg USART_IT_WU:  Wake up interrupt.
  *         @arg USART_IT_CM:  Character match interrupt.
  *         @arg USART_IT_EOB:  End of block interrupt.
  *         @arg USART_IT_RTO:  Receive time out interrupt.
  *         @arg USART_IT_CTS:  CTS change interrupt.
  *         @arg USART_IT_LBD:  LIN Break detection interrupt.
  *         @arg USART_IT_TXE:  Transmit Data Register empty interrupt.
  *         @arg USART_IT_TC:  Transmission complete interrupt.
  *         @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
  *         @arg USART_IT_IDLE:  Idle line detection interrupt.
  *         @arg USART_IT_PE:  Parity Error interrupt.
  *         @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
* @retval 无
*/
void drv_uart_it_disable( UsartType *pUart, UINT32 UartIt )
{
	UINT32 l_UsartRegsiter = 0x00, l_UsartItPosition = 0x00, l_UsartItMask = 0x00;

	l_UsartRegsiter = ( ( (UINT16)UartIt ) >> 0x08 );
	l_UsartItPosition = UartIt & IT_MASK;
	l_UsartItMask = ( ( (UINT32)0x01 ) << l_UsartItPosition );

	if ( l_UsartRegsiter == 0x02 ) //CR2
	{
		pUart->CR2.all &= ~l_UsartItMask;
	}
	else if ( l_UsartRegsiter == 0x03 ) //CR3
	{
		pUart->CR3.all &= ~l_UsartItMask;
	}
	else 	//CR1
	{
		pUart->CR1.all &= ~l_UsartItMask;
	}
}

/**
* @brief  检查串口标志.
* @param  pUart: UART1~UART6
* @param  UartFlag: 要检查的标志，可以是下面值的一个:
  *         @arg USART_FLAG_REACK:  Receive Enable acknowledge flag.
  *         @arg USART_FLAG_TEACK:  Transmit Enable acknowledge flag.
  *         @arg USART_FLAG_WUF:  Wake up flag.
  *         @arg USART_FLAG_RWU:  Receive Wake up flag.
  *         @arg USART_FLAG_SBK:  Send Break flag.
  *         @arg USART_FLAG_CMF:  Character match flag.
  *         @arg USART_FLAG_BUSY:  Busy flag.
  *         @arg USART_FLAG_ABRF:  Auto baud rate flag.
  *         @arg USART_FLAG_ABRE:  Auto baud rate error flag.
  *         @arg USART_FLAG_EOBF:  End of block flag.
  *         @arg USART_FLAG_RTOF:  Receive time out flag.
  *         @arg USART_FLAG_nCTSS:  Inverted nCTS input bit status.
  *         @arg USART_FLAG_CTS:  CTS Change flag.
  *         @arg USART_FLAG_LBD:  LIN Break detection flag.
  *         @arg USART_FLAG_TXE:  Transmit data register empty flag.
  *         @arg USART_FLAG_TC:  Transmission Complete flag.
  *         @arg USART_FLAG_RXNE:  Receive data register not empty flag.
  *         @arg USART_FLAG_IDLE:  Idle Line detection flag.
  *         @arg USART_FLAG_ORE:  OverRun Error flag.
  *         @arg USART_FLAG_NE:  Noise Error flag.
  *         @arg USART_FLAG_FE:  Framing Error flag.
  *         @arg USART_FLAG_PE:  Parity Error flag.
* @retval 当前状态.
*/
FlagStatus drv_uart_get_flag_status( UsartType *pUart, UINT32 UartFlag )
{
	if (( pUart->ISR.all & UartFlag ) != (UINT16)RESET )
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清串口挂起的标志.
* @param  pUart: UART1~UART6
* @param  UartFlag: 要清的标志，可以是下面值的组合:
  *         @arg USART_FLAG_WUF:  Wake up flag.
  *         @arg USART_FLAG_CMF:  Character match flag.
  *         @arg USART_FLAG_EOBF:  End of block flag.
  *         @arg USART_FLAG_RTOF:  Receive time out flag.
  *         @arg USART_FLAG_CTS:  CTS Change flag.
  *         @arg USART_FLAG_LBD:  LIN Break detection flag.
  *         @arg USART_FLAG_TC:  Transmission Complete flag.
  *         @arg USART_FLAG_IDLE:  IDLE line detected flag.
  *         @arg USART_FLAG_ORE:  OverRun Error flag.
  *         @arg USART_FLAG_NE: Noise Error flag.
  *         @arg USART_FLAG_FE: Framing Error flag.
  *         @arg USART_FLAG_PE:   Parity Errorflag.
  *
  * @note
  *   - RXNE pending bit is cleared by a read to the USART_RDR register 
  *     (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register USART_RQR
  *     (USART_RequestCmd()).
  *   - TC flag can be also cleared by software sequence: a read operation to 
  *     USART_SR register (USART_GetFlagStatus()) followed by a write operation
  *     to USART_TDR register (USART_SendData()).
  *   - TXE flag is cleared by a write to the USART_TDR register 
  *     (USART_SendData()) or by writing 1 to the TXFRQ in the register USART_RQR
  *     (USART_RequestCmd()).
  *   - SBKF flag is cleared by 1 to the SBKRQ in the register USART_RQR
  *     (USART_RequestCmd()).
*
* @retval 无
*/
void drv_uart_clear_flag_status( UsartType *pUart, UINT32 UartFlag )
{
	pUart->ICR.all = UartFlag;
}

/**
* @brief  检查串口中断状态.
* @param  pUart: UART1~UART6
* @param  UartItFlag: 要检查的中断状态，可以是下面值的一个:
*            @arg USART_IT_CTS:  CTS change interrupt (not available for UART4 and UART5)
*            @arg USART_IT_LBD:  LIN Break detection interrupt
*            @arg USART_IT_TXE:  Transmit Data Register empty interrupt
*            @arg USART_IT_TC:   Transmission complete interrupt
*            @arg USART_IT_RXNE: Receive Data register not empty interrupt
*            @arg USART_IT_IDLE: Idle line detection interrupt
*            @arg USART_IT_ORE_RX : OverRun Error interrupt if the RXNEIE bit is set
*            @arg USART_IT_ORE_ER : OverRun Error interrupt if the EIE bit is set
*            @arg USART_IT_NE:   Noise Error interrupt
*            @arg USART_IT_FE:   Framing Error interrupt
*            @arg USART_IT_PE:   Parity Error interrupt
* @retval 当前状态.
*/
ITStatus drv_uart_get_it_status( UsartType *pUart, UINT32 UartItFlag )
{
	UINT32 l_UsartRegsiter = 0x00, l_UsartItPosition = 0x00, l_UsartItMask = 0x00;

	l_UsartRegsiter = (((UINT16)UartItFlag ) >> 0x08 );
	l_UsartItMask = UartItFlag & IT_MASK;
	l_UsartItMask = (UINT32)0x01 << l_UsartItMask;

	if ( l_UsartRegsiter == 0x01 )		//CR1
	{
		l_UsartItMask &= pUart->CR1.all;
	}
	else if ( l_UsartRegsiter == 0x02 ) //CR2
	{
		l_UsartItMask &= pUart->CR2.all;
	}
	else 								//CR3
	{
		l_UsartItMask &= pUart->CR3.all;
	}

	l_UsartItPosition = UartItFlag >> 0x10;
	l_UsartItPosition = (UINT32)0x01 << l_UsartItPosition;
	l_UsartItPosition &= pUart->ISR.all;
	if (( l_UsartItMask != (UINT16)RESET ) && ( l_UsartItPosition != (UINT16)RESET ))
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  清串口中断挂起位.
* @param  pUart: UART1~UART6
* @param  UartItFlag: 要清的中断状态，可以是下面值的一个:
  *         @arg USART_IT_WU:  Wake up interrupt.
  *         @arg USART_IT_CM:  Character match interrupt.
  *         @arg USART_IT_EOB:  End of block interrupt.
  *         @arg USART_IT_RTO:  Receive time out interrupt.
  *         @arg USART_IT_CTS:  CTS change interrupt.
  *         @arg USART_IT_LBD:  LIN Break detection interrupt.
  *         @arg USART_IT_TC:  Transmission complete interrupt.
  *         @arg USART_IT_IDLE:  IDLE line detected interrupt.
  *         @arg USART_IT_ORE:  OverRun Error interrupt.
  *         @arg USART_IT_NE:  Noise Error interrupt.
  *         @arg USART_IT_FE:  Framing Error interrupt.
  *         @arg USART_IT_PE:  Parity Error interrupt.
  * @note
  *   - RXNE pending bit is cleared by a read to the USART_RDR register 
  *     (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register USART_RQR
  *     (USART_RequestCmd()).
  *   - TC pending bit can be also cleared by software sequence: a read 
  *     operation to USART_SR register (USART_GetITStatus()) followed by a write 
  *     operation to USART_TDR register (USART_SendData()).
  *   - TXE pending bit is cleared by a write to the USART_TDR register 
  *     (USART_SendData()) or by writing 1 to the TXFRQ in the register USART_RQR
  *     (USART_RequestCmd()).
*
* @retval 无
*/
void drv_uart_clear_it_pending_bit( UsartType *pUart, UINT32 UartItFlag )
{
	UINT16 bitpos = 0x00, itmask = 0x00;

	bitpos = UartItFlag >> 0x10;
	itmask = ((UINT32)0x01 << (UINT32)bitpos );
	pUart->ICR.all = (UINT32)itmask;
}

/**
* @brief 获取错误状态
* @param  pUart: UART1~UART6
* @retval 错误状态
*/
UINT8 drv_uart_get_error_status(UsartType *pUart)
{
	return ((pUart->ISR.all) & 0x0F);
}

/**
* @brief  串口堵塞方式接收一个字节数据
* @param  pUart: UART1~UART6
* @retval 收到的字符
*/
UINT8 drv_uart_get_byte_blocking(UsartType *pUart)
{
	while ( pUart->ISR.bit.RXNE == RESET );

	return (UINT8)(pUart->RDR.all & 0xFF);
}

/**
* @brief  串口非堵塞方式接收一个字节
* @param  pUart: 串口 UART1~UART6
* @param  *pDat: 接收到的字节数据
* @retval 0：成功，否则返回1
*/
UINT8 drv_uart_get_byte_noblocking( UsartType *pUart, UINT8 *pDat )
{
	if ( pUart->ISR.bit.RXNE == RESET )
	{
		return 1;
	}
	else
	{
		*pDat = (UINT8)( pUart->RDR.all & 0xFF );

		return 0;
	}
}

/**
* @brief  串口发送多个字节
* @param  pUart: 串口 UART1~UART6
* @param  *pDat: 要发送的数据首地址
* @param  Length: 要发送的字节数
* @retval 无
*/
void drv_uart_put_bytes(UsartType *pUart, UINT8 *pDat, UINT32 Length)
{
	UINT32 i;
	for ( i = 0; i < Length; i++ )
	{
		while ( pUart->ISR.bit.TXE == RESET );

		pUart->TDR.all = pDat[i];
	}
}

/**
 * @brief  发送一个字符串，遇0结束
 * @param  pUart: 串口 UART1~UART6
 * @param  *pString: 字符串首地址
 * @retval 无
 */
void drv_uart_put_string(UsartType *pUart, const char *pString)
{
	while ( *pString )
	{
		while ( pUart->ISR.bit.TXE == RESET );
		pUart->TDR.all = *pString++;
	}
}
