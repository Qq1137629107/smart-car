#include "drivers.h"

sbit PWM=P1^0;
sbit K4=P3^3;
sbit K3=P3^2;


void main ()
	
{  

	LCDA=1;
	Lcd_Init();
	Lcd_Clear();
	Lcd_ShowChar(0,0,'6');
	while(1)
	{
	
	}
}

