/**
  *******************************************************************
  * @file    reg_stm32f303_gpio.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    2016-03-18
  * @brief   STM32F303 GPIO寄存器定义头文件
  *******************************************************************
  * @attention
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */

#ifndef __REG_STM32F303_GPIO_H__
#define __REG_STM32F303_GPIO_H__

#include "typedefine.h"
#include "reg_stm32f303_address.h"


/** GPIO口模式寄存器位定义 */
typedef struct
{
	UINT32 MODER0 : 2;							/**< Bit0:1, 	第0位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER1 : 2;							/**< Bit2:3, 	第1位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER2 : 2;							/**< Bit4:5, 	第2位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER3 : 2;							/**< Bit6:7, 	第3位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER4 : 2;							/**< Bit8:9, 	第4位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER5 : 2;							/**< Bit10:11,	第5位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER6 : 2;							/**< Bit12:13,	第6位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER7 : 2;							/**< Bit14:15,	第7位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER8 : 2;							/**< Bit16:17,	第8位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER9 : 2;							/**< Bit18:19,	第9位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER10 : 2;							/**< Bit20:21,	第10位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER11 : 2;							/**< Bit22:23,	第11位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER12 : 2;							/**< Bit24:25, 	第12位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER13 : 2;							/**< Bit26:27,	第13位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER14 : 2;							/**< Bit28:29,	第14位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
	UINT32 MODER15 : 2;							/**< Bit30:31,	第15位模式,00:输入，01：通用输出，10：复用功能，11：模拟模式 */
}GpioModerBitType;

/** GPIO口模式寄存器定义 */
typedef union
{
	UINT32 all;									/**< GPIO口模式寄存器所有位 */
	GpioModerBitType bit;						/**< GPIO口模式寄存器位定义 */
}GpioModerType;

/** GPIO口输出类型寄存器位定义 */
typedef struct
{
	UINT32 OT0 : 1;							/**< Bit0:1,	第0位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT1 : 1;							/**< Bit1:1,	第1位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT2 : 1;							/**< Bit2:1,	第2位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT3 : 1;							/**< Bit3:1,	第3位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT4 : 1;							/**< Bit4:1,	第4位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT5 : 1;							/**< Bit5:1,	第5位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT6 : 1;							/**< Bit6:1,	第6位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT7 : 1;							/**< Bit7:1,	第7位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT8 : 1;							/**< Bit8:1,	第8位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT9 : 1;							/**< Bit9:1,	第9位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT10 : 1;						/**< Bit10:1,	第10位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT11 : 1;						/**< Bit11:1,	第11位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT12 : 1;						/**< Bit12:1,	第12位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT13 : 1;						/**< Bit13:1,	第13位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT14 : 1;						/**< Bit14:1,	第14位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 OT15 : 1;						/**< Bit15:1,	第15位输出类型,0:输出推挽，1：输出开漏 */
	UINT32 Rsvd : 16;						/**< Bit16~31:16,第16~31位保留 */
}GpioOtyperBitType;

/** GPIO口输出类型寄存器定义 */
typedef union
{
	UINT32 all;									/**< GPIO口输出类型寄存器所有位 */
	GpioOtyperBitType bit;						/**< GPIO口输出类型寄存器位定义 */
}GpioOtyperType;

/** GPIO口输出速度寄存器位定义 */
typedef struct
{
	UINT32 OSPEEDR0 : 2;						/**< Bit0:1,	第0位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR1 : 2;						/**< Bit2:3,	第1位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR2 : 2;						/**< Bit4:5,	第2位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR3 : 2;						/**< Bit6:7,	第3位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR4 : 2;						/**< Bit8:9,	第4位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR5 : 2;						/**< Bit10:11,	第5位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR6 : 2;						/**< Bit12:13,	第6位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR7 : 2;						/**< Bit14:15,	第7位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR8 : 2;						/**< Bit16:17,	第8位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR9 : 2;						/**< Bit18:19,	第9位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR10 : 2;						/**< Bit20:21,	第10位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR11 : 2;						/**< Bit22:23,	第11位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR12 : 2;						/**< Bit24:25,	第12位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR13 : 2;						/**< Bit26:27,	第13位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR14 : 2;						/**< Bit28:29,	第14位输出速度,x0:低速,01:中速,11:高速 */
	UINT32 OSPEEDR15 : 2;						/**< Bit30:31,	第15位输出速度,x0:低速,01:中速,11:高速 */
}GpioOspeedrBitType;

