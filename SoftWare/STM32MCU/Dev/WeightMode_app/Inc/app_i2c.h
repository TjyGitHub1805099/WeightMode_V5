#ifndef __APP_I2C_H__
#define __APP_I2C_H__

#include "i2c.h"
#include "hal_gpio.h"
#include "stm32f4xx_hal.h"

//是否使能测试
#define EXT_EEPROM_TEST_EN

//AT24C128C-SSHM-T相关信息
#define EXT_EEPROM_SLAVE_SIZE       (128)//共可存储：128KBit = 16384 Byte
#define EXT_EEPROM_REG_ADDRESS_MAX  (0x4000)//地址空间最大值：128*1024bit = 0x4000Byte = 16KByte
#define EXT_EEPROM_SLAVE_ADDRESS    (0xA0)//外部存储的从机地址：A2 A1 A0 = 000

#define EXT_EEPROM_SLAVE_PADGE_NUM  (0x40)//每页大小为64字节，多字节写时，地址只有低6位会循环递增，所以超过页的最大数量后就会重复写
#define EXT_EEPROM_WRITE_OFFSET     (10)//写间隔需要至少5ms

//参数存放地址
//==================SECTOR2:HX711 point sample , weight value , K ,B , weightRemove , weightDir
#define EXT_EEPROM_FLASH_STORE_ADDRESS_START            (0)

//==================SECTOR1:system control of unit , min , max , err , cascade
#define EXT_EEPROM_FLASH_SYS_PARA_STORE_ADDRESS_START   (64*10)

#define EXT_EEPROM_WRITE_PROTECT_DISABLE    hal_gpio_set_do_low(EX_EEPROM_I2C1_WP);//关闭写保护：可写
#define EXT_EEPROM_WRITE_PROTECT_ENABLE     hal_gpio_set_do_high(EX_EEPROM_I2C1_WP);//打开写保护：不可写

typedef struct app_i2cComtextDef
{
    I2C_HandleTypeDef *hi2c;
    uint16_t DevAddress;
    uint8_t *pDataWrite;
    uint8_t *pDataRead;
    uint16_t Size;
    uint32_t Timeout;
    uint16_t handle_sts;
}app_i2cComtextDef;

HAL_StatusTypeDef app_HAL_I2C_Master_Transmit(uint16_t writeRegAdd, uint8_t *pData, uint16_t writeTotalLen);
HAL_StatusTypeDef app_HAL_I2C_Master_Read(uint16_t writeRegAdd, uint8_t *pData, uint16_t writeTotalLen);

#ifdef EXT_EEPROM_TEST_EN
void app_i2c_test(void);
#endif


#endif

