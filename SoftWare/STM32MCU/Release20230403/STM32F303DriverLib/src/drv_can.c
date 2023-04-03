/**
*******************************************************************
* @file    drv_can.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x CAN模块驱动程序
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#include "drv_can.h"

const UINT32 g_TimeOut = 0x000FFFFF;

/**
* @brief  复位CAN外设寄存器为默认值.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @retval 无.
*/
void drv_can_deinit( void )
{
	drv_rcc_apb1_periph_reset_enable( RCC_APB1RSTR_CAN1RST );
	drv_rcc_apb1_periph_reset_disable( RCC_APB1RSTR_CAN1RST );
}

/**
* @brief  设置CAN外设波特率.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  Baudrate: 要设置的波特率值.
* @retval 无.
*/
UINT8 drv_can_set_baudrate( CanType *pCan, UINT8 Sjw, UINT8 Bs1, UINT8 Bs2, UINT16 Presc )
{
	UINT32 g_CanInrqFlag = 0, g_CanSleepFlag = 0, l_TimeOut = 0;
	
	pCan->MCR.bit.SLEEP = 0;						// 退出睡眠模式 
	pCan->MCR.bit.INRQ  = 1;						// 请求进入初始化模式 
	do
	{
		g_CanInrqFlag  = (UINT32)pCan->MSR.all;		// 读初始化模式标志 
		g_CanSleepFlag = (UINT32)pCan->MSR.all;		// 读睡眠模式标志 
		g_CanInrqFlag &= 0x00000001;
		g_CanSleepFlag &= 0x00000002;
	}while((( g_CanInrqFlag == 0 ) || ( g_CanSleepFlag == 1 )) && ( ++l_TimeOut < g_TimeOut ));

	if( l_TimeOut >= g_TimeOut )
	{
		return 1;									// 初始化模式切换失败 			
	}
	else											
	{	// 初始化模式切换完成  清楚状态判断标志
		l_TimeOut = 0;
		g_CanSleepFlag = 0;
		g_CanInrqFlag = 0;
		
		pCan->BTR.bit.SILM = 0;						// 正常模式 
		pCan->BTR.bit.LBKM = 0;						// 禁止环回模式 
		
		pCan->BTR.bit.SJW  = Sjw;					// 再同步跳转宽度 
		pCan->BTR.bit.TS1  = Bs1;					// 时间段1 
		pCan->BTR.bit.TS2  = Bs2;					// 时间段2 
		pCan->BTR.bit.BRP  = Presc - 1;				// 分频系数 
		pCan->MCR.bit.INRQ = 0;						// 请求退出初始化模式 
		do
		{
			g_CanInrqFlag  = (UINT32)pCan->MSR.all;		// 读初始化模式标志 
			g_CanSleepFlag = (UINT32)pCan->MSR.all;		// 读睡眠模式标志 
			g_CanInrqFlag &= 0x00000001;
			g_CanSleepFlag &= 0x00000002;
		}while(( g_CanInrqFlag == 1 || g_CanSleepFlag == 1 ) && ( ++l_TimeOut < g_TimeOut ));
		if( l_TimeOut >= g_TimeOut )
		{
			return 2;								// 退出初始化进入正常模式失败 
		}	
	}
	
	return 0;
}

