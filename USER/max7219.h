/*******************************************************

 *  程序名称：MAX7219.H

 *  程序功能：MAX7219.H的头文件

 *  程序作者：赵鹏震

 *  创建时间：2013-12-7

 *  修改时间：2013-12-9

 *  程序版本：V0.3

 ******************************************************/


#ifndef __MAX7219_H__

#define __MAX7219_H__

#include "stm32f10x.h"
#include "SysTick.h"

/******************************************************

 * 函数名称：

 * 函数功能：数据的发送

 * 入口参数：unsigned int uiDataOne, unsigned int uiDataTwo

 * 出口参数：void

*******************************************************/ 
extern u8 disp1[38][8];
extern const u8 nAsciiDot[96][8];
//extern const u8 AsciiCode[96][8];
extern void SendData(unsigned int uiDataOne, unsigned int uiDataTwo);
extern u16 Seg_Num;

/* 位码表 */



#define ON  1
#define OFF 0

#define Seg_time 25

#define MAX7219_PORT GPIOA

#define MAX7219_CLK_PIN GPIO_Pin_0
#define Max7219_CS_PIN  GPIO_Pin_2
#define Max7219_DIN_PIN  GPIO_Pin_4

//#define MAX7219_CLK_PIN GPIO_Pin_0
//#define Max7219_CS_PIN  GPIO_Pin_1
//#define Max7219_DIN_PIN  GPIO_Pin_2

//带参宏，可以像内联函数一样使用
#define MAX7219_CLK(a)	if (a)	\
					GPIO_SetBits(MAX7219_PORT,MAX7219_CLK_PIN);\
					else		\
					GPIO_ResetBits(MAX7219_PORT,MAX7219_CLK_PIN)

#define Max7219_CS(a)	if (a)	\
					GPIO_SetBits(MAX7219_PORT,Max7219_CS_PIN);\
					else		\
					GPIO_ResetBits(MAX7219_PORT,Max7219_CS_PIN)

#define Max7219_DIN(a)	if (a)	\
					GPIO_SetBits(MAX7219_PORT,Max7219_DIN_PIN);\
					else		\
					GPIO_ResetBits(MAX7219_PORT,Max7219_DIN_PIN)

#define SHOW_SEGMENT(num) (Seg_Num = num) 					
					
void LED_GPIO_Config(void);
void Delay_ms(__IO u32 nCount);
void Init_MAX7219(void);
void Write_Max7219(u8 address,u8 dat);
void Write_Max7219_byte(u8 DATA);

#endif
