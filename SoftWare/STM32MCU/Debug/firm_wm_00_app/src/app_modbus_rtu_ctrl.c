/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "drv_flash.h"
#include "app_main_task.h"
#include "app_modbus_rtu_ctrl.h"
#include "app_crc.h"
#include "app_hx711_ctrl.h"
#include "app_crc.h"
#include "hal_delay.h"
#include "app_sdwe_ctrl.h"
#include "app_syspara.h"
#include "app_t5l_ctrl.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
ModbusRtuType g_ModbusRtu = ModbusRtuDefault;

/*******************************************************************************
 * Functions
 ******************************************************************************/
//==ModbusRtu initial
void ModbusRtu_init(void)
{
	//
	g_ModbusRtu.pUartDevice = &g_UartDevice[UART_COM];
	//
	g_ModbusRtu.pUartDevice->pRxLength = &g_ModbusRtu.RxLength;
	g_ModbusRtu.pUartDevice->pRxFinishFlag = &g_ModbusRtu.RxFinishFlag;
	g_ModbusRtu.pUartDevice->pTxBuffer = &g_ModbusRtu.txData[0];
	g_ModbusRtu.pUartDevice->pRxBuffer = &g_ModbusRtu.rxDataUart[0];
	//
	//
	g_ModbusRtu.RxLength = 0;					/**< 接收字节数 */
	g_ModbusRtu.RxFinishFlag = FALSE;			/**< 接收完成标志 */
	//
	g_ModbusRtu.pUartDevice->init(g_ModbusRtu.pUartDevice);
}


void modbusRemoveAllWeightData(void)
{
	UINT8 com_id = 0 ,chn_i = 0;
	//clear com data
	for(com_id=0;com_id<(ModbusAdd_Slave_Max - ModbusAdd_Master);com_id++)
	{
		for(chn_i=0;chn_i<MODBUS_RTU_SLAVE_CHANEL_NUM;chn_i++)
		{
			g_ModbusRtu.MultWeightData[com_id][chn_i].f_value = 0.0;
		}
	}
	//clear gloabal data
}
void setModbusSelfRemoveFlag(UINT8 value)
{
	g_ModbusRtu.removeWeight_Slef = value;
}
void setModbusDataValid(UINT8 value)
{
	g_ModbusRtu.dataValid = value;
}

void setModbusOtherRemoveFlag(UINT8 value)
{
	g_ModbusRtu.removeWeight_Other = value;
}

UINT8 getModbusOtherRemoveFlag(void)
{
	return g_ModbusRtu.removeWeight_Other;
}

