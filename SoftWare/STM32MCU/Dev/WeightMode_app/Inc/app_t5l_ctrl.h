#ifndef __APP_T5L_CTRL_H__
#define __APP_T5L_CTRL_H__
#include "app_sdwe_ctrl.h"


#include "hal_uart.h"
#include "app_hx711_ctrl.h"

#define T5L_DMG_UART_TX_USE_DMA	(1)

#define T5L_DMG_UART_DATA_LEN	(0X100)

//================================================================================================
//==(update:20210328):DIWEN reserve (uodate to v3:2021.03.26)
#define DMG_MIN_DIFF_OF_TWO_SEND_ORDER			(20)//20ms 
#define DMG_DATA_HOLD_TIME						(250)//250ms

//==(update:20210328):address of set chanel number : 0->all chanel set  ; (1~8)->single chanel set
#define DMG_FUNC_SET_CHANEL_NUM					(0X2100)
//==(update:20210328):address of reset calibration of choice chanel number : 0->all chanel set  ; (1~x)->single chanel set
#define DMG_FUNC_RESET_CALIBRATION_ADDRESS		(0X2101)
//==(update:20210328):value of reset calibration of choice chanel number:2021 reset calibration
#define DMG_FUNC_RESET_CALIBRATION_VAL	 		(2021)

//==(update:20210328):address of remove weight
#define DMG_FUNC_REMOVE_WEIGHT_ADDRESS			(0X2102)
#define DMG_FUNC_REMOVE_WEIGHT_VAL				(0XA55A)

//==(update:20210428):address of remove weight
#define DMG_FUNC_JUNPTO_CALIBRATION_ADDRESS		(0X2103)
#define DMG_FUNC_JUNPTO_CALIBRATION_VAL			(2021)
#define DMG_FUNC_JUNPTO_ACTIVE_VAL				(1202)

//==(update:20211119):address of syspara entry
#define DMG_FUNC_JUNPTO_SYSPAR_ADDRESS		(0X2104)
#define DMG_FUNC_JUNPTO_SYSPAR_VAL			(1010)

//==(update:20210328):address of set point(weight value) of chanel : (0~9)-> point of chanel set (:g)
#define DMG_FUNC_SET_CHANEL_POINT_ADDRESS		(0X2200)//0x2200~0x2209

//==(update:20210328):address of set point of chanel triger : (0~9)-> point of chanel set triger(val=0x12FE(DMG triger MCU))
#define DMG_FUNC_SET_CHANEL_POINT_TRIG_ADDRESS	(0X2500)//0x2500~0x2509
#define DMG_FUNC_SET_CHANEL_POINT_TRIG_VAL		(0X12FE)


//==(update:20210328):address of triger COLOR back to DMG : (0~9)-> COLOR of point of chanel set triger(val=0x00:white(not triger),val=0x01green(triger))
#define DMG_FUNC_ASK_CHANEL_POINT_TRIG_BACK_COLOR_ADDRESS	(0X2300)//0x2300~0x2309

//==(update:20210328):address of triger sample back to DMG : (0~9)-> COLOR of point of chanel set triger(val=0x00:white(not triger),val=0x01green(triger))
#define DMG_FUNC_ASK_CHANEL_POINT_TRIG_SAMPLE_DATA_ADDRESS	(0X2400)//0x2400~0x2409

//==(update:20210328):address of weight back to DMG : (0~7)-> weight of chanel(val:g)
#define DMG_FUNC_ASK_CHANEL_WEIGHT_ADDRESS		(0X3000)//0x3000~0x300F 4byte each chanel
//==(update:20210328):address of color back to DMG : (0~7)-> color of chanel(val:g)
#define DMG_FUNC_ASK_CHANEL_COLOR_ADDRESS		(0X3100)//0x3100~0x3107


//==(update:20210411):address of unit min max ...
#define DMG_FUNC_SET_UNIT_ADDRESS				(0X1000)//0x1000

