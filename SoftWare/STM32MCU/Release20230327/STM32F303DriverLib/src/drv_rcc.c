/**
*******************************************************************
* @file    drv_rcc.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x RCC模块驱动程序
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __DRV_RCC_C__
#define __DRV_RCC_C__

#ifndef VECT_TAB_OFFSET
#define VECT_TAB_OFFSET		0x00
#endif

#include "drv_rcc.h"
#include "drv_nvic.h"


static UINT8 l_AhbPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
static UINT8 l_ApbPrescTable[8] = {0, 0 ,0 ,0 ,1, 2, 3, 4};
UINT32 l_RccWiteTimeOut = 0xFFFFFFFF;

structClockFreqType g_ClockFrequency;


/**
* @brief  初始化时钟.
* @param  XtalFreq: 晶振频率，单位MHz
* @param  CoreFreq: 内核频率，单位MHz 必须小于72M
* @param  Apb1Div: APB1分频值，参考定义
* @param  Apb2Div: APB2分频值，参考定义
* @retval 无
*/
UINT8 drv_rcc_init( UINT8 HseBypass, UINT16 XtalFreq, UINT16 CoreFreq, enumApb1PrescType Apb1Div, enumApb2PrescType Apb2Div, UINT32 VectStartAddress )
{
	UINT32 l_StatusTemp = 0;
	UINT32 l_WaitTimeOut = 0;
	UINT16 l_ClkMul = 0;
	
  /* FPU settings ------------------------------------------------------------*/
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
  #endif

	//寄存器复位
	RCC->CR.all |= (UINT32)0x00000001;
	RCC->CFGR.all &= 0xF87FC00C;
	RCC->CR.all &= (UINT32)0xFEF6FFFF;
	RCC->CR.all &= (UINT32)0xFFFBFFFF;
	RCC->CFGR.all &= (UINT32)0xFF80FFFF;
	RCC->CFGR2.all &= (UINT32)0xFFFFFFF0;
	RCC->CFGR3.all &= (UINT32)0xFF00FCCC;
	RCC->CIR.all = 0x00000000;
	
	//系统时钟设置
    if( XtalFreq == 0 )		//使用内部时钟
	{
		FLASH->ACR.all = 0x12;
		RCC->CR.bit.HSION = 1;
		//等待HSI准备好
		l_StatusTemp = 0;
		l_WaitTimeOut = 0;
		do{
			l_WaitTimeOut++;
			l_StatusTemp = RCC->CR.all;
			l_StatusTemp &= HSI_READY_FLAG;
			
		}while(( l_StatusTemp == 0 ) && ( l_WaitTimeOut < l_RccWiteTimeOut ));
		l_StatusTemp = RCC->CR.all;
		l_StatusTemp &= HSI_READY_FLAG;			//再次判断
		if( l_StatusTemp == 0 )
		{
			return 1;		//超时
		}
		else
		{
			//AHB APB1 APB2分频
			RCC->CFGR.bit.HPRE = (UINT32)AHB_PRESC_1;
			RCC->CFGR.bit.PPRE1 = (UINT32)Apb1Div;
			RCC->CFGR.bit.PPRE2 = (UINT32)Apb2Div;
			//PLL配置
			RCC->CFGR.bit.PLLSRC = 0;		//(UINT32)PLL_SOURCE_HSI_PRESC_2;
			l_ClkMul = CoreFreq / 4;		//HSI/2  MHZ所以再除1000000  HSI = 8000000 / 2000000 = 4
			if( l_ClkMul < 16 )
			{
				l_ClkMul = l_ClkMul - 2;
			}
			else
			{
				l_ClkMul = 15;
			}
			RCC->CFGR.bit.PLLMUL = l_ClkMul;
			RCC->CR.bit.PLLON= 1;
			//等待PLL准备好
			l_StatusTemp = 0;
			l_WaitTimeOut = 0;
			do{
				l_WaitTimeOut++;
				l_StatusTemp = RCC->CR.all;
				l_StatusTemp &= PLL_READY_FLAG;
			}while(( l_StatusTemp == 0 ) && ( l_WaitTimeOut <= l_RccWiteTimeOut ));
			l_StatusTemp = RCC->CR.all;
			l_StatusTemp &= PLL_READY_FLAG;
			if( l_StatusTemp == 0 )
			{
				return 2;	//等待超时
			}
			else
			{
				//系统时钟切换到PLL
				RCC->CFGR.bit.SW = SYSTEM_SOURCE_PLL;
				//等待PLL切换成系统时钟
				l_StatusTemp = 0;
				do{
					l_StatusTemp = RCC->CFGR.all;
					l_StatusTemp &= SYS_SOURCE_IS_PLL;
				}while( l_StatusTemp != SYS_SOURCE_IS_PLL );
			} 
		}
	}
	else	//使用外部时钟
	{
		RCC->CFGR2.bit.PREDIV = 0;		//HSE不分频 设置PLL时在2分频
		RCC->CR.all &= 0xFF00FFFF;		//与HSE有关的几个配置位清零

		//等待HSE准备好
		l_StatusTemp= 0;
		l_WaitTimeOut = 0;
        if( 1 == HseBypass )
        {
            RCC->CR.bit.HSEBYP = 1;
        }
        //else
        //{
		    RCC->CR.bit.HSEON = 1;
            do
            {
                l_WaitTimeOut++;
                l_StatusTemp = RCC->CR.all;
                l_StatusTemp &= HSE_READY_FLAG;
            } while( (l_StatusTemp == 0) && (l_WaitTimeOut < l_RccWiteTimeOut) );
        //}
		//启动SHE后会有等待时间利用该时间做计算
        g_ClockFrequency.XtalFreq = XtalFreq * 1000000;
		l_StatusTemp = RCC->CR.all;
		l_StatusTemp &= HSE_READY_FLAG;
		if( l_StatusTemp == 0 )
		{
			return 1;		//	等待超时
		}
		else
		{
			FLASH->ACR.bit.PRFTBE = 1;				//开启FLASH预存取功能
			FLASH->ACR.bit.LATENCY = 2;				//FLASH延时	
			//AHB APB1 APB2分频
			RCC->CFGR.bit.HPRE = (UINT32)AHB_PRESC_1;
			RCC->CFGR.bit.PPRE1 = (UINT32)Apb1Div;
			RCC->CFGR.bit.PPRE2 = (UINT32)Apb2Div;
			//PLL配置
			RCC->CFGR.bit.PLLXTPRE = 1;			//HSE2分频
			RCC->CFGR.bit.PLLSRC = 1;			//(UINT32)PLL_SOURCE_HSE_PREDIV;
			l_ClkMul = 0;
            l_ClkMul = CoreFreq / (XtalFreq / 2);
			if( l_ClkMul < 16 )
			{
				l_ClkMul = l_ClkMul - 2;
			}
			else
			{
				l_ClkMul = 15;
			}
			RCC->CFGR.bit.PLLMUL = l_ClkMul;
			RCC->CR.bit.PLLON= 1;
			//等待PLL准备好
			l_StatusTemp = 0;
			l_WaitTimeOut = 0;
			do{
				l_WaitTimeOut++;
				l_StatusTemp = RCC->CR.all;
				l_StatusTemp &= PLL_READY_FLAG;
			}while(( l_StatusTemp == 0 ) && ( l_WaitTimeOut < l_RccWiteTimeOut ));
			l_StatusTemp = RCC->CR.all;
			l_StatusTemp &= PLL_READY_FLAG;
			if( l_StatusTemp == 0 )
			{
				return 2;	//等待超时
			}
			else
			{
				//系统时钟切换到PLL
				RCC->CFGR.bit.SW = SYSTEM_SOURCE_PLL;
				//等待PLL切换成系统时钟
				l_StatusTemp = 0;
				do{
					l_StatusTemp = RCC->CFGR.all;
					l_StatusTemp &= SYS_SOURCE_IS_PLL;
				}while( l_StatusTemp != SYS_SOURCE_IS_PLL );
			} 
		}
	}
	
	SCB->VTOR = VectStartAddress;											//中断向量起始地址
	SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup_2;					//中断向量分组
	
	// 最后获取系统时钟频率信息
	drv_rcc_get_clocks_freq( &g_ClockFrequency );
	
	return 0;
}

