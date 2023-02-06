#include "sys.h"
#include "delay.h" 
#include "led.h"
#include "UID_Encryption.h"

/* ʵ��Ŀ�ģ�
    ��ʾ��ν��ѻ���������UID�Զ�����ܹ�����ӵ��û��Ĵ����� 
*/
/* ʵ������
    ��֤ͨ������LED1��LED2��1000ms��Ƶ�ʽ�����˸
    ��֤��ͨ������LED1��LED2��100ms��Ƶ�ʽ�����˸
*/

/******************* UID�Զ�����ܲ������� *******************/
/* UID��ʼ��ַ
ע�⣺ĳЩоƬϵ�е�UID��ַ�����������ģ���STM32L1XXϵ�У����û�ʹ��ʱ�Ȳο�оƬ�Ĺٷ��ֲ��������
    ���оƬ��UID�������Ļ������û���UIDƴ�յ�һ���������ڴ�������ʹ��UID_Encryption_Key_Check()�ӿ�*/
#define UID_BASE    0x1FFF7A10
/* �ѻ�������д�����Կ��ʼ��ַ */
#define KEY_BASE    0x08020000
/* �û��ԵĶ���ID */
const uint8_t custom_id[12] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC};

int main(void)
{ 
    Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz
    delay_init(168);        //��ʼ����ʱ����
    LED_Init();                //��ʼ��LEDʱ��

    /* ��֤UID�Զ�����ܵ���Կ�Ƿ���ȷ */
    if(UID_Encryption_Key_Check((void*)KEY_BASE,
                                (void*)UID_BASE,
                                (void*)custom_id,
                                LENGTH_12,
                                LITTLE_ENDIA,
                                ALGORITHM_4))
    {/* ��֤��ͨ�� */
        while(1) //LED����
        {
            LED0=0;                //DS0��
            LED1=1;                //DS1��
            delay_ms(100);
            LED0=1;                //DS0��
            LED1=0;                //DS1��
            delay_ms(100);
        }
    }
    else
    {/* ��֤ͨ�� */
    }
    
    while(1)//LED����
    {
        LED0=0;                //DS0��
        LED1=1;                //DS1��
        delay_ms(1000);
        LED0=1;                //DS0��
        LED1=0;                //DS1��
        delay_ms(1000);
    }
}

















