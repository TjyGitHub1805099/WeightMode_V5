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


UINT8 g_u8Read00A1_Data = 0XFF;

//=============================================15.6寸屏的=============================================

static INT16 int16_ChangeDisplayPosition_Larger = 0 ,int16_ChangeDisplayPosition_i_Larger = 0 ,int16_ChangeDisplayPosition_switch_Larger =0;
static INT16 describlePoint_add_Larger = 0x9000,*describlePoint_data_Larger,describlePoint_len_Larger = 1;

//=============================================8.8寸屏的=============================================
//屏幕的描述指针：显示托盘的重量控件
static INT16 int16_ChangeDisplayPosition = 0 ,int16_ChangeDisplayPosition_i = 0 ,int16_ChangeDisplayPosition_switch =0;
static INT16 describlePoint_add = 0x9000,*describlePoint_data,describlePoint_len = 1;


/*******************************************************************************
 * Functions
 ******************************************************************************/
//帮助信息统一处理
UINT8 screenT5L_HelpDataMainFunction(T5LType *pSdwe);


//==sdwe->mcu rx callback ,not used
void app_uart_extern_msg_packet_process( UartDeviceType *pUartDevice )
{
	//not used
}

//==sdwe initial
static void screenT5L_Init(T5LType *t5lCtx)
{
	UINT8 i = 0 ;
	//
	t5lCtx->readSdweInit = FALSE;


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
void allScreenCtx_Init(void)
{
	screenT5L_Init(&g_T5LCtx[ScreenIndex_Smaller]);
	screenT5L_Init(&g_T5LCtx[ScreenIndex_Larger]);
}

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

//========================================================================================check:20210619
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

//==write varible data to SDWE thought UART
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

//==write data to screen , have delay contrl
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

//if sreen calibtion point triger
UINT8 pointTrigerDeal(T5LType *pSdwe)
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
#if 0
void storeSysPara_3030(UINT16 varAdd, UINT16 varData)
{
	switch(varAdd)
	{
		case DMG_FUNC_SET_UNIT_ADDRESS://		(0X1000)//0x1000
			gSystemPara.uint = varData;
		break;
		case DMG_FUNC_SET_MIN_RANGE_ADDRESS://		(0X100A)//0x100A
		break;
		case  DMG_FUNC_SET_MAX_RANGE_ADDRESS://		(0X100B)//0x100B
		break;
		case DMG_FUNC_SET_ERR_RANGE_ADDRESS://		(0X100C)//0x100C
		break;
		case  DMG_FUNC_SET_isCascade_ADDRESS://		(0X100D)//0x100D
		break;
		case  DMG_FUNC_SET_isLedIndicate_ADDRESS://	(0X100E)//0x100E
		break;
		case  DMG_FUNC_SET_COLOR_START_ADDRESS://	(0X100F)//0x100F
		break;
		case DMG_FUNC_SET_COLOR_END_ADDRESS://		(0X1012)//0x1012
		break;
		case DMG_FUNC_SET_ZERO_RANGE_ADDRESS://		(0X1013)//0x1013
		break;
		default:
		break;
	}

}
#endif


UINT8 screenRxHandle_Version(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_SYS_VERSION_GET_ADD == pSdwe->SetAdd)
	{
		pSdwe->sdwePowerOn = TRUE;//if recived version , indicate allready power on
		t5lDisPlayDataClear();
		matched = TRUE;
	}
	return matched;
}
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
UINT8 screenRxHandle_SysPara(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if((pSdwe->SetAdd >= DMG_FUNC_SET_UNIT_ADDRESS)&&(pSdwe->SetAdd <= (DMG_FUNC_DIWEN_DAPING_ADDRESS)))
	{	
		matched = TRUE;
		switch(pSdwe->SetAdd)
		{
			case DMG_FUNC_SET_UNIT_ADDRESS:		//		(0X1000)//0x1000
				gSystemPara.uint = pSdwe->SetData;/**< 单位 */
			break;
			case DMG_FUNC_SET_MIN_RANGE_ADDRESS://		(0X100A)//0x100A
				gSystemPara.minWeight = pSdwe->SetData;/**< 最小量程 */
			break;
			case  DMG_FUNC_SET_MAX_RANGE_ADDRESS://		(0X100B)//0x100B
				gSystemPara.maxWeight = pSdwe->SetData;/**< 最大量程 */
			break;
			case  DMG_FUNC_SET_ERR_RANGE_ADDRESS://		(0X100C)//0x100C
				gSystemPara.errRange = pSdwe->SetData;/**< 误差范围 */
			break;
			case  DMG_FUNC_SET_isCascade_ADDRESS://		(0X100D)//0x100D
				gSystemPara.isCascade = pSdwe->SetData;/**< 是否级联 */
			break;
			case  DMG_FUNC_SET_isLedIndicate_ADDRESS://	(0X100E)//0x100E
				gSystemPara.isLedIndicate = pSdwe->SetData;/**< 是否LED指示 */
			break;
			case  DMG_FUNC_SET_ZERO_RANGE_ADDRESS://	(0X1013)//0x1013
				gSystemPara.zeroRange = pSdwe->SetData;/**< 零点范围 */
			break;
			case DMG_FUNC_SET_SCREEN_LIGHT_ADDRESS://	(0X1014)//0x1014
				gSystemPara.ScreenLight = pSdwe->SetData;/**< 屏幕背光亮度 */
				pSdwe->sdweFreshScreenLight = TRUE;
			break;
			case DMG_FUNC_SET_VOICE_NUM_TOUCH_ADDRESS://(0X1015)//0x1015
				gSystemPara.VoiceNumTouch = pSdwe->SetData;/**< 语音大小 触控*/
			break;
			case DMG_FUNC_SET_VOICE_NUM_ADDRESS://		(0X1016)//0x1016
				gSystemPara.VoiceNum = pSdwe->SetData;/**< 语音大小 */
			break;				
			case DMG_FUNC_SET_VOICE_SWITCH_ADDRESS://	(0X1017)//0x1017
				gSystemPara.ScreenVoiceSwitch = pSdwe->SetData;/**< HX711	语音开关 */ 
			break;
			case DMG_FUNC_SET_CAST_SWITCH_ADDRESS://	(0X1018)//0x1018
				gSystemPara.ScreenCastMode = pSdwe->SetData;/**< HX711	级联显示模式 */
			break;
			case DMG_FUNC_DIWEN_XIAOSHU_ADDRESS:/**< 小数显示 0x101C*/
				gSystemPara.xiaoShuXianShi = pSdwe->SetData;
				pSdwe->sdweChangeDescriblePoint = TRUE;
			break;
			case DMG_FUNC_DIWEN_BILV_ADDRESS:	/**< ml与g比率 0x101D*/
				gSystemPara.mlYugBiLv = pSdwe->SetData;
			break;
			case DMG_FUNC_DIWEN_DAPING_ADDRESS:/**< 大屏显示 0x101E*/
				gSystemPara.daPinXianShi = pSdwe->SetData;
			break;
			default:
				if((pSdwe->SetAdd >= DMG_FUNC_SET_COLOR_START_ADDRESS)&&(pSdwe->SetAdd <= (DMG_FUNC_SET_COLOR_END_ADDRESS)))
				{
					gSystemPara.userColorSet[pSdwe->SetAdd-DMG_FUNC_SET_COLOR_START_ADDRESS] = pSdwe->SetData;/**< 颜色1~4 */
				}
			break;
		}
		//
		pSdwe->needStore |= DMG_TRIGER_SAVE_SECOTOR_2 ;
	}
	return matched;
}
UINT8 screenRxHandle_JumpToBalancingClearnPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_Balancing_CLEARPAGE_SET_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_Balancing_CLEARPAGE_SET_VALUE == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpBalancing_cleanpagee = TRUE;
		}
	}
	return matched;
}
UINT8 screenRxHandle_JumpToBalancingHomePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_Balancing_HOME_SET_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_Balancing_HOME_SET_VALUE == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpBalancing_home = TRUE;
		}
	}
	return matched;
}
UINT8 screenRxHandle_JumpToBalancingPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_Balancing_SET_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_Balancing_SET_VALUE == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpBalancing = TRUE;
		}
	}
	return matched;
}
UINT8 screenRxHandle_CalibrateChanelSet(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_SET_CHANEL_NUM == pSdwe->SetAdd)
	{
		matched = TRUE;
		pSdwe->ResetTrigerValid = FALSE;/*重新校准取消*/
		if(pSdwe->CalibrateChanel != pSdwe->SetData)
		{
			pSdwe->sdweChanelChanged = TRUE;
			if(pSdwe->SetData <= HX711_CHANEL_NUM)
			{
				pSdwe->CalibrateChanel = pSdwe->SetData;//chanel
			}
		}
	}
	return matched;
}
UINT8 screenRxHandle_CalibrateAddressSet(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_RESET_CALIBRATION_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_RESET_CALIBRATION_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweResetTriger = TRUE;
			pSdwe->ResetTrigerValid = TRUE;
			clearLocalCalibrationRecordData(pSdwe->CalibrateChanel);
			clearLocalCalibrationKAndBAndSample(pSdwe->CalibrateChanel);
		}
	}
	return matched;
}
UINT8 screenRxHandle_JumpToCalibrateOrActivePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_JUNPTO_CALIBRATION_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_JUNPTO_CALIBRATION_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpToCalitrationPage = TRUE;//jump to page 53
		}
		else if(DMG_FUNC_JUNPTO_ACTIVE_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpActivePage = TRUE;//jump to page 56
		}
	}
	return matched;
}
UINT8 screenRxHandle_JumpToSysParaPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(DMG_FUNC_JUNPTO_SYSPAR_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_JUNPTO_SYSPAR_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweJumpToSysParaPage = TRUE;//jump to page 52
		}
	}
	return matched;
}
UINT8 screenRxHandle_RemoveWeightTriger(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	T5LType *pSdweSmaller = &g_T5LCtx[ScreenIndex_Smaller];
	if(DMG_FUNC_REMOVE_WEIGHT_ADDRESS == pSdwe->SetAdd)
	{
		matched = TRUE;
		if(DMG_FUNC_REMOVE_WEIGHT_VAL == (UINT16)pSdwe->SetData)
		{
			pSdwe->sdweRemoveWeightTriger = TRUE;
			pSdweSmaller->sdweRemoveWeightTriger = TRUE;
			//
			setModbusSelfRemoveFlag(TRUE);
		}
	}
	return matched;
}
UINT8 screenRxHandle_CalibratePointSet(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	UINT8 i = 0 , point = 0;
	INT32 weight=0;
	if((pSdwe->SetAdd >= DMG_FUNC_SET_CHANEL_POINT_ADDRESS)&&(pSdwe->SetAdd < (DMG_FUNC_SET_CHANEL_POINT_ADDRESS + CHANEL_POINT_NUM )))
	{
		matched = TRUE;
		//
		pSdwe->needStore |= DMG_TRIGER_SAVE_SECOTOR_1 ;
		//point
		pSdwe->CalibratePoint = (pSdwe->SetAdd -DMG_FUNC_SET_CHANEL_POINT_ADDRESS) ;//point
		point = pSdwe->CalibratePoint;
		pSdwe->CalibratePointArry[point] = pSdwe->SetData;
		//weight
		weight = pSdwe->SetData;
	
		if(0 == pSdwe->CalibrateChanel)//all chanel point weight value set
		{
			for(i=0;i<HX711_CHANEL_NUM;i++)//8通道
			{
				setSampleWeightValue(i,point,weight);
				pointWeightTrigerDataSet(i,point,weight);
			}
			pointWeightTrigerDataSet(i,point,weight);
		}
		else//single chanel point weight value set
		{
			setSampleWeightValue((pSdwe->CalibrateChanel-1),point,weight);
			pointWeightTrigerDataSet((pSdwe->CalibrateChanel-1),point,weight);
		}
	}
	return matched;
}
UINT8 screenRxHandle_CalibratePointSampleAndSet(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	UINT8 i = 0 , point = 0;
	INT32 avgSampleValue=0;
	if((TRUE == pSdwe->ResetTrigerValid)&&(pSdwe->SetAdd >= DMG_FUNC_SET_CHANEL_POINT_TRIG_ADDRESS)&&(pSdwe->SetAdd < (DMG_FUNC_SET_CHANEL_POINT_TRIG_ADDRESS + CHANEL_POINT_NUM )))
	{
		matched = TRUE;
		//value = 0x12fe
		if(DMG_FUNC_SET_CHANEL_POINT_TRIG_VAL == pSdwe->SetData)
		{
			//	
			pSdwe->sdwePointTriger = TRUE;
			//
			pSdwe->needStore |= DMG_TRIGER_SAVE_SECOTOR_1 ;
			point = ( pSdwe->SetAdd - DMG_FUNC_SET_CHANEL_POINT_TRIG_ADDRESS );
			
			if(0 == pSdwe->CalibrateChanel)//all chanel caculate	K & B
			{
				//avgSampleValue = hx711_getAvgSample(pSdwe->CalibrateChanel)/512;
				for(i=0;i<HX711_CHANEL_NUM;i++)//eight chanel
				{
					avgSampleValue = hx711_getAvgSample((enumHX711ChanelType)i)/512;
					trigerCalcKB(i,point);
					pointTrigerDataSet(i,point,1,avgSampleValue);
				}
				pointTrigerDataSet(HX711_CHANEL_NUM,point,1,avgSampleValue);
				
			}
			else if(HX711_CHANEL_NUM >= pSdwe->CalibrateChanel)//single chanel caculate  K & B
			{
				avgSampleValue = hx711_getAvgSample((enumHX711ChanelType)(pSdwe->CalibrateChanel-1))/512;
				trigerCalcKB((pSdwe->CalibrateChanel-1),point);
				pointTrigerDataSet((pSdwe->CalibrateChanel-1),point,1,avgSampleValue);
			}
			//sdwePointTrigerUpdata(point,1,avgSampleValue);
		}
	}
	return matched;
}
UINT8 screenRxHandle_VoicePrintfStatusFromScreen(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(pSdwe->SetAdd == DMG_SYS_STATUS_OF_VOICE_PRINTF_00A1)
	{
		matched = TRUE;
		g_u8Read00A1_Data = pSdwe->SetData;
	}
	return matched;
}
UINT8 screenRxHandle_SystemReset(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(pSdwe->SetAdd == SYS_SOFTWARE_RESET_ADD)
	{
		if(SYS_SOFTWARE_RESET_VLU == pSdwe->SetData)
		{
			HAL_NVIC_SystemReset();
		}
	}
	return matched;
}
//================================================================================================
//接收到小屏幕的数据处理
screenRxTxHandleType screenRxHandle[SCREEN_RX_HANDLE_TOTAL_NUM]=
{
	//priority index func_add
	{0,	0, &screenRxHandle_Version},//开机时MCU获取到屏幕版本时，代表屏幕可以正常通讯
	{0,	1, &screenRxHandle_SysPassWord},//密码管理
	{0,	2 ,&screenRxHandle_SysPara},//系统参数管理
	{0,	3, &screenRxHandle_JumpToBalancingClearnPage},//配平清爽界面
	{0,	4, &screenRxHandle_JumpToBalancingHomePage},//配平主界面界面 ， 它与清爽界面来会切换，当点击屏幕时
	{0,	5, &screenRxHandle_JumpToBalancingPage},//配平界面 ， 其他界面跳回配平界面时用
	{0,	6, &screenRxHandle_CalibrateChanelSet},//校准界面 ，通道号设置
	{0,	7 ,&screenRxHandle_CalibrateAddressSet},//校准界面 ，地址设置
	{0,	8 ,&screenRxHandle_JumpToCalibrateOrActivePage},//跳转校准界面
	{0,	9, &screenRxHandle_JumpToSysParaPage},//跳转系统参数设置界面
	{0,	10,&screenRxHandle_RemoveWeightTriger},//去皮事件触发
	{0,	11,&screenRxHandle_CalibratePointSet},//校准界面，校准点参考值设置
	{0,	12,&screenRxHandle_CalibratePointSampleAndSet},//校准界面，校准点采样及设置
	{0,	13,&screenRxHandle_VoicePrintfStatusFromScreen},//屏幕语音控制后状态返回
	{0,	14,&screenRxHandle_SystemReset},//屏幕语音控制后状态返回
};