/** GPIO口输出速度寄存器定义 */
typedef union
{
	UINT32 all;									/**< GPIO口输出速度寄存器所有位 */
	GpioOspeedrBitType bit;						/**< GPIO口输出速度寄存器位定义 */
}GpioOspeedrType;

/** GPIO上拉下拉寄存器位定义 */
typedef struct
{
	UINT32 PUPDR0 : 2;						/**< Bit0:1,	第0位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR1 : 2;						/**< Bit2:3,	第1位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR2 : 2;						/**< Bit4:5,	第2位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR3 : 2;						/**< Bit6:7,	第3位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR4 : 2;						/**< Bit8:9,	第4位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR5 : 2;						/**< Bit10:11,	第5位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR6 : 2;						/**< Bit12:13,	第6位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR7 : 2;						/**< Bit14:15,	第7位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR8 : 2;						/**< Bit16:17,	第8位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR9 : 2;						/**< Bit18:19,	第9位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR10 : 2;						/**< Bit20:21,	第10位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR11 : 2;						/**< Bit22:23,	第11位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR12 : 2;						/**< Bit24:25,	第12位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR13 : 2;						/**< Bit26:27,	第13位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR14 : 2;						/**< Bit28:29,	第14位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
	UINT32 PUPDR15 : 2;						/**< Bit30:31,	第15位上拉下拉,00:无上拉下拉，01:上拉，10:下拉，11:保留 */
}GpioPupdrBitType;

/** GPIO上拉下拉寄存器定义 */
typedef union
{
	UINT32 all;								/**< GPIO口上下拉寄存器所有位 */
	GpioPupdrBitType bit;					/**< GPIO口上下拉寄存器位定义 */
}GpioPupdrType;

/** GPIO输入数据寄存器位定义 */
typedef struct
{
	UINT32 IDR0 : 1;						/**< Bit0,		第0位输入数据 */
	UINT32 IDR1 : 1;						/**< Bit1,		第1位输入数据 */
	UINT32 IDR2 : 1;						/**< Bit2,		第2位输入数据 */
	UINT32 IDR3 : 1;						/**< Bit3,		第3位输入数据 */
	UINT32 IDR4 : 1;						/**< Bit4,		第4位输入数据 */
	UINT32 IDR5 : 1;						/**< Bit5,		第5位输入数据 */
	UINT32 IDR6 : 1;						/**< Bit6,		第6位输入数据 */
	UINT32 IDR7 : 1;						/**< Bit7,		第7位输入数据 */
	UINT32 IDR8 : 1;						/**< Bit8,		第8位输入数据 */
	UINT32 IDR9 : 1;						/**< Bit9,		第9位输入数据 */
	UINT32 IDR10 : 1;						/**< Bit10,		第10位输入数据 */
	UINT32 IDR11 : 1;						/**< Bit11,		第11位输入数据 */
	UINT32 IDR12 : 1;						/**< Bit12,		第12位输入数据 */
	UINT32 IDR13 : 1;						/**< Bit13,		第13位输入数据 */
	UINT32 IDR14 : 1;						/**< Bit14,		第14位输入数据 */
	UINT32 IDR15 : 1;						/**< Bit15,		第15位输入数据 */
	UINT32 Rsvd : 16;						/**< Bit16:31,	第16~31位保留 */
}GpioIdrBitType;

/** GPIO输入数据寄存器定义 */
typedef union
{
	UINT32 all;								/**< GPIO口输入寄存器所有位 */
	GpioIdrBitType bit;						/**< GPIO口输入寄存器位定义 */
}GpioIdrType;

