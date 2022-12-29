#include "beepled.h"
#include "smg.h"
extern u8 s1;
extern u8 s2;
extern u8 s3;
extern u8 s4;
extern u8 k4;
u8 leds[7]={0xfd,0xf9,0xfb,0xfa,0xfe,0xfc,0xfd};
u8 Led[5]={64,32,16,8,64};
code u8 SONG_TONE[] = { 212,212,190,212,159,169,212,212,190,212,142,159,
212,212,106,106,126,159,169,190,119,119,119,126,159,142,159,0 };
void Hc595_Send_Dat1(u8 dat)
{
	u8 i=0;
	for(i=0 ;i<8;i++)
	{
		SER1=dat>>7;
		dat<<=1;
		SRCLK1=0;
		SRCLK1=1;
	}
	RCLK1=0;
	RCLK1=1;
	
}

void beepled()
{
	static u16 i, j, k;
	static u8 x, y, z, a, b,d;

	if (k4 == 1 && s2 == 1)
	{
		i++; k++;
	}
	else if (k4 == 1 && s2 == 0)
		k++;
	else if (k4 == 0 && s2 == 1)
		i++;
	if(k4==1||s2==1)	
	{
		if (k < s4)
			z = 128;
		else
			z = 0;

		if (k == SONG_TONE[a])
		{
			k = 0;
			b++;
			if (b == 70)
			{
				b = 0;
				a++;d++;
				if (a == 27)
					a = 0;
			}
		}
		if (i < j)
			Hc595_Send_Dat1(leds[x + 1] - Led[y + 1] - z);//ด๓
		else
			Hc595_Send_Dat1(leds[x] - Led[y] - z);//ะก
		if (i == s3)
		{
			i = 0; j++;
		}
		if (j == s3)
		{
			j = 0; x++; y++;
		}
		if (x == 6)x = 0;
		if (y == 4)y = 0;
	}
	if (k4 == 1 && s2 == 0)
	{
		if(d==5)
		{
			d=1;
			Hc595_Send_Dat2(0x00);
		}
		if(d==1)
		{
			S0=0;
			S1=1;
			S2=1;
			S3=1;
		}
		if(d==2)
		{
			S0=1;
			S1=0;
			S2=1;
			S3=1;
		}
		if(d==3)
		{
			S0=1;
			S1=1;
			S2=0;
			S3=1;
		}
		if(d==4)
		{
			S0=1;
			S1=1;
			S2=1;
			S3=0;
		}
	}
}

