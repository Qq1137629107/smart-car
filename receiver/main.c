#include "commom.h"

U8 SelfAddr[TX_ADR_WIDTH] = {0x01, 0x01, 0x01, 0x01, 0x01};	
U8 rxbuf[TX_PLOAD_WIDTH];

U16 j;
u8 i;
void Timer0Init(void)		//8微秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xA0;		//设置定时初始值
	TH0 = 0xFF;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
}

void main()
{
	u8 rcv_buf[4];
	RF24_Init();
	RF24_RX_Mode(SelfAddr);		
	RF24_SetRfCh(40);
	OLED_Init();
    OLED_Clear(); //??'??LCDg??  
	
	Timer0Init();
	while(1)
	{
		bit b;
		b=RF24_RxData(rxbuf);
		j=rxbuf[0];
		if(b==0)P10=0;
		else P10=1;
		rcv_buf[0]=rxbuf[i]/100+48;
		rcv_buf[1]=rxbuf[i]/10%10+48;
		rcv_buf[2]=rxbuf[i]%100%10+48;
		OLED_ShowString(0,i*2,rcv_buf,12);
		i++;
		if(i==4)i=0;
	}
}

void timer() interrupt 1
{
	static u16 k;
	if(k<j+64)
	{
		PWM=1;
	}
	else 
	{
		PWM=0;
	}
	k++;
	if(k==2560)k=0;
	
}	