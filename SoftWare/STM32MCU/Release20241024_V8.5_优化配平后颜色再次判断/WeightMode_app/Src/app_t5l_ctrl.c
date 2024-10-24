/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app_main_task.h"
#include "app_sdwe_ctrl.h"
#include "app_crc.h"
#include "app_hx711_ctrl.h"
#include "app_crc.h"
#include "hal_delay.h"
#include "app_modbus_rtu_ctrl.h"
#include "app_syspara.h"
#include "app_t5l_ctrl.h"
#include "app_password.h"
#include "app_t5l_cfg.h"
#include "app_InnerScreen_Cfg.h"
#include "app_ExternalScreen_Cfg.h"

extern UINT8 appScreenCfgIndexGet(T5LType *pSdwe,UINT8 weight_help_index_color_orther);

/*******************************************************************************
 * Definitions
 ******************************************************************************/
T5LType g_T5LCtx[ScreenIndex_Max] = {T5LDataDefault,T5LDataDefault2};
ScreenHandleType g_ScreenHandle[ScreenIndex_Max] = {ScreenHandleDefault_Smaller,ScreenHandleDefault_Larger};

//1.chanel num :0~x HX711_CHANEL_NUM
//2.trigerStarus , back color , point avg Sample , point set weight
//3.point num
static INT16 g_t5l_triger_data[HX711_CHANEL_NUM+1][DMG_TRIGER_SAMPLE_MAX_NUM][CHANEL_POINT_NUM];

//voice printf buff
tT5LVoinceType g_T5L_VoiceBuff[T5L_VOICE_MAX_PRINTF_NUM][3];
UINT8 u8T5LVoiceBuffPush_i = 0 ,u8T5LVoiceBuffPop_i = 0 , u8T5LVoiceBuffStoreNum = 0;

