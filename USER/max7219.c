/*******************************************************

 *  程序名称：max7219.c

 *  程序功能：max7219的应用文件，max7219控制MATRIX

 *  程序作者：

 *  创建时间：2013-11-6

 *  修改时间：2013-11-9

 *  程序版本：V0.2

 ******************************************************/

/*

 *  包含头文件

 */

#include "max7219.h"

u16 Seg_Num = 0;

u8 disp1[38][8]={
	{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
	{0x0,0x0,0x44,0x7C,0x7C,0x04,0x0,0x0},//{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
	{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},//2
	{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},//3
	{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},//4
	{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},//5
	{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},//6
	{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},//7
	{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
	{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},//9
	{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
	{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
	{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
	{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
	{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
	{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
	{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
	{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
	{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
	{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
	{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
	{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
	{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
	{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
	{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
	{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
	{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
	{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
	{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
	{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
	{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
	{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
	{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
	{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
	{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
	{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},//Z
	{0x8,0x7F,0x49,0x49,0x7F,0x8,0x8,0x8},//中
	{0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},//国
};

//------------------  ASCII字模的数据表 ------------------------ //
// 码表从0x20~0x7e                                                //
// 字库: C:\Users\Knight\OneDrive\Download\LcmZimoLCD字模提取工具软件\Asc5x8E.dot 横向取模左高位//
//-------------------------------------------------------------- //
const u8 nAsciiDot[96][8] =              // ASCII
{
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // - -

	{0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x00}, // -!-

	{0x50,0x50,0x50,0x00,0x00,0x00,0x00,0x00}, // -"-

	{0x50,0x50,0xF8,0x50,0xF8,0x50,0x50,0x00}, // -#-

	{0x20,0x78,0xC0,0x70,0x28,0xF0,0x20,0x00}, // -$-

	{0xC0,0xC8,0x10,0x20,0x40,0x98,0x18,0x00}, // -%-

	{0x40,0xA0,0xA0,0x40,0xA8,0x90,0x68,0x00}, // -&-

	{0x30,0x20,0x40,0x00,0x00,0x00,0x00,0x00}, // -'-

	{0x10,0x20,0x40,0x40,0x40,0x20,0x10,0x00}, // -(-

	{0x40,0x20,0x10,0x10,0x10,0x20,0x40,0x00}, // -)-

	{0x20,0xA8,0x70,0x20,0x70,0xA8,0x20,0x00}, // -*-

	{0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x00}, // -+-

	{0x00,0x00,0x00,0x00,0x60,0x40,0x80,0x00}, // -,-

	{0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00}, // ---

	{0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00}, // -.-

	{0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00}, // -/-

	{0x70,0x88,0x98,0xA8,0xC8,0x88,0x70,0x00}, // -0-

	{0x20,0x60,0x20,0x20,0x20,0x20,0x70,0x00}, // -1-

	{0x70,0x88,0x08,0x30,0x40,0x80,0xF8,0x00}, // -2-

	{0xF8,0x08,0x10,0x30,0x08,0x88,0x70,0x00}, // -3-

	{0x10,0x30,0x50,0x90,0xF8,0x10,0x10,0x00}, // -4-

	{0xF8,0x80,0xF0,0x08,0x08,0x88,0x70,0x00}, // -5-

	{0x38,0x40,0x80,0xF0,0x88,0x88,0x70,0x00}, // -6-

	{0xF8,0x08,0x10,0x20,0x40,0x40,0x40,0x00}, // -7-

	{0x70,0x88,0x88,0x70,0x88,0x88,0x70,0x00}, // -8-

	{0x70,0x88,0x88,0x78,0x08,0x10,0xE0,0x00}, // -9-

	{0x00,0x60,0x60,0x00,0x60,0x60,0x00,0x00}, // -:-

	{0x00,0x60,0x60,0x00,0x60,0x60,0x80,0x00}, // -;-

	{0x10,0x20,0x40,0x80,0x40,0x20,0x10,0x00}, // -<-

	{0x00,0x00,0xF8,0x00,0xF8,0x00,0x00,0x00}, // -=-

	{0x40,0x20,0x10,0x08,0x10,0x20,0x40,0x00}, // ->-

	{0x70,0x88,0x10,0x20,0x20,0x00,0x20,0x00}, // -?-

	{0x70,0x88,0xB8,0xA8,0xB8,0x80,0x78,0x00}, // -@-

	{0x20,0x50,0x88,0x88,0xF8,0x88,0x88,0x00}, // -A-33

	{0xF0,0x88,0x88,0xF0,0x88,0x88,0xF0,0x00}, // -B-

	{0x70,0x88,0x80,0x80,0x80,0x88,0x70,0x00}, // -C-

	{0xF0,0x88,0x88,0x88,0x88,0x88,0xF0,0x00}, // -D-

	{0xF8,0x80,0x80,0xF0,0x80,0x80,0xF8,0x00}, // -E-

	{0xF8,0x80,0x80,0xF0,0x80,0x80,0x80,0x00}, // -F-

	{0x70,0x88,0x80,0x80,0xB8,0x88,0x78,0x00}, // -G-

	{0x88,0x88,0x88,0xF8,0x88,0x88,0x88,0x00}, // -H-

	{0x70,0x20,0x20,0x20,0x20,0x20,0x70,0x00}, // -I-

	{0x38,0x10,0x10,0x10,0x10,0x90,0x60,0x00}, // -J-

	{0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88,0x00}, // -K-

	{0x80,0x80,0x80,0x80,0x80,0x80,0xF8,0x00}, // -L-

	{0x88,0xD8,0xA8,0xA8,0x88,0x88,0x88,0x00}, // -M-

	{0x88,0x88,0xC8,0xA8,0x98,0x88,0x88,0x00}, // -N-

	{0x70,0x88,0x88,0x88,0x88,0x88,0x70,0x00}, // -O-

	{0xF0,0x88,0x88,0xF0,0x80,0x80,0x80,0x00}, // -P-

	{0x70,0x88,0x88,0x88,0xA8,0x90,0x68,0x00}, // -Q-

	{0xF0,0x88,0x88,0xF0,0xA0,0x90,0x88,0x00}, // -R-

	{0x70,0x88,0x80,0x70,0x08,0x88,0x70,0x00}, // -S-

	{0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x00}, // -T-

	{0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00}, // -U-

	{0x88,0x88,0x88,0x88,0x88,0x50,0x20,0x00}, // -V-

	{0x88,0x88,0x88,0xA8,0xA8,0xD8,0x88,0x00}, // -W-

	{0x88,0x88,0x50,0x20,0x50,0x88,0x88,0x00}, // -X-

	{0x88,0x88,0x50,0x20,0x20,0x20,0x20,0x00}, // -Y-

	{0xF8,0x08,0x10,0x20,0x40,0x80,0xF8,0x00}, // -Z-

	{0xF0,0xC0,0xC0,0xC0,0xC0,0xC0,0xF0,0x00}, // -[-

	{0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00}, // -\-

	{0x78,0x18,0x18,0x18,0x18,0x18,0x78,0x00}, // -]-

	{0x20,0x70,0xA8,0x20,0x20,0x20,0x20,0x00}, // -^-

	{0x00,0x20,0x40,0xF8,0x40,0x20,0x00,0x00}, // -_-

	{0x20,0x10,0x08,0x00,0x00,0x00,0x00,0x00}, // -`-

	{0x00,0x00,0xE0,0x10,0x70,0x90,0x68,0x00}, // -a-

	{0x80,0x80,0xB0,0xC8,0x88,0xC8,0xB0,0x00}, // -b-

	{0x00,0x00,0x70,0x88,0x80,0x80,0x70,0x00}, // -c-

	{0x08,0x08,0x68,0x98,0x88,0x98,0x68,0x00}, // -d-

	{0x00,0x00,0x70,0x88,0xF0,0x80,0x70,0x00}, // -e-

	{0x30,0x48,0x40,0xF0,0x40,0x40,0x40,0x00}, // -f-

	{0x00,0x00,0x70,0x88,0x88,0x78,0x08,0xF0}, // -g-

	{0x80,0x80,0xB0,0xC8,0x88,0x88,0x88,0x00}, // -h-

	{0x20,0x00,0x00,0x20,0x20,0x20,0x20,0x00}, // -i-

	{0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x60}, // -j-

	{0x80,0x80,0x90,0xA0,0xC0,0xA0,0x98,0x00}, // -k-

	{0x60,0x20,0x20,0x20,0x20,0x20,0x70,0x00}, // -l-

	{0x00,0x00,0x50,0xA8,0xA8,0xA8,0xA8,0x00}, // -m-

	{0x00,0x00,0xB0,0x48,0x48,0x48,0x48,0x00}, // -n-

	{0x00,0x00,0x70,0x88,0x88,0x88,0x70,0x00}, // -o-

	{0x00,0x00,0xF0,0x88,0x88,0xF0,0x80,0x80}, // -p-

	{0x00,0x00,0x78,0x88,0x88,0x78,0x08,0x08}, // -q-

	{0x00,0x00,0xB0,0x48,0x40,0x40,0x40,0x00}, // -r-

	{0x00,0x00,0x78,0x80,0x70,0x08,0xF0,0x00}, // -s-

	{0x40,0x40,0xF8,0x40,0x40,0x48,0x30,0x00}, // -t-

	{0x00,0x00,0x90,0x90,0x90,0x90,0x68,0x00}, // -u-

	{0x00,0x00,0x88,0x88,0x88,0x50,0x20,0x00}, // -v-

	{0x00,0x00,0xA8,0xA8,0xA8,0xA8,0x50,0x00}, // -w-

	{0x00,0x00,0x88,0x50,0x20,0x50,0x88,0x00}, // -x-

	{0x00,0x00,0x88,0x88,0x98,0x68,0x08,0xF0}, // -y-

	{0x00,0x00,0xF8,0x10,0x20,0x40,0xF8,0x00}, // -z-

	{0x20,0x40,0x40,0x80,0x40,0x40,0x20,0x00}, // -{-

	{0x20,0x20,0x20,0x00,0x20,0x20,0x20,0x00}, // -|-

	{0x20,0x10,0x10,0x08,0x10,0x10,0x20,0x00}, // -},-

	{0x00,0x00,0x40,0xA8,0x10,0x00,0x00,0x00}, // -~-

	{0xA8,0x50,0xA8,0x50,0xA8,0x50,0xA8,0x00}, // --
};



/*
const u8 AsciiCode[96][8] = 
{
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0xFA,0x00,0x00,0x00,0x00,0x00},
	{0x00,0xE0,0x00,0xE0,0x00,0x00,0x00,0x00},
	{0x28,0xFE,0x28,0xFE,0x28,0x00,0x00,0x00},
	{0x24,0x74,0xDE,0x54,0x48,0x00,0x00,0x00},
	{0xC4,0xC8,0x10,0x26,0x46,0x00,0x00,0x00},
	{0x6C,0x92,0x6A,0x04,0x0A,0x00,0x00,0x00},
	{0x00,0x20,0xC0,0x80,0x00,0x00,0x00,0x00},
	{0x00,0x38,0x44,0x82,0x00,0x00,0x00,0x00},
	{0x00,0x82,0x44,0x38,0x00,0x00,0x00,0x00},
	{0x44,0x28,0xFE,0x28,0x44,0x00,0x00,0x00},
	{0x10,0x10,0xFE,0x10,0x10,0x00,0x00,0x00},
	{0x02,0x0C,0x08,0x00,0x00,0x00,0x00,0x00},
	{0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00},
	{0x00,0x06,0x06,0x00,0x00,0x00,0x00,0x00},
	{0x04,0x08,0x10,0x20,0x40,0x00,0x00,0x00},
	{0x7C,0x8A,0x92,0xA2,0x7C,0x00,0x00,0x00},
	{0x00,0x42,0xFE,0x02,0x00,0x00,0x00,0x00},
	{0x46,0x8A,0x92,0x92,0x62,0x00,0x00,0x00},
	{0x84,0x82,0x92,0xB2,0xCC,0x00,0x00,0x00},
	{0x18,0x28,0x48,0xFE,0x08,0x00,0x00,0x00},
	{0xE4,0xA2,0xA2,0xA2,0x9C,0x00,0x00,0x00},
	{0x3C,0x52,0x92,0x92,0x8C,0x00,0x00,0x00},
	{0x80,0x8E,0x90,0xA0,0xC0,0x00,0x00,0x00},
	{0x6C,0x92,0x92,0x92,0x6C,0x00,0x00,0x00},
	{0x62,0x92,0x92,0x94,0x78,0x00,0x00,0x00},
	{0x00,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00},
	{0x02,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00},
	{0x10,0x28,0x44,0x82,0x00,0x00,0x00,0x00},
	{0x28,0x28,0x28,0x28,0x28,0x00,0x00,0x00},
	{0x00,0x82,0x44,0x28,0x10,0x00,0x00,0x00},
	{0x40,0x80,0x9A,0xA0,0x40,0x00,0x00,0x00},
	{0x7C,0x82,0xBA,0xAA,0x7A,0x00,0x00,0x00},
	{0x3E,0x48,0x88,0x48,0x3E,0x00,0x00,0x00},
	{0xFE,0x92,0x92,0x92,0x6C,0x00,0x00,0x00},
	{0x7C,0x82,0x82,0x82,0x44,0x00,0x00,0x00},
	{0xFE,0x82,0x82,0x82,0x7C,0x00,0x00,0x00},
	{0xFE,0x92,0x92,0x92,0x82,0x00,0x00,0x00},
	{0xFE,0x90,0x90,0x90,0x80,0x00,0x00,0x00},
	{0x7C,0x82,0x8A,0x8A,0x4E,0x00,0x00,0x00},
	{0xFE,0x10,0x10,0x10,0xFE,0x00,0x00,0x00},
	{0x00,0x82,0xFE,0x82,0x00,0x00,0x00,0x00},
	{0x04,0x02,0x82,0xFC,0x80,0x00,0x00,0x00},
	{0xFE,0x10,0x28,0x44,0x82,0x00,0x00,0x00},
	{0xFE,0x02,0x02,0x02,0x02,0x00,0x00,0x00},
	{0xFE,0x40,0x30,0x40,0xFE,0x00,0x00,0x00},
	{0xFE,0x20,0x10,0x08,0xFE,0x00,0x00,0x00},
	{0x7C,0x82,0x82,0x82,0x7C,0x00,0x00,0x00},
	{0xFE,0x90,0x90,0x90,0x60,0x00,0x00,0x00},
	{0x7C,0x82,0x8A,0x84,0x7A,0x00,0x00,0x00},
	{0xFE,0x90,0x98,0x94,0x62,0x00,0x00,0x00},
	{0x64,0x92,0x92,0x92,0x4C,0x00,0x00,0x00},
	{0x80,0x80,0xFE,0x80,0x80,0x00,0x00,0x00},
	{0xFC,0x02,0x02,0x02,0xFC,0x00,0x00,0x00},
	{0xF8,0x04,0x02,0x04,0xF8,0x00,0x00,0x00},
	{0xFE,0x04,0x18,0x04,0xFE,0x00,0x00,0x00},
	{0xC6,0x28,0x10,0x28,0xC6,0x00,0x00,0x00},
	{0xC0,0x20,0x1E,0x20,0xC0,0x00,0x00,0x00},
	{0x86,0x8A,0x92,0xA2,0xC2,0x00,0x00,0x00},
	{0xFE,0xFE,0x82,0x82,0x00,0x00,0x00,0x00},
	{0x40,0x20,0x10,0x08,0x04,0x00,0x00,0x00},
	{0x00,0x82,0x82,0xFE,0xFE,0x00,0x00,0x00},
	{0x20,0x40,0xFE,0x40,0x20,0x00,0x00,0x00},
	{0x10,0x38,0x54,0x10,0x10,0x00,0x00,0x00},
	{0x00,0x00,0x80,0x40,0x20,0x00,0x00,0x00},
	{0x24,0x2A,0x2A,0x1C,0x02,0x00,0x00,0x00},
	{0xFE,0x14,0x22,0x22,0x1C,0x00,0x00,0x00},
	{0x1C,0x22,0x22,0x22,0x10,0x00,0x00,0x00},
	{0x1C,0x22,0x22,0x14,0xFE,0x00,0x00,0x00},
	{0x1C,0x2A,0x2A,0x2A,0x10,0x00,0x00,0x00},
	{0x10,0x7E,0x90,0x90,0x40,0x00,0x00,0x00},
	{0x19,0x25,0x25,0x25,0x1E,0x00,0x00,0x00},
	{0xFE,0x10,0x20,0x20,0x1E,0x00,0x00,0x00},
	{0x00,0x00,0x9E,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x01,0x11,0x9E,0x00,0x00,0x00,0x00},
	{0xFE,0x08,0x14,0x22,0x02,0x00,0x00,0x00},
	{0x00,0x82,0xFE,0x02,0x00,0x00,0x00,0x00},
	{0x1E,0x20,0x1E,0x20,0x1E,0x00,0x00,0x00},
	{0x20,0x1E,0x20,0x20,0x1E,0x00,0x00,0x00},
	{0x1C,0x22,0x22,0x22,0x1C,0x00,0x00,0x00},
	{0x3F,0x24,0x24,0x24,0x18,0x00,0x00,0x00},
	{0x18,0x24,0x24,0x24,0x3F,0x00,0x00,0x00},
	{0x20,0x1E,0x20,0x20,0x10,0x00,0x00,0x00},
	{0x12,0x2A,0x2A,0x2A,0x24,0x00,0x00,0x00},
	{0x20,0xFC,0x22,0x22,0x24,0x00,0x00,0x00},
	{0x3C,0x02,0x02,0x3C,0x02,0x00,0x00,0x00},
	{0x38,0x04,0x02,0x04,0x38,0x00,0x00,0x00},
	{0x3C,0x02,0x3C,0x02,0x3C,0x00,0x00,0x00},
	{0x22,0x14,0x08,0x14,0x22,0x00,0x00,0x00},
	{0x39,0x05,0x05,0x09,0x3E,0x00,0x00,0x00},
	{0x22,0x26,0x2A,0x32,0x22,0x00,0x00,0x00},
	{0x10,0x6C,0x82,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0xEE,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x82,0x6C,0x10,0x00,0x00,0x00},
	{0x10,0x20,0x10,0x08,0x10,0x00,0x00,0x00},
	{0xAA,0x54,0xAA,0x54,0xAA,0x00,0x00,0x00}
};
*/

//void Delay_ms(__IO u32 nCount)	 //简单的延时函数
//{
//	for(; nCount != 0; nCount--);
//} 

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void LED_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOC的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);

	/*选择要控制的GPIOC引脚*/															   
	GPIO_InitStructure.GPIO_Pin = MAX7219_CLK_PIN | Max7219_CS_PIN | Max7219_DIN_PIN;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOC*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);			  

	/* 关闭所有led灯	*/
	GPIO_SetBits(GPIOA, MAX7219_CLK_PIN | Max7219_CS_PIN | Max7219_DIN_PIN);	 
	
	/*MAX7219初始化*/
	
}



//--------------------------------------------
//功能：向MAX7219(U3)写入字节
//入口参数：DATA 
//出口参数：无
//说明：
void Write_Max7219_byte(u8 DATA)         
{
	u8 i = 0;    
	Max7219_CS(OFF);		
	for(i=1; i<=8; ++i)
	{		  
		MAX7219_CLK(OFF);
		Max7219_DIN(DATA&0x80);
		DATA=DATA<<1;
		MAX7219_CLK(ON);
	}                                 
}
//-------------------------------------------
//功能：向MAX7219写入数据
//入口参数：address、dat
//出口参数：无
//说明：
void Write_Max7219(u8 address,u8 dat)
{ 
	 Max7219_CS(OFF);
	 Write_Max7219_byte(address);           //写入地址，即数码管编号
	 Write_Max7219_byte(dat);               //写入数据，即数码管显示数字 
	 Max7219_CS(ON);                        
}

void Init_MAX7219(void)
{
	Write_Max7219(0x09, 0x00);       //译码方式：BCD码
	Write_Max7219(0x0a, 0x03);       //亮度 
	Write_Max7219(0x0b, 0x07);       //扫描界限；8个数码管显示
	Write_Max7219(0x0c, 0x01);       //掉电模式：0，普通模式：1
	Write_Max7219(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0
}