#define DMG_FUNC_SET_MIN_RANGE_ADDRESS			(0X100A)//0x100A
#define DMG_FUNC_SET_MAX_RANGE_ADDRESS			(0X100B)//0x100B
#define DMG_FUNC_SET_ERR_RANGE_ADDRESS			(0X100C)//0x100C
#define DMG_FUNC_SET_isCascade_ADDRESS			(0X100D)//0x100D
#define DMG_FUNC_SET_isLedIndicate_ADDRESS		(0X100E)//0x100E
#define DMG_FUNC_SET_COLOR_START_ADDRESS		(0X100F)//0x100F
#define DMG_FUNC_SET_COLOR_END_ADDRESS			(0X1012)//0x1012
#define DMG_FUNC_SET_ZERO_RANGE_ADDRESS			(0X1013)//0x1013
#define DMG_FUNC_SET_SCREEN_LIGHT_ADDRESS		(0X1014)//0x1014
#define DMG_FUNC_SET_VOICE_NUM_TOUCH_ADDRESS 	(0X1015)//0x1015
#define DMG_FUNC_SET_VOICE_NUM_ADDRESS			(0X1016)//0x1016
#define DMG_FUNC_SET_VOICE_SWITCH_ADDRESS		(0X1017)//0x1017
#define DMG_FUNC_SET_CAST_SWITCH_ADDRESS		(0X1018)//0x1018
#define DMG_FUNC_SET_FLASH_ERASEE_TIMES_ADDRESS	(0X1019)//0x1019
#define DMG_FUNC_MCU_VERSION_ADDRESS			(0X101A)//0x101A
#define DMG_FUNC_DIWEN_VERSION_ADDRESS			(0X101B)//0x101B
#define DMG_FUNC_DIWEN_XIAOSHU_ADDRESS			(0X101C)//0X101C 小数使能
#define DMG_FUNC_DIWEN_BILV_ADDRESS				(0X101D)//0X101D ml/g比率
#define DMG_FUNC_DIWEN_DAPING_ADDRESS			(0X101E)//0X101E 大屏显示

#define DMG_FUNC_MCUID_ADDRESS				(0X1500)//0x1500

#define DMG_FUNC_PASSORD_SET_ADDRESS		(0X1510)//0x1510

#define DMG_FUNC_Balancing_SET_ADDRESS				(0X1101)//0x1101
#define DMG_FUNC_Balancing_SET_VALUE				(0X1101)//0x1101
#define DMG_FUNC_Balancing_HOME_SET_ADDRESS			(0X1102)//0x1102
#define DMG_FUNC_Balancing_HOME_SET_VALUE			(0X1102)//0x1102
#define DMG_FUNC_Balancing_CLEARPAGE_SET_ADDRESS	(0X1103)//0x1103
#define DMG_FUNC_Balancing_CLEARPAGE_SET_VALUE		(0X1103)//0x1103

#define DMG_FUNC_HELP_TO_JUDGE_SET_ADDRESS	(0X1201)//0x1201

#define DMG_SYS_STATUS_OF_VOICE_PRINTF_00A1	(0X00A1)

#define DMG_SYS_CUR_PAGE_GET_ADD			(0X0014)
#define DMG_SYS_VERSION_GET_ADD				(0X000E)

#define SYS_SOFTWARE_RESET_ADD				(0x6666)
#define SYS_SOFTWARE_RESET_VLU				(0xA55A)

//at BALANCING Page , auto to judge the remaining chanel weight minus
//to help user to caculate
//1.find out the remaining chanel
//2.find out the closed group(minus was smallest)
//3.send to DIWEN Screen to display

#define DIFF_JUDGE_GROUP_NUM_SLAVE1	(4)//4 group help data display 
#define DIFF_JUDGE_DATA_NUM_SLAVE1	(3)//num1 num2 minus
#define DIFF_TO_DIWEN_DATA_LEN		(DIFF_JUDGE_GROUP_NUM_SLAVE1*DIFF_JUDGE_DATA_NUM_SLAVE1)

