#include "smg.h"
#include "beepled.h"
#include "menu.h"
#include "oled.h"

extern u8 s0;
extern u8 s1;
extern u8 s2;

void Timer2Init(void)	
{
	AUXR |= 0x04;		
	T2L = 0x1d;		
	T2H = 0xfc;		
	AUXR |= 0x10;
	IE2|=0x04;
}

void all_breath()
{
	
	static u8 i,j,k,a=0x80,b=0xff,c;
	
	Hc595_Send_Dat2(0x00);
	i++;
	if(i<j)
	{
		S0=S1=S2=S3=k;
		Hc595_Send_Dat1(a);//大
	}
	else
	{
		Hc595_Send_Dat1(b);//小
	
		S0=S1=S2=S3=!k;
	}
	if(i==200)
	{
		i=0;j++;
	}
	if(j==200)
	{
		j=0;k=!k;c=a;a=b;b=c;
	}
}
void breath()
{
	
	static u8 i,j,a=0x80,b=0xff,c;

	i++;
	if(i<j)
	{
		Hc595_Send_Dat1(a);//大
	}
	else
	{
		Hc595_Send_Dat1(b);//小
	}
	if(i==200)
	{
		i=0;j++;
	}
	if(j==200)
	{
		j=0;c=a;a=b;b=c;
	}
}

void main ()
{
	EA=1;
	OLED_Init();			 
	OLED_Clear();
	Hc595_Send_Dat1(0xff);

	OLED_ShowString(36,3,"WELCOME");
	Delay1000ms();
	OLED_Clear();
	fun_0();
		
	Timer2Init();
	while(1)
	{
		key_scan();
		if(TR0==0)
			flash();
		if(s0==1)
		{
		
			if(s1==0)
			all_breath();
			
		}
	}
}


void time2() interrupt 12
{
	if(s1==1)
		breath();
	beepled();
}