//data send to DIWEN
INT32 g_i32DataBuff[T5L_MAX_CHANEL_LEN]={0};
INT32 g_i32DataBuffPre[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i32_i16DataBuff[2*T5L_MAX_CHANEL_LEN]={0};//cause STM32 was little mode : low address store low data but screen was not
//color send to DIWEN
INT16 g_i16ColorBuff[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i16ColorBuffPre[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i16ColorOtherChanel[T5L_MAX_CHANEL_LEN]={0};//T5L_WEIGHT_CHANEL_INVALID:invalid
//
float g_fDataBuffCaculate[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i16OtherChanelCaculate[T5L_MAX_CHANEL_LEN]={0};//other chanel need +1 , chanel = 1~x
//help data send to DIWEN
INT16 g_i16HelpDataBuff[DIFF_TO_DIWEN_DATA_LEN]={0};
INT16 g_i16HelpDataBuffPre[DIFF_TO_DIWEN_DATA_LEN]={0};

float g_i16HelpDataSort[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i16HelpDataChnSort[T5L_MAX_CHANEL_LEN]={0};


//=====================================================================================================================
//data send to DIWEN
INT32 g_i32DataBuffLarger[T5L_MAX_CHANEL_LEN]={0};
INT32 g_i32DataBuffPreLarger[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i32_i16DataBuffLarger[2*T5L_MAX_CHANEL_LEN]={0};//cause STM32 was little mode : low address store low data but screen was not
//color send to DIWEN
INT16 g_i16ColorBuffLarger[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i16ColorBuffPreLarger[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i16ColorOtherChanelLarger[T5L_MAX_CHANEL_LEN]={0};//T5L_WEIGHT_CHANEL_INVALID:invalid
//
float g_fDataBuffCaculateLarger[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i16OtherChanelCaculateLarger[T5L_MAX_CHANEL_LEN]={0};//other chanel need +1 , chanel = 1~x
//help data send to DIWEN
INT16 g_i16HelpDataBuffLarger[DIFF_TO_DIWEN_DATA_LEN]={0};
INT16 g_i16HelpDataBuffPreLarger[DIFF_TO_DIWEN_DATA_LEN]={0};

float g_i16HelpDataSortLarger[T5L_MAX_CHANEL_LEN]={0};
INT16 g_i16HelpDataChnSortLarger[T5L_MAX_CHANEL_LEN]={0};


//=====================================================================================================================

INT16 g_handleStatus[ScreenIndex_Max]={0};//发送重量和颜色给屏幕用的状态机
INT16 g_u16WeightHoldOn[ScreenIndex_Max]={0};//发送重量给屏幕后数据保持多久不表时再发送颜色
INT16 g_needSendHelp[ScreenIndex_Max]={0};
INT16 g_handle_i[ScreenIndex_Max]={0};
INT16 g_rmTrigerInnerSts[ScreenIndex_Max]={0};



//=============================================15.6寸屏的=============================================
//=============================================8.8寸屏的=============================================
//屏幕的描述指针：显示托盘的重量控件
//static INT16 describlePoint_add = 0x9000,*describlePoint_data,describlePoint_len = 1;


/*******************************************************************************
 * Functions
 ******************************************************************************/
//==sdwe->mcu rx callback ,not used
void app_uart_extern_msg_packet_process( UartDeviceType *pUartDevice )
{
	//not used
}

UINT8 screenPrivate_preColorDataAndJudgeIfNeedSend(INT32 *pData,INT16 *pColor,INT16 *pColorPre,INT16 *pColorOtherCh,UINT8 chanel_len);
void handleWeightColorWasSend(INT16 *pColor,INT16 *pColorPre ,UINT8 chanel_len);
UINT8 judgeWeightColorIfNotNeedSend(INT16 *pColor,INT16 *pColorPre ,UINT8 chanel_len);
void handleWeightDataWasSend(INT32 *pData , INT32 *pDataPre ,UINT8 chanel_len);
UINT8 judgeWeightDataIfNotNeedSend(INT32 *pData , INT32 *pDataPre ,UINT8 chanel_len);
void preColorData(INT32 *pData,INT16 *pColor,INT16 *pColorPre,INT16 *pColorOtherCh,UINT8 chanel_len);
UINT8 sdwe_VoicePrintfPop(tT5LVoinceType *u8Voice1 , tT5LVoinceType *u8Voice2 , tT5LVoinceType *u8Voice3);
void screenPublic_CurrentDevice_WeightDataPrepare(INT32 *pData,INT16 *pDataInt16);
void screenPublic_OtherDevice_WeightDataPrepare(INT32 *pData,INT16 *pDataInt16 ,enumModbusAddType modbusSlaveId);
void masterCaculateHelpData(ModbusRtuType *pContex,UINT8 chanel_len);
UINT8 sendHelpDataDiff(T5LType *pSdwe);



//=====================================================================================================================
//==================================================[ 屏幕处理公共函数 ：开始 ]==========================================
//=====================================================================================================================
//==write varible data to SDWE thought UART
void t5lWriteVarible(T5LType *t5lCtx,UINT16 varAdd, INT16 *pData ,UINT16 varlen ,UINT8 crcEn)
{
	//A5 5A 05 82 00 03 00 01:向0x0003地址写入数据0x0001
	UINT16 i = 0 ,l_data = 0 , total_len = 0 , crc = 0;
	if(((t5lCtx->LastSendTick > t5lCtx->CurTick)&&((t5lCtx->LastSendTick-t5lCtx->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((t5lCtx->LastSendTick < t5lCtx->CurTick)&&((t5lCtx->CurTick - t5lCtx->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		if(varAdd < 0xFFFF)
		{
			if(((varAdd+varlen)>0)&&((varAdd+varlen)<0xFFFF))
			{
				//head
				t5lCtx->txData[cmdPosHead1]=T5L_RX_FUN_HEAD1;
				t5lCtx->txData[cmdPosHead2]=T5L_RX_FUN_HEAD2;
				//data len
				t5lCtx->txData[cmdPosDataLen]=0X03+2*varlen;
				//order:write
				t5lCtx->txData[cmdPosCommand]=cmdWriteSWDEVariable;
				//varAdd
				t5lCtx->txData[cmdPosVarWriteAddress1]=0xff&(varAdd>>8);
				t5lCtx->txData[cmdPosVarWriteAddress2]=0xff&(varAdd>>0);
				//data
				for(i=0;i<varlen;i++)
				{
					l_data = *pData++;
					t5lCtx->txData[cmdPosVarWriteData+2*i+0] = 0xff&(l_data>>8);
					t5lCtx->txData[cmdPosVarWriteData+2*i+1] = 0xff&(l_data>>0);
				}
				//crc
				if(TRUE == crcEn)
				{
					crc = cal_crc16(&t5lCtx->txData[cmdPosCommand],(3+2*varlen));
					t5lCtx->txData[cmdPosVarWriteData+2*varlen+0] = 0xff&(crc>>8);
					t5lCtx->txData[cmdPosVarWriteData+2*varlen+1] = 0xff&(crc>>0);
					//total len
					total_len = cmdPosVarWriteData+2*varlen+2;
				}
				else
				{
					//total len
					total_len = cmdPosVarWriteData+2*varlen;
				}
				//send
				t5lCtx->pUartDevice->tx_bytes(t5lCtx->pUartDevice,&t5lCtx->txData[0],total_len);
				t5lCtx->LastSendTick = t5lCtx->CurTick;
				//
				#ifndef T5L_DMG_UART_TX_USE_DMA
					hal_delay_ms(1);
				#endif
			}
		}
	}
}

//==read varible data to SDWE thought UART
void t5lReadVarible(T5LType *t5lCtx,UINT16 varAdd,UINT16 varlen ,UINT8 crcEn)
{
	//A5 5A 04 83 00 A1 01:读系统变量0x00A1长度为1
	UINT16 total_len = 0 , crc = 0;
	if(((t5lCtx->LastSendTick > t5lCtx->CurTick)&&((t5lCtx->LastSendTick-t5lCtx->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((t5lCtx->LastSendTick < t5lCtx->CurTick)&&((t5lCtx->CurTick - t5lCtx->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		if(varAdd < 0xFFFF)
		{
			if(((varAdd+varlen)>0)&&((varAdd+varlen)<0xFFFF))
			{
				//head
				t5lCtx->txData[cmdPosHead1]=T5L_RX_FUN_HEAD1;
				t5lCtx->txData[cmdPosHead2]=T5L_RX_FUN_HEAD2;
				//data len
				t5lCtx->txData[cmdPosDataLen]=0X04;
				//order:write
				t5lCtx->txData[cmdPosCommand]=cmdReadSWDEVariable;
				//varAdd
				t5lCtx->txData[cmdPosVarWriteAddress1]=0xff&(varAdd>>8);
				t5lCtx->txData[cmdPosVarWriteAddress2]=0xff&(varAdd>>0);
				//len
				t5lCtx->txData[cmdPosVarReadLen]=varlen&0xff;
				//crc
				if(TRUE == crcEn)
				{
					crc = cal_crc16(&t5lCtx->txData[cmdPosCommand],4);
					t5lCtx->txData[cmdPosVarReadLen+1+0] = 0xff&(crc>>8);
					t5lCtx->txData[cmdPosVarReadLen+1+1] = 0xff&(crc>>0);
					//total len
					total_len = cmdPosVarReadLen+1+2;
				}
				else
				{
					//total len
					total_len = cmdPosVarReadLen+1;
				}
				//send
				t5lCtx->pUartDevice->tx_bytes(t5lCtx->pUartDevice,&t5lCtx->txData[0],total_len);
				t5lCtx->LastSendTick = t5lCtx->CurTick;
				//
				#ifndef T5L_DMG_UART_TX_USE_DMA
					hal_delay_ms(1);
				#endif
			}
		}
	}
}

//==write background to screen , have delay contrl
UINT8 t5lWriteDataColor(T5LType *t5lCtx,UINT16 varAdd, UINT16 ColorOrder1,UINT16 ColorOrder2,INT16 *pData_X_Y_X_Y_Color)
{
/*

5A A5 27 82 5440 0003 0003 011E 012C 01AA 018C F800 01AB 018D 01E6 01E6 F800 01E6 01E6 0162 022C F800 
FF00 

含义：0x5A A5帧头；0x27数据长度；0x82写指令；0x5440变量地址； 

0x 0003:画矩形； 

0x 0003:画三个矩形； 

0x 011E 012C:（286，300）左上坐标； 

0x 01AA 018C:（426,96）右下坐标；0x F800颜色； 

0x 01AB 018D:（426,96）左上坐标； 

0x 01E6 01E6:（486,486）右上坐标；0x F800颜色； 

0x 01E6 01E6:（486,486）左上坐标； 

0x 0162 022C:（354,556）右下坐标；0xF800颜色；
*/
	UINT8 ret = FALSE;
	//A5 5A 05 82 00 03 00 01:向0x0003地址写入数据0x0001	
	UINT16 i = 0 ,l_data = 0 , total_len = 0;
	if(((t5lCtx->LastSendTick > t5lCtx->CurTick)&&((t5lCtx->LastSendTick-t5lCtx->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((t5lCtx->LastSendTick < t5lCtx->CurTick)&&((t5lCtx->CurTick - t5lCtx->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		//head
		t5lCtx->txData[cmdPosHead1]=T5L_RX_FUN_HEAD1;
		t5lCtx->txData[cmdPosHead2]=T5L_RX_FUN_HEAD2;
		//order:write
		t5lCtx->txData[cmdPosCommand]=cmdWriteSWDEVariable;
		//varAdd color
		t5lCtx->txData[cmdPosVarWriteAddress1color]=0xff&(varAdd>>8);
		t5lCtx->txData[cmdPosVarWriteAddress2color]=0xff&(varAdd>>0);
		//color order1
		t5lCtx->txData[cmdPosVarWriteColorOrder1color]=0xff&(ColorOrder1>>8);
		t5lCtx->txData[cmdPosVarWriteColorOrder2color]=0xff&(ColorOrder1>>0);
		//color order2
		t5lCtx->txData[cmdPosVarWriteColorOrder3color]=0xff&(ColorOrder2>>8);
		t5lCtx->txData[cmdPosVarWriteColorOrder4color]=0xff&(ColorOrder2>>0);

		//data
		for(i=0;i<ColorOrder2;i++)
		{
			//左上坐标
			l_data = pData_X_Y_X_Y_Color[5*i+0];//X(2byte)
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+0] = 0xff&(l_data>>8);
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+1] = 0xff&(l_data>>0);
			l_data = pData_X_Y_X_Y_Color[5*i+1];//Y(2byte)
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+2] = 0xff&(l_data>>8);
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+3] = 0xff&(l_data>>0);
			//右下坐标
			l_data = pData_X_Y_X_Y_Color[5*i+2];//X(2byte)
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+4] = 0xff&(l_data>>8);
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+5] = 0xff&(l_data>>0);
			l_data = pData_X_Y_X_Y_Color[5*i+3];//Y(2byte)
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+6] = 0xff&(l_data>>8);
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+7] = 0xff&(l_data>>0);
			//矩形颜色
			l_data = pData_X_Y_X_Y_Color[5*i+4];//Color(2byte)
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+8] = 0xff&(l_data>>8);
			t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+9] = 0xff&(l_data>>0);
		}
		//结束符号
		t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+0] = 0XFF;
		t5lCtx->txData[cmdPosVarWriteColorXPos+10*i+1] = 0X00;

		//总长度
		total_len = (cmdPosVarWriteColorXPos+10*i+1) + 1;

		//有效长度
		t5lCtx->txData[cmdPosDataLen] = total_len - 3;

		//send
		t5lCtx->pUartDevice->tx_bytes(t5lCtx->pUartDevice,&t5lCtx->txData[0],total_len);
		t5lCtx->LastSendTick = t5lCtx->CurTick;
		//
		ret = TRUE;
	}
	return ret;
}

//==write data to screen , have delay contrl
UINT8 t5lWriteData(T5LType *t5lCtx,UINT16 varAdd, INT16 *pData ,UINT16 varlen ,UINT8 crcEn)
{
	UINT8 ret = FALSE;
	//A5 5A 05 82 00 03 00 01:向0x0003地址写入数据0x0001	
	UINT16 i = 0 ,l_data = 0 , total_len = 0 , crc = 0;
	if(((t5lCtx->LastSendTick > t5lCtx->CurTick)&&((t5lCtx->LastSendTick-t5lCtx->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((t5lCtx->LastSendTick < t5lCtx->CurTick)&&((t5lCtx->CurTick - t5lCtx->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		if(varAdd < 0xFFFF)
		{
			if(((varAdd+varlen)>0)&&((varAdd+varlen)<0xFFFF))
			{
				//head
				t5lCtx->txData[cmdPosHead1]=T5L_RX_FUN_HEAD1;
				t5lCtx->txData[cmdPosHead2]=T5L_RX_FUN_HEAD2;
				//data len
				t5lCtx->txData[cmdPosDataLen]=0X03+2*varlen;
				//order:write
				t5lCtx->txData[cmdPosCommand]=cmdWriteSWDEVariable;
				//varAdd
				t5lCtx->txData[cmdPosVarWriteAddress1]=0xff&(varAdd>>8);
				t5lCtx->txData[cmdPosVarWriteAddress2]=0xff&(varAdd>>0);
				//data
				for(i=0;i<varlen;i++)
				{
					l_data = pData[i];
					t5lCtx->txData[cmdPosVarWriteData+2*i+0] = 0xff&(l_data>>8);
					t5lCtx->txData[cmdPosVarWriteData+2*i+1] = 0xff&(l_data>>0);
				}
				//crc
				if(TRUE == crcEn)
				{
					crc = cal_crc16(&t5lCtx->txData[cmdPosCommand],(3+2*varlen));
					t5lCtx->txData[cmdPosVarWriteData+2*varlen+0] = 0xff&(crc>>8);
					t5lCtx->txData[cmdPosVarWriteData+2*varlen+1] = 0xff&(crc>>0);
					//total len
					total_len = cmdPosVarWriteData+2*varlen+2;
				}
				else
				{
					//total len
					total_len = cmdPosVarWriteData+2*varlen;
				}
				//send
				t5lCtx->pUartDevice->tx_bytes(t5lCtx->pUartDevice,&t5lCtx->txData[0],total_len);
				t5lCtx->LastSendTick = t5lCtx->CurTick;
				//
				ret = TRUE;
			}
		}
	}
	return ret;
}

//屏幕相关变量初始化
static void screenPrivate_Init(T5LType *t5lCtx)
{
	UINT8 i = 0;
	//
	t5lCtx->readSdweInit = FALSE;
	//externnal screen
	if(t5lCtx == &g_T5LCtx[ScreenIndex_Larger])
	{
		//data handle send to screen
		t5lCtx->screenCycle.pData = &g_i32DataBuffLarger[0];
		t5lCtx->screenCycle.pDataPre = &g_i32DataBuffPreLarger[0];
		t5lCtx->screenCycle.pDataSendToDiWen = &g_i32_i16DataBuffLarger[0];
		//color handle send to screen
		t5lCtx->screenCycle.pColor = &g_i16ColorBuffLarger[0];
		t5lCtx->screenCycle.pColorPre = &g_i16ColorBuffPreLarger[0];
		t5lCtx->screenCycle.pColorOtherCh = &g_i16ColorOtherChanelLarger[0];
		//help handle send to screen
		t5lCtx->screenCycle.pSortWeight = &g_fDataBuffCaculateLarger[0];
		t5lCtx->screenCycle.pSortArry = &g_i16OtherChanelCaculateLarger[0];
		t5lCtx->screenCycle.pHelp = &g_i16HelpDataBuffLarger[0];
		t5lCtx->screenCycle.pHelpPre = &g_i16HelpDataBuffPreLarger[0];

		t5lCtx->screenCycle.handleStatus = &g_handleStatus[ScreenIndex_Larger];
		t5lCtx->screenCycle.weightHoldOn = &g_u16WeightHoldOn[ScreenIndex_Larger];
		t5lCtx->screenCycle.needSendHelp = &g_needSendHelp[ScreenIndex_Larger];
		t5lCtx->screenCycle.handle_i  = &g_handle_i[ScreenIndex_Larger];
		t5lCtx->screenCycle.rmTrigerInnerSts = &g_rmTrigerInnerSts[ScreenIndex_Larger];



		//t5lCtx->sdweJumpBalancingMainPage = TRUE;
		t5lCtx->sdweChangeDescriblePoint = TRUE;
	}
	else
	{
		//data handle send to screen
		t5lCtx->screenCycle.pData = &g_i32DataBuff[0];
		t5lCtx->screenCycle.pDataPre = &g_i32DataBuffPre[0];
		t5lCtx->screenCycle.pDataSendToDiWen = &g_i32_i16DataBuff[0];
		//color handle send to screen
		t5lCtx->screenCycle.pColor = &g_i16ColorBuff[0];
		t5lCtx->screenCycle.pColorPre = &g_i16ColorBuffPre[0];
		t5lCtx->screenCycle.pColorOtherCh = &g_i16ColorOtherChanel[0];
		//help handle send to screen
		t5lCtx->screenCycle.pSortWeight = &g_fDataBuffCaculate[0];
		t5lCtx->screenCycle.pSortArry = &g_i16OtherChanelCaculate[0];
		t5lCtx->screenCycle.pHelp = &g_i16HelpDataBuff[0];
		t5lCtx->screenCycle.pHelpPre = &g_i16HelpDataBuffPre[0];

		t5lCtx->screenCycle.handleStatus = &g_handleStatus[ScreenIndex_Smaller];
		t5lCtx->screenCycle.weightHoldOn = &g_u16WeightHoldOn[ScreenIndex_Smaller];
		t5lCtx->screenCycle.needSendHelp = &g_needSendHelp[ScreenIndex_Smaller];
		t5lCtx->screenCycle.handle_i  = &g_handle_i[ScreenIndex_Smaller];
		t5lCtx->screenCycle.rmTrigerInnerSts = &g_rmTrigerInnerSts[ScreenIndex_Smaller];


		//t5lCtx->sdweJumpBalancingMainPage = TRUE;
		t5lCtx->sdweChangeDescriblePoint = TRUE;

	}

	//t5lCtx->pUartDevice = &g_UartDevice[t5lCtx->uartIndex];
	t5lCtx->version = 0;//SDWE version
	//
	t5lCtx->pUartDevice->pRxLength = &t5lCtx->RxLength;
	t5lCtx->pUartDevice->pRxFinishFlag = &t5lCtx->RxFinishFlag;
	t5lCtx->pUartDevice->pTxBuffer = &t5lCtx->rxData[0];
	t5lCtx->pUartDevice->pRxBuffer = &t5lCtx->rxData[0];
	//
	t5lCtx->RxLength = 0;			/**< 接收字节数 */
	t5lCtx->RxFinishFlag = FALSE;	/**< 接收完成标志 */
	//
	t5lCtx->SetAdd = 0XFFFF;	/**< 地址 */
	t5lCtx->DataLen = 0;		/**< 数据长度 */
	t5lCtx->SetData = 0;		/**< 数据 */
	//
	t5lCtx->ColorClen=FALSE;		/**< 通道切换SDWE颜色清除 */
	t5lCtx->CalibrateChanel=88;	/**< 通道 */
	t5lCtx->CalibratePoint=0;		/**< 校准点 */
	//
	t5lCtx->ResetTrigerValid = FALSE;
	//
	for(i=0;i<CHANEL_POINT_NUM;i++)
	{
		t5lCtx->CalibratePointArry[i] = defaultChanelSamplePoint[i];/**< 校准点数组 */
	}
	for(i=0;i<T5L_MAX_CHANEL_LEN;i++)
	{
		g_i16ColorOtherChanel[i]=T5L_CHANEL_WEIGHT_NOT_EQUAL;
	}
	//
	t5lCtx->pUartDevice->init(t5lCtx->pUartDevice);
}

//所有屏幕（内屏+外屏）初始化
void screenPublic_Init(void)
{
	screenPrivate_Init(&g_T5LCtx[ScreenIndex_Smaller]);
	screenPrivate_Init(&g_T5LCtx[ScreenIndex_Larger]);
}

//公共函数：获取屏幕的软件版本号
void screenPublic_ScreenVersionGet(T5LType *pSdwe)
{
	t5lReadVarible(pSdwe,DMG_SYS_VERSION_GET_ADD,1,0);//get version
}

//公共函数：获取屏幕的当前页面序号
void screenPublic_CurPageGet(T5LType *pSdwe)
{
	t5lReadVarible(pSdwe,DMG_SYS_CUR_PAGE_GET_ADD,1,0);//get cur page
}

//公共函数：屏幕亮度控制 
UINT8 screenPublic_ScreenLight(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 05 82 0082 5A01 page 0XEA60
	INT16 pageChangeOrderAndData[2]={0x6423,0XEA60};//0x64:black light ,0x23:standby light ,entry standby x*0.01S
	pageChangeOrderAndData[0] &= 0x00ff;
	pageChangeOrderAndData[0] |= (0xff00&(gSystemPara.ScreenLight<<8));
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0082),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}

//公共函数：跳转至 xxx 页面 
UINT8 screenPublic_PageJump(T5LType *pSdwe,INT16 pageNum)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,53};//53 page
	pageChangeOrderAndData[1] = pageNum;
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}

//公共函数：修改‘托盘重量’的描述指针
UINT8 screenPublic_FreshDisplayPosition_Of_WeightVlu(T5LType *pSdwe)
{
	INT16 total_handle = 0;
	UINT8 ret = FALSE;
	UINT8 index;
	INT16 describlePoint_add = 0x9000,*describlePoint_data,describlePoint_len = 1;
	//
	index=appScreenCfgIndexGet(pSdwe,0);
	total_handle = pSdwe->screenCfg[index].weightVluNum;
	describlePoint_add = pSdwe->screenCfg[index].dpParaAdd_WeightVlu[(*pSdwe->screenCycle.handle_i)%total_handle];
	describlePoint_len = 6;
	describlePoint_data = &pSdwe->screenCfg[index].dpParaVlu_WeightVlu_WXS[(*pSdwe->screenCycle.handle_i)%total_handle].positionX;
	if(0 != gSystemPara.xiaoShuXianShi)//带小数
	{
		describlePoint_data = &pSdwe->screenCfg[index].dpParaVlu_WeightVlu_YXS[(*pSdwe->screenCycle.handle_i)%total_handle].positionX;
	}
	//发送数据给屏幕
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		(*pSdwe->screenCycle.handle_i)++;
	}
	//操作数量达到总数量 清零 并处理成功
	if((*pSdwe->screenCycle.handle_i) >= total_handle)
	{
		(*pSdwe->screenCycle.handle_i) = 0 ;
		ret = TRUE;
	}		
	//返回结果
	return ret;
}

//公共函数：修改‘帮组信息’的描述指针
UINT8 screenPublic_FreshDisplayPosition_Of_HelpVlu(T5LType *pSdwe)
{
	INT16 total_handle = 0;
	UINT8 ret = FALSE;
	UINT8 index;
	INT16 describlePoint_add = 0x9000,*describlePoint_data,describlePoint_len = 1;
	//
	index=appScreenCfgIndexGet(pSdwe,1);
	total_handle = pSdwe->screenCfg[index].helpVluNum;
	describlePoint_add = pSdwe->screenCfg[index].dpParaAdd_HelpVlu[(*pSdwe->screenCycle.handle_i)%total_handle];
	describlePoint_len = 6;//这里发送：X Y ....等的6个属性
	describlePoint_data = &pSdwe->screenCfg[index].dpParaVlu_HelpVlu_WXS[(*pSdwe->screenCycle.handle_i)%total_handle].positionX;
	if(0 != gSystemPara.xiaoShuXianShi)//带小数
	{
		describlePoint_data = &pSdwe->screenCfg[index].dpParaVlu_HelpVlu_YXS[(*pSdwe->screenCycle.handle_i)%total_handle].positionX;
	}
	//发送数据给屏幕
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		(*pSdwe->screenCycle.handle_i)++;
	}
	//操作数量达到总数量 清零 并处理成功
	if((*pSdwe->screenCycle.handle_i) >= total_handle)
	{
		(*pSdwe->screenCycle.handle_i) = 0 ;
		ret = TRUE;
	}		
	//返回结果
	return ret;
}	

//公共函数：显示托盘序号（当是否显示小数参数修改时和上电初始化时执行）
UINT8 screenPublic_FreshDisplayPosition_Of_WeightIndex(T5LType *pSdwe)
{
	INT16 total_handle = 0;
	UINT8 ret = FALSE;
	UINT8 index;
	INT16 describlePoint_add = 0x9000,*describlePoint_data,describlePoint_len = 1;
	//
	index=appScreenCfgIndexGet(pSdwe,2);
	total_handle = pSdwe->screenCfg[index].weightIndexNum;
	describlePoint_add = pSdwe->screenCfg[index].dpParaAdd_WeightIndex[(*pSdwe->screenCycle.handle_i)%total_handle];
	describlePoint_len = 6;
	describlePoint_data = &pSdwe->screenCfg[index].dpParaVlu_WeightIndex[(*pSdwe->screenCycle.handle_i)%total_handle].positionX;
	//发送数据给屏幕
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		(*pSdwe->screenCycle.handle_i)++;
	}
	//操作数量达到总数量 清零 并处理成功
	if((*pSdwe->screenCycle.handle_i) >= total_handle)
	{
		(*pSdwe->screenCycle.handle_i) = 0 ;
		ret = TRUE;
	}		
	//返回结果
	return ret;
}

//公共函数：修改‘托盘背景色’的描述指针
UINT8 screenPublic_FreshDisplayPosition_Of_WeightColor(T5LType *pSdwe)
{
	INT16 total_handle = 0;
	UINT8 ret = FALSE;
	UINT8 index;
	INT16 describlePoint_add = 0x9000,*describlePoint_data,describlePoint_len = 1;
	//
	index=appScreenCfgIndexGet(pSdwe,3);
	total_handle = pSdwe->screenCfg[index].weightColorNum;
	describlePoint_add = pSdwe->screenCfg[index].dpParaAdd_WeightColor[(*pSdwe->screenCycle.handle_i)%total_handle];
	describlePoint_len = 2;//这里发送：X Y 的 2个属性
	describlePoint_data = &pSdwe->screenCfg[index].dpParaVlu_WeightColor[(*pSdwe->screenCycle.handle_i)%total_handle].positionX;
	//发送数据给屏幕
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		(*pSdwe->screenCycle.handle_i)++;
	}
	//操作数量达到总数量 清零 并处理成功
	if((*pSdwe->screenCycle.handle_i) >= total_handle)
	{
		(*pSdwe->screenCycle.handle_i) = 0 ;
		ret = TRUE;
	}		
	//返回结果
	return ret;
}

//公共函数：修改‘托盘背景色’的描述指针
UINT8 screenPublic_FreshDisplayPosition_Of_OtherMisc(T5LType *pSdwe)
{
	INT16 total_handle = 0;
	UINT8 ret = FALSE;
	UINT8 index;
	INT16 describlePoint_add = 0x9000,*describlePoint_data,describlePoint_len = 1;
	//
	index=appScreenCfgIndexGet(pSdwe,4);
	total_handle = pSdwe->screenCfg[index].miscNum;
	describlePoint_add = pSdwe->screenCfg[index].dpParaAdd_Misc[(*pSdwe->screenCycle.handle_i)%total_handle];
	describlePoint_len = 2;//这里发送：X Y 的 2个属性
	describlePoint_data = &pSdwe->screenCfg[index].dpParaVlu_Misc[(*pSdwe->screenCycle.handle_i)%total_handle].positionX;
	//发送数据给屏幕
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		(*pSdwe->screenCycle.handle_i)++;
	}
	//操作数量达到总数量 清零 并处理成功
	if((*pSdwe->screenCycle.handle_i) >= total_handle)
	{
		(*pSdwe->screenCycle.handle_i) = 0 ;
		ret = TRUE;
	}		
	//返回结果
	return ret;
}


//私有函数：校准时 通道号 改变后的处理
UINT8 screenPrivate_ChanelChangedTrigerHandle(T5LType *pSdwe)
{
	static UINT8 inerStatus = 0 , localChanel = 0 ;	

	INT16 *pSendData= 0 ;
	UINT8 result = 0 ;
	
	if(pSdwe->CalibrateChanel > HX711_CHANEL_NUM)
		return 0 ;

	//chanel get
	if(0 == pSdwe->CalibrateChanel)
	{
		localChanel = HX711_CHANEL_NUM ;
	}
	else if(pSdwe->CalibrateChanel <= HX711_CHANEL_NUM)
	{
		localChanel = pSdwe->CalibrateChanel - 1 ;
	}
	
	//status
	switch(inerStatus)
	{
		case 0://send back Color
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				pSendData= &g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_ASK_COLOR][0];//color:1 green 0:white
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_POINT_TRIG_BACK_COLOR_ADDRESS,pSendData,(CHANEL_POINT_NUM),0);
				//
				inerStatus++ ;
			}
		break;
		case 1://send avg sample data
			{
				if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
					((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
				{
					pSendData= &g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_AVG_SAMPLE][0];//avg sample data
					t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_POINT_TRIG_SAMPLE_DATA_ADDRESS,pSendData,(CHANEL_POINT_NUM),0);
					//
					inerStatus++ ;
				}
			}
			break;
		case 2://send weight point
			{
				if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
					((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
				{
					pSendData= &g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_ASK_WEIGHT][0];//weight point data
					t5lWriteVarible(pSdwe,DMG_FUNC_SET_CHANEL_POINT_ADDRESS,pSendData,(CHANEL_POINT_NUM),0);
					//
					inerStatus++ ;
				}
			}
			break;
		case 3://send chanel
			{
				if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
					((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
				{

					pSendData = (INT16 *)&(pSdwe->CalibrateChanel);		
					t5lWriteVarible(pSdwe,DMG_FUNC_SET_CHANEL_NUM,pSendData,1,0);
					//
					inerStatus++ ;
				}
			}
			break;
		default:
			inerStatus = 0 ;
			result = 1 ;
			break;
	}

	return result;

}

//公共函数：校准时 通道号 改变后的处理
UINT8 screenPublic_ChanelChangedTrigerHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweChanelChanged)
	{
		matched = TRUE;
		if(0 != screenPrivate_ChanelChangedTrigerHandle(pSdwe))
		{
			pSdwe->sdweChanelChanged = FALSE;
		}
	}
	return matched;
}

//私有函数：校准时 重置校准 处理
UINT8 screenPrivate_ResetCalibrationTrigerHandle(T5LType *pSdwe)
{
	static UINT8 inerStatus = 0 , localChanel = 0 ;	

	INT16 *pSendData= 0;
	UINT8 result = 0 ;

	if(pSdwe->CalibrateChanel > HX711_CHANEL_NUM)
		return 0 ;

	//chanel get
	if(0 == pSdwe->CalibrateChanel)
	{
		localChanel = 0 ;
	}
	else if(pSdwe->CalibrateChanel <= HX711_CHANEL_NUM)
	{
		localChanel = pSdwe->CalibrateChanel ;
	}
	//status
	switch(inerStatus)
	{
		case 0://send Color
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				pSendData= &g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_ASK_COLOR][0];//color:1 green 0:white
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_POINT_TRIG_BACK_COLOR_ADDRESS,pSendData,(CHANEL_POINT_NUM),0);
				//
				inerStatus++ ;
			}
		break;
		case 1://send data
			{
				if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
					((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
				{
					pSendData= &g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_AVG_SAMPLE][0];//data
					t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_POINT_TRIG_SAMPLE_DATA_ADDRESS,pSendData,(CHANEL_POINT_NUM),0);
					//
					inerStatus++ ;
				}
			}
			break;
		default:
			inerStatus = 0 ;
			result = 1 ;
			break;
	}

	return result;
}

//公共函数：校准时 重置校准 处理
UINT8 screenPublic_ResetCalibrationTrigerHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweResetTriger)
	{
		matched = TRUE;
		if(0 != screenPrivate_ResetCalibrationTrigerHandle(pSdwe))
		{
			pSdwe->sdweResetTriger = FALSE;
		}
	}
	return matched;
}

//私有函数：校准时 单点触发 处理
UINT8 screenPrivate_PointTrigerHandle(T5LType *pSdwe)
{
	static UINT8 inerStatus = 0 , localChanel = 0 ;	
	INT16 *pSendData= 0;
	UINT8 result = 0 ;

	if(pSdwe->CalibrateChanel > HX711_CHANEL_NUM)
		return 0 ;

	//chanel get
	if(0 == pSdwe->CalibrateChanel)
	{
		localChanel = HX711_CHANEL_NUM ;
	}
	else if(pSdwe->CalibrateChanel <= HX711_CHANEL_NUM)
	{
		localChanel = pSdwe->CalibrateChanel - 1 ;
	}

	//status
	switch(inerStatus)
	{
		case 0://send Color
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				pSendData= &g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_ASK_COLOR][0];//color:1 green 0:white
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_POINT_TRIG_BACK_COLOR_ADDRESS,pSendData,(CHANEL_POINT_NUM),0);
				//
				inerStatus++ ;
			}
		break;
		case 1://send sample data
			{
				if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
					((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
				{
					pSendData= &g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_AVG_SAMPLE][0];//data
					t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_POINT_TRIG_SAMPLE_DATA_ADDRESS,pSendData,(CHANEL_POINT_NUM),0);
					//
					inerStatus++ ;
				}
			}
			break;
		default:
			inerStatus = 0 ;
			result = 1 ;
			break;
	}

	return result;
}

//公共函数：校准时 单点触发 处理
UINT8 screenPublic_PointTrigerHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdwePointTriger)
	{
		matched = TRUE;
		if(0 != screenPrivate_PointTrigerHandle(pSdwe))
		{
			pSdwe->sdwePointTriger = FALSE;
		}
	}
	return matched;
}

//公共函数：清除重量 颜色 帮组等相关值
void t5lDisPlayDataClear(void)
{
	UINT8 i = 0 ;
	for(i=0;i<T5L_MAX_CHANEL_LEN;i++)
	{
		g_i32DataBuff[i] = 0 ;
		g_i32_i16DataBuff[2*i + 0] = 0 ;
		g_i32_i16DataBuff[2*i + 1] = 0 ;
		g_i32DataBuffPre[i] = 0xffff ;
		g_i16ColorBuff[i] = 0 ;
		g_i16ColorBuffPre[i] = 0xff;
		g_i16ColorOtherChanel[i] = T5L_CHANEL_WEIGHT_NOT_EQUAL;
		
		g_fDataBuffCaculate[i] = 0.0f;
		g_i16HelpDataSort[i] = 0.0f;
		g_i16HelpDataChnSort[i] = 0;
	}
}

//私有函数：去皮 处理
UINT8 screenPrivate_RemoveWeightTrigerHandle(T5LType *pSdwe)
{
	INT16 *pSendData = &g_i16ColorBuff[0];
	INT16 *pDataSendToDiWen = &g_i32_i16DataBuff[0];

	UINT8 result = 0 ;

	switch((*pSdwe->screenCycle.rmTrigerInnerSts))
	{
		case 0://==send weight vlu to Screen
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				pDataSendToDiWen = &g_i32_i16DataBuff[0];
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pDataSendToDiWen,(2*T5L_MAX_CHANEL_LEN),0);
				//
				(*pSdwe->screenCycle.rmTrigerInnerSts)=1;
			}
		break;
		case 1://==send color vlu to Screen
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				pSendData = &g_i16ColorBuff[0];
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pSendData,T5L_MAX_CHANEL_LEN,0);
				//
				(*pSdwe->screenCycle.rmTrigerInnerSts)=2;
			}
		break;
		default:
			(*pSdwe->screenCycle.rmTrigerInnerSts) = 0 ;
			result = TRUE;
		break;
	}
	return result;
}

