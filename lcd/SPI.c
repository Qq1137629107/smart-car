#include "drivers.h"


void SPI_WR_Byte(u8 dat, u8 cmd)
{
	u8 i;
	if (cmd)
		RS=1;
	else
		RS=0;
	CS=0;
	for (i = 0; i < 8; i++)
	{
		SCK=0;
		if (dat & 0x80)
		{
			SDA=1;
		}
		else
			SDA=0;
		SCK=1;
		dat <<= 1;
	}
	CS=1;
	RS=1;
}
void OLED_Set_Pos(u8 x, u8 y)
{
	OLED_WR_Byte(0xb0 + y, SEND_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, SEND_CMD);
	OLED_WR_Byte((x & 0x0f), SEND_CMD);
}