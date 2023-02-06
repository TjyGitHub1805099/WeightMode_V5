   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
   4                     ; Optimizer V4.3.6 - 29 Nov 2011
  90                     ; 28 static void Algorithm_0(char *pCustomID, char *pUID, char KeyLength, char *pKey)
  90                     ; 29 {
  92                     .text:	section	.text,new
  93  0000               L3_Algorithm_0:
  95  0000 89            	pushw	x
  96  0001 88            	push	a
  97       00000001      OFST:	set	1
 100                     ; 30     pKey[0] = (pUID[0]    ^ (pCustomID[3] & pCustomID[2])) ^ pCustomID[1];
 102  0002 e602          	ld	a,(2,x)
 103  0004 1e02          	ldw	x,(OFST+1,sp)
 104  0006 e403          	and	a,(3,x)
 105  0008 1e06          	ldw	x,(OFST+5,sp)
 106  000a f8            	xor	a,(x)
 107  000b 1e02          	ldw	x,(OFST+1,sp)
 108  000d e801          	xor	a,(1,x)
 109  000f 1e09          	ldw	x,(OFST+8,sp)
 110  0011 f7            	ld	(x),a
 111                     ; 31     pKey[1] = pCustomID[1] | (pUID[2]    ^ (pCustomID[3] & pCustomID[3]));
 113  0012 1e02          	ldw	x,(OFST+1,sp)
 114  0014 e603          	ld	a,(3,x)
 115  0016 1e06          	ldw	x,(OFST+5,sp)
 116  0018 e802          	xor	a,(2,x)
 117  001a 1e02          	ldw	x,(OFST+1,sp)
 118  001c ea01          	or	a,(1,x)
 119  001e 1e09          	ldw	x,(OFST+8,sp)
 120  0020 e701          	ld	(1,x),a
 121                     ; 32     pKey[2] = (pCustomID[2] ^ pCustomID[1]) | (pUID[0]    ^ pCustomID[0]);
 123  0022 1e02          	ldw	x,(OFST+1,sp)
 124  0024 f6            	ld	a,(x)
 125  0025 1e06          	ldw	x,(OFST+5,sp)
 126  0027 f8            	xor	a,(x)
 127  0028 6b01          	ld	(OFST+0,sp),a
 128  002a 1e02          	ldw	x,(OFST+1,sp)
 129  002c e601          	ld	a,(1,x)
 130  002e e802          	xor	a,(2,x)
 131  0030 1e09          	ldw	x,(OFST+8,sp)
 132  0032 1a01          	or	a,(OFST+0,sp)
 133  0034 e702          	ld	(2,x),a
 134                     ; 33     pKey[3] = ((pCustomID[3] & pCustomID[0]) ^ pCustomID[1]) | pUID[2];
 136  0036 1e02          	ldw	x,(OFST+1,sp)
 137  0038 f6            	ld	a,(x)
 138  0039 e403          	and	a,(3,x)
 139  003b e801          	xor	a,(1,x)
 140  003d 1e06          	ldw	x,(OFST+5,sp)
 141  003f ea02          	or	a,(2,x)
 142  0041 1e09          	ldw	x,(OFST+8,sp)
 143  0043 e703          	ld	(3,x),a
 144                     ; 35     if(KeyLength == 8)
 146  0045 7b08          	ld	a,(OFST+7,sp)
 147  0047 a108          	cp	a,#8
 148  0049 264c          	jrne	L54
 149                     ; 37         pKey[4] = (pUID[4]    ^ (pCustomID[7] & pCustomID[5])) ^ pCustomID[5];
 151  004b 1e02          	ldw	x,(OFST+1,sp)
 152  004d e605          	ld	a,(5,x)
 153  004f e407          	and	a,(7,x)
 154  0051 1e06          	ldw	x,(OFST+5,sp)
 155  0053 e804          	xor	a,(4,x)
 156  0055 1e02          	ldw	x,(OFST+1,sp)
 157  0057 e805          	xor	a,(5,x)
 158  0059 1e09          	ldw	x,(OFST+8,sp)
 159  005b e704          	ld	(4,x),a
 160                     ; 38         pKey[5] = pCustomID[5] | (pUID[6]    ^ (pCustomID[4] & pCustomID[7]));
 162  005d 1e02          	ldw	x,(OFST+1,sp)
 163  005f e607          	ld	a,(7,x)
 164  0061 e404          	and	a,(4,x)
 165  0063 1e06          	ldw	x,(OFST+5,sp)
 166  0065 e806          	xor	a,(6,x)
 167  0067 1e02          	ldw	x,(OFST+1,sp)
 168  0069 ea05          	or	a,(5,x)
 169  006b 1e09          	ldw	x,(OFST+8,sp)
 170  006d e705          	ld	(5,x),a
 171                     ; 39         pKey[6] = (pCustomID[6] ^ pCustomID[5]) | (pUID[7]    ^ pCustomID[4]);
 173  006f 1e02          	ldw	x,(OFST+1,sp)
 174  0071 e604          	ld	a,(4,x)
 175  0073 1e06          	ldw	x,(OFST+5,sp)
 176  0075 e807          	xor	a,(7,x)
 177  0077 6b01          	ld	(OFST+0,sp),a
 178  0079 1e02          	ldw	x,(OFST+1,sp)
 179  007b e605          	ld	a,(5,x)
 180  007d e806          	xor	a,(6,x)
 181  007f 1e09          	ldw	x,(OFST+8,sp)
 182  0081 1a01          	or	a,(OFST+0,sp)
 183  0083 e706          	ld	(6,x),a
 184                     ; 40         pKey[7] = ((pCustomID[7] & pCustomID[4]) ^ pCustomID[6]) | pUID[6];
 186  0085 1e02          	ldw	x,(OFST+1,sp)
 187  0087 e604          	ld	a,(4,x)
 188  0089 e407          	and	a,(7,x)
 189  008b e806          	xor	a,(6,x)
 190  008d 1e06          	ldw	x,(OFST+5,sp)
 191  008f ea06          	or	a,(6,x)
 192  0091 1e09          	ldw	x,(OFST+8,sp)
 193  0093 e707          	ld	(7,x),a
 194  0095 7b08          	ld	a,(OFST+7,sp)
 195  0097               L54:
 196                     ; 42     if(KeyLength == 12)
 198  0097 a10c          	cp	a,#12
 199  0099 2703cc0177    	jrne	L74
 200                     ; 44         pKey[0] = (pUID[0]    ^ (pCustomID[1] & pCustomID[2])) ^ pCustomID[3];
 202  009e 1e02          	ldw	x,(OFST+1,sp)
 203  00a0 e602          	ld	a,(2,x)
 204  00a2 e401          	and	a,(1,x)
 205  00a4 1e06          	ldw	x,(OFST+5,sp)
 206  00a6 f8            	xor	a,(x)
 207  00a7 1e02          	ldw	x,(OFST+1,sp)
 208  00a9 e803          	xor	a,(3,x)
 209  00ab 1e09          	ldw	x,(OFST+8,sp)
 210  00ad f7            	ld	(x),a
 211                     ; 45         pKey[1] = pCustomID[1] | (pUID[1]    ^ (pCustomID[3] & pCustomID[4]));
 213  00ae 1e02          	ldw	x,(OFST+1,sp)
 214  00b0 e604          	ld	a,(4,x)
 215  00b2 e403          	and	a,(3,x)
 216  00b4 1e06          	ldw	x,(OFST+5,sp)
 217  00b6 e801          	xor	a,(1,x)
 218  00b8 1e02          	ldw	x,(OFST+1,sp)
 219  00ba ea01          	or	a,(1,x)
 220  00bc 1e09          	ldw	x,(OFST+8,sp)
 221  00be e701          	ld	(1,x),a
 222                     ; 46         pKey[2] = (pCustomID[2] ^ pCustomID[1]) | (pUID[2]    ^ pCustomID[5]);
 224  00c0 1e02          	ldw	x,(OFST+1,sp)
 225  00c2 e605          	ld	a,(5,x)
 226  00c4 1e06          	ldw	x,(OFST+5,sp)
 227  00c6 e802          	xor	a,(2,x)
 228  00c8 6b01          	ld	(OFST+0,sp),a
 229  00ca 1e02          	ldw	x,(OFST+1,sp)
 230  00cc e601          	ld	a,(1,x)
 231  00ce e802          	xor	a,(2,x)
 232  00d0 1e09          	ldw	x,(OFST+8,sp)
 233  00d2 1a01          	or	a,(OFST+0,sp)
 234  00d4 e702          	ld	(2,x),a
 235                     ; 47         pKey[3] = ((pCustomID[3] & pCustomID[1]) ^ pCustomID[5]) | pUID[3];
 237  00d6 1e02          	ldw	x,(OFST+1,sp)
 238  00d8 e601          	ld	a,(1,x)
 239  00da e403          	and	a,(3,x)
 240  00dc e805          	xor	a,(5,x)
 241  00de 1e06          	ldw	x,(OFST+5,sp)
 242  00e0 ea03          	or	a,(3,x)
 243  00e2 1e09          	ldw	x,(OFST+8,sp)
 244  00e4 e703          	ld	(3,x),a
 245                     ; 48         pKey[4] = (pUID[4]    ^ (pCustomID[5] & pCustomID[6])) ^ pCustomID[7];
 247  00e6 1e02          	ldw	x,(OFST+1,sp)
 248  00e8 e606          	ld	a,(6,x)
 249  00ea e405          	and	a,(5,x)
 250  00ec 1e06          	ldw	x,(OFST+5,sp)
 251  00ee e804          	xor	a,(4,x)
 252  00f0 1e02          	ldw	x,(OFST+1,sp)
 253  00f2 e807          	xor	a,(7,x)
 254  00f4 1e09          	ldw	x,(OFST+8,sp)
 255  00f6 e704          	ld	(4,x),a
 256                     ; 49         pKey[5] = pCustomID[5] | (pUID[5]    ^ (pCustomID[7] & pCustomID[8]));
 258  00f8 1e02          	ldw	x,(OFST+1,sp)
 259  00fa e608          	ld	a,(8,x)
 260  00fc e407          	and	a,(7,x)
 261  00fe 1e06          	ldw	x,(OFST+5,sp)
 262  0100 e805          	xor	a,(5,x)
 263  0102 1e02          	ldw	x,(OFST+1,sp)
 264  0104 ea05          	or	a,(5,x)
 265  0106 1e09          	ldw	x,(OFST+8,sp)
 266  0108 e705          	ld	(5,x),a
 267                     ; 50         pKey[6] = (pCustomID[6] ^ pCustomID[7]) | (pUID[6]    ^ pCustomID[9]);
 269  010a 1e02          	ldw	x,(OFST+1,sp)
 270  010c e609          	ld	a,(9,x)
 271  010e 1e06          	ldw	x,(OFST+5,sp)
 272  0110 e806          	xor	a,(6,x)
 273  0112 6b01          	ld	(OFST+0,sp),a
 274  0114 1e02          	ldw	x,(OFST+1,sp)
 275  0116 e607          	ld	a,(7,x)
 276  0118 e806          	xor	a,(6,x)
 277  011a 1e09          	ldw	x,(OFST+8,sp)
 278  011c 1a01          	or	a,(OFST+0,sp)
 279  011e e706          	ld	(6,x),a
 280                     ; 51         pKey[7] = ((pCustomID[7] & pCustomID[8]) ^ pCustomID[9]) | pUID[7];
 282  0120 1e02          	ldw	x,(OFST+1,sp)
 283  0122 e608          	ld	a,(8,x)
 284  0124 e407          	and	a,(7,x)
 285  0126 e809          	xor	a,(9,x)
 286  0128 1e06          	ldw	x,(OFST+5,sp)
 287  012a ea07          	or	a,(7,x)
 288  012c 1e09          	ldw	x,(OFST+8,sp)
 289  012e e707          	ld	(7,x),a
 290                     ; 52         pKey[8] = (pUID[8]    ^ (pCustomID[9] & pCustomID[10])) ^ pCustomID[11];
 292  0130 1e02          	ldw	x,(OFST+1,sp)
 293  0132 e60a          	ld	a,(10,x)
 294  0134 e409          	and	a,(9,x)
 295  0136 1e06          	ldw	x,(OFST+5,sp)
 296  0138 e808          	xor	a,(8,x)
 297  013a 1e02          	ldw	x,(OFST+1,sp)
 298  013c e80b          	xor	a,(11,x)
 299  013e 1e09          	ldw	x,(OFST+8,sp)
 300  0140 e708          	ld	(8,x),a
 301                     ; 53         pKey[9] = pCustomID[9] | (pUID[9]    ^ (pCustomID[11] & pCustomID[0]));
 303  0142 1e02          	ldw	x,(OFST+1,sp)
 304  0144 f6            	ld	a,(x)
 305  0145 e40b          	and	a,(11,x)
 306  0147 1e06          	ldw	x,(OFST+5,sp)
 307  0149 e809          	xor	a,(9,x)
 308  014b 1e02          	ldw	x,(OFST+1,sp)
 309  014d ea09          	or	a,(9,x)
 310  014f 1e09          	ldw	x,(OFST+8,sp)
 311  0151 e709          	ld	(9,x),a
 312                     ; 54         pKey[10]= (pCustomID[10] ^ pCustomID[11]) | (pUID[0]   ^ pCustomID[1]);
 314  0153 1e02          	ldw	x,(OFST+1,sp)
 315  0155 e601          	ld	a,(1,x)
 316  0157 1e06          	ldw	x,(OFST+5,sp)
 317  0159 f8            	xor	a,(x)
 318  015a 6b01          	ld	(OFST+0,sp),a
 319  015c 1e02          	ldw	x,(OFST+1,sp)
 320  015e e60b          	ld	a,(11,x)
 321  0160 e80a          	xor	a,(10,x)
 322  0162 1e09          	ldw	x,(OFST+8,sp)
 323  0164 1a01          	or	a,(OFST+0,sp)
 324  0166 e70a          	ld	(10,x),a
 325                     ; 55         pKey[11]= ((pCustomID[11] & pCustomID[0]) ^ pCustomID[1]) | pUID[2];
 327  0168 1e02          	ldw	x,(OFST+1,sp)
 328  016a f6            	ld	a,(x)
 329  016b e40b          	and	a,(11,x)
 330  016d e801          	xor	a,(1,x)
 331  016f 1e06          	ldw	x,(OFST+5,sp)
 332  0171 ea02          	or	a,(2,x)
 333  0173 1e09          	ldw	x,(OFST+8,sp)
 334  0175 e70b          	ld	(11,x),a
 335  0177               L74:
 336                     ; 58 }
 339  0177 5b03          	addw	sp,#3
 340  0179 81            	ret	
 404                     ; 63 static void Algorithm_1(char *pCustomID, char *pUID, char KeyLength, char *pKey)
 404                     ; 64 {
 405                     .text:	section	.text,new
 406  0000               L15_Algorithm_1:
 408  0000 89            	pushw	x
 409       00000000      OFST:	set	0
 412                     ; 65     pKey[0] = ((pUID[0]    ^ pCustomID[1]) ^ pCustomID[2]) ^ pCustomID[3];
 414  0001 e601          	ld	a,(1,x)
 415  0003 1e05          	ldw	x,(OFST+5,sp)
 416  0005 f8            	xor	a,(x)
 417  0006 1e01          	ldw	x,(OFST+1,sp)
 418  0008 e802          	xor	a,(2,x)
 419  000a e803          	xor	a,(3,x)
 420  000c 1e08          	ldw	x,(OFST+8,sp)
 421  000e f7            	ld	(x),a
 422                     ; 66     pKey[1] = ((pCustomID[1] ^ pUID[1])    ^ pCustomID[3]) ^ pCustomID[0];
 424  000f 1e05          	ldw	x,(OFST+5,sp)
 425  0011 e601          	ld	a,(1,x)
 426  0013 1e01          	ldw	x,(OFST+1,sp)
 427  0015 e801          	xor	a,(1,x)
 428  0017 e803          	xor	a,(3,x)
 429  0019 f8            	xor	a,(x)
 430  001a 1e08          	ldw	x,(OFST+8,sp)
 431  001c e701          	ld	(1,x),a
 432                     ; 67     pKey[2] = ((pCustomID[2] ^ pCustomID[1]) ^ pUID[2])    ^ pCustomID[3];
 434  001e 1e01          	ldw	x,(OFST+1,sp)
 435  0020 e601          	ld	a,(1,x)
 436  0022 e802          	xor	a,(2,x)
 437  0024 1e05          	ldw	x,(OFST+5,sp)
 438  0026 e802          	xor	a,(2,x)
 439  0028 1e01          	ldw	x,(OFST+1,sp)
 440  002a e803          	xor	a,(3,x)
 441  002c 1e08          	ldw	x,(OFST+8,sp)
 442  002e e702          	ld	(2,x),a
 443                     ; 68     pKey[3] = ((pCustomID[3] ^ pCustomID[1]) ^ pCustomID[0]) ^ pUID[3];
 445  0030 1e01          	ldw	x,(OFST+1,sp)
 446  0032 e601          	ld	a,(1,x)
 447  0034 e803          	xor	a,(3,x)
 448  0036 f8            	xor	a,(x)
 449  0037 1e05          	ldw	x,(OFST+5,sp)
 450  0039 e803          	xor	a,(3,x)
 451  003b 1e08          	ldw	x,(OFST+8,sp)
 452  003d e703          	ld	(3,x),a
 453                     ; 70     if(KeyLength == 8)
 455  003f 7b07          	ld	a,(OFST+7,sp)
 456  0041 a108          	cp	a,#8
 457  0043 2646          	jrne	L501
 458                     ; 72         pKey[4] = ((pUID[4]    ^ pCustomID[5]) ^ pCustomID[6]) ^ pCustomID[7];
 460  0045 1e01          	ldw	x,(OFST+1,sp)
 461  0047 e605          	ld	a,(5,x)
 462  0049 1e05          	ldw	x,(OFST+5,sp)
 463  004b e804          	xor	a,(4,x)
 464  004d 1e01          	ldw	x,(OFST+1,sp)
 465  004f e806          	xor	a,(6,x)
 466  0051 e807          	xor	a,(7,x)
 467  0053 1e08          	ldw	x,(OFST+8,sp)
 468  0055 e704          	ld	(4,x),a
 469                     ; 73         pKey[5] = ((pCustomID[5] ^ pUID[5])    ^ pCustomID[7]) ^ pCustomID[2];
 471  0057 1e05          	ldw	x,(OFST+5,sp)
 472  0059 e605          	ld	a,(5,x)
 473  005b 1e01          	ldw	x,(OFST+1,sp)
 474  005d e805          	xor	a,(5,x)
 475  005f e807          	xor	a,(7,x)
 476  0061 e802          	xor	a,(2,x)
 477  0063 1e08          	ldw	x,(OFST+8,sp)
 478  0065 e705          	ld	(5,x),a
 479                     ; 74         pKey[6] = ((pCustomID[6] ^ pCustomID[7]) ^ pUID[6])    ^ pCustomID[3];
 481  0067 1e01          	ldw	x,(OFST+1,sp)
 482  0069 e607          	ld	a,(7,x)
 483  006b e806          	xor	a,(6,x)
 484  006d 1e05          	ldw	x,(OFST+5,sp)
 485  006f e806          	xor	a,(6,x)
 486  0071 1e01          	ldw	x,(OFST+1,sp)
 487  0073 e803          	xor	a,(3,x)
 488  0075 1e08          	ldw	x,(OFST+8,sp)
 489  0077 e706          	ld	(6,x),a
 490                     ; 75         pKey[7] = ((pCustomID[7] ^ pCustomID[4]) ^ pCustomID[5]) ^ pUID[4];
 492  0079 1e01          	ldw	x,(OFST+1,sp)
 493  007b e604          	ld	a,(4,x)
 494  007d e807          	xor	a,(7,x)
 495  007f e805          	xor	a,(5,x)
 496  0081 1e05          	ldw	x,(OFST+5,sp)
 497  0083 e804          	xor	a,(4,x)
 498  0085 1e08          	ldw	x,(OFST+8,sp)
 499  0087 e707          	ld	(7,x),a
 500  0089 7b07          	ld	a,(OFST+7,sp)
 501  008b               L501:
 502                     ; 77     if(KeyLength == 12)
 504  008b a10c          	cp	a,#12
 505  008d 2703cc0159    	jrne	L701
 506                     ; 79         pKey[0] = ((pUID[0]    ^ pCustomID[1]) ^ pCustomID[2]) ^ pCustomID[3];
 508  0092 1e01          	ldw	x,(OFST+1,sp)
 509  0094 e601          	ld	a,(1,x)
 510  0096 1e05          	ldw	x,(OFST+5,sp)
 511  0098 f8            	xor	a,(x)
 512  0099 1e01          	ldw	x,(OFST+1,sp)
 513  009b e802          	xor	a,(2,x)
 514  009d e803          	xor	a,(3,x)
 515  009f 1e08          	ldw	x,(OFST+8,sp)
 516  00a1 f7            	ld	(x),a
 517                     ; 80         pKey[1] = ((pCustomID[1] ^ pUID[1])    ^ pCustomID[3]) ^ pCustomID[4];
 519  00a2 1e05          	ldw	x,(OFST+5,sp)
 520  00a4 e601          	ld	a,(1,x)
 521  00a6 1e01          	ldw	x,(OFST+1,sp)
 522  00a8 e801          	xor	a,(1,x)
 523  00aa e803          	xor	a,(3,x)
 524  00ac e804          	xor	a,(4,x)
 525  00ae 1e08          	ldw	x,(OFST+8,sp)
 526  00b0 e701          	ld	(1,x),a
 527                     ; 81         pKey[2] = ((pCustomID[2] ^ pCustomID[1]) ^ pUID[2])    ^ pCustomID[5];
 529  00b2 1e01          	ldw	x,(OFST+1,sp)
 530  00b4 e601          	ld	a,(1,x)
 531  00b6 e802          	xor	a,(2,x)
 532  00b8 1e05          	ldw	x,(OFST+5,sp)
 533  00ba e802          	xor	a,(2,x)
 534  00bc 1e01          	ldw	x,(OFST+1,sp)
 535  00be e805          	xor	a,(5,x)
 536  00c0 1e08          	ldw	x,(OFST+8,sp)
 537  00c2 e702          	ld	(2,x),a
 538                     ; 82         pKey[3] = ((pCustomID[3] ^ pCustomID[1]) ^ pCustomID[5]) ^ pUID[3];
 540  00c4 1e01          	ldw	x,(OFST+1,sp)
 541  00c6 e601          	ld	a,(1,x)
 542  00c8 e803          	xor	a,(3,x)
 543  00ca e805          	xor	a,(5,x)
 544  00cc 1e05          	ldw	x,(OFST+5,sp)
 545  00ce e803          	xor	a,(3,x)
 546  00d0 1e08          	ldw	x,(OFST+8,sp)
 547  00d2 e703          	ld	(3,x),a
 548                     ; 83         pKey[4] = ((pUID[4]    ^ pCustomID[5]) ^ pCustomID[6]) ^ pCustomID[7];
 550  00d4 1e01          	ldw	x,(OFST+1,sp)
 551  00d6 e605          	ld	a,(5,x)
 552  00d8 1e05          	ldw	x,(OFST+5,sp)
 553  00da e804          	xor	a,(4,x)
 554  00dc 1e01          	ldw	x,(OFST+1,sp)
 555  00de e806          	xor	a,(6,x)
 556  00e0 e807          	xor	a,(7,x)
 557  00e2 1e08          	ldw	x,(OFST+8,sp)
 558  00e4 e704          	ld	(4,x),a
 559                     ; 84         pKey[5] = ((pCustomID[5] ^ pUID[5])    ^ pCustomID[7]) ^ pCustomID[8];
 561  00e6 1e05          	ldw	x,(OFST+5,sp)
 562  00e8 e605          	ld	a,(5,x)
 563  00ea 1e01          	ldw	x,(OFST+1,sp)
 564  00ec e805          	xor	a,(5,x)
 565  00ee e807          	xor	a,(7,x)
 566  00f0 e808          	xor	a,(8,x)
 567  00f2 1e08          	ldw	x,(OFST+8,sp)
 568  00f4 e705          	ld	(5,x),a
 569                     ; 85         pKey[6] = ((pCustomID[6] ^ pCustomID[7]) ^ pUID[6])    ^ pCustomID[9];
 571  00f6 1e01          	ldw	x,(OFST+1,sp)
 572  00f8 e607          	ld	a,(7,x)
 573  00fa e806          	xor	a,(6,x)
 574  00fc 1e05          	ldw	x,(OFST+5,sp)
 575  00fe e806          	xor	a,(6,x)
 576  0100 1e01          	ldw	x,(OFST+1,sp)
 577  0102 e809          	xor	a,(9,x)
 578  0104 1e08          	ldw	x,(OFST+8,sp)
 579  0106 e706          	ld	(6,x),a
 580                     ; 86         pKey[7] = ((pCustomID[7] ^ pCustomID[8]) ^ pCustomID[9]) ^ pUID[7];
 582  0108 1e01          	ldw	x,(OFST+1,sp)
 583  010a e608          	ld	a,(8,x)
 584  010c e807          	xor	a,(7,x)
 585  010e e809          	xor	a,(9,x)
 586  0110 1e05          	ldw	x,(OFST+5,sp)
 587  0112 e807          	xor	a,(7,x)
 588  0114 1e08          	ldw	x,(OFST+8,sp)
 589  0116 e707          	ld	(7,x),a
 590                     ; 87         pKey[8] = ((pUID[8]    ^ pCustomID[9]) ^ pCustomID[10]) ^ pCustomID[11];
 592  0118 1e01          	ldw	x,(OFST+1,sp)
 593  011a e609          	ld	a,(9,x)
 594  011c 1e05          	ldw	x,(OFST+5,sp)
 595  011e e808          	xor	a,(8,x)
 596  0120 1e01          	ldw	x,(OFST+1,sp)
 597  0122 e80a          	xor	a,(10,x)
 598  0124 e80b          	xor	a,(11,x)
 599  0126 1e08          	ldw	x,(OFST+8,sp)
 600  0128 e708          	ld	(8,x),a
 601                     ; 88         pKey[9] = ((pCustomID[9] ^ pUID[9])    ^ pCustomID[11]) ^ pCustomID[0];
 603  012a 1e05          	ldw	x,(OFST+5,sp)
 604  012c e609          	ld	a,(9,x)
 605  012e 1e01          	ldw	x,(OFST+1,sp)
 606  0130 e809          	xor	a,(9,x)
 607  0132 e80b          	xor	a,(11,x)
 608  0134 f8            	xor	a,(x)
 609  0135 1e08          	ldw	x,(OFST+8,sp)
 610  0137 e709          	ld	(9,x),a
 611                     ; 89         pKey[10]= ((pCustomID[10] ^ pCustomID[11]) ^ pUID[0])   ^ pCustomID[1];
 613  0139 1e01          	ldw	x,(OFST+1,sp)
 614  013b e60b          	ld	a,(11,x)
 615  013d e80a          	xor	a,(10,x)
 616  013f 1e05          	ldw	x,(OFST+5,sp)
 617  0141 f8            	xor	a,(x)
 618  0142 1e01          	ldw	x,(OFST+1,sp)
 619  0144 e801          	xor	a,(1,x)
 620  0146 1e08          	ldw	x,(OFST+8,sp)
 621  0148 e70a          	ld	(10,x),a
 622                     ; 90         pKey[11]= ((pCustomID[11] ^ pCustomID[0]) ^ pCustomID[1]) ^ pUID[2];
 624  014a 1e01          	ldw	x,(OFST+1,sp)
 625  014c f6            	ld	a,(x)
 626  014d e80b          	xor	a,(11,x)
 627  014f e801          	xor	a,(1,x)
 628  0151 1e05          	ldw	x,(OFST+5,sp)
 629  0153 e802          	xor	a,(2,x)
 630  0155 1e08          	ldw	x,(OFST+8,sp)
 631  0157 e70b          	ld	(11,x),a
 632  0159               L701:
 633                     ; 92 }
 636  0159 85            	popw	x
 637  015a 81            	ret	
 701                     ; 96 static void Algorithm_2(char *pCustomID, char *pUID, char KeyLength, char *pKey)
 701                     ; 97 {
 702                     .text:	section	.text,new
 703  0000               L111_Algorithm_2:
 705  0000 89            	pushw	x
 706  0001 88            	push	a
 707       00000001      OFST:	set	1
 710                     ; 98     pKey[0] = ((pUID[0]    & pCustomID[1]) ^ pCustomID[2]) ^ pCustomID[3];
 712  0002 e601          	ld	a,(1,x)
 713  0004 1e06          	ldw	x,(OFST+5,sp)
 714  0006 f4            	and	a,(x)
 715  0007 1e02          	ldw	x,(OFST+1,sp)
 716  0009 e802          	xor	a,(2,x)
 717  000b e803          	xor	a,(3,x)
 718  000d 1e09          	ldw	x,(OFST+8,sp)
 719  000f f7            	ld	(x),a
 720                     ; 99     pKey[1] = (pCustomID[1] ^ (pUID[1]    & pCustomID[3])) ^ pCustomID[0];
 722  0010 1e02          	ldw	x,(OFST+1,sp)
 723  0012 e603          	ld	a,(3,x)
 724  0014 1e06          	ldw	x,(OFST+5,sp)
 725  0016 e401          	and	a,(1,x)
 726  0018 1e02          	ldw	x,(OFST+1,sp)
 727  001a e801          	xor	a,(1,x)
 728  001c f8            	xor	a,(x)
 729  001d 1e09          	ldw	x,(OFST+8,sp)
 730  001f e701          	ld	(1,x),a
 731                     ; 100     pKey[2] = (pCustomID[2] | (pCustomID[1] ^ pUID[2]))    | pCustomID[3];
 733  0021 1e06          	ldw	x,(OFST+5,sp)
 734  0023 e602          	ld	a,(2,x)
 735  0025 1e02          	ldw	x,(OFST+1,sp)
 736  0027 e801          	xor	a,(1,x)
 737  0029 ea02          	or	a,(2,x)
 738  002b ea03          	or	a,(3,x)
 739  002d 1e09          	ldw	x,(OFST+8,sp)
 740  002f e702          	ld	(2,x),a
 741                     ; 101     pKey[3] = (pCustomID[3] ^ pCustomID[1]) | (pCustomID[0] ^ pUID[3]);
 743  0031 1e06          	ldw	x,(OFST+5,sp)
 744  0033 e603          	ld	a,(3,x)
 745  0035 1e02          	ldw	x,(OFST+1,sp)
 746  0037 f8            	xor	a,(x)
 747  0038 6b01          	ld	(OFST+0,sp),a
 748  003a e601          	ld	a,(1,x)
 749  003c e803          	xor	a,(3,x)
 750  003e 1e09          	ldw	x,(OFST+8,sp)
 751  0040 1a01          	or	a,(OFST+0,sp)
 752  0042 e703          	ld	(3,x),a
 753                     ; 103     if(KeyLength == 8)  
 755  0044 7b08          	ld	a,(OFST+7,sp)
 756  0046 a108          	cp	a,#8
 757  0048 264c          	jrne	L541
 758                     ; 105         pKey[4] = (pUID[4]    ^ (pCustomID[5] & pCustomID[6])) ^ pCustomID[7];
 760  004a 1e02          	ldw	x,(OFST+1,sp)
 761  004c e606          	ld	a,(6,x)
 762  004e e405          	and	a,(5,x)
 763  0050 1e06          	ldw	x,(OFST+5,sp)
 764  0052 e804          	xor	a,(4,x)
 765  0054 1e02          	ldw	x,(OFST+1,sp)
 766  0056 e807          	xor	a,(7,x)
 767  0058 1e09          	ldw	x,(OFST+8,sp)
 768  005a e704          	ld	(4,x),a
 769                     ; 106         pKey[5] = pCustomID[5] | (pUID[5]    ^ (pCustomID[7] & pCustomID[2]));
 771  005c 1e02          	ldw	x,(OFST+1,sp)
 772  005e e602          	ld	a,(2,x)
 773  0060 e407          	and	a,(7,x)
 774  0062 1e06          	ldw	x,(OFST+5,sp)
 775  0064 e805          	xor	a,(5,x)
 776  0066 1e02          	ldw	x,(OFST+1,sp)
 777  0068 ea05          	or	a,(5,x)
 778  006a 1e09          	ldw	x,(OFST+8,sp)
 779  006c e705          	ld	(5,x),a
 780                     ; 107         pKey[6] = ((pCustomID[6] & pCustomID[7]) ^ pUID[6])    | pCustomID[3];
 782  006e 1e02          	ldw	x,(OFST+1,sp)
 783  0070 e607          	ld	a,(7,x)
 784  0072 e406          	and	a,(6,x)
 785  0074 1e06          	ldw	x,(OFST+5,sp)
 786  0076 e806          	xor	a,(6,x)
 787  0078 1e02          	ldw	x,(OFST+1,sp)
 788  007a ea03          	or	a,(3,x)
 789  007c 1e09          	ldw	x,(OFST+8,sp)
 790  007e e706          	ld	(6,x),a
 791                     ; 108         pKey[7] = (pCustomID[7] ^ pCustomID[4]) | (pCustomID[1] ^ pUID[2]);
 793  0080 1e06          	ldw	x,(OFST+5,sp)
 794  0082 e602          	ld	a,(2,x)
 795  0084 1e02          	ldw	x,(OFST+1,sp)
 796  0086 e801          	xor	a,(1,x)
 797  0088 6b01          	ld	(OFST+0,sp),a
 798  008a e604          	ld	a,(4,x)
 799  008c e807          	xor	a,(7,x)
 800  008e 1e09          	ldw	x,(OFST+8,sp)
 801  0090 1a01          	or	a,(OFST+0,sp)
 802  0092 e707          	ld	(7,x),a
 803  0094 7b08          	ld	a,(OFST+7,sp)
 804  0096               L541:
 805                     ; 110     if(KeyLength == 12)
 807  0096 a10c          	cp	a,#12
 808  0098 2703cc0174    	jrne	L741
 809                     ; 112         pKey[0] = ((pUID[0]    & pCustomID[1]) ^ pCustomID[2]) ^ pCustomID[3];
 811  009d 1e02          	ldw	x,(OFST+1,sp)
 812  009f e601          	ld	a,(1,x)
 813  00a1 1e06          	ldw	x,(OFST+5,sp)
 814  00a3 f4            	and	a,(x)
 815  00a4 1e02          	ldw	x,(OFST+1,sp)
 816  00a6 e802          	xor	a,(2,x)
 817  00a8 e803          	xor	a,(3,x)
 818  00aa 1e09          	ldw	x,(OFST+8,sp)
 819  00ac f7            	ld	(x),a
 820                     ; 113         pKey[1] = (pCustomID[1] ^ (pUID[1]    & pCustomID[3])) ^ pCustomID[4];
 822  00ad 1e02          	ldw	x,(OFST+1,sp)
 823  00af e603          	ld	a,(3,x)
 824  00b1 1e06          	ldw	x,(OFST+5,sp)
 825  00b3 e401          	and	a,(1,x)
 826  00b5 1e02          	ldw	x,(OFST+1,sp)
 827  00b7 e801          	xor	a,(1,x)
 828  00b9 e804          	xor	a,(4,x)
 829  00bb 1e09          	ldw	x,(OFST+8,sp)
 830  00bd e701          	ld	(1,x),a
 831                     ; 114         pKey[2] = (pCustomID[2] | (pCustomID[1] ^ pUID[2]))    | pCustomID[5];
 833  00bf 1e06          	ldw	x,(OFST+5,sp)
 834  00c1 e602          	ld	a,(2,x)
 835  00c3 1e02          	ldw	x,(OFST+1,sp)
 836  00c5 e801          	xor	a,(1,x)
 837  00c7 ea02          	or	a,(2,x)
 838  00c9 ea05          	or	a,(5,x)
 839  00cb 1e09          	ldw	x,(OFST+8,sp)
 840  00cd e702          	ld	(2,x),a
 841                     ; 115         pKey[3] = (pCustomID[3] ^ pCustomID[1]) | (pCustomID[5] ^ pUID[3]);
 843  00cf 1e06          	ldw	x,(OFST+5,sp)
 844  00d1 e603          	ld	a,(3,x)
 845  00d3 1e02          	ldw	x,(OFST+1,sp)
 846  00d5 e805          	xor	a,(5,x)
 847  00d7 6b01          	ld	(OFST+0,sp),a
 848  00d9 e601          	ld	a,(1,x)
 849  00db e803          	xor	a,(3,x)
 850  00dd 1e09          	ldw	x,(OFST+8,sp)
 851  00df 1a01          	or	a,(OFST+0,sp)
 852  00e1 e703          	ld	(3,x),a
 853                     ; 116         pKey[4] = (pUID[4]    ^ (pCustomID[5] & pCustomID[6])) ^ pCustomID[7];
 855  00e3 1e02          	ldw	x,(OFST+1,sp)
 856  00e5 e606          	ld	a,(6,x)
 857  00e7 e405          	and	a,(5,x)
 858  00e9 1e06          	ldw	x,(OFST+5,sp)
 859  00eb e804          	xor	a,(4,x)
 860  00ed 1e02          	ldw	x,(OFST+1,sp)
 861  00ef e807          	xor	a,(7,x)
 862  00f1 1e09          	ldw	x,(OFST+8,sp)
 863  00f3 e704          	ld	(4,x),a
 864                     ; 117         pKey[5] = pCustomID[5] | (pUID[5]    ^ (pCustomID[7] & pCustomID[8]));
 866  00f5 1e02          	ldw	x,(OFST+1,sp)
 867  00f7 e608          	ld	a,(8,x)
 868  00f9 e407          	and	a,(7,x)
 869  00fb 1e06          	ldw	x,(OFST+5,sp)
 870  00fd e805          	xor	a,(5,x)
 871  00ff 1e02          	ldw	x,(OFST+1,sp)
 872  0101 ea05          	or	a,(5,x)
 873  0103 1e09          	ldw	x,(OFST+8,sp)
 874  0105 e705          	ld	(5,x),a
 875                     ; 118         pKey[6] = ((pCustomID[6] & pCustomID[7]) ^ pUID[6])    | pCustomID[9];
 877  0107 1e02          	ldw	x,(OFST+1,sp)
 878  0109 e607          	ld	a,(7,x)
 879  010b e406          	and	a,(6,x)
 880  010d 1e06          	ldw	x,(OFST+5,sp)
 881  010f e806          	xor	a,(6,x)
 882  0111 1e02          	ldw	x,(OFST+1,sp)
 883  0113 ea09          	or	a,(9,x)
 884  0115 1e09          	ldw	x,(OFST+8,sp)
 885  0117 e706          	ld	(6,x),a
 886                     ; 119         pKey[7] = (pCustomID[7] ^ pCustomID[8]) | (pCustomID[9] ^ pUID[7]);
 888  0119 1e06          	ldw	x,(OFST+5,sp)
 889  011b e607          	ld	a,(7,x)
 890  011d 1e02          	ldw	x,(OFST+1,sp)
 891  011f e809          	xor	a,(9,x)
 892  0121 6b01          	ld	(OFST+0,sp),a
 893  0123 e608          	ld	a,(8,x)
 894  0125 e807          	xor	a,(7,x)
 895  0127 1e09          	ldw	x,(OFST+8,sp)
 896  0129 1a01          	or	a,(OFST+0,sp)
 897  012b e707          	ld	(7,x),a
 898                     ; 120         pKey[8] = (pUID[8]    ^ (pCustomID[9] & pCustomID[10])) ^ pCustomID[11];
 900  012d 1e02          	ldw	x,(OFST+1,sp)
 901  012f e60a          	ld	a,(10,x)
 902  0131 e409          	and	a,(9,x)
 903  0133 1e06          	ldw	x,(OFST+5,sp)
 904  0135 e808          	xor	a,(8,x)
 905  0137 1e02          	ldw	x,(OFST+1,sp)
 906  0139 e80b          	xor	a,(11,x)
 907  013b 1e09          	ldw	x,(OFST+8,sp)
 908  013d e708          	ld	(8,x),a
 909                     ; 121         pKey[9] = (pCustomID[9] ^ pUID[9])    | (pCustomID[11] & pCustomID[0]);
 911  013f 1e02          	ldw	x,(OFST+1,sp)
 912  0141 f6            	ld	a,(x)
 913  0142 e40b          	and	a,(11,x)
 914  0144 6b01          	ld	(OFST+0,sp),a
 915  0146 1e06          	ldw	x,(OFST+5,sp)
 916  0148 e609          	ld	a,(9,x)
 917  014a 1e02          	ldw	x,(OFST+1,sp)
 918  014c e809          	xor	a,(9,x)
 919  014e 1e09          	ldw	x,(OFST+8,sp)
 920  0150 1a01          	or	a,(OFST+0,sp)
 921  0152 e709          	ld	(9,x),a
 922                     ; 122         pKey[10]= ((pCustomID[10] & pCustomID[11]) ^ pUID[0])   ^ pCustomID[1];
 924  0154 1e02          	ldw	x,(OFST+1,sp)
 925  0156 e60b          	ld	a,(11,x)
 926  0158 e40a          	and	a,(10,x)
 927  015a 1e06          	ldw	x,(OFST+5,sp)
 928  015c f8            	xor	a,(x)
 929  015d 1e02          	ldw	x,(OFST+1,sp)
 930  015f e801          	xor	a,(1,x)
 931  0161 1e09          	ldw	x,(OFST+8,sp)
 932  0163 e70a          	ld	(10,x),a
 933                     ; 123         pKey[11]= (pCustomID[11] ^ (pCustomID[0] & pCustomID[1])) ^ pUID[2];
 935  0165 1e02          	ldw	x,(OFST+1,sp)
 936  0167 e601          	ld	a,(1,x)
 937  0169 f4            	and	a,(x)
 938  016a e80b          	xor	a,(11,x)
 939  016c 1e06          	ldw	x,(OFST+5,sp)
 940  016e e802          	xor	a,(2,x)
 941  0170 1e09          	ldw	x,(OFST+8,sp)
 942  0172 e70b          	ld	(11,x),a
 943  0174               L741:
 944                     ; 125 }
 947  0174 5b03          	addw	sp,#3
 948  0176 81            	ret	
