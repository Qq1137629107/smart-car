#include "cmd_data.h"
#include "oled.h"
#include "oledfont.h"  	 

//IIC_PART

void IIC_Start()
{
	SCL = 1; SDA = 1; SDA = 0; SCL = 0;
}

void IIC_Stop()
{
	SCL = 1; SDA = 0; SDA = 1;
}

void IIC_Wait_Ack()
{
	SCL = 1; SCL = 0;
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
		else SDA = 0;
		da = da << 1;
		SCL = 1; SCL = 0;
	}
}

void Write_IIC_CMD(u8 IIC_CMD)
{
	IIC_Start();
	Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();
	Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_CMD);
	IIC_Wait_Ack();
	IIC_Stop();
}

void Write_IIC_Data(u8 IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();
	IIC_Stop();
}

//OLED_PART

void OLED_WR_Byte(u16 dat, u16 cmd)
{
	if (cmd)
	{
		Write_IIC_Data(dat);
	}
	else
	{
		Write_IIC_CMD(dat);
	}
}

void OLED_Set_Pos(u8 x, u8 y)
{
	OLED_WR_Byte(0xb0 + y, SEND_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, SEND_CMD);
	OLED_WR_Byte((x & 0x0f), SEND_CMD);
}

void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D, SEND_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14, SEND_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF, SEND_CMD);  //DISPLAY ON
}

void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D, SEND_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10, SEND_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE, SEND_CMD);  //DISPLAY OFF
}

void OLED_Clear(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, SEND_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte(0x00, SEND_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte(0x10, SEND_CMD);      //������ʾλ�á��иߵ�ַ   
		for (n = 0; n < 128; n++)OLED_WR_Byte(0, SEND_DATA);
	}
}
void OLED_On(void)
{
	u8 i, n;
	for (i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, SEND_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte(0x00, SEND_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte(0x10, SEND_CMD);      //������ʾλ�á��иߵ�ַ   
		for (n = 0; n < 128; n++)OLED_WR_Byte(1, SEND_DATA);
	} //������ʾ
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 Char_Size)
{
	
	u8 c = 0, i = 0;
	c = chr - ' ';//�õ�ƫ�ƺ��ֵ			
	if (x > Max_Column - 1)
	{
		x = 0; y = y + 2;
	}

	if (Char_Size == 16)
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i], SEND_DATA);
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i + 8], SEND_DATA);
	}
	else
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i < 6; i++)
			OLED_WR_Byte(F6x8[c][i], SEND_DATA);
	}
}
//m^n����
u32 oled_pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)result *= m;
	return result;
}
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2)
{
	u8 t, temp;
	u8 enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				OLED_ShowChar(x + (size2 / 2) * t, y, ' ', size2);
				continue;
			}
			else enshow = 1;

		}
		OLED_ShowChar(x + (size2 / 2) * t, y, temp + '0', size2);
	}
}

void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 Char_Size)
{
	u8 j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j], Char_Size);
		x += 8;
		if (x > 120) 
		{ 
			x = 0; y += 2; 
		}
		j++;
	}
}

void OLED_ShowCHinese(u8 x, u8 y, u8 no)
{
	u8 t, adder = 0;
	OLED_Set_Pos(x, y);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_Byte(Hzk[2 * no][t], SEND_DATA);
		adder += 1;
	}
	OLED_Set_Pos(x, y + 1);
	for (t = 0; t < 16; t++)
	{
		OLED_WR_Byte(Hzk[2 * no + 1][t], SEND_DATA);
		adder += 1;
	}	
}
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
{
	u32 j = 0;
	u8 x, y;

	if (y1 % 8 == 0) y = y1 / 8;
	else y = y1 / 8 + 1;
	for (y = y0; y < y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++)
		{
			OLED_WR_Byte(BMP[j++], SEND_DATA);
		}
	}
}

void OLED_Init(void)
{
	u8 i = 0;
	while (i < 27)
	{
		OLED_WR_Byte(cmd_data[i], SEND_CMD);
		i++;
	}
}


