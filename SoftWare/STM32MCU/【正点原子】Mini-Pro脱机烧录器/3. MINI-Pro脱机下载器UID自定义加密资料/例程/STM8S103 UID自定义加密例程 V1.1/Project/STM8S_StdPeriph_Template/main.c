/**
  ******************************************************************************
  * @file    GPIO_Toggle\main.c
  * @author  MCD Application Team
  * @version V2.0.4
  * @date    26-April-2018
  * @brief   This file contains the main function for GPIO Toggle example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stdio.h"
#include "UID_Encryption.h"
/**
  * @addtogroup UART1_Printf
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifdef _RAISONANCE_
#define PUTCHAR_PROTOTYPE int putchar (char c)
#define GETCHAR_PROTOTYPE int getchar (void)
#elif defined (_COSMIC_)
#define PUTCHAR_PROTOTYPE char putchar (char c)
#define GETCHAR_PROTOTYPE char getchar (void)
#else /* _IAR_ */
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
#endif /* _RAISONANCE_ */












/**
  * @addtogroup GPIO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Evalboard I/Os configuration */

/* Private macro -------------------------------------------------------------*/
#define UID_LOCATION        0x004865
#define KEY_LOCATION        0x009F00

/* Private variables ---------------------------------------------------------*/

uint8_t myKey[12] = {0};
const uint8_t myID[12] = {  0x01, 0x02, 0x03, 0x04,
                            0x05, 0x06, 0x07, 0x08,
                            0x09, 0x0A, 0x0B, 0x0C};

/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	

void main(void)
{
	uint8_t i = 0;
	uint8_t checkResult = 0;

	UART1_Init( 115200,
                UART1_WORDLENGTH_8D,
                UART1_STOPBITS_1,
                UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE,
                UART1_MODE_TX_ENABLE);
    

    /* 以下步骤在实际应用时不需要，此处只是为了方便查看 *******************/
    /* 打印UID */ 
    printf("myUID:\r\n");
    for(i = 0; i < 12; i ++)
    {
        printf("%02X ", (uint16_t)*(uint8_t*)(UID_LOCATION + i));
    }
    printf("\r\n");
    
    /* 计算并打印密钥 */
    UID_Encryption_Key_Calculate(   (void*)myKey,        //[OUT]计算得到的密钥
                                    (void*)UID_LOCATION, //[IN]本芯片的UID地址
                                    (void*)myID,         //[IN]用户自定义ID
                                    LENGTH_12,           //[IN]密钥长度为12
                                    BIG_ENDIA,        //[IN]小端模式
                                    ALGORITHM_1);        //[IN]算法1
    printf("myKey:\r\n");
    for(i = 0; i < 12; i ++)
    {
        printf("%02X ", (uint16_t)myKey[i]);
    }
    printf("\r\n");
    /***************************************************************************/
    
    /* 验证密钥是否有效 start **************************************************/
    
    checkResult = UID_Encryption_Key_Check( (void*)KEY_LOCATION,  //传入当前芯片中的密钥，此处输入的参数与烧录器配置应当完全一致
                                            (void*)UID_LOCATION,  //传入当前芯片UID
                                            (void*)myID,          //传入用户自定义ID, 此处输入的参数与烧录器配置应当完全一致
                                            LENGTH_12,            //传入密钥长度， 此处输入的参数与烧录器配置应当完全一致
                                            BIG_ENDIA,         //传入端序模式， 此处输入的参数与烧录器配置应当完全一致
                                            ALGORITHM_1);         //传入算法选择， 此处输入的参数与烧录器配置应当完全一致
      
    if (checkResult != 0)//如果验证结果为非零值，则验证不通过
    {
        printf("\r\n密钥非法\r\n");
        /* 此处执行密钥非法相应措施 */
        while(1)
        {
            
        }
    }
    printf("\r\n密钥合法!\r\n");

	
	/* 验证密钥是否有效 end **************************************************/
	
    /* Infinite loop */
    while (1)
    {
    }
}



/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}



/**
  * @brief Retargets the C library printf function to the UART.
  * @param c Character to send
  * @retval char Character sent
  */
PUTCHAR_PROTOTYPE
{
  /* Write a character to the UART1 */
  UART1_SendData8(c);
  /* Loop until the end of transmission */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);

  return (c);
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval char Character to Read
  */
GETCHAR_PROTOTYPE
{
#ifdef _COSMIC_
  char c = 0;
#else
  int c = 0;
#endif
  /* Loop until the Read data register flag is SET */
  while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
    c = UART1_ReceiveData8();
  return (c);
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
