/**
*******************************************************************
* @file    drv_i2c.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x I2C模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#include "drv_i2c.h"


/**
* @brief  恢复I2C寄存器为复位默认值.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C2.
* @retval 无
*/
void drv_i2c_deinit( I2cType *pI2C )
{
	if( pI2C == I2C1 )
	{
		drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_I2C1RST );
		drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_I2C1RST );
	}
	else 
	{
		if( pI2C == I2C2 )
		{
			drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_I2C1RST );
			drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_I2C1RST );
		}
	}
}

/**
* @brief  初始化I2C外设.
*
* @note   要想达到 400 KHz，APB1时钟必须是10MHz的整数倍
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  BusFrequency:总线通信频率，单位Hz.
* @retval 无
*/
void drv_i2c_init( I2cType *pI2C, UINT32 BusFrequency )
{
	UINT16 l_TempPsc = 0;
	UINT32 l_Pclk = 0;
	
	pI2C->CR1.bit.PE		= 0;		//禁止I2C
	//滤波器设置
	pI2C->CR1.bit.ANFOFF	= 1;		//使能模拟滤波器
	pI2C->CR1.bit.DNF		= 0;		//不使能数字滤波器
	//时钟设置
	l_Pclk = g_ClockFrequency.Apb1Freq;
	l_TempPsc = (UINT16)( l_Pclk / BusFrequency << 1 );		//计算分频系数
	pI2C->TIMINGR.bit.PRESC	= l_TempPsc - 1;
	pI2C->TIMINGR.bit.SCLL	= 1;		//低电平周期
	pI2C->TIMINGR.bit.SCLH	= 1;
	pI2C->TIMINGR.bit.SCLDEL = 0;
	pI2C->TIMINGR.bit.SDADEL = 0;
	pI2C->CR1.bit.PE		= 1;		//时钟设置完成使能I2C外设
	//自身地址寄存器1设置
	pI2C->OAR1.bit.OA1MODE	= 0;		//7位地址模式
	pI2C->OAR1.bit.OA1		= 0;		//默认地址为0
	pI2C->OAR1.bit.OA1EN	= 1;		//使能OA1,从接收OA1应答被使能
	//设置为I2C模式
	pI2C->CR1.bit.SMBDEN	= 0;
	pI2C->CR1.bit.SMBHEN	= 0;
	//使能ACK
	pI2C->CR2.bit.NACK		= 0;		//即禁止NACK
	
}

/**
* @brief  使能I2C外设.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C2.
* @retval 无
*/
void drv_i2c_enable( I2cType *pI2C )
{
	pI2C->CR1.bit.PE = 1;
}

/**
* @brief  禁止I2C外设.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C2.
* @retval 无
*/
void drv_i2c_disable( I2cType *pI2C )
{ 
	pI2C->CR1.bit.PE = 0;
}


/**
* @brief  发送开始条件.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @retval 无
*/
void drv_i2c_send_start( I2cType *pI2C )
{
	pI2C->CR2.bit.START = 1;
}

/**
* @brief  发送停止条件.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @retval 无
*/
void drv_i2c_send_stop( I2cType *pI2C )
{
	pI2C->CR2.bit.STOP = 1;
}

/**
* @brief  发送从机设备7位地址码.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  Address: 从机设备7位地址码
* @param  Dir: 指定设备是发送方还是接收方，可以是下面值的一种.
*            @arg I2C_Direction_Transmitter: 发送模式
*            @arg I2C_Direction_Receiver: 接收模式
* @retval 无
*/
void drv_i2c_send_7bit_address( I2cType *pI2C, UINT8 Address, enumI2cDirType Dir )
{
	Address = Address << 1;
	if( Dir != I2C_Direction_Transmitter )
	{
		Address |= 0x01;
	}
	else
	{
		Address &= 0xFE;
	}
	pI2C->TXDR.all = Address;
}

/**
* @brief  使能应答功能.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @retval 无
*/
void drv_i2c_ack_enable( I2cType *pI2C )
{
	pI2C->CR2.bit.NACK = 0;
}

/**
* @brief  禁止应答功能.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @retval 无
*/
void drv_i2c_ack_disable( I2cType *pI2C )
{
	pI2C->CR2.bit.NACK = 1;
}

/**
* @brief  设置本机地址.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  Address: 7位本机地址.
* @retval 无
*/
void drv_i2c_set_own_address( I2cType *pI2C, UINT8 Address )
{
	Address = Address << 1;
	pI2C->OAR1.bit.OA1 = Address;
}

/**
* @brief  发送一个字节.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  Data: 要发送的字节.
* @retval 无
*/
void drv_i2c_put_byte( I2cType *pI2C, UINT8 Data )
{
	pI2C->TXDR.all = Data;
}

