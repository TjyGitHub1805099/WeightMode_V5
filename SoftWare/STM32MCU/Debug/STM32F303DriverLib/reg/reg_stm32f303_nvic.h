/**
  *******************************************************************
  * @file    reg_stm32f303_nvic.h
  * @author  MKdriver
  * @version V1.0.0
  * @date    9-Oct-2015
  * @brief   STM32F40xNVIC寄存器定义头文件
  *******************************************************************
  * @attention
  *
  * 
  *
  * <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
  *******************************************************************
  */
#ifndef __REG_STM32F407_NVIC_H__
#define __REG_STM32F407_NVIC_H__


#include "reg_stm32f303_address.h"



/** NVIC置中断使能寄存器位定义 */
typedef struct
{
	UINT32 ISE0		: 1;							/**< Bit0,中断0入口使能，0：禁止，1：使能 */						
	UINT32 ISE1		: 1;							/**< Bit1,中断1入口使能，0：禁止，1：使能 */
	UINT32 ISE2		: 1;							/**< Bit2,中断2入口使能，0：禁止，1：使能 */
	UINT32 ISE3		: 1;							/**< Bit3,中断3入口使能，0：禁止，1：使能 */
	UINT32 ISE4		: 1;							/**< Bit4,中断4入口使能，0：禁止，1：使能 */
	UINT32 ISE5		: 1;							/**< Bit5,中断5入口使能，0：禁止，1：使能 */
	UINT32 ISE6		: 1;							/**< Bit6,中断6入口使能，0：禁止，1：使能 */
	UINT32 ISE7		: 1;							/**< Bit7,中断7入口使能，0：禁止，1：使能 */
	UINT32 ISE8		: 1;							/**< Bit8,中断8入口使能，0：禁止，1：使能 */
	UINT32 ISE9		: 1;							/**< Bit9,中断9入口使能，0：禁止，1：使能 */
	UINT32 ISE10	: 1;							/**< Bit10,中断10入口使能，0：禁止，1：使能 */
	UINT32 ISE11	: 1;							/**< Bit11,中断11入口使能，0：禁止，1：使能 */
	UINT32 ISE12	: 1;							/**< Bit12,中断12入口使能，0：禁止，1：使能 */
	UINT32 ISE13	: 1;							/**< Bit13,中断13入口使能，0：禁止，1：使能 */
	UINT32 ISE14	: 1;							/**< Bit14,中断14入口使能，0：禁止，1：使能 */
	UINT32 ISE15	: 1;							/**< Bit15,中断15入口使能，0：禁止，1：使能 */
	UINT32 ISE16	: 1;							/**< Bit16,中断16入口使能，0：禁止，1：使能 */
	UINT32 ISE17	: 1;							/**< Bit17,中断17入口使能，0：禁止，1：使能 */
	UINT32 ISE18	: 1;							/**< Bit18,中断18入口使能，0：禁止，1：使能 */
	UINT32 ISE19	: 1;							/**< Bit19,中断19入口使能，0：禁止，1：使能 */
	UINT32 ISE20	: 1;							/**< Bit20,中断20入口使能，0：禁止，1：使能 */
	UINT32 ISE21	: 1;							/**< Bit21,中断21入口使能，0：禁止，1：使能 */
	UINT32 ISE22	: 1;							/**< Bit22,中断22入口使能，0：禁止，1：使能 */
	UINT32 ISE23	: 1;							/**< Bit23,中断23入口使能，0：禁止，1：使能 */
	UINT32 ISE24	: 1;							/**< Bit24,中断24入口使能，0：禁止，1：使能 */
	UINT32 ISE25	: 1;							/**< Bit25,中断25入口使能，0：禁止，1：使能 */
	UINT32 ISE26	: 1;							/**< Bit26,中断26入口使能，0：禁止，1：使能 */
	UINT32 ISE27	: 1;							/**< Bit27,中断27入口使能，0：禁止，1：使能 */
	UINT32 ISE28	: 1;							/**< Bit28,中断28入口使能，0：禁止，1：使能 */
	UINT32 ISE29	: 1;							/**< Bit29,中断29入口使能，0：禁止，1：使能 */
	UINT32 ISE30	: 1;							/**< Bit30,中断30入口使能，0：禁止，1：使能 */
	UINT32 ISE31	: 1;							/**< Bit31,中断31入口使能，0：禁止，1：使能 */
}NvicIserRegBitType;

/** NVIC置中断使能寄存器定义 */
typedef union
{
	UINT32 all;										/**< 中断使能寄存器所有位 */
	NvicIserRegBitType bit;							/**< 中断使能寄存器位定义 */
}NvicIserRegType;

