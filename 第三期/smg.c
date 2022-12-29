#include "smg.h"

sbit SW1=P3^0;
sbit SW2=P3^1;
sbit SW3=P3^2;
static u8 x, y;

extern u8 s1;


u8 Smg_Display[20]={0x14,0xd7,0x4c,0x45,0x87,0x25,0x24,0x57,0x04,0x05,
                    0x10,0xd3,0x48,0x41,0x83,0x21,0x20,0x53,0x00,0x01};

void Hc595_Send_Dat2(u8 dat)
{
  u8 i=0;
	for(i=0 ;i<8;i++)
	{
		SER2=dat>>7;
		dat<<=1;
		SRCLK2=0;
		SRCLK2=1;
	}
	RCLK2=0;
	RCLK2=1;
}

void delay2_5ms(u8 ms)
{
	u8 T = 0;
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x00;		//设置定时初始值
	TH0 = 0xE5;		//设置定时初始值	
	TR0 = 1;		//定时器0开始计时
  
	while (T < ms)
	{
		if (TF0 == 1)
		{
			TF0 = 0;
			T++;
		}
	}
}


void flash()
{
	S3=0;
	S2=1;
	S1=1;
	S0=1;
	Hc595_Send_Dat2(Smg_Display[y%10]);
	delay2_5ms(1);
	Hc595_Send_Dat2(0xff);   

	S3=1;
	S2=0;
	S1=1;
	S0=1;
	Hc595_Send_Dat2(Smg_Display[y/10%10]);
	delay2_5ms(1);
	Hc595_Send_Dat2(0xff);   
	
	S3=1;
	S2=1;
	S1=0;
	S0=1;
	Hc595_Send_Dat2(Smg_Display[x%10+10]);
	delay2_5ms(1);
	Hc595_Send_Dat2(0xff);
	
	S3=1;
	S2=1;
	S1=1;
	S0=0;
	Hc595_Send_Dat2(Smg_Display[x/10%10]);
	delay2_5ms(1);
	Hc595_Send_Dat2(0xff);
}	

void timer()
{
	u8 T = 0;
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x00;		//设置定时初始值
	TH0 = 0xE5;		//设置定时初始值	
	flash();
	TR0 = 1;
	while (T < 80)
	{
		if (TF0 == 1)
		{
			TF0 = 0; 
			flash();  
			T++;
		}
	}
}

void jishiqi()
{
	
	while (1)
	{
		y++;
		if (y > 59)
		{
		x++;
		y = 0;
		}
						
		if (x > 59)
		{
			x = 0;
		}
						
		timer();
		if(SW2==0&&SW3==0)	
			return;
		if(SW3==0)
		{
			while(!SW3);
			if(s1==1)
			s1=2;
			TR0=0;
			while(1)
			{
				flash();
				if(SW1==0)
				{
					while(!SW1);
						x++;
					if(x>59)x=0;
				}
				if(SW2==0)
				{
					while(!SW2);
						y++;
					if(x>59)y=0;
				}
				if(SW3==0)
				{
					if(s1==2)
					s1=1;
					break;
				}
			}
		}
	}
}