/**
* @brief  设置CAN外设接收ID.
* @note   要配置成调试期间处于工作状态.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  Baudrate: 要设置的波特率值.
* @retval 无.
*/
UINT8 drv_can_init( CanType *pCan, UINT8 Sjw, UINT8 Bs1, UINT8 Bs2, UINT16 Presc )
{
	UINT32 g_CanInrqFlag = 0, g_CanSleepFlag = 0, l_TimeOut = 0;
	
	pCan->MCR.bit.SLEEP = 0;						// 退出睡眠模式 
	pCan->MCR.bit.INRQ  = 1;						// 请求进入初始化模式 
	
	do
	{
		g_CanInrqFlag  = (UINT32)pCan->MSR.all;		// 读初始化模式标志 
		g_CanSleepFlag = (UINT32)pCan->MSR.all;		// 读睡眠模式标志 
		g_CanInrqFlag &= 0x00000001;
		g_CanSleepFlag &= 0x00000002;
	}while((( g_CanInrqFlag == 0 ) || ( g_CanSleepFlag == 1 )) && ( ++l_TimeOut < g_TimeOut ));
	if( l_TimeOut >= g_TimeOut )
	{
		return 1;									// 初始化模式切换失败 			
	}
	else											
	{
		// 初始化模式切换完成  清楚状态判断标志
		l_TimeOut = 0;
		g_CanSleepFlag = 0;
		g_CanInrqFlag = 0;
		
		// CAN控制寄存器设置 
		pCan->MCR.bit.ABOM = 0;						// 禁止自动总线关闭 
		pCan->MCR.bit.AWUM = 0;						// 禁止自动唤醒 
		pCan->MCR.bit.NART = 0;						// 自动重发，直到发送成功 
		pCan->MCR.bit.RFLM = 0;						// FIFO满后，后一条消息覆盖前一条消息，FIFO不锁定 
		pCan->MCR.bit.TTCM = 0;						// 禁止事件触发通信 
		pCan->MCR.bit.TXFP = 0;						// FIFO优先级由标识符确定 
		
		// 模式设置 
		pCan->BTR.bit.SILM = 0;						// 正常模式 
		pCan->BTR.bit.LBKM = 0;						// 禁止环回模式 

		// 设置波特率 
		pCan->BTR.bit.SJW  = Sjw;					// 再同步跳转宽度 
		pCan->BTR.bit.TS1  = Bs1;					// 时间段1 
		pCan->BTR.bit.TS2  = Bs2;					// 时间段2 
		pCan->BTR.bit.BRP  = Presc - 1;				// 分频系数  
		pCan->MCR.bit.SLEEP = 0;
		pCan->MCR.bit.INRQ  = 0;					// 请求退出初始化模式 
		do
		{
			g_CanInrqFlag  = (UINT32)pCan->MSR.all;		// 读初始化模式标志 
			g_CanSleepFlag = (UINT32)pCan->MSR.all;		// 读睡眠模式标志 
			g_CanInrqFlag &= 0x00000001;
			g_CanSleepFlag &= 0x00000002;
		}while(( g_CanInrqFlag == 1 || g_CanSleepFlag == 1 ) && ( ++l_TimeOut < g_TimeOut ));
		if( l_TimeOut >= g_TimeOut )
		{
			return 2;								// 退出初始化进入正常模式失败 
		}		
	}
	
	return 0;
}

/**
* @brief  设置主机CAN外设接收ID.
* @attention 主机使用过滤器1，默认配置为32位位宽，屏蔽位模式，主机默认接收全部报文，FIFO0
* @retval 无.
*/
void drv_can_master_set_rx_id( CanType *pCan )
{
	CAN1->FMR.bit.FINIT	= 1;							// 过滤器进入初始化
	CAN1->FA1R.all &= ( UINT32 )( ~0x00000001 );		// 禁止相应过滤器使能位 
	CAN1->FM1R.all &= ( UINT32 )( ~0x00000001 );		// 主机采用屏蔽位模式  
	CAN1->FS1R.all |= ( UINT32 )0x00000001 ;			// 设置位宽模式
	CAN1->Filter[ 0 ].FR1.all = 0;						//ID
	CAN1->Filter[ 0 ].FR2.all = 0;						//IDMASK
	CAN1->FFA1R.all &= ( UINT32 )( ~0x00000001 );		// 选择FIFO0 
	CAN1->FA1R.all |= ( UINT32 )0x00000001;				// 激活过滤器  
	CAN1->FMR.bit.FINIT = 0;							// 过滤器退出初始化模式
}

