/**
*******************************************************************
* @file    typedefine.h
* @author  MKdriver
* @version V1.0.0
* @date    9-Oct-2015
* @brief   数据类型定义头文件
*******************************************************************
* @attention
*
* 适用于STM32系列处理器
*
* <h2><center>&copy; COPYRIGHT 2015 MKdriver</center></h2>
*******************************************************************
*/

#ifndef __TYPEDEFINE_H__
#define __TYPEDEFINE_H__


#define __INLINE		__inline

//#define CCMRAM  __attribute__((section("ccmram")))
#define CCMRAM

typedef unsigned    char        UINT8;      /**< 无符号8位整数 */
typedef signed      char        INT8;       /**< 带符号8位整数 */
typedef unsigned    short       UINT16;     /**< 无符号16位整数 */
typedef signed      short       INT16;      /**< 带符号16位整数 */
typedef unsigned    int         UINT32;     /**< 无符号32位整数 */
typedef signed      int         INT32;      /**< 带符号32位整数 */
typedef unsigned    long long   UINT64;     /**< 无符号64位整数 */
typedef signed      long long   INT64;      /**< 带符号64位整数 */

typedef union
{
	UINT32 U32;
	INT32  I32;
	float  F32;
	UINT16 U16[ 2 ];
	INT16  I16[ 2 ];
	UINT8  U8[ 4 ];
	INT8   I8[ 4 ];
}FourByteUnioType;

typedef union
{
	UINT16 U16;
	INT16  I16;
	UINT8  U8[ 2 ];
	INT8   I8[ 2 ];
}TwoByteUnioType;

typedef enum ParaAttrType
{
	PARA_READ_ONLY = 0,
	PARA_WRITE_SINGLE,
	PARA_WRITE_MULTI,
    PARA_READ_ONLY_PRIVATE,
    PARA_WRITE_SINGLE_PRIVATE,
    PARA_WRITE_MULTI_PRIVATE
}enumParaAttrType;

typedef enum ParaTypeType
{
    PARA_TYPE_BOOL = 0,
    PARA_TYPE_U8,
    PARA_TYPE_I8,
    PARA_TYPE_U16,
    PARA_TYPE_I16,
    PARA_TYPE_U32,
    PARA_TYPE_I32,
    PARA_TYPE_U8_HEX,
    PARA_TYPE_U16_HEX,
    PARA_TYPE_U32_HEX
}enumParaTypeType;

typedef struct ModbusAddrToParamIndexType
{
    UINT16 Index;
    UINT16 HighFlag;
}structModbusAddrToParamIndexType;

typedef struct MbEventIdBuffType
{
    UINT8 ReadAddr;
    UINT8 WriteAddr;
    UINT8 Left;
    UINT8 Size;
    UINT16 *pEventIdBuffer;
}structMbEventIdBuffType;

/** 32位整形类型变量定义 */
typedef struct MbParaType
{
    UINT16              MbAddress;
    UINT16              EventId;
    INT32				Value;
    INT32               ValueOld;
    enumParaAttrType	Attr;
    enumParaTypeType    Type;
    UINT8               DotBits;
    INT32				Default;
    INT32				Max;
    INT32				Min;
}structMbParaType;

/** 板子所有集合体变量指针定义 */
typedef struct ModbusParaType
{
    structMbParaType *pParam;
    UINT16	MbStartAddr;
    UINT16	MbEndAddr;
    structMbEventIdBuffType   EventBuff;
}structModbusParaType;

/** 使能控制状态定义 */
typedef enum
{
	DISABLE = 0,								/**< 不使能 */
	ENABLE = 1									/**< 使能 */
}FuncState;

/** 查询状态定义 */
typedef enum
{
	RESET = 0,									/**< 查询状态未置位 */
	SET = 1										/**< 查询状态置位 */
}FlagStatus, ITStatus;

/** 报警状态定义 */
typedef enum
{
	WARN = 0,									/**< 报警 */
	NORMAL = 1									/**< 正常 */
}WarnState;

/** 电平状态定义 */
typedef enum
{
	LOW = 0,									/**< 低电平 */
	HIGH = 1									/**< 高电平 */
}LevelState;

/** 执行状态定义 */
typedef enum
{
	SUCCESS = 0,								/**< 成功 */
	ERROR = 1									/**< 失败 */
}ErrorStatus;

typedef struct
{
	void( *init )( void );
	void( *read_bytes )( UINT8 StartAddr, UINT8 *pDat, UINT16 Length );
	void( *write_bytes )( UINT8 StartAddr, UINT8 *pDat, UINT16 Length );
}MemDeviceType;

#ifndef TRUE
#define TRUE	(1)
#endif

#ifndef FALSE
#define FALSE	(0)
#endif

#endif
