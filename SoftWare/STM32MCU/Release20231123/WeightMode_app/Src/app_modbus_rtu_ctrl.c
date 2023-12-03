/*******************************************************************************
 * Includes
 ******************************************************************************/
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

//modbus rx data check : finish flag and crc check
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
}

//==master tx mask handle
UINT8 ModbusRtu_MasterMaskHandle(ModbusRtuType *pContex)
{
	UINT16 ret =FALSE , star_pos = 0;
#if(TRUE == MODBUS_RTU_CRC_EN)
	UINT16 crc_data = 0 ;
#endif
	if((pContex->masterTxMask & MasterEvent_Tx_E6) != 0 )
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
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MFC_MASTER_SEND_DATA_TOTAL_LEN_NO_CRC;
		pContex->txData[MODBUS_RTU_DATA_STAR_POS] = MFC_Mater_Ask_6;
		//SetHelpDataToSlave(2*group*num)
		star_pos = MODBUS_RTU_DATA_STAR_POS + 1;
		readHelpDataFromSys(&pContex->txData[star_pos],DIFF_TO_DIWEN_DATA_LEN);

		//SendRemoveFlag
		star_pos += 2*DIFF_TO_DIWEN_DATA_LEN;
		pContex->txData[star_pos] = pContex->removeWeight_Slef;
		pContex->removeWeight_Slef = FALSE;

		//SendAllChnData(4*chn_num)
		star_pos += 1;
		readWeightDataFromSys(&pContex->txData[star_pos],T5L_MAX_CHANEL_LEN);

		//SendAllChnDataColor(2*chn_num)
		star_pos += 4*T5L_MAX_CHANEL_LEN;
		readColorDataFromSys(&pContex->txData[star_pos],T5L_MAX_CHANEL_LEN);

		//total len
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

//==master tx main function
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
			if(TRUE == ModbusRtu_MasterMaskHandle(pContex))
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

//==master rx main function
void ModbusRtu_MasterRxMainFunction(ModbusRtuType *pContex)
{
	UINT16 i = 0 , sender_add = 0 , recive_add = 0;
	//sender_ID , recv_ID
	sender_add = pContex->rxData[MODBUS_RTU_SEND_ADDRESS_POS];
	recive_add = pContex->rxData[MODBUS_RTU_ASK_ADDRESS_POS];
	//
	if(((sender_add >= ModbusAdd_Slave_1) && (sender_add < ModbusAdd_Slave_Max) ) || (sender_add == ModbusFuncA_Slave))
	{
		if(((ModbusAdd_Master == recive_add) && (ModbusAdd_Master == gSystemPara.isCascade)) || 
			((ModbusFuncA_Master == recive_add) && (ModbusFuncA_Master == gSystemPara.isCascade)))
		{
			if(sender_add == ModbusFuncA_Slave)
			{
				sender_add = 2;
			}
			switch(pContex->rxData[MODBUS_RTU_FUN_CODE_POS])
			{
				case MFC_Slave_Ans_6://master recv slave answer weight was flaot , remove flag
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == (MODBUS_RTU_SLAVE_DATA_LEN+1+1))
					{
						//recv data
						for(i=0;i<MODBUS_RTU_SLAVE_CHANEL_NUM;i++)
						{
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[0] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[1] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+1];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[2] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+2];
							pContex->MultWeightData[sender_add-ModbusAdd_Master][i].u_value[3] =  pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+3];
						}
						//slave remove key
						pContex->removeWeight_Other = pContex->rxData[MODBUS_RTU_DATA_STAR_POS+4*i+0];
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
	//judge sender
	if((ModbusAdd_Master == sender_add) || (ModbusFuncA_Master == sender_add))
	{
		//judge reciver : 
		if(((recive_add >= ModbusAdd_Slave_1) && (recive_add < ModbusAdd_Slave_Max) && (ModbusAdd_Master == sender_add)) ||
			((recive_add == gSystemPara.isCascade) && (ModbusFuncA_Master == sender_add)))
		{
			switch(pContex->rxData[MODBUS_RTU_FUN_CODE_POS])
			{
				case MFC_Mater_Ask_6:
					if(pContex->rxData[MODBUS_RTU_DATA_LEN_POS] == MFC_MASTER_SEND_DATA_TOTAL_LEN_NO_CRC)
					{
						if(pContex->rxData[MODBUS_RTU_DATA_STAR_POS] == MFC_Mater_Ask_6)
						{
							//rx data
							//SetHelpDataToSlave1(2*group*num)
							star_pos = MODBUS_RTU_DATA_STAR_POS+1;
							writeHelpDataFromCom(&pContex->rxData[star_pos],DIFF_TO_DIWEN_DATA_LEN);

							//SendRemoveFlag(1)
							star_pos += 2*DIFF_TO_DIWEN_DATA_LEN;
							pContex->removeWeight_Other = pContex->rxData[star_pos];

							//SendAllChnData(4*chn_num)
							star_pos += 1;
							writeWeightDataFromCom(&pContex->rxData[star_pos],T5L_MAX_CHANEL_LEN);

							//SendAllChnDataColor(2*chn_num)
							star_pos += 4*T5L_MAX_CHANEL_LEN;
							writeColorDataFromCom(&pContex->rxData[star_pos],T5L_MAX_CHANEL_LEN);

							//event mask
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

//==slave tx mask handle function
UINT8 ModbusRtu_SlaveTxMaskHandle(ModbusRtuType *pContex)
{
	UINT8 ret = 0 ;
	UINT16 i = 0 ,recive_add = 0;
#if(TRUE == MODBUS_RTU_CRC_EN)
		UINT16 crc_data = 0 ;
#endif
	if((pContex->slaveTxMask & SlaveEvent_Tx_E6) != 0)
	{
		//clear rx event
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
				//sender_ID , recv_ID
				recive_add = pContex->rxData[MODBUS_RTU_ASK_ADDRESS_POS];
			break;
		}
		pContex->txData[MODBUS_RTU_FUN_CODE_POS] = MFC_Slave_Ans_6;
		pContex->txData[MODBUS_RTU_DATA_LEN_POS] = MODBUS_RTU_SLAVE_DATA_LEN+1+1;
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
			if(TRUE ==ModbusRtu_SlaveTxMaskHandle(pContex))
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
}
