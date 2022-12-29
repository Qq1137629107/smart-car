#include "commom.h"


void main()
{
    u16 adc_value;
    float adc_vol;
    u8 adc_buf[6];
    OLED_Init();
    OLED_Clear();
		EA=0;
    init_adc();
	  EA=1;

    while (1) {
        adc_value  = read_xpt2046_adc_value(0x94);
        adc_vol    = 5.0 * adc_value / 4096;
        adc_value  = adc_vol * 1000;
        adc_buf[0] = adc_value / 1000 + 48;
        adc_buf[1] = adc_value / 100 % 10 + 48;
        adc_buf[2] = adc_value / 10 % 100 % 10 + 48;
        adc_buf[3] = adc_value % 1000 % 100 % 10 + 48;
        OLED_ShowString(0, 0, adc_buf);
				adc_buf[5]=read_adc1_value(0);
				Delay100us();
			  OLED_ShowString(0, 3,adc_buf);

    }
}