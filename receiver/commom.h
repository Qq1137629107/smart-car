#ifndef _COMMOM_H
#define _COMMOM_H
#include <STC15F2K60S2.H>


//----------public----------//

typedef unsigned char U8;
typedef unsigned int U16;
typedef unsigned long U32;

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned int u32;

//----------public----------//


//----------nrf-------------//
sbit CE=P5^5;
sbit SCK=P5^4;
sbit MISO=P1^5;
sbit IRQ=P1^4;
sbit MOSI=P1^3;
sbit CSN=P1^2;
sbit PWM=P3^7;

#define TX_ADR_WIDTH		5				//发送/接收地址宽度
#define TX_PLOAD_WIDTH		6				//数据通道有效数据宽度
#define WR_SETUP_AW			0x23			//写设置地址宽度寄存器
#define WR_RF_SETUP			0x26			//写设置无线发射速率、功耗寄存器
#define WR_EN_AA			0x21			//写设置自动应答功能寄存器
#define WR_EN_RXADDR		0x22			//写设置使能接收地址寄存器
#define WR_RX_ADDR_P0		0x2A			//写通道0接收数据地址寄存器
#define WR_SETUP_RETR		0x24			//写设置自动重发寄存器
#define	RFSETUP		        (RATE_1Mbps | E01ML01SP4_20dBm)	   //RF速率和发射功率
#define RATE_1Mbps			0x00			//1M速率
#define WR_RX_PW_P0			0x31			//写通道0接收有效数据宽度寄存器
#define E01ML01SP4_20dBm	0x06			//成都亿佰特模块20dBm
#define RETE_VAL			((AUTO_RESEND_TIME/250-1)<<4) + AUTO_RESEND_NUM 	//自动重发配置值
#define	AUTO_RESEND_TIME	500				//自动重发时间间隔，单位uS，必须是250的整数倍，最大4000uS，不启用ACK请忽略此项
#define	AUTO_RESEND_NUM		15				//自动重发次数，最多15次，不启用ACK请忽略此项
#define WR_CONFIG			0x20			//写配置寄存器
#define WR_STATUS			0x27			//写状态寄存器
#define STATUS				0x07			//状态寄存器
#define RX_DR				0x40			//接收成功
#define RD_RX_PLOAD			0x61  			//定义读有效接收数据寄存器指令
#define FLUSH_RX			0xE2			//定义清洗接收缓冲区FIFO寄存器指令
#define WR_RF_CH			0x25			//写设置无线频道寄存器
#define OFF           0
#define ON            1

void RF24_SetRfCh(U8 ch);							//nRF24L01P+工作频道设置
void RF24_Init();									//nRF24L01P+初始化
void RF24_RX_Mode(U8 *SelfAddr);								//nRF24L01P+设置为接收模式
bit RF24_RxData(U8 *rxbuf);							//nRF24L01P+判断是否收到数据，若收到直接取出，应在主循环中调用

//----------nrf-------------//

#define SEND_CMD  0	
#define SEND_DATA 1	
#define SET_MODE 0

sbit SCL=P3^3;
sbit SDA=P3^6;

#define SIZE 16

#define Max_Column	128

void delay_ms(unsigned int ms);

void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(u8 x, u8 y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void Delay_50ms(u8 Del_50ms);
void Delay_1ms(u32 Del_1ms);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(u8 IIC_Command);
void Write_IIC_Data(u8 IIC_Data);
void Write_IIC_Byte(u8 IIC_Byte);
void IIC_Wait_Ack();

								 


#endif