/** GPIO输出数据寄存器位定义 */
typedef struct
{
	UINT32 ODR0 : 1;						/**< Bit0,		第0位输出数据 */
	UINT32 ODR1 : 1;						/**< Bit1,		第1位输出数据 */
	UINT32 ODR2 : 1;						/**< Bit2,		第2位输出数据 */
	UINT32 ODR3 : 1;						/**< Bit3,		第3位输出数据 */
	UINT32 ODR4 : 1;						/**< Bit4,		第4位输出数据 */
	UINT32 ODR5 : 1;						/**< Bit5,		第5位输出数据 */
	UINT32 ODR6 : 1;						/**< Bit6,		第6位输出数据 */
	UINT32 ODR7 : 1;						/**< Bit7,		第7位输出数据 */
	UINT32 ODR8 : 1;						/**< Bit8,		第8位输出数据 */
	UINT32 ODR9 : 1;						/**< Bit9,		第9位输出数据 */
	UINT32 ODR10 : 1;						/**< Bit10,		第10位输出数据 */
	UINT32 ODR11 : 1;						/**< Bit11,		第11位输出数据 */
	UINT32 ODR12 : 1;						/**< Bit12,		第12位输出数据 */
	UINT32 ODR13 : 1;						/**< Bit13,		第13位输出数据 */
	UINT32 ODR14 : 1;						/**< Bit14,		第14位输出数据 */
	UINT32 ODR15 : 1;						/**< Bit15,		第15位输出数据 */
	UINT32 Rsvd : 16;						/**< Bit16:31,	第16~31位保留 */
}GpioOdrBitType;

/** GPIO输入数据寄存器定义 */
typedef union
{
	UINT32 all;								/**< GPIO口输出寄存器所有位 */
	GpioOdrBitType bit;						/**< GPIO口输出寄存器位定义 */
}GpioOdrType;

/** GPIO置位寄存器位定义 */
typedef struct
{
	UINT16 BS0 : 1;						/**< Bit0,		第0位置位位，写1对相应IO口置位 */
	UINT16 BS1 : 1;						/**< Bit1,		第1位置位位，写1对相应IO口置位  */
	UINT16 BS2 : 1;						/**< Bit2,		第2位置位位，写1对相应IO口置位  */
	UINT16 BS3 : 1;						/**< Bit3,		第3位置位位，写1对相应IO口置位  */
	UINT16 BS4 : 1;						/**< Bit4,		第4位置位位，写1对相应IO口置位  */
	UINT16 BS5 : 1;						/**< Bit5,		第5位置位位，写1对相应IO口置位  */
	UINT16 BS6 : 1;						/**< Bit6,		第6位置位位，写1对相应IO口置位  */
	UINT16 BS7 : 1;						/**< Bit7,		第7位置位位，写1对相应IO口置位  */
	UINT16 BS8 : 1;						/**< Bit8,		第8位置位位，写1对相应IO口置位  */
	UINT16 BS9 : 1;						/**< Bit9,		第9位置位位，写1对相应IO口置位  */
	UINT16 BS10 : 1;					/**< Bit10,		第10位置位位，写1对相应IO口置位  */
	UINT16 BS11 : 1;					/**< Bit11,		第11位置位位，写1对相应IO口置位  */
	UINT16 BS12 : 1;					/**< Bit12,		第12位置位位，写1对相应IO口置位  */
	UINT16 BS13 : 1;					/**< Bit13,		第13位置位位，写1对相应IO口置位  */
	UINT16 BS14 : 1;					/**< Bit14,		第14位置位位，写1对相应IO口置位  */
	UINT16 BS15 : 1;					/**< Bit15,		第15位置位位，写1对相应IO口置位  */
}GpioBsrrlBitType;

/** GPIO复位寄存器位定义 */
typedef struct
{
	UINT16 BR0 : 1;						/**< Bit16,		第0位复位位，写1对相应IO口复位  */
	UINT16 BR1 : 1;						/**< Bit17,		第1位复位位，写1对相应IO口复位 */
	UINT16 BR2 : 1;						/**< Bit18,		第2位复位位，写1对相应IO口复位 */
	UINT16 BR3 : 1;						/**< Bit19,		第3位复位位，写1对相应IO口复位 */
	UINT16 BR4 : 1;						/**< Bit20,		第4位复位位，写1对相应IO口复位 */
	UINT16 BR5 : 1;						/**< Bit21,		第5位复位位，写1对相应IO口复位 */
	UINT16 BR6 : 1;						/**< Bit22,		第6位复位位，写1对相应IO口复位 */
	UINT16 BR7 : 1;						/**< Bit23,		第7位复位位，写1对相应IO口复位 */
	UINT16 BR8 : 1;						/**< Bit24,		第8位复位位，写1对相应IO口复位 */
	UINT16 BR9 : 1;						/**< Bit25,		第9位复位位，写1对相应IO口复位 */
	UINT16 BR10 : 1;					/**< Bit26,		第10位复位位，写1对相应IO口复位 */
	UINT16 BR11 : 1;					/**< Bit27,		第11位复位位，写1对相应IO口复位 */
	UINT16 BR12 : 1;					/**< Bit28,		第12位复位位，写1对相应IO口复位 */
	UINT16 BR13 : 1;					/**< Bit29,		第13位复位位，写1对相应IO口复位 */
	UINT16 BR14 : 1;					/**< Bit30,		第14位复位位，写1对相应IO口复位 */
	UINT16 BR15 : 1;					/**< Bit31,		第15位复位位，写1对相应IO口复位 */
}GpioBsrrhBitType;

