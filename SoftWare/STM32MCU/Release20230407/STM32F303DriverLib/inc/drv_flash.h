/**
*******************************************************************
* @file    drv_flash.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x Flash模块驱动程序H文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include "reg_stm32f303_flash.h"

#define FLASH_PAGE_SIZE                     ((UINT32)0x00000800)
#define FLASH_START_ADDRESS                 ((UINT32)0x08000000)
#define FLASH_END_ADDRESS                   ((UINT32)0x08000000 + FLASH_PAGE_SIZE * 128)

#define FLASH_KEY1							((UINT32)0x45670123)	/*解锁密匙1*/
#define FLASH_KEY2							((UINT32)0xCDEF89AB)	/*解锁密匙2*/

#define FLASH_SR_BSY                        ((UINT32)0x00000001)
#define FLASH_SR_PGERR                      ((UINT32)0x00000004)
#define FLASH_SR_WRPERR                     ((UINT32)0x00000010)
#define FLASH_SR_EOP                        ((UINT32)0x00000020) 


#define FLASH_FLAG_BSY						FLASH_SR_BSY
#define FLASH_FLAG_WRPERR					FLASH_SR_WRPERR
#define FLASH_FLAG_PGERR					FLASH_SR_PGERR
#define FLASH_FLAG_EOP						FLASH_SR_EOP


//#define OB_WRP_Pages0to1               		((UINT32)0x00000001) /* Write protection of page 0 to 1 */
//#define OB_WRP_Pages2to3               		((UINT32)0x00000002) /* Write protection of page 2 to 3 */
//#define OB_WRP_Pages4to5               		((UINT32)0x00000004) /* Write protection of page 4 to 5 */
//#define OB_WRP_Pages6to7               		((UINT32)0x00000008) /* Write protection of page 6 to 7 */
//#define OB_WRP_Pages8to9               		((UINT32)0x00000010) /* Write protection of page 8 to 9 */
//#define OB_WRP_Pages10to11             		((UINT32)0x00000020) /* Write protection of page 10 to 11 */
//#define OB_WRP_Pages12to13             		((UINT32)0x00000040) /* Write protection of page 12 to 13 */
//#define OB_WRP_Pages14to15             		((UINT32)0x00000080) /* Write protection of page 14 to 15 */
//#define OB_WRP_Pages16to17             		((UINT32)0x00000100) /* Write protection of page 16 to 17 */
//#define OB_WRP_Pages18to19             		((UINT32)0x00000200) /* Write protection of page 18 to 19 */
//#define OB_WRP_Pages20to21             		((UINT32)0x00000400) /* Write protection of page 20 to 21 */
//#define OB_WRP_Pages22to23             		((UINT32)0x00000800) /* Write protection of page 22 to 23 */
//#define OB_WRP_Pages24to25             		((UINT32)0x00001000) /* Write protection of page 24 to 25 */
//#define OB_WRP_Pages26to27             		((UINT32)0x00002000) /* Write protection of page 26 to 27 */
//#define OB_WRP_Pages28to29             		((UINT32)0x00004000) /* Write protection of page 28 to 29 */
//#define OB_WRP_Pages30to31             		((UINT32)0x00008000) /* Write protection of page 30 to 31 */
//#define OB_WRP_Pages32to33             		((UINT32)0x00010000) /* Write protection of page 32 to 33 */
//#define OB_WRP_Pages34to35             		((UINT32)0x00020000) /* Write protection of page 34 to 35 */
//#define OB_WRP_Pages36to37             		((UINT32)0x00040000) /* Write protection of page 36 to 37 */
//#define OB_WRP_Pages38to39             		((UINT32)0x00080000) /* Write protection of page 38 to 39 */
//#define OB_WRP_Pages40to41             		((UINT32)0x00100000) /* Write protection of page 40 to 41 */
//#define OB_WRP_Pages42to43             		((UINT32)0x00200000) /* Write protection of page 42 to 43 */
//#define OB_WRP_Pages44to45             		((UINT32)0x00400000) /* Write protection of page 44 to 45 */
//#define OB_WRP_Pages46to47             		((UINT32)0x00800000) /* Write protection of page 46 to 47 */
//#define OB_WRP_Pages48to49             		((UINT32)0x01000000) /* Write protection of page 48 to 49 */
//#define OB_WRP_Pages50to51             		((UINT32)0x02000000) /* Write protection of page 50 to 51 */
//#define OB_WRP_Pages52to53             		((UINT32)0x04000000) /* Write protection of page 52 to 53 */
//#define OB_WRP_Pages54to55             		((UINT32)0x08000000) /* Write protection of page 54 to 55 */
//#define OB_WRP_Pages56to57             		((UINT32)0x10000000) /* Write protection of page 56 to 57 */
//#define OB_WRP_Pages58to59             		((UINT32)0x20000000) /* Write protection of page 58 to 59 */
//#define OB_WRP_Pages60to61             		((UINT32)0x40000000) /* Write protection of page 60 to 61 */

/** FLASH操作状态定义 */
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_COMPLETE,
  FLASH_TIMEOUT,
  FLASH_ADDRESS_OUT
}FLASH_Status;


extern void drv_flash_unlock( void );
extern void drv_flash_lock( void );
extern FLASH_Status drv_flash_erase_sector( UINT32 PageAddress );
extern FLASH_Status drv_flash_erase_all_sector( void );
extern FLASH_Status drv_flash_write_word( UINT32 Address, UINT32 Data );
extern FLASH_Status drv_flash_write_half_word( UINT32 Address, UINT16 Data );
extern FLASH_Status drv_flash_write_words( UINT32 Address, UINT32 *pData, UINT16 Length );
extern FLASH_Status drv_flash_write_half_words( UINT32 Address, UINT16 *pData, UINT16 Length );
extern void drv_flash_read_half_words( UINT32 Address, UINT16 *pData, UINT16 Length );
extern void drv_flash_read_words( UINT32 Address, UINT32 *pData, UINT16 Length );
extern FlagStatus drv_flash_get_flag_status( UINT32 FlashFlag );
extern void drv_flash_clear_flag_status( UINT32 FlashFlag );
extern FLASH_Status drv_flash_get_status( void );
extern FLASH_Status drv_flash_wait_last_operation( void );




#endif

