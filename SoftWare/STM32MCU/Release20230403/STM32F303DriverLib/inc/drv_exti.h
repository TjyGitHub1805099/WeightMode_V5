/**
*******************************************************************
* @file    drv_exti.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40xEXTI模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_EXTI_H__
#define __DRV_EXTI_H__



#include "reg_stm32f303_exti.h"


#define EXTI_LINE0								((UINT32)0x00000001)
#define EXTI_LINE1								((UINT32)0x00000002)
#define EXTI_LINE2								((UINT32)0x00000004)
#define EXTI_LINE3								((UINT32)0x00000008)
#define EXTI_LINE4								((UINT32)0x00000010)
#define EXTI_LINE5								((UINT32)0x00000020)
#define EXTI_LINE6								((UINT32)0x00000040)
#define EXTI_LINE7								((UINT32)0x00000080)
#define EXTI_LINE8								((UINT32)0x00000100)
#define EXTI_LINE9								((UINT32)0x00000200)
#define EXTI_LINE10								((UINT32)0x00000400)
#define EXTI_LINE11								((UINT32)0x00000800)
#define EXTI_LINE12								((UINT32)0x00001000)
#define EXTI_LINE13								((UINT32)0x00002000)
#define EXTI_LINE14								((UINT32)0x00004000)
#define EXTI_LINE15								((UINT32)0x00008000)
#define EXTI_LINE16								((UINT32)0x00010000)
#define EXTI_LINE17								((UINT32)0x00020000)
#define EXTI_LINE18								((UINT32)0x00040000)
#define EXTI_LINE19								((UINT32)0x00080000)
#define EXTI_LINE20								((UINT32)0x00100000)
#define EXTI_LINE21								((UINT32)0x00200000)
#define EXTI_LINE22								((UINT32)0x00400000)
#define EXTI_LINE29								((UINT32)0x20000000)
#define EXTI_LINE30								((UINT32)0x40000000)
#define EXTI_LINE31								((UINT32)0x80000000)
#define EXTI_LINE32								((UINT32)0x10000001)		//BIT28 做寄存器区别
#define EXTI_LINE33								((UINT32)0x10000002)		//BIT28 做寄存器区别
#define EXTI_LINE34								((UINT32)0x10000004)		//BIT28 做寄存器区别
#define EXTI_LINE35								((UINT32)0x10000008)		//BIT28 做寄存器区别

//EXTI_PIN_SOURCE
#define EXTI_LINE_PIN_SOURCE0					((UINT8)0x00)
#define EXTI_LINE_PIN_SOURCE1					((UINT8)0x01)
#define EXTI_LINE_PIN_SOURCE2					((UINT8)0x02)
#define EXTI_LINE_PIN_SOURCE3					((UINT8)0x03)
#define EXTI_LINE_PIN_SOURCE4					((UINT8)0x04)
#define EXTI_LINE_PIN_SOURCE5					((UINT8)0x05)
#define EXTI_LINE_PIN_SOURCE6					((UINT8)0x06)
#define EXTI_LINE_PIN_SOURCE7					((UINT8)0x07)
#define EXTI_LINE_PIN_SOURCE8					((UINT8)0x08)
#define EXTI_LINE_PIN_SOURCE9					((UINT8)0x09)
#define EXTI_LINE_PIN_SOURCE10					((UINT8)0x0A)
#define EXTI_LINE_PIN_SOURCE11					((UINT8)0x0B)
#define EXTI_LINE_PIN_SOURCE12					((UINT8)0x0C)
#define EXTI_LINE_PIN_SOURCE13					((UINT8)0x0D)
#define EXTI_LINE_PIN_SOURCE14					((UINT8)0x0E)
#define EXTI_LINE_PIN_SOURCE15					((UINT8)0x0F)

//EXTI_PORT_SUORCE
#define EXTI_LINE_PORTA_SOURCE					((UINT8)0x00)
#define EXTI_LINE_PORTB_SOURCE					((UINT8)0x01)
#define EXTI_LINE_PORTC_SOURCE					((UINT8)0x02)
#define EXTI_LINE_PORTD_SOURCE					((UINT8)0x03)
#define EXTI_LINE_PORTE_SOURCE					((UINT8)0x04)
#define EXTI_LINE_PORTF_SOURCE					((UINT8)0x05)
#define EXTI_LINE_PORTG_SOURCE					((UINT8)0x06)
#define EXTI_LINE_PORTH_SOURCE					((UINT8)0x07)


/** EXTI模式 */
typedef enum ExtiModeType
{
	EXTI_MODE_INTERRUPT = 0,					/**< EXTI中断 */
	EXTI_MODE_EVENT								/**< EXTI事件 */
}EnumExtiModeType;

/** EXTI触发选择 */
typedef enum ExtiTriggerSelectionType
{
	EXTI_TRIGGER_RISING = 0,					/**< 上升沿触发 */
	EXTI_TRIGGER_FALLING,						/**< 下降沿触发 */
	EXTI_TRIGGER_RISING_FALLING					/**< 上升沿下降沿都触发 */
}EnumExtiTrigEdgeType;


extern void drv_exti_deinit( void );
extern void drv_exti_init( UINT32 ExtiLine, EnumExtiTrigEdgeType ExtiTrigEdge );
extern void drv_exti_enable( UINT32 ExtiLine, EnumExtiModeType ExtiMode );
extern void drv_exti_disable( UINT32 ExtiLine, EnumExtiModeType ExtiMode );
extern FlagStatus drv_exti_get_flag_status( UINT32 ExtiLine );
extern void drv_exti_clear_flag_status( UINT32 ExtiLine );
extern ITStatus drv_exti_get_it_status( UINT32 ExtiLine );
extern void drv_exti_clear_it_pending_bit( UINT32 ExtiLine );



#endif

