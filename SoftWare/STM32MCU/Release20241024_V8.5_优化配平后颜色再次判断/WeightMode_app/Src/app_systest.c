#include "typedefine.h"
#include "app_systest.h"
#include "hal_gpio.h"
#include "app_led_ctrl.h"
#include "app_hx711_ctrl.h"
#include "app_main_task.h"
#include "app_key_ctrl.h"
#include "app_sdwe_ctrl.h"
#include "app_modbus_rtu_ctrl.h"

//============================================================================================
//========================================LED TEST START======================================
//============================================================================================
#if LED_CTRL_TEST//test
//==led test
void LedSysTest(UINT32 ms_tick)
{
	static UINT16 l_led_test_cycle = 1000;
	static enumLedColorType color = LED_COLOR_REG;
	enumLedSeqType seq = LED_SEQ_1;
	
	//every 1s change color:reg->yellow->blue->green
	if(0 == (ms_tick%l_led_test_cycle))
	{
		for(seq = LED_SEQ_1 ; seq < LED_SEQ_NUM ; seq++)
		{
			LedDataSet(seq,color);
		}
		
		color++;
		if( color >= LED_COLOR_NUM )
		{
			color = LED_COLOR_REG;
		}
	}
}
#endif
//============================================================================================
//========================================LED TEST END======================================
//============================================================================================

















//============================================================================================
//========================================T5L TEST START======================================
//============================================================================================
#if T5L_VOICE_PRITF
void T5L_VoicePritfTest(UINT32 sysTick)
{
	static tT5LVoinceType testVoiceId = VoiceTypeNum_1;
	if(1==(sysTick%4000))
	{
		sdwe_VoicePrintfPush(testVoiceId,(tT5LVoinceType)((testVoiceId+1)%VoiceTypeYu_13));
		{
			testVoiceId++;
			if(testVoiceId >= VoiceTypeYu_13)
			{
				testVoiceId = VoiceTypeNum_1;
			}
		}
	}
}
#endif

#if T5L_WEIGHT_COLOR_TEST
//==write varible data to SDWE thought UART
void sdweWriteVarible_dw(UINT16 varAdd, INT16 *pData ,UINT16 varlen ,UINT8 crcEn)
{
	//A5 5A 05 82 00 03 00 01:向0x0003地址写入数据0x0001
	UINT16 i = 0 ,l_data = 0 , total_len = 0 , crc = 0;
	if(varAdd < 0xFFFF)
	{
		if(((varAdd+varlen)>0)&&((varAdd+varlen)<0xFFFF))
		{
			//head
			g_T5L.txData[cmdPosHead1]=0x5A;
			g_T5L.txData[cmdPosHead2]=0XA5;
			//data len
			g_T5L.txData[cmdPosDataLen]=0X03+2*varlen;
			//order:write
			g_T5L.txData[cmdPosCommand]=cmdWriteSWDEVariable;
			//varAdd
			g_T5L.txData[cmdPosVarWriteAddress1]=0xff&(varAdd>>8);
			g_T5L.txData[cmdPosVarWriteAddress2]=0xff&(varAdd>>0);
			//data
			for(i=0;i<varlen;i++)
			{
				l_data = *pData++;
				g_T5L.txData[cmdPosVarWriteData+2*i+0] = 0xff&(l_data>>8);
				g_T5L.txData[cmdPosVarWriteData+2*i+1] = 0xff&(l_data>>0);
			}
			//crc
			if(TRUE == crcEn)
			{
				crc = cal_crc16(&g_T5L.txData[cmdPosCommand],(3+2*varlen));
				g_T5L.txData[cmdPosVarWriteData+2*varlen+0] = 0xff&(crc>>8);
				g_T5L.txData[cmdPosVarWriteData+2*varlen+1] = 0xff&(crc>>0);
				//total len
				total_len = cmdPosVarWriteData+2*varlen+2;
			}
			else
			{
				//total len
				total_len = cmdPosVarWriteData+2*varlen;
			}
			//send
			g_T5L.pUartDevice->tx_bytes(g_T5L.pUartDevice,&g_T5L.txData[0],total_len);
			//
			hal_delay_ms(1);
		}
	}
}

