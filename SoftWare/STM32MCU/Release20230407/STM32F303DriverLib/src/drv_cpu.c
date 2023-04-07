/**
 *******************************************************************
 * @file    drv_cpu.c
 * @author  MKdriver
 * @version V1.0.0
 * @date    9-Oct-2015
 * @brief   STM32F40x CPU驱动程序C文件
 *******************************************************************
 * @attention
 *
 *
 *
 * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
 *******************************************************************
 */
 
#include "reg_stm32f303_nvic.h"
#include "drv_cpu.h"


/**
 * @brief  系统软复位
 * @retval 无
 */
void drv_soft_system_reset( void )
{
  __DSB();                                                     /* Ensure all outstanding memory accesses included
                                                                  buffered write are completed before reset */
  SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)      |
                 (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                 SCB_AIRCR_SYSRESETREQ_Msk);                   /* Keep priority group unchanged */
  __DSB();                                                     /* Ensure completion of memory access */
  while(1);                                                    /* wait until reset */
}

/**
 * @brief  读芯片ID
 * @param  pChipId: 读出芯片ID存储地址
 * @retval 无
 */
void drv_read_chip_id( UINT32 *pChipId )
{
    pChipId[0] = *((volatile UINT32 *)0x1FFFF7AC);
    pChipId[1] = *((volatile  UINT32 *)(0x1FFFF7AC + 4));
    pChipId[2] = *((volatile  UINT32 *)(0x1FFFF7AC + 8));
}

/**
 * @brief  读芯片flash大小
 * @retval 无
 */
UINT16 drv_read_flash_size( void )
{
	UINT16 l_ChipFlashSize = 0;
	
	l_ChipFlashSize = *(( UINT16 *)0x1FFF7A22 );
	
	return l_ChipFlashSize;
}