/** GPIO置位复位寄存器定义 */
typedef union
{
	UINT16 all;							/**< GPIO口置位寄存器所有位 */
	GpioBsrrlBitType bit;				/**< GPIO口置位寄存器位定义 */
}GpioBsrrlType;

typedef union
{
	UINT16 all;							/**< GPIO口复位寄存器所有位 */
	GpioBsrrhBitType bit;				/**< GPIO口复位寄存器位定义 */
}GpioBsrrhType;

/** GPIO配置锁定寄存器位定义 */
typedef struct
{
	UINT32 LCK0 : 1;						/**< Bit0,		第0位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK1 : 1;						/**< Bit1,		第1位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK2 : 1;						/**< Bit2,		第2位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK3 : 1;						/**< Bit3,		第3位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK4 : 1;						/**< Bit4,		第4位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK5 : 1;						/**< Bit5,		第5位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK6 : 1;						/**< Bit6,		第6位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK7 : 1;						/**< Bit7,		第7位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK8 : 1;						/**< Bit8,		第8位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK9 : 1;						/**< Bit9,		第9位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK10 : 1;						/**< Bit10,		第10位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK11 : 1;						/**< Bit11,		第11位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK12 : 1;						/**< Bit12,		第12位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK13 : 1;						/**< Bit13,		第13位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK14 : 1;						/**< Bit14,		第14位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCK15 : 1;						/**< Bit15,		第15位锁定位，0:端口配置未锁定,1:端口配置已锁定 */
	UINT32 LCKK : 1;						/**< Bit16,		锁定键，0:端口配置锁定键未激活，1：端口配置锁定键激活 */
	UINT32 Rsvd : 15;						/**< Bit17:31,	保留 */
}GpioLckrBitType;

/** GPIO配置锁定寄存器定义 */
typedef union
{
	UINT32 all;								/**< GPIO口锁存寄存器所有位 */
	GpioLckrBitType bit;					/**< GPIO口锁存寄存器位定义 */
}GpioLckrType;

/** GPIO复用功能低位寄存器位定义 */
typedef struct
{
	UINT32 AFRL0 : 4;						/**< Bit0:3,	第0位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRL1 : 4;						/**< Bit4:7,	第1位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRL2 : 4;						/**< Bit8:11,	第2位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRL3 : 4;						/**< Bit12:15,	第3位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRL4 : 4;						/**< Bit16:19,	第4位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRL5 : 4;						/**< Bit20:23,	第5位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRL6 : 4;						/**< Bit24:27,	第6位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRL7 : 4;						/**< Bit28:31,	第7位的复用功能选择位，0000~1111:AF0~AF15 */
}GpioAfrlBitType;

/** GPIO复用功能低位寄存器定义 */
typedef union
{
	UINT32 all;								/**< GPIO口复用功能低位寄存器所有位 */
	GpioAfrlBitType bit;					/**< GPIO口复用功能低位寄存器位定义 */
}GpioAfrlType;

/** GPIO复用功能高位寄存器位定义 */
typedef struct
{
	UINT32 AFRH0 : 4;						/**< Bit0:3,	第8位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRH1 : 4;						/**< Bit4:7,	第9位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRH2 : 4;						/**< Bit8:11,	第10位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRH3 : 4;						/**< Bit12:15,	第11位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRH4 : 4;						/**< Bit16:19,	第12位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRH5 : 4;						/**< Bit20:23,	第13位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRH6 : 4;						/**< Bit24:27,	第14位的复用功能选择位，0000~1111:AF0~AF15 */
	UINT32 AFRH7 : 4;						/**< Bit28:31,	第15位的复用功能选择位，0000~1111:AF0~AF15 */
}GpioAfrhBitType;