UINT8 ModbusRtu_RxMainFunction(ModbusRtuType *pContex)
{
	UINT16 rcv_valid = FALSE , i = 0;
#if(TRUE == MODBUS_RTU_CRC_EN)
	UINT16 crc_data = 0 ;
#endif
	
	//rx data from bus
	if(TRUE == pContex->RxFinishFlag)
	{
		//1.clear flag
		pContex->RxFinishFlag = FALSE;
		//2.judge len
		if((pContex->RxLength > 2) && (pContex->RxLength < MODBUS_RTU_UART_DATA_LEN))
		{
			//2.crc check
			#if(TRUE == MODBUS_RTU_CRC_EN)
				crc_data = (pContex->rxDataUart[pContex->RxLength-2]<<8)&0xff00;
				crc_data += pContex->rxDataUart[pContex->RxLength-1];
				if(crc_data == cal_crc16(pContex->rxDataUart,(pContex->RxLength-2)))
				{
					for(i=0;i<pContex->RxLength;i++)
					{
						pContex->rxData[i] = pContex->rxDataUart[i];
					}
					//
					rcv_valid = TRUE;
				}
			#else
				rcv_valid = TRUE;
			#endif
		}
	}
	return rcv_valid;
}
//==master mask scan
void ModbusRtu_MasterCycleReadWeightScan(ModbusRtuType *pContex)
{
#if 0//before 20211229 used normal
	if(0 == (pContex->sysTick % MasterTimer_EventTriger_TX_T5))
	{
		pContex->masterTxMask |= MasterEvent_Tx_E5;
		//read slave ID
		pContex->slaveID++;
		if(pContex->slaveID >= ModbusAdd_Slave_Max)
		{
			pContex->slaveID = ModbusAdd_Slave_1;
		}
	}
#else//20220119 changed
	if(0 == (pContex->sysTick % MasterTimer_EventTriger_TX_T6))
	{
		pContex->masterTxMask |= MasterEvent_Tx_E6;
		//read slave ID
		switch(gSystemPara.isCascade)
		{
			case ModbusAdd_Master:
				pContex->slaveID = ModbusAdd_Slave_1;
			break;
			case ModbusFuncA_Master:
					pContex->slaveID = ModbusFuncA_Slave;
			break;
			default:
			break;
		}
	}
#endif
}
//==master mask deal
UINT8 ModbusRtu_MasterMaskDeal(ModbusRtuType *pContex)
{
	UINT16 ret =FALSE , star_pos = 0;
#if(TRUE == MODBUS_RTU_CRC_EN)
	UINT16 crc_data = 0 ;
#endif
	if((pContex->masterTxMask & MasterEvent_Tx_E1) != 0 )//CycleReadWeightFloat
	{
		//clear Mask
		pContex->masterTxMask &= (~MasterEvent_Tx_E1);
		//
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = pContex->slaveID;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Mater_Ask_1;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MFC_ASK_MAJID_LEN;
		pContex->txData[MODBUS_RTU_DATA_STAR_POS] = MFC_Mater_Ask_1;
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+MFC_ASK_MAJID_LEN+1;
		//	
		#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
		#endif
		//
		ret = TRUE;
	}
	else if((pContex->masterTxMask & MasterEvent_Tx_E2) != 0 )//CycleReadWeightInit
	{
		//clear Mask
		pContex->masterTxMask &= (~MasterEvent_Tx_E2);
		//
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = pContex->slaveID;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Mater_Ask_2;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MFC_ASK_MAJID_LEN;
		pContex->txData[MODBUS_RTU_DATA_STAR_POS] = MFC_Mater_Ask_2;
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+MFC_ASK_MAJID_LEN+1;
		//	
	#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
	#endif
		//
		ret = TRUE;
	}
	else if((pContex->masterTxMask & MasterEvent_Tx_E3) != 0 )//CycleReadWeightFloat + SetHelpDataToSlave1
	{
		//clear Mask
		pContex->masterTxMask &= (~MasterEvent_Tx_E3);
		//
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = pContex->slaveID;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Mater_Ask_3;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MFC_ASK_MAJID_LEN + 2*DIFF_TO_DIWEN_DATA_LEN;
		pContex->txData[MODBUS_RTU_DATA_STAR_POS] = MFC_Mater_Ask_3;
		readHelpDataFromSys(&pContex->txData[MODBUS_RTU_DATA_STAR_POS+MFC_ASK_MAJID_LEN],DIFF_TO_DIWEN_DATA_LEN);
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+MFC_ASK_MAJID_LEN+1+2*DIFF_TO_DIWEN_DATA_LEN;
		//	
		#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
		#endif
		//
		ret = TRUE;
	}
	else if((pContex->masterTxMask & MasterEvent_Tx_E4) != 0 )
	{
		//clear Mask
		pContex->masterTxMask &= (~MasterEvent_Tx_E4);
		//
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = pContex->slaveID;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Mater_Ask_4;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN+1;
		pContex->txData[MODBUS_RTU_DATA_STAR_POS] = MFC_Mater_Ask_4;
		readHelpDataFromSys(&pContex->txData[MODBUS_RTU_DATA_STAR_POS+MFC_ASK_MAJID_LEN],DIFF_TO_DIWEN_DATA_LEN);
		pContex->txData[MODBUS_RTU_DATA_STAR_POS+MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN] = pContex->removeWeight_Slef;
		pContex->removeWeight_Slef = FALSE;
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+MFC_ASK_MAJID_LEN+1+2*DIFF_TO_DIWEN_DATA_LEN+1;
		//	
		#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
		#endif
		//
		ret = TRUE;
	}
	else if((pContex->masterTxMask & MasterEvent_Tx_E5) != 0 )
	{
		//clear Mask
		pContex->masterTxMask &= (~MasterEvent_Tx_E5);
		//
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = pContex->slaveID;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Mater_Ask_5;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN+1+2*T5L_MAX_CHANEL_LEN+2*T5L_MAX_CHANEL_LEN;
		pContex->txData[MODBUS_RTU_DATA_STAR_POS] = MFC_Mater_Ask_5;
		//
		star_pos = MODBUS_RTU_DATA_STAR_POS + 1;
		readHelpDataFromSys(&pContex->txData[star_pos],DIFF_TO_DIWEN_DATA_LEN);
		//
		star_pos += 2*DIFF_TO_DIWEN_DATA_LEN;
		pContex->txData[star_pos] = pContex->removeWeight_Slef;
		pContex->removeWeight_Slef = FALSE;
		//
		star_pos += 1;
		readWeightDataFromSys(&pContex->txData[star_pos],T5L_MAX_CHANEL_LEN);
		//
		star_pos += 2*T5L_MAX_CHANEL_LEN;
		readColorDataFromSys(&pContex->txData[star_pos],T5L_MAX_CHANEL_LEN);

		//
		star_pos += 2*T5L_MAX_CHANEL_LEN;
		pContex->needSendLen = star_pos + 1;
		//	
	#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
	#endif
		//
		ret = TRUE;
	}
	else if((pContex->masterTxMask & MasterEvent_Tx_E6) != 0 )
	{
		//clear Mask
		pContex->masterTxMask &= (~MasterEvent_Tx_E6);
		//
		switch(gSystemPara.isCascade)
		{
			case ModbusAdd_Master:
				pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = ModbusAdd_Master ;
			break;
			case ModbusFuncA_Master:
				pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = ModbusFuncA_Master ;
			break;
			default:
			break;
		}
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = pContex->slaveID;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Mater_Ask_6;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN+1+2*T5L_MAX_CHANEL_LEN+2*T5L_MAX_CHANEL_LEN;
		pContex->txData[MODBUS_RTU_DATA_STAR_POS] = MFC_Mater_Ask_6;
		//
		star_pos = MODBUS_RTU_DATA_STAR_POS + 1;
		readHelpDataFromSys(&pContex->txData[star_pos],DIFF_TO_DIWEN_DATA_LEN);
		//
		star_pos += 2*DIFF_TO_DIWEN_DATA_LEN;
		pContex->txData[star_pos] = pContex->removeWeight_Slef;
		pContex->removeWeight_Slef = FALSE;
		//
		star_pos += 1;
		readWeightDataFromSys(&pContex->txData[star_pos],T5L_MAX_CHANEL_LEN);
		//
		star_pos += 2*T5L_MAX_CHANEL_LEN;
		readColorDataFromSys(&pContex->txData[star_pos],T5L_MAX_CHANEL_LEN);

		//
		star_pos += 2*T5L_MAX_CHANEL_LEN;
		pContex->needSendLen = star_pos + 1;
		//	
#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
#endif
		//
		ret = TRUE;
	}
	return ret;
}