//================================================================================================
//枚举：大小屏序号
typedef enum
{
	ScreenIndex_Smaller  = 0 ,
	ScreenIndex_Larger = 1 ,	
	ScreenIndex_Max,
}enumScreenIndexType;

//枚举：语音控制流程
typedef enum
{
	cmdWaitVoivePrint_forceRead  = 0 ,
	cmdWaitVoivePrint_waitResult = 1 ,	
	cmdWaitVoivePrint_max,
}enumSDWEcmdWaitVoivePrintType;

//枚举：小屏界面序号
//DMG PageType
typedef enum DMGPageType
{
	DMG_FUNC_Balancing_6_PAGE = 49,
	DMG_FUNC_Balancing_6_HOME_PAGE = 57,
	DMG_FUNC_Balancing_12_PAGE = 55,
	DMG_FUNC_Balancing_12_HOME_PAGE =58,
	DMG_FUNC_Help_PAGE =59
}enumDMGPageType;

//语音队列：深度
#define T5L_VOICE_MAX_PRINTF_NUM		(6)

//语音序号
typedef enum VoinceType
{
	T5L_VoiceTypeNum_0 = 0,
	T5L_VoiceTypeNum_1 = 1,
	T5L_VoiceTypeNum_2 = 2,
	T5L_VoiceTypeNum_3 = 3,
	T5L_VoiceTypeNum_4 = 4,
	T5L_VoiceTypeNum_5 = 5,
	T5L_VoiceTypeNum_6 = 6,
	T5L_VoiceTypeNum_7 = 7,
	T5L_VoiceTypeNum_8 = 8,
	T5L_VoiceTypeNum_9 = 9,
	T5L_VoiceTypeNum_10 = 10,
	T5L_VoiceTypeNum_11 = 11,
	T5L_VoiceTypeNum_12 = 12,
	T5L_VoiceTypeNum_13 = 13,
	T5L_VoiceTypeNum_14 = 14,
	T5L_VoiceTypeNum_15 = 15,
	T5L_VoiceTypeNum_16 = 16,
	VoiceTypeYu_17 = 17,
	VoiceTypePeiPin_18 = 18,
	VoiceTypeMax,
}tT5LVoinceType;

//ask calibration page data
typedef enum CalibrationAskParaType
{
	DMG_TRIGER_SAMPLE_OF_STATUS = 0 ,		/* trigerStarus */
	DMG_TRIGER_SAMPLE_OF_ASK_COLOR = 1 ,	/* back color of point*/
	DMG_TRIGER_SAMPLE_OF_AVG_SAMPLE = 2 ,	/* avg sample of point*/
	DMG_TRIGER_SAMPLE_OF_ASK_WEIGHT = 3 ,	/* set weight of point */
	DMG_TRIGER_SAMPLE_MAX_NUM
}enumCalibrationAskParaType;

//迪文屏幕通信协议：命令头
typedef enum sdweRxFuncIdType
{
	/**< SDWE_RX_0X83 举例
	1：A5 5A 06 83 01 FF 01 00 01 ; 代表 add = 0x01ff(校准通道号选择) , len = 0x01 , data = 0x0001 
	解释：校准通道选择 (add=0x01ff , len = 1), data=0:所有通道 data=1~8:代表具体通道
	2:A5 5A 06 83 03 00 01 00 0A
	解释：对于通道下的校准点选择 (add=0x0300 , len = 1), data=1~11:具体点(十段总共11点)
	*/
	T5L_RX_FUN_HEAD1 = 0X5A, /**< SDWE HEAD1*/
	T5L_RX_FUN_HEAD2 = 0XA5, /**< SDWE HEAD2*/
	SDWE_RX_FUN_0X83 = 0X83, /**< SDWE 设置变量 下发给MCU*/
	SDWE_RX_FUN_NUM	 		 /**< SDWE 总数量*/
}enumsdweRxFuncIdType;

