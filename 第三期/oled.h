#ifndef __OLED_H
#define __OLED_H			  	 
#include <REG51.H>
#include <public.h>
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


#endif  