//==master TX main function
void ModbusRtu_MasterTxMainFunction(ModbusRtuType *pContex)
{
	//make cycle read Mask 
	ModbusRtu_MasterCycleReadWeightScan(pContex);

	//masterState deal
	switch(pContex->masterState)
	{
		//master orderA and orderB need delay
		case MasterState_Idle:
			pContex->masterTxDiffTick++;
			if(pContex->masterTxDiffTick >= MasterTimer_TxOrderDlay)
			{
				pContex->masterState = MasterState_AllowTx;
			}
		break;
		//master allow to seed
		case MasterState_AllowTx:
			//Mask Deal
			if(TRUE == ModbusRtu_MasterMaskDeal(pContex))
			{
				pContex->pUartDevice->tx_bytes(pContex->pUartDevice,pContex->txData,pContex->needSendLen);
				//
				pContex->masterState = MasterState_WaitRx;
				pContex->masterMaxWaitRxTick = 0 ;
			}	
		break;
		//master wait RX
		case MasterState_WaitRx:
			if( pContex->masterMaxWaitRxTick++ >= MasterTimer_RxTimeOut)
			{
				pContex->masterState = MasterState_AllowTx;
			}
			//if recv slave answer , goto IDLE
			if(TRUE == pContex->RxFinishFlag)
			{
				pContex->masterState = MasterState_Idle;
			}
		break;
		default :
			pContex->masterState = MasterState_Idle;
		break;
	}
}
//==master RX main function
void ModbusRtu_MasterRxMainFunction(ModbusRtuType *pContex)
{
	UINT16 i = 0 , sender_add = 0 , recive_add = 0;

	//sender_ID , recv_ID
	sender_add = pContex->rxData[MODBUS_RTU_SEND_ADDRESS_POS];
	recive_add = pContex->rxData[MODBUS_RTU_ASK_ADDRESS_POS];
	//
	if((sender_add >= ModbusAdd_Slave_1) && (sender_add < ModbusAdd_Slave_Max) )
	{
		if((ModbusAdd_Master == recive_add) && (ModbusAdd_Master == gSystemPara.isCascade))
		{
			switch(pContex->rxData[MODBUS_RTU_FUN_CODE_POS])
			{
				case MFC_Slave_Ans_1://master recv slave answer weight was float
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == MODBUS_RTU_SLAVE_DATA_LEN)
					{
						//recv data
						for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
						{
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[0] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[1] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+1];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[2] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+2];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[3] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+3];
						}
					}
				break;
				case MFC_Slave_Ans_2://master recv slave answer weight was int
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == MODBUS_RTU_SLAVE_DATA_LEN)
					{
						//recv data
						for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
						{
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].i_value = 0 ;
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].i_value += pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].i_value <<= 8;
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].i_value += pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+1];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].i_value <<= 8;
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].i_value += pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+2];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].i_value <<= 8;
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].i_value += pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+3];
						}
					}
				break;
				case MFC_Slave_Ans_3://master recv slave answer weight was flaot
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == MODBUS_RTU_SLAVE_DATA_LEN)
					{
						//recv data
						for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
						{
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[0] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[1] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+1];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[2] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+2];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[3] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+3];
						}
					}
				break;
				case MFC_Slave_Ans_4://master recv slave answer weight was flaot , remove flag
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MODBUS_RTU_SLAVE_DATA_LEN+1))
					{
						//recv data
						for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
						{
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[0] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[1] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+1];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[2] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+2];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[3] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+3];
						}
						//
						if(TRUE == pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0])
						{
							pContex->removeWeight_Other = TRUE;
						}
					}
				break;
				case MFC_Slave_Ans_5://master recv slave answer weight was flaot , remove flag
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MODBUS_RTU_SLAVE_DATA_LEN+1))
					{
						//recv data
						for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
						{
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[0] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[1] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+1];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[2] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+2];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[3] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+3];
						}
						//
						if(TRUE == pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0])
						{
							pContex->removeWeight_Other = TRUE;
						}
					}
				break;
				case MFC_Slave_Ans_6://master recv slave answer weight was flaot , remove flag
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MODBUS_RTU_SLAVE_DATA_LEN+1))
					{
						//recv data
						for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
						{
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[0] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[1] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+1];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[2] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+2];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[3] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+3];
						}
						//
						if(TRUE == pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0])
						{
							pContex->removeWeight_Other = TRUE;
						}
					}
				break;				
				default:
				break;
			}
		}
	}
	else if(sender_add == ModbusFuncA_Slave)
	{
		if((ModbusFuncA_Master == recive_add) && (ModbusFuncA_Master == gSystemPara.isCascade))
		{
			sender_add = 2;
			switch(pContex->rxData[MODBUS_RTU_FUN_CODE_POS])
			{
				case MFC_Slave_Ans_6://master recv slave answer weight was flaot , remove flag
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MODBUS_RTU_SLAVE_DATA_LEN+1))
					{
						//recv data
						for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
						{
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[0] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[1] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+1];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[2] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+2];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[3] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+3];
						}
						//
						if(TRUE == pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0])
						{
							pContex->removeWeight_Other = TRUE;
						}
					}
				break;				
				default:
				break;
			}
		}
	}
}

