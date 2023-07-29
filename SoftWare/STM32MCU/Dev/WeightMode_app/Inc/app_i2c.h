#ifndef __APP_I2C_H__
#define __APP_I2C_H__

#include "stm32f4xx_hal.h"
#include "i2c.h"
#define EXT_EEPROM_SLAVE_SIZE       (128)//128KBit = 16384 Byte
#define EXT_EEPROM_REG_ADDRESS_MAX  (0x4000)//128*1024bit = 0x4000Byte = 16KByte

#define EXT_EEPROM_SLAVE_ADDRESS    (0xA0)
#define EXT_EEPROM_SLAVE_PADGE_NUM  (0x40)//每页大小为64字节，多字节写时，地址只有低6位会循环递增，所以超过页的最大数量后就会重复写


#define EXT_EEPROM_FLASH_STORE_ADDRESS_START            (0)

#define EXT_EEPROM_FLASH_SYS_PARA_STORE_ADDRESS_START   (64*10)

extern uint8_t app_i2cRxData[EXT_EEPROM_SLAVE_PADGE_NUM];
extern uint8_t app_i2cTxData[EXT_EEPROM_SLAVE_PADGE_NUM];

typedef struct app_i2cComtextDef
{
    I2C_HandleTypeDef *hi2c;
    uint16_t DevAddress;
    uint8_t *pDataWrite;
    uint8_t *pDataRead;
    uint16_t Size;
    uint32_t Timeout;
}app_i2cComtextDef;

#define APP_I2C_COMTEXT_DEFAULT \
{\
    &hi2c1,\
    EXT_EEPROM_SLAVE_ADDRESS,\
    &app_i2cTxData[0],\
    &app_i2cRxData[0],\
    0,\
    100,\
}
#endif


HAL_StatusTypeDef app_HAL_I2C_Master_Transmit(uint16_t DevAddress, uint16_t writeRegAdd, uint8_t *pData, uint16_t writeTotalLen, uint32_t Timeout);
HAL_StatusTypeDef app_HAL_I2C_Master_Read(uint16_t DevAddress, uint16_t writeRegAdd, uint8_t *pData, uint16_t writeTotalLen, uint32_t Timeout);
void app_i2c_test(void);
