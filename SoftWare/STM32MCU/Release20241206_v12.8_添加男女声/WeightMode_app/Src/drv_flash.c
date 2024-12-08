/**
*******************************************************************
* @file    drv_flash.c
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x Flash模块驱动程序C文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/
#include "typedefine.h"
#include "drv_flash.h"

#define SECTOR_MASK               ((UINT32)0xFFFFFF07)

FLASH_SectorTypeDef FLASH_SectorInfo[8] = {
{0,0x08000000,0x08003FFF,16},//扇区 0 0x0800 0000 - 0x0800 3FFF 16 KB
{1,0x08004000,0x08007FFF,16},//扇区 1 0x0800 4000 - 0x0800 7FFF 16 KB
{2,0x08008000,0x0800BFFF,16},//扇区 2 0x0800 8000 - 0x0800 BFFF 16 KB
{3,0x0800C000,0x0800FFFF,16},//扇区 3 0x0800 C000 - 0x0800 FFFF 16 KB
{4,0x08010000,0x0801FFFF,64},//扇区 4 0x0801 0000 - 0x0801 FFFF 64 KB
{5,0x08020000,0x0803FFFF,128},//扇区 5 0x0802 0000 - 0x0803 FFFF 128 KB
{6,0x08040000,0x0805FFFF,128},//扇区 6 0x0804 0000 - 0x0805 FFFF 128 KB
{7,0x08060000,0x0807FFFF,128},//扇区 7 0x0806 0000 - 0x0807 FFFF 128 KB
};

/**
* @brief  解锁FLASH，允许访问控制寄存器
* @retval 无
*/
void drv_flash_unlock( void )
{ 
	HAL_FLASH_Unlock();
}

/**
* @brief  锁FLASH，不允许访问控制寄存器
* @retval 无
*/
void drv_flash_lock( void )
{ 
	HAL_FLASH_Lock();
}

/**
* @brief  擦除Flash指定扇区
* @param  PageAddress: OB_WRP_Pages0to1 ~ OB_WRP_Pages60to61
* @retval Flash操作状态: 返回值可以是：FLASH_ERROR_PROGRAM,FLASH_ERROR_WRP, FLASH_TIMEOUT或FLASH_COMPLETE.
*/
FLASH_Status drv_flash_erase_sector( UINT32 PageAddress )
{
	FLASH_Status status = FLASH_COMPLETE;
	FLASH_EraseInitTypeDef FLASH_EraseInit;
	uint32_t SectorError = 0,i=0;

	for(i = 0 ; i < FLASH_SECTOR_TOTAL ; i++)
	{
		if(PageAddress == FLASH_SectorInfo[i].SectorStartAdd)
		{
			break;
		}
	}

	if( i < FLASH_SECTOR_TOTAL )
	{
		FLASH_EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
		FLASH_EraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
		FLASH_EraseInit.Sector = i;
		FLASH_EraseInit.NbSectors = 1;

		if(HAL_FLASHEx_Erase(&FLASH_EraseInit,&SectorError) != HAL_OK)
		{
			status = FLASH_ERROR_PROGRAM;
		}
	}
	else
	{
		status = FLASH_ADDRESS_OUT;
	}

	return status;
}

/**
* @brief  擦除所有扇区.
* @param  无
* @retval Flash操作状态: FLASH_ERROR_PG,FLASH_ERROR_WRP, FLASH_TIMEOUT或FLASH_COMPLETE.
*/
FLASH_Status drv_flash_erase_all_sector( void )
{
	FLASH_Status status = FLASH_COMPLETE;
	#if 0

	status = drv_flash_wait_last_operation( );

	if(status == FLASH_COMPLETE)
	{
		FLASH->CR.bit.MER = 1;		//批量擦除
		FLASH->CR.bit.STRT = 1;
		status = drv_flash_wait_last_operation( );
		FLASH->CR.bit.MER = 0;
	}
	#endif

	return status;
}

/**
* @brief  16位半字编程.
* @param  Address: 要编程的地址.
* @param  Data: 要编程的数据.
* @retval Flash操作状态: 返回值可以是：FLASH_ERROR_PG,FLASH_ERROR_WRP, FLASH_TIMEOUT或FLASH_COMPLETE.
*/
FLASH_Status drv_flash_write_half_word( UINT32 Address, UINT16 Data )
{
	FLASH_Status status = FLASH_COMPLETE;
	#if 0

	status = drv_flash_wait_last_operation( );
	if(status == FLASH_COMPLETE)
	{
		FLASH->CR.bit.PG = 1;		//写编程
		*(UINT16*)Address = (UINT16)Data;
		status = drv_flash_wait_last_operation( );
		FLASH->CR.bit.PG = 0;
	}
	#endif
	
	return status;
}

