#pragma once
#include "string.h"


/*
V1.1:
    
    ���£�
        ����������Կ����Ϊ4�ֽڡ�8�ֽ�ʱ��ȡ�û��Զ��� IDԽ�絼���������Կ�������ȷ�����⡣
        MINI-Pro�ѻ������� V1.20B �汾�̼���ʹ��V1.1�汾���룻
        
    Ӱ�죺
        ǰ��������
            (1).MINI-Pro���ѻ��������������˹̼���V1.20B��ʹ��MINI�ѻ����������õ���V1.1�汾����;
            (2).��Կ��������Ϊ4�ֽڡ�8�ֽڵ������
        ��������
            (1).�����������㷨����Կ����Ϊ 4/8�ֽ�ʱ�������߼����ᵼ�����������Կ���������Կ����Ϊ4/8�ֽ���Ӱ�죩
            ��V1.0�汾�Ĵ�����������ͬ��
        ����취��
            (1).MINI-Pro���ѻ��������Ѿ�������V1.20B�汾�̼����û����Ի��˵��ɰ汾�̼�����ʹ�á�
        ����Ӱ��������
            (1).ֻҪ��Կ����Ϊ12�ֽھ�����Ӱ�죻
V1.0��
    MINI-Pro���ѻ�������V1.19b��̼���֮ǰ�Ĺ̼��о�ʹ����V1.0�汾�Ĵ��룻
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


/****************** �������º��������Կ��֤ ******************/
/*
	���ܣ�
		��ָ֤���洢�����UID������Կ�Ƿ���ȷ
    ���룺
        pKey, ָ����Կ�Ĵ洢�����ָ�룬��Կ����ʼ�洢��ַ
        pUID, ָ��UID�Ĵ洢�����ָ�룬 UID����ʼ�洢��ַ
        pCustomID, ָ���û��趨���Զ���ID�洢�����ָ��
        keyLength, ��Կ���ֽڳ��ȣ��ο�ö������ eKeyLengthType�Ķ���
        AlgorithmNum������UID������Կ���㷨ѡ�񣬲ο�ö������ eAlgorithmType�Ķ���
    �����
        ��
    ���أ�
        ������Կ��֤�Ľ����
        0����ȷ
        1������
*/
char UID_Encryption_Key_Check(void *pKey,                      //[IN]
                              void *pUID,                      //[IN]
                              void *pCustomID,                 //[IN]
                              eKeyLengthType keyLength,        //[IN]
                              eEndiaType endiaType,            //[IN] 
                              eAlgorithmType AlgorithmNum);    //[IN]
/****************** �������º��������Կ���� ******************/
/*
	���ܣ�
		����UID������Կ
    ���룺
        pUID, ָ��UID�Ĵ洢�����ָ���û�Ӧ��Ԥ�ȷ���ã� UID����ʼ�洢��ַ
        pCustomID, ָ���û��趨���Զ���ID�洢�����ָ��
        keyLength, ��Կ���ֽڳ��ȣ��ο�ö������ eKeyLengthType�Ķ���
        AlgorithmNum������UID������Կ���㷨ѡ�񣬲ο�ö������ eAlgorithmType�Ķ���
    �����
        pKey, ָ��һ���ڴ��������ڴ�ż��������Կ
    ���أ�
        ��
*/
void UID_Encryption_Key_Calculate(void *pKey,                  //[OUT]
                                  void *pUID,                  //[IN]
                                  void *pCustomID,             //[IN]
                                  eKeyLengthType keyLength,    //[IN]
                                  eEndiaType endiaType,        //[IN]
                                  eAlgorithmType AlgorithmNum);//[IN]

