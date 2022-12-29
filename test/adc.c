#include "commom.h"

void spi_write_byte(u8 byte)
{
    u8 i;

    CLK=0;
    for(i=0;i<8;i++)
    {
        DIN=byte>>7;
        byte<<=1;
        CLK=1;
        CLK=0;
    }

}

u16 spi_read_xpt2046_data()
{
    u8 i;
    u16 dat;
    CLK=0;
    for(i=0;i<12;i++)
    {
        dat<<=1;
        CLK=1;
        CLK=0;
        dat|=DOUT;
    }
    return dat;
}

u16 read_xpt2046_adc_value(u8 cmd)
{
    u16 adc_value;
    u8 i=0;
    CS=0;
    CLK=0;
    spi_write_byte(cmd);
    CLK=0;
    CLK=1;
    adc_value=spi_read_xpt2046_data();
    CS=1;
    return adc_value;

}