/**
* @brief  设置从机CAN外设接收标准ID.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  pId: 要设置的ID.
* @param  pFilterId: 要设置的验收滤波ID.
* @param  IdNumber: 要设置的ID数量.
* @attention 过滤器默认从第1个过滤器开始，配置为32位位宽，标识符位模式，FIFO0
* @retval 无.
*/
void drv_can_slaver_set_rx_std_id( CanType *pCan, UINT32 *pId, UINT32 *pFilterId, UINT8 IdNumber )
{
	UINT32 l_FilterNumberRegPosition = 0;
	UINT8  l_FirstFilterNumber = 0;
		
	CAN1->FMR.bit.FINIT	= 1;				// 过滤器进入初始化
	while( IdNumber-- )
	{
		//CAN模块过滤器在过滤过程中，实际STD_ID的比对是从FRx寄存器BIT21开始，BIT0保留，BIT1为RTR=0，BIT2为IDE=0，其他位保留。
		//在标准数据帧中，IED=0,RTR=0,能够满足过滤要求，即只要ID能通过过滤数据就能被收下。
		
		l_FilterNumberRegPosition = ( UINT32 )( 0x00000001 <<  l_FirstFilterNumber );		//过滤器一次加1相应的配置位左移一位											
		CAN1->FA1R.all &= ( UINT32 )( ~l_FilterNumberRegPosition );			// 禁止相应过滤器使能位 
		CAN1->FM1R.all |= ( UINT32 )l_FilterNumberRegPosition;				// 标识符模式  
		CAN1->FS1R.all |= ( UINT32 )l_FilterNumberRegPosition ;				// 设置位宽模式
		CAN1->Filter[ l_FirstFilterNumber ].FR1.all = *pId << 21;			// 写入ID 1 BIT21开始
		CAN1->Filter[ l_FirstFilterNumber ].FR2.all = *pFilterId << 21;		// 写入ID 2
		CAN1->FFA1R.all &= ( UINT32 )( ~l_FilterNumberRegPosition );		// 选择FIFO0 
		CAN1->FA1R.all |= ( UINT32 )l_FilterNumberRegPosition;				// 激活过滤器  
		l_FirstFilterNumber++;
		pId++;
		pFilterId++;
	}
	
	CAN1->FMR.bit.FINIT = 0;				// 过滤器退出初始化模式
}

/**
* @brief  设置CAN外设接收扩展ID.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  pId: 要设置的ID.
* @param  pFilterId: 要设置的验收滤波ID.
* @param  IdNumber: 要设置的ID数量.
* @attention 过滤器默认配置为32位位宽，标识符位模式，FIFO0
* @retval 无.
*/
void drv_can_slaver_set_rx_exp_id( CanType *pCan, UINT32 *pId, UINT32 *pFilterId, UINT8 IdNumber )
{
	UINT32 l_FilterNumberRegPosition = 0,l_Id =0, l_FilterId = 0;
	UINT8  l_FirstFilterNumber = 0;

	CAN1->FMR.bit.FINIT	= 1;				// 过滤器进入初始化
	while( IdNumber-- )
	{
		//CAN模块过滤器在过滤过程中，实际EXP_ID的比对是从FRx寄存器BIT3开始，BIT0保留，BIT1为RTR=0，BIT2为IDE=0。
		//在扩展数据帧中，IED=1,RTR=0,为了能满足过滤要求，将过滤器中IED为默认置1。
		
		l_Id = *pId;
		l_FilterId = *pFilterId;
		l_Id = l_Id << 3;
		l_FilterId = l_FilterId << 3;
		l_Id |= (UINT32)0x04 ;
		l_FilterId |= (UINT32)0x04 ;
		l_FilterNumberRegPosition = ( UINT32 )( 0x00000001 <<  l_FirstFilterNumber );	
		
		CAN1->FA1R.all &= ( UINT32 )( ~l_FilterNumberRegPosition );		// 禁止相应过滤器使能位 
		CAN1->FM1R.all |= ( UINT32 )l_FilterNumberRegPosition;;			// 标识符模式  
		CAN1->FS1R.all |= ( UINT32 )l_FilterNumberRegPosition ;			// 设置位宽模式
		CAN1->Filter[ l_FirstFilterNumber ].FR1.all = l_Id;				// 写入ID 
		CAN1->Filter[ l_FirstFilterNumber ].FR2.all = l_FilterId;		// 写入ID 
		CAN1->FFA1R.all &= ( UINT32 )( ~l_FilterNumberRegPosition );	// 选择FIFO0 
		CAN1->FA1R.all |= ( UINT32 )l_FilterNumberRegPosition;			// 激活过滤器  
		l_FirstFilterNumber++;
		pId++;
		pFilterId++;
	}
	
	CAN1->FMR.bit.FINIT = 0;							// 过滤器退出初始化模式
}