//接收到大屏幕的数据处理
screenRxTxHandleType screenLargerRxHandle[SCREEN_LARGER_RX_HANDLE_TOTAL_NUM]=
{
	//priority index func_add
	{0,	0, &screenRxHandle_Version},//开机时MCU获取到屏幕版本时，代表屏幕可以正常通讯
	{0,	1, &screenRxHandle_RemoveWeightTriger},//去皮事件触发
};

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

//================================================================================================
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

//================================================================================================
//if need jump to startup page 
UINT8 jumpToStartUpPage(T5LType *pSdwe,INT16 curPage)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,1};//1 page
	pageChangeOrderAndData[1] = curPage;
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}
//if need jump to active page 
UINT8 jumpToActivePage(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,56};//56 page
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}
//if need jump to Syspara page 
UINT8 jumpToSysparaPage(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,52};//52 page
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}

//if need jump to active page 
UINT8 jumpToBalancingPage(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,DMG_FUNC_Balancing_6_PAGE};//49 page

	//20220119 changed
	switch(gSystemPara.isCascade)
	{
		case 0://single module , not cascade
		case ModbusFuncA_Master://FuncA module
		case ModbusFuncA_Slave://FuncA module
			pageChangeOrderAndData[1] = DMG_FUNC_Balancing_6_PAGE;
		break;
		case ModbusAdd_Master:
		case ModbusAdd_Slave_1:
			if(0 == gSystemPara.ScreenCastMode)
			{
				pageChangeOrderAndData[1] = DMG_FUNC_Balancing_12_PAGE;
			}
			else
			{
				pageChangeOrderAndData[1] = DMG_FUNC_Help_PAGE;
			}
		break;
		default :
		break;
	}

	pageChangeOrderAndData[1] = DMG_FUNC_Balancing_6_PAGE;
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}
//if need jump to active page 
UINT8 jumpToBalancingHomePage(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,DMG_FUNC_Balancing_6_HOME_PAGE};

	//20220119 changed
	switch(gSystemPara.isCascade)
	{
		case 0://single module , not cascade
		case ModbusFuncA_Master://FuncA module
		case ModbusFuncA_Slave://FuncA module
			pageChangeOrderAndData[1] = DMG_FUNC_Balancing_6_HOME_PAGE;
		break;
		case ModbusAdd_Master:
		case ModbusAdd_Slave_1:
			pageChangeOrderAndData[1] = DMG_FUNC_Balancing_12_HOME_PAGE;
		break;
		default :
		break;
	}

	pageChangeOrderAndData[1] = DMG_FUNC_Balancing_6_HOME_PAGE;
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}
//if need jump to active page 
UINT8 jumpToBalancingCleanPage(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,DMG_FUNC_Balancing_6_PAGE};

	if(TRUE == gSystemPara.isCascade)
	{
		//pageChangeOrderAndData[1] = DMG_FUNC_Balancing_12_PAGE;
	}
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}

