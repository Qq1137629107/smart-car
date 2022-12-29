#include "public.h"
#include "font.h"

void Spi_Write_Byte(u8 dat, u8 mode)
{
	u8 i;
	if (mode)
		RS=1;
	else
		RS=0;
	CS=0;
	for (i = 0; i < 8; i++){
		CLK=0;
		if (dat & 0x80)
		{
			SDA=1;
		}
		else
			SDA=0;
		CLK=1;
		dat <<= 1;
	}
	CS=1;
	RS=1;
}

void Lcd_Set_Pos(u8 x, u8 y)
{
	Spi_Write_Byte(0xb0 + y, CMD);
	Spi_Write_Byte(((x & 0xf0) >> 4) | 0x10, CMD);
	Spi_Write_Byte((x & 0x0f), CMD);
}

void Lcd_Clear()
{
	u8 i,j;
	for(i=0;i<8;i++)
	{
		Spi_Write_Byte(0xb0 + i, CMD);
		Spi_Write_Byte(0x00, CMD);
		Spi_Write_Byte(0x10, CMD);
		for(j=0;j<128;j++)
		{
			Spi_Write_Byte(0x00,DATA);
		}
	}
}

void Lcd_ShowChar(u8 x, u8 y, u8 chr)
{
	u8 c = 0, i = 0;
	c = chr - ' ';		
	if (x > 128 - 1)
	{
		x = 0; y = y + 2;
	}

		Lcd_Set_Pos(x, y);
		for (i = 0; i < 6; i++)
			Spi_Write_Byte(F6x8[c][i], DATA);
}


void Lcd_ShowString(u8 x, u8 y, u8 *chr)
{
	u8 j = 0;
	while (chr[j] != '\0')
	{
		Lcd_ShowChar(x, y, chr[j]);
		x += 8;
		if (x > 120) 
		{ 
			x = 0; y += 2; 
		}
		j++;
	}
}
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void Lcd_Init()
{
	RST=0;
	Delay100ms();
	RST=1;
	Spi_Write_Byte(0xe2, CMD);
	Spi_Write_Byte(0x2c, CMD);
	Spi_Write_Byte(0x2e, CMD);
	Spi_Write_Byte(0x2f, CMD);
	Spi_Write_Byte(0x23, CMD);
	Spi_Write_Byte(0x81, CMD);
	Spi_Write_Byte(0x28, CMD);
	Spi_Write_Byte(0xa2, CMD);
	Spi_Write_Byte(0xc8, CMD);
	Spi_Write_Byte(0xa0, CMD);
	Spi_Write_Byte(0x40, CMD);
	Spi_Write_Byte(0xaf, CMD);
	Lcd_Clear();
}