/**
* @brief  发送CAN报文.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  Id: 发送报文的ID.
* @param  IDE: 发送报文是标准帧还是扩展帧，可以是 CAN_ID_STD 和 CAN_ID_EXT .
* @param  RTR: 发送报文是数据帧还是遥控帧，可以是 CAN_RTR_DATA 和 CAN_RTR_REMOTE .
* @param  DLC: 发送报文数据字节数，可以是0 ~ 8 .
* @param  *pData: 报文要发送的数据 .
* @retval 0 ~ 3为发送邮箱编号，其他为发送失败（发送邮箱满）.
*/
UINT8 drv_can_tx( CanType *pCan, UINT32 Id, enumCanIdStdAndExtType IDE, UINT8 RTR, UINT8 DLC, UINT8 *pData )
{
	UINT8 l_TxMailBoxStatus = 0xFF;
	 
	if( pCan->TSR.bit.TME0 == 1 )
	{
		l_TxMailBoxStatus = 0;				// 邮箱0空  
	}
	else if( pCan->TSR.bit.TME1 == 1 )
	{
		l_TxMailBoxStatus = 1;				// 邮箱1空  
	}
	else
	{
		if( pCan->TSR.bit.TME2 == 1 )
		{
			l_TxMailBoxStatus = 2;			// 邮箱2空  
		}
	} 
	if(l_TxMailBoxStatus == 0xFF )
	{
		return 1;							// 未找到空邮箱供发送数据，返回错误代码1									
	}
	else
	{  
		if( IDE == CAN_ID_STANDARD )// 标准帧											
		{
			pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_st.TXRQ = 0;						// 清发送请求  
			pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_st.STID = (UINT16)( Id & 0x03FF );	// 写入标准帧ID  
			pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_st.IDE  = (UINT16)IDE;						// 写人IDE  
			pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_st.RTR  = RTR;						// 写入RTR  	
		} 
		else						// 扩展帧 
		{
			pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_ex.TXRQ = 0;						// 清发送请求  
			pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_ex.EXID = Id & 0x1FFFFFFF ;		// 写入扩展帧ID  
			pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_ex.IDE  = (UINT16)IDE;				// 写人IDE  
			pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_ex.RTR  = RTR;						// 写入RTR  
		} 
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDTR.bit.DLC = DLC;								// 写入发送数据的个数 
		// 写入发送数据  
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDLR.bit.DATA0 = pData[ 0 ];
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDLR.bit.DATA1 = pData[ 1 ];
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDLR.bit.DATA2 = pData[ 2 ];
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDLR.bit.DATA3 = pData[ 3 ];
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDHR.bit.DATA4 = pData[ 4 ];
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDHR.bit.DATA5 = pData[ 5 ];
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDHR.bit.DATA6 = pData[ 6 ];
		pCan->TxMailBox[ l_TxMailBoxStatus ].TDHR.bit.DATA7 = pData[ 7 ];
	} 
	pCan->TxMailBox[ l_TxMailBoxStatus ].TIR.bit_st.TXRQ = 1;	 // 请求发送 bit_STID.TXRQ == bit_EXID.TXRQ,他们指向同一寄存器地址
	
	return 0;
}