//公共函数：去皮 处理
UINT8 screenPublic_RemoveWeightTrigerHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if((TRUE == pSdwe->sdweRemoveWeightTriger)||(TRUE == getModbusOtherRemoveFlag()))
	{
		matched = TRUE;
		hx711_setAllRemoveWeight();
		t5lDisPlayDataClear();
		if(0 != screenPrivate_RemoveWeightTrigerHandle(pSdwe))
		{
			pSdwe->sdweRemoveWeightTriger = FALSE;
			//
			setModbusOtherRemoveFlag(FALSE);
		}
	}
	return matched;
}

//公共函数：写序号事件触发
UINT8 screenPublic_WriteIndexHandle(T5LType *pSdwe)
{
	UINT8 ret = 0 ;
	INT16 sendData[64],len=0;
	//
	switch(gSystemPara.isCascade)
	{
		case 0:
		case ModbusAdd_Master:
			for(len = 0 ; len < 2*HX711_CHANEL_NUM ; len++)
			{
				sendData[len] = len;
			}					
		break;
		case ModbusAdd_Slave_1:
			for(len = 0 ; len < HX711_CHANEL_NUM ; len++)
			{
				sendData[len] = HX711_CHANEL_NUM + len;
			}
		break;
		default:
			for(len = 0 ; len < HX711_CHANEL_NUM ; len++)
			{
				sendData[len] = len;
			}
		break;
	}
	//
	ret = t5lWriteData(pSdwe,(0x3901),sendData,len,0);
	return ret;
}

