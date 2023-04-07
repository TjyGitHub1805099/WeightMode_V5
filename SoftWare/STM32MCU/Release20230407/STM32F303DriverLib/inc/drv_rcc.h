/**
*******************************************************************
* @file    drv_rcc.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   STM32F40x RCC模块驱动程序头文件
*******************************************************************
* @attention
*
*
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/
#ifndef __DRV_RCC_H__
#define __DRV_RCC_H__

#define __FPU_PRESENT		1
#define __FPU_USED			1

#include "reg_stm32f303_rcc.h"
#include "reg_stm32f303_flash.h"

#define HSI_READY_FLAG			((UINT32)0x00000002)
#define HSE_READY_FLAG			((UINT32)0x00020000)
#define PLL_READY_FLAG			((UINT32)0x02000000)
#define SYS_SOURCE_FLAG			((UINT32)0x0000000C)
#define PLL_SOURCE_FALG			((UINT32)0x00018000)
#define PLL_CLK_MUL				((UINT32)0x003C0000)
#define SYS_SOURCE_IS_PLL		((UINT32)0x00000008)


/*******************  Bit definition for RCC_AHBRSTR register  ****************/
#define  RCC_AHBRSTR_FMCRST                  ((UINT32)0x00000020)         /*!< FMC reset */
#define  RCC_AHBRSTR_GPIOHRST                ((UINT32)0x00010000)         /*!< GPIOH reset */
#define  RCC_AHBRSTR_GPIOARST                ((UINT32)0x00020000)         /*!< GPIOA reset */
#define  RCC_AHBRSTR_GPIOBRST                ((UINT32)0x00040000)         /*!< GPIOB reset */
#define  RCC_AHBRSTR_GPIOCRST                ((UINT32)0x00080000)         /*!< GPIOC reset */
#define  RCC_AHBRSTR_GPIODRST                ((UINT32)0x00010000)         /*!< GPIOD reset */
#define  RCC_AHBRSTR_GPIOERST                ((UINT32)0x00200000)         /*!< GPIOE reset */
#define  RCC_AHBRSTR_GPIOFRST                ((UINT32)0x00400000)         /*!< GPIOF reset */
#define  RCC_AHBRSTR_GPIOGRST                ((UINT32)0x00800000)         /*!< GPIOG reset */
#define  RCC_AHBRSTR_TSRST                   ((UINT32)0x00100000)         /*!< TS reset */
#define  RCC_AHBRSTR_ADC12RST                ((UINT32)0x10000000)         /*!< ADC1 & ADC2 reset */
#define  RCC_AHBRSTR_ADC34RST                ((UINT32)0x20000000)         /*!< ADC3 & ADC4 reset */
/******************  Bit definition for RCC_AHBENR register  ******************/
#define  RCC_AHBENR_DMA1EN                   ((UINT32)0x00000001)        /*!< DMA1 clock enable */
#define  RCC_AHBENR_DMA2EN                   ((UINT32)0x00000002)        /*!< DMA2 clock enable */
#define  RCC_AHBENR_SRAMEN                   ((UINT32)0x00000004)        /*!< SRAM interface clock enable */
#define  RCC_AHBENR_FLITFEN                  ((UINT32)0x00000010)        /*!< FLITF clock enable */
#define  RCC_AHBENR_FMCEN                    ((UINT32)0x00000020)        /*!< FMC clock enable */
#define  RCC_AHBENR_CRCEN                    ((UINT32)0x00000040)        /*!< CRC clock enable */
#define  RCC_AHBENR_GPIOHEN                  ((UINT32)0x00010000)        /*!< GPIOH clock enable */
#define  RCC_AHBENR_GPIOAEN                  ((UINT32)0x00020000)        /*!< GPIOA clock enable */
#define  RCC_AHBENR_GPIOBEN                  ((UINT32)0x00040000)        /*!< GPIOB clock enable */
#define  RCC_AHBENR_GPIOCEN                  ((UINT32)0x00080000)        /*!< GPIOC clock enable */
#define  RCC_AHBENR_GPIODEN                  ((UINT32)0x00100000)        /*!< GPIOD clock enable */
#define  RCC_AHBENR_GPIOEEN                  ((UINT32)0x00200000)        /*!< GPIOE clock enable */
#define  RCC_AHBENR_GPIOFEN                  ((UINT32)0x00400000)        /*!< GPIOF clock enable */
#define  RCC_AHBENR_GPIOGEN                  ((UINT32)0x00800000)        /*!< GPIOG clock enable */
#define  RCC_AHBENR_TSEN                     ((UINT32)0x01000000)        /*!< TS clock enable */
#define  RCC_AHBENR_ADC12EN                  ((UINT32)0x10000000)        /*!< ADC1/ ADC2 clock enable */
#define  RCC_AHBENR_ADC34EN                  ((UINT32)0x20000000)        /*!< ADC3/ ADC4 clock enable */
/******************  Bit definition for RCC_APB1RSTR register  ******************/
#define  RCC_APB1RSTR_TIM2RST                ((UINT32)0x00000001)        /*!< Timer 2 reset */
#define  RCC_APB1RSTR_TIM3RST                ((UINT32)0x00000002)        /*!< Timer 3 reset */
#define  RCC_APB1RSTR_TIM4RST                ((UINT32)0x00000004)        /*!< Timer 4 reset */
#define  RCC_APB1RSTR_TIM6RST                ((UINT32)0x00000010)        /*!< Timer 6 reset */
#define  RCC_APB1RSTR_TIM7RST                ((UINT32)0x00000020)        /*!< Timer 7 reset */
#define  RCC_APB1RSTR_WWDGRST                ((UINT32)0x00000800)        /*!< Window Watchdog reset */
#define  RCC_APB1RSTR_SPI2RST                ((UINT32)0x00004000)        /*!< SPI2 reset */
#define  RCC_APB1RSTR_SPI3RST                ((UINT32)0x00008000)        /*!< SPI3 reset */
#define  RCC_APB1RSTR_USART2RST              ((UINT32)0x00020000)        /*!< USART 2 reset */
#define  RCC_APB1RSTR_USART3RST              ((UINT32)0x00040000)        /*!< USART 3 reset */
#define  RCC_APB1RSTR_UART4RST               ((UINT32)0x00080000)        /*!< UART 4 reset */
#define  RCC_APB1RSTR_UART5RST               ((UINT32)0x00100000)        /*!< UART 5 reset */
#define  RCC_APB1RSTR_I2C1RST                ((UINT32)0x00200000)        /*!< I2C 1 reset */
#define  RCC_APB1RSTR_I2C2RST                ((UINT32)0x00400000)        /*!< I2C 2 reset */
#define  RCC_APB1RSTR_USBRST                 ((UINT32)0x00800000)        /*!< USB reset */
#define  RCC_APB1RSTR_CAN1RST                ((UINT32)0x02000000)        /*!< CAN reset */
#define  RCC_APB1RSTR_PWRRST                 ((UINT32)0x10000000)        /*!< PWR reset */
#define  RCC_APB1RSTR_DAC1RST                ((UINT32)0x20000000)        /*!< DAC 1 reset */
#define  RCC_APB1RSTR_I2C3RST                ((UINT32)0x40000000)        /*!< I2C 3 reset */
#define  RCC_APB1RSTR_DAC2RST                ((UINT32)0x04000000)        /*!< DAC 2 reset */
#define  RCC_APB1RSTR_DACRST                 RCC_APB1RSTR_DAC1RST          /*!< DAC reset */
/******************  Bit definition for RCC_APB1ENR register  ******************/
#define  RCC_APB1ENR_TIM2EN                  ((UINT32)0x00000001)        /*!< Timer 2 clock enable */
#define  RCC_APB1ENR_TIM3EN                  ((UINT32)0x00000002)        /*!< Timer 3 clock enable */
#define  RCC_APB1ENR_TIM4EN                  ((UINT32)0x00000004)        /*!< Timer 4 clock enable */
#define  RCC_APB1ENR_TIM6EN                  ((UINT32)0x00000010)        /*!< Timer 6 clock enable */
#define  RCC_APB1ENR_TIM7EN                  ((UINT32)0x00000020)        /*!< Timer 7 clock enable */
#define  RCC_APB1ENR_WWDGEN                  ((UINT32)0x00000800)        /*!< Window Watchdog clock enable */
#define  RCC_APB1ENR_SPI2EN                  ((UINT32)0x00004000)        /*!< SPI2 clock enable */
#define  RCC_APB1ENR_SPI3EN                  ((UINT32)0x00008000)        /*!< SPI3 clock enable */
#define  RCC_APB1ENR_USART2EN                ((UINT32)0x00020000)        /*!< USART 2 clock enable */
#define  RCC_APB1ENR_USART3EN                ((UINT32)0x00040000)        /*!< USART 3 clock enable */
#define  RCC_APB1ENR_UART4EN                 ((UINT32)0x00080000)        /*!< UART 4 clock enable */
#define  RCC_APB1ENR_UART5EN                 ((UINT32)0x00100000)        /*!< UART 5 clock enable */
#define  RCC_APB1ENR_I2C1EN                  ((UINT32)0x00200000)        /*!< I2C 1 clock enable */
#define  RCC_APB1ENR_I2C2EN                  ((UINT32)0x00400000)        /*!< I2C 2 clock enable */
#define  RCC_APB1ENR_USBEN                   ((UINT32)0x00800000)        /*!< USB clock enable */
#define  RCC_APB1ENR_CAN1EN                  ((UINT32)0x02000000)        /*!< CAN clock enable */
#define  RCC_APB1ENR_DAC2EN                  ((UINT32)0x04000000)        /*!< DAC 2 clock enable */
#define  RCC_APB1ENR_PWREN                   ((UINT32)0x10000000)        /*!< PWR clock enable */
#define  RCC_APB1ENR_DAC1EN                  ((UINT32)0x20000000)        /*!< DAC clock enable */
#define  RCC_APB1ENR_I2C3EN                  ((UINT32)0x40000000)        /*!< I2C 3 clock enable */
#define  RCC_APB1ENR_DACEN                   RCC_APB1ENR_DAC1EN
/******************  Bit definition for RCC_APB2RSTR register  *****************/
#define  RCC_APB2RSTR_SYSCFGRST              ((UINT32)0x00000001)        /*!< SYSCFG reset */
#define  RCC_APB2RSTR_TIM1RST                ((UINT32)0x00000200)        /*!< TIM1 reset */
#define  RCC_APB2RSTR_SPI1RST                ((UINT32)0x00001000)        /*!< SPI1 reset */
#define  RCC_APB2RSTR_TIM8RST                ((UINT32)0x00002000)        /*!< TIM8 reset */
#define  RCC_APB2RSTR_USART1RST              ((UINT32)0x00004000)        /*!< USART1 reset */
#define  RCC_APB2RSTR_SPI4RST                ((UINT32)0x00008000)        /*!< SPI4 reset */
#define  RCC_APB2RSTR_TIM15RST               ((UINT32)0x00010000)        /*!< TIM15 reset */
#define  RCC_APB2RSTR_TIM16RST               ((UINT32)0x00020000)        /*!< TIM16 reset */
#define  RCC_APB2RSTR_TIM17RST               ((UINT32)0x00040000)        /*!< TIM17 reset */
#define  RCC_APB2RSTR_TIM20RST               ((UINT32)0x00100000)        /*!< TIM20 reset */
#define  RCC_APB2RSTR_HRTIM1RST              ((UINT32)0x20000000)        /*!< HRTIM1 reset */
/*****************  Bit definition for RCC_APB2ENR register  ******************/
#define  RCC_APB2ENR_SYSCFGEN                ((UINT32)0x00000001)        /*!< SYSCFG clock enable */
#define  RCC_APB2ENR_TIM1EN                  ((UINT32)0x00000800)        /*!< TIM1 clock enable */
#define  RCC_APB2ENR_SPI1EN                  ((UINT32)0x00001000)        /*!< SPI1 clock enable */
#define  RCC_APB2ENR_TIM8EN                  ((UINT32)0x00002000)        /*!< TIM8 clock enable */ 
#define  RCC_APB2ENR_USART1EN                ((UINT32)0x00004000)        /*!< USART1 clock enable */
#define  RCC_APB2ENR_SPI4EN                  ((UINT32)0x00008000)        /*!< SPI4 clock enable */
#define  RCC_APB2ENR_TIM15EN                 ((UINT32)0x00010000)        /*!< TIM15 clock enable */
#define  RCC_APB2ENR_TIM16EN                 ((UINT32)0x00020000)        /*!< TIM16 clock enable */
#define  RCC_APB2ENR_TIM17EN                 ((UINT32)0x00040000)        /*!< TIM17 clock enable */
#define  RCC_APB2ENR_TIM20EN                 ((UINT32)0x00100000)        /*!< TIM20 clock enable */
#define  RCC_APB2ENR_HRTIM1                  ((UINT32)0x20000000)        /*!< HRTIM1 clock enable */