/**
* @brief  接收CAN报文.
* @note   每次接收到一帧消息要释放一次对应的FIFO.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  Fifo: 接收使用的FIFO，可以是 CAN_RX_FIFO0 和 CAN_RX_FIFO1 .
* @param  pRxMsg: 接收到的报文.
* @retval 0为接收到有效报文，其他为没有接收到报文.
*/
UINT8 drv_can_rx( CanType *pCan, enumCanRxFifoType Fifo, structCanMsgType *pRxMsg )
{
	UINT32 l_Rir = 0, l_Rdtr = 0, l_Rdlr = 0, l_Rdhr = 0;
	
	l_Rir = (UINT32)pCan->RxFifoMailBox[ Fifo ].RIR.all;
	l_Rdtr = (UINT32)pCan->RxFifoMailBox[ Fifo ].RDTR.all;
	l_Rdlr = (UINT32)pCan->RxFifoMailBox[ Fifo ].RDLR.all;
	l_Rdhr = (UINT32)pCan->RxFifoMailBox[ Fifo ].RDHR.all;
	
	// 取出IDE，RTR标志
	pRxMsg->IDE = (UINT8)((UINT32) (( l_Rir & CAN_RIR_REG_IDE ) >> 2 ) );
	pRxMsg->RTR = (UINT8)((UINT32) (( l_Rir & CAN_RIR_REG_RTR ) >> 1 ) );
	
	//ID
	if( pRxMsg->IDE == (UINT8)CAN_ID_STANDARD )									
	{
		pRxMsg->Id = (UINT32)(( l_Rir & CAN_RIR_REG_STD ) >> 21 );	
	} 
	else
	{
		pRxMsg->Id = (UINT32)(( l_Rir & CAN_RIR_REG_EXD ) >> 3 );
	}
	
	pRxMsg->DLC = (UINT8)((UINT32)( l_Rdtr & CAN_RDTR_REG_DLC ));			// 数据长度
	pRxMsg->FMI = (UINT8)((UINT32)(( l_Rdtr & CAN_RDTR_REG_FMI ) >> 8 ));	// 过滤器引索		  
	
	// 取数据  
	pRxMsg->Data[ 0 ] = (UINT8)l_Rdlr;
	pRxMsg->Data[ 1 ] = (UINT8)((UINT32)(l_Rdlr >> 8 ));
	pRxMsg->Data[ 2 ] = (UINT8)((UINT32)(l_Rdlr >> 16 ));
	pRxMsg->Data[ 3 ] = (UINT8)((UINT32)(l_Rdlr >> 24 ));
	
	pRxMsg->Data[ 4 ] = (UINT8)l_Rdhr;
	pRxMsg->Data[ 5 ] = (UINT8)((UINT32)(l_Rdhr >> 8 ));
	pRxMsg->Data[ 6 ] = (UINT8)((UINT32)(l_Rdhr >> 16 ));
	pRxMsg->Data[ 7 ] = (UINT8)((UINT32)(l_Rdhr >> 24 ));

	if( Fifo == CAN_RX_FIFO0 )
	{
		pCan->RF0R.bit.RFOM0 = 1;	// 释放FIFO0输出邮箱  
	}
	else
	{
		pCan->RF1R.bit.RFOM1 = 1;	// 释放FIFO1输出邮箱  
	}
	
	return 0;
}

/**
* @brief  释放一个CAN接收FIFO.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  Fifo: 接收使用的FIFO，可以是 CAN_RX_FIFO0 和 CAN_RX_FIFO1 .
* @retval 无.
*/
void drv_can_fifo_release( CanType *pCan, enumCanRxFifoType Fifo )
{
	if( Fifo == CAN_RX_FIFO0 )
	{
		pCan->RF0R.bit.RFOM0 = 1;	// 释放FIFO0输出邮箱  
	}
	else
	{
		pCan->RF1R.bit.RFOM1 = 1;	// 释放FIFO1输出邮箱  
	}
}

/**
* @brief  检查CAN接收FIFO是否有数据未被读取.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  Fifo: 接收使用的FIFO，可以是 CAN_RX_FIFO0 和 CAN_RX_FIFO1 .
* @retval 无.
*/
UINT8 drv_can_fifo_check( CanType *pCan, enumCanRxFifoType Fifo )
{
	UINT32 l_Rfr = 0;
	
	if( Fifo == CAN_RX_FIFO0 )
	{
		l_Rfr = (UINT32)pCan->RF0R.all;
	}
	else
	{
		l_Rfr = (UINT32)pCan->RF1R.all;
	}	

	return ((UINT8)( l_Rfr & CAN_RFR_REG_FMP ));
}

/**
* @brief  检查CAN错误状态.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @retval 错误状态寄存器所有值.
*/
UINT32 drv_can_get_error_status( CanType *pCan )
{
	return ( pCan->ESR.all );
}