//if need jump to calibration page 
UINT8 jumpToCalibrationPage(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,53};//53 page
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}
//if need jump to home page 
UINT8 jumpToHomePage(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,54};//54 page
	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);
		result = 1;
	}
	return result;
}
//if need jump to Banling page , 跳转至配平页面
UINT8 jumpToBanlingPage(T5LType *pSdwe)
{
	UINT8 result = 0 ;
	//5A A5 07 82 0084 5A01 page
	INT16 pageChangeOrderAndData[2]={0x5A01,DMG_FUNC_Balancing_6_PAGE};//49 page
#if 0//before 20211119
	if(0 == gSystemPara.isCascade)
	{
		pageChangeOrderAndData[1] = DMG_FUNC_Balancing_6_PAGE;
	}
	else 
	{
		if(0 == gSystemPara.ScreenCastMode)
		{
			pageChangeOrderAndData[1] = DMG_FUNC_Balancing_12_PAGE;
		}
		else
		{
			pageChangeOrderAndData[1] = DMG_FUNC_Help_PAGE;
		}
	}
#else
	//20220119 changed
	switch(gSystemPara.isCascade)
	{
		//1、非级联
		//2、级联+模式是11（主机）+12（从机）
		//以上2种：页面跳转至8个方块界面
		case 0://single module , not cascade
		case ModbusFuncA_Master://FuncA module
		case ModbusFuncA_Slave://FuncA module
			pageChangeOrderAndData[1] = DMG_FUNC_Balancing_6_PAGE;
		break;
		//1、常规级联 1（主机）+（从机）
		//2、常规级联的显示模式：16个方块界面 或 带帮助信息界面
		case ModbusAdd_Master:
		case ModbusAdd_Slave_1:
			if(0 == gSystemPara.ScreenCastMode)
			{
				pageChangeOrderAndData[1] = DMG_FUNC_Balancing_6_PAGE;
			}
			else
			{
				pageChangeOrderAndData[1] = DMG_FUNC_Help_PAGE;
			}
		break;
		default :
		break;

	}
#endif
	pageChangeOrderAndData[1] = DMG_FUNC_Balancing_6_PAGE;

	if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
		((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
	{
		t5lWriteVarible(pSdwe,(0X0084),pageChangeOrderAndData,2,0);/**< DIWEN屏幕界面跳转 */  //0084
		result = 1;
	}
	return result;
}
//send screen light 
UINT8 sendScreenLight(T5LType *pSdwe)
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

//if reset calibration valid 
//prepare DMG display of color and sample avg data
UINT8 resetCalibrationTrigerDeal(T5LType *pSdwe)
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


//if sreen chanel changed
UINT8 chanelChangedTrigerDeal(T5LType *pSdwe)
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


UINT8 removeWeightTrigerDeal(T5LType *pSdwe)
{
	INT16 *pSendData = &g_i16ColorBuff[0];
	INT16 *pDataSendToDiWen = &g_i32_i16DataBuff[0];

	UINT8 result = 0 ;
	static UINT8 inerStatus = 0 ; 

	switch(inerStatus)
	{
		case 0://==send weight vlu to Screen
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				pDataSendToDiWen = &g_i32_i16DataBuff[0];
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pDataSendToDiWen,(2*T5L_MAX_CHANEL_LEN),0);
				//
				inerStatus=1;
			}
		break;
		case 1://==send color vlu to Screen
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				pSendData = &g_i16ColorBuff[0];
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pSendData,T5L_MAX_CHANEL_LEN,0);
				//
				inerStatus=2;
			}
		break;
		default:
			inerStatus = 0 ;
			result = TRUE;
		break;
	}
	return result;
}

UINT8 sendHelpDataDiff(T5LType *pSdwe)
{
	static UINT8 needSend = FALSE;
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
			needSend = TRUE;
		}
	}
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
	return localStatus;
}

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


float GetFloatBalancingModelData(enumModbusAddType slaveId,enumHX711ChanelType chanel)
{
	float weight = 0.0;
	ModbusRtuType *pContex = &g_ModbusRtu;
	if((chanel < HX711_CHANEL_NUM ) 
		&& ( slaveId >= ModbusAdd_Slave_1 )
		&& ( slaveId < ModbusAdd_Slave_Max ))
	{
		weight = pContex->MultWeightData[slaveId-ModbusAdd_Master][chanel].f_value;
	}
	return weight;
}

void preCurrentDeviceWeightData(INT32 *pData,INT16 *pDataInt16)
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
void preOtherDeviceWeightData(INT32 *pData,INT16 *pDataInt16 ,enumModbusAddType modbusSlaveId)
{
	UINT8 offset = 0;
	enumHX711ChanelType chanel = HX711Chanel_1;
	//
	if(modbusSlaveId < ModbusAdd_Slave_Max)
	{
		for(chanel = HX711Chanel_1 ; chanel < HX711_CHANEL_NUM ; chanel++)
		{
			offset = HX711_CHANEL_NUM*(modbusSlaveId - ModbusAdd_Master) + chanel;
			pData[offset] = (INT32)(GetFloatBalancingModelData(modbusSlaveId,chanel)+0.5f);
			//INT32 data to INT16 data
			pDataInt16[2*offset + 0] = (pData[offset] >> 16) & 0xFFFF;
			pDataInt16[2*offset + 1] = (pData[offset] >> 0 ) & 0xFFFF;
		}		
	}
}

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


UINT8 preWeightDataAndJudgeIfNeedSend(INT32 *pData,INT16 *pDataInt16, INT32 *pDataPre,UINT8 chanel_len)
{
	UINT8 ret = FALSE;
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		switch(gSystemPara.isCascade)
		{
			//单台，不级联，直接获取hx711采样值并计算
			case 0:
				//master local data
				preCurrentDeviceWeightData(pData,pDataInt16);
			break;

			//多台，级联，主机端：先获取本机hx711采样值，在获取从机发过来的hx711采样值
			case ModbusAdd_Master:
				//ModbusAdd_Slave_1 recv data
				preOtherDeviceWeightData(pData,pDataInt16,ModbusAdd_Slave_1);
			break;

			//多台，级联，从机端：直接从主机发过来的数据截取
			case ModbusAdd_Slave_1:
				//直接使用总线的数据，这里不需要更新，他的更新在总线侧
			break;

			default :
			break;
		}

		//judge if not need send
		ret = judgeWeightDataIfNotNeedSend(pData,pDataPre,chanel_len);			
	}
	//
	return ret;
}


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
			preCurrentDeviceWeightData(pData,pDataInt16);
			//judge if not need send
			ret = judgeWeightDataIfNotNeedSend(pData,pDataPre,chanel_len);
		}
		else if(ModbusAdd_Master == gSystemPara.isCascade)
		{
			//master local data
			preCurrentDeviceWeightData(pData,pDataInt16);
			//ModbusAdd_Slave_1 recv data
			preOtherDeviceWeightData(pData,pDataInt16,ModbusAdd_Slave_1);
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
		preCurrentDeviceWeightData(pData,pDataInt16);
		//ModbusAdd_Slave_1 recv data
		preOtherDeviceWeightData(pData,pDataInt16,ModbusAdd_Slave_1);
		//judge if not need send
		ret = judgeWeightDataIfNotNeedSend(pData,pDataPre,chanel_len);			
	}
	//
	return ret;
}

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

//==20210609
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

//
UINT8 preColorDataAndJudgeIfNeedSend(INT32 *pData,INT16 *pColor,INT16 *pColorPre,INT16 *pColorOtherCh,UINT8 chanel_len)
{
	UINT8 ret = FALSE;
	//1.pre Color Data
	preColorData(pData,pColor,pColorPre,pColorOtherCh,chanel_len);

	//2.updata pColorPre from pColor
	ret = judgeWeightColorIfNotNeedSend(pColor,pColorPre,chanel_len);
	return ret;	
}

//
UINT8 preColorDataAndJudgeIfNeedSend_Newxx(INT32 *pData,INT16 *pColor,INT16 *pColorPre,INT16 *pColorOtherCh,UINT8 chanel_len)
{
	UINT8 ret = FALSE ;
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
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
		//2.updata pColorPre from pColor
		ret = judgeWeightColorIfNotNeedSend(pColor,pColorPre,chanel_len);
	}
	return ret;
}
UINT8 sendBalancingWeightAndColor_Slave_1(T5LType *pSdwe)
{
	static UINT8 dataSendFlag = FALSE,colorSendFlag = FALSE;
	UINT8 data_i = 0 ,chn_i = 0 , ret = 0;
	//
	INT32 *pData = &g_i32DataBuff[0];
	INT32 *pDataPre = &g_i32DataBuffPre[0];
	//
	INT16 *pDataSendToDiWen = &g_i32_i16DataBuff[0];
	//
	INT16 *pColor = &g_i16ColorBuff[0];
	INT16 *pColorPre = &g_i16ColorBuffPre[0];
	for(data_i=0;data_i<T5L_MAX_CHANEL_LEN;data_i++)
	{
		if(pDataPre[data_i] != pData[data_i])
		{
			pDataPre[data_i] = pData[data_i];
			dataSendFlag = TRUE;
		}
	}
	//
	if(TRUE == dataSendFlag)
	{
		if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pDataSendToDiWen,(2*T5L_MAX_CHANEL_LEN),0))
		{
			dataSendFlag = FALSE;
		}
	}
	else if(dataSendFlag == FALSE)
	{
		for(data_i=0;data_i<T5L_MAX_CHANEL_LEN;data_i++)
		{
			if(pColorPre[data_i] != pColor[data_i])
			{
				pColorPre[data_i] = pColor[data_i];
				colorSendFlag = TRUE;
			}
		}
		if(TRUE == colorSendFlag)
		{
			if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pColor,T5L_MAX_CHANEL_LEN,0))
			{
				colorSendFlag = FALSE;
				ret = 1;
			}
		}
	}

	for(chn_i=0;chn_i<HX711_CHANEL_NUM;chn_i++)
	{
		//LED : display
		LedDataSet((enumLedSeqType)chn_i, (enumLedColorType)(pColor[HX711_CHANEL_NUM+chn_i]));
	}

	return ret;
}

