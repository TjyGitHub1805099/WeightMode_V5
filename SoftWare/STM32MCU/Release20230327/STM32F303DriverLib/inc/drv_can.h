/**
*******************************************************************
* @file    drv_can.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x CAN模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#include "reg_stm32f303_can.h"
#include "drv_rcc.h"

//常用位定义
#define CAN_FLAGS_TSR     				((UINT32)0x08000000) 		/* Flags in TSR register */
#define CAN_FLAGS_RF1R    				((UINT32)0x04000000) 		/* Flags in RF1R register */
#define CAN_FLAGS_RF0R    				((UINT32)0x02000000) 		/* Flags in RF0R register */
#define CAN_FLAGS_MSR     				((UINT32)0x01000000) 		/* Flags in MSR register */
#define CAN_FLAGS_ESR     				((UINT32)0x00F00000) 		/* Flags in ESR register */

#define CAN_RIR_REG_IDE					((UINT32)0x00000004)
#define CAN_RIR_REG_RTR					((UINT32)0x00000002)
#define CAN_RIR_REG_STD					((UINT32)0xFFE00000)
#define CAN_RIR_REG_EXD					((UINT32)0xFFFFFFF8)
#define CAN_RDTR_REG_DLC				((UINT32)0x0000000F)
#define CAN_RDTR_REG_FMI				((UINT32)0x0000FF00)
#define CAN_RFR_REG_FMP					((UINT32)0x00000003)

//中断定义
#define CAN_IT_TME                  	((UINT32)0x00000001) /*!< Transmit mailbox empty Interrupt*/
/* Receive Interrupts */
#define CAN_IT_FMP0                 	((UINT32)0x00000002) /*!< FIFO 0 message pending Interrupt*/
#define CAN_IT_FF0                  	((UINT32)0x00000004) /*!< FIFO 0 full Interrupt*/
#define CAN_IT_FOV0                 	((UINT32)0x00000008) /*!< FIFO 0 overrun Interrupt*/
#define CAN_IT_FMP1                 	((UINT32)0x00000010) /*!< FIFO 1 message pending Interrupt*/
#define CAN_IT_FF1                  	((UINT32)0x00000020) /*!< FIFO 1 full Interrupt*/
#define CAN_IT_FOV1                 	((UINT32)0x00000040) /*!< FIFO 1 overrun Interrupt*/
/* Operating Mode Interrupts */
#define CAN_IT_WKU                  	((UINT32)0x00010000) /*!< Wake-up Interrupt*/
#define CAN_IT_SLK                  	((UINT32)0x00020000) /*!< Sleep acknowledge Interrupt*/
/* Error Interrupts */
#define CAN_IT_EWG                  	((UINT32)0x00000100) /*!< Error warning Interrupt*/
#define CAN_IT_EPV                  	((UINT32)0x00000200) /*!< Error passive Interrupt*/
#define CAN_IT_BOF                  	((UINT32)0x00000400) /*!< Bus-off Interrupt*/
#define CAN_IT_LEC                  	((UINT32)0x00000800) /*!< Last error code Interrupt*/
#define CAN_IT_ERR                  	((UINT32)0x00008000) /*!< Error Interrupt*/
/* Flags named as Interrupts : kept only for FW compatibility */
#define CAN_IT_RQCP0   					CAN_IT_TME
#define CAN_IT_RQCP1   					CAN_IT_TME
#define CAN_IT_RQCP2   					CAN_IT_TME