//私有函数：准备 重量 判断是否需要发送给屏幕
UINT8 screenPrivate_preWeightDataAndJudgeIfNeedSend(INT32 *pData,INT16 *pDataInt16, INT32 *pDataPre,UINT8 chanel_len)
{
	UINT8 ret = FALSE,i=0;
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		//external screen use inner screen : weight data
		if(pData == &g_i32DataBuffLarger[0])
		{
			for(i=0;i<T5L_MAX_CHANEL_LEN;i++)
			{
				pData[i] = g_i32DataBuff[i];
				pDataInt16[2*i+0] = g_i32_i16DataBuff[2*i+0];
				pDataInt16[2*i+1] = g_i32_i16DataBuff[2*i+1];
			}
		}
		else
		{
			switch(gSystemPara.isCascade)
			{
				//单台，不级联，直接获取hx711采样值并计算
				case 0:
					//master local data
					screenPublic_CurrentDevice_WeightDataPrepare(pData,pDataInt16);
				break;

				//多台，级联，主机端：先获取本机hx711采样值，在获取从机发过来的hx711采样值
				case ModbusAdd_Master:
					//ModbusAdd_Slave_1 recv data
					screenPublic_CurrentDevice_WeightDataPrepare(pData,pDataInt16);
					screenPublic_OtherDevice_WeightDataPrepare(pData,pDataInt16,ModbusAdd_Slave_1);
				break;

				//多台，级联，从机端：直接从主机发过来的数据截取
				case ModbusAdd_Slave_1:
					//直接使用总线的数据，这里不需要更新，他的更新在总线侧
				break;

				default :
				break;
			}
		}
		//judge if not need send
		ret = judgeWeightDataIfNotNeedSend(pData,pDataPre,chanel_len);			
	}
	//
	return ret;
}

//私有函数：准备 颜色 判断是否需要发送给屏幕
UINT8 screenPrivate_preColorDataAndJudgeIfNeedSend(INT32 *pData,INT16 *pColor,INT16 *pColorPre,INT16 *pColorOtherCh,UINT8 chanel_len)
{
	UINT8 ret = FALSE ,i=0;
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		if(pColor == g_i16ColorBuffLarger)
		{
			for(i=0;i<T5L_MAX_CHANEL_LEN;i++)
			{
				pColor[i] = g_i16ColorBuff[i];
			}
		}
		else
		{
			//1.更新颜色数据
			switch(gSystemPara.isCascade)
			{
				//单台，不级联，直接拿hx711采样值来计算颜色
				case 0:
				//多台，级联，主机端：数据在之前的步骤已经完成，这里只需要计算即可
				case ModbusAdd_Master:
					preColorData(pData,pColor,pColorPre,pColorOtherCh,chanel_len);
				break;

				//多台，级联，从机端：直接从主机发过来的数据截取
				case ModbusAdd_Slave_1:
					//直接使用总线的color数据，这里不需要更新，他的更新在总线侧
				break;

				default :
				break;
			}
		}
		//2.updata pColorPre from pColor
		ret = judgeWeightColorIfNotNeedSend(pColor,pColorPre,chanel_len);
	}
	return ret;
}

//私有函数：准备 重量+颜色 判断是否需要发送给屏幕
UINT16 screenPrivate_preBalancingWeightAndColorThenSendToSreen(T5LType *pSdwe,INT32 *pData , INT16 *pDataSendToDiWen , INT32 *pDataPre, \
INT16 *pColor , INT16 *pColorPre , INT16 *pColorOtherCh , UINT8 chanel_len)
{
	UINT16 ret = FALSE ;
	//
	switch((*pSdwe->screenCycle.handleStatus))
	{
		//judge if weight need send to screen
		//if weight was hold on some time then go to send color 
		case 0x00:
			//=================prepare weight data
			if(TRUE == screenPrivate_preWeightDataAndJudgeIfNeedSend(pData,pDataSendToDiWen,pDataPre,chanel_len))
			{
				if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pDataSendToDiWen,(2*chanel_len),0))//2*chanel_len:because each data type was 4 byte
				{
					(*pSdwe->screenCycle.weightHoldOn) = 0 ;
					handleWeightDataWasSend(pData,pDataPre,chanel_len);
				}
			}
			else
			{
				(*pSdwe->screenCycle.weightHoldOn)++;
				if((*pSdwe->screenCycle.weightHoldOn) >= DMG_DATA_HOLD_TIME)//if weight not changed then check if color need send
				{
					(*pSdwe->screenCycle.weightHoldOn) = 0;
					(*pSdwe->screenCycle.handleStatus) = 0x10;//if weight was send to screen go to send color
				}
			}
		break;

		//judge if color need send to screenxx
		case 0x10:
			//=================prepare color data
			if(TRUE == screenPrivate_preColorDataAndJudgeIfNeedSend(pData,pColor,pColorPre,pColorOtherCh,chanel_len))
			{
				if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pColor,chanel_len,0))
				{
					handleWeightColorWasSend(pColor,pColorPre,chanel_len);
					(*pSdwe->screenCycle.handleStatus) = 0x20;//if color was send to screen go to default
				}
			}
			else
			{
				(*pSdwe->screenCycle.handleStatus) = 0x20;//if color was send to screen go to default
			}
		break;

		default :
			(*pSdwe->screenCycle.handleStatus) = 0;//go to check weigth if not need send
			(*pSdwe->screenCycle.weightHoldOn) = 0;
			ret = TRUE;//this cycle was handle done
		break;
	}
	return ret;
}

//公共函数：发送 重量+颜色 给屏幕
UINT16 screenPublic_sendBalancingWeightAndColor(T5LType *pSdwe)
{
	INT32 *pData = &g_i32DataBuff[0];
	INT32 *pDataPre = &g_i32DataBuffPre[0];
	INT16 *pDataSendToDiWen = &g_i32_i16DataBuff[0];
	//
	INT16 *pColor = &g_i16ColorBuff[0];
	INT16 *pColorPre = &g_i16ColorBuffPre[0];
	INT16 *pColorOtherCh = &g_i16ColorOtherChanel[0];
	//
	UINT8 chanel_len = 0 , ret = 0;
#if 1
	pData = pSdwe->screenCycle.pData;
	pDataPre = pSdwe->screenCycle.pDataPre;
	pDataSendToDiWen = pSdwe->screenCycle.pDataSendToDiWen;

	pColor = pSdwe->screenCycle.pColor;
	pColorPre = pSdwe->screenCycle.pColorPre;
	pColorOtherCh = pSdwe->screenCycle.pColorOtherCh;
#endif
	//
	if(0 == gSystemPara.isCascade)
	{
		chanel_len = HX711_CHANEL_NUM;
	}
	else
	{
		chanel_len = T5L_MAX_CHANEL_LEN;
	}
	//1.prepare weight data and judge if not need send to screen
	//2.if need send , delay 250ms
	//3.send weight wo screen
	//4.prepare color data and judge if not need sent to screen
	//5.if need send to screen , otherwise back to judge data
	ret = screenPrivate_preBalancingWeightAndColorThenSendToSreen(pSdwe,pData,pDataSendToDiWen,pDataPre,pColor,pColorPre,pColorOtherCh,chanel_len);
	return ret;
}

//私有函数：发送 帮组信息 给屏幕 从机
void sendHelpDataDiff_AtSlave1Device(T5LType *pSdwe)
{
	static UINT8 needSend = FALSE;
	UINT8 i = 0;
	for(i=0;i<DIFF_TO_DIWEN_DATA_LEN;i++)
	{
		if(g_i16HelpDataBuffPre[i] != g_i16HelpDataBuff[i])
		{
			g_i16HelpDataBuffPre[i] = g_i16HelpDataBuff[i];
			needSend = TRUE;
		}
	}
	if(TRUE == needSend)
	{	
		if(TRUE == t5lWriteData(pSdwe,DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS,&g_i16HelpDataBuff[0],(DIFF_TO_DIWEN_DATA_LEN),0))
		{
			needSend = FALSE;
		}
	}
}

//公共函数：发送 帮组信息 给屏幕
UINT8 screenPublic_HelpDataMainFunction(T5LType *pSdwe)
{
	ModbusRtuType *pContex = &g_ModbusRtu;
	UINT8 localStatus = FALSE,i=0;
	
	//external data use inner screen data : color
	if(&g_T5LCtx[ScreenIndex_Larger] == pSdwe)
	{
		for(i = 0 ;i< DIFF_TO_DIWEN_DATA_LEN;i++)
		{
			g_i16HelpDataBuffLarger[i] = g_i16HelpDataBuff[i];
			if(g_i16HelpDataBuffLarger[i] != g_i16HelpDataBuffPreLarger[i])
			{
				*pSdwe->screenCycle.needSendHelp = TRUE;
			}
		}
	}
	else
	{
		if(0 == gSystemPara.isCascade)
		{
			localStatus = sendHelpDataDiff(pSdwe);
		}else if(gSystemPara.isCascade == ModbusAdd_Slave_1)//cascade : slave Device
		{
			sendHelpDataDiff_AtSlave1Device(pSdwe);
		}else if(gSystemPara.isCascade == ModbusAdd_Master)//cascade : master Device
		{
			masterCaculateHelpData(pContex,T5L_MAX_CHANEL_LEN);	
			sendHelpDataDiff_AtSlave1Device(pSdwe);
		}else if(gSystemPara.isCascade == ModbusFuncA_Slave)//cascade : slave Device
		{
			sendHelpDataDiff_AtSlave1Device(pSdwe);
		}else if(gSystemPara.isCascade == ModbusFuncA_Master)//cascade : master Device
		{
			masterCaculateHelpData(pContex,T5L_MAX_CHANEL_LEN); 
			sendHelpDataDiff_AtSlave1Device(pSdwe);
		}	
	}
	//如果需要发送
	if(TRUE == *pSdwe->screenCycle.needSendHelp)
	{	
		if(TRUE == t5lWriteData(pSdwe,DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS,&g_i16HelpDataBuff[0],(DIFF_TO_DIWEN_DATA_LEN),0))
		{
			*pSdwe->screenCycle.needSendHelp = FALSE;
			localStatus = TRUE;
		}
	}
	return localStatus;
}

//公共函数：发送 语音提示 给屏幕
UINT8 screenPublic_VoicePrintfMainfunction(T5LType *pSdwe)
{
	static UINT8 u8Vstatus = 0 ;
	static tT5LVoinceType u8Voice1 = T5L_VoiceTypeNum_0 ,u8Voice2 = T5L_VoiceTypeNum_0 ,u8Voice3 = T5L_VoiceTypeNum_0 ;
	static UINT32 u16Ticks = 0 ;
	UINT8 localStatus = FALSE;
	//
	if(FALSE == gSystemPara.ScreenVoiceSwitch)
	{
		return localStatus;
	}
	switch(u8Vstatus)
	{
		case 0:
			if(TRUE == sdwe_VoicePrintfPop(&u8Voice1,&u8Voice2,&u8Voice3))
			{
				u8Vstatus++;
			}
			else
			{
				localStatus = TRUE;//special handle , no anly voice need printf return TRUE
			}
		break;
		
		//===========voice 1
		case 1://printf V1
			if(TRUE == screenT5L_OutputVoice(pSdwe,u8Voice1))
			{
				u8Vstatus++;
				u16Ticks = pSdwe->CurTick ;
			}
		break;
		case 2://wait time
			if(pSdwe->CurTick >= (u16Ticks + 900))
			{
				u8Vstatus=5;
			}
		break;

		//===========voice 2
		case 5://printf v2
			if(TRUE == screenT5L_OutputVoice(pSdwe,u8Voice2))
			{
				u8Vstatus++;
				u16Ticks = pSdwe->CurTick ;
			}
		break;
		case 6://wait time
			if(pSdwe->CurTick >= (u16Ticks + 900))
			{
				u8Vstatus++;
			}
		break;

		//==========pei pin cheng gong
		case 7://printf v1 v2 success
			if(TRUE == screenT5L_OutputVoice(pSdwe,u8Voice3))
			{
				u8Vstatus++;
				u16Ticks = pSdwe->CurTick ;
			}
		break;
		case 8://wait time
			if(pSdwe->CurTick >= (u16Ticks + 1200))
			{
				u8Vstatus++;
				screenT5L_OutputVoice(pSdwe,VoiceTypeMax);
			}
		break;

		//===========yu
		case 3://printf yu
			if(TRUE == screenT5L_OutputVoice(pSdwe,VoiceTypeYu_17))
			{
				u8Vstatus++;
				u16Ticks = pSdwe->CurTick ;
			}
		break;
		case 4://wait time
			if(pSdwe->CurTick >= (u16Ticks + 1000))
			{
				u8Vstatus++;
			}
		break;

		default:
			u8Vstatus = 0 ;
			localStatus = TRUE;
		break;
	}
	return localStatus;
}


//=====================================================================================================================
//==================================================[ 屏幕处理公共函数 : 结束 ]==========================================
//=====================================================================================================================
//========================================================================================check:20210619
//if screen at calibration page point trigerd
void pointWeightTrigerDataSet(UINT8 localChanel , UINT8 point , INT16 value)
{
	if(localChanel > HX711_CHANEL_NUM)
		return ;

	if(point < CHANEL_POINT_NUM)
	{
		g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_ASK_WEIGHT][point] = value;//point weight triger	
	}
}

//if screen at calibration page point trigerd
void pointSampleTrigerDataSet(UINT8 localChanel , UINT8 point , INT16 value)
{
	if(localChanel > HX711_CHANEL_NUM)
		return ;

	if(point < CHANEL_POINT_NUM)
	{
		g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_AVG_SAMPLE][point] = value;//point sample triger	
	}
}