UINT16 preBalancingWeightAndColorIfNotNeedSendToSreen(T5LType *pSdwe,INT32 *pData , INT16 *pDataSendToDiWen , INT32 *pDataPre, \
INT16 *pColor , INT16 *pColorPre , INT16 *pColorOtherCh , UINT8 chanel_len)
{
	UINT16 ret = FALSE ;
	static UINT16 handleStatus = 0 ;
	static UINT16 u16WeightHoldOn = 0 ;//when DMG_DATA_HOLD_TIME data not changed send to screen
	//
	switch(handleStatus)
	{
		//judge if weight need send to screen
		//if weight was hold on some time then go to send color 
		case 0x00:
			//=================prepare weight data
			if(TRUE == preWeightDataAndJudgeIfNeedSend(pData,pDataSendToDiWen,pDataPre,chanel_len))
			{
				if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pDataSendToDiWen,(2*chanel_len),0))//2*chanel_len:because each data type was 4 byte
				{
					u16WeightHoldOn = 0 ;
					handleWeightDataWasSend(pData,pDataPre,chanel_len);
				}
			}
			else
			{
				u16WeightHoldOn++;
				if(u16WeightHoldOn >= DMG_DATA_HOLD_TIME)//if weight not changed then check if color need send
				{
					u16WeightHoldOn = 0;
					handleStatus = 0x10;//if weight was send to screen go to send color
				}
			}
		break;

		//judge if color need send to screenxx
		case 0x10:
			//=================prepare color data
			if(TRUE == preColorDataAndJudgeIfNeedSend_Newxx(pData,pColor,pColorPre,pColorOtherCh,chanel_len))
			{
				if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pColor,chanel_len,0))
				{
					handleWeightColorWasSend(pColor,pColorPre,chanel_len);
					handleStatus = 0x20;//if color was send to screen go to default
				}
			}
			else
			{
				handleStatus = 0x20;//if color was send to screen go to default
			}
		break;

		default :
			handleStatus = 0;//go to check weigth if not need send
			ret = TRUE;//this cycle was handle done
		break;
	}
	return ret;
}

UINT16 sendBalancingWeightAndColor_Master(T5LType *pSdwe)
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
	ret = preBalancingWeightAndColorIfNotNeedSendToSreen(pSdwe,pData,pDataSendToDiWen,pDataPre,pColor,pColorPre,pColorOtherCh,chanel_len);
	return ret;
}

UINT8 sendBalancingWeightAndColor20220125_FuncA_Master(T5LType *pSdwe)
{
	//
	UINT8 ret = 0 ;
	//
	static UINT8 dataSendFlag = FALSE , colorSendFlag = FALSE;
	//
	INT32 *pData = &g_i32DataBuff[0];
	INT32 *pDataPre = &g_i32DataBuffPre[0];
	//
	INT16 *pDataSendToDiWen = &g_i32_i16DataBuff[0];
	//
	INT16 *pColor = &g_i16ColorBuff[0];
	INT16 *pColorPre = &g_i16ColorBuffPre[0];
	INT16 *pColorOtherCh = &g_i16ColorOtherChanel[0];
	//
	static UINT16 u16WeightHoldOn = 0 ;
	//=================prepare weight data
	if(TRUE == preWeightDataAndJudgeIfNeedSend_FuncA_Master(pSdwe,pData,pDataSendToDiWen,pDataPre,HX711_CHANEL_NUM))
	{
		dataSendFlag = TRUE;
		u16WeightHoldOn=0;
	}
	else
	{
		u16WeightHoldOn++;
		if(u16WeightHoldOn >= DMG_DATA_HOLD_TIME)
		{
			u16WeightHoldOn = DMG_DATA_HOLD_TIME;
		}
	}
	//weightTest();
	//=================send weight data
	if(TRUE == dataSendFlag)
	{
		if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pDataSendToDiWen,(2*T5L_MAX_CHANEL_LEN),0))
		{
			dataSendFlag = FALSE;
		}
	}
	else if(u16WeightHoldOn >= DMG_DATA_HOLD_TIME)
	{
		//=================prepare color data
		if(TRUE == preColorDataAndJudgeIfNeedSend(pData,pColor,pColorPre,pColorOtherCh,T5L_MAX_CHANEL_LEN))
		{
			colorSendFlag = TRUE;
		}
		//=================send color data
		if(TRUE == colorSendFlag)
		{
			if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pColor,T5L_MAX_CHANEL_LEN,0))
			{
				colorSendFlag = FALSE;
				ret = 1;
			}
		}
	}
	return ret;
}
UINT8 sendBalancingWeightAndColor20220125_FuncA_Slave(T5LType *pSdwe)
{
	static UINT8 dataSendFlag = FALSE,colorSendFlag = FALSE;
	UINT8 data_i = 0 ,chn_i = 0 , ret = 0;
	//
	INT32 *pData = &g_i32DataBuff[0];
	INT32 *pDataPre = &g_i32DataBuffPre[0];
	//
	INT16 *pDataSendToDiWen = &g_i32_i16DataBuff[0];
	//
	INT16 *pColor = &g_i16ColorBuff[0];
	INT16 *pColorPre = &g_i16ColorBuffPre[0];
	for(data_i=HX711_CHANEL_NUM;data_i<T5L_MAX_CHANEL_LEN;data_i++)
	{
		if(pDataPre[data_i] != pData[data_i])
		{
			pDataPre[data_i] = pData[data_i];
			dataSendFlag = TRUE;
		}
	}
	//
	if(TRUE == dataSendFlag)
	{
		if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pDataSendToDiWen,(2*T5L_MAX_CHANEL_LEN),0))
		{
			dataSendFlag = FALSE;
		}
	}
	else if(dataSendFlag == FALSE)
	{
		for(data_i=HX711_CHANEL_NUM;data_i<T5L_MAX_CHANEL_LEN;data_i++)
		{
			if(pColorPre[data_i] != pColor[data_i])
			{
				pColorPre[data_i] = pColor[data_i];
				colorSendFlag = TRUE;
			}
		}
		if(TRUE == colorSendFlag)
		{
			if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,&pColor[HX711_CHANEL_NUM],HX711_CHANEL_NUM,0))
			{
				colorSendFlag = FALSE;
				ret = 1;
			}
		}
	}

	for(chn_i=0;chn_i<HX711_CHANEL_NUM;chn_i++)
	{
		//LED : display
		LedDataSet((enumLedSeqType)chn_i, (enumLedColorType)(pColor[HX711_CHANEL_NUM+chn_i]));
	}

	return ret;
}

//================================================================================================
//屏幕：显示托盘的重量（当是否显示小数参数修改时和上电初始化时执行）
UINT8 screen_ChangeDisplayPosition(T5LType *pSdwe)
{
	static INT16 add_offset = 0,data_offset = 0,len_offset = 0,handle_i=0,total_handle = HX711_CHANEL_NUM;
	UINT8 ret = FALSE;
	//
	if(0 == gSystemPara.isCascade)//不级联
	{
		total_handle = HX711_CHANEL_NUM;
		describlePoint_add = describlePointAdd[handle_i%total_handle]+add_offset;
		describlePoint_len = 6+len_offset;
		//
		if(0 == gSystemPara.xiaoShuXianShi)//无小数
		{
			describlePoint_data = &describlePointVluWuXiaoShu[handle_i%total_handle][0]+data_offset;
		}
		else
		{
			describlePoint_data = &describlePointVluXiaoShu[handle_i%total_handle][0]+data_offset;
		}	
	}
	else
	{
		total_handle = T5L_MAX_CHANEL_LEN;
		ret =TRUE;
	}
	//
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		handle_i++;
	}
	//
	if(handle_i >= total_handle)
	{
		handle_i = 0 ;
		ret = TRUE;
	}		
	//
	return ret;
}	
UINT8 screen_ChangeHelpDisplayPosition(T5LType *pSdwe)
{
	static INT16 add_offset = 0,data_offset = 0,len_offset = 0,handle_i=0,total_handle = HX711_CHANEL_NUM;
	UINT8 ret = FALSE;
	//
	if(0 == gSystemPara.isCascade)//不级联
	{
		total_handle = DESCRIBLE_POINT_HELP_NUM;
		describlePoint_add = describlePointAdd_help[handle_i%total_handle]+add_offset;
		describlePoint_len = 6+len_offset;
		//
		if(0 == gSystemPara.xiaoShuXianShi)//无小数
		{
			describlePoint_data = &describlePointVluWuXiaoShu_help[handle_i%total_handle][0]+data_offset;
		}
		else
		{
			describlePoint_data = &describlePointVluXiaoShu_help[handle_i%total_handle][0]+data_offset;
		}	
	}
	else
	{
		total_handle = DESCRIBLE_POINT_HELP_NUM;
		ret =TRUE;
	}
	//
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		handle_i++;
	}
	//
	if(handle_i >= total_handle)
	{
		handle_i = 0 ;
		ret = TRUE;
	}		
	//
	return ret;
}	
//================================================================================================
//屏幕：显示托盘的重量（当是否显示小数参数修改时和上电初始化时执行）
UINT8 screenLarger_ChangeDisplayPosition(T5LType *pSdwe)
{
	static INT16 add_offset = 0,data_offset = 0,len_offset = 0,handle_i=0,total_handle = HX711_CHANEL_NUM;
	UINT8 ret = FALSE;
	//
	if(0 == gSystemPara.isCascade)//不级联
	{
		total_handle = HX711_CHANEL_NUM;
		describlePoint_add = describlePointWeightVluAdd_Larger_8[handle_i%total_handle]+add_offset;
		describlePoint_len = 6+len_offset;
		//
		if(0 == gSystemPara.xiaoShuXianShi)//无小数
		{
			describlePoint_data = &describlePointWeightVluWuXiaoShu_Larger_8[handle_i%total_handle][0]+data_offset;
		}
		else
		{
			describlePoint_data = &describlePointWeightVluYouXiaoShu_Larger_8[handle_i%total_handle][0]+data_offset;
		}	
	}
	else
	{
		total_handle = T5L_MAX_CHANEL_LEN;
		ret =TRUE;
	}
	//
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		handle_i++;
	}
	//
	if(handle_i >= total_handle)
	{
		handle_i = 0 ;
		ret = TRUE;
	}		
	//
	return ret;
}


