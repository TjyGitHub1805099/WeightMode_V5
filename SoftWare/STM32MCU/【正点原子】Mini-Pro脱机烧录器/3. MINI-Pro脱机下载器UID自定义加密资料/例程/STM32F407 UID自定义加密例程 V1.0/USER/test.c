#include "sys.h"
#include "delay.h" 
#include "led.h"
#include "UID_Encryption.h"

/* 实验目的：
    演示如何将脱机下载器的UID自定义加密功能添加到用户的代码中 
*/
/* 实验现象：
    验证通过现象：LED1和LED2以1000ms的频率交替闪烁
    验证不通过现象：LED1和LED2以100ms的频率交替闪烁
*/

/******************* UID自定义加密参数定义 *******************/
/* UID起始地址
注意：某些芯片系列的UID地址并不是连续的（如STM32L1XX系列），用户使用时先参考芯片的官方手册的描述；
    如果芯片的UID不连续的话，请用户将UID拼凑到一段连续的内存里面以使用UID_Encryption_Key_Check()接口*/
#define UID_BASE    0x1FFF7A10
/* 脱机下载器写入的密钥起始地址 */
#define KEY_BASE    0x08020000
/* 用户自的定义ID */
const uint8_t custom_id[12] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC};

int main(void)
{ 
    Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz
    delay_init(168);        //初始化延时函数
    LED_Init();                //初始化LED时钟

    /* 验证UID自定义加密的密钥是否正确 */
    if(UID_Encryption_Key_Check((void*)KEY_BASE,
                                (void*)UID_BASE,
                                (void*)custom_id,
                                LENGTH_12,
                                LITTLE_ENDIA,
                                ALGORITHM_4))
    {/* 验证不通过 */
        while(1) //LED快闪
        {
            LED0=0;                //DS0亮
            LED1=1;                //DS1灭
            delay_ms(100);
            LED0=1;                //DS0灭
            LED1=0;                //DS1亮
            delay_ms(100);
        }
    }
    else
    {/* 验证通过 */
    }
    
    while(1)//LED慢闪
    {
        LED0=0;                //DS0亮
        LED1=1;                //DS1灭
        delay_ms(1000);
        LED0=1;                //DS0灭
        LED1=0;                //DS1亮
        delay_ms(1000);
    }
}

















