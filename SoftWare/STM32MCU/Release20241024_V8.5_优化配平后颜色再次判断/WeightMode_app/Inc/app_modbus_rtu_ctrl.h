
#ifndef __APP_MODBUS_RTU_H__
#define __APP_MODBUS_RTU_H__

#include "hal_uart.h"
#include "app_hx711_ctrl.h"

#define MODBUS_RTU_UART_DATA_LEN	(0X100)
#define MODBUS_RTU_CRC_EN			(TRUE)


#define MODBUS_RTU_SLAVE_CHANEL_NUM	(HX711_CHANEL_NUM)
#define MODBUS_RTU_SLAVE_DATA_LEN	(4*MODBUS_RTU_SLAVE_CHANEL_NUM)

//aa bb cc dd ee ff .. hh
//aa-> sender address
//bb-> recive address
//cc-> fuction code
//dd-> data len
//ee-> data
//hh-> crc of all
#define MODBUS_RTU_SEND_ADDRESS_POS	(0)//sender ID : master(1) or slave(2~n)
#define MODBUS_RTU_ASK_ADDRESS_POS	(1)//recive ID : master(1) or slave(2~n)
#define MODBUS_RTU_FUN_CODE_POS		(2)//function code :
#define MODBUS_RTU_DATA_LEN_POS		(3)//data len
#define MODBUS_RTU_DATA_STAR_POS	(4)//data start position

//changed at 20231014
//FuncA:seqence num was continuous but only display eight block 
#define ModbusFuncA_Master			(11)
#define ModbusFuncA_Slave			(12)

//slave address type
typedef enum ModbusAddType
{
	ModbusAdd_Master	= 1 ,//1:was the master ID
	ModbusAdd_Slave_1	= 2 ,//other:was the slave ID
	ModbusAdd_Slave_Max
}enumModbusAddType;

//function code def address type
typedef enum ModbusFuncCodeType
{
	MFC_Mater_Ask_6 = 0x06 ,//: MFC_Mater_Ask_6(1) + SetHelpDataToSlave1(2*group*num) + SendRemoveFlag(1)  + SendAllChnData(4*chn_num) + SendAllChnDataColor(2*chn_num)
	MFC_Slave_Ans_6 = 0x86  //: MFC_Slave_Ans_6(1) + SendRemoveFlag(1) + SelfAllChnData(4*sel_chn_num)
}enumModbusFuncCodeType;

//valid data len of master
#define MFC_MASTER_SEND_DATA_TOTAL_LEN_NO_CRC	(MODBUS_RTU_DATA_STAR_POS + 1 + 2*DIFF_TO_DIWEN_DATA_LEN + 1 + 4*T5L_MAX_CHANEL_LEN + 2*T5L_MAX_CHANEL_LEN)

//evern handle timer define
//======MasterTimer
#define MasterTimer_TxOrderDlay			(15)//15ms   : the diff time of two master order Delay
#define MasterTimer_RxTimeOut			(60)//60ms   : the timeout of master recv slave answer data , if timeouted retriger
#define MasterTimer_EventTriger_TX_T6	(200)//200ms : the diff time of master send order to slave

//======SlaveTimer
#define SlaveTimer_TxOrderDlay			(10)//10ms must leas than MasterTimer_TxOrderDlay

//even handle mask define
//======MasterEvent:TX
typedef UINT16 MasterEventTxMaskType;
#define MasterEvent_Tx_IDLE	(MasterEventTxMaskType)(0x0000)
#define MasterEvent_Tx_E6	(MasterEventTxMaskType)(0x0020)//MFC_Mater_Ask_6

//======MasterEvent:RX
typedef UINT16 MasterEventRxMaskType;
#define MasterEvent_Rx_IDLE	(MasterEventRxMaskType)(0x0000)

//======SlaveEvent:TX
typedef UINT16 SlaveEventTxMaskType;
#define SlaveEvent_Tx_IDLE	(SlaveEventTxMaskType)(0x0000)
#define SlaveEvent_Tx_E6	(SlaveEventTxMaskType)(0x0020)//MFC_Slave_Ans_6

//======SlaveEvent:RX
typedef UINT16 SlaveEventRxMaskType;
#define SlaveEvent_Rx_Idle	(SlaveEventRxMaskType)(0x0000)
#define SlaveEvent_Rx_E6	(SlaveEventRxMaskType)(0x0020)

typedef enum MasterStateType
{
	MasterState_Idle = 0 ,
	MasterState_AllowTx = 1 ,
	MasterState_WaitRx = 2,
}enumMasterStateType;
typedef enum SlaveStateType
{
	SlaveState_Idle = 0 ,
	SlaveState_AllowTx = 1 ,
	SlaveState_WaitRx = 2,
}enumSlaveStateType;


/** 定义从机串口设备类型 */
typedef struct structModbusRtuType
{
	UartDeviceType *pUartDevice;        /**< 串口设备 */
	UINT8 	rxData[MODBUS_RTU_UART_DATA_LEN];
	UINT8 	txData[MODBUS_RTU_UART_DATA_LEN];
	UINT8 	rxDataUart[MODBUS_RTU_UART_DATA_LEN];
	UINT16	RxLength;					/**< 接收字节数 */
	UINT8 	RxFinishFlag;				/**< 接收完成标志 */	
	UINT32	sysTick;
	unionFloatInt32	MultWeightData[ModbusAdd_Slave_Max - ModbusAdd_Master][MODBUS_RTU_SLAVE_CHANEL_NUM];
	
	//master
	enumMasterStateType 	masterState;
	MasterEventTxMaskType	masterTxMask;
	MasterEventRxMaskType	masterRxMask;
	UINT16 					masterTxDiffTick;
	UINT16 					masterMaxWaitRxTick;

	//slave
	enumSlaveStateType		slaveState;
	SlaveEventTxMaskType	slaveTxMask;
	SlaveEventRxMaskType	slaveRxMask;
	UINT16 					slaveTxDiffTick;

	UINT8	needSendLen;
	UINT8 	slaveID;
	UINT8	removeWeight_Slef;
	UINT8	removeWeight_Other;
	UINT8   dataValid;
}ModbusRtuType;

#define SLAVE_DATA_VALID (0XA5)
/** ModbusRtu设备默认配置 */
#define ModbusRtuDefault   { \
	&g_UartDevice[UART_COM], \
	{0}, \
	{0}, \
	{0}, \
	0,\
	0,\
	0,\
	{{0}},\
	MasterState_Idle,\
	MasterEvent_Tx_IDLE,\
	MasterEvent_Rx_IDLE,\
	0,\
	0,\
	SlaveState_Idle,\
	SlaveEvent_Tx_IDLE,\
	SlaveEvent_Rx_Idle,\
	0,\
	0,\
	0,\
	FALSE,\
	FALSE,\
	0,\
	}
	
extern ModbusRtuType g_ModbusRtu;

extern void ModbusRtu_init(void);
extern void ModbusRtu_MainFunction(void);

extern void setModbusSelfRemoveFlag(UINT8 value);
extern void setModbusOtherRemoveFlag(UINT8 value);
extern void modbusRemoveAllWeightData(void);
extern UINT8 getModbusOtherRemoveFlag(void);
extern void setModbusDataValid(UINT8 value);

#endif