/** NVIC清中断使能寄存器位定义 */
typedef struct
{
	UINT32 ICE0		: 1;							/**< Bit0,中断0入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE1		: 1;							/**< Bit1,中断1入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE2		: 1;							/**< Bit2,中断2入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE3		: 1;							/**< Bit3,中断3入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE4		: 1;							/**< Bit4,中断4入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE5		: 1;							/**< Bit5,中断5入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE6		: 1;							/**< Bit6,中断6入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE7		: 1;							/**< Bit7,中断7入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE8		: 1;							/**< Bit8,中断8入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE9		: 1;							/**< Bit9,中断9入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE10	: 1;							/**< Bit10,中断10入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE11	: 1;							/**< Bit11,中断11入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE12	: 1;							/**< Bit12,中断12入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE13	: 1;							/**< Bit13,中断13入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE14	: 1;							/**< Bit14,中断14入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE15	: 1;							/**< Bit15,中断15入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE16	: 1;							/**< Bit16,中断16入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE17	: 1;							/**< Bit17,中断17入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE18	: 1;							/**< Bit18,中断18入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE19	: 1;							/**< Bit19,中断19入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE20	: 1;							/**< Bit20,中断20入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE21	: 1;							/**< Bit21,中断21入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE22	: 1;							/**< Bit22,中断22入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE23	: 1;							/**< Bit23,中断23入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE24	: 1;							/**< Bit24,中断24入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE25	: 1;							/**< Bit25,中断25入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE26	: 1;							/**< Bit26,中断26入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE27	: 1;							/**< Bit27,中断27入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE28	: 1;							/**< Bit28,中断28入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE29	: 1;							/**< Bit29,中断29入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE30	: 1;							/**< Bit30,中断30入口清使能位，0：使能，1：清使能位（禁止） */
	UINT32 ICE31	: 1;							/**< Bit31,中断31入口清使能位，0：使能，1：清使能位（禁止） */
}NvicIcerRegBitType;

/** NVIC清中断使能寄存器定义 */
typedef union
{
	UINT32 all;										/**< 清中断使能寄存器所有位 */
	NvicIcerRegBitType bit;							/**< 清中断使能寄存器位定义 */
}NvicIcerRegType;

/** NVIC置中断挂起寄存器位定义 */
typedef struct
{
	UINT32 ISP0		: 1;							/**< Bit0,中断0挂起，置1中断挂起 */						
	UINT32 ISP1		: 1;							/**< Bit1,中断1挂起，置1中断挂起 */
	UINT32 ISP2		: 1;							/**< Bit2,中断2挂起，置1中断挂起 */
	UINT32 ISP3		: 1;							/**< Bit3,中断3挂起，置1中断挂起 */
	UINT32 ISP4		: 1;							/**< Bit4,中断4挂起，置1中断挂起 */
	UINT32 ISP5		: 1;							/**< Bit5,中断5挂起，置1中断挂起 */
	UINT32 ISP6		: 1;							/**< Bit6,中断6挂起，置1中断挂起 */
	UINT32 ISP7		: 1;							/**< Bit7,中断7挂起，置1中断挂起 */
	UINT32 ISP8		: 1;							/**< Bit8,中断8挂起，置1中断挂起 */
	UINT32 ISP9		: 1;							/**< Bit9,中断9挂起，置1中断挂起 */
	UINT32 ISP10	: 1;							/**< Bit10,中断10挂起，置1中断挂起 */
	UINT32 ISP11	: 1;							/**< Bit11,中断11挂起，置1中断挂起 */
	UINT32 ISP12	: 1;							/**< Bit12,中断12挂起，置1中断挂起 */
	UINT32 ISP13	: 1;							/**< Bit13,中断13挂起，置1中断挂起 */
	UINT32 ISP14	: 1;							/**< Bit14,中断14挂起，置1中断挂起 */
	UINT32 ISP15	: 1;							/**< Bit15,中断15挂起，置1中断挂起 */
	UINT32 ISP16	: 1;							/**< Bit16,中断16挂起，置1中断挂起 */
	UINT32 ISP17	: 1;							/**< Bit17,中断17挂起，置1中断挂起 */
	UINT32 ISP18	: 1;							/**< Bit18,中断18挂起，置1中断挂起 */
	UINT32 ISP19	: 1;							/**< Bit19,中断19挂起，置1中断挂起 */
	UINT32 ISP20	: 1;							/**< Bit20,中断20挂起，置1中断挂起 */
	UINT32 ISP21	: 1;							/**< Bit21,中断21挂起，置1中断挂起 */
	UINT32 ISP22	: 1;							/**< Bit22,中断22挂起，置1中断挂起 */
	UINT32 ISP23	: 1;							/**< Bit23,中断23挂起，置1中断挂起 */
	UINT32 ISP24	: 1;							/**< Bit24,中断24挂起，置1中断挂起 */
	UINT32 ISP25	: 1;							/**< Bit25,中断25挂起，置1中断挂起 */
	UINT32 ISP26	: 1;							/**< Bit26,中断26挂起，置1中断挂起 */
	UINT32 ISP27	: 1;							/**< Bit27,中断27挂起，置1中断挂起 */
	UINT32 ISP28	: 1;							/**< Bit28,中断28挂起，置1中断挂起 */
	UINT32 ISP29	: 1;							/**< Bit29,中断29挂起，置1中断挂起 */
	UINT32 ISP30	: 1;							/**< Bit30,中断30挂起，置1中断挂起 */
	UINT32 ISP31	: 1;							/**< Bit31,中断31挂起，置1中断挂起 */
}NvicIsprRegBitType;