//if screen at calibration page point trigerd
void pointTrigerDataSet(UINT8 localChanel , UINT8 point , UINT8 value ,INT16 avgSampleValue)
{	
	if(localChanel > HX711_CHANEL_NUM)
		return ;

	if(point < CHANEL_POINT_NUM)
	{
		g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_STATUS][point] = TRUE;//point triger need answer flag	
		g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_ASK_COLOR][point] = value;//point triger color answer	
		g_t5l_triger_data[localChanel][DMG_TRIGER_SAMPLE_OF_AVG_SAMPLE][point] = avgSampleValue;//point triger avg sample value answer
	}
}

//==clear all color vlu
void color_clearAllColor(void)
{
	UINT8 seq = 0;
	for(seq=0;seq<T5L_MAX_CHANEL_LEN;seq++)
	{
		g_i16ColorBuff[seq] = LED_COLOR_NONE;
		g_i16ColorBuffPre[seq] = LED_COLOR_NUM;
	}
}

//clear data to screen at calibration page
void clearLocalCalibrationRecordData(UINT8 sreen_chanel)
{
	UINT8 chane_i = 0 , point_j = 0 ;
	
	if(0 == sreen_chanel)//clear all
	{
		for(chane_i=0;chane_i<(HX711_CHANEL_NUM+1);chane_i++)
		{
			//==1:clear sreen needs back color and sample data
			for(point_j=0;point_j<CHANEL_POINT_NUM;point_j++)
			{
				//back color
				g_t5l_triger_data[chane_i][DMG_TRIGER_SAMPLE_OF_ASK_COLOR][point_j] = 0 ;//color:1 green 0:white
				//data
				g_t5l_triger_data[chane_i][DMG_TRIGER_SAMPLE_OF_AVG_SAMPLE][point_j] = 0 ;//sample data = 0
			}
		}
	}
	else if(sreen_chanel <= HX711_CHANEL_NUM)
	{
		chane_i = sreen_chanel - 1 ;
		//==1:clear sreen needs back color and sample data
		for(point_j=0;point_j<CHANEL_POINT_NUM;point_j++)
		{
			//back color
			g_t5l_triger_data[chane_i][DMG_TRIGER_SAMPLE_OF_ASK_COLOR][point_j] = 0 ;//color:1 green 0:white
			//data
			g_t5l_triger_data[chane_i][DMG_TRIGER_SAMPLE_OF_AVG_SAMPLE][point_j] = 0 ;//sample data = 0
		}
	}
}

//clear local recode k and b and sample data
void clearLocalCalibrationKAndBAndSample(UINT8 sreen_chanel)
{
	UINT8 chane_i = 0 , point_j = 0 ;
	ChanelType *pChanel=0;
	
	if(0 == sreen_chanel)//clear all
	{
		for(chane_i=0;chane_i<HX711_CHANEL_NUM;chane_i++)
		{
			//==1:clear local sample data and k and b
			//get chanel
			pChanel = getChanelStruct(chane_i);
			//clear local sample point
			for(point_j=0;point_j<CHANEL_POINT_NUM;point_j++)
			{
				pChanel->section_PointSample[point_j] = 0 ;
			}
			//clear local k & b
			for(point_j=0;point_j<(CHANEL_POINT_NUM+1);point_j++)
			{
				pChanel->section_K[point_j] = 0.0 ;
				pChanel->section_B[point_j] = 0.0 ;
			}
		}
	}
	else if(sreen_chanel <= HX711_CHANEL_NUM)
	{
		chane_i = sreen_chanel - 1 ;

		//==1:clear local sample data and k and b
		//get chanel
		pChanel = getChanelStruct(chane_i);
		//clear local sample point
		for(point_j=0;point_j<CHANEL_POINT_NUM;point_j++)
		{
			pChanel->section_PointSample[point_j] = 0 ;
		}
		//clear local k & b
		for(point_j=0;point_j<(CHANEL_POINT_NUM+1);point_j++)
		{
			pChanel->section_K[point_j] = 0.0 ;
			pChanel->section_B[point_j] = 0.0 ;
		}
	}	
}

//密码管理
UINT8 screenRxHandle_SysPassWord(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(pSdwe->SetAdd == DMG_FUNC_PASSORD_SET_ADDRESS)
	{
		STM32CheckPassWord(pSdwe->SetData);/**< 密码 */
		pSdwe->needStore |= DMG_TRIGER_SAVE_SECOTOR_2 ;
		matched = TRUE;
	}
	return matched;
}

//=====================================================================================================================
//==================================================[ 屏幕处理公共函数 ：屏幕串口解析执行回调函数 ]========================
//=====================================================================================================================
//接收到屏幕的数据变量的处理
UINT8 sdweAskVaribleData(ScreenHandleType  *screenHandlePtr,UINT16 varAdd, UINT16 varData)
{
	UINT8 needStore = FALSE , i = 0;
	T5LType *pSdwe = screenHandlePtr->Ctx;
	//
	pSdwe->SetAdd = varAdd ;
	pSdwe->SetData = varData ;
	//receive address from SDWE
	if(0xffff != pSdwe->SetAdd)
	{
		for( i = 0 ; i < screenHandlePtr->recvScreenHadlleNum ; i++)
		{
			if(TRUE == screenHandlePtr->recvScreenHadlleCtx[i].func(pSdwe))
			{
				needStore = pSdwe->needStore;
				break;//遍历所有屏幕发过来的变量地址，满足则退出遍历
			}
		}
		//clr address
		pSdwe->SetAdd = 0xffff;
	}
	return needStore;
}

//接收到屏幕的寄存器数据处理
UINT8 sdweAskRegData(ScreenHandleType  *screenHandlePtr,UINT8 regAdd, UINT8 regData)
{
	UINT8 needStore = FALSE ;
	T5LType *pSdwe = screenHandlePtr->Ctx;
	if(0 == regAdd)
	{
		pSdwe->version = regData;
		pSdwe->readSdweInit = TRUE;
	}
	return needStore;
}

//=====================================================================================================================
//==================================================[ 系统处理公共函数 ：从MODBUS获取信息 ]===============================
//=====================================================================================================================
//发送帮组信息
UINT8 sendHelpDataDiff(T5LType *pSdwe)
{
	UINT8 i = 0 , localStatus = 0;

	INT32 *pData = &g_i32DataBuff[0];
	INT16 *pColorOtherCh = &g_i16ColorOtherChanel[0];
	//
	float *sortWeight = &g_i16HelpDataSort[0];
	INT16 *sortArry = &g_i16HelpDataChnSort[0];
	INT16 i16Minus = 0 , minPos_i = 0xff ,minPos_j=0xff;
	UINT8 help_i = 0;
	//
	INT16 *pOutData = &g_i16HelpDataBuff[0];
	//
	UINT8 sortArry_num = 0 ,chn_i = 0 , chn_j = 0;

	//2.use pColor ==  LED_COLOR_NONE , to triger need judge weight
	sortArry_num = 0 ;
	for(chn_i=0;chn_i<HX711_CHANEL_NUM;chn_i++)
	{
		if(T5L_CHANEL_WEIGHT_NOT_EQUAL == pColorOtherCh[chn_i])
		{
			sortWeight[sortArry_num] = pData[chn_i];
			sortArry[sortArry_num] = chn_i;
			sortArry_num++;
		}
	}
	//==sort weight : from min to max
	if(sortArry_num > 1)
	{	
		BubbleSort((float *)sortWeight,sortArry,sortArry_num);
	}
	//
	for(help_i=0;help_i < DIFF_JUDGE_GROUP_NUM_SLAVE1;)
	{
		i16Minus = 0x7FFF ;
		minPos_i = 0xff;
		minPos_j = 0xff;
		//find chn_i
		for(chn_i=0;chn_i<sortArry_num;chn_i++)
		{
			if((sortWeight[chn_i] >= gSystemPara.zeroRange) || 
				(sortWeight[chn_i] <= -gSystemPara.zeroRange) )
			{
				//find chn_j
				for(chn_j=(chn_i+1);chn_j<sortArry_num;chn_j++)
				{
					//if chn_j larger than zero
					if((sortWeight[chn_j] >= gSystemPara.zeroRange) || 
						(sortWeight[chn_j] <= -gSystemPara.zeroRange) )
					{
						break;
					}
				}
				//==out the least value of diff 
				if((chn_i < sortArry_num) && (chn_j < sortArry_num))
				{
					if((sortWeight[chn_j] - sortWeight[chn_i]) < i16Minus)
					{
						i16Minus = sortWeight[chn_j] - sortWeight[chn_i];
						minPos_j = chn_j;
						minPos_i = chn_i;
					}
				}
			}	
		}
		//==qunene the least value of diff
		if((i16Minus != 0x7FFF) && (0xff != minPos_i) && (0xff != minPos_j))
		{
			if(help_i < DIFF_JUDGE_GROUP_NUM_SLAVE1)
			{
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 0] = sortArry[minPos_j]+1;
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 1] = sortArry[minPos_i]+1;
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 2] = i16Minus;
				help_i++;
			}
			sortWeight[minPos_j] = 0 ;
			sortWeight[minPos_i] = 0 ;
		}
		else
		{
			break;
		}
	}
	//==the remain help data set to 0
	for(;help_i<(DIFF_JUDGE_GROUP_NUM_SLAVE1);help_i++)
	{
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 0] = 0;
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 1] = 0;
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 2] = 0;
	}
	//==judge if not send to screen
	for(i=0;i<DIFF_TO_DIWEN_DATA_LEN;i++)
	{
		if(g_i16HelpDataBuffPre[i] != g_i16HelpDataBuff[i])
		{
			g_i16HelpDataBuffPre[i] = g_i16HelpDataBuff[i];
			*pSdwe->screenCycle.needSendHelp = TRUE;
		}
	}
#if 0
	if(TRUE == needSend)
	{	
		if(TRUE == t5lWriteData(pSdwe,DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS,&g_i16HelpDataBuff[0],(DIFF_TO_DIWEN_DATA_LEN),0))
		{
			needSend = FALSE;
			localStatus = TRUE;//如果需要发送帮助信息，且发送成功，代表本轮结束
		}
	}
	else
	{
		localStatus = TRUE;//如果不需要更新帮助信息
	}
#endif
	return localStatus;
}

//主机 计算 帮组信息
void masterCaculateHelpData(ModbusRtuType *pContex,UINT8 chanel_len)
{
	INT32 *pData = &g_i32DataBuff[0];
	INT16 *pColorOtherCh = &g_i16ColorOtherChanel[0];
	//
	float *sortWeight = &g_i16HelpDataSort[0];
	INT16 *sortArry = &g_i16HelpDataChnSort[0];
	INT16 i16Minus = 0 ,minPos_i = 0xff ,minPos_j=0xff;
	UINT8 help_i = 0 ;
	//
	INT16 *pOutData = &g_i16HelpDataBuff[0];
	//
	UINT8 sortArry_num = 0 ,chn_i = 0 , chn_j = 0;
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		for(chn_i=0;chn_i<chanel_len;chn_i++)
		{
			if(T5L_CHANEL_WEIGHT_NOT_EQUAL == pColorOtherCh[chn_i])
			{
				sortWeight[sortArry_num] = pData[chn_i];
				sortArry[sortArry_num] = chn_i;
				sortArry_num++;
			}
		}
	}
	//==sort weight : from min to max
	if(sortArry_num > 1)
	{	
		BubbleSort((float *)sortWeight,sortArry,sortArry_num);
	}
	//
	for(help_i=0;help_i < DIFF_JUDGE_GROUP_NUM_SLAVE1;)
	{
		i16Minus = 0x7FFF ;
		minPos_i = 0xff;
		minPos_j = 0xff;
		//find chn_i
		for(chn_i=0;chn_i<sortArry_num;chn_i++)
		{
			if((sortWeight[chn_i] >= gSystemPara.zeroRange) || 
				(sortWeight[chn_i] <= -gSystemPara.zeroRange) )
			{
				//find chn_j
				for(chn_j=(chn_i+1);chn_j<sortArry_num;chn_j++)
				{
					//if chn_j larger than zero
					if((sortWeight[chn_j] >= gSystemPara.zeroRange) || 
						(sortWeight[chn_j] <= -gSystemPara.zeroRange) )
					{
						break;
					}
				}
				//==out the least value of diff 
				if((chn_i < sortArry_num) && (chn_j < sortArry_num))
				{
					if((sortWeight[chn_j] - sortWeight[chn_i]) < i16Minus)
					{
						i16Minus = sortWeight[chn_j] - sortWeight[chn_i];
						minPos_j = chn_j;
						minPos_i = chn_i;
					}
				}
			}	
		}
		//==qunene the least value of diff
		if((i16Minus != 0x7FFF) && (0xff != minPos_i) && (0xff != minPos_j))
		{
			if(help_i < DIFF_JUDGE_GROUP_NUM_SLAVE1)
			{
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 0] = sortArry[minPos_j]+1;
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 1] = sortArry[minPos_i]+1;
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 2] = i16Minus;
				help_i++;
			}
			sortWeight[minPos_j] = 0 ;
			sortWeight[minPos_i] = 0 ;
		}
		else
		{
			break;
		}
	}
	//==the remain help data set to 0
	for(;help_i<(DIFF_JUDGE_GROUP_NUM_SLAVE1);help_i++)
	{
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 0] = 0;
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 1] = 0;
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 2] = 0;
	}
}

//主机 将帮组信息 写入MODBUS
void writeHelpDataFromCom(UINT8 *pHelpData,UINT8 len)
{
	UINT8 i = 0 ;
	if(len <= DIFF_TO_DIWEN_DATA_LEN)
	{
		for(i=0;i<len;i++)
		{
			g_i16HelpDataBuff[i] = 0 ;
			g_i16HelpDataBuff[i] = pHelpData[2*i+0];
			g_i16HelpDataBuff[i] <<= 8;
			g_i16HelpDataBuff[i] &= 0XFF00;
			g_i16HelpDataBuff[i] += pHelpData[2*i+1];
		}
	}
}

