#ifndef __APP_MAIN_TASK_H__
#define __APP_MAIN_TASK_H__

#include "typedefine.h"
#include "app_led_ctrl.h"

#define COLOR_ALT_20210328_DEFINE	(FALSE)
#define COLOR_ALT_20210414_DEFINE	(FALSE)
#define COLOR_ALT_20210427_DEFINE	(FALSE)
#define COLOR_ALT_20210606_DEFINE	(FALSE)

#define SYS_HX711_ONLINE_CHECK_TIME	(2000)//when power on 2000ms start check HX711
#define SYS_REMOVE_WEIGHT_TIME		(3300)//when power on 3300ms remove weight
#define SYS_POWER_REDAY_TIME		(3500)//when power on 3500ms send data to T5L , do not change
#define MCU_VERSION			(33)//2022.01.27
#define DIWEN_VERSION		(33)//2022.01.27
//================================================================================================
/*
1.Screen Page describe
Page1~48:log printf from min to max
Page49:Balancing page , six block display , two group of help data display
Page50:number input page
Page51:text input page
Page52:system param set page
Page53:system caculate page
Page54:second sheet , used for enter Page52 or Page49 or Page53
Page55:Balancing page , 12 block display
Page56:sys password
Page57:Balancing page , six block display , logo and unit and err display
Page58:Balancing page , 12 block display , home enter and remove enter
Page59:help page , six group help data display , logo and unit and err display

2.Page jump logic
2.1.1 when sys powerup , entry Page49
2.1.2 when 0x1102 write 0x1102 , Page49  -> Page57 (single module) ,or Page55  -> Page58 (cascatde module) 
2.1.3 when 0x1101 write 0x1101 , Page57  -> Page49 (single module) ,or Page58  -> Page55 (cascatde module)
2.1.4 when 0x2104 write   1010 , Page54  -> Page52
2.1.5 when 0x2103 write   2021 , Page54  -> Page53
2.1.6 when 0x2103 write   1202 , Page54  -> Page56
2.1.7 when home key enter 		 Page54 <-> Page49(single module) , or Page49 <-> Page55 / Page59 (cascatde module)

*/

//================================================================================================
/*20220119 change list
1.FunctionA Module
1.1.when gSystemPara.isCascade = ModbusFuncA_Slave
    1.1.1.need send the screen block display num as 7~12
    1.1.2.send it's self weight data to screen
    1.1.3.send color data from master to screen
    1.1.4.send caculate help data from master to screen
    1.1.5.screen exchange only six block page to sys para page
1.2.when gSystemPara.isCascade = ModbusFuncA_Master
	1.1.1.need send the screen block display num as 1~6 ; [don't change]
	1.1.2.send it's self weight data to screen ; [don't change]
	1.1.3.send color data from master to screen ; [don't change]
	1.1.4.send caculate help data from master to screen ; [don't change]
	1.1.5.screen exchange only six block page to sys para page

2.1 send weight and color date to screen
	
*/
#endif
