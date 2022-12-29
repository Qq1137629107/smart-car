#ifndef _public_h
#define _public_h
#include "STC12C5A60S2.H"

typedef unsigned char u8;
typedef unsigned int u16;


//----------------------adc

#define ADC_POWER       0x80
#define ADC_SPEEDLL     0x00
#define ADC_START       0x08
#define ADC_FLAG        0x10

void init_adc();
u8 read_adc_value(u8 ch);

//----------------------adc


//----------------------lcd
#define CMD  0	
#define DATA 1	

sbit CS=P0^4;
sbit RST=P0^3;
sbit RS=P0^2;
sbit SDA=P0^1;
sbit CLK=P0^0;
sbit LEDA=P4^6;

void Lcd_Init();
void Lcd_Clear();
void Lcd_ShowChar(u8 x, u8 y, u8 chr);
void Lcd_ShowString(u8 x, u8 y, u8 *chr);
//----------------------lcd


//----------------------nrf

#define	MOSI				P22				//主机输出，从机输入引脚（输出）
#define	MISO				P23				//主机输入，从机输出引脚（输入）
#define	SCK				P21				//主机输出，串行时钟引脚（输出）
#define	CSN					P27				//主机输出，从机选择引脚（输出到CSN，低电平有效）
#define	CE					P45				//芯片使能信号引脚（输出，I/O口配置为推挽）
#define	IRQ					P26				//来自NRF24L01的中断信号引脚（输入，低电平有效）

#define TX_ADR_WIDTH		5				//·¢ËÍ/½ÓÊÕµØÖ·¿í¶È
#define TX_PLOAD_WIDTH		6				//Êý¾ÝÍ¨µÀÓÐÐ§Êý¾Ý¿í¶È
#define WR_RF_CH			0x25			//Ð´ÉèÖÃÎÞÏßÆµµÀ¼Ä´æÆ÷
#define WR_SETUP_AW			0x23			//Ð´ÉèÖÃµØÖ·¿í¶È¼Ä´æÆ÷
#define WR_RF_SETUP			0x26			//Ð´ÉèÖÃÎÞÏß·¢ÉäËÙÂÊ¡¢¹¦ºÄ¼Ä´æÆ÷
#define WR_EN_AA			0x21			//Ð´ÉèÖÃ×Ô¶¯Ó¦´ð¹¦ÄÜ¼Ä´æÆ÷
#define WR_EN_RXADDR		0x22			//Ð´ÉèÖÃÊ¹ÄÜ½ÓÊÕµØÖ·¼Ä´æÆ÷
#define WR_RX_PW_P0			0x31			//Ð´Í¨µÀ0½ÓÊÕÓÐÐ§Êý¾Ý¿í¶È¼Ä´æÆ÷
#define	RFSETUP		        (RATE_1Mbps | E01ML01SP4_20dBm)	   //RFËÙÂÊºÍ·¢Éä¹¦ÂÊ
#define WR_SETUP_RETR		0x24			//Ð´ÉèÖÃ×Ô¶¯ÖØ·¢¼Ä´æÆ÷
#define WR_TX_ADDR			0x30			//Ð´·¢ËÍÄ¿±êµØÖ·¼Ä´æÆ÷
#define RATE_1Mbps			0x00			//1MËÙÂÊ
#define RETE_VAL			((AUTO_RESEND_TIME/250-1)<<4) + AUTO_RESEND_NUM 	//×Ô¶¯ÖØ·¢ÅäÖÃÖµ
#define E01ML01SP4_20dBm	0x06			//³É¶¼ÒÚ°ÛÌØÄ£¿é20dBm
#define	AUTO_RESEND_TIME	500				//×Ô¶¯ÖØ·¢Ê±¼ä¼ä¸ô£¬µ¥Î»uS£¬±ØÐëÊÇ250µÄÕûÊý±¶£¬×î´ó4000uS£¬²»ÆôÓÃACKÇëºöÂÔ´ËÏî
#define	AUTO_RESEND_NUM		15				//×Ô¶¯ÖØ·¢´ÎÊý£¬×î¶à15´Î£¬²»ÆôÓÃACKÇëºöÂÔ´ËÏî
#define WR_CONFIG			0x20			//Ð´ÅäÖÃ¼Ä´æÆ÷
#define WR_RX_ADDR_P0		0x2A			//Ð´Í¨µÀ0½ÓÊÕÊý¾ÝµØÖ·¼Ä´æÆ÷
#define WR_STATUS			0x27			//Ð´×´Ì¬¼Ä´æÆ÷
#define RPD					0x09			//½ÓÊÕ¹¦ÂÊ¼ì²â¼Ä´æÆ÷
#define WR_TX_PLOAD			0xA0  			//¶¨ÒåÐ´ÓÐÐ§·¢ËÍÊý¾Ý¼Ä´æÆ÷Ö¸Áî
#define STATUS				0x07			//×´Ì¬¼Ä´æÆ÷
#define WR_STATUS			0x27			//Ð´×´Ì¬¼Ä´æÆ÷
#define TX_DS				0x20			//·¢ËÍ³É¹¦
#define FLUSH_TX			0xE1			//¶¨ÒåÇåÏ´·¢ËÍ»º³åÇøFIFO¼Ä´æÆ÷Ö¸Áî                                  
#define ON           1
#define OFF          0

void RF24_SetRfCh(u8 ch);							//nRF24L01P+¹¤×÷ÆµµÀÉèÖÃ
void RF24_Init();									//nRF24L01P+³õÊ¼»¯
void RF24_TX_Mode(u8 *toAddr);						//nRF24L01P+ÉèÖÃÎª·¢ËÍÄ£Ê½
bit RF24_TxData(u8 *txbuf);	//nRF24L01P+·¢ËÍÊý¾Ý

//----------------------nrf

#endif