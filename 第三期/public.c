#include <public.h>

void Delay10ms()		//@33.1776MHz
{
	unsigned char i, j, k;

	i = 2;
	j = 67;
	k = 183;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay1000ms()		//@33.1776MHz
{
	u8 i, j, k;

	i = 127;
	j = 18;
	k = 107;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
