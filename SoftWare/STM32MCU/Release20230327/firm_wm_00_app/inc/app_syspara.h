#ifndef __APP_SYSPARA_H__
#define __APP_SYSPARA_H__
#include "typedefine.h"
#include "app_led_ctrl.h"
#include "app_sdwe_ctrl.h"

//==(update:20210606):the SYS data need store : SECTOR1 and SECTOR2
#define DMG_TRIGER_SAVE_SECOTOR_1			(0X01)
#define DMG_TRIGER_SAVE_SECOTOR_2			(0X02)


//system parameter
typedef enum HX711SystemParaType
{
	HX711SystemPara_UNIT = 0,  		/**< HX711  系统设置-单位 */
	HX711SystemPara_MIN_RANGE = 1,  /**< HX711  系统设置-最小量程 */
	HX711SystemPara_MAX_RANGE = 2,  /**< HX711  系统设置-最大量程 */
	HX711SystemPara_ERR_RANGE = 3,	/**< HX711	系统设置-误差 */
	HX711SystemPara_CASCADE = 4,  	/**< HX711  系统设置-级联 */	
	HX711SystemPara_LED_DIS_EN = 5,	/**< HX711	系统设置-LED指示 */
	HX711SystemPara_COLOR1 = 6,		/**< HX711	系统设置-颜色1 */
	HX711SystemPara_COLOR2 = 7,		/**< HX711	系统设置-颜色2 */
	HX711SystemPara_COLOR3 = 8,		/**< HX711	系统设置-颜色3 */
	HX711SystemPara_COLOR4 = 9,		/**< HX711	系统设置-颜色4 */	
	HX711SystemPara_ZERO_RANGE = 10,/**< HX711	零点范围 */ 
	HX711SystemPara_ScreenVoiceSwitch = 11,/**< HX711	语音开关 */ 
	HX711SystemPara_ScreenCastMode = 12,/**< HX711	级联模式 */ 
	HX711SystemPara_FlashEraseTimes = 13,/**< HX711	FLASH擦写次数 */ 
	HX711SystemPara_McuVersion = 14,/**< MCU 软件版本 */ 
	HX711SystemPara_DiVenVersion = 15,/**< 迪文屏 软件版本 */ 
	HX711SystemPara_VoiceNum = 16,/**< 音量参数 */ 
	HX711SystemPara_VoiceNumTouch = 17,/**< 音量参数 触控*/ 
	HX711SystemPara_ScreenLight = 18,/**< 屏幕背光亮度 */	
	HX711SystemPara_NUM  			/**< HX711  系统设置-最大长度 */
}enumHX711SystemParaType;


//==========================================================================================================================
//==================code area
//start of on board flash store address
//0x0800 0000 ~ 0x0803 0000

//===================================important:each need store data need 4 byte=============================================
//==================SECTOR1:system control of unit , min , max , err , cascade
//start of on board flash store address
//0X0803E000 ~ 0X0803E7FF
//start of on board sys para flash store address
#define FLASH_SYS_PARA_STORE_ADDRESS_START	(0X0803E000)
#define FLASH_SYS_PASSWORD_ADDRESS_START	FLASH_SYS_PARA_STORE_ADDRESS_START
#define FLASH_SYS_PASSWORD_ADDRESS_LED		(4)
#define FLASH_SYS_PASSWORD_ADDRESS_END		(FLASH_SYS_PASSWORD_ADDRESS_START+FLASH_SYS_PASSWORD_ADDRESS_LED)
//unit:g or ml
#define FLASH_SYS_UNIT_ADDRESS_START	FLASH_SYS_PASSWORD_ADDRESS_END
#define FLASH_SYS_UNIT_LEN				(HX711SystemPara_NUM*4)
#define FLASH_SYS_UNIT_ADDRESS_END		(FLASH_SYS_UNIT_ADDRESS_START+FLASH_SYS_UNIT_LEN)

//end of on board sys para flash store address
#define FLASH_SYS_PARA_STORE_ADDRESS_END		(FLASH_SYS_UNIT_ADDRESS_END)

//store flash data : PASSWORD unit , min , max , cascade ,... , crc
#define FLASH_SYS_PARA_STORE_MAX_LEN			(((FLASH_SYS_PARA_STORE_ADDRESS_END-FLASH_SYS_PARA_STORE_ADDRESS_START)/4)+1)

//==========================================================================================================================
//==================SECTOR2:HX711 point sample , weight value , K ,B , weightRemove , weightDir
//start of on board flash store address
//0X0803F000 ~ 0X0803F7FF
//start of on board flash store address
#define FLASH_STORE_ADDRESS_START				(0X0803F000)