//主机 读取 计算得到的 重量信息
void readWeightDataFromSys(UINT8 *pWeightData,UINT8 len)
{
	UINT8 i = 0 ;
	if(len <= T5L_MAX_CHANEL_LEN)
	{
		for(i=0;i<len;i++)
		{
			pWeightData[4*i+0] = (g_i32DataBuff[i]>>24)&0xff;
			pWeightData[4*i+1] = (g_i32DataBuff[i]>>16)&0xff;
			pWeightData[4*i+2] = (g_i32DataBuff[i]>>8)&0xff;
			pWeightData[4*i+3] = (g_i32DataBuff[i]>>0)&0xff;
		}
	}
}

//主机 读取 计算得到的 颜色信息
void readColorDataFromSys(UINT8 *pColorData,UINT8 len)
{
	UINT8 i = 0 ;
	if(len <= T5L_MAX_CHANEL_LEN)
	{
		for(i=0;i<len;i++)
		{
			pColorData[2*i+0] = (g_i16ColorBuff[i]>>8)&0xff;
			pColorData[2*i+1] = (g_i16ColorBuff[i]>>0)&0xff;
		}
	}
}

//主机 读取 计算得到的 帮组信息
void readHelpDataFromSys(UINT8 *pHelpData,UINT8 len)
{
	UINT8 i = 0 ;
	if(len <= DIFF_TO_DIWEN_DATA_LEN)
	{
		for(i=0;i<len;i++)
		{
			pHelpData[2*i+0] = (g_i16HelpDataBuff[i]>>8)&0xff;
			pHelpData[2*i+1] = (g_i16HelpDataBuff[i]>>0)&0xff;
		}
	}
}

//主机：从MODBUS中读取从机的 重量信息（带换算和小数点）
float GetFloatBalancingModelData(enumModbusAddType slaveId,enumHX711ChanelType chanel)
{
	float weight = 0.0;
	ModbusRtuType *pContex = &g_ModbusRtu;
	if((chanel < HX711_CHANEL_NUM ) 
		&& ( slaveId >= ModbusAdd_Master )
		&& ( slaveId < ModbusAdd_Slave_Max ))
	{
		weight = pContex->MultWeightData[slaveId-ModbusAdd_Master][chanel].f_value;
		//
		if((0 != gSystemPara.mlYugBiLv) && (SYS_ML_G_WAS_ML == gSystemPara.uint))
		{
			weight *= 1000;
			weight /= gSystemPara.mlYugBiLv;
		}
		//judge if not have decimal
		if(0 == gSystemPara.xiaoShuXianShi)
		{
			weight = weight + 0.5f;
		}
		else
		{
			weight = 10*weight;
		}
	}
	return weight;
}

//主机：从MODBUS中读取从机的 重量信息
void screenPublic_OtherDevice_WeightDataPrepare(INT32 *pData,INT16 *pDataInt16 ,enumModbusAddType modbusSlaveId)
{
	UINT8 offset = 0;
	enumHX711ChanelType chanel = HX711Chanel_1;
	//
	if(modbusSlaveId < ModbusAdd_Slave_Max)
	{
		for(chanel = HX711Chanel_1 ; chanel < HX711_CHANEL_NUM ; chanel++)
		{
			offset = HX711_CHANEL_NUM*(modbusSlaveId - ModbusAdd_Master) + chanel;
			pData[offset] = (INT32)(GetFloatBalancingModelData(modbusSlaveId,chanel));
			//INT32 data to INT16 data
			pDataInt16[2*offset + 0] = (pData[offset] >> 16) & 0xFFFF;
			pDataInt16[2*offset + 1] = (pData[offset] >> 0 ) & 0xFFFF;
		}		
	}
}

//主机/从机：从HX711读取 重量信息
void screenPublic_CurrentDevice_WeightDataPrepare(INT32 *pData,INT16 *pDataInt16)
{
	float weight;
	enumHX711ChanelType chanel = HX711Chanel_1;
	//
	for(chanel = HX711Chanel_1 ; chanel < HX711_CHANEL_NUM ; chanel++)
	{
		//get current device weight
		weight = hx711_getWeight(chanel);
		//uint handle of g/ml
		if((0 != gSystemPara.mlYugBiLv) && (SYS_ML_G_WAS_ML == gSystemPara.uint))
		{
			weight *= 1000;
			weight /= gSystemPara.mlYugBiLv;
		}
		//judge if not have decimal
		if(0 == gSystemPara.xiaoShuXianShi)
		{
			pData[chanel] = (INT32)(weight+0.5f);
		}
		else
		{
			pData[chanel] = (INT32)(10*weight);
		}
		//pData[chanel] = 0x12345678*(1+chanel);
		//INT32 data to INT16 data
		pDataInt16[2*chanel + 0] = (pData[chanel] >> 16) & 0xFFFF;
		pDataInt16[2*chanel + 1] = (pData[chanel] >> 0 ) & 0xFFFF;
	}
}

//从机：从MODBUS中获取 重量信息
void writeWeightDataFromCom(UINT8 *pWeightData,UINT8 len)
{
	UINT8 i = 0 ;
	if(len <= T5L_MAX_CHANEL_LEN)
	{
		for(i=0;i<len;i++)
		{
			g_i32DataBuff[i] = 0 ;
			g_i32DataBuff[i] = pWeightData[4*i+0];
			g_i32DataBuff[i] <<= 8;
			g_i32DataBuff[i] &= 0X0000FF00;
			g_i32DataBuff[i] += pWeightData[4*i+1];
			g_i32DataBuff[i] <<= 8 ;
			g_i32DataBuff[i] &= 0X00FFFF00;
			g_i32DataBuff[i] += pWeightData[4*i+2];
			g_i32DataBuff[i] <<= 8;
			g_i32DataBuff[i] &= 0XFFFFFF00;
			g_i32DataBuff[i] += pWeightData[4*i+3];		
		}
	}
}

//从机：从MODBUS中获取 颜色信息
void writeColorDataFromCom(UINT8 *pColorData,UINT8 len)
{
	UINT8 i = 0 ;
	if(len <= T5L_MAX_CHANEL_LEN)
	{
		for(i=0;i<len;i++)
		{
			g_i16ColorBuff[i] = 0 ;
			g_i16ColorBuff[i] = pColorData[2*i+0];
			g_i16ColorBuff[i] <<= 8;
			g_i16ColorBuff[i] &= 0XFF00;
			g_i16ColorBuff[i] += pColorData[2*i+1];
		}
	}
}

//================================================================================================
//需要播报语音的语音序号入队
void sdwe_VoicePrintfPush(tT5LVoinceType u8Voice1 ,tT5LVoinceType u8Voice2)
{
	if(u8T5LVoiceBuffStoreNum == 0)
	{
		g_T5L_VoiceBuff[u8T5LVoiceBuffPush_i][0] = u8Voice1;
		g_T5L_VoiceBuff[u8T5LVoiceBuffPush_i][1] = u8Voice2;
		g_T5L_VoiceBuff[u8T5LVoiceBuffPush_i][2] = VoiceTypePeiPin_18;
		u8T5LVoiceBuffPush_i = (u8T5LVoiceBuffPush_i+1)%T5L_VOICE_MAX_PRINTF_NUM;
		//
		u8T5LVoiceBuffStoreNum++;
	}
}

//需要播报语音的语音序号出队
UINT8 sdwe_VoicePrintfPop(tT5LVoinceType *u8Voice1 , tT5LVoinceType *u8Voice2 , tT5LVoinceType *u8Voice3)
{
	UINT8 ret = FALSE;
	if(u8T5LVoiceBuffStoreNum > 0)
	{
		u8T5LVoiceBuffStoreNum--;
		//
		*u8Voice1 = g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][0];
		g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][0] =T5L_VoiceTypeNum_0;
		*u8Voice2 = g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][1];
		g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][1] = T5L_VoiceTypeNum_0;
		*u8Voice3 = g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][2];
		g_T5L_VoiceBuff[u8T5LVoiceBuffPop_i][2] = T5L_VoiceTypeNum_0;
		
		//add u8T5LVoiceBuffPop_i
		u8T5LVoiceBuffPop_i = (u8T5LVoiceBuffPop_i+1)%T5L_VOICE_MAX_PRINTF_NUM;
		//
		if(((T5L_VoiceTypeNum_1 <= *u8Voice1) && (T5L_VoiceTypeNum_16 >= *u8Voice1)) &&
			((T5L_VoiceTypeNum_1 <= *u8Voice2) && (T5L_VoiceTypeNum_16 >= *u8Voice2)) &&
			(VoiceTypePeiPin_18 == *u8Voice3) )
		{
			ret = TRUE;
		}
	}
	//
	return ret;
}

//触发屏幕语音播报
UINT8 screenT5L_OutputVoice(T5LType *pSdwe,UINT8 voiceId)
{
	UINT8 result = 0 ;
	//5A A5 07 82 00A0 3101 4000
	INT16 pageChangeOrderAndData[2]={0x3101,0X6400};//0x40=64 音量100 00速度

	if((gSystemPara.VoiceNum > 0) && (gSystemPara.VoiceNum <= 100) )
	{
		pageChangeOrderAndData[1] &= 0x00ff;
		pageChangeOrderAndData[1] |= (0xff00&(gSystemPara.VoiceNum<<8)); 
	}
	if(voiceId == VoiceTypeMax)
	{
		pageChangeOrderAndData[1] &= 0x00ff;
		pageChangeOrderAndData[1] |= (0xff00&(gSystemPara.VoiceNumTouch<<8)); 
	}
	//
	pageChangeOrderAndData[0] = ((voiceId%VoiceTypeMax)<<8)+(1);//音乐序号 1：整段音乐
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X00A0),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}









//=====================================================================================================================
//==================================================[ 屏幕处理私有函数 ：开始 ]==========================================
//=====================================================================================================================

//私有函数：
UINT8 judgeWeightDataIfNotNeedSend(INT32 *pData , INT32 *pDataPre ,UINT8 chanel_len)
{
	UINT8 ret = FALSE , offset = 0;
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		for(offset = 0 ; offset < chanel_len ; offset++)
		{
			if(pData[offset] != pDataPre[offset])
			{
				ret = TRUE ;
			}
		}
	}
	return ret;
}

//私有函数：
void handleWeightDataWasSend(INT32 *pData , INT32 *pDataPre ,UINT8 chanel_len)
{
	UINT8 offset = 0;
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		for(offset = 0 ; offset < chanel_len ; offset++)
		{
			pDataPre[offset] = pData[offset];
		}
	}
}

//私有函数：颜色控制
UINT8 judgeWeightColorIfNotNeedSend(INT16 *pColor,INT16 *pColorPre ,UINT8 chanel_len)
{
	UINT8 ret = FALSE , offset = 0;
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		for(offset = 0 ; offset < chanel_len ; offset++)
		{
			if(pColor[offset] != pColorPre[offset])
			{
				ret = TRUE ;
			}
		}
	}
	return ret;
}

//私有函数：系统颜色控制
void handleWeightColorWasSend(INT16 *pColor,INT16 *pColorPre ,UINT8 chanel_len)
{
	UINT8 offset = 0;
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		for(offset = 0 ; offset < chanel_len ; offset++)
		{
			pColorPre[offset] = pColor[offset];
		}
	}
}

//私有函数：系统颜色控制
enumLedColorType getSysColorWhichUsable(void)
{
	enumLedColorType ret = LED_COLOR_NONE;
	UINT8 i = 0 ;
	for(i=0;i<SYS_COLOR_GROUP_NUM;i++)
	{
		if(SYS_COLOR_USED_FLAG != gSystemPara.userColorUsed[i])
		{
			gSystemPara.userColorUsed[i] = SYS_COLOR_USED_FLAG;
			ret = (enumLedColorType)gSystemPara.userColorSet[i]; 
			break;
		}
	}
	return ret;
}

//私有函数：系统颜色控制
void releaseSysColor(enumLedColorType color)
{
	UINT8 i = 0 ;
	for(i=0;i<SYS_COLOR_GROUP_NUM;i++)
	{
		if(color == gSystemPara.userColorSet[i])
		{
			gSystemPara.userColorUsed[i] = 0;
			break;
		}
	}
}

//私有函数：系统颜色控制
void holdSysColor(enumLedColorType color)
{
	UINT8 i = 0 ;
	for(i=0;i<SYS_COLOR_GROUP_NUM;i++)
	{
		if(color == gSystemPara.userColorSet[i])
		{
			gSystemPara.userColorUsed[i] = SYS_COLOR_USED_FLAG;
			break;
		}
	}
}