1012                     ; 128 static void Algorithm_3(char *pCustomID, char *pUID, char KeyLength, char *pKey)
1012                     ; 129 {
1013                     .text:	section	.text,new
1014  0000               L151_Algorithm_3:
1016  0000 89            	pushw	x
1017  0001 88            	push	a
1018       00000001      OFST:	set	1
1021                     ; 130     pKey[0] = ((pUID[0] & pCustomID[1]) ^ pCustomID[2]) ^ pCustomID[3];
1023  0002 e601          	ld	a,(1,x)
1024  0004 1e06          	ldw	x,(OFST+5,sp)
1025  0006 f4            	and	a,(x)
1026  0007 1e02          	ldw	x,(OFST+1,sp)
1027  0009 e802          	xor	a,(2,x)
1028  000b e803          	xor	a,(3,x)
1029  000d 1e09          	ldw	x,(OFST+8,sp)
1030  000f f7            	ld	(x),a
1031                     ; 131     pKey[1] = (pUID[1] ^ (pCustomID[2] & pCustomID[3])) ^ pCustomID[4];
1033  0010 1e02          	ldw	x,(OFST+1,sp)
1034  0012 e603          	ld	a,(3,x)
1035  0014 e402          	and	a,(2,x)
1036  0016 1e06          	ldw	x,(OFST+5,sp)
1037  0018 e801          	xor	a,(1,x)
1038  001a 1e02          	ldw	x,(OFST+1,sp)
1039  001c e804          	xor	a,(4,x)
1040  001e 1e09          	ldw	x,(OFST+8,sp)
1041  0020 e701          	ld	(1,x),a
1042                     ; 132     pKey[2] = (pUID[2] | (pCustomID[3] ^ pCustomID[4])) | pCustomID[5];
1044  0022 1e02          	ldw	x,(OFST+1,sp)
1045  0024 e604          	ld	a,(4,x)
1046  0026 e803          	xor	a,(3,x)
1047  0028 1e06          	ldw	x,(OFST+5,sp)
1048  002a ea02          	or	a,(2,x)
1049  002c 1e02          	ldw	x,(OFST+1,sp)
1050  002e ea05          	or	a,(5,x)
1051  0030 1e09          	ldw	x,(OFST+8,sp)
1052  0032 e702          	ld	(2,x),a
1053                     ; 133     pKey[3] = (pUID[3] ^ pCustomID[4]) | (pCustomID[5] ^ pCustomID[6]);
1055  0034 1e02          	ldw	x,(OFST+1,sp)
1056  0036 e606          	ld	a,(6,x)
1057  0038 e805          	xor	a,(5,x)
1058  003a 6b01          	ld	(OFST+0,sp),a
1059  003c e604          	ld	a,(4,x)
1060  003e 1e06          	ldw	x,(OFST+5,sp)
1061  0040 e803          	xor	a,(3,x)
1062  0042 1e09          	ldw	x,(OFST+8,sp)
1063  0044 1a01          	or	a,(OFST+0,sp)
1064  0046 e703          	ld	(3,x),a
1065                     ; 135     if(KeyLength == 8)  
1067  0048 7b08          	ld	a,(OFST+7,sp)
1068  004a a108          	cp	a,#8
1069  004c 264c          	jrne	L502
1070                     ; 137         pKey[4] = (pCustomID[4] ^ (pUID[5] & pCustomID[6])) ^ pCustomID[7];
1072  004e 1e02          	ldw	x,(OFST+1,sp)
1073  0050 e606          	ld	a,(6,x)
1074  0052 1e06          	ldw	x,(OFST+5,sp)
1075  0054 e405          	and	a,(5,x)
1076  0056 1e02          	ldw	x,(OFST+1,sp)
1077  0058 e804          	xor	a,(4,x)
1078  005a e807          	xor	a,(7,x)
1079  005c 1e09          	ldw	x,(OFST+8,sp)
1080  005e e704          	ld	(4,x),a
1081                     ; 138         pKey[5] = pCustomID[5] | (pUID[6] ^ (pCustomID[7] & pCustomID[4]));
1083  0060 1e02          	ldw	x,(OFST+1,sp)
1084  0062 e604          	ld	a,(4,x)
1085  0064 e407          	and	a,(7,x)
1086  0066 1e06          	ldw	x,(OFST+5,sp)
1087  0068 e806          	xor	a,(6,x)
1088  006a 1e02          	ldw	x,(OFST+1,sp)
1089  006c ea05          	or	a,(5,x)
1090  006e 1e09          	ldw	x,(OFST+8,sp)
1091  0070 e705          	ld	(5,x),a
1092                     ; 139         pKey[6] = ((pCustomID[6] & pUID[7]) ^ pCustomID[6]) | pCustomID[3];
1094  0072 1e06          	ldw	x,(OFST+5,sp)
1095  0074 e607          	ld	a,(7,x)
1096  0076 1e02          	ldw	x,(OFST+1,sp)
1097  0078 e406          	and	a,(6,x)
1098  007a e806          	xor	a,(6,x)
1099  007c ea03          	or	a,(3,x)
1100  007e 1e09          	ldw	x,(OFST+8,sp)
1101  0080 e706          	ld	(6,x),a
1102                     ; 140         pKey[7] = (pCustomID[7] ^ pUID[4]) | (pCustomID[5] ^ pCustomID[6]);
1104  0082 1e02          	ldw	x,(OFST+1,sp)
1105  0084 e606          	ld	a,(6,x)
1106  0086 e805          	xor	a,(5,x)
1107  0088 6b01          	ld	(OFST+0,sp),a
1108  008a 1e06          	ldw	x,(OFST+5,sp)
1109  008c e604          	ld	a,(4,x)
1110  008e 1e02          	ldw	x,(OFST+1,sp)
1111  0090 e807          	xor	a,(7,x)
1112  0092 1e09          	ldw	x,(OFST+8,sp)
1113  0094 1a01          	or	a,(OFST+0,sp)
1114  0096 e707          	ld	(7,x),a
1115  0098 7b08          	ld	a,(OFST+7,sp)
1116  009a               L502:
1117                     ; 142     if(KeyLength == 12)
1119  009a a10c          	cp	a,#12
1120  009c 2703cc0178    	jrne	L702
1121                     ; 144         pKey[0] = ((pUID[0] & pCustomID[1]) ^ pCustomID[2]) ^ pCustomID[3];
1123  00a1 1e02          	ldw	x,(OFST+1,sp)
1124  00a3 e601          	ld	a,(1,x)
1125  00a5 1e06          	ldw	x,(OFST+5,sp)
1126  00a7 f4            	and	a,(x)
1127  00a8 1e02          	ldw	x,(OFST+1,sp)
1128  00aa e802          	xor	a,(2,x)
1129  00ac e803          	xor	a,(3,x)
1130  00ae 1e09          	ldw	x,(OFST+8,sp)
1131  00b0 f7            	ld	(x),a
1132                     ; 145         pKey[1] = (pUID[1] ^ (pCustomID[2] & pCustomID[3])) ^ pCustomID[4];
1134  00b1 1e02          	ldw	x,(OFST+1,sp)
1135  00b3 e603          	ld	a,(3,x)
1136  00b5 e402          	and	a,(2,x)
1137  00b7 1e06          	ldw	x,(OFST+5,sp)
1138  00b9 e801          	xor	a,(1,x)
1139  00bb 1e02          	ldw	x,(OFST+1,sp)
1140  00bd e804          	xor	a,(4,x)
1141  00bf 1e09          	ldw	x,(OFST+8,sp)
1142  00c1 e701          	ld	(1,x),a
1143                     ; 146         pKey[2] = (pUID[2] | (pCustomID[3] ^ pCustomID[4])) | pCustomID[5];
1145  00c3 1e02          	ldw	x,(OFST+1,sp)
1146  00c5 e604          	ld	a,(4,x)
1147  00c7 e803          	xor	a,(3,x)
1148  00c9 1e06          	ldw	x,(OFST+5,sp)
1149  00cb ea02          	or	a,(2,x)
1150  00cd 1e02          	ldw	x,(OFST+1,sp)
1151  00cf ea05          	or	a,(5,x)
1152  00d1 1e09          	ldw	x,(OFST+8,sp)
1153  00d3 e702          	ld	(2,x),a
1154                     ; 147         pKey[3] = (pUID[3] ^ pCustomID[4]) | (pCustomID[5] ^ pCustomID[6]);
1156  00d5 1e02          	ldw	x,(OFST+1,sp)
1157  00d7 e606          	ld	a,(6,x)
1158  00d9 e805          	xor	a,(5,x)
1159  00db 6b01          	ld	(OFST+0,sp),a
1160  00dd e604          	ld	a,(4,x)
1161  00df 1e06          	ldw	x,(OFST+5,sp)
1162  00e1 e803          	xor	a,(3,x)
1163  00e3 1e09          	ldw	x,(OFST+8,sp)
1164  00e5 1a01          	or	a,(OFST+0,sp)
1165  00e7 e703          	ld	(3,x),a
1166                     ; 148         pKey[4] = (pCustomID[4] ^ (pUID[5] & pCustomID[6])) ^ pCustomID[7];
1168  00e9 1e02          	ldw	x,(OFST+1,sp)
1169  00eb e606          	ld	a,(6,x)
1170  00ed 1e06          	ldw	x,(OFST+5,sp)
1171  00ef e405          	and	a,(5,x)
1172  00f1 1e02          	ldw	x,(OFST+1,sp)
1173  00f3 e804          	xor	a,(4,x)
1174  00f5 e807          	xor	a,(7,x)
1175  00f7 1e09          	ldw	x,(OFST+8,sp)
1176  00f9 e704          	ld	(4,x),a
1177                     ; 149         pKey[5] = pCustomID[5] | (pUID[6] ^ (pCustomID[7] & pCustomID[8]));
1179  00fb 1e02          	ldw	x,(OFST+1,sp)
1180  00fd e608          	ld	a,(8,x)
1181  00ff e407          	and	a,(7,x)
1182  0101 1e06          	ldw	x,(OFST+5,sp)
1183  0103 e806          	xor	a,(6,x)
1184  0105 1e02          	ldw	x,(OFST+1,sp)
1185  0107 ea05          	or	a,(5,x)
1186  0109 1e09          	ldw	x,(OFST+8,sp)
1187  010b e705          	ld	(5,x),a
1188                     ; 150         pKey[6] = ((pCustomID[6] & pUID[7]) ^ pCustomID[6]) | pCustomID[9];
1190  010d 1e06          	ldw	x,(OFST+5,sp)
1191  010f e607          	ld	a,(7,x)
1192  0111 1e02          	ldw	x,(OFST+1,sp)
1193  0113 e406          	and	a,(6,x)
1194  0115 e806          	xor	a,(6,x)
1195  0117 ea09          	or	a,(9,x)
1196  0119 1e09          	ldw	x,(OFST+8,sp)
1197  011b e706          	ld	(6,x),a
1198                     ; 151         pKey[7] = (pCustomID[7] ^ pUID[8]) | (pCustomID[9] ^ pCustomID[10]);
1200  011d 1e02          	ldw	x,(OFST+1,sp)
1201  011f e60a          	ld	a,(10,x)
1202  0121 e809          	xor	a,(9,x)
1203  0123 6b01          	ld	(OFST+0,sp),a
1204  0125 1e06          	ldw	x,(OFST+5,sp)
1205  0127 e608          	ld	a,(8,x)
1206  0129 1e02          	ldw	x,(OFST+1,sp)
1207  012b e807          	xor	a,(7,x)
1208  012d 1e09          	ldw	x,(OFST+8,sp)
1209  012f 1a01          	or	a,(OFST+0,sp)
1210  0131 e707          	ld	(7,x),a
1211                     ; 152         pKey[8] = (pCustomID[8]  ^ (pCustomID[9]  & pUID[10])) ^ pCustomID[11];
1213  0133 1e06          	ldw	x,(OFST+5,sp)
1214  0135 e60a          	ld	a,(10,x)
1215  0137 1e02          	ldw	x,(OFST+1,sp)
1216  0139 e409          	and	a,(9,x)
1217  013b e808          	xor	a,(8,x)
1218  013d e80b          	xor	a,(11,x)
1219  013f 1e09          	ldw	x,(OFST+8,sp)
1220  0141 e708          	ld	(8,x),a
1221                     ; 153         pKey[9] = (pCustomID[9]  ^ pCustomID[10]) | (pUID[11] & pCustomID[0]);
1223  0143 1e02          	ldw	x,(OFST+1,sp)
1224  0145 f6            	ld	a,(x)
1225  0146 1e06          	ldw	x,(OFST+5,sp)
1226  0148 e40b          	and	a,(11,x)
1227  014a 6b01          	ld	(OFST+0,sp),a
1228  014c 1e02          	ldw	x,(OFST+1,sp)
1229  014e e60a          	ld	a,(10,x)
1230  0150 e809          	xor	a,(9,x)
1231  0152 1e09          	ldw	x,(OFST+8,sp)
1232  0154 1a01          	or	a,(OFST+0,sp)
1233  0156 e709          	ld	(9,x),a
1234                     ; 154         pKey[10]= ((pCustomID[10] & pCustomID[11]) ^ pUID[0])  ^ pCustomID[1];
1236  0158 1e02          	ldw	x,(OFST+1,sp)
1237  015a e60b          	ld	a,(11,x)
1238  015c e40a          	and	a,(10,x)
1239  015e 1e06          	ldw	x,(OFST+5,sp)
1240  0160 f8            	xor	a,(x)
1241  0161 1e02          	ldw	x,(OFST+1,sp)
1242  0163 e801          	xor	a,(1,x)
1243  0165 1e09          	ldw	x,(OFST+8,sp)
1244  0167 e70a          	ld	(10,x),a
1245                     ; 155         pKey[11]= (pCustomID[11] ^ (pCustomID[0]  & pUID[1]))  ^ pCustomID[2];
1247  0169 1e06          	ldw	x,(OFST+5,sp)
1248  016b e601          	ld	a,(1,x)
1249  016d 1e02          	ldw	x,(OFST+1,sp)
1250  016f f4            	and	a,(x)
1251  0170 e80b          	xor	a,(11,x)
1252  0172 e802          	xor	a,(2,x)
1253  0174 1e09          	ldw	x,(OFST+8,sp)
1254  0176 e70b          	ld	(11,x),a
1255  0178               L702:
1256                     ; 157 }
1259  0178 5b03          	addw	sp,#3
1260  017a 81            	ret	
1324                     ; 161 static void Algorithm_4(char *pCustomID, char *pUID, char KeyLength, char *pKey) 
1324                     ; 162 {
1325                     .text:	section	.text,new
1326  0000               L112_Algorithm_4:
1328  0000 89            	pushw	x
1329  0001 88            	push	a
1330       00000001      OFST:	set	1
1333                     ; 163     pKey[0] = (pUID[0] & pCustomID[1]) ^ (pUID[2] & pCustomID[3]);
1335  0002 e603          	ld	a,(3,x)
1336  0004 1e06          	ldw	x,(OFST+5,sp)
1337  0006 e402          	and	a,(2,x)
1338  0008 6b01          	ld	(OFST+0,sp),a
1339  000a 1e02          	ldw	x,(OFST+1,sp)
1340  000c e601          	ld	a,(1,x)
1341  000e 1e06          	ldw	x,(OFST+5,sp)
1342  0010 f4            	and	a,(x)
1343  0011 1e09          	ldw	x,(OFST+8,sp)
1344  0013 1801          	xor	a,(OFST+0,sp)
1345  0015 f7            	ld	(x),a
1346                     ; 164     pKey[1] = (pCustomID[1] ^ (pUID[2] & pCustomID[3])) ^ pUID[4];
1348  0016 1e02          	ldw	x,(OFST+1,sp)
1349  0018 e603          	ld	a,(3,x)
1350  001a 1e06          	ldw	x,(OFST+5,sp)
1351  001c e402          	and	a,(2,x)
1352  001e 1e02          	ldw	x,(OFST+1,sp)
1353  0020 e801          	xor	a,(1,x)
1354  0022 1e06          	ldw	x,(OFST+5,sp)
1355  0024 e804          	xor	a,(4,x)
1356  0026 1e09          	ldw	x,(OFST+8,sp)
1357  0028 e701          	ld	(1,x),a
1358                     ; 165     pKey[2] = (pCustomID[2] | (pUID[3] ^ pUID[4])) | pCustomID[3];
1360  002a 1e06          	ldw	x,(OFST+5,sp)
1361  002c e604          	ld	a,(4,x)
1362  002e e803          	xor	a,(3,x)
1363  0030 1e02          	ldw	x,(OFST+1,sp)
1364  0032 ea02          	or	a,(2,x)
1365  0034 ea03          	or	a,(3,x)
1366  0036 1e09          	ldw	x,(OFST+8,sp)
1367  0038 e702          	ld	(2,x),a
1368                     ; 166     pKey[3] = (pUID[3] - pCustomID[0]) | (pCustomID[2] ^ pUID[3]);
1370  003a 1e06          	ldw	x,(OFST+5,sp)
1371  003c e603          	ld	a,(3,x)
1372  003e 1e02          	ldw	x,(OFST+1,sp)
1373  0040 e802          	xor	a,(2,x)
1374  0042 6b01          	ld	(OFST+0,sp),a
1375  0044 f6            	ld	a,(x)
1376  0045 1e06          	ldw	x,(OFST+5,sp)
1377  0047 e003          	sub	a,(3,x)
1378  0049 40            	neg	a
1379  004a 1e09          	ldw	x,(OFST+8,sp)
1380  004c 1a01          	or	a,(OFST+0,sp)
1381  004e e703          	ld	(3,x),a
1382                     ; 168     if(KeyLength == 8)  
1384  0050 7b08          	ld	a,(OFST+7,sp)
1385  0052 a108          	cp	a,#8
1386  0054 2655          	jrne	L542
1387                     ; 170         pKey[4] = (pUID[4] ^ (pCustomID[5] & pUID[6])) ^ pCustomID[7];
1389  0056 1e06          	ldw	x,(OFST+5,sp)
1390  0058 e606          	ld	a,(6,x)
1391  005a 1e02          	ldw	x,(OFST+1,sp)
1392  005c e405          	and	a,(5,x)
1393  005e 1e06          	ldw	x,(OFST+5,sp)
1394  0060 e804          	xor	a,(4,x)
1395  0062 1e02          	ldw	x,(OFST+1,sp)
1396  0064 e807          	xor	a,(7,x)
1397  0066 1e09          	ldw	x,(OFST+8,sp)
1398  0068 e704          	ld	(4,x),a
1399                     ; 171         pKey[5] = pCustomID[5] | (pUID[6] ^ (pCustomID[7] & pUID[8]));
1401  006a 1e06          	ldw	x,(OFST+5,sp)
1402  006c e608          	ld	a,(8,x)
1403  006e 1e02          	ldw	x,(OFST+1,sp)
1404  0070 e407          	and	a,(7,x)
1405  0072 1e06          	ldw	x,(OFST+5,sp)
1406  0074 e806          	xor	a,(6,x)
1407  0076 1e02          	ldw	x,(OFST+1,sp)
1408  0078 ea05          	or	a,(5,x)
1409  007a 1e09          	ldw	x,(OFST+8,sp)
1410  007c e705          	ld	(5,x),a
1411                     ; 172         pKey[6] = ((pCustomID[6] & pUID[7]) ^ pCustomID[6]) | pUID[9];
1413  007e 1e06          	ldw	x,(OFST+5,sp)
1414  0080 e607          	ld	a,(7,x)
1415  0082 1e02          	ldw	x,(OFST+1,sp)
1416  0084 e406          	and	a,(6,x)
1417  0086 e806          	xor	a,(6,x)
1418  0088 1e06          	ldw	x,(OFST+5,sp)
1419  008a ea09          	or	a,(9,x)
1420  008c 1e09          	ldw	x,(OFST+8,sp)
1421  008e e706          	ld	(6,x),a
1422                     ; 173         pKey[7] = (pUID[7] - pCustomID[3]) | (pUID[9] ^ pCustomID[5]);
1424  0090 1e02          	ldw	x,(OFST+1,sp)
1425  0092 e605          	ld	a,(5,x)
1426  0094 1e06          	ldw	x,(OFST+5,sp)
1427  0096 e809          	xor	a,(9,x)
1428  0098 6b01          	ld	(OFST+0,sp),a
1429  009a 1e02          	ldw	x,(OFST+1,sp)
1430  009c e603          	ld	a,(3,x)
1431  009e 1e06          	ldw	x,(OFST+5,sp)
1432  00a0 e007          	sub	a,(7,x)
1433  00a2 40            	neg	a
1434  00a3 1e09          	ldw	x,(OFST+8,sp)
1435  00a5 1a01          	or	a,(OFST+0,sp)
1436  00a7 e707          	ld	(7,x),a
1437  00a9 7b08          	ld	a,(OFST+7,sp)
1438  00ab               L542:
1439                     ; 175     if(KeyLength == 12)
1441  00ab a10c          	cp	a,#12
1442  00ad 2703cc01a4    	jrne	L742
1443                     ; 177         pKey[0] = (pUID[0] & pCustomID[1]) ^ (pUID[2] & pCustomID[3]);
1445  00b2 1e02          	ldw	x,(OFST+1,sp)
1446  00b4 e603          	ld	a,(3,x)
1447  00b6 1e06          	ldw	x,(OFST+5,sp)
1448  00b8 e402          	and	a,(2,x)
1449  00ba 6b01          	ld	(OFST+0,sp),a
1450  00bc 1e02          	ldw	x,(OFST+1,sp)
1451  00be e601          	ld	a,(1,x)
1452  00c0 1e06          	ldw	x,(OFST+5,sp)
1453  00c2 f4            	and	a,(x)
1454  00c3 1e09          	ldw	x,(OFST+8,sp)
1455  00c5 1801          	xor	a,(OFST+0,sp)
1456  00c7 f7            	ld	(x),a
1457                     ; 178         pKey[1] = (pCustomID[1] ^ (pUID[2] & pCustomID[3])) ^ pUID[4];
1459  00c8 1e02          	ldw	x,(OFST+1,sp)
1460  00ca e603          	ld	a,(3,x)
1461  00cc 1e06          	ldw	x,(OFST+5,sp)
1462  00ce e402          	and	a,(2,x)
1463  00d0 1e02          	ldw	x,(OFST+1,sp)
1464  00d2 e801          	xor	a,(1,x)
1465  00d4 1e06          	ldw	x,(OFST+5,sp)
1466  00d6 e804          	xor	a,(4,x)
1467  00d8 1e09          	ldw	x,(OFST+8,sp)
1468  00da e701          	ld	(1,x),a
1469                     ; 179         pKey[2] = (pCustomID[2] | (pUID[3] ^ pUID[4])) | pCustomID[5];
1471  00dc 1e06          	ldw	x,(OFST+5,sp)
1472  00de e604          	ld	a,(4,x)
1473  00e0 e803          	xor	a,(3,x)
1474  00e2 1e02          	ldw	x,(OFST+1,sp)
1475  00e4 ea02          	or	a,(2,x)
1476  00e6 ea05          	or	a,(5,x)
1477  00e8 1e09          	ldw	x,(OFST+8,sp)
1478  00ea e702          	ld	(2,x),a
1479                     ; 180         pKey[3] = (pUID[3] - pCustomID[4]) | (pCustomID[5] ^ pUID[6]);
1481  00ec 1e06          	ldw	x,(OFST+5,sp)
1482  00ee e606          	ld	a,(6,x)
1483  00f0 1e02          	ldw	x,(OFST+1,sp)
1484  00f2 e805          	xor	a,(5,x)
1485  00f4 6b01          	ld	(OFST+0,sp),a
1486  00f6 e604          	ld	a,(4,x)
1487  00f8 1e06          	ldw	x,(OFST+5,sp)
1488  00fa e003          	sub	a,(3,x)
1489  00fc 40            	neg	a
1490  00fd 1e09          	ldw	x,(OFST+8,sp)
1491  00ff 1a01          	or	a,(OFST+0,sp)
1492  0101 e703          	ld	(3,x),a
1493                     ; 181         pKey[4] = (pUID[4] ^ (pCustomID[5] & pUID[6])) ^ pCustomID[7];
1495  0103 1e06          	ldw	x,(OFST+5,sp)
1496  0105 e606          	ld	a,(6,x)
1497  0107 1e02          	ldw	x,(OFST+1,sp)
1498  0109 e405          	and	a,(5,x)
1499  010b 1e06          	ldw	x,(OFST+5,sp)
1500  010d e804          	xor	a,(4,x)
1501  010f 1e02          	ldw	x,(OFST+1,sp)
1502  0111 e807          	xor	a,(7,x)
1503  0113 1e09          	ldw	x,(OFST+8,sp)
1504  0115 e704          	ld	(4,x),a
1505                     ; 182         pKey[5] = pCustomID[5] | (pUID[6] ^ (pCustomID[7] & pUID[8]));
1507  0117 1e06          	ldw	x,(OFST+5,sp)
1508  0119 e608          	ld	a,(8,x)
1509  011b 1e02          	ldw	x,(OFST+1,sp)
1510  011d e407          	and	a,(7,x)
1511  011f 1e06          	ldw	x,(OFST+5,sp)
1512  0121 e806          	xor	a,(6,x)
1513  0123 1e02          	ldw	x,(OFST+1,sp)
1514  0125 ea05          	or	a,(5,x)
1515  0127 1e09          	ldw	x,(OFST+8,sp)
1516  0129 e705          	ld	(5,x),a
1517                     ; 183         pKey[6] = ((pCustomID[6] & pUID[7]) ^ pCustomID[6]) | pUID[9];
1519  012b 1e06          	ldw	x,(OFST+5,sp)
1520  012d e607          	ld	a,(7,x)
1521  012f 1e02          	ldw	x,(OFST+1,sp)
1522  0131 e406          	and	a,(6,x)
1523  0133 e806          	xor	a,(6,x)
1524  0135 1e06          	ldw	x,(OFST+5,sp)
1525  0137 ea09          	or	a,(9,x)
1526  0139 1e09          	ldw	x,(OFST+8,sp)
1527  013b e706          	ld	(6,x),a
1528                     ; 184         pKey[7] = (pUID[7] - pCustomID[8]) | (pUID[9] ^ pCustomID[10]);
1530  013d 1e02          	ldw	x,(OFST+1,sp)
1531  013f e60a          	ld	a,(10,x)
1532  0141 1e06          	ldw	x,(OFST+5,sp)
1533  0143 e809          	xor	a,(9,x)
1534  0145 6b01          	ld	(OFST+0,sp),a
1535  0147 1e02          	ldw	x,(OFST+1,sp)
1536  0149 e608          	ld	a,(8,x)
1537  014b 1e06          	ldw	x,(OFST+5,sp)
1538  014d e007          	sub	a,(7,x)
1539  014f 40            	neg	a
1540  0150 1e09          	ldw	x,(OFST+8,sp)
1541  0152 1a01          	or	a,(OFST+0,sp)
1542  0154 e707          	ld	(7,x),a
1543                     ; 185         pKey[8] = (pCustomID[8] ^ (pUID[9] & pCustomID[10])) ^ pUID[11];
1545  0156 1e02          	ldw	x,(OFST+1,sp)
1546  0158 e60a          	ld	a,(10,x)
1547  015a 1e06          	ldw	x,(OFST+5,sp)
1548  015c e409          	and	a,(9,x)
1549  015e 1e02          	ldw	x,(OFST+1,sp)
1550  0160 e808          	xor	a,(8,x)
1551  0162 1e06          	ldw	x,(OFST+5,sp)
1552  0164 e80b          	xor	a,(11,x)
1553  0166 1e09          	ldw	x,(OFST+8,sp)
1554  0168 e708          	ld	(8,x),a
1555                     ; 186         pKey[9] = (pUID[9] ^ pCustomID[10]) | (pUID[11] & pCustomID[0]);
1557  016a 1e02          	ldw	x,(OFST+1,sp)
1558  016c f6            	ld	a,(x)
1559  016d 1e06          	ldw	x,(OFST+5,sp)
1560  016f e40b          	and	a,(11,x)
1561  0171 6b01          	ld	(OFST+0,sp),a
1562  0173 1e02          	ldw	x,(OFST+1,sp)
1563  0175 e60a          	ld	a,(10,x)
1564  0177 1e06          	ldw	x,(OFST+5,sp)
1565  0179 e809          	xor	a,(9,x)
1566  017b 1e09          	ldw	x,(OFST+8,sp)
1567  017d 1a01          	or	a,(OFST+0,sp)
1568  017f e709          	ld	(9,x),a
1569                     ; 187         pKey[10]= ((pUID[10] & pCustomID[11]) ^ pUID[0])  ^ pCustomID[1];
1571  0181 1e02          	ldw	x,(OFST+1,sp)
1572  0183 e60b          	ld	a,(11,x)
1573  0185 1e06          	ldw	x,(OFST+5,sp)
1574  0187 e40a          	and	a,(10,x)
1575  0189 f8            	xor	a,(x)
1576  018a 1e02          	ldw	x,(OFST+1,sp)
1577  018c e801          	xor	a,(1,x)
1578  018e 1e09          	ldw	x,(OFST+8,sp)
1579  0190 e70a          	ld	(10,x),a
1580                     ; 188         pKey[11]= ((pCustomID[11] - pUID[0]) & pCustomID[1])  ^ pUID[2];
1582  0192 1e06          	ldw	x,(OFST+5,sp)
1583  0194 f6            	ld	a,(x)
1584  0195 1e02          	ldw	x,(OFST+1,sp)
1585  0197 e00b          	sub	a,(11,x)
1586  0199 40            	neg	a
1587  019a e401          	and	a,(1,x)
1588  019c 1e06          	ldw	x,(OFST+5,sp)
1589  019e e802          	xor	a,(2,x)
1590  01a0 1e09          	ldw	x,(OFST+8,sp)
1591  01a2 e70b          	ld	(11,x),a
1592  01a4               L742:
1593                     ; 190 }
1596  01a4 5b03          	addw	sp,#3
1597  01a6 81            	ret	
1600                     .const:	section	.text
1601  0000               L152_Algorithm_Fun_Array:
1603  0000 0000          	dc.w	L3_Algorithm_0
1605  0002 0000          	dc.w	L15_Algorithm_1
1607  0004 0000          	dc.w	L111_Algorithm_2
1609  0006 0000          	dc.w	L151_Algorithm_3
1611  0008 0000          	dc.w	L112_Algorithm_4
1663                     ; 213 void LittleEndia_BigEndia_Interconvert_32(unsigned long* pBuffer, unsigned long WordLen)
1663                     ; 214 {
1664                     .text:	section	.text,new
1665  0000               _LittleEndia_BigEndia_Interconvert_32:
1667  0000 89            	pushw	x
1668  0001 5210          	subw	sp,#16
1669       00000010      OFST:	set	16
1672                     ; 217     for(i = 0; i < WordLen; i ++)
1674  0003 5f            	clrw	x
1675  0004 1f0f          	ldw	(OFST-1,sp),x
1676  0006 1f0d          	ldw	(OFST-3,sp),x
1678  0008 cc0099        	jra	L503
1679  000b               L103:
1680                     ; 219         pBuffer[i] = BigLittleSwap32(pBuffer[i]);
1682  000b 1e0f          	ldw	x,(OFST-1,sp)
1683  000d 58            	sllw	x
1684  000e 58            	sllw	x
1685  000f 72fb11        	addw	x,(OFST+1,sp)
1686  0012 e603          	ld	a,(3,x)
1687  0014 b703          	ld	c_lreg+3,a
1688  0016 3f02          	clr	c_lreg+2
1689  0018 3f01          	clr	c_lreg+1
1690  001a 3f00          	clr	c_lreg
1691  001c a618          	ld	a,#24
1692  001e cd0000        	call	c_llsh
1694  0021 96            	ldw	x,sp
1695  0022 1c0009        	addw	x,#OFST-7
1696  0025 cd0000        	call	c_rtol
1698  0028 1e0f          	ldw	x,(OFST-1,sp)
1699  002a 58            	sllw	x
1700  002b 58            	sllw	x
1701  002c 72fb11        	addw	x,(OFST+1,sp)
1702  002f cd0000        	call	c_ltor
1704  0032 3f03          	clr	c_lreg+3
1705  0034 3f01          	clr	c_lreg+1
1706  0036 3f00          	clr	c_lreg
1707  0038 a608          	ld	a,#8
1708  003a cd0000        	call	c_llsh
1710  003d 96            	ldw	x,sp
1711  003e 1c0005        	addw	x,#OFST-11
1712  0041 cd0000        	call	c_rtol
1714  0044 1e0f          	ldw	x,(OFST-1,sp)
1715  0046 58            	sllw	x
1716  0047 58            	sllw	x
1717  0048 72fb11        	addw	x,(OFST+1,sp)
1718  004b cd0000        	call	c_ltor
1720  004e 3f03          	clr	c_lreg+3
1721  0050 3f02          	clr	c_lreg+2
1722  0052 3f00          	clr	c_lreg
1723  0054 a608          	ld	a,#8
1724  0056 cd0000        	call	c_lursh
1726  0059 96            	ldw	x,sp
1727  005a 5c            	incw	x
1728  005b cd0000        	call	c_rtol
1730  005e 1e0f          	ldw	x,(OFST-1,sp)
1731  0060 58            	sllw	x
1732  0061 58            	sllw	x
1733  0062 72fb11        	addw	x,(OFST+1,sp)
1734  0065 cd0000        	call	c_ltor
1736  0068 3f03          	clr	c_lreg+3
1737  006a 3f02          	clr	c_lreg+2
1738  006c 3f01          	clr	c_lreg+1
1739  006e a618          	ld	a,#24
1740  0070 cd0000        	call	c_lursh
1742  0073 96            	ldw	x,sp
1743  0074 5c            	incw	x
1744  0075 cd0000        	call	c_lor
1746  0078 96            	ldw	x,sp
1747  0079 1c0005        	addw	x,#OFST-11
1748  007c cd0000        	call	c_lor
1750  007f 96            	ldw	x,sp
1751  0080 1c0009        	addw	x,#OFST-7
1752  0083 cd0000        	call	c_lor
1754  0086 1e0f          	ldw	x,(OFST-1,sp)
1755  0088 58            	sllw	x
1756  0089 58            	sllw	x
1757  008a 72fb11        	addw	x,(OFST+1,sp)
1758  008d cd0000        	call	c_rtol
1760                     ; 217     for(i = 0; i < WordLen; i ++)
1762  0090 96            	ldw	x,sp
1763  0091 1c000d        	addw	x,#OFST-3
1764  0094 a601          	ld	a,#1
1765  0096 cd0000        	call	c_lgadc
1767  0099               L503:
1770  0099 96            	ldw	x,sp
1771  009a 1c000d        	addw	x,#OFST-3
1772  009d cd0000        	call	c_ltor
1774  00a0 96            	ldw	x,sp
1775  00a1 1c0015        	addw	x,#OFST+5
1776  00a4 cd0000        	call	c_lcmp
1778  00a7 2403cc000b    	jrult	L103
1779                     ; 221     return;
1782  00ac 5b12          	addw	sp,#18
1783  00ae 81            	ret	
1786                     	switch	.const
1787  000a               L313_KeyBuf:
1788  000a 00            	dc.b	0
1789  000b 000000000000  	ds.b	11
1976                     ; 229 char UID_Encryption_Key_Check(void *pKey,
1976                     ; 230                               void *pUID,
1976                     ; 231                               void *pCustomID,
1976                     ; 232                               eKeyLengthType keyLength,
1976                     ; 233                               eEndiaType endiaType,                              
1976                     ; 234                               eAlgorithmType AlgorithmNum)
1976                     ; 235 {   
1977                     .text:	section	.text,new
1978  0000               _UID_Encryption_Key_Check:
1980  0000 89            	pushw	x
1981  0001 520c          	subw	sp,#12
1982       0000000c      OFST:	set	12
1985                     ; 236     char KeyBuf[12] = {0};//临时存储计算得到的Key
1987  0003 96            	ldw	x,sp
1988  0004 5c            	incw	x
1989  0005 90ae000a      	ldw	y,#L313_KeyBuf
1990  0009 a60c          	ld	a,#12
1991  000b cd0000        	call	c_xymvx
1993                     ; 240     pAlgorithm_Fun = Algorithm_Fun_Array[AlgorithmNum];
1995  000e 7b17          	ld	a,(OFST+11,sp)
1996  0010 5f            	clrw	x
1997  0011 97            	ld	xl,a
1998  0012 58            	sllw	x
1999  0013 de0000        	ldw	x,(L152_Algorithm_Fun_Array,x)
2000  0016 bf00          	ldw	L113_pAlgorithm_Fun,x
2001                     ; 242     (*pAlgorithm_Fun)(pCustomID, pUID, keyLength, KeyBuf); 
2003  0018 96            	ldw	x,sp
2004  0019 5c            	incw	x
2005  001a 89            	pushw	x
2006  001b 7b17          	ld	a,(OFST+11,sp)
2007  001d 88            	push	a
2008  001e 1e14          	ldw	x,(OFST+8,sp)
2009  0020 89            	pushw	x
2010  0021 1e18          	ldw	x,(OFST+12,sp)
2011  0023 92cd00        	call	[L113_pAlgorithm_Fun.w]
2013  0026 5b05          	addw	sp,#5
2014                     ; 244     if(endiaType == BIG_ENDIA)
2016  0028 7b16          	ld	a,(OFST+10,sp)
2017  002a 4a            	dec	a
2018  002b 2617          	jrne	L324
2019                     ; 246         LittleEndia_BigEndia_Interconvert_32((unsigned long*)KeyBuf, keyLength/sizeof(unsigned long));
2021  002d 7b15          	ld	a,(OFST+9,sp)
2022  002f 44            	srl	a
2023  0030 44            	srl	a
2024  0031 5f            	clrw	x
2025  0032 cd0000        	call	c_uitol
2027  0035 be02          	ldw	x,c_lreg+2
2028  0037 89            	pushw	x
2029  0038 be00          	ldw	x,c_lreg
2030  003a 89            	pushw	x
2031  003b 96            	ldw	x,sp
2032  003c 1c0005        	addw	x,#OFST-7
2033  003f cd0000        	call	_LittleEndia_BigEndia_Interconvert_32
2035  0042 5b04          	addw	sp,#4
2036  0044               L324:
2037                     ; 250     if(memcmp(pKey, KeyBuf, keyLength)) 
2039  0044 7b15          	ld	a,(OFST+9,sp)
2040  0046 5f            	clrw	x
2041  0047 97            	ld	xl,a
2042  0048 89            	pushw	x
2043  0049 96            	ldw	x,sp
2044  004a 1c0003        	addw	x,#OFST-9
2045  004d 89            	pushw	x
2046  004e 1e11          	ldw	x,(OFST+5,sp)
2047  0050 cd0000        	call	_memcmp
2049  0053 5b04          	addw	sp,#4
2050  0055 5d            	tnzw	x
2051  0056 2704          	jreq	L524
2052                     ; 252         return 1;
2054  0058 a601          	ld	a,#1
2056  005a 2001          	jra	L03
2057  005c               L524:
2058                     ; 255     return 0; 
2060  005c 4f            	clr	a
2062  005d               L03:
2064  005d 5b0e          	addw	sp,#14
2065  005f 81            	ret	
2155                     ; 258 void UID_Encryption_Key_Calculate(void *pKey,
2155                     ; 259                                   void *pUID,
2155                     ; 260                                   void *pCustomID,
2155                     ; 261                                   eKeyLengthType keyLength,
2155                     ; 262                                   eEndiaType endiaType,
2155                     ; 263                                   eAlgorithmType AlgorithmNum)
2155                     ; 264 {    
2156                     .text:	section	.text,new
2157  0000               _UID_Encryption_Key_Calculate:
2159  0000 89            	pushw	x
2160       00000000      OFST:	set	0
2163                     ; 266     pAlgorithm_Fun = Algorithm_Fun_Array[AlgorithmNum];
2165  0001 7b0b          	ld	a,(OFST+11,sp)
2166  0003 5f            	clrw	x
2167  0004 97            	ld	xl,a
2168  0005 58            	sllw	x
2169  0006 de0000        	ldw	x,(L152_Algorithm_Fun_Array,x)
2170  0009 bf00          	ldw	L113_pAlgorithm_Fun,x
2171                     ; 268     (*pAlgorithm_Fun)(pCustomID, pUID, keyLength, pKey);   
2173  000b 1e01          	ldw	x,(OFST+1,sp)
2174  000d 89            	pushw	x
2175  000e 7b0b          	ld	a,(OFST+11,sp)
2176  0010 88            	push	a
2177  0011 1e08          	ldw	x,(OFST+8,sp)
2178  0013 89            	pushw	x
2179  0014 1e0c          	ldw	x,(OFST+12,sp)
2180  0016 92cd00        	call	[L113_pAlgorithm_Fun.w]
2182  0019 5b05          	addw	sp,#5
2183                     ; 270     if(endiaType == BIG_ENDIA)
2185  001b 7b0a          	ld	a,(OFST+10,sp)
2186  001d 4a            	dec	a
2187  001e 2615          	jrne	L174
2188                     ; 272         LittleEndia_BigEndia_Interconvert_32((unsigned long*)pKey, keyLength/sizeof(unsigned long));
2190  0020 7b09          	ld	a,(OFST+9,sp)
2191  0022 44            	srl	a
2192  0023 44            	srl	a
2193  0024 5f            	clrw	x
2194  0025 cd0000        	call	c_uitol
2196  0028 be02          	ldw	x,c_lreg+2
2197  002a 89            	pushw	x
2198  002b be00          	ldw	x,c_lreg
2199  002d 89            	pushw	x
2200  002e 1e05          	ldw	x,(OFST+5,sp)
2201  0030 cd0000        	call	_LittleEndia_BigEndia_Interconvert_32
2203  0033 5b04          	addw	sp,#4
2204  0035               L174:
2205                     ; 275     return; 
2208  0035 85            	popw	x
2209  0036 81            	ret	
2248                     	switch	.ubsct
2249  0000               L113_pAlgorithm_Fun:
2250  0000 0000          	ds.b	2
2251                     	xdef	_LittleEndia_BigEndia_Interconvert_32
2252                     	xdef	_UID_Encryption_Key_Calculate
2253                     	xdef	_UID_Encryption_Key_Check
2254                     	xref	_memcmp
2255                     	xref.b	c_lreg
2256                     	xref.b	c_x
2276                     	xref	c_uitol
2277                     	xref	c_xymvx
2278                     	xref	c_lcmp
2279                     	xref	c_lgadc
2280                     	xref	c_llsh
2281                     	xref	c_lor
2282                     	xref	c_rtol
2283                     	xref	c_lursh
2284                     	xref	c_ltor
2285                     	end
