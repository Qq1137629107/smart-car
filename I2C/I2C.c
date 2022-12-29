#include "I2C.H"

void i2c_start(void)
{
	SDA=1;
	SCL=1;
	Delay10us();
	SDA=0;
	Delay10us();
	SCL=0;
}

void i2c_stop(void)
{
	SDA=0;
	SCL=1;
	Delay10us();
	SDA=1;
	Delay10us();
}

void i2c_ack(void)
{
	SCL=0;
	SDA=0;
	Delay10us();
	SCL=1;
	Delay10us();
	SCL=0;
}

void i2c_nack(void)
{
	SCL=0;
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();
	SCL=0;
}

u8 i2c_wait_ack(void)
{
	u8 time_temp=0;
	SCL=1;
	Delay10us();
	
	while(SDA)
	{
		time_temp++;
		if(time_temp>100)
		{
			i2c_stop();
			return 1;
		}
	}
	SCL=0;
	return 0;
}

void i2c_send_byte(u8 dat)
{
	u8 i=0;
	
	SCL=0;
	for(i=0;i<8;i++)
	{
		if((dat&0x80)>0)
			SDA=1;
		else
			SDA=0;
		dat<<=1;
		SCL=1;
		Delay10us();
		SCL=0;
		Delay10us();
	}
}
u8 i2c_read_byte(u8 ack)
{
	u8 i=0;
	u8 receive=0;
	for(i=0;i<8;i++)
	{
		SCL=0;
		Delay10us();
		SCL=1;
		Delay10us();
		receive<<=1;
		if(SDA)
			receive++;
	}
	if(!ack)
		i2c_nack();
	else
		i2c_ack();
	return receive;
}










