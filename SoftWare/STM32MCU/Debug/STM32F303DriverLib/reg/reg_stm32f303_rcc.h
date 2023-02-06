/**
  *******************************************************************
  * @file    reg_stm32f303_rcc.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-18
  * @brief   STM32F303	RCC寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#ifndef __REG_STM32F303_RCC_H__
#define __REG_STM32F303_RCC_H__


#include "reg_stm32f303_address.h"


/** RCC时钟控制寄存器位定义 */
typedef struct
{
	UINT32  HSION   : 1;			          /**< Bit0,内部高速时钟使能，1表示HSI 振荡器打开 */
	UINT32  HSIRDY  : 1;				      /**< Bit1, 内部高速时钟就绪标志，1表示HSI 振荡器已就绪 */
	UINT32  Rsvd1   : 1;				      /**< Bit2, 保留 */
	UINT32  HSITRIM : 5;			          /**< Bit3~7, 内部高速时钟微调 */
	UINT32  HSICAL  : 8;					  /**< Bit8~15, 内部高速时钟校准 */
	UINT32  HSEON   : 1;				      /**< Bit16, HSE 时钟使能，1表示HSE 振荡器打开 */
	UINT32  HSERDY  : 1;				      /**< Bit17, HSE 时钟就绪标志,1表示HSE 振荡器已就绪 */
	UINT32  HSEBYP  : 1;				      /**< Bit18, HSE 时钟旁路,1表示外部时钟旁路 HSE 振荡器 */
	UINT32  CSSON   : 1;				      /**< Bit19, 时钟安全系统使能,1表示时钟安全系统打开 */
	UINT32  Rsvd2   : 4;				      /**< Bit20~23, 保留 */
	UINT32  PLLON   : 1;				      /**< Bit24, 主 PLL (PLL) 使能,1表示PLL 开启 */
	UINT32  PLLRDY  : 1;				      /**< Bit25,主 PLL (PLL) 时钟就绪标志,1表示PLL 已锁定  */
	UINT32  Rsvd3   : 6;				      /**< Bit28~31, 保留 */
}RccCrBitType;

/** RCC时钟控制寄存器定义 */
typedef union
{
	UINT32  all;						  	/**< RCC状态寄存器所有位 */
	RccCrBitType  bit;			  			/**< RCC状态寄存器位定义 */
}RccCrType;

/** RCC 时钟配置寄存器位定义 */
typedef struct
{
	UINT32  SW   			: 2;	/**< Bit0~1,系统时钟切换 */
	UINT32  SWS  			: 2;	/**< Bit2~3, 系统时钟切换状态 */
	UINT32  HPRE 			: 4;	/**< Bit4~7, AHB 预分频器 */
	UINT32  PPRE1			: 3;	/**< Bit8~10, 低速APB(APB1) 时钟预分频器 */
	UINT32  PPRE2			: 3;	/**< Bit11~13, 高速APB(APB2) 高速预分频器 */
	UINT32	Rsvd1			: 1;	/**< Bit14,保留 */
#ifdef STM32F303XDE
	UINT32	PLLSRC			: 2;	/**< Bit15~16,进入PLL时钟源， 1：HSE/PREDIV设置作为PLL输入时钟*/
#else
	UINT32	Rsvd4			: 1;	/**< Bit15 */
	UINT32	PLLSRC			: 1;	/**< Bit16,进入PLL时钟源， 1：HSE/PREDIV设置作为PLL输入时钟*/
#endif
    UINT32	PLLXTPRE		: 1;	/**< Bit17,HSE分频后作为PLL输入时钟 */
	UINT32	PLLMUL			: 4;	/**< Bit18~21,PLL倍频系数 */
	UINT32	USBPRE			: 1;	/**< Bit22,USB分频 */
	UINT32	I2SSRC			: 1;	/**< Bit23,I2S外设时钟源选择 */
	UINT32	MCO				: 3;	/**< Bit24~26,单片机时钟输出 */
	UINT32	Rsvd5			: 1;	/**< Bit7,保留 */
	UINT32	MCOF			: 1;	/**< Bit28,单片机时钟输出标志 */
	UINT32	MCOPRE			: 2;	/**< Bit29~30,单片机时钟输出分频 */
	UINT32	PLLNODIV		: 1;	/**< Bit32,PLL不分频连接到MCO */
}RccCfgrBitType;	

