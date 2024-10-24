#ifndef __APP_EPS8266_H__
#define __APP_EPS8266_H__
//详见：https://blog.csdn.net/weixin_43772810/article/details/123921429
//及：https://blog.csdn.net/qq_52046032/article/details/126189265
#include "hal_gpio.h"
#include "stm32f4xx_hal.h"

//结束符
const uint8_t s_AT_Order_End[] = "\r\n";

//检测设备是否在线
const uint8_t s_AT_Order_AT[5] = "AT\r\n"; 

//设置工作模式 1：station模式   2：AP模式  3：兼容 AP+station模式
const uint8_t s_AT_Order_Set_CWMODE_ST[] = "AT+CWMODE=1\r\n";//返回值：OK
const uint8_t s_AT_Order_Set_CWMODE_AP[] = "AT+CWMODE=2\r\n";//返回值：OK
const uint8_t s_AT_Order_Set_CWMODE_ST_AP[] = "AT+CWMODE=3\r\n";//返回值：OK
const uint8_t s_AT_Order_Get_CWMODE[] = "AT+CWMODE?\r\n";

//让Wifi模块重启的命令
const uint8_t s_AT_Order_RST[] = "AT+RST\r\n";

//是否启用多连接：=0：单路连接模式     =1：多路连接模式
const uint8_t s_AT_Order_Set_CIPMUX_0[]="AT+CIPMUX=0\r\n"//返回值：OK
const uint8_t s_AT_Order_Set_CIPMUX_1[]="AT+CIPMUX=1\r\n"//返回值：OK

 //设置设备网络端口 8080
 const uint8_t s_AT_Order_Set_CIPSERVER[] = "AT+CIPSERVER=1,8080\r\n";


 //若当主机：设置wifi名称密码 
const uint8_t s_AT_Order_Set_CWSAP[] = "AT+CWSAP=\"mechanical\",\"a1234567\",11,3\r\n";

//若当从机：连接WiFi
const uint8_t s_AT_Order_Set_CWJAP[] ="AT+CWJAP=\"mechanical\",\"a1234567\"\r\n";////返回 WIFI CONNECTED + WIFI GOT IP + OK
//若当从机：断开热点
const uint8_t s_AT_Order_Set_CWQAP[] ="AT+CWQAP\r\n";//返回 OK + WIFI DISCONNECT



//查询设备IP地址
const uint8_t s_AT_Order_Get_CIFSR[] = "AT+CIFSR\r\n";


//建立TCP连接  连接类型  远程服务器IP地址   远程服务器端口号
const uint8_t s_AT_Order_Set_CIPSTART[] =  "AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080\r\n";
//断开TCP连接
const uint8_t s_AT_Order_Set_CIPCLOSE[] = "AT+CIPCLOSE\r\n";


//是否开启透传模式  0：表示关闭 1：表示开启透传
const uint8_t s_AT_Order_Set_CIPMODE[] = "AT+CIPMODE=1\r\n";

//透传模式下 1、首先发指令 2、就可以直接发数据
const uint8_t s_AT_Order_Set_CIPSEND[] ="AT+CIPSEND\r\n";

//退出发送数据：连续3个+，不需要回车换行
const uint8_t s_AT_Order_Set_CIPSEND_CLOSE[] = "\43\43\43\r\n";//+++

#endif
