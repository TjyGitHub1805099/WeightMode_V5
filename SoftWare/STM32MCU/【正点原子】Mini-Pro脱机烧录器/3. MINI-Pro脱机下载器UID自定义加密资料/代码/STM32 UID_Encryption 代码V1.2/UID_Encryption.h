#pragma once
#include "string.h"

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
    输入：
        pKey, 指向密钥的存储区域的指针，密钥的起始存储地址
        pUID, 指向UID的存储区域的指针， UID的起始存储地址
        pCustomID, 指向用户设定的自定义ID存储区域的指针
        keyLength, 密钥的字节长度，可选项参考枚举类型 eKeyLengthType的定义
        endiaType, 大小端序选择，可选项参考枚举类型 eEndiaType的定义
        AlgorithmNum，计算UID加密密钥的算法选择，可选项参考枚举类型 eAlgorithmType的定义
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
    输入：
        pUID, 指向UID的存储区域的指针用户应该预先分配好， UID的起始存储地址
        pCustomID, 指向用户设定的自定义ID存储区域的指针
        keyLength, 密钥的字节长度，可选项参考枚举类型 eKeyLengthType的定义
        endiaType, 大小端序选择，可选项参考枚举类型 eEndiaType的定义
        AlgorithmNum，计算UID加密密钥的算法选择，可选项参考枚举类型 eAlgorithmType的定义
    输出：
        pKey, 指向一块内存区域，用于存放计算出的密钥
    返回：
        返回密钥验证的结果：
        0，正确
        1，错误
*/
void UID_Encryption_Key_Calculate(void *pKey,                  //[OUT]
                                  void *pUID,                  //[IN]
                                  void *pCustomID,             //[IN]
                                  eKeyLengthType keyLength,    //[IN]
                                  eEndiaType endiaType,        //[IN]
                                  eAlgorithmType AlgorithmNum);//[IN]

