#include "cmd_data.h"
#include "oled.h"
#include "oledfont.h"  	 
#include "iic.h"

void OLED_WR_Byte(u16 dat, u16 cmd)
{
	if (cmd)
	{
		Write_IIC_Data(dat);
	}
	else
	{
		Write_IIC_CMD(dat);
	}
}

void OLED_Set_Pos(u8 x, u8 y)
{
	OLED_WR_Byte(0xb0 + y, SEND_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, SEND_CMD);
	OLED_WR_Byte((x & 0x0f), SEND_CMD);
}

void OLED_Clear(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, SEND_CMD); 
		OLED_WR_Byte(0x00, SEND_CMD);      
		OLED_WR_Byte(0x10, SEND_CMD);      
		for (n = 0; n < 128; n++)OLED_WR_Byte(0, SEND_DATA);
	}
}

void OLED_ShowChar(u8 x, u8 y, u8 chr)
{
	u8 c = 0, i = 0;
	c = chr - ' ';		
	if (x > Max_Column - 1)
	{
		x = 0; y = y + 2;
	}

		OLED_Set_Pos(x, y);
		for (i = 0; i < 6; i++)
			OLED_WR_Byte(F6x8[c][i], SEND_DATA);
}


void OLED_ShowString(u8 x, u8 y, u8 *chr)
{
	u8 j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j]);
		x += 8;
		if (x > 120) 
		{ 
			x = 0; y += 2; 
		}
		j++;
	}
}

void OLED_Init(void)
{
	u8 i = 0;
	while (i < 27)
	{
		OLED_WR_Byte(cmd_data[i], SEND_CMD);
		i++;
	}
}


