#ifndef _IIC_H
#define _IIC_H
#include "public.h"

sbit SDA=P1^0;
sbit SCL=P3^0;

void IIC_Start();
void IIC_Stop();
void Write_IIC_CMD(u8 IIC_CMD);
void Write_IIC_Data(u8 IIC_Data);
void Write_IIC_Byte(u8 IIC_Byte);
void IIC_Wait_Ack();

#endif