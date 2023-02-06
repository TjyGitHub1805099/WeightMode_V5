#ifndef __APP_HX711_CTRL_H__
#define __APP_HX711_CTRL_H__

#include "typedefine.h"
#include "app_led_ctrl.h"
#include "app_main_task.h"

//sample NUM
typedef enum HX711ChanelType
{
	HX711Chanel_1 = 0,  /**< HX711  1控制 */
	HX711Chanel_2 ,      /**< HX711  2控制 */
	HX711Chanel_3 ,      /**< HX711  3控制 */
	HX711Chanel_4 ,      /**< HX711  4控制 */
	HX711Chanel_5 ,      /**< HX711  5控制 */
	HX711Chanel_6 ,      /**< HX711  6控制 */
	HX711_CHANEL_NUM,	 /**< HX711  总数量 hardware chanel number */
	HX711_CHANEL_LOCKED=0X80,
	HX711_CHANEL_UNLOCKED=0X81
}enumHX711ChanelType;

#define HX711_DATA_SAMPLE_TYPE 	(25)//hx711 sample type ;25:used chanel A 128 gain
#define HX711_DATA_SAMPLE_WIDE 	(10)//us:careful not lager than 50us 

#define HX711_DATA_SAMPLE_NUM 	(10)//each chanel filter number
#define HX711_MAX_WAIT_TIME 	(650)//ms:the max wait Data line from high -> low

//HX711 POWER ON CHECK
#define HX711_ON_LINE_CHECK_TIME			(SYS_HX711_ONLINE_CHECK_TIME)//ms
#define HX711_POWERON_AHEAD_WAIT_TIME 		(10)//ms:the max wait Data when power off
#define HX711_POWERON_CHECK_OK_MINUS_TIME	(500)//when hx711 from power off -> power on , need 4 cycle , reback to normal 
//#define HX711_POWERON_ONLINE_CHECK_OK_TIME	(0.5*(HX711_MAX_WAIT_TIME-HX711_POWERON_CHECK_OK_MINUS_TIME))
#define HX711_POWERON_ONLINE_CHECK_OK_TIME	(50)
#define HX711_ON_LINE_CHECK_TOTAL_TIME		(HX711_ON_LINE_CHECK_TIME/(HX711_MAX_WAIT_TIME+HX711_POWERON_AHEAD_WAIT_TIME))
#define HX711_ON_LINE_CHECK_PASS_NUM		(0.7*HX711_ON_LINE_CHECK_TOTAL_TIME)

#define HX711_NOT_ON_LINE_DEFAULT_VLU		(0)

#define HX711_DEFAULT_DATA		(0X1FFFFFF)
#define HX711_NEGATIVE_DATA		(0X1000000)//if lager than this data ,it's negative data


#define CHANEL_FILTER_NUM	(7)

#define CHANEL_POINT_NUM	(10)//must lager than 2 , used to cal k & b


#define CHANEL_MAX_WEIGHT	(5000)
#define CHANEL_DEFAULT_K	(float)(0.001223)//defaule k
#define CHANEL_DEFAULT_B	(float)(-267.71)//default b

#define CHANEL_MAX_ERR_RANGE	(float)(2.0)//2.0g
#define CHANEL_MAX_TACKOUT_RANGE	(float)(10.0)//10.0g

#define COMAPRE_SPECIAL_FLAG	(0X10)
#define COMPARE_USED_COLOR		(0XF00)
#define WEIGHT_DIRECTION_FW	(0)
#define WEIGHT_DIRECTION_BW	(1)

typedef union
{
	UINT8 u_value[4];
	INT32 i_value;
	float f_value;
}unionFloatInt32;

typedef struct
{
	enumLedSeqType ledType;
	UINT8 	initFlag;
	UINT8	sampleCycle;//only single cycle sample done ,allow to calculate total
	
	UINT8	sample_offset;
	INT32	sample_Arr[CHANEL_FILTER_NUM];
	INT32	sample_TotalValue;
	INT32	sample_AvgValue;

	UINT8	calibrationArr[CHANEL_POINT_NUM];//if not calibration used to judge weight direction
	
	//need storeLstart
	INT32	section_PointSample[CHANEL_POINT_NUM];
	INT32	section_PointWeight[CHANEL_POINT_NUM];
	float 	section_K[CHANEL_POINT_NUM+1];//0:degative  CHANEL_POINT_NUM+1:out range;this 2 status use default K & B
	float 	section_B[CHANEL_POINT_NUM+1];
	float	weightRemove;//remove weighe
	INT32 	weightDir;//senser sample value direction:forword or backword
	//need store:end
	
	float	weight;   //cur weight
	float	weightPre;//pre weight
} ChanelType;

extern ChanelType HX711Chanel[HX711_CHANEL_NUM];

//main task status
typedef enum HX711CtrlType
{
	HX711_CTRL_INIT = 0,   	/**< HX711  初始化控制 */
	HX711_CTRL_POWER_OFF,   /**< HX711  下电控制 */
	HX711_CTRL_POWER_ON,	/**< HX711  上电控制 */
	HX711_CTRL_WAIT,		/**< HX711  等待下降沿控制 */
	HX711_CTRL_SAMPLE,		/**< HX711  采样控制 */
	HX711_CTRL_POWER_ON_AHEAD_WAIT,	/**< HX711	上电前等待控制 */
	HX711_CTRL_POWER_ON_CHECK,	/**< HX711	上电后检测 */
	HX711_CTRL_POWER_ON_CHECK_COMPLETE,	/**< HX711	上电后检测完成 */
	HX711_CTRL_NUM
}enumHX711CtrlType;







extern const INT32 defaultChanelSamplePoint[CHANEL_POINT_NUM];

extern void hx711_init(void);
extern UINT8 hx711_SenserCheck(void);
extern UINT8 hx711_MainFunction(void);
extern float hx711_getWeight(enumHX711ChanelType chanel);
extern INT32 hx711_getAvgSample(enumHX711ChanelType chanel);
extern void setSampleWeightValue(UINT8 chanel,UINT8 point,INT32 weight);
extern void setSampleValue(UINT8 chanel,UINT8 point,INT32 sample);
extern void trigerCalcKB(UINT8 chanel,UINT8 point);
extern ChanelType* getChanelStruct(UINT8 chanel_i);
extern void hx711_setAllRemoveWeight(void);
#endif