/** NVIC置中断挂起寄存器定义 */
typedef union
{
	UINT32 all;										/**< 置中断挂起寄存器所有位 */
	NvicIsprRegBitType bit;							/**< 置中断挂起寄存器位定义 */
}NvicIsprRegType;

/** NVIC清中断挂起寄存器位定义 */
typedef struct
{
	UINT32 ICP0		: 1;							/**< Bit0,清中断0挂起，置1清中断挂起 */
	UINT32 ICP1		: 1;							/**< Bit1,清中断1挂起，置1清中断挂起 */
	UINT32 ICP2		: 1;							/**< Bit2,清中断2挂起，置1清中断挂起 */
	UINT32 ICP3		: 1;							/**< Bit3,清中断3挂起，置1清中断挂起 */
	UINT32 ICP4		: 1;							/**< Bit4,清中断4挂起，置1清中断挂起 */
	UINT32 ICP5		: 1;							/**< Bit5,清中断5挂起，置1清中断挂起 */
	UINT32 ICP6		: 1;							/**< Bit6,清中断6挂起，置1清中断挂起 */
	UINT32 ICP7		: 1;							/**< Bit7,清中断7挂起，置1清中断挂起 */
	UINT32 ICP8		: 1;							/**< Bit8,清中断8挂起，置1清中断挂起 */
	UINT32 ICP9		: 1;							/**< Bit9,清中断9挂起，置1清中断挂起 */
	UINT32 ICP10	: 1;							/**< Bit10,清中断10挂起，置1清中断挂起 */
	UINT32 ICP11	: 1;							/**< Bit11,清中断11挂起，置1清中断挂起 */
	UINT32 ICP12	: 1;							/**< Bit12,清中断12挂起，置1清中断挂起 */
	UINT32 ICP13	: 1;							/**< Bit13,清中断13挂起，置1清中断挂起 */
	UINT32 ICP14	: 1;							/**< Bit14,清中断14挂起，置1清中断挂起 */
	UINT32 ICP15	: 1;							/**< Bit15,清中断15挂起，置1清中断挂起 */
	UINT32 ICP16	: 1;							/**< Bit16,清中断16挂起，置1清中断挂起 */
	UINT32 ICP17	: 1;							/**< Bit17,清中断17挂起，置1清中断挂起 */
	UINT32 ICP18	: 1;							/**< Bit18,清中断18挂起，置1清中断挂起 */
	UINT32 ICP19	: 1;							/**< Bit19,清中断19挂起，置1清中断挂起 */
	UINT32 ICP20	: 1;							/**< Bit20,清中断20挂起，置1清中断挂起 */
	UINT32 ICP21	: 1;							/**< Bit21,清中断21挂起，置1清中断挂起 */
	UINT32 ICP22	: 1;							/**< Bit22,清中断22挂起，置1清中断挂起 */
	UINT32 ICP23	: 1;							/**< Bit23,清中断23挂起，置1清中断挂起 */
	UINT32 ICP24	: 1;							/**< Bit24,清中断24挂起，置1清中断挂起 */
	UINT32 ICP25	: 1;							/**< Bit25,清中断25挂起，置1清中断挂起 */
	UINT32 ICP26	: 1;							/**< Bit26,清中断26挂起，置1清中断挂起 */
	UINT32 ICP27	: 1;							/**< Bit27,清中断27挂起，置1清中断挂起 */
	UINT32 ICP28	: 1;							/**< Bit28,清中断28挂起，置1清中断挂起 */
	UINT32 ICP29	: 1;							/**< Bit29,清中断29挂起，置1清中断挂起 */
	UINT32 ICP30	: 1;							/**< Bit30,清中断30挂起，置1清中断挂起 */
	UINT32 ICP31	: 1;							/**< Bit31,清中断31挂起，置1清中断挂起 */
}NvicIcprRegBitType;

