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

#define TX_ADR_WIDTH		5				//����/���յ�ַ���
#define TX_PLOAD_WIDTH		6				//����ͨ����Ч���ݿ��
#define WR_RF_CH			0x25			//д��������Ƶ���Ĵ���
#define WR_SETUP_AW			0x23			//д���õ�ַ��ȼĴ���
#define WR_RF_SETUP			0x26			//д�������߷������ʡ����ļĴ���
#define WR_EN_AA			0x21			//д�����Զ�Ӧ���ܼĴ���
#define WR_EN_RXADDR		0x22			//д����ʹ�ܽ��յ�ַ�Ĵ���
#define WR_RX_PW_P0			0x31			//дͨ��0������Ч���ݿ�ȼĴ���
#define	RFSETUP		        (RATE_1Mbps | E01ML01SP4_20dBm)	   //RF���ʺͷ��书��
#define WR_SETUP_RETR		0x24			//д�����Զ��ط��Ĵ���
#define WR_TX_ADDR			0x30			//д����Ŀ���ַ�Ĵ���
#define RATE_1Mbps			0x00			//1M����
#define RETE_VAL			((AUTO_RESEND_TIME/250-1)<<4) + AUTO_RESEND_NUM 	//�Զ��ط�����ֵ
#define E01ML01SP4_20dBm	0x06			//�ɶ��ڰ���ģ��20dBm
#define	AUTO_RESEND_TIME	500				//�Զ��ط�ʱ��������λuS��������250�������������4000uS��������ACK����Դ���
#define	AUTO_RESEND_NUM		15				//�Զ��ط����������15�Σ�������ACK����Դ���
#define WR_CONFIG			0x20			//д���üĴ���
#define WR_RX_ADDR_P0		0x2A			//дͨ��0�������ݵ�ַ�Ĵ���
#define WR_STATUS			0x27			//д״̬�Ĵ���
#define RPD					0x09			//���չ��ʼ��Ĵ���
#define WR_TX_PLOAD			0xA0  			//����д��Ч�������ݼĴ���ָ��
#define STATUS				0x07			//״̬�Ĵ���
#define WR_STATUS			0x27			//д״̬�Ĵ���
#define TX_DS				0x20			//���ͳɹ�
#define FLUSH_TX			0xE1			//������ϴ���ͻ�����FIFO�Ĵ���ָ��                                  
#define ON           1
#define OFF          0

void RF24_SetRfCh(U8 ch);							//nRF24L01P+����Ƶ������
void RF24_Init();									//nRF24L01P+��ʼ��
void RF24_TX_Mode(U8 *toAddr);						//nRF24L01P+����Ϊ����ģʽ
bit RF24_TxData(U8 *txbuf);	//nRF24L01P+��������

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



























