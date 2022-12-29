#include <public.h>

void delay_ms(u16 ms)
{                         
	u16 a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}