/**
* @brief  接收一个字节.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @retval 接收到的字节.
*/
UINT8 drv_i2c_get_byte( I2cType *pI2C )
{
	I2cRxdrType l_Rxdr;
	
	l_Rxdr.all = pI2C->RXDR.all;
	return ( (UINT8)( l_Rxdr.all ) );
}

/**
* @brief  使能I2C TX DMA请求.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @retval 无
*/
void drv_i2c_tx_dma_enable( I2cType *pI2C )
{
	pI2C->CR1.bit.TXDMAEN = 1;
}

/**
* @brief  禁止I2C TX DMA请求.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @retval 无
*/
void drv_i2c_tx_dma_disable( I2cType *pI2C )
{
	pI2C->CR1.bit.TXDMAEN = 0;
}

/**
* @brief  使能I2C RX DMA请求.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @retval 无
*/
void drv_i2c_rx_dma_enable( I2cType *pI2C )
{
	pI2C->CR1.bit.RXDMAEN = 1;
}

/**
* @brief  禁止I2C RX DMA请求.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C2.
* @retval 无
*/
void drv_i2c_rx_dma_disable( I2cType *pI2C )
{
	pI2C->CR1.bit.RXDMAEN = 0;
}

/**
* @brief  使能IT中断.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C2.
* @param  I2cIt: 要使能的中断源，可以是下面值的组合：
*            @arg I2C_IT_ERRI
*            @arg I2C_IT_TCI
*            @arg I2C_IT_STOPI
*            @arg I2C_IT_NACKI
*            @arg I2C_IT_ADDRI
*            @arg I2C_IT_RXI
*            @arg I2C_IT_TXI
* @retval 无
*/
void drv_i2c_it_enable( I2cType *pI2C, UINT32 I2cIt )
{
	pI2C->CR1.all |= I2cIt;
}

/**
* @brief  禁止IT中断.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  I2cIt: 要禁止的中断源，可以是下面值的组合：
*            @arg I2C_IT_ERRI
*            @arg I2C_IT_TCI
*            @arg I2C_IT_STOPI
*            @arg I2C_IT_NACKI
*            @arg I2C_IT_ADDRI
*            @arg I2C_IT_RXI
*            @arg I2C_IT_TXI
* @retval 无
*/
void drv_i2c_it_disable( I2cType *pI2C, UINT32 I2cIt )
{
	pI2C->CR1.all &= (UINT32)~I2cIt;
}

/**
* @brief  获取最后一个事件.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C2.
*
* @note  
*
* @retval The last event
*/
UINT32 drv_i2c_get_last_event( I2cType *pI2C )
{
	I2cIsrType	l_Isr;
	
	l_Isr.all = pI2C->ISR.all;
	
	return ( l_Isr.all );
}

/**
* @brief  检查状态标志是否被设置.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  I2cFlag: 要检查的标志，可以是下面值的一个:
  *     @arg I2C_FLAG_TXE: Transmit data register empty
  *     @arg I2C_FLAG_TXIS: Transmit interrupt status
  *     @arg I2C_FLAG_RXNE: Receive data register not empty
  *     @arg I2C_FLAG_ADDR: Address matched (slave mode)
  *     @arg I2C_FLAG_NACKF: NACK received flag
  *     @arg I2C_FLAG_STOPF: STOP detection flag
  *     @arg I2C_FLAG_TC: Transfer complete (master mode)
  *     @arg I2C_FLAG_TCR: Transfer complete reload
  *     @arg I2C_FLAG_BERR: Bus error
  *     @arg I2C_FLAG_ARLO: Arbitration lost
  *     @arg I2C_FLAG_OVR: Overrun/Underrun
  *     @arg I2C_FLAG_PECERR: PEC error in reception
  *     @arg I2C_FLAG_TIMEOUT: Timeout or Tlow detection flag
  *     @arg I2C_FLAG_ALERT: SMBus Alert
  *     @arg I2C_FLAG_BUSY: Bus busy
* @retval 状态值.
*/
FlagStatus drv_i2c_get_flag_status( I2cType *pI2C, UINT32 I2cFlag )
{
	I2cIsrType	l_Isr;
	
	l_Isr.all = pI2C->ISR.all;
	if(( l_Isr.all & I2cFlag ) != (UINT32)RESET )
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}