/** PLL时钟源定义 */
typedef enum PllClkSourceType
{
//	#ifdef STM32F303xDE
//	PLL_SOURCE_HSI_PRESC_2 = 0,
//	PLL_SOURCE_HSI,
//	PLL_SOURCE_HSE
//	#else
	PLL_SOURCE_HSI_PRESC_2 = 0,
	PLL_SOURCE_HSE_PREDIV
//	#endif
}enumPllClkSourceType;

/** SYSTEM时钟源定义 */
typedef enum SystemSourceType
{
	SYSTEM_SOURCE_HSI = 0,
	SYSTEM_SOURCE_HSE,
	SYSTEM_SOURCE_PLL
}enumSystemSourceType;

/** AHB总线分频系数定义 */
typedef enum AhbPrescType
{
	AHB_PRESC_1 = 0x07,					/**< AHB总线上时钟来自系统时钟1分频 */
	AHB_PRESC_2,						/**< AHB总线上时钟来自系统时钟2分频 */
	AHB_PRESC_4,						/**< AHB总线上时钟来自系统时钟4分频 */
	AHB_PRESC_8,						/**< AHB总线上时钟来自系统时钟8分频 */
	AHB_PRESC_16,						/**< AHB总线上时钟来自系统时钟16分频 */
	AHB_PRESC_64,						/**< AHB总线上时钟来自系统时钟64分频 */
	AHB_PRESC_128,						/**< AHB总线上时钟来自系统时钟128分频 */
	AHB_PRESC_256,						/**< AHB总线上时钟来自系统时钟256分频 */
	AHB_PRESC_512 						/**< AHB总线上时钟来自系统时钟512分频 */	
}enumAhbPrescType;