/**
* @brief  CAN中断使能.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  CanIt: 中断源，可以是下面值的组合 .
  *            @arg CAN_IT_TME: Transmit mailbox empty Interrupt 
  *            @arg CAN_IT_FMP0: FIFO 0 message pending Interrupt 
  *            @arg CAN_IT_FF0: FIFO 0 full Interrupt
  *            @arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
  *            @arg CAN_IT_FMP1: FIFO 1 message pending Interrupt 
  *            @arg CAN_IT_FF1: FIFO 1 full Interrupt
  *            @arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
  *            @arg CAN_IT_WKU: Wake-up Interrupt
  *            @arg CAN_IT_SLK: Sleep acknowledge Interrupt  
  *            @arg CAN_IT_EWG: Error warning Interrupt
  *            @arg CAN_IT_EPV: Error passive Interrupt
  *            @arg CAN_IT_BOF: Bus-off Interrupt  
  *            @arg CAN_IT_LEC: Last error code Interrupt
  *            @arg CAN_IT_ERR: Error Interrupt
* @retval 无.
*/
void drv_can_it_enable( CanType *pCan, UINT32  CanIt )
{
	pCan->IER.all |= CanIt;
}

/**
* @brief  CAN中断禁止.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  CanIt: 中断源，可以是下面值的组合 . 参考 drv_can_it_enable 说明
* @retval 无.
*/
void drv_can_it_disable( CanType *pCan, UINT32  CanIt )
{
	pCan->IER.all &= (UINT32)~CanIt;
}

/**
* @brief  检查CAN标志状态.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  CanFlag: 要检查的标志，可以是下面值的一个 .
  *            @arg CanFlag_RQCP0: Request MailBox0 Flag
  *            @arg CanFlag_RQCP1: Request MailBox1 Flag
  *            @arg CanFlag_RQCP2: Request MailBox2 Flag
  *            @arg CanFlag_FMP0: FIFO 0 Message Pending Flag   
  *            @arg CanFlag_FF0: FIFO 0 Full Flag       
  *            @arg CanFlag_FOV0: FIFO 0 Overrun Flag 
  *            @arg CanFlag_FMP1: FIFO 1 Message Pending Flag   
  *            @arg CanFlag_FF1: FIFO 1 Full Flag        
  *            @arg CanFlag_FOV1: FIFO 1 Overrun Flag     
  *            @arg CanFlag_WKU: Wake up Flag
  *            @arg CanFlag_SLAK: Sleep acknowledge Flag 
  *            @arg CanFlag_EWG: Error Warning Flag
  *            @arg CanFlag_EPV: Error Passive Flag  
  *            @arg CanFlag_BOF: Bus-Off Flag    
  *            @arg CanFlag_LEC: Last error code Flag   
* @retval 标志的状态，为 SET 或 RESET .
*/
FlagStatus drv_can_get_flag_status( CanType *pCan, UINT32  CanFlag )
{
	FlagStatus bitstatus = RESET;

	if(( CanFlag & CAN_FLAGS_ESR ) != (UINT32)RESET )
	{
		//ESR FLAG
		if (( pCan->ESR.all & ( CanFlag & 0x000FFFFF )) != (UINT32)RESET )
		{ 
			bitstatus = SET;
		}
		else
		{ 
			bitstatus = RESET;
		}
	}
	else if(( CanFlag & CAN_FLAGS_MSR ) != (UINT32)RESET )
	{ 
		//MSR FLAG
		if ((pCan->MSR.all & ( CanFlag & 0x000FFFFF )) != (UINT32)RESET )
		{ 
			bitstatus = SET;
		}
		else
		{ 
			bitstatus = RESET;
		}
	}
	else if(( CanFlag & CAN_FLAGS_TSR ) != (UINT32)RESET )
	{ 
		//TSR FLAG
		if (( pCan->TSR.all & (CanFlag & 0x000FFFFF )) != (UINT32)RESET )
		{ 
			bitstatus = SET;
		}
		else
		{ 
			bitstatus = RESET;
		}
	}
	else if(( CanFlag & CAN_FLAGS_RF0R ) != (UINT32)RESET )
	{ 
		//RF0R FLAG
		if (( pCan->RF0R.all & ( CanFlag & 0x000FFFFF )) != (UINT32)RESET )
		{ 
			bitstatus = SET;
		}
		else
		{ 
			bitstatus = RESET;
		}
	}
	else /* If(CAN_FLAG & CAN_FLAGS_RF1R != (UINT32)RESET) */
	{ 
		//RF1R FLAG
		if ((UINT32)( pCan->RF1R.all & ( CanFlag & 0x000FFFFF )) != (UINT32)RESET )
		{ 
			bitstatus = SET;
		}
		else
		{ 
			bitstatus = RESET;
		}
	}
	
	return  bitstatus;
}