void sdwe_MainFunctionTest(void)
{
	//测试流程
	//1.chanelTestEn=1
	//0x2200后面10个地址为，校验模式，参考点 设定值
	//0x2300后面10个地址为，校验模式，参考点 校验状态设定值
	//0x2400后面10个地址为，校验模式，参考点 实际采样值
	
	//0x3000后面12个地址为，配平模式，各通道采样转换后的值
	//0x3100后面12个地址为，配平模式，各通道背景色值
	static UINT8 chanelTestEn= 0 ;
	static UINT32 cnt = 0 ;
	UINT8 i = 0 ;
	
	static UINT8 chanelDataEn= 0 ;
	static INT16 chanelDataAddress = 0x3000 ;//转换后数据
	static INT16 chanelDataTest[32] ={0};
	
	static UINT8 chanelColorEn = 0 ;
	static INT16 chanelColorAddress = 0x3100 ;//背景色
	static INT16 chanelColorTest[32] ={0};
	
	static INT16 chanelDataLen = 6;
	
	cnt++;
	if((1 == chanelTestEn) && 0 == (cnt%1000))
	{
		if(1 == chanelDataEn)
		{
			for(i=0;i<chanelDataLen;i++)
			{
				chanelDataTest[i]=cnt;
			}
			sdweWriteVarible_dw(chanelDataAddress,&chanelDataTest[0],chanelDataLen,0);
		}
		else if(1 == chanelColorEn)
		{
			for(i=0;i<chanelDataLen;i++)
			{
				switch(chanelColorTest[i])
				{
					case 0:chanelColorTest[i]=1;break;
					case 1:chanelColorTest[i]=2;break;
					case 2:chanelColorTest[i]=3;break;
					case 3:chanelColorTest[i]=4;break;
					case 4:chanelColorTest[i]=0;break;
					default:chanelColorTest[i]=0;break;
				}
			}
			sdweWriteVarible_dw(chanelColorAddress,&chanelColorTest[0],chanelDataLen,0);
		}
	}
}
#endif

//============================================================================================
//========================================T5L TEST END======================================
//============================================================================================