UINT8 screenLarger_ChangeWeightIndexDisplayPosition(T5LType *pSdwe)
{
	static INT16 add_offset = 0,data_offset = 0,len_offset = 0,handle_i=0,total_handle = HX711_CHANEL_NUM;
	UINT8 ret = FALSE;
	//
	if(0 == gSystemPara.isCascade)//不级联
	{
		total_handle = HX711_CHANEL_NUM;
		describlePoint_add = describlePointWeightIndexAdd_Larger_8[handle_i%total_handle]+add_offset;
		describlePoint_len = 6+len_offset;
		describlePoint_data = &describlePointWeightIndex_Larger_8[handle_i%total_handle][0]+data_offset;
	}
	else
	{
		total_handle = T5L_MAX_CHANEL_LEN;
		ret =TRUE;
	}
	//
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		handle_i++;
	}
	//
	if(handle_i >= total_handle)
	{
		handle_i = 0 ;
		ret = TRUE;
	}		
	//
	return ret;
}

UINT8 screenLarger_ChangeWeightColorDisplayPosition(T5LType *pSdwe)
{
	static INT16 add_offset = 0,data_offset = 0,len_offset = 0,handle_i=0,total_handle = HX711_CHANEL_NUM;
	UINT8 ret = FALSE;
	//
	if(0 == gSystemPara.isCascade)//不级联
	{
		total_handle = HX711_CHANEL_NUM;
		describlePoint_add = describlePointWeightColorAdd_Larger_8[handle_i%total_handle]+add_offset;
		describlePoint_len = 2+len_offset;//========================================special
		//
		describlePoint_data = &describlePointWeightColor_Larger_8[handle_i%total_handle][0]+data_offset;
	}
	else
	{
		total_handle = T5L_MAX_CHANEL_LEN;
		ret =TRUE;
	}
	//
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		handle_i++;
	}
	//
	if(handle_i >= total_handle)
	{
		handle_i = 0 ;
		ret = TRUE;
	}		
	//
	return ret;
}


UINT8 screenLarger_ChangeHelpVluDisplayPosition(T5LType *pSdwe)
{
	static INT16 add_offset = 0,data_offset = 0,len_offset = 0,handle_i=0,total_handle = HX711_CHANEL_NUM;
	UINT8 ret = FALSE;
	//
	if(0 == gSystemPara.isCascade)//不级联
	{
		total_handle = DIFF_TO_DIWEN_DATA_LEN;
		describlePoint_add = describlePointHelpVluAdd_Larger_8[handle_i%total_handle]+add_offset;
		describlePoint_len = 6+len_offset;
		//
		if(0 == gSystemPara.xiaoShuXianShi)//无小数
		{
			describlePoint_data = &describlePointHelpVluWuXiaoShu_Larger_8[handle_i%total_handle][0]+data_offset;
		}
		else
		{
			describlePoint_data = &describlePointHelpVluYouXiaoShu_Larger_8[handle_i%total_handle][0]+data_offset;
		}	
	}
	else
	{
		total_handle = DIFF_TO_DIWEN_DATA_LEN;
		ret =TRUE;
	}
	//
	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		handle_i++;
	}
	//
	if(handle_i >= total_handle)
	{
		handle_i = 0 ;
		ret = TRUE;
	}		
	//
	return ret;
}








//================================================================================================
//屏幕：显示托盘序号（当是否显示小数参数修改时和上电初始化时执行）
UINT8 screen_ChangeDisplayPositionOfIndex(T5LType *pSdwe)
{
	static INT16 add_offset = 0,data_offset = 0,len_offset = 0 , int16_ChangeDisplayPosition_ii = 0;
	UINT8 ret = FALSE;

	describlePoint_add = describleIndexPointAdd[int16_ChangeDisplayPosition_ii%HX711_CHANEL_NUM]+add_offset;
	describlePoint_data = &describleIndexPointData[int16_ChangeDisplayPosition_ii%HX711_CHANEL_NUM][0]+data_offset;
	describlePoint_len = 2+len_offset;

	if(TRUE == t5lWriteData(pSdwe,describlePoint_add,describlePoint_data,describlePoint_len,0))
	{
		int16_ChangeDisplayPosition_ii++;
	}

	if(int16_ChangeDisplayPosition_ii >= HX711_CHANEL_NUM)
	{
		int16_ChangeDisplayPosition_ii = 0 ;
		ret = TRUE;
	}

	return ret;
}
//获取屏幕的当前页面序号
void screenT5L_CurPageGet(T5LType *pSdwe)
{
	t5lReadVarible(pSdwe,DMG_SYS_CUR_PAGE_GET_ADD,1,0);//get cur page
}
//获取屏幕的软件版本号
void screenT5L_VersionGet(T5LType *pSdwe)
{
	t5lReadVarible(pSdwe,DMG_SYS_VERSION_GET_ADD,1,0);//get version
}
//
UINT8 sendBalancingWeightAndColorAndHelpDataToScreen(T5LType *pSdwe)
{
	UINT8 ret = 0 ;
	switch(gSystemPara.isCascade)
	{
		case 0:
		case ModbusAdd_Master:
			ret = sendBalancingWeightAndColor_Master(pSdwe);
		break;
		case ModbusAdd_Slave_1:
			ret = sendBalancingWeightAndColor_Slave_1(pSdwe);
		break;
		case ModbusFuncA_Master:
			ret = sendBalancingWeightAndColor20220125_FuncA_Master(pSdwe);
		break;
		case ModbusFuncA_Slave:
			ret = sendBalancingWeightAndColor20220125_FuncA_Slave(pSdwe);
		break;
		default:
		break;
	}
	screenT5L_HelpDataMainFunction(pSdwe);
	return ret;
}

//大屏的相关变量初始化过程
UINT8 largerScreen_Init(T5LType *pSdwe)
{
	UINT8 result = FALSE ;
	INT16 sendData[64],len=0,i;
	switch(pSdwe->sendSysParaDataToDiwenIndex)
	{
		case 0x80://获取系统版本 若获取回则代表 屏已上电
			if(FALSE == pSdwe->sdwePowerOn)
			{
				if(0 == (pSdwe->CurTick %100))//every 500ms send order to get version
				{
					screenT5L_VersionGet(pSdwe);
				}
			}
			else
			{
				pSdwe->sendSysParaDataToDiwenIndex = 0x81;
			}
		break;
		case 0x81://发送【托盘重量显示的描述指针】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenLarger_ChangeDisplayPosition(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		case 0x82://发送【托盘序号显示的描述指针】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenLarger_ChangeWeightIndexDisplayPosition(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		case 0x83://发送【托盘重量背景色显示的描述指针】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenLarger_ChangeWeightColorDisplayPosition(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		case 0x84://发送【帮组模块显示的描述指针】到屏幕
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screenLarger_ChangeHelpVluDisplayPosition(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		case 0x85:
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{	
				len = T5L_MAX_CHANEL_LEN;
				for(i=0;i<len;i++)
				{
					sendData[i]=i+1;
				}	
				t5lWriteVarible(pSdwe,(0x3901),sendData,len,0);
				pSdwe->sendSysParaDataToDiwenIndex = 0;
			}
		break;

		case 0://send screen light
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				sendScreenLight(pSdwe);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 1://send weight data to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<(2*T5L_MAX_CHANEL_LEN);len++)//每个通道是4字节变量
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,sendData,len,0);/**< 通道重量 */
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 2://send back color to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<T5L_MAX_CHANEL_LEN;len++)
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,sendData,len,0);/**< 通道背景色 */  //3100
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 3://send help data to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<DIFF_TO_DIWEN_DATA_LEN;len++)
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS,sendData,len,0);/**< 通道差值，帮助信息 */  //1201
				pSdwe->sendSysParaDataToDiwenIndex = 7;
			}
		break;


		case 7://send 0x1000 单位
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				sendData[len++] = gSystemPara.uint;
				t5lWriteVarible(pSdwe,(0x1000),sendData,len,0);		/**< 单位：ml/g */ 				//1000
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 8://send 0X100A~0X101E 系统参数
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len = 0 ;
				sendData[len++] = gSystemPara.minWeight;		/**< 最小量程 */ 				//100A
				sendData[len++] = gSystemPara.maxWeight;		/**< 最大量程 */ 				//100B
				sendData[len++] = gSystemPara.errRange;			/**< 误差范围 */ 				//100C
				sendData[len++] = gSystemPara.isCascade;		/**< 是否级联 */ 				//100D
				sendData[len++] = gSystemPara.isLedIndicate;  	/**< 是否LED指示 */ 			//100E
				sendData[len++] = gSystemPara.userColorSet[0];	/**< 配平色1 */ 				//100F
				sendData[len++] = gSystemPara.userColorSet[1];	/**< 配平色2 */ 				//1010
				sendData[len++] = gSystemPara.userColorSet[2];	/**< 配平色3 */ 				//1011
				sendData[len++] = gSystemPara.userColorSet[3];	/**< 配平色4 */ 				//1012
				sendData[len++] = gSystemPara.zeroRange;		/**< 零点范围 */ 				//1013
				sendData[len++] = gSystemPara.ScreenLight;		/**< 正常亮度 */ 				//1014