/**
* @brief  32位字编程.
* @param  Address: 要编程的地址.
* @param  Data: 要编程的数据.
* @retval Flash操作状态: 返回值可以是: FLASH_ERROR_PG,FLASH_ERROR_WRP, FLASH_TIMEOUT或FLASH_COMPLETE.
*/
FLASH_Status drv_flash_write_word( UINT32 Address, UINT32 Data )
{
	FLASH_Status status = FLASH_COMPLETE;
	#if 0
	UINT32 tmp = 0;

	status = drv_flash_wait_last_operation( );
	if(status == FLASH_COMPLETE)
	{
		FLASH->CR.bit.PG = 1;		//写编程
		*(UINT16*)Address = (UINT16)Data;
		status = drv_flash_wait_last_operation( );

		if(status == FLASH_COMPLETE)
		{
			//前两个字节写入完成，继续写后两个字节
			tmp = Address + 2;
			*(UINT16*) tmp = Data >> 16;
			status = drv_flash_wait_last_operation( );
			FLASH->CR.bit.PG = 0;
		}
		else
		{
			FLASH->CR.bit.PG = 0;
		}
	}
	#endif

	return status;
}

/**
* @brief  多个32位字编程.
* @param  Address: 要编程的地址.
* @param  Data: 要编程的数据.
* @retval Flash操作状态: 返回值可以是: FLASH_ERROR_PG,FLASH_ERROR_WRP, FLASH_TIMEOUT或FLASH_COMPLETE.
*/
FLASH_Status drv_flash_write_words( UINT32 Address, UINT32 *pData, UINT16 Length )
{
	FLASH_Status status = FLASH_COMPLETE;
	uint16_t i=0;
	#if 0
	UINT32 tmp = 0;

	status = drv_flash_wait_last_operation( );
	if(status == FLASH_COMPLETE)
	{
		FLASH->CR.bit.PG = 1;		//写编程
		do
		{
			*(UINT16*)Address = (UINT16)(*pData);
			status = drv_flash_wait_last_operation( );
			if(status == FLASH_COMPLETE)
			{
				//前两个字节写入完成，继续写后两个字节
				tmp = Address + 2;
				*(UINT16*)tmp = (*pData) >> 16;
				status = drv_flash_wait_last_operation( );
			}
			else
			{
				FLASH->CR.bit.PG = 0;
				break;
			}
			Length--;
			Address += 4;
			pData++;	
		}while( Length );
		
		FLASH->CR.bit.PG = 0;
	}
	#endif
	for( i = 0 ; i < Length ; i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, i, pData[i]);
	}
	return status;
}

/**
* @brief  多个半字编程.
* @param  Address: 要编程的地址.
* @param  Data: 要编程的数据地址.
* @retval Flash操作状态: 返回值可以是: FLASH_ERROR_PG,FLASH_ERROR_WRP, FLASH_TIMEOUT或FLASH_COMPLETE.
*/
FLASH_Status drv_flash_write_half_words( UINT32 Address, UINT16 *pData, UINT16 Length )
{
	FLASH_Status status = FLASH_COMPLETE;
	#if 0

	status = drv_flash_wait_last_operation( );
	do{
		FLASH->CR.bit.PG = 1;		//写编程
		*(UINT16*)Address = *pData;
		status = drv_flash_wait_last_operation( );
		Address += 2;
		Length--;
		pData++;
	}while(( status == FLASH_COMPLETE ) && ( Length != 0 ));
	FLASH->CR.bit.PG = 0;
	#endif

	return status;
}

/**
* @brief  半字读.
* @param  Address: 要编程的地址.
* @param  Data: 要编程的数据地址.
* @retval Flash操作状态: 返回值可以是: FLASH_ERROR_PG,FLASH_ERROR_WRP, FLASH_TIMEOUT或FLASH_COMPLETE.
*/
void drv_flash_read_half_words( UINT32 Address, UINT16 *pData, UINT16 Length )
{
	#if 0
	while( Length -- )
	{
		*pData = *( (UINT16 *)Address );
		pData++;
		Address += 2;
	}
	#endif
}