/** NVIC清中断挂起寄存器定义 */
typedef union
{
	UINT32 all;										/**< 清中断挂起寄存器所有位 */
	NvicIcprRegBitType bit;							/**< 清中断挂起寄存器位定义 */
}NvicIcprRegType;

/** NVIC中断状态寄存器位定义 */
typedef struct
{
	UINT32 IAB0		: 1;							/**< Bit0,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB1		: 1;							/**< Bit1,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB2		: 1;							/**< Bit2,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB3		: 1;							/**< Bit3,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB4		: 1;							/**< Bit4,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB5		: 1;							/**< Bit5,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB6		: 1;							/**< Bit6,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB7		: 1;							/**< Bit7,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB8		: 1;							/**< Bit8,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB9		: 1;							/**< Bit9,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB10	: 1;							/**< Bit10,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB11	: 1;							/**< Bit11,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB12	: 1;							/**< Bit12,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB13	: 1;							/**< Bit13,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB14	: 1;							/**< Bit14,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB15	: 1;							/**< Bit15,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB16	: 1;							/**< Bit16,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB17	: 1;							/**< Bit17,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB18	: 1;							/**< Bit18,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB19	: 1;							/**< Bit19,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB20	: 1;							/**< Bit20,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB21	: 1;							/**< Bit21,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB22	: 1;							/**< Bit22,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB23	: 1;							/**< Bit23,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB24	: 1;							/**< Bit24,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB25	: 1;							/**< Bit25,中断0状态，0：该中断没有发生，1：该中断已发生 */	
	UINT32 IAB26	: 1;							/**< Bit26,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB27	: 1;							/**< Bit27,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB28	: 1;							/**< Bit28,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB29	: 1;							/**< Bit29,中断0状态，0：该中断没有发生，1：该中断已发生 */	
	UINT32 IAB30	: 1;							/**< Bit30,中断0状态，0：该中断没有发生，1：该中断已发生 */
	UINT32 IAB31	: 1;							/**< Bit31,中断0状态，0：该中断没有发生，1：该中断已发生 */
}NvicIabrRegBitType;

/** NVIC中断状态寄存器定义 */
typedef union
{
	UINT32 all;										/**< 中断状态寄存器所有位 */
	NvicIabrRegBitType bit;							/**< 中断状态寄存器位定义 */
}NvicIabrRegType;