#if 0				
				sendData[len++] = 25;							/**< 待机亮度 */ 				//1015
				sendData[len++] = 300;							/**< 待机时间 */ 				//1016
#else
				sendData[len++] = gSystemPara.VoiceNumTouch;	/**< 音量大小 触控*/ 			//1015
				sendData[len++] = gSystemPara.VoiceNum;			/**< 音量大小 */ 			    //1016
#endif				
				sendData[len++] = gSystemPara.ScreenVoiceSwitch;/**< HX711	语音开关 */ 		//1017
				sendData[len++] = gSystemPara.ScreenCastMode;	/**< HX711	级联显示模式 */ 	//1018
				sendData[len++] = gSystemPara.FlashEraseTimes;	/**< HX711	FLASH 擦写次数 */ 	//1019
				sendData[len++] = MCU_VERSION;					/**< MCU 版本 */ 				//101A
				sendData[len++] = DIWEN_VERSION;				/**< DIVEN 版本 */ 				//101B
				
				sendData[len++] = gSystemPara.xiaoShuXianShi;	/**< 小数显示 0x101c*/			//101C
				sendData[len++] = gSystemPara.mlYugBiLv;		/**< ml与g比率 0x101d*/			//101D
				sendData[len++] = gSystemPara.daPinXianShi;		/**< 大屏显示 0x101e*/			//101E

				t5lWriteVarible(pSdwe,(0x100A),sendData,len,0);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;




		default:
			if(TRUE == pSdwe->sdweHX711FirstSampleCoplt)
			{
				result = TRUE;
			}
		break;
	}
	return result;
}

//小屏的相关变量初始化过程
UINT8 smallerScreen_Init(T5LType *pSdwe)
{
	INT16 sendData[64],len=0;
	UINT8 result = FALSE ;
	static INT16 curPage = 0 ,  curPageDelay_offset = 80;
	//
	switch(pSdwe->sendSysParaDataToDiwenIndex)
	{
		case 0x80://获取系统版本 若获取回则代表 屏已上电
			if(FALSE == pSdwe->sdwePowerOn)
			{
				if(0 == (pSdwe->CurTick %100))//every 500ms send order to get version
				{
					screenT5L_VersionGet(pSdwe);
				}
			}
			else
			{
				pSdwe->sendSysParaDataToDiwenIndex = 0x81;
			}
		break;
		case 0x81:
			if(0 == (pSdwe->CurTick %curPageDelay_offset))//every 500ms send order to get version
			{	
				if(TRUE ==jumpToStartUpPage(pSdwe,curPage))//触发屏幕播放开机动画
				{
					if(curPage++ >= 25)
					{
						pSdwe->sendSysParaDataToDiwenIndex = 0x82;
					}				
				}			
			}
		break;
		case 0x82://发送配平页面的数据 规整为0 等待HX711采集到一轮完整数据后在继续往后
			if(TRUE == pSdwe->sdweHX711FirstSampleCoplt)
			{
				pSdwe->sendSysParaDataToDiwenIndex = 0 ;//准备配平页面的数据 后在发送相关参数
			}
		break;
		case 0x83://发送配平页面的数据 规整为0
			if(TRUE == pSdwe->sdweHX711FirstSampleCoplt)
			{
				if(TRUE == sendBalancingWeightAndColorAndHelpDataToScreen(pSdwe))
				{
					pSdwe->sendSysParaDataToDiwenIndex = 0 ;
				}
			}
		break;
		case 0://send screen light
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				sendScreenLight(pSdwe);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 1://send weight data to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<(2*T5L_MAX_CHANEL_LEN);len++)//每个通道是4字节变量
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,sendData,len,0);/**< 通道重量 */
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 2://send back color to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<T5L_MAX_CHANEL_LEN;len++)
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,sendData,len,0);/**< 通道背景色 */  //3100
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 3://send help data to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				for(len=0;len<DIFF_TO_DIWEN_DATA_LEN;len++)
				{
					sendData[len] = 0;
				}
				t5lWriteVarible(pSdwe,DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS,sendData,len,0);/**< 通道差值，帮助信息 */  //1201
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 4://小数显示相关描述指针变量发送，托盘重量显示相关
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screen_ChangeDisplayPosition(pSdwe))//根据小数是否打开 发送相关数据
				{
					pSdwe->sendSysParaDataToDiwenIndex=41;
				}
			}
		break;
		case 41://小数显示相关描述指针变量发送，帮组信息相关
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screen_ChangeHelpDisplayPosition(pSdwe))//根据小数是否打开 发送相关数据
				{
					pSdwe->sendSysParaDataToDiwenIndex = 5;
				}
			}
		break;
		case 5://changed at 20220119 , FuncA Module special , send num
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				if(gSystemPara.isCascade == ModbusFuncA_Slave)//only FuncA Module and Slave , need change block num to 9~16
				{
					for(len = 0 ; len < HX711_CHANEL_NUM ; len++)
					{
						sendData[len] = HX711_CHANEL_NUM + len;
					}					
					t5lWriteVarible(pSdwe,(0x3901),sendData,len,0);
				}			
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 6://jump to Banling page
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				jumpToBanlingPage(pSdwe);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;	
		case 7://send 0x1000 单位
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				sendData[len++] = gSystemPara.uint;
				t5lWriteVarible(pSdwe,(0x1000),sendData,len,0);		/**< 单位：ml/g */ 				//1000
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 8://send 0X100A~0X101E 系统参数
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len = 0 ;
				sendData[len++] = gSystemPara.minWeight;		/**< 最小量程 */ 				//100A
				sendData[len++] = gSystemPara.maxWeight;		/**< 最大量程 */ 				//100B
				sendData[len++] = gSystemPara.errRange;			/**< 误差范围 */ 				//100C
				sendData[len++] = gSystemPara.isCascade;		/**< 是否级联 */ 				//100D
				sendData[len++] = gSystemPara.isLedIndicate;  	/**< 是否LED指示 */ 			//100E
				sendData[len++] = gSystemPara.userColorSet[0];	/**< 配平色1 */ 				//100F
				sendData[len++] = gSystemPara.userColorSet[1];	/**< 配平色2 */ 				//1010
				sendData[len++] = gSystemPara.userColorSet[2];	/**< 配平色3 */ 				//1011
				sendData[len++] = gSystemPara.userColorSet[3];	/**< 配平色4 */ 				//1012
				sendData[len++] = gSystemPara.zeroRange;		/**< 零点范围 */ 				//1013
				sendData[len++] = gSystemPara.ScreenLight;		/**< 正常亮度 */ 				//1014
#if 0				
				sendData[len++] = 25;							/**< 待机亮度 */ 				//1015
				sendData[len++] = 300;							/**< 待机时间 */ 				//1016
#else
				sendData[len++] = gSystemPara.VoiceNumTouch;	/**< 音量大小 触控*/ 			//1015
				sendData[len++] = gSystemPara.VoiceNum;			/**< 音量大小 */ 			    //1016
