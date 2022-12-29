#ifndef _commom_h
#define _commom_h
#include <STC12C5A60S2.H>

//----------------------public

typedef unsigned char u8;
typedef unsigned int u16;

//----------------------public


//----------------------oled

sbit SDA=P0^1;
sbit SCL=P0^0;

void IIC_Start();
void IIC_Stop();
void Write_IIC_CMD(u8 IIC_CMD);
void Write_IIC_Data(u8 IIC_Data);
void Write_IIC_Byte(u8 IIC_Byte);
void IIC_Wait_Ack();

#define SEND_CMD  0	
#define SEND_DATA 1	
#define SIZE 16
#define Max_Column	128   						  				   

void OLED_WR_Byte(unsigned dat,unsigned cmd);  	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(u8 x, u8 y);

//----------------------oled


//----------------------adc1
#define ADC_POWER       0x80
#define ADC_SPEEDLL     0x00
#define ADC_START       0x08
#define ADC_FLAG        0x10

void init_adc();
u8 read_adc1_value(u8 ch);


#endif