/**
* @brief  清除CAN标志状态.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  CanFlag: 要清除的标志，可以是下面值的一个 .
  *            @arg CAN_FLAG_RQCP0: Request MailBox0 Flag
  *            @arg CAN_FLAG_RQCP1: Request MailBox1 Flag
  *            @arg CAN_FLAG_RQCP2: Request MailBox2 Flag 
  *            @arg CAN_FLAG_FF0: FIFO 0 Full Flag       
  *            @arg CAN_FLAG_FOV0: FIFO 0 Overrun Flag  
  *            @arg CAN_FLAG_FF1: FIFO 1 Full Flag        
  *            @arg CAN_FLAG_FOV1: FIFO 1 Overrun Flag     
  *            @arg CAN_FLAG_WKU: Wake up Flag
  *            @arg CAN_FLAG_SLAK: Sleep acknowledge Flag    
  *            @arg CAN_FLAG_LEC: Last error code Flag   
* @retval 无 .
*/
void drv_can_clear_flag_status( CanType *pCan, UINT32 CanFlag )
{
	UINT32 flagtmp=0;

	if ( CanFlag == CAN_FLAG_LEC) /* ESR register */
	{
		pCan->ESR.all = (UINT32)RESET;
	}
	else /* MSR or TSR or RF0R or RF1R */
	{
		flagtmp = CanFlag & 0x000FFFFF;

		if (( CanFlag & CAN_FLAGS_RF0R ) != (UINT32)RESET )
		{
			/* Receive Flags */
			pCan->RF0R.all = (UINT32)(flagtmp);
		}
		else if (( CanFlag & CAN_FLAGS_RF1R )!= (UINT32)RESET )
		{
			/* Receive Flags */
			pCan->RF1R.all = (UINT32)(flagtmp);
		}
		else if (( CanFlag & CAN_FLAGS_TSR) != (UINT32)RESET )
		{
			/* Transmit Flags */
			pCan->TSR.all = (UINT32)(flagtmp);
		}
		else /* If((CAN_FLAG & CAN_FLAGS_MSR)!=(UINT32)RESET) */
		{
			/* Operating mode Flags */
			pCan->MSR.all = (UINT32)(flagtmp);
		}
	}
}

