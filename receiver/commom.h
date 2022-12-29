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

#define TX_ADR_WIDTH		5				//����/���յ�ַ���
#define TX_PLOAD_WIDTH		6				//����ͨ����Ч���ݿ��
#define WR_SETUP_AW			0x23			//д���õ�ַ��ȼĴ���
#define WR_RF_SETUP			0x26			//д�������߷������ʡ����ļĴ���
#define WR_EN_AA			0x21			//д�����Զ�Ӧ���ܼĴ���
#define WR_EN_RXADDR		0x22			//д����ʹ�ܽ��յ�ַ�Ĵ���
#define WR_RX_ADDR_P0		0x2A			//дͨ��0�������ݵ�ַ�Ĵ���
#define WR_SETUP_RETR		0x24			//д�����Զ��ط��Ĵ���
#define	RFSETUP		        (RATE_1Mbps | E01ML01SP4_20dBm)	   //RF���ʺͷ��书��
#define RATE_1Mbps			0x00			//1M����
#define WR_RX_PW_P0			0x31			//дͨ��0������Ч���ݿ�ȼĴ���
#define E01ML01SP4_20dBm	0x06			//�ɶ��ڰ���ģ��20dBm
#define RETE_VAL			((AUTO_RESEND_TIME/250-1)<<4) + AUTO_RESEND_NUM 	//�Զ��ط�����ֵ
#define	AUTO_RESEND_TIME	500				//�Զ��ط�ʱ��������λuS��������250�������������4000uS��������ACK����Դ���
#define	AUTO_RESEND_NUM		15				//�Զ��ط����������15�Σ�������ACK����Դ���
#define WR_CONFIG			0x20			//д���üĴ���
#define WR_STATUS			0x27			//д״̬�Ĵ���
#define STATUS				0x07			//״̬�Ĵ���
#define RX_DR				0x40			//���ճɹ�
#define RD_RX_PLOAD			0x61  			//�������Ч�������ݼĴ���ָ��
#define FLUSH_RX			0xE2			//������ϴ���ջ�����FIFO�Ĵ���ָ��
#define WR_RF_CH			0x25			//д��������Ƶ���Ĵ���
#define OFF           0
#define ON            1

void RF24_SetRfCh(U8 ch);							//nRF24L01P+����Ƶ������
void RF24_Init();									//nRF24L01P+��ʼ��
void RF24_RX_Mode(U8 *SelfAddr);								//nRF24L01P+����Ϊ����ģʽ
bit RF24_RxData(U8 *rxbuf);							//nRF24L01P+�ж��Ƿ��յ����ݣ����յ�ֱ��ȡ����Ӧ����ѭ���е���

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


