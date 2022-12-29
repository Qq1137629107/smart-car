#ifndef _DRIVERS_H
#define _DRIVERS_H

//------public
#include <reg51.h>
typedef unsigned char u8;
void Delay100ms();
//------public

//------lcd
#define CMD  0	
#define DATA 1	

sbit	CS=P0^0;
sbit	RST=P0^1;
sbit	RS=P0^2;
sbit	SDA=P0^3;
sbit	SCK=P0^4;
sbit	LCDA=P0^5;

void Lcd_Init();
void Lcd_Clear();
void Lcd_ShowChar(u8 x, u8 y, u8 chr);
//------lcd




#endif