//==slave rx main function
void ModbusRtu_SlaveRxMainFunction(ModbusRtuType *pContex)
{
	UINT16 sender_add = 0 , recive_add = 0 , star_pos = 0 ;
	//sender_ID , recv_ID
	sender_add = pContex->rxData[MODBUS_RTU_SEND_ADDRESS_POS];
	recive_add = pContex->rxData[MODBUS_RTU_ASK_ADDRESS_POS];
	//
	if(ModbusAdd_Master == sender_add)
	{
		if((recive_add >= ModbusAdd_Slave_1) && (recive_add < ModbusAdd_Slave_Max) && (recive_add == gSystemPara.isCascade))
		{
			switch(pContex->rxData[MODBUS_RTU_FUN_CODE_POS])
			{
				case MFC_Mater_Ask_1://master ask slave chanel weight:float
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == MFC_ASK_MAJID_LEN)
					{
						if(pContex->rxData[MODBUS_RTU_DATA_STAR_POS] == MFC_Mater_Ask_1)
						{
							pContex->slaveTxMask |= SlaveEvent_Tx_E1;
						}
					}
				break;
				case MFC_Mater_Ask_2://master ask slave chanel weight:int32
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == MFC_ASK_MAJID_LEN)
					{
						if(pContex->rxData[MODBUS_RTU_DATA_STAR_POS] == MFC_Mater_Ask_2)
						{
							pContex->slaveTxMask |= SlaveEvent_Tx_E2;
						}
					}
				break;
				case MFC_Mater_Ask_3:
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN))
					{
						if(pContex->rxData[MODBUS_RTU_DATA_STAR_POS] == MFC_Mater_Ask_3)
						{
							//rx data
							writeHelpDataFromCom(&pContex->rxData[MODBUS_RTU_DATA_STAR_POS+1],DIFF_TO_DIWEN_DATA_LEN);
							//
							pContex->slaveTxMask |= SlaveEvent_Tx_E3;
						}
					}
				break;
				case MFC_Mater_Ask_4:
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN+1))
					{
						if(pContex->rxData[MODBUS_RTU_DATA_STAR_POS] == MFC_Mater_Ask_4)
						{
							//rx data
							writeHelpDataFromCom(&pContex->rxData[MODBUS_RTU_DATA_STAR_POS+1],DIFF_TO_DIWEN_DATA_LEN);
							if(TRUE == pContex->rxData[MODBUS_RTU_DATA_STAR_POS+1+2*DIFF_TO_DIWEN_DATA_LEN])
							{
								pContex->removeWeight_Other = TRUE;
								//
							}
					
							//
							pContex->slaveTxMask |= SlaveEvent_Tx_E4;
						}
					}
				break;
				case MFC_Mater_Ask_5:
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN+1+2*T5L_MAX_CHANEL_LEN+2*T5L_MAX_CHANEL_LEN))
					{
						if(pContex->rxData[MODBUS_RTU_DATA_STAR_POS] == MFC_Mater_Ask_5)
						{
							//rx data
							star_pos = MODBUS_RTU_DATA_STAR_POS+1;
							writeHelpDataFromCom(&pContex->rxData[star_pos],DIFF_TO_DIWEN_DATA_LEN);
							//
							star_pos += 2*DIFF_TO_DIWEN_DATA_LEN;
							if(TRUE == pContex->rxData[star_pos])
							{
								pContex->removeWeight_Other = TRUE;
							}
							//
							star_pos += 1;
							writeWeightDataFromCom(&pContex->rxData[star_pos],T5L_MAX_CHANEL_LEN);
							//
							star_pos += 2*T5L_MAX_CHANEL_LEN;
							writeColorDataFromCom(&pContex->rxData[star_pos],T5L_MAX_CHANEL_LEN);
							//
							pContex->slaveTxMask |= SlaveEvent_Tx_E5;
						}
					}
				break;
				case MFC_Mater_Ask_6:
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN+1+2*T5L_MAX_CHANEL_LEN+2*T5L_MAX_CHANEL_LEN))
					{
						if(pContex->rxData[MODBUS_RTU_DATA_STAR_POS] == MFC_Mater_Ask_6)
						{
							//rx data
							star_pos = MODBUS_RTU_DATA_STAR_POS+1;
							writeHelpDataFromCom(&pContex->rxData[star_pos],DIFF_TO_DIWEN_DATA_LEN);
							//
							star_pos += 2*DIFF_TO_DIWEN_DATA_LEN;
							if(TRUE == pContex->rxData[star_pos])
							{
								pContex->removeWeight_Other = TRUE;
							}
							//
							star_pos += 1;
							writeWeightDataFromCom(&pContex->rxData[star_pos],T5L_MAX_CHANEL_LEN);
							//
							star_pos += 2*T5L_MAX_CHANEL_LEN;
							writeColorDataFromCom(&pContex->rxData[star_pos],T5L_MAX_CHANEL_LEN);
							//
							pContex->slaveTxMask |= SlaveEvent_Tx_E6;
						}
					}
				break;
				default:
				break;
			}
		}
	}
	else if(ModbusFuncA_Master == sender_add)
	{
		if((recive_add == ModbusFuncA_Slave) && (recive_add == gSystemPara.isCascade))
		{
			switch(pContex->rxData[MODBUS_RTU_FUN_CODE_POS])
			{
				case MFC_Mater_Ask_6:
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MFC_ASK_MAJID_LEN+2*DIFF_TO_DIWEN_DATA_LEN+1+2*T5L_MAX_CHANEL_LEN+2*T5L_MAX_CHANEL_LEN))
					{
						if(pContex->rxData[MODBUS_RTU_DATA_STAR_POS] == MFC_Mater_Ask_6)
						{
							//rx data
							star_pos = MODBUS_RTU_DATA_STAR_POS+1;
							writeHelpDataFromCom(&pContex->rxData[star_pos],DIFF_TO_DIWEN_DATA_LEN);
							//
							star_pos += 2*DIFF_TO_DIWEN_DATA_LEN;
							if(TRUE == pContex->rxData[star_pos])
							{
								pContex->removeWeight_Other = TRUE;
							}
							//
							star_pos += 1;
							writeWeightDataFromCom(&pContex->rxData[star_pos],T5L_MAX_CHANEL_LEN);
							//
							star_pos += 2*T5L_MAX_CHANEL_LEN;
							writeColorDataFromCom(&pContex->rxData[star_pos],T5L_MAX_CHANEL_LEN);
							//
							pContex->slaveTxMask |= SlaveEvent_Tx_E6;
						}
					}
				break;
				default:
				break;
			}
		}
	}
}
//==slave tx mask deal function
UINT8 ModbusRtu_SlaveTxMaskDeal(ModbusRtuType *pContex)
{
	UINT8 ret = 0 ;
	UINT16 i = 0 ,recive_add = 0;
#if(TRUE == MODBUS_RTU_CRC_EN)
		UINT16 crc_data = 0 ;
#endif
	//sender_ID , recv_ID
	recive_add = pContex->rxData[MODBUS_RTU_ASK_ADDRESS_POS];
	if((pContex->slaveTxMask & SlaveEvent_Tx_E1 ) != 0)
	{
		pContex->slaveTxMask &= (~SlaveEvent_Tx_E1);
		//
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = gSystemPara.isCascade;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Slave_Ans_1;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MODBUS_RTU_SLAVE_DATA_LEN;
		//===================push data to MultWeightData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value = hx711_getWeight((enumHX711ChanelType)i);
		}
		//===================push data to txData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[0];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+1] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[1];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+2] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[2];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+3] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[3];
		}
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+4*i;
		//crc
		#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
		#endif
		//
		ret =TRUE;
	}
	else if((pContex->slaveTxMask & SlaveEvent_Tx_E2 ) != 0)
	{
		pContex->slaveTxMask &= (~SlaveEvent_Tx_E2);
		//
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = gSystemPara.isCascade;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Slave_Ans_2;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MODBUS_RTU_SLAVE_DATA_LEN;
		//===================push data to MultWeightData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value = hx711_getWeight((enumHX711ChanelType)i);
		}
		//===================push data to txData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = (((INT32)pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value)>>24)&0xff;
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+1] = (((INT32)pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value)>>16)&0xff;
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+2] = (((INT32)pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value)>>8)&0xff;
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+3] = (((INT32)pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value)>>0)&0xff;
		}
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+4*i;
		//crc
		#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
			#endif
		//
		ret =TRUE;
	}
	else if((pContex->slaveTxMask & SlaveEvent_Tx_E3 ) != 0)
	{
		pContex->slaveTxMask &= (~SlaveEvent_Tx_E3);
		//
		//tx data
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = gSystemPara.isCascade;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Slave_Ans_3;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MODBUS_RTU_SLAVE_DATA_LEN;
		//===================push data to MultWeightData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value = hx711_getWeight((enumHX711ChanelType)i);
		}
		//===================push data to txData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[0];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+1] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[1];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+2] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[2];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+3] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[3];
		}
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+4*i;
		//crc
		#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
		#endif
		//
		ret =TRUE;
	}
	else if((pContex->slaveTxMask & SlaveEvent_Tx_E4) != 0)
	{
		pContex->slaveTxMask &= (~SlaveEvent_Tx_E4);
		//
		//tx data
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = gSystemPara.isCascade;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Slave_Ans_4;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MODBUS_RTU_SLAVE_DATA_LEN+1;
		//===================push data to MultWeightData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value = hx711_getWeight((enumHX711ChanelType)i);
		}
		//===================push data to txData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[0];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+1] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[1];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+2] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[2];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+3] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[3];
		}
		pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = pContex->removeWeight_Slef;
		pContex->removeWeight_Slef = FALSE;
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+4*i+1;
		//crc
		#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
		#endif
		//
		ret =TRUE;
	}
	else if((pContex->slaveTxMask & SlaveEvent_Tx_E5) != 0)
	{
		pContex->slaveTxMask &= (~SlaveEvent_Tx_E5);
		//
		//tx data
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = gSystemPara.isCascade;
		pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = ModbusAdd_Master;
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Slave_Ans_5;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MODBUS_RTU_SLAVE_DATA_LEN+1;
		//===================push data to MultWeightData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value = hx711_getWeight((enumHX711ChanelType)i);
		}
		//===================push data to txData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[0];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+1] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[1];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+2] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[2];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+3] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[3];
		}
		pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = pContex->removeWeight_Slef;
		pContex->removeWeight_Slef = FALSE;

		pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+1] = pContex->dataValid;
		
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+4*i+2;
		//crc
	#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
	#endif
		//
		ret =TRUE;
	}
	else if((pContex->slaveTxMask & SlaveEvent_Tx_E6) != 0)
	{
		pContex->slaveTxMask &= (~SlaveEvent_Tx_E6);
		//
		pContex->txData[MODBUS_RTU_SEND_ADDRESS_POS] = gSystemPara.isCascade;
		switch(gSystemPara.isCascade)
		{
			case ModbusAdd_Slave_1:
				pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = ModbusAdd_Master;
				recive_add = 2;
			break;
			case ModbusFuncA_Slave:
				pContex->txData[MODBUS_RTU_ASK_ADDRESS_POS] = ModbusFuncA_Master ;
				recive_add = 2;
			break;
			default:
			break;
		}
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Slave_Ans_6;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MODBUS_RTU_SLAVE_DATA_LEN+1;
		//===================push data to MultWeightData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->MultWeightData[recive_add-ModbusAdd_Master][i].f_value = hx711_getWeight((enumHX711ChanelType)i);
		}
		//===================push data to txData.....
		for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
		{
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[0];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+1] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[1];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+2] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[2];
			pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+3] = pContex->MultWeightData[recive_add-ModbusAdd_Master][i].u_value[3];
		}
		pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+0] = pContex->removeWeight_Slef;
		pContex->removeWeight_Slef = FALSE;

		pContex->txData[MODBUS_RTU_DATA_STAR_POS+4*i+1] = pContex->dataValid;
		
		pContex->needSendLen = MODBUS_RTU_DATA_STAR_POS+4*i+2;
		//crc
