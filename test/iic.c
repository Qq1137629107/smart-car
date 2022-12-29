#include"commom.h"


void IIC_Start()
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
	SCL = 0;
}

void IIC_Stop()
{
	SCL = 1; 
	SDA = 0;
	SDA = 1;
}

void IIC_Wait_Ack()
{
	SCL = 1; 
	SCL = 0;
}

void Write_IIC_Byte(u8 IIC_Byte)
{
	u8 i;
	u8 m, da;
	da = IIC_Byte;
	SCL = 0;
	for (i = 0; i < 8; i++)
	{
		m = da;
		m = m & 0x80;
		if (m == 0x80)
		{
			SDA = 1;
		}
		else 
			SDA = 0;
		da = da << 1;
		SCL = 1; 
		SCL = 0;
	}
}

void Write_IIC_CMD(u8 IIC_CMD)
{
	IIC_Start();
	Write_IIC_Byte(0x78);   
	IIC_Wait_Ack();
	Write_IIC_Byte(0x00);
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_CMD);
	IIC_Wait_Ack();
	IIC_Stop();
}

void Write_IIC_Data(u8 IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);		
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40);		
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();
	IIC_Stop();
}
