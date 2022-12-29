#ifndef _BEEPLED_H
#define _BEEPLED_H
#include "public.h"

sbit SRCLK1=P1^3;
sbit RCLK1=P1^2;
sbit SER1=P1^4;

void Hc595_Send_Dat1(u8 dat);
void beepled();
void breath();

#endif