//迪文屏幕通信协议：寄存器及变量读写命令
typedef enum
{
	cmdWriteSWDERegister = 0x80 ,
	cmdReadSWDERegister = 0x81 ,
	cmdWriteSWDEVariable = 0x82 ,
	cmdReadSWDEVariable = 0x83 ,
}enumSDWEcmdType;

//迪文屏幕通信协议：数据位置含义
typedef enum
{
	cmdPosHead1  = 0 ,//A5
	cmdPosHead2  = 1 ,//5A
	cmdPosDataLen= 2 ,//last data len
	cmdPosCommand= 3 ,//command position

	//=======MCU->SDWE order
	//read register 
	cmdPosRegReadAddress= 4 ,//reg address one byte position
	cmdPosRegReadLen= 5 ,//reg address one byte position
	//write register 
	cmdPosRegWriteAddress= 4 ,//reg address one byte position
	cmdPosRegWritesData= 5 ,//reg address one byte position

	//read varible 
	cmdPosVarReadAddress1= 4 ,//val address two byte position
	cmdPosVarReadAddress2= 5 ,//val address two byte position
	cmdPosVarReadLen= 6 ,//val address two byte position
	//write varible 
	cmdPosVarWriteAddress1= 4 ,//val address two byte position
	cmdPosVarWriteAddress2= 5 ,//val address two byte position
	cmdPosVarWriteData= 6 ,//val address two byte position

	//=======SDWE->MCU order
	//read register
	cmdPosRegAddress= 4 ,//reg address one byte position
	cmdPosReadRegAskLen= 5 ,//when read data ask data len position
	cmdPosRegData= 6 ,//reg address one byte position
	//read varible
	cmdPosVarAddress1= 4 ,//val address two byte position
	cmdPosVarAddress2= 5 ,//val address two byte position
	cmdPosReadVarAskLen= 6 ,//when read data ask data len position
	cmdPosVarData1= 7 ,//val address two byte position

		//write varible color 
	cmdPosVarWriteAddress1color= 4 ,//val address two byte position
	cmdPosVarWriteAddress2color= 5 ,//val address two byte position
	cmdPosVarWriteColorOrder1color= 6 ,//val address two byte position
	cmdPosVarWriteColorOrder2color= 7 ,//val address two byte position
	cmdPosVarWriteColorOrder3color= 8 ,//val address two byte position
	cmdPosVarWriteColorOrder4color= 9 ,//val address two byte position
	cmdPosVarWriteColorXPos= 10 ,//val address two byte position




	cmdPosVarWriteDatacolor= 6 ,//val address two byte position

}enumSDWEcmdPosType;

typedef enum
{
	SCREEN_STATUS_GET_VERSION = 0 ,
	SCREEN_STATUS_SEND_BANLING_DATA,
}enumSDWEStatusType;
typedef enum
{
	SCREEN_CYCLE_DATA_HANDLE_JUDGE_WEIGHT_DATA = 0X00,
	SCREEN_CYCLE_DATA_HANDLE_SEND_WEIGHT_DATA = 0X01,
	//
	SCREEN_CYCLE_DATA_HANDLE_JUDGE_COLOR_DATA = 0X10,
	SCREEN_CYCLE_DATA_HANDLE_SEND_COLOR_DATA = 0X11,
	//
	SCREEN_CYCLE_DATA_HANDLE_JUDGE_VOICE_DATA = 0X20,
	SCREEN_CYCLE_DATA_HANDLE_SEND_VOICE_DATA = 0X21,
	//
	SCREEN_CYCLE_DATA_HANDLE_JUDGE_HELP_DATA = 0X30,
	SCREEN_CYCLE_DATA_HANDLE_SEND_HELP_DATA = 0X31,
	//
	SCREEN_CYCLE_DATA_HANDLE_DEFAULT
}enumScreenCycleDataHandleStatusType;