//each chanel have 10 point : HX711_CHANEL_NUM*10*8(sample + weight value) byte
#define FLASH_CHANEL_POINT_ADDRESS_START		(FLASH_STORE_ADDRESS_START)
#define FLASH_CHANEL_POINT_LEN					(HX711_CHANEL_NUM*CHANEL_POINT_NUM*8)
#define FLASH_CHANEL_POINT_ADDRESS_END			(FLASH_CHANEL_POINT_ADDRESS_START+FLASH_CHANEL_POINT_LEN)

//each chanel have 10 point -> 11 KB : HX711_CHANEL_NUM*11*8(K + B) byte
#define FLASH_CHANEL_POINT_KB_ADDRESS_START		(FLASH_CHANEL_POINT_ADDRESS_END)
#define FLASH_CHANEL_POINT_KB_LEN				(HX711_CHANEL_NUM*(CHANEL_POINT_NUM+1)*8)
#define FLASH_CHANEL_POINT_KB_ADDRESS_END		(FLASH_CHANEL_POINT_KB_ADDRESS_START+FLASH_CHANEL_POINT_KB_LEN)

//each chanel remove weight:HX711_CHANEL_NUM*4
#define FLASH_CHANEL_POINT_RMW_ADDRESS_START	(FLASH_CHANEL_POINT_KB_ADDRESS_END)
#define FLASH_CHANEL_POINT_RMW_LEN				(HX711_CHANEL_NUM*4)
#define FLASH_CHANEL_POINT_RMW_ADDRESS_END		((FLASH_CHANEL_POINT_RMW_ADDRESS_START)+FLASH_CHANEL_POINT_RMW_LEN)

//each chanel sensor direction :HX711_CHANEL_NUM*4
#define FLASH_CHANEL_SERNSER_DIR_ADDRESS_START	(FLASH_CHANEL_POINT_RMW_ADDRESS_END)
#define FLASH_CHANEL_SERNSER_DIR_LEN			(HX711_CHANEL_NUM*4)
#define FLASH_CHANEL_SERNSER_DIR_ADDRESS_END	((FLASH_CHANEL_SERNSER_DIR_ADDRESS_START)+FLASH_CHANEL_SERNSER_DIR_LEN)

//end of on board flash store address
#define FLASH_STORE_ADDRESS_END					(FLASH_CHANEL_SERNSER_DIR_ADDRESS_END)

//store flash data : HX711_CHANEL_NUM * (sample value , weight value , k , b , remove value , weightDir ) , crc
#define FLASH_STORE_MAX_LEN						(((FLASH_STORE_ADDRESS_END-FLASH_STORE_ADDRESS_START)/4)+1)
//==========================================================================================================================
//
typedef struct SystemParaType
{
	//store in flash
	INT32	uint;/**< 单位 */
	INT32	minWeight;/**< 最小量程 */
	INT32	maxWeight;/**< 最大量程 */
	float	errRange;/**< 误差范围 */
	INT32	isCascade;/**< 是否级联 0:不级联 1:master 2~n:slave*/
	INT32	isLedIndicate;/**< 是否LED指示 */
	INT32	userColorSet[SYS_COLOR_GROUP_NUM];/**< 配平色1~4 */
	float	zeroRange;/**< 零点范围 */
	
	INT32	ScreenVoiceSwitch;/**< HX711	语音开关 */ 
	INT32 	ScreenCastMode;/**< HX711	级联显示模式 */ 
	INT32 	FlashEraseTimes;/**< HX711	FLASH 擦写次数 */ 

	INT32 	McuVersion;/**< MCU	软件版本号 */ 
	INT32 	DiWenVersion;/**< 迪文	软件版本号 */ 
	INT32 	VoiceNum;/**< 语音大小 */ 
	INT32 	VoiceNumTouch;/**< 语音大小 触控 */ 
	INT32	ScreenLight;/**< 屏幕背光亮度 */
	//sys used flag
	UINT16	userColorUsed[SYS_COLOR_GROUP_NUM];/**< chanel_a<<8 + chanel_b*/
} gSystemParaType;
//
#define gSystemParaDefault {\
0, \
0, \
5000, \
(float)(2.0), \
0, \
TRUE, \
{LED_COLOR_GREEN, LED_COLOR_NONE, LED_COLOR_NONE, LED_COLOR_NONE },\
(float)(5.0), \
0,\
0,\
0,\
100,\
30,\
30,\
30,\
50,\
{FALSE, FALSE, FALSE, FALSE },\
}
//
extern gSystemParaType gSystemPara;

//===================sys para functions
//DMG_TRIGER_SAVE_SECOTOR_1
extern void readSysDataFromFlash(void);
extern void storeSysDataToFlash(void);

//DMG_TRIGER_SAVE_SECOTOR_2
extern void readSysDataFromFlash_3030(void);
extern void storeSysDataToFlash_3030(void);

#endif