/** RCC 时钟配置寄存器定义 */
typedef union
{
	RccCfgrBitType  bit;			    /**< RCC 时钟配置寄存器位定义 */
	UINT32  all;						    /**< RCC 时钟配置寄存器所有位 */
}RccCfgrType;

/** RCC 时钟中断寄存器位定义 */
typedef struct
{
	UINT32  LSIRDYF     : 1;			    /**< Bit0,LSI 就绪中断标志，1表示因 LSI 振荡器引起时钟就绪中断 */
	UINT32  LSERDYF     : 1;			    /**< Bit1,LSE 就绪中断标志，1表示因 LSE 振荡器引起时钟就绪中断 */
	UINT32  HSIRDYF     : 1;			    /**< Bit2,HSI 就绪中断标志，1表示因 HSI 振荡器引起时钟就绪中断 */
	UINT32  HSERDYF     : 1;			    /**< Bit3,HSE 就绪中断标志，1表示因 HSE 振荡器引起时钟就绪中断 */
	UINT32  PLLRDYF     : 1;				/**< Bit4,主 PLL (PLL) 就绪中断标志，1表示因 PLL 锁定而引起时钟就绪中断 */
	UINT32  Rsvd1       : 2;		        /**< Bit6, 保留 */
	UINT32  CSSF        : 1;				/**< Bit7,时钟安全系统中断标志，1表示因 HSE 时钟故障而引起时钟安全中断 */
	UINT32  LSIRDYIE    : 1;	            /**< Bit8,LSI 就绪中断使能，1表示使能 LSI 就绪中断 */
	UINT32  LSERDYIE    : 1;				/**< Bit9,LSE 就绪中断使能，1表示使能 LSE 就绪中断 */
	UINT32  HSIRDYIE    : 1;				/**< Bit10,HSI 就绪中断使能，1表示使能 HSI 就绪中断 */
	UINT32  HSERDYIE    : 1;			    /**< Bit11, HSE 就绪中断使能，1表示使能 HSE 就绪中断 */
	UINT32  PLLRDYIE    : 1;			    /**< Bit12, 主 PLL (PLL) 就绪中断使能，1表示使能 PLL 锁定中断 */
	UINT32  Rsvd2       : 3;		        /**< Bit14~15, 保留 */
	UINT32  LSIRDYC     : 1;				/**< Bit16,LSI 就绪中断清零，1表示清零 LSIRDYF */
	UINT32  LSERDYC     : 1;				/**< Bit17,LSE 就绪中断清零，1表示清零 LSERDYF */
	UINT32  HSIRDYC     : 1;				/**< Bit18,HSI 就绪中断清零，1表示清零 HSIRDYF */
	UINT32  HSERDYC     : 1;				/**< Bit19,HSE 就绪中断清零，1表示清零 HSERDYF */
	UINT32  PLLRDYC     : 1;				/**< Bit20,LSI 主 PLL(PLL) 就绪中断清零，1表示清零 PLLRDYF */
	UINT32  Rsvd3       : 2;				/**< Bit22,保留 */
	UINT32  CSSC        : 1;				/**< Bit23,时钟安全系统中断清零，1表示将 CSSF 标志清零 */
	UINT32  Rsvd4       : 8;				/**< Bit24~31,保留 */
}RccCirBitType;


/** RCC 时钟中断寄存器定义 */
typedef union
{
	RccCirBitType  bit;		    /**< RCC 时钟中断寄存器位定义 */
	UINT32  all;					        /**< RCC 时钟中断寄存器所有位 */
}RccCirType;