typedef struct structScreenCycleType
{
	//chanel_len
	UINT8 chanel_len;
	//weight data
	INT32 *pData;
	INT32 *pDataPre;
	INT16 *pDataSendToDiWen;
	//color data
	INT16 *pColor;
	INT16 *pColorPre;
	INT16 *pColorOtherCh;
	//help data
	float *pSortWeight;
	INT16 *pSortArry;
	INT16 *pHelp;
	INT16 *pHelpPre;
}ScreenCycleType;
/** 定义从机串口设备类型 */
typedef struct structSdweType
{
	enumSDWEStatusType status;				/**< status ：sdwe 状态 */

	ScreenCycleType screenCycle;

	UINT8 	sendSdweInit;					/**< sendSdweInit ：初始化屏幕完成状态*/
	UINT8 	readSdweInit;					/**< readSdweInit ：状态 */
	
	enumUartPortType uartIndex;				/**< uartIndex ： 串口的序号 */
	UartDeviceType *pUartDevice;        	/**< pUartDevice：串口设备 */
	
	UINT8 	version;						/**< version：屏幕的版本值 */
	
	UINT8 	rxData[T5L_DMG_UART_DATA_LEN];	/**< rxData：接收到屏幕的缓存 */
	UINT8 	txData[T5L_DMG_UART_DATA_LEN];	/**< txData：发送到屏幕的缓存 */
	UINT16	RxLength;						/**< RxLength ：接收字节数 */
	UINT8 	RxFinishFlag;					/**< RxFinishFlag ：接收完成标志 */
	
	UINT16  SetAdd;							/**< SetAdd：屏幕发过来的数据变量的地址 */
	INT16  	DataLen;						/**< DataLen：屏幕发过来的数据长度 */
	INT16  	SetData;						/**< SetData：屏幕发过来的数据 */

	UINT16 	sdweRemoveWeightTriger;			/**< sdweRemoveWeightTriger：(事件)去皮 */
	UINT16 	sdwePointTriger;				/**< sdwePointTriger：(事件)点触发校准 */
	UINT16 	sdweResetTriger;				/**< sdweResetTriger：(事件)重新校准 */
	UINT16 	ResetTrigerValid;				/**< ResetTrigerValid：(事件)重新校准有效 */
	UINT16 	sdweChanelChanged;				/**< sdweChanelChanged：(事件)通道改变 */
	UINT16 	ColorClen;						/**< ColorClen：(事件)通道改变时清颜色 */
	UINT16 	CalibrateChanel;						/**< CalibrateChanel：称重校准的通道号 */
	UINT16 	CalibratePoint;							/**< CalibratePoint：称重校准的校准点 */
	INT32 	CalibratePointArry[CHANEL_POINT_NUM];	/**< CalibratePointArry：称重校准的校准点数组 */
	
	UINT32	CurTick;					/**< CurTick：当前系统时间 */
	UINT32	LastSendTick;				/**< LastSendTick：上次发送给屏幕的时间 */
	
	UINT16 	sdweJumpToCalitrationPage;	/**< sdweJumpToCalitrationPage：(事件)跳转至校准页面 */
	UINT16	sdweJumpToHomePage;			/**< sdweJumpToHomePage：(事件)跳转至主页面 */
	UINT16	sdweJumpToBanlingPage;		/**< sdweJumpToBanlingPage：(事件)跳转至配平页面 */
	UINT16 	sdweJumpActivePage;			/**< sdweJumpActivePage：(事件)跳转至激活页面 */
	UINT16 	sdweJumpBalancing;			/**< sdweJumpBalancing：(事件)跳转至配平页面 */
	UINT16 	sdweJumpBalancing_home;		/**< sdweJumpBalancing_home：(事件)跳转至配平页面可去皮 */
	UINT16 	sdweJumpBalancing_cleanpagee;/**< sdweJumpBalancing_cleanpagee：(事件)跳转至配平清爽页面 */
	UINT16 	sdweJumpToSysParaPage;		/**< sdweJumpToSysParaPage：(事件)跳转至参数页面 */
	UINT16 	sdweFreshScreenLight;		/**< sdweFreshScreenLight：(事件)刷新背光亮度 */
	UINT16  sdweChangeDescriblePoint;	/**< sdweChangeDescriblePoint：(事件)修改小数显示 */
	UINT16  sdwePowerOn;				/**< sdwePowerOn：(事件)屏幕已经上电 */
	UINT16  sdweHX711FirstSampleCoplt;	/**< sdweHX711FirstSampleCoplt：(事件)HX711数据采集完成 */
	UINT8 	needStore;					/**< needStore：(事件)是否需要保存*/
	UINT8 	sendSysParaDataToDiwenIndex;/**< sendSysParaDataToDiwenIndex：(事件)初始化屏幕时的序号*/
}T5LType;