/**
* @brief  获取芯片内核及各总线时钟.
* @note   只使用外部时钟源，启用PLL倍频
* @param  pClockFreq: 时钟频率，单位Hz
* @note   串口函数可以使用该函数提供的参数来计算波特率，定时器计算时也需要用到
* @retval 无
*/
void drv_rcc_get_clocks_freq( structClockFreqType *pClockFreq )
{
	UINT32 tmp = 0, presc = 0, pllvco = 0, pllsource = 0, pllmul = 0;
	
	// 计算核心频率和外设频率
	tmp = (UINT8)( RCC->CFGR.all & SYS_SOURCE_FLAG );	//CLK SOURCE
	switch( tmp )
	{
		case 0x00:										//HSI
		g_ClockFrequency.CoreFreq = 8000000;
		break;
		case 0x04:  									//HSE
		g_ClockFrequency.CoreFreq = g_ClockFrequency.XtalFreq;
		break;
		case 0x08:										//PLL

		pllsource = RCC->CFGR.all;	
		#ifdef STM32F303XDE
		pllsource = ( pllsource & PLL_SOURCE_FALG ) >> 15;
		#else
		pllsource = ( pllsource & PLL_SOURCE_FALG ) >> 16;	//PLL SOURCE
		#endif
		pllmul = RCC->CFGR.all;
		pllmul = ( pllmul & PLL_CLK_MUL ) >> 18;			//PLL 倍频系数
		
		if( pllmul < 0x0E )
		{
			pllmul = pllmul + 2;
		}
		else
		{
			pllmul = 16;
		}
		if ( pllsource != 0 )
		{
			pllvco = g_ClockFrequency.XtalFreq / 2 * pllmul;	// PLL输出 = HSE * 倍频系数(HSE默认不分频)
		}
		else
		{
			pllvco = 8000000 * pllmul / 2;					// PLL输出 = HSI/2 * 倍频系数	
		}
		g_ClockFrequency.CoreFreq = pllvco;					// 得到系统时钟 					
		break;
		default:
		g_ClockFrequency.CoreFreq = 8000000;				// 默认为HSI时钟 
		break;
	}
	// 获取HCLK, PCLK1 and PCLK2 时钟频率 
	tmp = RCC->CFGR.bit.HPRE;												// 获取HCLK分频系数,Bit4~7 
	presc = l_AhbPrescTable[tmp];											// 查表获得AHB分频系数2的幂:presc 
	g_ClockFrequency.AhbFreq = g_ClockFrequency.CoreFreq >> presc;			// 计算得出实际AHB总线上频率 

	tmp = RCC->CFGR.bit.PPRE1;												// 获取PCLK1分频系数,Bit10~12 
	presc = l_ApbPrescTable[tmp];											// 查表获得PCLK1分频系数2的幂:presc 
	g_ClockFrequency.Apb1Freq = g_ClockFrequency.AhbFreq >> presc;			// 计算得出实际PCLK1总线上频率 

	tmp = RCC->CFGR.bit.PPRE2;												// 获取PCLK2分频系数,Bit13~15 
	presc = l_ApbPrescTable[tmp];											// 查表获得PCLK2分频系数2的幂:presc 
	g_ClockFrequency.Apb2Freq = g_ClockFrequency.AhbFreq >> presc;			// 计算得出实际PCLK2总线上频率 
	// 计算挂在外设上的定时器时钟频率
	if (g_ClockFrequency.AhbFreq == g_ClockFrequency.Apb1Freq)
	{
		g_ClockFrequency.Apb1TimerClkFreq = g_ClockFrequency.Apb1Freq;
	}
	else
	{
		g_ClockFrequency.Apb1TimerClkFreq = 2 * g_ClockFrequency.Apb1Freq;
	}
	if (g_ClockFrequency.AhbFreq == g_ClockFrequency.Apb2Freq)
	{
		g_ClockFrequency.Apb2TimerClkFreq = g_ClockFrequency.Apb2Freq;
	}
	else
	{
		g_ClockFrequency.Apb2TimerClkFreq = 2 * g_ClockFrequency.Apb2Freq;
	}
}