#if(TRUE == MODBUS_RTU_CRC_EN)
			crc_data = cal_crc16(pContex->txData,(pContex->needSendLen));
			pContex->txData[pContex->needSendLen++] = (crc_data>>8)&0xff;
			pContex->txData[pContex->needSendLen++] = (crc_data>>0)&0xff;
#endif
		//
		ret =TRUE;
	}
	return ret;
}
//==slave tx main function
void ModbusRtu_SlaveTxMainFunction(ModbusRtuType *pContex)
{		
	//slaveState deal
	switch(pContex->slaveState)
	{
		//slave orderA and orderB need delay
		case SlaveState_Idle:
			pContex->slaveTxDiffTick++;
			if(pContex->slaveTxDiffTick >= SlaveTimer_TxOrderDlay)
			{
				pContex->slaveState = SlaveState_AllowTx;
			}
		break;
		case SlaveState_AllowTx :
			if(TRUE ==ModbusRtu_SlaveTxMaskDeal(pContex))
			{
				pContex->pUartDevice->tx_bytes(pContex->pUartDevice,pContex->txData,pContex->needSendLen);
				pContex->slaveState = SlaveState_Idle;
			}
		break;
		default:
			pContex->slaveState = SlaveState_Idle;
		break;
	}
}

//==master main function
void ModbusRtu_MasterMainFunction(ModbusRtuType *pContex)
{
	ModbusRtu_MasterTxMainFunction(pContex);
	if(TRUE == ModbusRtu_RxMainFunction(pContex))
	{
		if(pContex->rxDataUart[pContex->RxLength-3] == SLAVE_DATA_VALID)
		{
			ModbusRtu_MasterRxMainFunction(pContex);
		}
	}
}
//==slave main function
void ModbusRtu_SlaveMainFunction(ModbusRtuType *pContex)
{
	ModbusRtu_SlaveTxMainFunction(pContex);
	if(TRUE == ModbusRtu_RxMainFunction(pContex))
	{
		ModbusRtu_SlaveRxMainFunction(pContex);
	}
}
//==main function
void ModbusRtu_MainFunction(void)
{
	ModbusRtuType *pContex = &g_ModbusRtu;
	//
	pContex->sysTick++;
	//
#if 0//before 20211119
	if(0 != gSystemPara.isCascade)//not cascade , only one
	{
		if(ModbusAdd_Master == gSystemPara.isCascade)//cascade : master Device
		{
			ModbusRtu_MasterMainFunction(pContex);
		}else if ((gSystemPara.isCascade >= ModbusAdd_Slave_1) && (gSystemPara.isCascade < ModbusAdd_Slave_Max))////cascade : slave Device
		{
			ModbusRtu_SlaveMainFunction(pContex);
		}
	}
#else
	if(0 != gSystemPara.isCascade)//not cascade , only one
	{
		switch(gSystemPara.isCascade)
		{
			//master
			case ModbusAdd_Master:
			case ModbusFuncA_Master:
				ModbusRtu_MasterMainFunction(pContex);
			break;
			//slave
			case ModbusAdd_Slave_1:
			case ModbusFuncA_Slave:
				ModbusRtu_SlaveMainFunction(pContex);
			break;
			default:
			break;
		}
	}
#endif
}

