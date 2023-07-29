#include "app_i2c.h"
#include "string.h"
#include "hal_gpio.h"

uint8_t app_i2cRxData[EXT_EEPROM_SLAVE_PADGE_NUM];
uint8_t app_i2cTxData[EXT_EEPROM_SLAVE_PADGE_NUM];//2byte address

app_i2cComtextDef app_i2cComtext=APP_I2C_COMTEXT_DEFAULT; 


//参考：https://blog.csdn.net/weixin_56565733/article/details/124401443

uint8_t handle_sts = 0 ;
HAL_StatusTypeDef app_HAL_I2C_Master_Transmit(uint16_t DevAddress, uint16_t writeRegAdd, uint8_t *pData, uint16_t writeTotalLen, uint32_t Timeout)
{
    HAL_StatusTypeDef ret = HAL_OK;
    uint16_t curRegAddWrite = 0 , curLenWrite = 0 , curOffsetWrite = 0 , remainLenWrite = 0 , curOffsetCopyWrite = 0;
    //judge length if not overwite
    if((writeRegAdd + writeTotalLen) <= EXT_EEPROM_REG_ADDRESS_MAX)
    {
        hal_gpio_set_do_low(EX_EEPROM_I2C1_WP);
        curOffsetWrite = 0 ;
        curLenWrite = 0 ;
        curOffsetCopyWrite = 0;
        remainLenWrite = writeTotalLen;
        curRegAddWrite = writeRegAdd;
        //
        while((remainLenWrite)&&(HAL_OK == ret))
        {
            curRegAddWrite += curOffsetWrite;
            curLenWrite = EXT_EEPROM_SLAVE_PADGE_NUM - curRegAddWrite%EXT_EEPROM_SLAVE_PADGE_NUM;
            if(curLenWrite >= remainLenWrite)
            {
                curLenWrite = remainLenWrite;
            }
            memcpy((void *)&app_i2cTxData[0],(void *)&pData[curOffsetCopyWrite],curLenWrite);
            //hal_delay_ms_use_sys_tick(10);//官方要求写间隔需要5ms
            hal_delay_ms(10);//官方要求写间隔需要5ms
            ret = HAL_I2C_Mem_Write(&hi2c1,DevAddress,curRegAddWrite,I2C_MEMADD_SIZE_16BIT,&app_i2cTxData[0],curLenWrite,1000);
            if(HAL_OK == ret)
            {
                curOffsetWrite = curLenWrite;
                curOffsetCopyWrite += curLenWrite;
                remainLenWrite -= curLenWrite;
            }
            else
            {
                handle_sts = 123;
            }
        }
        //hal_gpio_set_do_high(EX_EEPROM_I2C1_WP);
    }
    else
    {
        ret = HAL_ERROR;
    }

    return ret;
}

HAL_StatusTypeDef app_HAL_I2C_Master_Read(uint16_t DevAddress, uint16_t readRegAdd, uint8_t *pData, uint16_t readTotalLen, uint32_t Timeout)
{
    HAL_StatusTypeDef ret = HAL_OK;
    uint16_t curRegAddRead = 0 , curLenRead = 0 , curOffsetRead = 0 , remainLenRead = 0 , curOffsetCopyRead = 0;
    //judge length if not overwite
    if((readRegAdd + readTotalLen) <= EXT_EEPROM_REG_ADDRESS_MAX)
    {
        curOffsetRead = 0 ;
        curLenRead = 0 ;
        curOffsetCopyRead = 0 ;
        remainLenRead = readTotalLen;
        curRegAddRead = readRegAdd;
        
        while((remainLenRead)&&(HAL_OK == ret))
        {
            curRegAddRead += curOffsetRead;
            curLenRead = EXT_EEPROM_SLAVE_PADGE_NUM - curRegAddRead%EXT_EEPROM_SLAVE_PADGE_NUM;
            if(curLenRead >= remainLenRead)
            {
                curLenRead = remainLenRead;
            }
            //
            hal_delay_ms(10);
            ret = HAL_I2C_Mem_Read(&hi2c1,DevAddress,curRegAddRead,I2C_MEMADD_SIZE_16BIT,&app_i2cRxData[0],curLenRead,1000);
            if(HAL_OK == ret)
            {
                memcpy((void *)&pData[curOffsetCopyRead],(void *)&app_i2cRxData[0],curLenRead);
                curOffsetRead = curLenRead;
                curOffsetCopyRead += curLenRead;
                remainLenRead -= curLenRead;
            }
            else
            {
                handle_sts = 321;
            }
        }
    }
    else
    {
        ret = HAL_ERROR;
    }

    return ret;
}
#define user_i2c_test_data_len  (1024)// (2*EXT_EEPROM_SLAVE_PADGE_NUM)
uint16_t user_i2c_test_data_add = 0;
uint8_t user_i2cRxData[user_i2c_test_data_len];
uint8_t user_i2cTxData[user_i2c_test_data_len];
uint8_t app_i2c_test_flag = 0 ;
uint8_t ADD_ADD = 0xA0;
uint32_t TICK_00,TICK_01;
extern uint32_t sys_tick;
void app_i2c_test(void)
{
    uint16_t i = 0 ;
    HAL_StatusTypeDef ret = HAL_OK;

    if(1 == app_i2c_test_flag)//write
    {
        for(i=0;i<user_i2c_test_data_len;i++)
        {
            user_i2cTxData[i] = i;
        }
        TICK_00 = sys_tick;
		ret = app_HAL_I2C_Master_Transmit(ADD_ADD,user_i2c_test_data_add,(uint8_t *)&user_i2cTxData[0],user_i2c_test_data_len,100);
        TICK_01 = sys_tick;
        app_i2c_test_flag = 0 ;
		
    }
    if(2 == app_i2c_test_flag)//read
    {
		ret = app_HAL_I2C_Master_Read(ADD_ADD,user_i2c_test_data_add,(uint8_t *)&user_i2cRxData[0],user_i2c_test_data_len,100);
        app_i2c_test_flag = 0 ;
    }
    if(3 == app_i2c_test_flag)//CHECK
    {
        for( i = 0 ; i < user_i2c_test_data_len ; i++ )
        {
            if(user_i2cRxData[i] != i)
            {
                app_i2c_test_flag = 0 ;
                break;
            }
        }
    }
}