/**
* @brief  使能 AHB1 外设时钟.
* @note   复位后所有外设时钟全部是禁止状态.
* @param  RccAhbPeriph: 要控制时钟开关的 AHB 外设. 可以是下面值的组合
*            @arg RCC_AHBENR_DMA1EN:       
*            @arg RCC_AHBENR_DMA2EN:     
*            @arg RCC_AHBENR_SRAMEN:      
*            @arg RCC_AHBENR_FLITFEN:      
*            @arg RCC_AHBENR_FMCEN:   
*            @arg RCC_AHBENR_CRCEN:   
*            @arg RCC_AHBENR_GPIOHEN:     
*            @arg RCC_AHBENR_GPIOAEN: 
*            @arg RCC_AHBENR_GPIOBEN:  
*            @arg RCC_AHBENR_GPIOCEN:
*            @arg RCC_AHBENR_GPIODEN:     
*            @arg RCC_AHBENR_GPIOEEN:
*            @arg RCC_AHBENR_GPIOFEN:
*            @arg RCC_AHBENR_GPIOGEN:   
*            @arg RCC_AHBENR_TSEN:   
*            @arg RCC_AHBENR_ADC12EN: 
*            @arg RCC_AHBENR_ADC34EN:  
* @retval 无
*/
void drv_rcc_ahb1_clk_enable( UINT32 RccAhbPeriph )
{ 
	RCC->AHBENR.all |= RccAhbPeriph;						
}