/** APB2 外设复位寄存器 */
typedef struct
{
	UINT32		SYSCFGRST	: 1;	/**< BIT0,SYSCFG , COMP , OPAMP复位 */
	UINT32		Rsvd1		: 10;	/**< BIT1~10, 保留 */
	UINT32		TIMRST		: 1;	/**< BIT11，定时器1复位 */
	UINT32		SPI1RST		: 1;	/**< BIT12，SPI1复位 */
	UINT32		TIM8RST		: 1;	/**< BIT13，定时器8复位 */
	UINT32		USART1RST	: 1;	/**< BIT14，串口1复位 */
	UINT32		SPI4RST		: 1;	/**< BIT15，SPI4复位 */
	UINT32		TIM15RST	: 1;	/**< BIT16，定时器15复位 */
	UINT32		TIM16RST	: 1;	/**< BIT17，定时器16复位 */
	UINT32		TIM18RST	: 1;	/**< BIT18，定时器17复位 */
	UINT32		Rsvd4		: 1;	/**< BIT19，保留 */
	UINT32		TIM20RST	: 1;	/**< BIT20，定时器20复位 */
	UINT32		Rsvd3		: 11;	/**< BIT21~31，保留 */
	
}RccApb2rstrBitType;

typedef union
{
	UINT32	all;
	RccApb2rstrBitType	bit;
}RccApb2rstrType;

/** RCC APB1 外设复位寄存器位定义 */
typedef struct
{
	UINT32  TIM2RST      : 1;			    /**< Bit0,TIM2 复位，1表示复位 TIM2 */
	UINT32  TIM3RST      : 1;			    /**< Bit1,TIM3 复位，1表示复位 TIM3 */
	UINT32  TIM4RST      : 1;			    /**< Bit2,TIM4 复位，1表示复位 TIM4 */
	UINT32  Rsvd2        : 1;			    /**< BIT3，保留 */
	UINT32  TIM6RST      : 1;			    /**< Bit4,TIM6 复位，1表示复位 TIM6 */
	UINT32  TIM7RST      : 1;			    /**< Bit5,TIM7 复位，1表示复位 TIM7 */
	UINT32	Rsvd3		 : 5;				/**< Bit6~10,保留 */
	UINT32  WWDGRST      : 1;				/**< Bit11,窗口看门狗复位，1表示复位窗口看门狗 */
	UINT32  Rsvd4        : 2;				/**< Bit12~13,保留 */
	UINT32  SPI2RST      : 1;			    /**< Bit14, SPI2 复位，1表示复位 SPI2 */
	UINT32  SPI3RST      : 1;			    /**< Bit15, SPI3 复位，1表示复位 SPI3 */
	UINT32  Rsvd5        : 1;			    /**< Bit16, 保留 */
	UINT32  USART2RST    : 1;		        /**< Bit17, USART2 复位,1表示USART2 复位 */
	UINT32  USART3RST    : 1;				/**< Bit18, USART3 复位,1表示USART3 复位 */
	UINT32  UART4RST     : 1;				/**< Bit19,UART4 复位，1表示UART4 复位 */
	UINT32  UART5RST     : 1;			    /**< Bit20,UART5 复位，1表示UART5 复位 */
	UINT32  I2C1RST      : 1;			    /**< Bit21,I2C1 复位，1表示I2C1 复位 */
	UINT32  I2C2RST      : 1;			    /**< Bit22,I2C2 复位，1表示I2C2 复位 */
	UINT32  USBRST       : 1;			    /**< Bit23,USB 复位，1表示USB 复位 */
	UINT32  Rsvd8        : 1;			    /**< Bit24,保留 */
	UINT32  CAN1RST      : 1;			    /**< Bit25,CAN1 复位，1表示CAN1 复位 */
	UINT32  DAC2RST      : 1;			    /**< Bit26,DAC2 复位，1表示DAC2 复位 */
	UINT32  Rsvd10       : 1;			    /**< Bit27,保留 */
	UINT32  PWRRST       : 1;			    /**< Bit28,电源接口复位，1表示电源接口复位 */
	UINT32  DAC1RST      : 1;			    /**< Bit29,复位 DAC1 接口，1表示复位 DAC 接口 */
	UINT32	I2CRST		 : 1;				/**< BIT30，I2C3 复位，1表示复位I2C3 */
	UINT32  Rsvd12       : 1;			    /**< Bit31,保留 */

}RccApb1rstrBitType;

/** RCC APB1 外设复位寄存器定义*/
typedef union
{
	RccApb1rstrBitType  bit;			    /**< RCC APB1 外设复位寄存器位定义 */
	UINT32  all;					        /**< RCC APB1 外设复位寄存器定义所有位 */
}RccApb1rstrType;