#define ScreenCycleTypeDefault   { \
	/*chanel_len*/\
	0,\
	/*weight data*/\
	0,\
	0,\
	0,\
	/*color data*/\
	0,\
	0,\
	0,\
	/*help data*/\
	0,\
	0,\
	0,\
	0,\
}






/** ModbusRtu设备默认配置 */
#define T5LDataDefault   { \
	SCREEN_STATUS_GET_VERSION,/*status ：sdwe 状态*/\
	ScreenCycleTypeDefault,\
	0,/**/\
	0,/**/\
	\
	UART_EXTERN,/**< uartIndex ： 串口的序号 */\
	&g_UartDevice[UART_EXTERN],/**< pUartDevice：串口设备 */\
	\
	0,/**< version：屏幕的版本值 */\
	\
	{0},/**< rxData：接收到屏幕的缓存 */\
	{0},/**< txData：发送到屏幕的缓存 */\
	0,/**< RxLength ：接收字节数 */\
	0,/**< RxFinishFlag ：接收完成标志 */\
	\
	0XFFFF,/**/\
	0,/**/\
	0,/**/\
	\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	88,/**/\
	0,/**/\
	{0},/**< CalibratePointArry：称重校准的校准点数组 */\
	\
	0,/**/\
	0,/**< LastSendTick：上次发送给屏幕的时间 */\
	\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0x80,/**< sendSysParaDataToDiwenIndex：(事件)初始化屏幕时的序号*/\
	}

/** ModbusRtu设备默认配置 */
#define T5LDataDefault2   { \
	SCREEN_STATUS_GET_VERSION,/*status ：sdwe 状态*/\
	ScreenCycleTypeDefault,\
	0,/**/\
	0,/**/\
	\
	UART_EXTERN2,/**< uartIndex ： 串口的序号 */\
	&g_UartDevice[UART_EXTERN2],/**< pUartDevice：串口设备 */\
	\
	0,/**< version：屏幕的版本值 */\
	\
	{0},/**< rxData：接收到屏幕的缓存 */\
	{0},/**< txData：发送到屏幕的缓存 */\
	0,/**< RxLength ：接收字节数 */\
	0,/**< RxFinishFlag ：接收完成标志 */\
	\
	0XFFFF,/**/\
	0,/**/\
	0,/**/\
	\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	88,/**/\
	0,/**/\
	{0},/**< CalibratePointArry：称重校准的校准点数组 */\
	\
	0,/**/\
	0,/**< LastSendTick：上次发送给屏幕的时间 */\
	\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0,/**/\
	0x80,/**< sendSysParaDataToDiwenIndex：(事件)初始化屏幕时的序号*/\
	}
//================================================================================================


//================================================================================================
typedef UINT8 (*screenRxTxHandleFunc)(T5LType *pSdwe);  // 定义屏幕指令接收发送处理函数指针： screenRxTxHandleFunc

typedef struct screenRxTxHandleType_Struct
{
	UINT8 priority;
	UINT8 index;
	screenRxTxHandleFunc func;
}screenRxTxHandleType;

typedef struct structScreenHandleType
{
	enumScreenIndexType index;
	T5LType *Ctx;
	UINT8 recvScreenHadlleNum;
	screenRxTxHandleType *recvScreenHadlleCtx;
	UINT8 sendScreenHadlleNum;
	screenRxTxHandleType *sendScreenHadlleCtx;
}ScreenHandleType;