/** GPIO复用功能高位寄存器定义 */
typedef union
{
	UINT32 all;								/**< GPIO口复用功能高位寄存器所有位 */
	GpioAfrhBitType bit;					/**< GPIO口复用功能高位寄存器位定义 */
}GpioAfrhType;

/** GPIO复位寄存器位定义 */
typedef struct
{
	UINT32 BR0 : 1;						/**< Bit0,		第0位复位位，写1对相应IO口复位  */
	UINT32 BR1 : 1;						/**< Bit1,		第1位复位位，写1对相应IO口复位 */
	UINT32 BR2 : 1;						/**< Bit2,		第2位复位位，写1对相应IO口复位 */
	UINT32 BR3 : 1;						/**< Bit3,		第3位复位位，写1对相应IO口复位 */
	UINT32 BR4 : 1;						/**< Bit4,		第4位复位位，写1对相应IO口复位 */
	UINT32 BR5 : 1;						/**< Bit5,		第5位复位位，写1对相应IO口复位 */
	UINT32 BR6 : 1;						/**< Bit6,		第6位复位位，写1对相应IO口复位 */
	UINT32 BR7 : 1;						/**< Bit7,		第7位复位位，写1对相应IO口复位 */
	UINT32 BR8 : 1;						/**< Bit8,		第8位复位位，写1对相应IO口复位 */
	UINT32 BR9 : 1;						/**< Bit9,		第9位复位位，写1对相应IO口复位 */
	UINT32 BR10 : 1;					/**< Bit10,		第10位复位位，写1对相应IO口复位 */
	UINT32 BR11 : 1;					/**< Bit11,		第11位复位位，写1对相应IO口复位 */
	UINT32 BR12 : 1;					/**< Bit12,		第12位复位位，写1对相应IO口复位 */
	UINT32 BR13 : 1;					/**< Bit13,		第13位复位位，写1对相应IO口复位 */
	UINT32 BR14 : 1;					/**< Bit14,		第14位复位位，写1对相应IO口复位 */
	UINT32 BR15 : 1;					/**< Bit15,		第15位复位位，写1对相应IO口复位 */
	UINT32 Rsvd	: 16;					/**< Bit 16~31， 保留 */
}GpioBrrBitType;

/** GPIO复位寄存器定义 */
typedef union
{
	UINT32	all;						/**< GPIO口置位寄存器所有位 */
	GpioBrrBitType	bit;				/**< GPIO口置位寄存器位定义 */
}GpioBrrType;

/** GPIO寄存器定义 */
typedef struct
{
	GpioModerType		MODER;						/**< GPIO模式寄存器,		偏移地址: 0x00 */
	GpioOtyperType		OTYPER;						/**< GPIO输出类型寄存器,	偏移地址: 0x04 */
	GpioOspeedrType		OSPEEDR;					/**< GPIO输出速度寄存器,	偏移地址: 0x08 */
	GpioPupdrType		PUPDR;						/**< GPIO上拉下拉寄存器,	偏移地址: 0x0C */
	GpioIdrType			IDR;						/**< GPIO输入数据寄存器,	偏移地址: 0x10 */
	GpioOdrType			ODR;						/**< GPIO输出数据寄存器,	偏移地址: 0x14 */
	GpioBsrrlType		BSRRL;						/**< GPIO置位寄存器,		偏移地址: 0x18 */
	GpioBsrrhType		BSRRH;						/**< GPIO复位寄存器,		偏移地址: 0x18 */
	GpioLckrType		LCKR;						/**< GPIO锁寄存器,		偏移地址: 0x1C */
	GpioAfrlType		AFRL;						/**< GPIO复用低位寄存器,	偏移地址: 0x20 */
	GpioAfrhType		AFRH;						/**< GPIO复用高位存器,	偏移地址: 0x24 */
	GpioBrrType			BRR;						/**< GPIO复位寄存器，		偏移地址：0x28 */
}GpioType;



/** GPIO口寄存器地址 */
#define GPIOA			(( GpioType*) GPIOA_BASE)
#define GPIOB			(( GpioType*) GPIOB_BASE)
#define GPIOC			(( GpioType*) GPIOC_BASE)
#define GPIOD			(( GpioType*) GPIOD_BASE)
#define GPIOE			(( GpioType*) GPIOE_BASE)
#define GPIOF			(( GpioType*) GPIOF_BASE)
//#define GPIOG			(( GpioType*) GPIOG_BASE)
//#define GPIOH			(( GpioType*) GPIOH_BASE)



#endif