/** RCC AHB 外设时钟使能寄存器位定义 */
typedef struct
{
	UINT32	DMA1EN	: 1;
	UINT32	DMA2EN	: 1;
	UINT32	SRAMEN	: 1;
	UINT32	Rsvd1	: 1;
	UINT32	FLITFEN	: 1;
	UINT32	FMCEN	: 1;
	UINT32	CRCEN	: 1;
	UINT32	Rsvd2	: 9;
	UINT32	IOPHEN	: 1;
	UINT32	IOPAEN	: 1;
	UINT32	IOPBEN	: 1;
	UINT32	IOPCEN	: 1;
	UINT32	IOPDEN	: 1;
	UINT32	IOPEEN	: 1;
	UINT32	IOPFEN	: 1;
	UINT32	IOPGEN	: 1;
	UINT32	TSCEN	: 1;
	UINT32	Rsvd3	: 3;
	UINT32	ADC12EN	: 1;
	UINT32	ADC34EN	: 1;
	UINT32	Rsvd4	: 2;
}RccAhbenrBitType;

/** RCC AHB 外设时钟使能寄存器定义 */
typedef union
{
	UINT32	all;
	RccAhbenrBitType	bit;
}RccAhbenrType;

/** RCC APB2 外设时钟使能寄存器位定义 */
typedef struct
{
	UINT32	SYSCFGEN	: 1;
	UINT32	Rsvd1		: 10;
	UINT32	TIM1EN		: 1;
	UINT32	SPI1EN		: 1;
	UINT32	TIM8EN		: 1;
	UINT32	USART1EN	: 1;
	UINT32	SPI4EN		: 1;
	UINT32	TIM15EN		: 1;
	UINT32	TIM16EN		: 1;
	UINT32	TIM17EN		: 1;
	UINT32	Rsvd2		: 1;
	UINT32	TIM20EN		: 1;
	UINT32	Rsvd3		: 11;
	
}RccApb2enrBitType;

/** RCC APB2 外设时钟使能寄存器定义 */
typedef union
{
	UINT32	all;
	RccApb2enrBitType	bit;
}RccApb2enrType;

/** RCC APB1 外设时钟使能寄存器位定义 */
typedef struct
{
	UINT32  TIM2EN     : 1;			        /**< Bit0,TIM2 时钟使能，1表示TIM2 时钟使能 */
	UINT32  TIM3EN     : 1;			        /**< Bit1,TIM3 时钟使能，1表示TIM3 时钟使能 */
	UINT32  TIM4EN     : 1;			        /**< Bit2,TIM4 时钟使能，1表示TIM4 时钟使能 */
	UINT32  Rsvd1	   : 1;
	UINT32  TIM6EN     : 1;			        /**< Bit4,TIM6 时钟使能，1表示TIM6 时钟使能 */
	UINT32  TIM7EN     : 1;			        /**< Bit5,TIM7 时钟使能，1表示TIM7 时钟使能 */	
	UINT32  Rsvd2      : 5;	                /**< Bit9~10,保留 */
	UINT32  WWDGEN     : 1;				    /**< Bit11,窗口看门狗时钟使能，1表示窗口看门狗时钟使能 */
	UINT32  Rsvd3      : 2;				    /**< Bit12~13,保留 */
	UINT32  SPI2EN     : 1;			        /**< Bit14, SPI2 时钟使能，1表示SPI2 时钟使能 */
	UINT32  SPI3EN     : 1;			        /**< Bit15, SPI3 时钟使能，1表示SPI3 时钟使能 */
	UINT32  Rsvd4      : 1;			        /**< Bit16, 保留 */
	UINT32  USART2EN   : 1;		            /**< Bit17, USART2 时钟使能,1表示USART2 时钟使能 */
	UINT32  USART3EN   : 1;				    /**< Bit18, USART3 时钟使能,1表示USART3 时钟使能 */
	UINT32  UART4EN    : 1;				    /**< Bit19,UART4 时钟使能，1表示UART4 时钟使能 */
	UINT32  UART5EN    : 1;			        /**< Bit20,UART5 时钟使能，1表示UART5 时钟使能 */	
	UINT32  I2C1EN     : 1;			        /**< Bit21,I2C1 时钟使能，1表示I2C1 时钟使能 */
	UINT32  I2C2EN     : 1;			        /**< Bit22,I2C2 时钟使能，1表示I2C2 时钟使能 */
	UINT32  USBEN      : 1;			        /**< Bit23,USB 时钟使能，1表示USB 时钟使能 */
	UINT32  Rsvd5      : 1;			        /**< Bit24, 保留 */
	UINT32  CANEN      : 1;			        /**< Bit25,CAN 时钟使能，1表示CAN时钟使能 */
	UINT32  DAC2EN     : 1;			        /**< Bit26,DAC2 时钟使能，1表示DAC2时钟使能 */
	UINT32  Rsvd6      : 1;			        /**< Bit27, 保留 */
	UINT32  PWREN      : 1;			        /**< Bit28,电源接口时钟使能，1表示电源接口时钟使能 */
	UINT32  DAC1EN     : 1;			    /**< Bit29,DAC1 接口时钟使能能，1表示DAC1 接口时钟使能 */
	UINT32	I2C3EN	   : 1;					/**< BIT30, I2C3时钟使能，1表示I2C3时钟使能 */
	UINT32  Rsvd7      : 1;			        /**< Bit31, 保留 */
}RccApb1enrBitType;

