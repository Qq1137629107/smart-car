#ifndef _COMMOM_H
#define _COMMOM_H
#include <STC15F2K60S2.H>




//----------public----------//

typedef unsigned char U8;
typedef unsigned int U16;
typedef unsigned long U32;

typedef signed char S8;
typedef signed int S16;
typedef signed long S32;

//----------public----------//


//----------nrf-------------//

sbit CE=P1^2;
sbit SCK=P1^7;
sbit MISO=P1^6;
sbit IRQ=P1^4;
sbit MOSI=P1^1;
sbit CSN=P1^3;
sbit K1=P3^1;
sbit K2=P3^0;

#define TX_ADR_WIDTH		5				//发送/接收地址宽度
#define TX_PLOAD_WIDTH		6				//数据通道有效数据宽度
#define WR_RF_CH			0x25			//写设置无线频道寄存器
#define WR_SETUP_AW			0x23			//写设置地址宽度寄存器
#define WR_RF_SETUP			0x26			//写设置无线发射速率、功耗寄存器
#define WR_EN_AA			0x21			//写设置自动应答功能寄存器
#define WR_EN_RXADDR		0x22			//写设置使能接收地址寄存器
#define WR_RX_PW_P0			0x31			//写通道0接收有效数据宽度寄存器
#define	RFSETUP		        (RATE_1Mbps | E01ML01SP4_20dBm)	   //RF速率和发射功率
#define WR_SETUP_RETR		0x24			//写设置自动重发寄存器
#define WR_TX_ADDR			0x30			//写发送目标地址寄存器
#define RATE_1Mbps			0x00			//1M速率
#define RETE_VAL			((AUTO_RESEND_TIME/250-1)<<4) + AUTO_RESEND_NUM 	//自动重发配置值
#define E01ML01SP4_20dBm	0x06			//成都亿佰特模块20dBm
#define	AUTO_RESEND_TIME	500				//自动重发时间间隔，单位uS，必须是250的整数倍，最大4000uS，不启用ACK请忽略此项
#define	AUTO_RESEND_NUM		15				//自动重发次数，最多15次，不启用ACK请忽略此项
#define WR_CONFIG			0x20			//写配置寄存器
#define WR_RX_ADDR_P0		0x2A			//写通道0接收数据地址寄存器
#define WR_STATUS			0x27			//写状态寄存器
#define RPD					0x09			//接收功率检测寄存器
#define WR_TX_PLOAD			0xA0  			//定义写有效发送数据寄存器指令
#define STATUS				0x07			//状态寄存器
#define WR_STATUS			0x27			//写状态寄存器
#define TX_DS				0x20			//发送成功
#define FLUSH_TX			0xE1			//定义清洗发送缓冲区FIFO寄存器指令                                  
#define ON           1
#define OFF          0

void RF24_SetRfCh(U8 ch);							//nRF24L01P+工作频道设置
void RF24_Init();									//nRF24L01P+初始化
void RF24_TX_Mode(U8 *toAddr);						//nRF24L01P+设置为发送模式
bit RF24_TxData(U8 *txbuf);	//nRF24L01P+发送数据

//----------nrf-------------//


//----------IIC-------------//

sbit SDA=P0^0;
sbit SCL=P0^1                                                                             ;

void IIC_Start();
void IIC_Stop();
void Write_IIC_CMD(U8 IIC_CMD);
void Write_IIC_Data(U8 IIC_Data);
void Write_IIC_Byte(U8 IIC_Byte);
void IIC_Wait_Ack();

//----------IIC-------------//


//----------OLED------------//

#define SEND_CMD  0	
#define SEND_DATA 1	
#define SIZE 16
#define Max_Column	128   						  				   

void OLED_WR_Byte(unsigned dat,unsigned cmd);  	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(U8 x,U8 y,U8 chr);
void OLED_ShowString(U8 x,U8 y, U8 *p);	 
void OLED_Set_Pos(U8 x, U8 y);


#endif



























