#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
/* ����UID����ͷ�ļ� */
#include "UID_Encryption.h"

//ALIENTEK Mini STM32�����巶������11
//TFTLCD��ʾʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
/* 
V1.2:
    
    ���£�
        ����������Կ����Ϊ4�ֽڡ�8�ֽ�ʱ��ȡ�û��Զ��� IDԽ�絼���������Կ�������ȷ�����⡣
        MINI-Pro�ѻ������� V1.20B �汾�̼���ʹ��V1.2�汾���룻
        MINI�ѻ������� V1.4A2 �汾�̼���ʹ��V1.2�汾���룻
        
    Ӱ�죺
        ǰ��������
            (1).MINI���ѻ��������������˹̼���V1.4A2��ʹ��MINI�ѻ����������õ���V1.2�汾����;
            (2).MINI-Pro���ѻ��������������˹̼���V1.20B��ʹ��MINI�ѻ����������õ���V1.2�汾����;
            (3).��Կ��������Ϊ4�ֽڡ�8�ֽڵ������
        ��������
            (1).�����������㷨����Կ����Ϊ 4/8�ֽ�ʱ�������߼����ᵼ�����������Կ���������Կ����Ϊ4/8�ֽ���Ӱ�죩
            ��V1.1�汾ǰ�Ĵ�����������ͬ��
        ����취��
            (1).MINI-Pro���ѻ��������Ѿ�������V1.20B�汾�̼����û����Ի��˵��ɰ汾�̼�����ʹ�á�
            (2).MINI���ѻ��������Ѿ�������V1.4A2�汾�̼����û����Ի��˵��ɰ汾�̼�����ʹ�á�
        ����Ӱ��������
            (1).ֻҪ��Կ����Ϊ12�ֽھ�����Ӱ�죻
V1.1:
    
    ���£�
        MINI���ѻ�������V1,3A5��̼�ʹ��V1.1�汾���룬V1.1�汾�����޸���V1.0�汾
        ����UID_Encryption_Key_Check(),UID_Encryption_Key_Calculate()ʹ�ô��
        ģʽ�п��ܳ��ֵ��ڴ�Խ�����⡣
    Ӱ�죺
        ǰ��������
            (1).��������MINI���ѻ��������Ĺ̼���V1.3A5��ʹ��MINI�ѻ����������õ���V1.1�汾����;
            (2).��ǰ ʹ��V1.3A4��֮ǰ�汾�̼���MINI�ѻ������� ����Ϊ���ģʽ�����û�����ʹ�õ��������V1.0�汾���룻
        ��������
            (1).����ʹ��V1.3A5�汾�̼���MINI�ѻ���������������UID�Զ�����ܹ��ܣ�Ȼ�������¼������V1.0�汾������û�����
            ����V1.1�汾����Ĵ��ģʽ��Կ��V1.0�汾�������Կ��һ�£���˻ᵼ��оƬ�л���ֻ������Կ��֤��ͨ�������⣡
        ����취��
            (1).���û������е�V1.0�����ͬ�����µ�V1.1����롣
        ����Ӱ��������
            (1).��ǰʹ�� С��ģʽ ���õ��û���Ʒ�����ܵ�V1.1�汾��������Լ�MINI�ѻ��������̼����µ�Ӱ�죻
            (2).����Ѿ�ʹ��V1.0����Ĳ�Ʒ����ʹ��IAP��ʽ�����򲻻��ܵ�Ӱ�죻
            (3).����Ѿ�ʹ��V1.0����Ĳ�Ʒ����ʹ��MINI�ѻ�������������Ʒ �� ������UID�Զ�����ܹ������¸�����Կ�����ܵ�Ӱ�죬
            �������ʹ���ѻ�������������Ʒ�Ļ�����������û�������˵�UID�Զ�����ܴ���ΪV1.1��ͬʱ����UID�Զ���������¸�����Կ��
            (4)MINI-Pro���ѻ��������װ�̼���ʹ�õ���V1.1�汾�Ĵ��룬����Ӱ�죻
V1.0��
    MINI���ѻ�������V1.3A4��̼���֮ǰ�Ĺ̼��о�ʹ����V1.0�汾�Ĵ��룻
*/

/**** ��֤��Կ�����һЩ���� */
#define KEY_LOCATION   0x08020000  //��Կ�ڵ�ǰоƬ�еĴ洢��ַ
#define UID_LOCATION   0x1FFFF7E8  //��ǰоƬUID���ڵ�ַ
u8 checkResult = 0; //��֤���
u8 myID[12] = {
                0x01, 0x02, 0x03, 0x04,
                0x05, 0x06, 0x07, 0x08, 
                0x09, 0x0A, 0x0B, 0x0C};//�û��Զ���ID



int main(void)
{ 
    u8 x=0;
    
    u8 lcd_id[12];            //���LCD ID�ַ���    
    delay_init();             //��ʱ������ʼ��      
    uart_init(115200);         //���ڳ�ʼ��Ϊ9600
    LED_Init();                  //��ʼ����LED���ӵ�Ӳ���ӿ�
    LCD_Init();
    POINT_COLOR=RED; 
    sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣
    
    
/**** ��֤��Կ�Ƿ���Ч start ****/

    checkResult = UID_Encryption_Key_Check(  (void*)KEY_LOCATION,//���뵱ǰоƬFLASH�е���Կ���˴�����Ĳ�������¼������Ӧ����ȫһ��
                                             (void*)UID_LOCATION,//���뵱ǰоƬUID
                                              myID,              //�����û��Զ���ID, �˴�����Ĳ�������¼������Ӧ����ȫһ��
                                              LENGTH_12,         //������Կ���ȣ� �˴�����Ĳ�������¼������Ӧ����ȫһ��
                                              LITTLE_ENDIA,      //�������ѡ�� �˴�����Ĳ�������¼������Ӧ����ȫһ��
                                              ALGORITHM_2);      //�����㷨ѡ�� �˴�����Ĳ�������¼������Ӧ����ȫһ��

    if(checkResult != 0)//�����֤���Ϊ����ֵ������֤��ͨ��
    {   
        printf("\r\n��Կ�Ƿ�!\r\n"); 
        LCD_ShowString(30,40,200,24,24,"Invalid Key !!!");
        LED0=0;
        while(1)
        {     
            delay_ms(100);
            LED0=!LED0;
            LED1=!LED1;
        }
    }
    printf("\r\n��Կ�Ϸ�!\r\n");
    
/**** ��֤��Կ�Ƿ���Ч end ****/                             
    
    
    while(1) 
    {         
        switch(x)
        {
            case 0:LCD_Clear(WHITE);break;
            case 1:LCD_Clear(BLACK);break;
            case 2:LCD_Clear(BLUE);break;
            case 3:LCD_Clear(RED);break;
            case 4:LCD_Clear(MAGENTA);break;
            case 5:LCD_Clear(GREEN);break;
            case 6:LCD_Clear(CYAN);break;

            case 7:LCD_Clear(YELLOW);break;
            case 8:LCD_Clear(BRRED);break;
            case 9:LCD_Clear(GRAY);break;
            case 10:LCD_Clear(LGRAY);break;
            case 11:LCD_Clear(BROWN);break;
        }
        POINT_COLOR=RED;      
        LCD_ShowString(30,40,200,24,24,"Mini STM32 ^_^");    
        LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
        LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
         LCD_ShowString(30,110,200,16,16,lcd_id);        //��ʾLCD ID                               
        LCD_ShowString(30,130,200,12,12,"2014/3/7");                               
        x++;
        if(x==12)x=0;
        LED0=!LED0;     
        delay_ms(1000);    
    } 
}