/** RCC APB1 外设时钟使能寄存器定义 */
typedef union
{
	RccApb1enrBitType  bit;			    /**< RCC APB1 外设时钟使能寄存器位定义 */
	UINT32  all;					        /**< RCC APB1 外设时钟使能寄存器定义所有位 */
}RccApb1enrType;

/** RTC 域控制寄存器位定义 */
typedef struct
{
	UINT32  LSEON          : 1;			    /**< Bit0,外部低速振荡器使能，1表示外部低速振荡器使能 */
	UINT32  LSERDY         : 1;			    /**< Bit1,外部低速振荡器就绪，1表示外部低速振荡器就绪 */	
	UINT32  LSEBYP         : 1;			    /**< Bit2,外部低速振荡器旁路，1表示旁路 LSE 振荡器 */
	UINT32  LSEDRV         : 2;			    /**< Bit3~4,LSE振荡器驱动能力 */
	UINT32	Rsvd1		   : 3;
	UINT32  RTCSEL         : 2;			    /**< Bit8~9,RTC 时钟源选择，00：无时钟,01：LSE 振荡器时钟用作 RTC 时钟,10：LSI 振荡器时钟用作 RTC 时钟,11：由可编程预分频器分频的 HSE 振荡器时钟 */
	UINT32  Rsvd2          : 5;				/**< Bit10~14,保留 */
	UINT32  RTCEN          : 1;				/**< Bit15,RTC 时钟使能,1表示RTC 时钟使能 */
	UINT32  BDRST          : 1;			    /**< Bit16, 备份域软件复位，1表示复位整个备份域 */
	UINT32  Rsvd3          : 15;			/**< Bit17~31, 保留 */	
}RccBdcrBitType;

/** RTC 域控制寄存器定义 */
typedef union
{
	RccBdcrBitType  bit;			        /**< RCC 备份域控制寄存器位定义 */
	UINT32  all;					        /**< RCC 备份域控制寄存器定义所有位 */
}RccBdcrType;

/** RCC 控制和状态寄存器位定义 */
typedef struct
{
	UINT32  LSION          : 1;			    /**< Bit0,内部低速振荡器使能，1表示内部低速振荡器使能 */
	UINT32  LSIRDY         : 1;			    /**< Bit1,内部低速振荡器就绪，1表示LSI RC 振荡器就绪 */
	UINT32  Rsvd1          : 21;		    /**< Bit2~22,保留 */
	UINT32  VREGRSTF       : 1;			    /**< Bit23,电压调整复位标志，1表示电压调整复位发生 */
	UINT32	RMVF		   : 1;				/**< Bit24，移除复位标志 */
	UINT32  OBLRSTF        : 1;			    /**< Bit25,选项字节载入复位标志，1表示从OBL发生复位 */
	UINT32  PINRSTF        : 1;			    /**< Bit26,引脚复位标志，1表示发生来自 NRST 引脚的复位 */
	UINT32  PORRSTF        : 1;			    /**< Bit27,POR/PDR 复位标志,1表示发生 POR/PDR 复位 */
	UINT32  SFTRSTF        : 1;			    /**< Bit28,软件复位标志，1表示发生软件复位 */	
	UINT32  IWDGRSTF       : 1;			    /**< Bit29,独立看门狗复位标志，1表示发生看门狗复位 */	
	UINT32  WWDGRSTF       : 1;	            /**< Bit30,窗口看门狗复位标志 ,1表示发生窗口看门狗复位 */
	UINT32  LPWRRSTF       : 1;				/**< Bit31,低功耗复位标志,1表示发生低功耗管理复位 */
}RccCsrBitType;

