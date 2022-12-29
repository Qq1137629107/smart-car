#include "AT24C02.H"
#include "I2C.H"


void at24c02_send_one_byte(u8 addr,u8 dat)
{
	i2c_start();
	i2c_send_byte(0xa0);
	i2c_wait_ack();
	i2c_send_byte(addr);
	i2c_wait_ack();
	i2c_send_byte(dat);
	i2c_wait_ack();
	i2c_stop();
	Delay10ms();
}

u8 at24c02_read_one_byte(u8 addr)
{
	u8 temp=0;
	i2c_start();
	i2c_send_byte(0xa0);
	i2c_wait_ack();
	i2c_send_byte(addr);
	i2c_wait_ack();
	i2c_start();
	i2c_send_byte(0xa1);
	i2c_wait_ack();
	temp=i2c_read_byte(0);
	i2c_stop();
	return temp;
}