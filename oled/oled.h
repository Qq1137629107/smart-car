#ifndef __OLED_H
#define __OLED_H			  	 
#include <STC15F2K60S2.H>
#include <public.h>
#define SEND_CMD  0	
#define SEND_DATA 1	
#define SET_MODE 0

sbit SCL=P3^0;
sbit SDA=P1^0;

#define SIZE 16

#define Max_Column	128

void delay_ms(unsigned int ms);

void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(u8 x, u8 y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void Delay_50ms(u8 Del_50ms);
void Delay_1ms(u32 Del_1ms);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(u8 IIC_Command);
void Write_IIC_Data(u8 IIC_Data);
void Write_IIC_Byte(u8 IIC_Byte);
void IIC_Wait_Ack();

#endif  