/** RCC 控制和状态寄存器定义 */
typedef union
{
	RccCsrBitType  bit;			        /**< RCC 时钟控制和状态寄存器位定义 */
	UINT32  all;					    /**< RCC 时钟控制和状态寄存器定义所有位 */
}RccCsrType;

/** AHB外设复位寄存器位定义 */
typedef struct
{
	UINT32	Rsvd1		: 5;	
	UINT32	FMCRST		: 1;
	UINT32	Rsvd2		: 10;
	UINT32	IOPHRST 	: 1;
	UINT32	IOPARST		: 1;
	UINT32	IOPBRST		: 1;
	UINT32	IOPCRST		: 1;
	UINT32	IOPDRST		: 1;
	UINT32	IOPERST		: 1;
	UINT32	IOPFRST		: 1;
	UINT32	IOPGRST		: 1;
	UINT32	TSCRST		: 1;
	UINT32	Rsvd3		: 3;
	UINT32	ADC12RST	: 1;
	UINT32	ADC34RST	: 1;
	UINT32	Rsvd4		: 2;
}RccAhbrstrBitType;

/** AHB外设复位寄存器 */
typedef union
{
	UINT32	all;
	RccAhbrstrBitType	bit;
}RccAhbrstrType;

/** 时钟配置寄存器2位定义 */
typedef struct
{
	UINT32 	PREDIV		: 4;
	UINT32	ADC12PRES	: 5;
	UINT32	ADC34PRES	: 5;
	UINT32	Rsvd1		: 18;
}RccCfgr2BitType;

/** 时钟配置寄存器2定义 */
typedef union
{
	UINT32	all;
	RccCfgr2BitType		bit;
}RccCfgr2Type;

/** 时钟配置寄存器3位定义 */
typedef struct
{
	UINT32 	USART1SW		: 2;
	UINT32	Rsvd1			: 2;
	UINT32	I2C1SW			: 1;
	UINT32	I2C2SW			: 1;
	UINT32	I2C3SW			: 1;
	UINT32	Rsvd2			: 1;
	UINT32	TIM1SW			: 1;
	UINT32	TIM8SW			: 1;
	UINT32	TIM15SW			: 1;
	UINT32	TIM16SW			: 1;
	UINT32	Rsvd3			: 1;
	UINT32	TIM17SW			: 1;
	UINT32	Rsvd4			: 1;
	UINT32	TIM20SW			: 1;
	UINT32	USART2SW		: 2;
	UINT32	USART3SW		: 2;
	UINT32	UART4SW			: 2;
	UINT32	UART5SW			: 2;
	UINT32	TIM2SW			: 1;
	UINT32	TIM34SW			: 1;
	UINT32	Rsvd5			: 6;
}RccCfgr3BitType;

/** 时钟配置寄存器3定义 */
typedef struct
{
	UINT32	all;
	RccCfgr3BitType		bit;
}RccCfgr3Type;

/** RCC寄存器 */
typedef struct
{
	RccCrType			CR;
	RccCfgrType			CFGR;
	RccCirType			CIR;
	RccApb2rstrType		APB2RSTR;
	RccApb1rstrType		APB1RSTR;
	RccAhbenrType		AHBENR;
	RccApb2enrType		APB2ENR;
	RccApb1enrType		APB1ENR;
	RccBdcrType			BDCR;
	RccCsrType			CSR;
	RccAhbrstrType		AHBRSTR;
	RccCfgr2Type		CFGR2;
	RccCfgr3Type		CFGR3;
}RccType;



/** RCC寄存器地址 */
#define	RCC		((RccType *) RCC_BASE)




#endif