//标志定义
/* Transmit Flags */
#define CAN_FLAG_RQCP0             		((UINT32)0x38000001) /*!< Request MailBox0 Flag */
#define CAN_FLAG_RQCP1             		((UINT32)0x38000100) /*!< Request MailBox1 Flag */
#define CAN_FLAG_RQCP2             		((UINT32)0x38010000) /*!< Request MailBox2 Flag */
/* Receive Flags */
#define CAN_FLAG_FMP0              		((UINT32)0x12000003) /*!< FIFO 0 Message Pending Flag */
#define CAN_FLAG_FF0               		((UINT32)0x32000008) /*!< FIFO 0 Full Flag            */
#define CAN_FLAG_FOV0              		((UINT32)0x32000010) /*!< FIFO 0 Overrun Flag         */
#define CAN_FLAG_FMP1              		((UINT32)0x14000003) /*!< FIFO 1 Message Pending Flag */
#define CAN_FLAG_FF1               		((UINT32)0x34000008) /*!< FIFO 1 Full Flag            */
#define CAN_FLAG_FOV1              		((UINT32)0x34000010) /*!< FIFO 1 Overrun Flag         */
/* Operating Mode Flags */
#define CAN_FLAG_WKU               		((UINT32)0x31000008) /*!< Wake up Flag */
#define CAN_FLAG_SLAK              		((UINT32)0x31000012) /*!< Sleep acknowledge Flag */
/* @note When SLAK interrupt is disabled (SLKIE=0), no polling on SLAKI is possible. 
         In this case the SLAK bit can be polled.*/
/* Error Flags */
#define CAN_FLAG_EWG               		((UINT32)0x10F00001) /*!< Error Warning Flag   */
#define CAN_FLAG_EPV               		((UINT32)0x10F00002) /*!< Error Passive Flag   */
#define CAN_FLAG_BOF               		((UINT32)0x10F00004) /*!< Bus-Off Flag         */
#define CAN_FLAG_LEC               		((UINT32)0x30F00070) /*!< Last error code Flag */


/** 标准帧扩展帧定义 */
typedef enum CanIdStdAndExtType
{
	CAN_ID_STANDARD = 0,		/**< 标准帧 */
	CAN_ID_EXTENDED				/**< 扩展帧 */
}enumCanIdStdAndExtType;

/** 过滤器FIFO分配定义 */
typedef enum CanRxFifoType
{
	CAN_RX_FIFO0 = 0,			/**< 过滤器选择FIFO0 */
	CAN_RX_FIFO1				/**< 过滤器选择FIFO1 */
}enumCanRxFifoType;

typedef struct CanMsgType
{
	UINT32 Id;	 /*!< Can ID. */
	UINT8 IDE;	 /*!< ID类型 */
	UINT8 RTR;	 /*!< 帧类型 */
	UINT8 DLC;	 /*!< 数据长度 */
	UINT8 Data[8];	/*!< 数据区. */
	UINT8 FMI;	 /*!< 接收邮箱滤波器索引 */
}structCanMsgType;



extern void drv_can_deinit( void );
extern UINT8 drv_can_set_baudrate( CanType *pCan, UINT8 Sjw, UINT8 Bs1, UINT8 Bs2, UINT16 Presc );
extern UINT8 drv_can_init( CanType *pCan, UINT8 Sjw, UINT8 Bs1, UINT8 Bs2, UINT16 Presc );
extern void drv_can_master_set_rx_id( CanType *pCan );
extern void drv_can_slaver_set_rx_std_id( CanType *pCan, UINT32 *pId, UINT32 *pFilterId, UINT8 IdNumber );
extern void drv_can_slaver_set_rx_exp_id( CanType *pCan, UINT32 *pId, UINT32 *pFilterId, UINT8 IdNumber );
extern UINT8 drv_can_tx( CanType *pCan, UINT32 Id, enumCanIdStdAndExtType IDE, UINT8 RTR, UINT8 DLC, UINT8 *pData );
extern UINT8 drv_can_rx( CanType *pCan, enumCanRxFifoType Fifo, structCanMsgType *pRxMsg );
extern void drv_can_fifo_release( CanType *pCan, enumCanRxFifoType Fifo );
extern UINT8 drv_can_fifo_check( CanType *pCan, enumCanRxFifoType Fifo );
extern UINT32 drv_can_get_error_status( CanType *pCan );
extern void drv_can_it_enable( CanType *pCan, UINT32  CanIt );
extern void drv_can_it_disable( CanType *pCan, UINT32  CanIt );
extern FlagStatus drv_can_get_flag_status( CanType *pCan, UINT32  CanFlag );
extern void drv_can_clear_flag_status( CanType *pCan, UINT32 CanFlag );
extern ITStatus drv_can_get_it_status( CanType *pCan, UINT32 CanIt );
extern void drv_can_clear_it_pending_bit( CanType *pCan, UINT32 CanIt );


#endif