/**
* @brief  禁止 AHB 外设时钟.
* @note   复位后所有外设时钟全部是禁止状态.
* @param  RccAhbPeriph: 要控制时钟开关的 AHB 外设. 参考 drv_rcc_ahb1_clk_enable
* @retval 无
*/
void drv_rcc_ahb1_clk_disable( UINT32 RccAhbPeriph )
{ 
	RCC->AHBENR.all &= (UINT32)(~RccAhbPeriph);
}

/**
* @brief  使能 APB1 外设时钟.
* @note   复位后所有外设时钟全部是禁止状态.
* @param  RccApb1Periph: 要控制时钟开关的 APB1 外设. 可以是下面值的组合
*            @arg RCC_APB1ENR_TIM2EN:   TIM2 时钟
*            @arg RCC_APB1ENR_TIM3EN:   TIM3 时钟
*            @arg RCC_APB1ENR_TIM4EN:   TIM4 时钟
*            @arg RCC_APB1ENR_TIM5EN:   TIM5 时钟
*            @arg RCC_APB1ENR_TIM6EN:   TIM6 时钟
*            @arg RCC_APB1ENR_TIM7EN:   TIM7 时钟
*            @arg RCC_APB1ENR_WWDGEN:  WWDG 时钟
*            @arg RCC_APB1ENR_SPI2EN:  SPI2 时钟
*            @arg RCC_APB1ENR_SPI3EN:  SPI3 时钟
*            @arg RCC_APB1ENR_USART2EN:   USART 时钟
*            @arg RCC_APB1ENR_USART3EN:   USART 时钟
*            @arg RCC_APB1ENR_UART4EN:   UART4 时钟
*            @arg RCC_APB1ENR_UART5EN:  UART5 时钟
*            @arg RCC_APB1ENR_I2C1EN:  I2C1 时钟
*            @arg RCC_APB1ENR_I2C2EN:  I2C2 时钟
*            @arg RCC_APB1ENR_USBEN:  USB 时钟
*            @arg RCC_APB1ENR_CAN1EN:   CAN1 时钟
*            @arg RCC_APB1ENR_DAC2EN:   DAC2 时钟
*            @arg RCC_APB1ENR_PWREN:   PWR 时钟
*            @arg RCC_APB1ENR_DAC1EN:   DAC1 时钟
*            @arg RCC_APB1ENR_I2C3EN:   I2C3 时钟
*            @arg RCC_APB1ENR_DACEN:    DAC 时钟
* @retval 无
*/
void drv_rcc_apb1_clk_enable( UINT32 RccApb1Periph )
{
	RCC->APB1ENR.all |= RccApb1Periph;
}

/**
* @brief  禁止 APB1 外设时钟.
* @note   复位后所有外设时钟全部是禁止状态.
* @param  RccApb1Periph: 要控制时钟开关的 APB1 外设. 参考 drv_rcc_apb1_clk_enable 部分说明
* @retval 无
*/
void drv_rcc_apb1_clk_disable( UINT32 RccApb1Periph )
{ 
	RCC->APB1ENR.all &= (UINT32)(~RccApb1Periph);
}

