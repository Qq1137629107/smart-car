#include "public.h"
// ch3=p14;ch4=p15;ch1=p17;ch2=p16
// p4.7=菜单；右=p31 左p30
//下p32 上p35 左37 右36
// p10电源输入检测

u8 SelfAddr[TX_ADR_WIDTH] = {0x01, 0x01, 0x01, 0x01, 0x01};				//±¾»úÓ²¼þµØÖ·
u8 txbuf[TX_PLOAD_WIDTH];
u8 adc_buf[4];

void main()
{
    u16 i;
    u8 adc_buf[6];
	  P4SW = 0x70; //允许P4 IO
    P2M0 = 0x20; //推挽输出
		EA=0;
    init_adc();
		EA=1;
    Lcd_Init();
    Lcd_Clear();
   RF24_Init();
    RF24_TX_Mode(SelfAddr);
	  RF24_SetRfCh(40);
    while (1) 
    {
      txbuf[i]=read_adc_value(i+4);
      RF24_TxData(txbuf);
      adc_buf[0]=read_adc_value(i+4)/100+48;
      adc_buf[1]=read_adc_value(i+4)/10%10+48;
      adc_buf[2]=read_adc_value(i+4)%100%10+48;
      Lcd_ShowString(0,i*2,adc_buf);
      i++;
      if(i==4)i=0;
    }
}