/** APB1总线分频系数定义 */
typedef enum Apb1PrescType
{
	APB1_PRESC_1 = 0x03,				/**< APB1总线上时钟来AHB时钟1分频 */
	APB1_PRESC_2,						/**< APB1总线上时钟来AHB时钟2分频 */
	APB1_PRESC_4,						/**< APB1总线上时钟来AHB时钟4分频 */
	APB1_PRESC_8,						/**< APB1总线上时钟来AHB时钟8分频 */
	APB1_PRESC_16 						/**< APB1总线上时钟来AHB时钟16分频 */
}enumApb1PrescType;

/** APB2总线分频系数定义 */
typedef enum Apb2PrescType
{
	APB2_PRESC_1 = 0x03,				/**< APB2总线上时钟来AHB时钟1分频 */
	APB2_PRESC_2,						/**< APB2总线上时钟来AHB时钟2分频 */
	APB2_PRESC_4,						/**< APB2总线上时钟来AHB时钟4分频 */
	APB2_PRESC_8,						/**< APB2总线上时钟来AHB时钟8分频 */
	APB2_PRESC_16 						/**< APB2总线上时钟来AHB时钟16分频 */
}enumApb2PrescType;

/** ADC分频系数定义 */
typedef enum AdcPrescType
{
	ADC_CLK_PLL_DIV_NONE = 15,			/**< ADC不是能PLL时钟，使用AHB时钟 */
	ADC_CLK_PLL_DIV_1,					/**< ADC不是能PLL时钟1分频 */
	ADC_CLK_PLL_DIV_2,					/**< ADC不是能PLL时钟2分频 */
	ADC_CLK_PLL_DIV_4,					/**< ADC不是能PLL时钟4分频 */
	ADC_CLK_PLL_DIV_6,					/**< ADC不是能PLL时钟6分频 */
	ADC_CLK_PLL_DIV_8,					/**< ADC不是能PLL时钟8分频 */
	ADC_CLK_PLL_DIV_10,					/**< ADC不是能PLL时钟10分频 */
	ADC_CLK_PLL_DIV_12,					/**< ADC不是能PLL时钟12分频 */
	ADC_CLK_PLL_DIV_16,					/**< ADC不是能PLL时钟16分频 */
	ADC_CLK_PLL_DIV_32,					/**< ADC不是能PLL时钟32分频 */
	ADC_CLK_PLL_DIV_64,					/**< ADC不是能PLL时钟64分频 */
	ADC_CLK_PLL_DIV_128,				/**< ADC不是能PLL时钟128分频 */
	ADC_CLK_PLL_DIV_256					/**< ADC不是能PLL时钟256分频 */
}enumAdcPrescType;