/**
* @brief  使能 APB2 外设时钟.
* @note   复位后所有外设时钟全部是禁止状态.
* @param  RccApb2Periph: 要控制时钟开关的 APB2 外设. 可以是下面值的组合
*            @arg RCC_APB2ENR_SYSCFGEN:   SYSCFG 时钟
*            @arg RCC_APB2ENR_TIM1EN:   TIM1 时钟
*            @arg RCC_APB2ENR_SPI1EN:  SPI1 时钟
*            @arg RCC_APB2ENR_TIM8EN:  TIM8 时钟
*            @arg RCC_APB2ENR_USART1EN:   USART1 时钟
*            @arg RCC_APB2ENR_SPI4EN:   SPI4 时钟
*            @arg RCC_APB2ENR_TIM15EN:   TIM15 时钟
*            @arg RCC_APB2ENR_TIM16EN:   TIM16 时钟
*            @arg RCC_APB2ENR_TIM17EN:   TIM17 时钟
*            @arg RCC_APB2ENR_TIM20EN:   TIM20 时钟
*            @arg RCC_APB2ENR_HRTIM1: HRTIM1 时钟
* @retval 无
*/
void drv_rcc_apb2_clk_enable( UINT32 RccApb2Periph )
{
	RCC->APB2ENR.all |= RccApb2Periph;
}

/**
* @brief  禁止 APB2 外设时钟.
* @note   复位后所有外设时钟全部是禁止状态.
* @param  RccApb2Periph: 要控制时钟开关的 APB2 外设. 参考 drv_rcc_apb2_clk_enable 说明
* @retval 无
*/
void drv_rcc_apb2_clk_disable( UINT32 RccApb2Periph )
{
	RCC->APB2ENR.all &= (UINT32)(~RccApb2Periph);
}

/**
* @brief  强制复位 AHB 外设.
* @param  RccAhb1Periph: 要复位的 AHB1 外设，可以是下面值的组合
*            @arg RCC_AHBRSTR_FMCRST:       FMC 时钟
*            @arg RCC_AHBRSTR_GPIOHRST:       GPIOH 时钟
*            @arg RCC_AHBRSTR_GPIOARST:       GPIOA 时钟
*            @arg RCC_AHBRSTR_GPIOBRST:       GPIOB 时钟
*            @arg RCC_AHBRSTR_GPIOCRST:       GPIOC 时钟
*            @arg RCC_AHBRSTR_GPIODRST:       GPIOD 时钟
*            @arg RCC_AHBRSTR_GPIOERST:       GPIOE 时钟
*            @arg RCC_AHBRSTR_GPIOFRST:       GPIOF 时钟
*            @arg RCC_AHBRSTR_GPIOGRST:       GPIOG 时钟
*            @arg RCC_AHBRSTR_TSRST:         TS 时钟
*            @arg RCC_AHBRSTR_ADC12RST:        ADC12 时钟
*            @arg RCC_AHBRSTR_ADC34RST:        ADC34 时钟
* @retval 无
*/
void drv_rcc_ahb_periph_reset_enable( UINT32 RccAhbPeriph )
{
	RCC->AHBRSTR.all |= RccAhbPeriph;
}

/**
* @brief  或解除复位 AHB 外设.
* @param  RccAhb1Periph: 要复位的 AHB1 外设，参考 drv_rcc_ahb_periph_reset_enable 说明
* @retval 无
*/
void drv_rcc_ahb_periph_reset_disable( UINT32 RccAhbPeriph )
{ 
	RCC->AHBRSTR.all &= (UINT32)(~RccAhbPeriph);
}