/*
//sdwe 10 point triger color data:arr0 is triger flag ,arr1 is color ,arr2 is sample data
static INT16 g_sdwe_triger_data[4][CHANEL_POINT_NUM]={{0},{0},{0}};



//==read SDWE version
void sdweReadVersion()
{
	sdweReadRegister(0x00 ,1 ,FALSE);
	//at sdwe answer
	//g_T5L.version = version;
}
//==when sdwe point triger,update g_sdwe_triger_data[]
void sdwePointTrigerUpdata(UINT8 point , UINT8 value ,INT16 avgSampleValue)
{
	if(point < CHANEL_POINT_NUM)
	{
		g_sdwe_triger_data[0][point] = TRUE;//point triger need answer flag	
		g_sdwe_triger_data[1][point] = value;//point triger color answer
		g_sdwe_triger_data[2][point] = avgSampleValue;//point triger avg sample value answer	
	}
}

//==get if not sdwe point triger
UINT8 getSdwePointTriger()
{
	UINT8 ret = 0 , i = 0 ;
	
	for(i=0;i<CHANEL_POINT_NUM;i++)
	{
		ret = g_sdwe_triger_data[0][i];//point triger need answer flag	
		if(1 == ret)
		{
			break;
		}
	}
	return ret;
}
//==sdwe triger point changed ,clear point triger
void clrSdwePointTriger()
{
	UINT8 i = 0 ;
	for(i=0;i<CHANEL_POINT_NUM;i++)
	{
		g_sdwe_triger_data[0][i] = FALSE ;//clr point triger need answer flag	
	}
}
//==sdwe triger chanel changed ,clear all
void clrSdwePointTrigerAll()
{
	UINT8 i = 0 ;
	for(i=0;i<CHANEL_POINT_NUM;i++)
	{
		g_sdwe_triger_data[0][i] = 0 ;//clr triger flag	
		g_sdwe_triger_data[1][i] = 0 ;//clr color data	
		g_sdwe_triger_data[2][i] = 0 ;//clr avg sample data	
	}
}




//==read register data from SDWE thought UART
void sdweReadRegister(UINT8 regAdd ,UINT8 regLen ,UINT8 crcEn)
{
	//A5 5A 03 81 03 02:读取03和04号寄存器数据
	//A5 5A (03) 81 XX len
	UINT16 total_len = 0 , crc = 0 ;
	
	if(regAdd < 0xFF)
	{
		if(((regAdd+regLen)>0)&&((regAdd+regLen)<0xFf))
		{
			//head
			g_T5L.txData[cmdPosHead1]=T5L_RX_FUN_HEAD1;
			g_T5L.txData[cmdPosHead2]=T5L_RX_FUN_HEAD2;
			//data len
			g_T5L.txData[cmdPosDataLen]=0X03;
			//order:write register
			g_T5L.txData[cmdPosCommand]=cmdReadSWDERegister;
			//address
			g_T5L.txData[cmdPosRegReadAddress]=regAdd;
			//len
			g_T5L.txData[cmdPosRegReadLen]=regLen;
			//crc
			if(TRUE == crcEn)
			{
				crc = cal_crc16(&g_T5L.txData[cmdPosCommand],(3));
				g_T5L.txData[cmdPosRegReadLen+1] = 0xff&(crc>>8);
				g_T5L.txData[cmdPosRegReadLen+2] = 0xff&(crc>>0);
				//total len
				total_len =cmdPosRegReadLen+3;
			}
			else
			{
				//total len
				total_len = cmdPosRegReadLen+1;
			}
			//send
			g_T5L.pUartDevice->tx_bytes(g_T5L.pUartDevice,&g_T5L.txData[0],total_len);
			//
			//hal_delay_ms(5);
		}
	}
}
//==write register data to SDWE thought UART
void sdweWriteRegister(UINT8 regAdd, UINT8 *pData ,UINT8 regLen ,UINT8 crcEn)
{
	//A5 5A 04 80 03 00 01:向03和04号寄存器写入数据00和01
	//A5 5A (02+n*DD) 80 XX n*DD
	UINT8 reg_i = 0 ;
	UINT16 total_len = 0 , crc = 0 ;
	if(regAdd < 0xFF)
	{
		if(((regAdd+regLen)>0)&&((regAdd+regLen)<0xFF))
		{
			//head
			g_T5L.txData[cmdPosHead1]=T5L_RX_FUN_HEAD1;
			g_T5L.txData[cmdPosHead2]=T5L_RX_FUN_HEAD2;
			//data len
			g_T5L.txData[cmdPosDataLen]=0X02+regLen;
			//order:write register
			g_T5L.txData[cmdPosCommand]=cmdWriteSWDERegister;
			//address
			g_T5L.txData[cmdPosRegWriteAddress]=regAdd;
			//data
			for(reg_i = 0 ; reg_i < regLen ; reg_i++)
			{
				g_T5L.txData[cmdPosRegWritesData+reg_i] = *(pData+reg_i);
			}
			//crc
			if(TRUE == crcEn)
			{
				crc = cal_crc16(&g_T5L.txData[cmdPosCommand],(2+1*regLen));
				g_T5L.txData[cmdPosRegWritesData+regLen+0] = 0xff&(crc>>8);
				g_T5L.txData[cmdPosRegWritesData+regLen+1] = 0xff&(crc>>0);
				//total len
				total_len = cmdPosRegWritesData+regLen+2;
			}
			else
			{
				//total len
				total_len = cmdPosRegWritesData+regLen;
			}
			//send
			g_T5L.pUartDevice->tx_bytes(g_T5L.pUartDevice,&g_T5L.txData[0],total_len);
			//
			hal_delay_ms(1);
		}
	}
}
//==read varible data from SDWE thought UART
void sdweReadVarible(UINT16 varAdd ,UINT16 varlen ,UINT8 crcEn)
{
	//A5 5A 04 83 00 03 02:读取0x0003和0x0004两个寄存器
	//A5 5A (04) 83 XX XX len
	UINT16 total_len = 0 , crc = 0;
	if(varAdd < 0xFFFF)
	{
		if(((varAdd+varlen)>0)&&((varAdd+varlen)<0xFFFF))
		{
			//head
			g_T5L.txData[cmdPosHead1]=T5L_RX_FUN_HEAD1;
			g_T5L.txData[cmdPosHead2]=T5L_RX_FUN_HEAD2;
			//data len
			g_T5L.txData[cmdPosDataLen]=0X04;
			//order:write
			g_T5L.txData[cmdPosCommand]=cmdReadSWDEVariable;
			//varAdd
			g_T5L.txData[cmdPosVarReadAddress1]=0xff&(varAdd>>8);
			g_T5L.txData[cmdPosVarReadAddress2]=0xff&(varAdd>>0);
			//len
			g_T5L.txData[cmdPosVarReadLen]=0xff&(varlen>>0);
			//crc
			if(TRUE == crcEn)
			{
				crc = cal_crc16(&g_T5L.txData[cmdPosCommand],(4));
				g_T5L.txData[cmdPosVarReadLen+1] = 0xff&(crc>>8);
				g_T5L.txData[cmdPosVarReadLen+2] = 0xff&(crc>>0);
				//total len
				total_len = cmdPosVarReadLen+3;
			}
			else
			{
				//total len
				total_len = cmdPosVarReadLen+1;
			}
			//send
			g_T5L.pUartDevice->tx_bytes(g_T5L.pUartDevice,&g_T5L.txData[0],total_len);
			//
			hal_delay_ms(1);
		}
	}
}

void sendBalancingModelData()
{
	static UINT8 need_send = 0;
	INT16 *pSendData= &g_t5l_dis_data[0];
	INT16 weight[HX711_CHANEL_NUM];	
	static INT16 weightPre[HX711_CHANEL_NUM]={1,1,1,1,1,1}; 
	enumHX711ChanelType chanel = HX711Chanel_1;
	
	static UINT8 inerStatus = 0 ;	
	
	UINT8 i = 0;

	//=============================================================weight value and color
	pSendData= &g_t5l_dis_data[0];
	for(chanel=HX711Chanel_1;chanel<HX711_CHANEL_NUM;chanel++)
	{
		weight[chanel] = (INT16)(hx711_getWeight(chanel)+0.5f);
		pSendData[chanel] = weight[chanel];
		//
		if(weight[chanel] != weightPre[chanel])
		{
			weightPre[chanel] = weight[chanel];
			need_send = TRUE ;
			inerStatus = 0 ;
		}
	}

	//
	if(TRUE == need_send)
	{

		switch(inerStatus)
		{
			case 0:
				if(((g_T5L.LastSendTick > g_T5L.CurTick)&&((g_T5L.LastSendTick-g_T5L.CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
					((g_T5L.LastSendTick < g_T5L.CurTick)&&((g_T5L.CurTick - g_T5L.LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
				{
					if(0 == gSystemPara.isCascade)
					{
						for(chanel=HX711Chanel_1;chanel<HX711_CHANEL_NUM;chanel++)
						{
							g_t5l_dis_data_buff[chanel] = g_t5l_dis_data[chanel];
						}
						t5lWriteVarible(DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pSendData,HX711_CHANEL_NUM,0);
					}
					else if(ModbusAdd_Master == gSystemPara.isCascade)
					{
						for(chanel=HX711Chanel_1;chanel<HX711_CHANEL_NUM;chanel++)
						{
							g_t5l_dis_data_buff[chanel] = g_t5l_dis_data[chanel];
						}
						t5lWriteVarible(DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS,pSendData,HX711_CHANEL_NUM,0);
					}
					//
					inerStatus=1;
					//
					//inerStatus=0;
					//need_send = FALSE;
				}
			break;
			case 1:
				if(((g_T5L.LastSendTick > g_T5L.CurTick)&&((g_T5L.LastSendTick-g_T5L.CurTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER))||
					((g_T5L.LastSendTick < g_T5L.CurTick)&&((g_T5L.CurTick - g_T5L.LastSendTick) >= DMG_MIN_DIFF_OF_TWO_SEND_ORDER)))
				{
					//
					pSendData= &g_t5l_dis_data[HX711_CHANEL_NUM];
					for(i=0;i<HX711_CHANEL_NUM;i++)
					{
						g_t5l_dis_data_buff[HX711_CHANEL_NUM+i] = g_t5l_dis_data[HX711_CHANEL_NUM+i];
					}
					t5lWriteVarible(DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS,pSendData,HX711_CHANEL_NUM,0);
					//
					inerStatus=2;
					//
					need_send = FALSE;
				}
			break;
			default:
				inerStatus = 0 ;
				need_send = FALSE;
			break;
		}
	}
}
















*/
