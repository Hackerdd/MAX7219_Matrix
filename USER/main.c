/***
		Copyright (c) 2016
		All rights reserved.
		
		File name						:main.c
		file identification :
		Subject							:A matrix led project based on MAX7219 
													@example Matrix_printf("string");
																	Hello World character will be shown on matrix led
		
		Current Version 		:
		Author							:Hacker
		Date								:2016-1-23 17:29:14
		
		Instead Version			:
		Date								:
***/
#include "stm32f10x.h"
#include "max7219.h"
#include "SysTick.h"
#include "Time_test.h"
#include "String.h"

void Matrix(void);
void Draw_Dot(u8 l, u8 c);
void Circle(void);
void Line(void);
void Moving_word(u8 n);//字符滚动
void Array_printf(u8 *n);
void Matrix_printf(char *ptr);

int a = 1;
int b = 1;
char array[] = {"Hackerrr"};

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{	
	/* LED 端口初始化 */
	LED_GPIO_Config();
	
	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();
	
	/*MAX7219 初始化*/
	Init_MAX7219();
	
	Delay_us(50);
	
	while(1)
	{
		Matrix_printf(array);
		Delay_ms(300);
		Matrix_printf("1234567890");
		Delay_ms(300);
	}
}

void Circle(void)//回型扫描
{
	u32 t = 90000;
	u8 c = 24;
	u8 a = 1;
	u8 b = 1;
	while(c--)
	{
		Draw_Dot(a,b);
		if((a  < 8) && (b  < 8))a++;
		else if((a == 8) && (b  < 8))b++;
//		if((a == 8) && (b == 8))a--;
		else if((b == 8) && (a != 1))a--;
		else if((b == 8) && (a == 1))
		{
			while(b > 1)
			{
				Draw_Dot(a,b);
				b--;
				Delay_us(t);
			}
		}
		Delay_us(t);
	}
}

void Line(void)//逐行单点扫描
{
	u8 a = 1;
	u8 b = 1;
	u32 t = 90000;
	while(b < 10)
	{
		while(a < 9)
		{
			Draw_Dot(a++,b);
			Delay_us(t);
		}
		b++;
		a = 0;
	}
}

//有问题，导致硬件错误，可能堆栈溢出
void Moving_word(u8 n)//字符滚动
{	
	u8 a = 1;
	u8 b = 8;
	u8 c = 8;//完全移出
	u8 d = 8;
	u32 t = 120000;
	u8 Array_dot[8] ={0};
	
	while(d--)Array_dot[d-1] = nAsciiDot[n][d-1];
	
	while(c--)
	{
		for(a=1;a<9;a++)Write_Max7219(a,Array_dot[a-1]);
		while(b--)
		{
			Array_dot[b-1] = Array_dot[b-1]<<1;
		}
		Delay_us(t);
	}
	
//	c = 9;
//	b = 8;
//	while(d--)Array_dot[d-1] = nAsciiDot[n][d-1];
//	
//	while(c--)
//	{
//		for(a=1;a<9;a++)Write_Max7219(a,Array_dot[a-1]);
//		while(b--)
//		{
//			Array_dot[b-1] = Array_dot[b-1]>>1;
//		}
//		Delay_us(t);
//	}
}

//滚动显现字符，正常运行
void Matrix_printf(char *ptr)//滚动输出
{
	u8 a = 0;
	u8 b = 0;
//	u8 c = sizeof(*ptr);
	u8 c = strlen(ptr);
	u32 t = 300;
	u8 Array_dot[8] ={0};
	u8 Array_Tem[8] ={0};
	
	//因为字符靠左，修正；32是修正真正ascii与table表的偏差
	for(a=0;a<8;a++)Array_Tem[a] = nAsciiDot[(u8)*ptr - 32][a]>>2;
	
	if(c == 1)for(a=0;a<8;a++)Write_Max7219(a+1,Array_Tem[a]);
	else
	{		
		while(--c)
		{
			for(b=1;b<7;b++)
			{
				for(a=0;a<8;a++)Array_dot[a] = (Array_Tem[a]<<b) | (nAsciiDot[(u8)*(ptr+1) - 32][a]>>(8-b));
				for(a=0;a<8;a++)Write_Max7219(a+1,Array_dot[a]);
				Delay_ms(t);
			}
			++ptr;
			for(a=0;a<8;a++)Array_Tem[a] = Array_dot[a];
		}
	}	
}

void Array_printf(u8 *n)//滚动输出
{
	u8 a = 0;
	u8 b = 0;
	u32 t = 200;
	u8 Array_dot[8] ={0};
	u8 Array_Tem[8] ={0};
	
	for(a=0;a<8;a++)Array_Tem[a] = nAsciiDot[(u8)*n][a]>>2;//因为字符靠左，修正
	
	for(b=0;b<7;b++)
	{
		for(a=0;a<8;a++)Array_dot[a] = (Array_Tem[a]<<b) | (nAsciiDot[(u8)*n+1][a]>>(8-b));
		for(a=0;a<8;a++)Write_Max7219(a+1,Array_dot[a]);
		Delay_ms(t);
	}
	
	for(a=0;a<8;a++)Array_Tem[a] = Array_dot[a];
	
//	for(b=1;b<7;b++)
//	{
//		for(a=0;a<8;a++)Array_dot[a] = (Array_Tem[a]<<(b)) | (nAsciiDot[n+2][a]>>(8-b));
//		for(a=0;a<8;a++)Write_Max7219(a+1,Array_dot[a]);
//		Delay_ms(t);
//	}
}

void Draw_Dot(u8 l, u8 c)
{
	u8 a;
	u8 Array_dot[8] = {0x00};
	Array_dot[l-1] = 0x80>>(c-1);
	for(a=1;a<9;a++)Write_Max7219(a,Array_dot[a-1]);
}

void Matrix(void)
{
	u8 i = 0;
	u8 j = 0;
	for(j=33;j<96;j++)
	{
		 for(i=1;i<9;++i)Write_Max7219(i,nAsciiDot[j][i-1]);
		 Delay_us(1000);
	}  
}



/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