/**
* @brief  检查状态标志是否被设置.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  I2cFlag: 要检查的标志，可以是下面值的一个:
  *     @arg I2C_EVENT_BUSY
  *     @arg I2C_EVENT_ADDR
  *     @arg I2C_EVENT_TC
  *     @arg I2C_EVENT_RXNE
  *     @arg I2C_EVENT_TXE
* @retval 状态值.
*/
ErrorStatus drv_i2c_check_event( I2cType *pI2C , UINT32 I2cEvent )
{
	UINT32 l_I2cTimeOut = AT24C02_Clk64Mhz_100us;
	
	while( --l_I2cTimeOut )
	{
		if( drv_i2c_get_flag_status( pI2C, I2cEvent ) != RESET )
		{
			break;
		}
	}
	if( l_I2cTimeOut != 0 )
	{
		return SUCCESS;
	}
	else
	{
		return ERROR;
	}
}

/**
* @brief  清状态标志.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  I2cFlag: 清除状态标志，可以是下面值的组合:
  *     @arg I2C_FLAG_ADDR: Address matched (slave mode)
  *     @arg I2C_FLAG_NACKF: NACK received flag
  *     @arg I2C_FLAG_STOPF: STOP detection flag
  *     @arg I2C_FLAG_BERR: Bus error
  *     @arg I2C_FLAG_ARLO: Arbitration lost
  *     @arg I2C_FLAG_OVR: Overrun/Underrun
  *     @arg I2C_FLAG_PECERR: PEC error in reception
  *     @arg I2C_FLAG_TIMEOUT: Timeout or Tlow detection flag
  *     @arg I2C_FLAG_ALERT: SMBus Alert
* @retval 无
*/
void drv_i2c_clear_flag_status( I2cType *pI2C, UINT32 I2cFlag )
{
	pI2C->ICR.all = I2cFlag;		
}

/**
* @brief  检查中断状态.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  I2cIt: 要检查的中断状态，可以是下面值的一个:
  *     @arg I2C_IT_TXIS: Transmit interrupt status
  *     @arg I2C_IT_RXNE: Receive data register not empty
  *     @arg I2C_IT_ADDR: Address matched (slave mode)
  *     @arg I2C_IT_NACKF: NACK received flag
  *     @arg I2C_IT_STOPF: STOP detection flag
  *     @arg I2C_IT_TC: Transfer complete (master mode)
  *     @arg I2C_IT_TCR: Transfer complete reload
  *     @arg I2C_IT_BERR: Bus error
  *     @arg I2C_IT_ARLO: Arbitration lost
  *     @arg I2C_IT_OVR: Overrun/Underrun
  *     @arg I2C_IT_PECERR: PEC error in reception
  *     @arg I2C_IT_TIMEOUT: Timeout or Tlo
* @retval 读取状态值.
*/
ITStatus drv_i2c_get_it_status( I2cType *pI2C, UINT32 I2cIt )
{
	I2cCr1Type l_Cr;
	I2cIsrType l_Sr;
	
	UINT32 l_ItTemp = 0, l_FlagTemp = 0;
	
	l_Cr.all = pI2C->CR1.all;
	l_Sr.all = pI2C->ISR.all;
	//错误中断
	if((UINT32)( I2cIt & ERROR_IT_MASK ))
	{
		l_ItTemp = (UINT32)(( I2C_IT_ERRI ) & l_Cr.all );
	}
	//发送完成中断
	else if((UINT32)( I2cIt & TC_IT_MASK ))
	{
		l_ItTemp = (UINT32)(( I2C_IT_TCI ) & l_Cr.all );
	}
	else
	{
		l_ItTemp = (UINT32)( I2cIt & l_Cr.all );
	}
	
	l_FlagTemp = l_Sr.all & l_Sr.all;
	
	if(( l_ItTemp != (UINT32)RESET ) && ( l_FlagTemp != (UINT32)RESET ))
	{
		return SET;
	}
	else
	{
		return  RESET;
	}
}

/**
* @brief  清中断挂起标志位.
* @param  pI2C: 要操作的I2C模块，可以是 I2C1 ~ I2C3.
* @param  I2cIt: 要清除的中断挂起标志位，可以是下面值的组合:
  *     @arg I2C_IT_ADDR: Address matched (slave mode)
  *     @arg I2C_IT_NACKF: NACK received flag
  *     @arg I2C_IT_STOPF: STOP detection flag
  *     @arg I2C_IT_BERR: Bus error
  *     @arg I2C_IT_ARLO: Arbitration lost
  *     @arg I2C_IT_OVR: Overrun/Underrun
  *     @arg I2C_IT_PECERR: PEC error in reception
  *     @arg I2C_IT_TIMEOUT: Timeout or Tlow detection flag
  *     @arg I2C_IT_ALERT: SMBus Alert
* @retval 无
*/
void drv_i2c_clear_it_pending_bit( I2cType *pI2C, UINT32 I2cIt )
{
	pI2C->ICR.all = I2cIt;		
}