#endif				
				sendData[len++] = gSystemPara.ScreenVoiceSwitch;/**< HX711	语音开关 */ 		//1017
				sendData[len++] = gSystemPara.ScreenCastMode;	/**< HX711	级联显示模式 */ 	//1018
				sendData[len++] = gSystemPara.FlashEraseTimes;	/**< HX711	FLASH 擦写次数 */ 	//1019
				sendData[len++] = MCU_VERSION;					/**< MCU 版本 */ 				//101A
				sendData[len++] = DIWEN_VERSION;				/**< DIVEN 版本 */ 				//101B
				
				sendData[len++] = gSystemPara.xiaoShuXianShi;	/**< 小数显示 0x101c*/			//101C
				sendData[len++] = gSystemPara.mlYugBiLv;		/**< ml与g比率 0x101d*/			//101D
				sendData[len++] = gSystemPara.daPinXianShi;		/**< 大屏显示 0x101e*/			//101E

				t5lWriteVarible(pSdwe,(0x100A),sendData,len,0);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 9://send 2100 DMG_FUNC_SET_CHANEL_NUM
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				sendData[len++] = pSdwe->CalibrateChanel;
				t5lWriteVarible(pSdwe,DMG_FUNC_SET_CHANEL_NUM,sendData,len,0);/**< 校准的通道号 */  //2100
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 10://send voice info to DW
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{
				len=0;
				screenT5L_OutputVoice(pSdwe,VoiceTypeMax);
				pSdwe->sendSysParaDataToDiwenIndex++;
			}
		break;
		case 11://序号显示相关描述指针变量发送
			if(((pSdwe->LastSendTick > pSdwe->CurTick)&&((pSdwe->LastSendTick-pSdwe->CurTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
				((pSdwe->LastSendTick < pSdwe->CurTick)&&((pSdwe->CurTick - pSdwe->LastSendTick) >= 2*DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
			{		
				if(0 != screen_ChangeDisplayPositionOfIndex(pSdwe))//根据小数是否打开 发送相关数据
				{
					pSdwe->sendSysParaDataToDiwenIndex++;
				}
			}
		break;
		default:
			if(TRUE == pSdwe->sdweHX711FirstSampleCoplt)
			{
				result = TRUE;
			}
		break;
	}
	return result;
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
//屏幕语音播报处理
UINT8 screenT5L_VoicePrintfMainfunction(T5LType *pSdwe)
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
//==send help data te screen
UINT8 screenT5L_HelpDataMainFunction(T5LType *pSdwe)
{
	ModbusRtuType *pContex = &g_ModbusRtu;
	UINT8 localStatus = FALSE;

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
	return localStatus;
}

//小屏的屏幕初始化：发送相关参数给屏幕
UINT8 screenTxHandle_ScreenInit(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(T5L_INITIAL_COMPLETE != pSdwe->sendSdweInit)
	{
		matched = TRUE;
		if(TRUE == smallerScreen_Init(pSdwe))
		{
			pSdwe->sendSdweInit = T5L_INITIAL_COMPLETE;
		}
	}
	return matched;
}
//大屏的屏幕初始化：发送相关参数给屏幕
UINT8 screenLargerTxHandle_ScreenInit(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(T5L_INITIAL_COMPLETE != pSdwe->sendSdweInit)
	{
		matched = TRUE;
		if(TRUE == largerScreen_Init(pSdwe))
		{
			pSdwe->sendSdweInit = T5L_INITIAL_COMPLETE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_JumpToHomePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToHomePage)
	{
		matched = TRUE;
		if(0 != jumpToHomePage(pSdwe))
		{
			pSdwe->sdweJumpToHomePage = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_JumpToBanlingPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToBanlingPage)
	{
		matched = TRUE;
		if(0 != jumpToBanlingPage(pSdwe))
		{
			pSdwe->sdweJumpToBanlingPage = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_JumpToCalibrationPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToCalitrationPage)
	{
		matched = TRUE;
		if(0 != jumpToCalibrationPage(pSdwe))
		{
			pSdwe->sdweJumpToCalitrationPage = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_JumpToActivePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpActivePage)
	{
		matched = TRUE;
		if(0 != jumpToActivePage(pSdwe))
		{
			pSdwe->sdweJumpActivePage = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_JumpToSysParaPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpToSysParaPage)
	{
		matched = TRUE;
		if(0 != jumpToSysparaPage(pSdwe))
		{
			pSdwe->sdweJumpToSysParaPage = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_FreshScreenLight(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweFreshScreenLight)
	{
		matched = TRUE;
		if(0 != sendScreenLight(pSdwe))
		{
			pSdwe->sdweFreshScreenLight = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_ChangeDisplayPosition(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	static UINT8 changeHelpInfoDisp = FALSE;
	//
	if(TRUE == pSdwe->sdweChangeDescriblePoint)
	{
		matched = TRUE;
		if(FALSE == changeHelpInfoDisp)//先修改重量单元的描述指针
		{
			if(0 != screen_ChangeDisplayPosition(pSdwe))
			{
				changeHelpInfoDisp = TRUE;
			}
		}
		else//在修改帮助信息的描述指针
		{
			if(0 != screen_ChangeHelpDisplayPosition(pSdwe))
			{
				changeHelpInfoDisp = FALSE;
				//
				pSdwe->sdweChangeDescriblePoint = FALSE;
				matched = FALSE;
			}
		}
	}
	return matched;
}
UINT8 screenTxHandle_JmmpToBalancingPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpBalancing)
	{
		matched = TRUE;
		if(0!= jumpToBalancingPage(pSdwe))
		{
			pSdwe->sdweJumpBalancing = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_JumpToBalancingCleanPage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpBalancing_cleanpagee)
	{
		matched = TRUE;
		if(0!= jumpToBalancingCleanPage(pSdwe))
		{
			pSdwe->sdweJumpBalancing_cleanpagee = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_JumpToBalancingHomePage(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweJumpBalancing_home)
	{
		matched = TRUE;
		if(0!= jumpToBalancingHomePage(pSdwe))
		{
			pSdwe->sdweJumpBalancing_home = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_ChanelChangedTrigerDeal(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweChanelChanged)
	{
		matched = TRUE;
		if(0 != chanelChangedTrigerDeal(pSdwe))
		{
			pSdwe->sdweChanelChanged = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_ResetCalibrationTrigerHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdweResetTriger)
	{
		matched = TRUE;
		if(0 != resetCalibrationTrigerDeal(pSdwe))
		{
			pSdwe->sdweResetTriger = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_PointTrigerHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(TRUE == pSdwe->sdwePointTriger)
	{
		matched = TRUE;
		if(0 != pointTrigerDeal(pSdwe))
		{
			pSdwe->sdwePointTriger = FALSE;
		}
	}
	return matched;
}
UINT8 screenTxHandle_RemoveWeightTrigerHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if((TRUE == pSdwe->sdweRemoveWeightTriger)||(TRUE == getModbusOtherRemoveFlag()))
	{
		matched = TRUE;
		hx711_setAllRemoveWeight();
		t5lDisPlayDataClear();
		if(0 != removeWeightTrigerDeal(pSdwe))
		{
			pSdwe->sdweRemoveWeightTriger = FALSE;
			//
			setModbusOtherRemoveFlag(FALSE);
		}
	}
	return matched;
}
UINT8 screenTxHandle_ScreenWeightAndColorAndVoiceHandle(T5LType *pSdwe)
{
	UINT8 matched = FALSE;
	if(g_sysLocked == STM32MCU_UNLOCKED)
	{
		matched = TRUE;
		switch(gSystemPara.isCascade)
		{
			case 0:
			case ModbusAdd_Master:
				sendBalancingWeightAndColor_Master(pSdwe);
			break;
			case ModbusAdd_Slave_1:
				sendBalancingWeightAndColor_Slave_1(pSdwe);
			break;
			case ModbusFuncA_Master:
				sendBalancingWeightAndColor20220125_FuncA_Master(pSdwe);
			break;
			case ModbusFuncA_Slave:
				sendBalancingWeightAndColor20220125_FuncA_Slave(pSdwe);
			break;
			default:
			break;
		}
		screenT5L_HelpDataMainFunction(pSdwe);

		//voice printf mainfunction
		if(TRUE == gSystemPara.ScreenVoiceSwitch)
		{
			switch(gSystemPara.isCascade)
			{
				//master
				case 0:
				case ModbusAdd_Master:
				case ModbusFuncA_Master:
					screenT5L_VoicePrintfMainfunction(pSdwe);
				break;
				default:
				break;
			}
		}
	}	
	return matched;
}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
void preCurrentDeviceWeightData_New(T5LType *pSdwe,UINT8 chanel_len)
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
UINT8 judgeWeightDataIfNotNeedSend_New(T5LType *pSdwe,UINT8 chanel_len)
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
void preOtherDeviceWeightData_New(T5LType *pSdwe,enumModbusAddType modbusSlaveId)
{
	UINT8 offset = 0;
	enumHX711ChanelType chanel = HX711Chanel_1;
	//
	if(modbusSlaveId < ModbusAdd_Slave_Max)
	{
		for(chanel = HX711Chanel_1 ; chanel < HX711_CHANEL_NUM ; chanel++)
		{
			offset = HX711_CHANEL_NUM*(modbusSlaveId - ModbusAdd_Master) + chanel;	
			pSdwe->screenCycle.pData[offset] = (INT32)(GetFloatBalancingModelData(modbusSlaveId,chanel)+0.5f);
			//INT32 data to INT16 data
			pSdwe->screenCycle.pDataSendToDiWen[2*offset + 0] = (pSdwe->screenCycle.pData[offset] >> 16) & 0xFFFF;
			pSdwe->screenCycle.pDataSendToDiWen[2*offset + 1] = (pSdwe->screenCycle.pData[offset] >> 0 ) & 0xFFFF;
		}		
	}
}
UINT8 preWeightDataAndJudgeIfNeedSend_New(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 ret = FALSE;
	//
	if(chanel_len <= T5L_MAX_CHANEL_LEN)
	{
		switch(gSystemPara.isCascade)
		{
			case 0:
				//master local data
				preCurrentDeviceWeightData_New(pSdwe,chanel_len);
			break;
 
			case ModbusAdd_Master:
				preCurrentDeviceWeightData_New(pSdwe,chanel_len);
				//ModbusAdd_Slave_1 recv data
				preOtherDeviceWeightData_New(pSdwe,ModbusAdd_Slave_1);
			break;
 
			case ModbusAdd_Slave_1:

			break;
 
			default :
			break;
		}
 
		//judge if not need send
		ret = judgeWeightDataIfNotNeedSend_New(pSdwe,chanel_len);			
	}
	//
	return ret;
}
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
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
UINT8 preColorDataAndJudgeIfNeedSend_New(T5LType *pSdwe,UINT8 chanel_len)
//(INT32 *pData,INT16 *pColor,INT16 *pColorPre,INT16 *pColorOtherCh,UINT8 chanel_len)
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
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

UINT8 preHelpData_New(T5LType *pSdwe)
{
	static UINT8 needSend = FALSE;
	UINT8 i = 0 , localStatus = 0;

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




UINT8 preHelpDataAndJudgeIfNeedSend_New(T5LType *pSdwe,UINT8 chanel_len)
{
	UINT8 localStatus = FALSE;
	UINT8 ret = FALSE , offset = 0;
	T5LType *pSdweSmaller = &g_T5LCtx[ScreenIndex_Smaller];

	UINT8 i = 0;
	//pre help data
	switch(gSystemPara.isCascade)
	{
		//self not jilian 
		case 0:

		break;

		//master
		case ModbusAdd_Master:
		case ModbusFuncA_Master:
			//localStatus = sendHelpDataDiff(pSdwe);
		break;

		//slave used com data
		case ModbusAdd_Slave_1:
		case ModbusFuncA_Slave:
			//doing nothing cause pHelp data from COM
		break;

		//default
		default:
		break;
	}
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
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//15.6 larger screen cycle data 
UINT8 screenLargerTxHandle_CycleData(T5LType *pSdwe)
{
	UINT8 chanel_len = T5L_MAX_CHANEL_LEN , ret = 0 ,localStatus = 0;
	//
	static enumScreenCycleDataHandleStatusType u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_JUDGE_WEIGHT_DATA;
	static UINT32 u16WeightHoldOn = 0 ;//when DMG_DATA_HOLD_TIME data not changed send to screen
	//
	switch(u8InnerHandleStatus)
	{
		//=======================================================================================================
		//==weight handle
		case SCREEN_CYCLE_DATA_HANDLE_JUDGE_WEIGHT_DATA:
			if(TRUE == preWeightDataAndJudgeIfNeedSend_New(pSdwe,chanel_len))
			{
				u16WeightHoldOn = pSdwe->CurTick;
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_SEND_WEIGHT_DATA;
			}
			else
			{
				if(pSdwe->CurTick >= (u16WeightHoldOn + DMG_DATA_HOLD_TIME))
				{
					u16WeightHoldOn = pSdwe->CurTick;
					u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_JUDGE_COLOR_DATA;//if weight not changed then go to color handle
				}
			}
		break;
		case SCREEN_CYCLE_DATA_HANDLE_SEND_WEIGHT_DATA:
			if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pSdwe->screenCycle.pDataSendToDiWen,(2*chanel_len),0))//2*chanel_len:because each data type was 4 byte
			{
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_JUDGE_WEIGHT_DATA;//if send weight data to screen complete back to check it again
			}
		break;


		//=======================================================================================================
		//==color handle
		case SCREEN_CYCLE_DATA_HANDLE_JUDGE_COLOR_DATA:
			if(TRUE == preColorDataAndJudgeIfNeedSend_New(pSdwe,chanel_len))
			{
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_SEND_COLOR_DATA;
			}
			else
			{
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_JUDGE_HELP_DATA;//if color was not need send to screen , go to help handle
			}
		break;
		case SCREEN_CYCLE_DATA_HANDLE_SEND_COLOR_DATA:
			if(TRUE ==t5lWriteData(pSdwe,DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pSdwe->screenCycle.pColorPre,chanel_len,0))
			{
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_JUDGE_HELP_DATA;//if color was send to screen , go to help handle
			}
		break;

		/*
		//cause voice printf need delay so move it
		//=======================================================================================================
		//==voice handle
		case SCREEN_CYCLE_DATA_HANDLE_JUDGE_VOICE_DATA:
			//if voice was enable
			if(TRUE == gSystemPara.ScreenVoiceSwitch)
			{
				localStatus = screenT5L_VoicePrintfMainfunction(pSdwe);//special:if no voice need printf this func will return TRUE
				if(TRUE == localStatus)
				{
					//if voice was not need handle or allready send to screen , go to help handle
					u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_JUDGE_HELP_DATA;
				}			
			}
			else
			{
				//if voice was disable , go to help handle
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_JUDGE_HELP_DATA;
			}
		break;
		*/

		//=======================================================================================================
		//==help handle
		case SCREEN_CYCLE_DATA_HANDLE_JUDGE_HELP_DATA:
			if(TRUE == preHelpDataAndJudgeIfNeedSend_New(pSdwe,chanel_len))
			{
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_SEND_HELP_DATA;
			}
			else
			{
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_DEFAULT;//if help was not need send to screen , go to default handle
			}
		break;
		case SCREEN_CYCLE_DATA_HANDLE_SEND_HELP_DATA:
			if(TRUE == t5lWriteData(pSdwe,DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS,pSdwe->screenCycle.pHelpPre,(DIFF_TO_DIWEN_DATA_LEN),0))
			{
				u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_DEFAULT;//if help was send to screen , go to default handle
			}
		break;

		//=======================================================================================================
		//==default handle
		default:
			//cycle data of : weight color voice and help data was send to screen , Represent cycle data handle complete 
			u8InnerHandleStatus = SCREEN_CYCLE_DATA_HANDLE_JUDGE_WEIGHT_DATA;
			ret = TRUE;
		break;
	}

	//=======================================================================================================
	//==help handle
	//localStatus = screenT5L_VoicePrintfMainfunction(pSdwe);//special:if no voice need printf this func will return TRUE
	//
	return ret;
}

//the Tx handle function group of small screen
screenRxTxHandleType screenTxHandle[SCREEN_TX_HANDLE_TOTAL_NUM]=
{
	//priority index func_add
	{0,	0, &screenTxHandle_ScreenInit},//==send initial data to DIWEN to display
	{0,	1, &screenTxHandle_JumpToHomePage},//==M1 event arrive:jump to HOME Page 
	{0,	2, &screenTxHandle_JumpToBanlingPage},//==M2 event arrive:jump to BALANCING Page , Physical keying trigger
	{0,	3, &screenTxHandle_JumpToCalibrationPage},//==M3 event arrive:jump to CALITRATION Page
	{0,	4, &screenTxHandle_JumpToActivePage},//==M4 event arrive:jump to ACTIVE Page
	{0,	5, &screenTxHandle_JumpToSysParaPage},//==M5 event arrive:jump to SYSPARA Page
	{0,	6, &screenTxHandle_FreshScreenLight},//==M6 event arrive:fresh sreen light
	{0,	7, &screenTxHandle_ChangeDisplayPosition},//==M7 event arrive:修改小数点
	{0,	8, &screenTxHandle_JmmpToBalancingPage},//==M2-1 event arrive: jump to BALANCING Page , screen touch trigger
	{0,	9, &screenTxHandle_JumpToBalancingCleanPage},//==M2-2 event arrive:jump to BALANCING (clean)page
	{0,	10, &screenTxHandle_JumpToBalancingHomePage},//==M2-3 event arrive:jump to BALANCING (home)page
	{0,	11, &screenTxHandle_ChanelChangedTrigerDeal},	//==C1 event arrive:At Calibration Page , chanel changed trigerd
	{0,	12, &screenTxHandle_ResetCalibrationTrigerHandle},//==C2 event arrive:At Calibration Page , calibration reset trigerd 
	{0,	13, &screenTxHandle_PointTrigerHandle},//==C3 event arrive:At Calibration Page , point trigerd
	{0,	14, &screenTxHandle_RemoveWeightTrigerHandle},//==B1 event arrive:At Balancing Page , remove weight trigerd
	{0,	15, &screenTxHandle_ScreenWeightAndColorAndVoiceHandle},//normaly weight color voice handle
};
 
//the Tx handle function group of larger screen
screenRxTxHandleType screenLargerTxHandle[SCREEN_LARGER_TX_HANDLE_TOTAL_NUM]=
{
	//priority index func_add
	{0,	0, &screenLargerTxHandle_ScreenInit},//==send initial data to DIWEN to display
	{0,	1, &screenLargerTxHandle_CycleData},//==send initial data to DIWEN to display
 
};
 
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
				}
				//store in flash
				else if(0 != (DMG_TRIGER_SAVE_SECOTOR_2&needStore))
				{
					storeSysDataToFlash_3030();
				}
			}
		}
		//
		t5lCtx->RxFinishFlag = FALSE;
	}
}
 
//all screen MainFunction
void sreenT5L_MainFunction(void)
{
	//update self CurTick
	g_ScreenHandle[ScreenIndex_Smaller].Ctx->CurTick++;
	g_ScreenHandle[ScreenIndex_Larger].Ctx->CurTick++;
 
	//handle rx data from SDWE
	screenT5L_RxFunction(&g_ScreenHandle[ScreenIndex_Smaller]);
	screenT5L_RxFunction(&g_ScreenHandle[ScreenIndex_Larger]);
	
	//prepare data and send to SDWE
	screenT5L_TxFunction(&g_ScreenHandle[ScreenIndex_Smaller]);
	screenT5L_TxFunction(&g_ScreenHandle[ScreenIndex_Larger]);
 
	//slave data valid
	setModbusDataValid(SLAVE_DATA_VALID);
}
