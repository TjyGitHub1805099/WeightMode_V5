#ifndef __APP_LED_CTRL_H__
#define __APP_LED_CTRL_H__

#include "typedefine.h"
#include "app_main_task.h"

#define LED_CTRL_DATA_LEN 	(3)

#define SYS_COLOR_GROUP_NUM		(4)//sys max color num
#define SYS_COLOR_USED_FLAG		(0X123)//color used
#define SYS_COLOR_NOT_USED_FLAG		(0)//color not used

//main task status
typedef enum LedSeqType
{
	LED_SEQ_1 = 0,    /**< LED 1控制 */
	LED_SEQ_2 ,       /**< LED 2控制 */
	LED_SEQ_3 ,       /**< LED 3控制 */
	LED_SEQ_4 ,       /**< LED 4控制 */
	LED_SEQ_5 ,       /**< LED 5控制 */
	LED_SEQ_6 ,       /**< LED 6控制 */
	LED_SEQ_NUM
}enumLedSeqType;

typedef enum LedColorType
{
	LED_COLOR_NONE = 0,		/**< LED 无 控制 */
	LED_COLOR_REG ,	/**< LED 红 控制 */
	LED_COLOR_GREEN,	/**< LED 绿 控制 */
	LED_COLOR_BLUE, 	/**< LED 蓝 控制 */
	LED_COLOR_WHITE,	/**< LED 白 控制 */
	LED_COLOR_NUM,
	LED_COLOR_LOCK=0X80,
}enumLedColorType;


#if(COLOR_ALT_20210606_DEFINE)

#define MATER_WEIGHT_CHANEL_NUM	HX711_CHANEL_NUM
#define SLAVE_WEIGHT_GROUP_NUM	1
#define SLAVE_WEIGHT_CHANEL_NUM	HX711_CHANEL_NUM

#define ALL_BALANCING_COLOR_NUM		(MATER_WEIGHT_CHANEL_NUM+(SLAVE_WEIGHT_GROUP_NUM*SLAVE_WEIGHT_CHANEL_NUM))
#define ALL_BALANCING_WEIGHT_NUM	(MATER_WEIGHT_CHANEL_NUM+(SLAVE_WEIGHT_GROUP_NUM*SLAVE_WEIGHT_CHANEL_NUM))

typedef struct BalancingGroupDataType
{
	float fMaster[MATER_WEIGHT_CHANEL_NUM];
	float fSlavers[SLAVE_WEIGHT_GROUP_NUM*SLAVE_WEIGHT_CHANEL_NUM];
	UINT8 u8MasterDataLen;
	UINT8 u8SlaversDataLen[SLAVE_WEIGHT_GROUP_NUM];
	UINT8 u8ClrValue[2][ALL_BALANCING_COLOR_NUM];
	UINT16 u16WgtValue[2][ALL_BALANCING_WEIGHT_NUM];
}sBalancingGroupDataType;

#endif

void led_init(void);
extern void led_MainFunction(void);
UINT8 LedDataSet(enumLedSeqType seq , enumLedColorType color);
void useWeightUpdateLedAndSdweColor(UINT8 hx711DataUpgrade);
void useWeightCompareOutColor(UINT8 hx711DataUpgrade);
extern void useWeightUpdataOutColor(UINT8 hx711DataUpgrade);
extern void useWeightUpdataOutColor_3030(UINT8 hx711DataUpgrade);
void LedSysTest(UINT32 ms_tick);
extern UINT8 led_test_flag ;
extern void balaningColorClear(void);


#if(COLOR_ALT_20210414_DEFINE)
extern void useWeightUpdataOutColor_20210414(UINT8 hx711DataUpgrade);
#endif

#if(COLOR_ALT_20210606_DEFINE)
extern void useWeightUpdataOutColor_20210606(UINT8 hx711DataUpgrade);
#endif



#endif