/** NVIC中断软件触发寄存器位定义 */
typedef struct
{
	UINT32 STI0		: 1;							/**< Bit0,中断通道0软件触发使能位，0：不使能，1：使能 */
	UINT32 STI1		: 1;							/**< Bit1,中断通道1软件触发使能位，0：不使能，1：使能 */
	UINT32 STI2		: 1;                            /**< Bit2,中断通道2软件触发使能位，0：不使能，1：使能 */
	UINT32 STI3		: 1;							/**< Bit3,中断通道3软件触发使能位，0：不使能，1：使能 */
	UINT32 STI4		: 1;							/**< Bit4,中断通道4软件触发使能位，0：不使能，1：使能 */
	UINT32 STI5		: 1;							/**< Bit5,中断通道5软件触发使能位，0：不使能，1：使能 */
	UINT32 STI6		: 1;							/**< Bit6,中断通道6软件触发使能位，0：不使能，1：使能 */
	UINT32 STI7		: 1;							/**< Bit7,中断通道7软件触发使能位，0：不使能，1：使能 */
	UINT32 STI8		: 1;							/**< Bit8,中断通道8软件触发使能位，0：不使能，1：使能 */
	UINT32 STI9		: 1;							/**< Bit9,中断通道9软件触发使能位，0：不使能，1：使能 */
	UINT32 STI10	: 1;							/**< Bit10,中断通道10软件触发使能位，0：不使能，1：使能 */
	UINT32 STI11	: 1;							/**< Bit11,中断通道11软件触发使能位，0：不使能，1：使能 */
	UINT32 STI12	: 1;							/**< Bit12,中断通道12软件触发使能位，0：不使能，1：使能 */
	UINT32 STI13	: 1;							/**< Bit13,中断通道13软件触发使能位，0：不使能，1：使能 */
	UINT32 STI14	: 1;							/**< Bit14,中断通道14软件触发使能位，0：不使能，1：使能 */
	UINT32 STI15	: 1;							/**< Bit15,中断通道15软件触发使能位，0：不使能，1：使能 */
	UINT32 STI16	: 1;							/**< Bit16,中断通道16软件触发使能位，0：不使能，1：使能 */
	UINT32 STI17	: 1;							/**< Bit17,中断通道17软件触发使能位，0：不使能，1：使能 */
	UINT32 STI18	: 1;							/**< Bit18,中断通道18软件触发使能位，0：不使能，1：使能 */
	UINT32 STI19	: 1;							/**< Bit19,中断通道19软件触发使能位，0：不使能，1：使能 */
	UINT32 STI20	: 1;							/**< Bit20,中断通道20软件触发使能位，0：不使能，1：使能 */
	UINT32 STI21	: 1;							/**< Bit21,中断通道21软件触发使能位，0：不使能，1：使能 */
	UINT32 STI22	: 1;							/**< Bit22,中断通道22软件触发使能位，0：不使能，1：使能 */
	UINT32 STI23	: 1;							/**< Bit23,中断通道23软件触发使能位，0：不使能，1：使能 */
	UINT32 STI24	: 1;							/**< Bit24,中断通道24软件触发使能位，0：不使能，1：使能 */
	UINT32 STI25	: 1;							/**< Bit25,中断通道25软件触发使能位，0：不使能，1：使能 */
	UINT32 STI26	: 1;							/**< Bit26,中断通道26软件触发使能位，0：不使能，1：使能 */
	UINT32 STI27	: 1;							/**< Bit27,中断通道27软件触发使能位，0：不使能，1：使能 */
	UINT32 STI28	: 1;							/**< Bit28,中断通道28软件触发使能位，0：不使能，1：使能 */
	UINT32 STI29	: 1;							/**< Bit29,中断通道29软件触发使能位，0：不使能，1：使能 */
	UINT32 STI30	: 1;							/**< Bit30,中断通道30软件触发使能位，0：不使能，1：使能 */
	UINT32 STI31	: 1;							/**< Bit31,中断通道31软件触发使能位，0：不使能，1：使能 */
}NvicStirRegBitType;

/** NVIC中断软件触发寄存器定义 */
typedef union
{
	UINT32 all;										/**< 中断软件触发寄存器所有位 */
	NvicStirRegBitType bit;							/**< 中断软件触发寄存器位定义 */
}NvicStirRegType;


/** NVIC寄存器定义 */
typedef struct
{
	NvicIserRegType ISER[8];                 /**< 使能寄存器, 偏移地址: 0x000 */
	UINT32 RESERVED0[24];
	NvicIcerRegType ICER[8];                 /**< 清使能寄存器,偏移地址: 0x080 */
	UINT32 RSERVED1[24];
	NvicIsprRegType ISPR[8];                 /**< 置中断挂起寄存器, 偏移地址: 0x100 */
	UINT32 RESERVED2[24];
	NvicIcprRegType ICPR[8];                 /**< 清中断挂起寄存器, 偏移地址: 0x180 */
	UINT32 RESERVED3[24];
	NvicIabrRegType IABR[8];                 /**< 活跃状态寄存器, 偏移地址: 0x200 */
	UINT32 RESERVED4[56];
	UINT8  IP[240];                  		/**< 中断优先级寄存器， 偏移地址: 0x300 */
	UINT32 RESERVED5[644];
	NvicStirRegType STIR;                    /**< 软件触发中断寄存器, 偏移地址: 0xE00 */
}  NvicRegType;


#define NVIC                (( NvicRegType *) NVIC_BASE )

//=======================================================================================================

/** SCB寄存器定义 */
typedef struct
{
    volatile const UINT32 CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
    UINT32 ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
    UINT32 VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
    volatile  UINT32 AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
    UINT32 SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
    UINT32 CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
    UINT8  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    UINT32 SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
    UINT32 CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
    UINT32 HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
    UINT32 DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
    UINT32 MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
    UINT32 BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
    UINT32 AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
    UINT32 PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
    UINT32 DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
    UINT32 ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
    UINT32 MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
    UINT32 ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
    UINT32 RESERVED0[5];
    UINT32 CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
} ScbRegType;

#define SCB                 	((ScbRegType   *) SCB_BASE)   /*!< SCB configuration struct           */

//===========================================================================

#endif

