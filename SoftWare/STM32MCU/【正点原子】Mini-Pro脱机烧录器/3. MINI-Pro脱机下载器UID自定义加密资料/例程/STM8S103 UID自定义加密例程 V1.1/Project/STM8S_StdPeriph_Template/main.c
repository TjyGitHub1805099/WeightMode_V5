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
    

    /* ���²�����ʵ��Ӧ��ʱ����Ҫ���˴�ֻ��Ϊ�˷���鿴 *******************/
    /* ��ӡUID */ 
    printf("myUID:\r\n");
    for(i = 0; i < 12; i ++)
    {
        printf("%02X ", (uint16_t)*(uint8_t*)(UID_LOCATION + i));
    }
    printf("\r\n");
    
    /* ���㲢��ӡ��Կ */
    UID_Encryption_Key_Calculate(   (void*)myKey,        //[OUT]����õ�����Կ
                                    (void*)UID_LOCATION, //[IN]��оƬ��UID��ַ
                                    (void*)myID,         //[IN]�û��Զ���ID
                                    LENGTH_12,           //[IN]��Կ����Ϊ12
                                    BIG_ENDIA,        //[IN]С��ģʽ
                                    ALGORITHM_1);        //[IN]�㷨1
    printf("myKey:\r\n");
    for(i = 0; i < 12; i ++)
    {
        printf("%02X ", (uint16_t)myKey[i]);
    }
    printf("\r\n");
    /***************************************************************************/
    
    /* ��֤��Կ�Ƿ���Ч start **************************************************/
    
    checkResult = UID_Encryption_Key_Check( (void*)KEY_LOCATION,  //���뵱ǰоƬ�е���Կ���˴�����Ĳ�������¼������Ӧ����ȫһ��
                                            (void*)UID_LOCATION,  //���뵱ǰоƬUID
                                            (void*)myID,          //�����û��Զ���ID, �˴�����Ĳ�������¼������Ӧ����ȫһ��
                                            LENGTH_12,            //������Կ���ȣ� �˴�����Ĳ�������¼������Ӧ����ȫһ��
                                            BIG_ENDIA,         //�������ģʽ�� �˴�����Ĳ�������¼������Ӧ����ȫһ��
                                            ALGORITHM_1);         //�����㷨ѡ�� �˴�����Ĳ�������¼������Ӧ����ȫһ��
      
    if (checkResult != 0)//�����֤���Ϊ����ֵ������֤��ͨ��
    {
        printf("\r\n��Կ�Ƿ�\r\n");
        /* �˴�ִ����Կ�Ƿ���Ӧ��ʩ */
        while(1)
        {
            
        }
    }
    printf("\r\n��Կ�Ϸ�!\r\n");

	
	/* ��֤��Կ�Ƿ���Ч end **************************************************/
	
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
