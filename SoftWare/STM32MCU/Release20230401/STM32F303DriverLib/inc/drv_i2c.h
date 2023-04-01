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
#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__


#include "drv_rcc.h"
#include "reg_stm32f303_i2c.h"

#define AT24C02_Clk64Mhz_100us 			1600					//while(X--)形式100us延时
#define ERROR_IT_MASK					((UINT32)0x00003F00)  /*<! I2C Error interrupt register Mask */
#define TC_IT_MASK						((UINT32)0x000000C0)  /*<! I2C TC interrupt register Mask */


/* I2C中断 */
#define I2C_IT_ERRI                     ((UINT32)0x00000080)
#define I2C_IT_TCI                      ((UINT32)0x00000040)
#define I2C_IT_STOPI                    ((UINT32)0x00000020)
#define I2C_IT_NACKI                    ((UINT32)0x00000010)
#define I2C_IT_ADDRI                    ((UINT32)0x00000008) 
#define I2C_IT_RXI                      ((UINT32)0x00000004)
#define I2C_IT_TXI                      ((UINT32)0x00000002)
/* I2C中断状态 */
#define I2C_IT_TXIS                    	((UINT32)0x00000002) 
#define I2C_IT_RXNE                    	((UINT32)0x00000004) 
#define I2C_IT_ADDR                     ((UINT32)0x00000008)
#define I2C_IT_NACKF                    ((UINT32)0x00000010)
#define I2C_IT_STOPF                    ((UINT32)0x00000020)
#define I2C_IT_TC                       ((UINT32)0x00000040)
#define I2C_IT_TCR                      ((UINT32)0x00000080)
#define I2C_IT_BERR                     ((UINT32)0x00000100)
#define I2C_IT_ARLO                     ((UINT32)0x00000200) 
#define I2C_IT_OVR                      ((UINT32)0x00000400)
#define I2C_IT_PECERR                   ((UINT32)0x00000800)
#define I2C_IT_TIMEOUT                  ((UINT32)0x00001000)
#define I2C_IT_ALERT                    ((UINT32)0x00002000)
/* I2C标志 */
#define  I2C_FLAG_TXE                   ((UINT32)0x00000001)
#define  I2C_FLAG_TXIS                  ((UINT32)0x00000002)
#define  I2C_FLAG_RXNE                  ((UINT32)0x00000004)
#define  I2C_FLAG_ADDR                  ((UINT32)0x00000008)
#define  I2C_FLAG_NACKF                 ((UINT32)0x00000010)
#define  I2C_FLAG_STOPF                 ((UINT32)0x00000020)
#define  I2C_FLAG_TC                    ((UINT32)0x00000040)
#define  I2C_FLAG_TCR                   ((UINT32)0x00000080)
#define  I2C_FLAG_BERR                  ((UINT32)0x00000100)
#define  I2C_FLAG_ARLO                  ((UINT32)0x00000200)
#define  I2C_FLAG_OVR                   ((UINT32)0x00000400)
#define  I2C_FLAG_PECERR                ((UINT32)0x00000800)
#define  I2C_FLAG_TIMEOUT               ((UINT32)0x00001000)
#define  I2C_FLAG_ALERT                 ((UINT32)0x00002000)
#define  I2C_FLAG_BUSY                  ((UINT32)0x00008000)

/* I2C事件 */
#define I2C_EVENT_BUSY					I2C_FLAG_BUSY
#define I2C_EVENT_ADDR					I2C_FLAG_ADDR
#define I2C_EVENT_TC					I2C_FLAG_TC
#define I2C_EVENT_RXNE					I2C_FLAG_RXNE
#define I2C_EVENT_TXE					I2C_FLAG_TXE


/** I2C模式定义 */
typedef enum I2cModeType						
{
	I2C_MODE_I2C = 0,					/**< I2C模式 */
	I2C_MODE_SMBUSDEVICE				/**< SMBU模式 */
}enumI2cModeType;

/** I2C应答机制定义 */
typedef enum I2cAckModeType						
{
	I2C_ACK_MODE_ENABLE = 0,			/**< 使能应答 */
	I2C_ACK_MODE_DISABLE				/**< 禁止应答 */
}enumI2cAckModeType;

/** I2C地址模式定义 */
typedef enum I2cAddrModeType					
{
	I2C_ADDRESS_MODE_7 = 0,				/**< 7位地址模式 */
	I2C_ADDRESS_MODE_10					/**< 10位地址模式 */
}enumI2cAddrModeType;

/** I2C通信模式定义 */
typedef enum I2cComModeType						
{
	I2C_STANDARD_MODE = 0,				/**< 标准模式 */
	I2C_FAST_MODE ,						/**< 快速模式 */
}enumI2cComModeType;

/** 数据方向定义 */
typedef enum I2cDirectionType
{
	I2C_Direction_Transmitter = 0,		/**< 发送器 */
	I2C_Direction_Receiver,				/**< 接收器 */
}enumI2cDirType;



extern void drv_i2c_deinit( I2cType *pI2C );
extern void drv_i2c_init( I2cType *pI2C, UINT32 BusFrequency );
extern void drv_i2c_enable( I2cType *pI2C );
extern void drv_i2c_disable( I2cType *pI2C );
extern void drv_i2c_send_start( I2cType *pI2C );
extern void drv_i2c_send_stop( I2cType *pI2C );
extern void drv_i2c_send_7bit_address( I2cType *pI2C, UINT8 Address, enumI2cDirType Dir );
extern void drv_i2c_ack_enable( I2cType *pI2C );
extern void drv_i2c_ack_disable( I2cType *pI2C );
extern void drv_i2c_set_own_address( I2cType *pI2C, UINT8 Address );
extern void drv_i2c_put_byte( I2cType *pI2C, UINT8 Data );
extern UINT8 drv_i2c_get_byte( I2cType *pI2C );
extern void drv_i2c_tx_dma_enable( I2cType *pI2C );
extern void drv_i2c_tx_dma_disable( I2cType *pI2C );
extern void drv_i2c_rx_dma_enable( I2cType *pI2C );
extern void drv_i2c_rx_dma_disable( I2cType *pI2C );
extern void drv_i2c_it_enable( I2cType *pI2C, UINT32 I2cIt );
extern void drv_i2c_it_disable( I2cType *pI2C, UINT32 I2cIt );
extern UINT32 drv_i2c_get_last_event( I2cType *pI2C );
extern FlagStatus drv_i2c_get_flag_status( I2cType *pI2C, UINT32 I2cFlag );
extern ErrorStatus drv_i2c_check_event( I2cType *pI2C , UINT32 I2cEvent );
extern void drv_i2c_clear_flag_status( I2cType *pI2C, UINT32 I2cFlag );
extern ITStatus drv_i2c_get_it_status( I2cType *pI2C, UINT32 I2cIt );
extern void drv_i2c_clear_it_pending_bit( I2cType *pI2C, UINT32 I2cIt );




#endif
