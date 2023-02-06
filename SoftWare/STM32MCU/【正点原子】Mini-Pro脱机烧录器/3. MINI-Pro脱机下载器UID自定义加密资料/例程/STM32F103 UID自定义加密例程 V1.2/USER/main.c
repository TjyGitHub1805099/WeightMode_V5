#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
/* 包含UID加密头文件 */
#include "UID_Encryption.h"

//ALIENTEK Mini STM32开发板范例代码11
//TFTLCD显示实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
/* 
V1.2:
    
    更新：
        修正配置密钥长度为4字节、8字节时，取用户自定义 ID越界导致运算的密钥结果不正确的问题。
        MINI-Pro脱机下载器 V1.20B 版本固件后使用V1.2版本代码；
        MINI脱机下载器 V1.4A2 版本固件后使用V1.2版本代码；
        
    影响：
        前提条件：
            (1).MINI版脱机下载器在升级了固件到V1.4A2后，使得MINI脱机下载器内置的是V1.2版本代码;
            (2).MINI-Pro版脱机下载器在升级了固件到V1.20B后，使得MINI脱机下载器内置的是V1.2版本代码;
            (3).密钥长度配置为4字节、8字节的情况；
        导致现象：
            (1).由于修正了算法里密钥长度为 4/8字节时的运算逻辑，会导致运算出的密钥结果（仅密钥长度为4/8字节受影响）
            与V1.1版本前的代码运算结果不同！
        解决办法：
            (1).MINI-Pro版脱机下载器已经升级到V1.20B版本固件的用户可以回退到旧版本固件继续使用。
            (2).MINI版脱机下载器已经升级到V1.4A2版本固件的用户可以回退到旧版本固件继续使用。
        不受影响的情况：
            (1).只要密钥长度为12字节均不受影响；
V1.1:
    
    更新：
        MINI版脱机下载器V1,3A5版固件使用V1.1版本代码，V1.1版本代码修复了V1.0版本
        调用UID_Encryption_Key_Check(),UID_Encryption_Key_Calculate()使用大端
        模式有可能出现的内存越界问题。
    影响：
        前提条件：
            (1).在升级了MINI版脱机下载器的固件到V1.3A5后，使得MINI脱机下载器内置的是V1.1版本代码;
            (2).此前 使用V1.3A4及之前版本固件的MINI脱机下载器 配置为大端模式，且用户程序使用的是最初的V1.0版本代码；
        导致现象：
            (1).后续使用V1.3A5版本固件的MINI脱机下载器，开启了UID自定义加密功能，然后继续烧录包含了V1.0版本代码的用户程序，
            由于V1.1版本计算的大端模式密钥与V1.0版本计算的密钥不一致，因此会导致芯片中会出现会造成密钥验证不通过的问题！
        解决办法：
            (1).将用户程序中的V1.0版代码同步更新到V1.1版代码。
        不受影响的情况：
            (1).此前使用 小端模式 配置的用户产品不会受到V1.1版本代码更新以及MINI脱机下载器固件更新的影响；
            (2).如果已经使用V1.0代码的产品后续使用IAP方式升级则不会受到影响；
            (3).如果已经使用V1.0代码的产品后续使用MINI脱机下载器升级产品 且 不开启UID自定义加密功能重新更新密钥不会受到影响，
            但是如果使用脱机下载器升级产品的话，建议更新用户代码的了的UID自定义加密代码为V1.1，同时开启UID自定义加密重新更新密钥；
            (4)MINI-Pro版脱机下载器首版固件中使用的是V1.1版本的代码，不受影响；
V1.0：
    MINI版脱机下载器V1.3A4版固件及之前的固件中均使用了V1.0版本的代码；
*/

/**** 验证密钥所需的一些参数 */
#define KEY_LOCATION   0x08020000  //密钥在当前芯片中的存储地址
#define UID_LOCATION   0x1FFFF7E8  //当前芯片UID所在地址
u8 checkResult = 0; //验证结果
u8 myID[12] = {
                0x01, 0x02, 0x03, 0x04,
                0x05, 0x06, 0x07, 0x08, 
                0x09, 0x0A, 0x0B, 0x0C};//用户自定义ID



int main(void)
{ 
    u8 x=0;
    
    u8 lcd_id[12];            //存放LCD ID字符串    
    delay_init();             //延时函数初始化      
    uart_init(115200);         //串口初始化为9600
    LED_Init();                  //初始化与LED连接的硬件接口
    LCD_Init();
    POINT_COLOR=RED; 
    sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
    
    
/**** 验证密钥是否有效 start ****/

    checkResult = UID_Encryption_Key_Check(  (void*)KEY_LOCATION,//传入当前芯片FLASH中的密钥，此处输入的参数与烧录器配置应当完全一致
                                             (void*)UID_LOCATION,//传入当前芯片UID
                                              myID,              //传入用户自定义ID, 此处输入的参数与烧录器配置应当完全一致
                                              LENGTH_12,         //传入密钥长度， 此处输入的参数与烧录器配置应当完全一致
                                              LITTLE_ENDIA,      //传入端序选择， 此处输入的参数与烧录器配置应当完全一致
                                              ALGORITHM_2);      //传入算法选择， 此处输入的参数与烧录器配置应当完全一致

    if(checkResult != 0)//如果验证结果为非零值，则验证不通过
    {   
        printf("\r\n密钥非法!\r\n"); 
        LCD_ShowString(30,40,200,24,24,"Invalid Key !!!");
        LED0=0;
        while(1)
        {     
            delay_ms(100);
            LED0=!LED0;
            LED1=!LED1;
        }
    }
    printf("\r\n密钥合法!\r\n");
    
/**** 验证密钥是否有效 end ****/                             
    
    
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
         LCD_ShowString(30,110,200,16,16,lcd_id);        //显示LCD ID                               
        LCD_ShowString(30,130,200,12,12,"2014/3/7");                               
        x++;
        if(x==12)x=0;
        LED0=!LED0;     
        delay_ms(1000);    
    } 
}