//私有函数==20210609
void preColorData(INT32 *pData,INT16 *pColor,INT16 *pColorPre,INT16 *pColorOtherCh,UINT8 chanel_len)
{
	UINT8 release = FALSE;
	UINT8 sortArry_num = 0 ,chn_self = 0 , chn_other = 0 , chn_i = 0;
	//
	float *sortWeight = &g_fDataBuffCaculate[0];
	INT16 *sortArry = &g_i16OtherChanelCaculate[0];
	//
	UINT8 compare_i = 0 ;
	//
	float judge_errRange = gSystemPara.errRange,judge_zeroRange = gSystemPara.zeroRange;

	enumLedColorType colorVld = LED_COLOR_NONE;

	//有小数点时，判断范围乘以10
	if(1 == gSystemPara.xiaoShuXianShi)
	{
		judge_errRange = gSystemPara.errRange*10;
		judge_zeroRange = gSystemPara.zeroRange*10;
	}
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		//1.judge the equal chanle again
		for(chn_i=0;chn_i<chanel_len;chn_i++)
		{
			release = FALSE;//dit not release channel display color
			//
			chn_self = chn_i;//self chanel
			chn_other = (UINT8)pColorOtherCh[chn_self];//other chanel
			//other chanel matched
			if(chn_other < chanel_len)
			{
				if(((pData[chn_self] - pData[chn_other]) >= -judge_errRange) && ((pData[chn_self] - pData[chn_other]) <= judge_errRange) )
				{
					//self and other chanel weight equal again
					if(((pData[chn_self] > -judge_zeroRange) && (pData[chn_self] < judge_zeroRange)) ||	
						((pData[chn_other] > -judge_zeroRange) && (pData[chn_other] < judge_zeroRange)))
					{
						//1.3 someone weight at zero range , need release
						release = TRUE;
					}
					else
					{
						if(pColor[chn_self] != pColor[chn_other])
						{
							//1.2 weight equal but color not equal or someone was NONE color, need release
							release = TRUE;
						}
					}
				}
				else
				{
					//1.1 weight not equal again , need release
					release = TRUE;
				}
			}
			else
			{
				//1.0 other channel not match , need release
				release = TRUE;
			}

			//if need release , must release self and other
			if(TRUE == release)
			{
				//clear the self other chanel = Invalid
				if(T5L_CHANEL_WEIGHT_NOT_EQUAL != pColorOtherCh[chn_self])
				{
					pColorOtherCh[chn_self] = T5L_CHANEL_WEIGHT_NOT_EQUAL;
				}
				//clear the other chanel = Invalid
				if((chn_other < T5L_MAX_CHANEL_LEN) && (T5L_CHANEL_WEIGHT_NOT_EQUAL != pColorOtherCh[chn_other]))
				{
					pColorOtherCh[chn_other] = T5L_CHANEL_WEIGHT_NOT_EQUAL;
				}
				//release self color
				if(LED_COLOR_NONE != pColor[chn_self])
				{
					releaseSysColor((enumLedColorType)pColor[chn_self]);//release used color
					LedDataSet((enumLedSeqType)chn_self, LED_COLOR_NONE);//LED : display
					pColor[chn_self] = LED_COLOR_NONE;//clear chn_self color
				}
				//release other color
				if((chn_other < T5L_MAX_CHANEL_LEN) && (LED_COLOR_NONE != pColor[chn_other]))
				{
					releaseSysColor((enumLedColorType)pColor[chn_other]);//release used color
					LedDataSet((enumLedSeqType)chn_other, LED_COLOR_NONE);//LED : display
					pColor[chn_other] = LED_COLOR_NONE;//clear chn_other color
				}
			}
		}
		//2.use pColor ==  LED_COLOR_NONE , to triger need judge weight
		sortArry_num = 0 ;
		for(chn_i=0;chn_i<chanel_len;chn_i++)
		{
			//no color and weight was need match outof zero
			if((LED_COLOR_NONE == pColor[chn_i]) &&
			((pData[chn_i] < -judge_zeroRange) || (pData[chn_i] > judge_zeroRange)))
			{
				sortWeight[sortArry_num] = pData[chn_i];
				sortArry[sortArry_num] = chn_i;
				sortArry_num++;
			}
		}
		//3.use weight Sort
		BubbleSort(sortWeight,sortArry,sortArry_num);
		//4.user sorted weight , set color
		for(compare_i=0;compare_i<(sortArry_num-1);compare_i++)
		{
			chn_self = sortArry[compare_i];
			chn_other = sortArry[compare_i+1];
			if(( chn_self < chanel_len) && ( chn_other < chanel_len) )
			{
				//is equal
				if( ((pData[chn_self] < -judge_zeroRange) || (pData[chn_self] > judge_zeroRange)) &&
					((pData[chn_other] < -judge_zeroRange) || (pData[chn_other] > judge_zeroRange)) &&
					(((pData[chn_self] - pData[chn_other]) >= -judge_errRange) && ((pData[chn_self] - pData[chn_other]) <= judge_errRange) ) )
				{
					//screen : set the same color
					colorVld = getSysColorWhichUsable();
					pColor[chn_self] = colorVld;
					pColor[chn_other] = colorVld;
					//otherChn recode
					pColorOtherCh[chn_self] = chn_other;
					pColorOtherCh[chn_other] = chn_self;
					
					//screen : voice pritf
					if(LED_COLOR_NONE != colorVld)//bug : case weight equal but colot was LED_COLOR_NONE
					{
						sdwe_VoicePrintfPush((tT5LVoinceType)(chn_self+1),(tT5LVoinceType)(chn_other+1));
					}
					//LED : display
					LedDataSet((enumLedSeqType)chn_self, colorVld);
					LedDataSet((enumLedSeqType)chn_other, colorVld);

					//
					compare_i++;//!!!!! must add it !!!!!
				}
			}
		}
	}
}





//=====================================================================================================================
//==================================================[ 屏幕处理私有函数 ：结束 ]==========================================
//=====================================================================================================================


//占无用
#if 0
UINT8 preWeightDataAndJudgeIfNeedSend_Master(INT32 *pData,INT16 *pDataInt16, INT32 *pDataPre,UINT8 chanel_len)
{
	UINT8 ret = FALSE;
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		//not ji lian
		if(0 == gSystemPara.isCascade)
		{
			//master local data
			screenPublic_CurrentDevice_WeightDataPrepare(pData,pDataInt16);
			//judge if not need send
			ret = judgeWeightDataIfNotNeedSend(pData,pDataPre,chanel_len);
		}
		else if(ModbusAdd_Master == gSystemPara.isCascade)
		{
			//master local data
			screenPublic_CurrentDevice_WeightDataPrepare(pData,pDataInt16);
			//ModbusAdd_Slave_1 recv data
			screenPublic_OtherDevice_WeightDataPrepare(pData,pDataInt16,ModbusAdd_Slave_1);
			//judge if not need send
			ret = judgeWeightDataIfNotNeedSend(pData,pDataPre,chanel_len);			
		}
	}
	//
	return ret;
}
UINT8 preWeightDataAndJudgeIfNeedSend_FuncA_Master(T5LType *pSdwe,INT32 *pData,INT16 *pDataInt16,INT32 *pDataPre,UINT8 chanel_len)
{
	UINT8 ret = FALSE ;
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		//master local data
		screenPublic_CurrentDevice_WeightDataPrepare(pData,pDataInt16);
		//ModbusAdd_Slave_1 recv data
		screenPublic_OtherDevice_WeightDataPrepare(pData,pDataInt16,ModbusAdd_Slave_1);
		//judge if not need send
		ret = judgeWeightDataIfNotNeedSend(pData,pDataPre,chanel_len);			
	}
	//
	return ret;
}


UINT8 preHelpData_New(T5LType *pSdwe)
{
	UINT8 localStatus = 0;

	INT32 *pData = pSdwe->screenCycle.pDataPre;//&g_i32DataBuff[0];
	INT16 *pColorOtherCh = pSdwe->screenCycle.pColorOtherCh;//&g_i16ColorOtherChanel[0];
	//
	float *sortWeight = &g_i16HelpDataSortLarger[0];
	INT16 *sortArry = &g_i16HelpDataChnSort[0];
	INT16 i16Minus = 0 , minPos_i = 0xff ,minPos_j=0xff;
	UINT8 help_i = 0;
	//
	INT16 *pOutData = pSdwe->screenCycle.pHelp;//&g_i16HelpDataBuffLarger[0];
	//
	UINT8 sortArry_num = 0 ,chn_i = 0 , chn_j = 0;

	//2.use pColor ==  LED_COLOR_NONE , to triger need judge weight
	sortArry_num = 0 ;
	for(chn_i=0;chn_i<HX711_CHANEL_NUM;chn_i++)
	{
		if(T5L_CHANEL_WEIGHT_NOT_EQUAL == pColorOtherCh[chn_i])
		{
			sortWeight[sortArry_num] = pData[chn_i];
			sortArry[sortArry_num] = chn_i;
			sortArry_num++;
		}
	}
	//==sort weight : from min to max
	if(sortArry_num > 1)
	{	
		BubbleSort((float *)sortWeight,sortArry,sortArry_num);
	}
	//
	for(help_i=0;help_i < DIFF_JUDGE_GROUP_NUM_SLAVE1;)
	{
		i16Minus = 0x7FFF ;
		minPos_i = 0xff;
		minPos_j = 0xff;
		//find chn_i
		for(chn_i=0;chn_i<sortArry_num;chn_i++)
		{
			if((sortWeight[chn_i] >= gSystemPara.zeroRange) || 
				(sortWeight[chn_i] <= -gSystemPara.zeroRange) )
			{
				//find chn_j
				for(chn_j=(chn_i+1);chn_j<sortArry_num;chn_j++)
				{
					//if chn_j larger than zero
					if((sortWeight[chn_j] >= gSystemPara.zeroRange) || 
						(sortWeight[chn_j] <= -gSystemPara.zeroRange) )
					{
						break;
					}
				}
				//==out the least value of diff 
				if((chn_i < sortArry_num) && (chn_j < sortArry_num))
				{
					if((sortWeight[chn_j] - sortWeight[chn_i]) < i16Minus)
					{
						i16Minus = sortWeight[chn_j] - sortWeight[chn_i];
						minPos_j = chn_j;
						minPos_i = chn_i;
					}
				}
			}	
		}
		//==qunene the least value of diff
		if((i16Minus != 0x7FFF) && (0xff != minPos_i) && (0xff != minPos_j))
		{
			if(help_i < DIFF_JUDGE_GROUP_NUM_SLAVE1)
			{
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 0] = sortArry[minPos_j]+1;
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 1] = sortArry[minPos_i]+1;
				pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 2] = i16Minus;
				help_i++;
			}
			sortWeight[minPos_j] = 0 ;
			sortWeight[minPos_i] = 0 ;
		}
		else
		{
			break;
		}
	}
	//==the remain help data set to 0
	for(;help_i<(DIFF_JUDGE_GROUP_NUM_SLAVE1);help_i++)
	{
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 0] = 0;
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 1] = 0;
		pOutData[DIFF_JUDGE_DATA_NUM_SLAVE1 * help_i + 2] = 0;
	}
	
	return localStatus;
}

void preCurrentDeviceWeightData_CycleData(T5LType *pSdwe,UINT8 chanel_len)
{
	float weight;
	enumHX711ChanelType chanel = HX711Chanel_1;
	//
	for(chanel = HX711Chanel_1 ; chanel < HX711_CHANEL_NUM ; chanel++)
	{
		//get current device weight
		weight = hx711_getWeight(chanel);
		//uint handle of g/ml
		if((0 != gSystemPara.mlYugBiLv) && (SYS_ML_G_WAS_ML == gSystemPara.uint))
		{
			weight *= 1000;
			weight /= gSystemPara.mlYugBiLv;
		}
		//judge if not have decimal
		if(0 == gSystemPara.xiaoShuXianShi)
		{
			pSdwe->screenCycle.pData[chanel] = (INT32)(weight+0.5f);
		}
		else
		{
			pSdwe->screenCycle.pData[chanel] = (INT32)(10*weight);
		}
		//		
		pSdwe->screenCycle.pDataSendToDiWen[2*chanel + 0] = (pSdwe->screenCycle.pData[chanel] >> 16) & 0xFFFF;
		pSdwe->screenCycle.pDataSendToDiWen[2*chanel + 1] = (pSdwe->screenCycle.pData[chanel] >> 0 ) & 0xFFFF;
	}
}
void preOtherDeviceWeightData_CycleData(T5LType *pSdwe,enumModbusAddType modbusSlaveId)
{
	UINT8 offset = 0;
	enumHX711ChanelType chanel = HX711Chanel_1;
	//
	if(modbusSlaveId < ModbusAdd_Slave_Max)
	{
		for(chanel = HX711Chanel_1 ; chanel < HX711_CHANEL_NUM ; chanel++)
		{
			offset = HX711_CHANEL_NUM*(modbusSlaveId - ModbusAdd_Master) + chanel;	
			pSdwe->screenCycle.pData[offset] = (INT32)(GetFloatBalancingModelData(modbusSlaveId,chanel));
			//INT32 data to INT16 data
			pSdwe->screenCycle.pDataSendToDiWen[2*offset + 0] = (pSdwe->screenCycle.pData[offset] >> 16) & 0xFFFF;
			pSdwe->screenCycle.pDataSendToDiWen[2*offset + 1] = (pSdwe->screenCycle.pData[offset] >> 0 ) & 0xFFFF;
		}		
	}
}
UINT8 judgeWeightDataIfNotNeedSend_CycleData(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 ret = FALSE , offset = 0;
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		for(offset = 0 ; offset < chanel_len ; offset++)
		{
			if(pSdwe->screenCycle.pData[offset] != pSdwe->screenCycle.pDataPre[offset])
			{
				pSdwe->screenCycle.pDataPre[offset] = pSdwe->screenCycle.pData[offset];
				ret = TRUE ;
			}
		}
	}
	return ret;
}
UINT8 preWeightDataAndJudgeIfNeedSend_CycleData(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 ret = FALSE;
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		switch(gSystemPara.isCascade)
		{
			case 0:
				//master local data
				preCurrentDeviceWeightData_CycleData(pSdwe,chanel_len);
			break;
 
			case ModbusAdd_Master:
				preCurrentDeviceWeightData_CycleData(pSdwe,chanel_len);
				//ModbusAdd_Slave_1 recv data
				preOtherDeviceWeightData_CycleData(pSdwe,ModbusAdd_Slave_1);
			break;
 
			case ModbusAdd_Slave_1:

			break;
 
			default :
			break;
		}
 
		//judge if not need send
		ret = judgeWeightDataIfNotNeedSend_CycleData(pSdwe,chanel_len);			
	}
	//
	return ret;
}