/**
* @brief  检查CAN中断状态.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  CanIt: 要检查的中断状态，可以是下面值的一个 .
*            @arg CAN_IT_TME: Transmit mailbox empty Interrupt
*            @arg CAN_IT_FMP0: FIFO 0 message pending Interrupt
*            @arg CAN_IT_FF0: FIFO 0 full Interrupt
*            @arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
*            @arg CAN_IT_FMP1: FIFO 1 message pending Interrupt
*            @arg CAN_IT_FF1: FIFO 1 full Interrupt
*            @arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
*            @arg CAN_IT_WKU: Wake-up Interrupt
*            @arg CAN_IT_SLK: Sleep acknowledge Interrupt
*            @arg CAN_IT_EWG: Error warning Interrupt
*            @arg CAN_IT_EPV: Error passive Interrupt
*            @arg CAN_IT_BOF: Bus-off Interrupt
*            @arg CAN_IT_LEC: Last error code Interrupt
*            @arg CAN_IT_ERR: Error Interrupt
* @retval 标志的状态，为 SET 或 RESET .
*/
ITStatus drv_can_get_it_status( CanType *pCan, UINT32 CanIt )
{
	ITStatus l_ReturnStatus = RESET;
	
	if(( pCan->IER.all & CanIt ) != (UINT32)RESET )
	{
		switch( CanIt )
		{
			case CAN_IT_TME: 
				if(( pCan->TSR.all & 0x00010101 ) != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_FMP0:
				if( pCan->RF0R.bit.FMP0 != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_FF0:
				if( pCan->RF0R.bit.FULL0 != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_FOV0:
				if( pCan->RF0R.bit.FOVR0 != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_FMP1:
				if( pCan->RF1R.bit.FMP1 != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_FF1:
				if( pCan->RF1R.bit.FULL1 != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_FOV1:
				if( pCan->RF1R.bit.FOVR1 != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_WKU:
				if( pCan->MSR.bit.WKUI != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_SLK:
				if( pCan->MSR.bit.SLAKI != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_EWG:
				if( pCan->ESR.bit.EWGF != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_EPV:
				if( pCan->ESR.bit.EPVF != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_BOF:
				if( pCan->ESR.bit.BOFF != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_LEC:
				if( pCan->ESR.bit.LEC != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			case CAN_IT_ERR:
				if( pCan->MSR.bit.ERRI != (UINT32)RESET )
				{
					l_ReturnStatus = SET;
				}
				else
				{
					l_ReturnStatus = RESET;
				}
				break;
			default: l_ReturnStatus = RESET; break;
		}
	}
	else
	{
		l_ReturnStatus = RESET;
	}
	return l_ReturnStatus;
}

/**
* @brief  清除CAN中断挂起标志.
* @param  pCan: 要操作的CAN外设，可以是CAN1和CAN2.
* @param  CanIt: 要清除的的中断挂起标志，可以是下面值的一个 .
*            @arg CAN_IT_TME: Transmit mailbox empty Interrupt
*            @arg CAN_IT_FF0: FIFO 0 full Interrupt
*            @arg CAN_IT_FOV0: FIFO 0 overrun Interrupt
*            @arg CAN_IT_FF1: FIFO 1 full Interrupt
*            @arg CAN_IT_FOV1: FIFO 1 overrun Interrupt
*            @arg CAN_IT_WKU: Wake-up Interrupt
*            @arg CAN_IT_SLK: Sleep acknowledge Interrupt
*            @arg CAN_IT_EWG: Error warning Interrupt
*            @arg CAN_IT_EPV: Error passive Interrupt
*            @arg CAN_IT_BOF: Bus-off Interrupt
*            @arg CAN_IT_LEC: Last error code Interrupt
*            @arg CAN_IT_ERR: Error Interrupt
* @retval 无 .
*/
void drv_can_clear_it_pending_bit( CanType *pCan, UINT32 CanIt )
{
	switch ( CanIt )
	{
		//写1清0
		case CAN_IT_TME:
			pCan->TSR.bit.RQCP0 = 0; 
			pCan->TSR.bit.RQCP1 = 0;
			pCan->TSR.bit.RQCP2 = 0; break;		
		case CAN_IT_FF0:
			pCan->RF0R.bit.FULL0 = 1; break;
		case CAN_IT_FOV0:
			pCan->RF0R.bit.FOVR0 = 1; break;
		case CAN_IT_FF1:
			pCan->RF1R.bit.FULL1 = 1; break;
		case CAN_IT_FOV1:
			pCan->RF1R.bit.FOVR1 = 1; break;
		case CAN_IT_WKU:
			pCan->MSR.bit.WKUI = 1; break;
		case CAN_IT_SLK:
			pCan->MSR.bit.SLAKI = 1; break;
		case CAN_IT_EWG:
			pCan->MSR.bit.ERRI = 1; break;
		case CAN_IT_EPV:
			pCan->MSR.bit.ERRI = 1; break;
		case CAN_IT_BOF:
			pCan->MSR.bit.ERRI = 1; break;
		case CAN_IT_LEC:
			pCan->ESR.all = (UINT32)RESET; 
			pCan->MSR.bit.ERRI = 1; break;
		case CAN_IT_ERR:
			pCan->ESR.all = (UINT32)RESET; 
			pCan->MSR.bit.ERRI = 1; break;
		default:
		break;
	}
}



