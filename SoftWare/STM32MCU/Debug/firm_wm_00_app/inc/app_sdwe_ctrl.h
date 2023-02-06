
#ifndef __APP_SDWE_H__
#define __APP_SDWE_H__

//address of weight back to SDWE : (0~7)-> weight of chanel(val:g)
#define SDWE_FUNC_ASK_CHANEL_WEIGHT			(0X0160)//0x0160~0x0167

//address of COLOR back to SDWE : (0~7)-> COLOR of chanel(val=0x00:white,val=0x01:red,val=0x02:green,val=0x03:blue,val=0x04:yellowWhite)
#define SDWE_FUNC_ASK_CHANEL_WEIGHT_COLOR	(0X0168)//0x0168~0x016F

//address of COLOR back to SDWE : (0~9)-> COLOR of point of chanel set triger(val=0x00:white(not triger),val=0x01green(triger))
#define SDWE_FUNC_ASK_CHANEL_POINT_TRIG		(0X020A)//0x020A~0x0213


#endif
