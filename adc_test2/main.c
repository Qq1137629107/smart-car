#include "commom.h"

void main()
{
	u16 i;
	float j;
    u8 adc_buf[6];
    OLED_Init();
    OLED_Clear();
		EA=0;
    init_adc();
		EA=1;
    while(1)
    {
				i=read_adc1_value(6);
				j=i*5.0/256;
				i=j*1000;
				adc_buf[0] = i/ 1000 + 48;
        adc_buf[1] = i / 100 % 10 + 48;
        adc_buf[2] = i / 10 % 100 % 10 + 48;
        adc_buf[3] = i % 1000 % 100 % 10 + 48;
				OLED_ShowString(0, 0, adc_buf);
    }
}