/**
* @brief  字读.
* @param  Address: 要编程的地址.
* @param  Data: 要编程的数据地址.
* @retval Flash操作状态: 返回值可以是: FLASH_ERROR_PG,FLASH_ERROR_WRP, FLASH_TIMEOUT或FLASH_COMPLETE.
*/
void drv_flash_read_words( UINT32 Address, UINT32 *pData, UINT16 Length )
{
	UINT16 l_TempData = 0;
	
	while( Length -- )
	{
		l_TempData = *( (UINT16 *)Address );
		Address += 2;
		*(pData++) = l_TempData | ( *( (UINT16 *)Address ) << 16 );
		Address += 2;
	}

}

/**
* @brief  检查 FLASH 标志状态.
* @param  FlashFlag: 要检查的标志，可以是下面值中的一个
  *     @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag 
  *     @arg FLASH_FLAG_PGERR: FLASH Programming error flag 
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *     @arg FLASH_FLAG_EOP: FLASH End of Programming flag     
* @retval 新状态.
*/
FlagStatus drv_flash_get_flag_status( UINT32 FlashFlag )
{
	#if 0
	UINT32 l_Sr;
	
	l_Sr = (UINT32)FLASH->SR.all;
	if(( l_Sr & FlashFlag) != (UINT32)RESET )
	{
		return  SET;
	}
	else
	{
		return RESET;
	}
	#endif
	return  SET;
}

/**
* @brief  清Flash挂起标志.
* @param  FlashFlag: 要清除的标志，参考 drv_flash_get_flag_status 的注释
* @retval 无
*/
void drv_flash_clear_flag_status( UINT32 FlashFlag )
{
	#if 0
	FLASH->SR.all = FlashFlag;
	#endif
}

/**
* @brief  读 FLASH 状态.
* @retval Flash操作状态: 返回值可以是：FLASH_BUSY, FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE.
*/
FLASH_Status drv_flash_get_status( void )
{
	FLASH_Status FLASHstatus = FLASH_COMPLETE;
	#if 0
	UINT32 l_Sr;
	
	l_Sr = (UINT32)FLASH->SR.all;
	if((l_Sr & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
	{
		FLASHstatus = FLASH_BUSY;
	}
	else 
	{  
		if((l_Sr & (UINT32)FLASH_FLAG_WRPERR)!= (UINT32)0x00)
		{ 
			FLASHstatus = FLASH_ERROR_WRP;
		}
		else 
		{
			if((l_Sr & (UINT32)(FLASH_SR_PGERR)) != (UINT32)0x00)
			{
				FLASHstatus = FLASH_ERROR_PROGRAM; 
			}
			else
			{
				FLASHstatus = FLASH_COMPLETE;
			}
		}
	}
	#endif

	return FLASHstatus;
}

/**
* @brief  等到最后的操作完成.
* @param  无
* @retval Flash操作状态: 返回值可以是：FLASH_BUSY, FLASH_ERROR_PROGRAM,FLASH_ERROR_WRP或FLASH_COMPLETE.
*/
FLASH_Status drv_flash_wait_last_operation( void )
{
	
	FLASH_Status status = FLASH_COMPLETE;
	#if 0
	UINT32 l_Timeout = 0xFFFFFFFF;
	status = drv_flash_get_status();

	while((status == FLASH_BUSY) && (l_Timeout != 0x00))
	{
		status = drv_flash_get_status();
		l_Timeout--;
	}

	if(l_Timeout == 0x00 )
	{
		status = FLASH_TIMEOUT;
	}
	#endif
	return status;
}





/*
//参见 https://blog.51cto.com/u_15830484/5761606

uint16_t WriteFlash(uint32_t start_Add,uint32_t end_Add,uint32_t *data)
{ 
  uint32_t i;
  uint8_t j=0;
  uint32_t PageError;
  FLASH_EraseInitTypeDef f;
  
  f.TypeErase = FLASH_TYPEERASE_PAGES;
  f.PageAddress = START_ADDRESS;
  f.NbPages = 1;
  PageError = 0;
  
  HAL_FLASH_Unlock();  
  HAL_FLASHEx_Erase(&f, &PageError);
  data = (uint32_t*)(&Saved_Param);
  
  for(i = START_ADDRESS; i < END_ADDRESS; i += 4)
  {
      HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, i, data[j++]);
  }
  
  HAL_FLASH_Lock();

}

uint8_t ReadFlash (uint32_t start_Add,uint32_t end_Add,uint32_t *data)
{
    uint32_t i;
    uint8_t j=0;

    for(i = start_Add; i < end_Add; i += 4)
    {
        data[j++]=*(uint32_t *)(i);
    }
    return HAL_OK;
 
}

*/



