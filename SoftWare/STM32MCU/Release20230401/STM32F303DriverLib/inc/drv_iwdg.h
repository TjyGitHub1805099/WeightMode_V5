/**
*******************************************************************
* @file    drv_iwdg.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x IWDG模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/
#ifndef __DRV_IWDG_H__
#define __DRV_IWDG_H__

#include "reg_stm32f303_iwdg.h"


#define IWDG_ACESS_VALUE			(( UINT16 )0x5555 )
#define IWDG_ENABLE_VALUE			(( UINT16 )0xCCCC )
#define IWDG_RELOAD_VALUE			(( UINT16 )0xAAAA )

/** 看门狗时钟分频系数定义 */
typedef enum
{
	IWDG_PR_PRESCAL_4 = 0,			/**< 看门狗时钟频率为LSI时钟4分频 */
	IWDG_PR_PRESCAL_8,				/**< 看门狗时钟频率为LSI时钟8分频 */
	IWDG_PR_PRESCAL_16,				/**< 看门狗时钟频率为LSI时钟16分频 */
	IWDG_PR_PRESCAL_32,				/**< 看门狗时钟频率为LSI时钟32分频 */
	IWDG_PR_PRESCAL_64,				/**< 看门狗时钟频率为LSI时钟64分频 */
	IWDG_PR_PRESCAL_128,			/**< 看门狗时钟频率为LSI时钟128分频 */
	IWDG_PR_PRESCAL_256				/**< 看门狗时钟频率为LSI时钟256分频，110，111均为256分频 */
}enumIwdgPrPrescalType;


/**
* @brief  看门狗喂狗.
* @retval 无
*/
void __INLINE drv_iwdg_feed( void )
{ 
	IWDG->KR = IWDG_RELOAD_VALUE;               // 喂狗，重载看门狗计数器值 
}


extern void drv_iwdg_init( UINT32 MsTime );
extern void drv_iwdg_feed( void );

#endif
