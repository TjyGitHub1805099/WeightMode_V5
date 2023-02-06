#pragma once
#include "string.h"


/*
V1.1:
    
    更新：
        修正配置密钥长度为4字节、8字节时，取用户自定义 ID越界导致运算的密钥结果不正确的问题。
        MINI-Pro脱机下载器 V1.20B 版本固件后使用V1.1版本代码；
        
    影响：
        前提条件：
            (1).MINI-Pro版脱机下载器在升级了固件到V1.20B后，使得MINI脱机下载器内置的是V1.1版本代码;
            (2).密钥长度配置为4字节、8字节的情况；
        导致现象：
            (1).由于修正了算法里密钥长度为 4/8字节时的运算逻辑，会导致运算出的密钥结果（仅密钥长度为4/8字节受影响）
            与V1.0版本的代码运算结果不同！
        解决办法：
            (1).MINI-Pro版脱机下载器已经升级到V1.20B版本固件的用户可以回退到旧版本固件继续使用。
        不受影响的情况：
            (1).只要密钥长度为12字节均不受影响；
V1.0：
    MINI-Pro版脱机下载器V1.19b版固件及之前的固件中均使用了V1.0版本的代码；
*/

typedef enum 
{
    LENGTH_4 = 4,
    LENGTH_8 = 8,
    LENGTH_12 = 12
    
}eKeyLengthType;

typedef enum 
{
    LITTLE_ENDIA = 0,
    BIG_ENDIA
    
}eEndiaType;

typedef enum 
{
    ALGORITHM_0 = 0,
    ALGORITHM_1,
    ALGORITHM_2,
    ALGORITHM_3,
    ALGORITHM_4
    
}eAlgorithmType;


/****************** 调用以下函数完成密钥验证 ******************/
/*
	功能：
		验证指定存储区域的UID加密密钥是否正确
    输入：
        pKey, 指向密钥的存储区域的指针，密钥的起始存储地址
        pUID, 指向UID的存储区域的指针， UID的起始存储地址
        pCustomID, 指向用户设定的自定义ID存储区域的指针
        keyLength, 密钥的字节长度，参考枚举类型 eKeyLengthType的定义
        AlgorithmNum，计算UID加密密钥的算法选择，参考枚举类型 eAlgorithmType的定义
    输出：
        无
    返回：
        返回密钥验证的结果：
        0，正确
        1，错误
*/
char UID_Encryption_Key_Check(void *pKey,                      //[IN]
                              void *pUID,                      //[IN]
                              void *pCustomID,                 //[IN]
                              eKeyLengthType keyLength,        //[IN]
                              eEndiaType endiaType,            //[IN] 
                              eAlgorithmType AlgorithmNum);    //[IN]
/****************** 调用以下函数完成密钥计算 ******************/
/*
	功能：
		计算UID加密密钥
    输入：
        pUID, 指向UID的存储区域的指针用户应该预先分配好， UID的起始存储地址
        pCustomID, 指向用户设定的自定义ID存储区域的指针
        keyLength, 密钥的字节长度，参考枚举类型 eKeyLengthType的定义
        AlgorithmNum，计算UID加密密钥的算法选择，参考枚举类型 eAlgorithmType的定义
    输出：
        pKey, 指向一块内存区域，用于存放计算出的密钥
    返回：
        无
*/
void UID_Encryption_Key_Calculate(void *pKey,                  //[OUT]
                                  void *pUID,                  //[IN]
                                  void *pCustomID,             //[IN]
                                  eKeyLengthType keyLength,    //[IN]
                                  eEndiaType endiaType,        //[IN]
                                  eAlgorithmType AlgorithmNum);//[IN]

