   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
   4                     ; Optimizer V4.3.6 - 29 Nov 2011
  21                     	bsct
  22  0000               _myKey:
  23  0000 00            	dc.b	0
  24  0001 000000000000  	ds.b	11
  25                     .const:	section	.text
  26  0000               _myID:
  27  0000 01            	dc.b	1
  28  0001 02            	dc.b	2
  29  0002 03            	dc.b	3
  30  0003 04            	dc.b	4
  31  0004 05            	dc.b	5
  32  0005 06            	dc.b	6
  33  0006 07            	dc.b	7
  34  0007 08            	dc.b	8
  35  0008 09            	dc.b	9
  36  0009 0a            	dc.b	10
  37  000a 0b            	dc.b	11
  38  000b 0c            	dc.b	12
  93                     ; 94 void main(void)
  93                     ; 95 {
  95                     .text:	section	.text,new
  96  0000               _main:
  98  0000 88            	push	a
  99       00000001      OFST:	set	1
 102                     ; 96 	uint8_t i = 0;
 104                     ; 97 	uint8_t checkResult = 0;
 106                     ; 99 	UART1_Init( 115200,
 106                     ; 100                 UART1_WORDLENGTH_8D,
 106                     ; 101                 UART1_STOPBITS_1,
 106                     ; 102                 UART1_PARITY_NO,
 106                     ; 103                 UART1_SYNCMODE_CLOCK_DISABLE,
 106                     ; 104                 UART1_MODE_TX_ENABLE);
 108  0001 4b04          	push	#4
 109  0003 4b80          	push	#128
 110  0005 4b00          	push	#0
 111  0007 4b00          	push	#0
 112  0009 4b00          	push	#0
 113  000b aec200        	ldw	x,#49664
 114  000e 89            	pushw	x
 115  000f ae0001        	ldw	x,#1
 116  0012 89            	pushw	x
 117  0013 cd0000        	call	_UART1_Init
 119  0016 5b09          	addw	sp,#9
 120                     ; 109     printf("myUID:\r\n");
 122  0018 ae0039        	ldw	x,#L33
 123  001b cd0000        	call	_printf
 125                     ; 110     for(i = 0; i < 12; i ++)
 127  001e 4f            	clr	a
 128  001f 6b01          	ld	(OFST+0,sp),a
 129  0021               L53:
 130                     ; 112         printf("%02X ", (uint16_t)*(uint8_t*)(UID_LOCATION + i));
 132  0021 5f            	clrw	x
 133  0022 97            	ld	xl,a
 134  0023 d64865        	ld	a,(18533,x)
 135  0026 ad6b          	call	LC001
 136                     ; 110     for(i = 0; i < 12; i ++)
 138  0028 0c01          	inc	(OFST+0,sp)
 141  002a 7b01          	ld	a,(OFST+0,sp)
 142  002c a10c          	cp	a,#12
 143  002e 25f1          	jrult	L53
 144                     ; 114     printf("\r\n");
 146  0030 ae0030        	ldw	x,#L54
 147  0033 cd0000        	call	_printf
 149                     ; 117     UID_Encryption_Key_Calculate(   (void*)myKey,        //[OUT]计算得到的密钥
 149                     ; 118                                     (void*)UID_LOCATION, //[IN]本芯片的UID地址
 149                     ; 119                                     (void*)myID,         //[IN]用户自定义ID
 149                     ; 120                                     LENGTH_12,           //[IN]密钥长度为12
 149                     ; 121                                     BIG_ENDIA,        //[IN]小端模式
 149                     ; 122                                     ALGORITHM_1);        //[IN]算法1
 151  0036 4b01          	push	#1
 152  0038 4b01          	push	#1
 153  003a 4b0c          	push	#12
 154  003c ae0000        	ldw	x,#_myID
 155  003f 89            	pushw	x
 156  0040 ae4865        	ldw	x,#18533
 157  0043 89            	pushw	x
 158  0044 ae0000        	ldw	x,#_myKey
 159  0047 cd0000        	call	_UID_Encryption_Key_Calculate
 161  004a 5b07          	addw	sp,#7
 162                     ; 123     printf("myKey:\r\n");
 164  004c ae0027        	ldw	x,#L74
 165  004f cd0000        	call	_printf
 167                     ; 124     for(i = 0; i < 12; i ++)
 169  0052 4f            	clr	a
 170  0053 6b01          	ld	(OFST+0,sp),a
 171  0055               L15:
 172                     ; 126         printf("%02X ", (uint16_t)myKey[i]);
 174  0055 5f            	clrw	x
 175  0056 97            	ld	xl,a
 176  0057 e600          	ld	a,(_myKey,x)
 177  0059 ad38          	call	LC001
 178                     ; 124     for(i = 0; i < 12; i ++)
 180  005b 0c01          	inc	(OFST+0,sp)
 183  005d 7b01          	ld	a,(OFST+0,sp)
 184  005f a10c          	cp	a,#12
 185  0061 25f2          	jrult	L15
 186                     ; 128     printf("\r\n");
 188  0063 ae0030        	ldw	x,#L54
 189  0066 cd0000        	call	_printf
 191                     ; 133     checkResult = UID_Encryption_Key_Check( (void*)KEY_LOCATION,  //传入当前芯片中的密钥，此处输入的参数与烧录器配置应当完全一致
 191                     ; 134                                             (void*)UID_LOCATION,  //传入当前芯片UID
 191                     ; 135                                             (void*)myID,          //传入用户自定义ID, 此处输入的参数与烧录器配置应当完全一致
 191                     ; 136                                             LENGTH_12,            //传入密钥长度， 此处输入的参数与烧录器配置应当完全一致
 191                     ; 137                                             BIG_ENDIA,         //传入端序模式， 此处输入的参数与烧录器配置应当完全一致
 191                     ; 138                                             ALGORITHM_1);         //传入算法选择， 此处输入的参数与烧录器配置应当完全一致
 193  0069 4b01          	push	#1
 194  006b 4b01          	push	#1
 195  006d 4b0c          	push	#12
 196  006f ae0000        	ldw	x,#_myID
 197  0072 89            	pushw	x
 198  0073 ae4865        	ldw	x,#18533
 199  0076 89            	pushw	x
 200  0077 ae9f00        	ldw	x,#40704
 201  007a cd0000        	call	_UID_Encryption_Key_Check
 203  007d 5b07          	addw	sp,#7
 204  007f 6b01          	ld	(OFST+0,sp),a
 205                     ; 140     if (checkResult != 0)//如果验证结果为非零值，则验证不通过
 207  0081 2708          	jreq	L75
 208                     ; 142         printf("\r\n密钥非法\r\n");
 210  0083 ae001a        	ldw	x,#L16
 211  0086 cd0000        	call	_printf
 213  0089               L36:
 215  0089 20fe          	jra	L36
 216  008b               L75:
 217                     ; 149     printf("\r\n密钥合法!\r\n");
 219  008b ae000c        	ldw	x,#L76
 220  008e cd0000        	call	_printf
 222  0091               L17:
 224  0091 20fe          	jra	L17
 225  0093               LC001:
 226  0093 5f            	clrw	x
 227  0094 97            	ld	xl,a
 228  0095 89            	pushw	x
 229  0096 ae0033        	ldw	x,#L34
 230  0099 cd0000        	call	_printf
 232  009c 85            	popw	x
 233  009d 81            	ret	
 267                     ; 167 void Delay(uint16_t nCount)
 267                     ; 168 {
 268                     .text:	section	.text,new
 269  0000               _Delay:
 271  0000 89            	pushw	x
 272       00000000      OFST:	set	0
 275  0001 2003          	jra	L511
 276  0003               L311:
 277                     ; 172     nCount--;
 279  0003 5a            	decw	x
 280  0004 1f01          	ldw	(OFST+1,sp),x
 281  0006               L511:
 282                     ; 170   while (nCount != 0)
 284  0006 1e01          	ldw	x,(OFST+1,sp)
 285  0008 26f9          	jrne	L311
 286                     ; 174 }
 289  000a 85            	popw	x
 290  000b 81            	ret	
 326                     ; 183 PUTCHAR_PROTOTYPE
 326                     ; 184 {
 327                     .text:	section	.text,new
 328  0000               _putchar:
 330  0000 88            	push	a
 331       00000000      OFST:	set	0
 334                     ; 186   UART1_SendData8(c);
 336  0001 cd0000        	call	_UART1_SendData8
 339  0004               L141:
 340                     ; 188   while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
 342  0004 ae0080        	ldw	x,#128
 343  0007 cd0000        	call	_UART1_GetFlagStatus
 345  000a 4d            	tnz	a
 346  000b 27f7          	jreq	L141
 347                     ; 190   return (c);
 349  000d 7b01          	ld	a,(OFST+1,sp)
 352  000f 5b01          	addw	sp,#1
 353  0011 81            	ret	
 389                     ; 198 GETCHAR_PROTOTYPE
 389                     ; 199 {
 390                     .text:	section	.text,new
 391  0000               _getchar:
 393  0000 88            	push	a
 394       00000001      OFST:	set	1
 397                     ; 201   char c = 0;
 400  0001               L561:
 401                     ; 206   while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
 403  0001 ae0020        	ldw	x,#32
 404  0004 cd0000        	call	_UART1_GetFlagStatus
 406  0007 4d            	tnz	a
 407  0008 27f7          	jreq	L561
 408                     ; 207     c = UART1_ReceiveData8();
 410  000a cd0000        	call	_UART1_ReceiveData8
 412                     ; 208   return (c);
 416  000d 5b01          	addw	sp,#1
 417  000f 81            	ret	
 452                     ; 221 void assert_failed(uint8_t* file, uint32_t line)
 452                     ; 222 { 
 453                     .text:	section	.text,new
 454  0000               _assert_failed:
 458  0000               L702:
 459  0000 20fe          	jra	L702
 494                     	xdef	_main
 495                     	xdef	_Delay
 496                     	xdef	_myID
 497                     	xdef	_myKey
 498                     	xref	_UID_Encryption_Key_Calculate
 499                     	xref	_UID_Encryption_Key_Check
 500                     	xdef	_putchar
 501                     	xref	_printf
 502                     	xdef	_getchar
 503                     	xdef	_assert_failed
 504                     	xref	_UART1_GetFlagStatus
 505                     	xref	_UART1_SendData8
 506                     	xref	_UART1_ReceiveData8
 507                     	xref	_UART1_Init
 508                     	switch	.const
 509  000c               L76:
 510  000c 0d0ac3dcd4bf  	dc.b	13,10,195,220,212,191
 511  0012 bacfb7a8210d  	dc.b	186,207,183,168,33,13
 512  0018 0a00          	dc.b	10,0
 513  001a               L16:
 514  001a 0d0ac3dcd4bf  	dc.b	13,10,195,220,212,191
 515  0020 b7c7b7a80d0a  	dc.b	183,199,183,168,13,10,0
 516  0027               L74:
 517  0027 6d794b65793a  	dc.b	"myKey:",13
 518  002e 0a00          	dc.b	10,0
 519  0030               L54:
 520  0030 0d0a00        	dc.b	13,10,0
 521  0033               L34:
 522  0033 253032582000  	dc.b	"%02X ",0
 523  0039               L33:
 524  0039 6d795549443a  	dc.b	"myUID:",13
 525  0040 0a00          	dc.b	10,0
 545                     	end