UINT8 preHelpDataAndJudgeIfNeedSend_CycleData(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 localStatus = FALSE;
	UINT8 offset = 0;
	//T5LType *pSdweSmaller = &g_T5LCtx[ScreenIndex_Smaller];

	UINT8 i = 0;
	//pre help data
	for(offset = 0 ; offset < DIFF_TO_DIWEN_DATA_LEN ; offset++)
	{
		pSdwe->screenCycle.pHelp[offset] = g_i16HelpDataBuff[offset];
	}

	//check if need send
	for(i=0;i<DIFF_TO_DIWEN_DATA_LEN;i++)
	{
		if(pSdwe->screenCycle.pHelpPre[i] != pSdwe->screenCycle.pHelp[i])
		{
			pSdwe->screenCycle.pHelpPre[i] = pSdwe->screenCycle.pHelp[i];
			localStatus = TRUE;
		}
	}
	
	//
	return localStatus;
}

void preColorData_New(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 release = FALSE;
	UINT8 sortArry_num = 0 ,chn_self = 0 , chn_other = 0 , chn_i = 0;
	//weight use pDataPre
	INT32 *pData = pSdwe->screenCycle.pDataPre;
	//color data
	INT16 *pColor = pSdwe->screenCycle.pColor;
	//INT16 *pColorPre = pSdwe->screenCycle.pColorPre;
	INT16 *pColorOtherCh = pSdwe->screenCycle.pColorOtherCh;
	//sort need data
	float *sortWeight = pSdwe->screenCycle.pSortWeight;//&g_fDataBuffCaculate[0];
	INT16 *sortArry = pSdwe->screenCycle.pSortArry;//&g_i16OtherChanelCaculate[0];
	//
	UINT8 compare_i = 0 ;
	//
	float judge_errRange = gSystemPara.errRange,judge_zeroRange = gSystemPara.zeroRange;
 
	enumLedColorType colorVld = LED_COLOR_NONE;
 
	//有小数点时，判断范围乘以10
	if(1 == gSystemPara.xiaoShuXianShi)
	{
		judge_errRange = gSystemPara.errRange*10;
		judge_zeroRange = gSystemPara.zeroRange*10;
	}
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		//1.judge the equal chanle again
		for(chn_i=0;chn_i<chanel_len;chn_i++)
		{
			release = FALSE;//dit not release channel display color
			//
			chn_self = chn_i;//self chanel
			chn_other = (UINT8)pColorOtherCh[chn_self];//other chanel
			//other chanel matched
			if(chn_other < chanel_len)
			{
				if(((pData[chn_self] - pData[chn_other]) >= -judge_errRange) && ((pData[chn_self] - pData[chn_other]) <= judge_errRange) )
				{
					//self and other chanel weight equal again
					if(((pData[chn_self] > -judge_zeroRange) && (pData[chn_self] < judge_zeroRange)) ||	
						((pData[chn_other] > -judge_zeroRange) && (pData[chn_other] < judge_zeroRange)))
					{
						//1.3 someone weight at zero range , need release
						release = TRUE;
					}
					else
					{
						if(pColor[chn_self] != pColor[chn_other])
						{
							//1.2 weight equal but color not equal or someone was NONE color, need release
							release = TRUE;
						}
					}
				}
				else
				{
					//1.1 weight not equal again , need release
					release = TRUE;
				}
			}
			else
			{
				//1.0 other channel not match , need release
				release = TRUE;
			}
 
			//if need release , must release self and other
			if(TRUE == release)
			{
				//clear the self other chanel = Invalid
				if(T5L_CHANEL_WEIGHT_NOT_EQUAL != pColorOtherCh[chn_self])
				{
					pColorOtherCh[chn_self] = T5L_CHANEL_WEIGHT_NOT_EQUAL;
				}
				//clear the other chanel = Invalid
				if((chn_other < T5L_MAX_CHANEL_LEN) && (T5L_CHANEL_WEIGHT_NOT_EQUAL != pColorOtherCh[chn_other]))
				{
					pColorOtherCh[chn_other] = T5L_CHANEL_WEIGHT_NOT_EQUAL;
				}
				//release self color
				if(LED_COLOR_NONE != pColor[chn_self])
				{
					releaseSysColor((enumLedColorType)pColor[chn_self]);//release used color
					LedDataSet((enumLedSeqType)chn_self, LED_COLOR_NONE);//LED : display
					pColor[chn_self] = LED_COLOR_NONE;//clear chn_self color
				}
				//release other color
				if((chn_other < T5L_MAX_CHANEL_LEN) && (LED_COLOR_NONE != pColor[chn_other]))
				{
					releaseSysColor((enumLedColorType)pColor[chn_other]);//release used color
					LedDataSet((enumLedSeqType)chn_other, LED_COLOR_NONE);//LED : display
					pColor[chn_other] = LED_COLOR_NONE;//clear chn_other color
				}
			}
		}
		//2.use pColor ==  LED_COLOR_NONE , to triger need judge weight
		sortArry_num = 0 ;
		for(chn_i=0;chn_i<chanel_len;chn_i++)
		{
			//no color and weight was need match outof zero
			if((LED_COLOR_NONE == pColor[chn_i]) &&
			((pData[chn_i] < -judge_zeroRange) || (pData[chn_i] > judge_zeroRange)))
			{
				sortWeight[sortArry_num] = pData[chn_i];
				sortArry[sortArry_num] = chn_i;
				sortArry_num++;
			}
		}
		//3.use weight Sort
		BubbleSort(sortWeight,sortArry,sortArry_num);
		//4.user sorted weight , set color
		for(compare_i=0;compare_i<(sortArry_num-1);compare_i++)
		{
			chn_self = sortArry[compare_i];
			chn_other = sortArry[compare_i+1];
			if(( chn_self < chanel_len) && ( chn_other < chanel_len) )
			{
				//is equal
				if( ((pData[chn_self] < -judge_zeroRange) || (pData[chn_self] > judge_zeroRange)) &&
					((pData[chn_other] < -judge_zeroRange) || (pData[chn_other] > judge_zeroRange)) &&
					(((pData[chn_self] - pData[chn_other]) >= -judge_errRange) && ((pData[chn_self] - pData[chn_other]) <= judge_errRange) ) )
				{
					//screen : set the same color
					colorVld = getSysColorWhichUsable();
					pColor[chn_self] = colorVld;
					pColor[chn_other] = colorVld;
					//otherChn recode
					pColorOtherCh[chn_self] = chn_other;
					pColorOtherCh[chn_other] = chn_self;
					
					//screen : voice pritf
					if(LED_COLOR_NONE != colorVld)//bug : case weight equal but colot was LED_COLOR_NONE
					{
						sdwe_VoicePrintfPush((tT5LVoinceType)(chn_self+1),(tT5LVoinceType)(chn_other+1));
					}
					//LED : display
					LedDataSet((enumLedSeqType)chn_self, colorVld);
					LedDataSet((enumLedSeqType)chn_other, colorVld);
 
					//
					compare_i++;//!!!!! must add it !!!!!
				}
			}
		}
	}
}
UINT8 judgeWeightColorIfNotNeedSend_New(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 ret = FALSE , offset = 0;
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		for(offset = 0 ; offset < chanel_len ; offset++)
		{
			if(pSdwe->screenCycle.pColor[offset] != pSdwe->screenCycle.pColorPre[offset])
			{
				pSdwe->screenCycle.pColorPre[offset] = pSdwe->screenCycle.pColor[offset];
				ret = TRUE ;
			}
		}
	}
	return ret;
} 
UINT8 preColorDataAndJudgeIfNeedSend_CycleData(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 ret = FALSE , offset = 0;
	T5LType *pSdweSmaller = &g_T5LCtx[ScreenIndex_Smaller];
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		switch(gSystemPara.isCascade)
		{
			case 0:
			case ModbusAdd_Master:
				//preColorData_New(pSdwe,chanel_len);
				for(offset = 0 ; offset < chanel_len ; offset++)
				{
					pSdwe->screenCycle.pColor[offset] = pSdweSmaller->screenCycle.pColor[offset];
				}
			break;
 
			case ModbusAdd_Slave_1:
			break;
 
			default :
			break;
		}
		//2.updata pColorPre from pColor
		ret = judgeWeightColorIfNotNeedSend_New(pSdwe,chanel_len);
	}
	return ret;
}

#endif



//the Tx handle  of all screen
void screenT5L_TxFunction(ScreenHandleType  *screenHandlePtr)
{
	UINT8 i = 0;
	T5LType *t5lCtx = screenHandlePtr->Ctx;
	for( i = 0 ; i < screenHandlePtr->sendScreenHadlleNum ; i++)
	{
		if(TRUE == screenHandlePtr->sendScreenHadlleCtx[i].func(t5lCtx))
		{
			break;
		}
	}	
}
 
//the Rx handle of all screen
void screenT5L_RxFunction(ScreenHandleType  *screenHandlePtr)
{
	UINT8 needStore = FALSE ;
	UINT16 regLen = 0 , reg_i = 0 , regAdd = 0 , regData = 0;
	UINT16 varLen = 0 , var_i = 0 , varAdd = 0 , varData = 0;
	T5LType *t5lCtx=screenHandlePtr->Ctx;
	//
	if(TRUE == t5lCtx->RxFinishFlag)
	{
		//A5 5A
		if((T5L_RX_FUN_HEAD1 == t5lCtx->rxData[cmdPosHead1]) && (T5L_RX_FUN_HEAD2 == t5lCtx->rxData[cmdPosHead2]))
		{
			//2 head + 1 len + last 3(cmd:1 add:1-2 data:1-n) data 
			if(( t5lCtx->RxLength >= 6 ) && ((t5lCtx->RxLength-3) == t5lCtx->rxData[cmdPosDataLen]) )
			{
				switch(t5lCtx->rxData[cmdPosCommand])
				{
					case cmdWriteSWDERegister:
					break;
					case cmdReadSWDERegister://each register is 8 bits
						//send:A5 5A 03 cmdReadSWDERegister XX YY (XX:address YY:len)
						//rec :A5 5A (03+YY) cmdReadSWDERegister XX YY DD^YY (XX:address YY:len DD:data)
						//if((t5lCtx->RxLength-3) == t5lCtx->rxData[cmdPosDataLen])//remove 2 head + 1 data len
						{
							regLen = t5lCtx->rxData[cmdPosReadRegAskLen];
							if(((t5lCtx->rxData[cmdPosDataLen]-3)/1) == regLen)
							{
								regAdd = 0 ;
								regAdd = t5lCtx->rxData[cmdPosRegAddress];
								//mult varible deal
								for(reg_i = 0 ; reg_i < regLen ;reg_i++)
								{
									regData = 0 ;
									regData = t5lCtx->rxData[cmdPosRegData+reg_i];
									//deal
									needStore |= sdweAskRegData(screenHandlePtr,(regAdd+reg_i),regData);
								}
							}
						}
					break;
					case cmdWriteSWDEVariable:
					break;
					case cmdReadSWDEVariable://each variable is 16 bits
						//send:A5 5A 04 cmdReadSWDEVariable XX XX YY (XX XX:address YY:len)
						//rec :A5 5A (04+2*YY) cmdReadSWDEVariable XX XX YY DD DD^YY (XX XX:address YY:len DD DD:data)
						//if((t5lCtx->RxLength-3) == t5lCtx->rxData[cmdPosDataLen])//remove 2 head + 1 data len
						{
							varLen = t5lCtx->rxData[cmdPosReadVarAskLen];
							if(((t5lCtx->rxData[cmdPosDataLen]-4)/2) == varLen)
							{
								varAdd = 0 ;
								varAdd = t5lCtx->rxData[cmdPosVarAddress1];					
								varAdd <<= 8 ;
								varAdd &= 0xff00;
								varAdd += t5lCtx->rxData[cmdPosVarAddress2];
								//mult varible deal
								for(var_i = 0 ; var_i < varLen ;var_i++)
								{
									varData = 0 ;
									varData = t5lCtx->rxData[cmdPosVarData1+2*var_i+0];					
									varData <<= 8 ;
									varData &= 0xff00;
									varData += t5lCtx->rxData[cmdPosVarData1+2*var_i+1];
									//deal
									needStore |= sdweAskVaribleData(screenHandlePtr,(varAdd+var_i),varData);
								}
							}
						}						
					break;
					default:
					break;
				}
			}
 
			//store in flash
			if(t5lCtx->CurTick > 5000)
			{
				if(0 != (DMG_TRIGER_SAVE_SECOTOR_1&needStore))
				{
					storeSysDataToFlash();
					storeSysDataToFlash_3030();//Flash Erase Times Manager
					screenHandlePtr->Ctx->needStore = 0;
				}
				//store in flash
				else if(0 != (DMG_TRIGER_SAVE_SECOTOR_2&needStore))
				{
					storeSysDataToFlash_3030();
					screenHandlePtr->Ctx->needStore = 0;
				}
			}
		}
		//
		t5lCtx->RxFinishFlag = FALSE;
	}
}

//================================================================================================
//=========================================[大小屏主函数]==========================================
//================================================================================================
void sreenT5L_MainFunction(void)
{
	//update self CurTick
	g_ScreenHandle[ScreenIndex_Smaller].Ctx->CurTick++;
	g_ScreenHandle[ScreenIndex_Larger].Ctx->CurTick++;
 
	//handle rx data from SDWE
	screenT5L_RxFunction(&g_ScreenHandle[ScreenIndex_Smaller]);
	screenT5L_RxFunction(&g_ScreenHandle[ScreenIndex_Larger]);
	
	//prepare data and send to SDWE
	screenT5L_TxFunction(&g_ScreenHandle[ScreenIndex_Smaller]);//WeightAndColorAndVoice was handle at here
	screenT5L_TxFunction(&g_ScreenHandle[ScreenIndex_Larger]);
 
	//slave data valid
	setModbusDataValid(SLAVE_DATA_VALID);
}
