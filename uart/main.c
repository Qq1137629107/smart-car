#include <REG51.H>

typedef unsigned char u8;
typedef unsigned int u16;

sbit S=P3^1;

void uart_init(u8 baud)
{
	TMOD|=0x20;
	PCON=0x80;
	SCON=0x50;
	TH1=baud;
	TL1=baud;
	ES=1;
	EA=1;
	TR1=1;
}


void main()
{
	uart_init(0xfa);
	while(1)
	{

	}
}

void uart() interrupt 4
{
	u8 rec_dat=0;
	RI=0;
	rec_dat=SBUF;
	SBUF=rec_dat;
	while(!TI);
	TI=0;
}