/**
* @brief  强制复位 APB1 外设.
* @param  RccApb1Periph: 要复位的 APB1 外设，可以是下面值的组合
*            @arg RCC_APB1RSTR_TIM2RST:   TIM2 时钟
*            @arg RCC_APB1RSTR_TIM3RST:   TIM3 时钟
*            @arg RCC_APB1RSTR_TIM4RST:   TIM4 时钟
*            @arg RCC_APB1RSTR_TIM6RST:   TIM5 时钟
*            @arg RCC_APB1RSTR_TIM7RST:   TIM6 时钟
*            @arg RCC_APB1RSTR_WWDGRST:   TIM7 时钟
*            @arg RCC_APB1RSTR_SPI2RST:  TIM12 时钟
*            @arg RCC_APB1RSTR_SPI3RST:  TIM13 时钟
*            @arg RCC_APB1RSTR_USART2RST:  TIM14 时钟
*            @arg RCC_APB1RSTR_USART3RST:   WWDG 时钟
*            @arg RCC_APB1RSTR_UART4RST:   SPI2 时钟
*            @arg RCC_APB1RSTR_UART5RST:   SPI3 时钟
*            @arg RCC_APB1RSTR_I2C1RST:  UART2 时钟
*            @arg RCC_APB1RSTR_I2C2RST:  UART3 时钟
*            @arg RCC_APB1RSTR_USBRST:  UART4 时钟
*            @arg RCC_APB1RSTR_CAN1RST:  UART5 时钟
*            @arg RCC_APB1RSTR_PWRRST:   I2C1 时钟
*            @arg RCC_APB1RSTR_DAC1RST:   I2C2 时钟
*            @arg RCC_APB1RSTR_I2C3RST:   I2C3 时钟
*            @arg RCC_APB1RSTR_DAC2RST:   CAN1 时钟
*            @arg RCC_APB1RSTR_DACRST:   CAN2 时钟
* @retval 无
*/
void drv_rcc_apb1_periph_reset_enable( UINT32 RccApb1Periph )
{ 
	RCC->APB1RSTR.all |= RccApb1Periph;
}

/**
* @brief  解除复位 APB1 外设.
* @param  RccApb1Periph: 要复位的 APB1 外设，参考 drv_rcc_apb1_periph_reset_enable 说明
* @retval 无
*/
void drv_rcc_apb1_periph_reset_disable( UINT32 RccApb1Periph )
{ 
	RCC->APB1RSTR.all &= (UINT32)(~RccApb1Periph);
}

/**
* @brief  强制复位 APB2 外设.
* @param  RccApb2Periph: 要复位的 APB2 外设，可以是下面值的组合
*            @arg RCC_APB2RSTR_SYSCFGRST:   TIM1 时钟
*            @arg RCC_APB2RSTR_TIM1RST:   TIM8 时钟
*            @arg RCC_APB2RSTR_SPI1RST:  UART1 时钟
*            @arg RCC_APB2RSTR_TIM8RST:  UART6 时钟
*            @arg RCC_APB2RSTR_USART1RST:   ADC1 时钟
*            @arg RCC_APB2RSTR_SPI4RST:   ADC2 时钟
*            @arg RCC_APB2RSTR_TIM15RST:   ADC3 时钟
*            @arg RCC_APB2RSTR_TIM16RST:   SDIO 时钟
*            @arg RCC_APB2RSTR_TIM17RST:   SPI1 时钟
*            @arg RCC_APB2RSTR_TIM20RST:   SPI4 时钟
*            @arg RCC_APB2RSTR_HRTIM1RST: SYSCFG 时钟
* @retval 无
*/
void drv_rcc_apb2_periph_reset_enable( UINT32 RccApb2Periph )
{
	RCC->APB2RSTR.all |= RccApb2Periph;
}

/**
* @brief  解除复位 APB2 外设.
* @param  RccApb2Periph: 要复位的 APB2 外设，参考 drv_rcc_apb2_periph_reset_enable
* @retval 无
*/
void drv_rcc_apb2_periph_reset_disable( UINT32 RccApb2Periph )
{ 
	RCC->APB2RSTR.all &= (UINT32)(~RccApb2Periph);
}

/**
* @brief  设置ADC12分频系数.
* @param  AdcPresc: PLL时钟到ADC模块的分频系数
* @retval 无
*/
void drv_rcc_adc12_presc( enumAdcPrescType AdcPresc )
{
	RCC->CFGR2.bit.ADC12PRES = (UINT16)AdcPresc;
}

/**
* @brief  设置ADC34分频系数.
* @param  AdcPresc: PLL时钟到ADC模块的分频系数
* @retval 无
*/
void drv_rcc_adc34_presc( enumAdcPrescType AdcPresc )
{
	RCC->CFGR2.bit.ADC34PRES = (UINT16)AdcPresc;
}

#endif 