/** 时钟频率 */
typedef struct ClockFreqType
{
	UINT32 XtalFreq;                                /**< 晶振频率 */
	UINT32 CoreFreq;								/**< 内核频率 */
	UINT32 AhbFreq;									/**< AHB总线频率 */
	UINT32 Apb1Freq;								/**< APB1总线频率 */
	UINT32 Apb2Freq;								/**< APB2总线频率 */
	UINT32 Apb1TimerClkFreq;						/**< APB1总线上定时器频率 */
	UINT32 Apb2TimerClkFreq;						/**< APB2总线上定时器频率 */
	UINT32 Adc12Freq;								/**< ADC1和ADC2时钟频率 */
    UINT32 Adc34Freq;								/**< ADC3和ADC4时钟频率 */
}structClockFreqType;

extern structClockFreqType g_ClockFrequency;


extern UINT8 drv_rcc_init( UINT8 HseBypass, UINT16 XtalFreq, UINT16 CoreFreq, enumApb1PrescType Apb1Div, enumApb2PrescType Apb2Div, UINT32 VectStartAddress );
extern void drv_rcc_get_clocks_freq( structClockFreqType *pClockFreq );
extern void drv_rcc_ahb1_clk_enable( UINT32 RccAhbPeriph );
extern void drv_rcc_ahb1_clk_disable( UINT32 RccAhbPeriph );
extern void drv_rcc_apb1_clk_enable( UINT32 RccApb1Periph );
extern void drv_rcc_apb1_clk_disable( UINT32 RccApb1Periph );
extern void drv_rcc_apb2_clk_enable( UINT32 RccApb2Periph );
extern void drv_rcc_apb2_clk_disable( UINT32 RccApb2Periph );
extern void drv_rcc_ahb_periph_reset_enable( UINT32 RccAhbPeriph );
extern void drv_rcc_ahb_periph_reset_disable( UINT32 RccAhbPeriph );
extern void drv_rcc_apb1_periph_reset_enable( UINT32 RccApb1Periph );
extern void drv_rcc_apb1_periph_reset_disable( UINT32 RccApb1Periph );
extern void drv_rcc_apb2_periph_reset_enable( UINT32 RccApb2Periph );
extern void drv_rcc_apb2_periph_reset_disable( UINT32 RccApb2Periph );
extern void drv_rcc_adc12_presc( enumAdcPrescType AdcPresc );
extern void drv_rcc_adc34_presc( enumAdcPrescType AdcPresc );

#endif
