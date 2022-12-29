#ifndef _SMG_H
#define _SMG_H
#include <public.h>

sbit S0=P3^3;
sbit S1=P5^5;
sbit S2=P1^5;
sbit S3=P5^4;

sbit SRCLK2=P3^6;
sbit RCLK2=P3^7;
sbit SER2=P1^1;
void flash();
void timer();
void Hc595_Send_Dat2(u8 dat);
void delay2_5ms(u8 ms);
void jishiqi();	

										
#endif