#define SCREEN_RX_HANDLE_TOTAL_NUM	(15)	/**< 屏幕RX数据处理事件数量 */
#define SCREEN_TX_HANDLE_TOTAL_NUM	(16)	/**< 屏幕TX数据处理事件数量 */
extern screenRxTxHandleType screenRxHandle[SCREEN_RX_HANDLE_TOTAL_NUM];
extern screenRxTxHandleType screenTxHandle[SCREEN_TX_HANDLE_TOTAL_NUM];

#define SCREEN_LARGER_RX_HANDLE_TOTAL_NUM	(2)	/**< 屏幕RX数据处理事件数量 */
#define SCREEN_LARGER_TX_HANDLE_TOTAL_NUM	(2)	/**< 屏幕TX数据处理事件数量 */
extern screenRxTxHandleType screenLargerRxHandle[SCREEN_LARGER_RX_HANDLE_TOTAL_NUM];
extern screenRxTxHandleType screenLargerTxHandle[SCREEN_LARGER_TX_HANDLE_TOTAL_NUM];

#define ScreenHandleDefault_Smaller   { \
	ScreenIndex_Smaller,\
	&g_T5LCtx[ScreenIndex_Smaller],\
	SCREEN_RX_HANDLE_TOTAL_NUM,\
	&screenRxHandle[0],\
	SCREEN_TX_HANDLE_TOTAL_NUM,\
	&screenTxHandle[0],\
}
#define ScreenHandleDefault_Larger   { \
	ScreenIndex_Larger,\
	&g_T5LCtx[ScreenIndex_Larger],\
	SCREEN_LARGER_RX_HANDLE_TOTAL_NUM,\
	&screenLargerRxHandle[0],\
	SCREEN_LARGER_TX_HANDLE_TOTAL_NUM,\
	&screenLargerTxHandle[0],\
}

//================================================================================================
#define T5L_INITIAL_COMPLETE		(0X12)//屏初始化完成标志
#define T5L_MAX_CHANEL_LEN			(2*HX711_CHANEL_NUM)
#define T5L_CHANEL_WEIGHT_NOT_EQUAL	(0XFF)
#define T5L_L_HELP_TOTAL_NUM		(6)	
#define DESCRIBLE_POINT_HELP_NUM	(4)//4组帮助信息

//================================================================================================
extern T5LType g_T5LCtx[ScreenIndex_Max];
extern ScreenHandleType g_ScreenHandle[ScreenIndex_Max];
extern INT16 g_i16ColorOtherChanel[T5L_MAX_CHANEL_LEN];//T5L_CHANEL_WEIGHT_NOT_EQUAL:invalid

//================================================================================================
extern void color_clearAllColor(void);
extern void allScreenCtx_Init(void);
extern void pointSampleTrigerDataSet(UINT8 localChanel , UINT8 point , INT16 value);
extern void pointWeightTrigerDataSet(UINT8 localChanel , UINT8 point , INT16 value);
extern void sdwe_VoicePrintfPush(tT5LVoinceType u8Voice1 ,tT5LVoinceType u8Voice2);
extern void pointWeightTrigerDataSet(UINT8 localChanel , UINT8 point , INT16 value);
extern void sreenT5L_MainFunction(void);
extern void writeHelpDataFromCom(UINT8 *pHelpData,UINT8 len);
extern void readHelpDataFromSys(UINT8 *pHelpData,UINT8 len);
extern void t5lDisPlayDataClear(void);
extern void readWeightDataFromSys(UINT8 *pWeightData,UINT8 len);
extern void readColorDataFromSys(UINT8 *pColorData,UINT8 len);
extern void writeWeightDataFromCom(UINT8 *pWeightData,UINT8 len);
extern void writeColorDataFromCom(UINT8 *pColorData,UINT8 len);
extern UINT8 screenT5L_OutputVoice(T5LType *pSdwe,UINT8 voiceId);

#endif
