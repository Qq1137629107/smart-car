#include "commom.h"

void init_adc()
{
    P1=P1M0=P1M1=0x70;
    ADC_RES=0;
    ADC_CONTR=ADC_POWER|ADC_SPEEDLL;
		
}

u8 read_adc1_value(u8 ch)
{
    ADC_CONTR=ADC_POWER|ADC_SPEEDLL|ch|ADC_START;
		
    while (!(ADC_CONTR&ADC_FLAG));
    ADC_CONTR&=~ADC_FLAG;
    return ADC_RES;
}