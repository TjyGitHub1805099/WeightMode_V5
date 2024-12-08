#ifndef __APP_MAIN_TASK_H__
#define __APP_MAIN_TASK_H__

#include "typedefine.h"
#include "app_led_ctrl.h"
#include "stm32f4xx_it.h"

#define SYS_HX711_ONLINE_CHECK_TIME	(2000)//when power on 2000ms start check HX711  , total 3 times
#define MCU_VERSION			        (1208)//2024.12.08
#define DIWEN_VERSION		        (1208)//2024.12.08

extern UINT32 get_SysTick_ByTimer(void);
extern void app_main_task(void);

/*
//mcu version : 8.0  , diwen version :8.0
1、上电后，通过MCU获取到迪文屏的版本信息，进而指示可以正常与屏通信
2、迪文屏自身存在上电2秒后屏幕才显示，因此屏幕的开机动画，右MCU控制从第1页显示到45页
3、迪文屏幕正常不需要刷写其.cfg文件，如果需要刷写，那么.cfg的第二行（屏幕信息）第三行（校准信息）必须为0（0：代表不做任何更改）
4、重量信息从2字节改成4字节，便于小数显示
5、采用描述指针来控制重量显示，字体信息有：位置，字体颜色，字库及字体大小，对齐方式，小数显示等

//mcu version : 8.1  , diwen version :8.1
1、对屏幕序号添加描述指针，便于对位置调整
2、屏幕的每个单元的序号添加描述指针

//mcu version : 8.5  , diwen version :8.3
1、修改主板程序，解决屏幕未配平时显示有颜色，比如拿下来后全0还存在颜色 详见微信聊天

//mcu version : 12.3  , diwen version :12.3
1、修改主板程序，将托盘数量添加存储
2、修改主板程序，将屏的描述指针分类成6 8 12 16独立cfg文件
3、修改屏幕程序，使用48页面，只显示6头内容
4、修改屏幕程序，DIWENSET里面的cfg用T5LCFG_C088-CTP-20231011-LANTAINA.CFG 但是存在触摸反应慢

//mcu version : 12.6  , diwen version :12.6
A1、修改主板程序，添加新的配平方法
A2、修改主板程序，修改帮助信息的输入用当前托盘颜色，无效的则排序
A3、修改主板程序，配平组里面的扩容函数添加对最小值最大值及当前重量是否在零点以内
B1、修改屏幕程序，在系统参数2添加"等重配平"

//mcu version : 12.8  , diwen version :12.8
A1、修改主板程序，在系统参数2添加"男声女声"

B1、修改屏幕程序，在系统参数2添加"男声女声"
*/
#endif
