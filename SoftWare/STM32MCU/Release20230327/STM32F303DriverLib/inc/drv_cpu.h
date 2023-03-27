/**
*******************************************************************
* @file    drv_cpu.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x CPU驱动程序H文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_PWR_H__
#define __DRV_PWR_H__

#include "drv_rcc.h"


#define __DSB()								__dsb(0xF)
#define SCB_AIRCR_PRIGROUP_Pos              8                                             /*!< SCB AIRCR: PRIGROUP Position */
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)                /*!< SCB AIRCR: PRIGROUP Mask */
#define SCB_AIRCR_VECTKEY_Pos				16                                            /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk				(0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)           /*!< SCB AIRCR: VECTKEY Mask */
#define SCB_AIRCR_SYSRESETREQ_Pos			2                                             /*!< SCB AIRCR: SYSRESETREQ Position */
#define SCB_AIRCR_SYSRESETREQ_Msk			(1UL << SCB_AIRCR_SYSRESETREQ_Pos)            /*!< SCB AIRCR: SYSRESETREQ Mask */


extern void drv_soft_system_reset( void );
extern void drv_read_chip_id( UINT32 *pChipId );
extern UINT16 drv_read_flash_size( void );


#endif
