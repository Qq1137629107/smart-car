#include "commom.h"

U8 SelfAddr[TX_ADR_WIDTH] = {0x01, 0x01, 0x01, 0x01, 0x01};				//本机硬件地址
U8 txbuf[TX_PLOAD_WIDTH];


void main()
{
	
	OLED_Init();
	OLED_Clear();
	RF24_Init();
	RF24_TX_Mode(SelfAddr);
	RF24_SetRfCh(40);
	txbuf[0]=15;
	while(1)
	{
		RF24_TxData(txbuf);
		OLED_ShowString(0,0,txbuf);
		if(K1==0)
		{
				while(!K1);
			txbuf[0]++;
			if(txbuf[0]>25)
			{
				txbuf[0]=25;
			}
		}		
		if(K2==0)
		{
				while(!K2);
			txbuf[0]--;
			if(txbuf[0]<5)
			{
				txbuf[0]=5;
			}
		}
		if(P32==0)
		{
			while(!P32);
			txbuf[0]=15;txbuf[0]=15;
		}
	}
}
