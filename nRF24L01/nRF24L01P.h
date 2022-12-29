#ifndef __NRF24L01P__
#define __NRF24L01P__

#include "STC15.H"
#include "Sys.h"
#include "Type.h"
#include "Timer.h"


/***************************************MCU��NRF24L01+�����Ŷ��壨�û�������******************************************/

#define	MOSI				P13				//����������ӻ��������ţ������
#define	MISO				P14				//�������룬�ӻ�������ţ����룩
#define	SCK					P15				//�������������ʱ�����ţ������
#define	CSN					P16				//����������ӻ�ѡ�����ţ������CSN���͵�ƽ��Ч��
#define	CE					P17				//оƬʹ���ź����ţ������I/O������Ϊ���죩
#define	IRQ					P12				//����NRF24L01���ж��ź����ţ����룬�͵�ƽ��Ч��

#define	AUTO_RESEND_TIME	500				//�Զ��ط�ʱ��������λuS��������250�������������4000uS��������ACK����Դ���
#define	AUTO_RESEND_NUM		15				//�Զ��ط����������15�Σ�������ACK����Դ���

#define	RFSETUP		        (RATE_1Mbps | E01ML01SP4_20dBm)	   //RF���ʺͷ��书��


/********************************************NRF24L01+���ݳ�������ֵ����**********************************************/

#define TX_ADR_WIDTH		5				//����/���յ�ַ���
#define TX_PLOAD_WIDTH		32				//����ͨ����Ч���ݿ��

/*************************************************** ȫ�ֱ������� ***************************************************/

extern U8 SelfAddr[TX_ADR_WIDTH];			//����Ӳ����ַ


/***************************************************NRF24L01+����*****************************************************/

#define READ_REG			0x00  			//�����ȡ�Ĵ�������
#define WRITE_REG			0x20  			//����дȡ�Ĵ�������
#define RD_RX_PLOAD			0x61  			//�������Ч�������ݼĴ���ָ��
#define WR_TX_PLOAD			0xA0  			//����д��Ч�������ݼĴ���ָ��
#define WR_TX_PLOAD_NOACK	0xB0  			//����д��Ч�������ݼĴ���ָ���ACKӦ��ģʽ
#define FLUSH_TX			0xE1			//������ϴ���ͻ�����FIFO�Ĵ���ָ��                                  
#define FLUSH_RX			0xE2			//������ϴ���ջ�����FIFO�Ĵ���ָ��
#define REUSE_TX_PL			0xE3			//�����ظ�װ�ط������ݼĴ���ָ��
#define NOP					0xFF			//�����޲��������ܻᱻ������״̬�Ĵ���

#define RETE_VAL			((AUTO_RESEND_TIME/250-1)<<4) + AUTO_RESEND_NUM 	//�Զ��ط�����ֵ


/************************************************NRF24L01+�Ĵ�����ַ**************************************************/

#define CONFIG				0x00			//���üĴ���
#define EN_AA				0x01			//�����Զ�Ӧ���ܼĴ���
#define EN_RXADDR			0x02			//����ʹ�ܽ��յ�ַ�Ĵ���
#define SETUP_AW			0x03			//���õ�ַ��ȼĴ���
#define SETUP_RETR			0x04			//�����Զ��ط��Ĵ���
#define RF_CH				0x05			//��������Ƶ���Ĵ���
#define RF_SETUP			0x06			//�������߷������ʡ����ļĴ���
#define STATUS				0x07			//״̬�Ĵ���
#define OBSERVE_TX			0x08			//���ͼ��Ĵ���
#define RPD					0x09			//���չ��ʼ��Ĵ���
#define RX_ADDR_P0			0x0A			//ͨ��0�������ݵ�ַ�Ĵ���
#define RX_ADDR_P1			0x0B			//ͨ��1�������ݵ�ַ�Ĵ���
#define RX_ADDR_P2			0x0C			//ͨ��2�������ݵ�ַ�Ĵ���
#define RX_ADDR_P3			0x0D			//ͨ��3�������ݵ�ַ�Ĵ���
#define RX_ADDR_P4			0x0E			//ͨ��4�������ݵ�ַ�Ĵ���
#define RX_ADDR_P5			0x0F			//ͨ��5�������ݵ�ַ�Ĵ���
#define TX_ADDR				0x10			//����Ŀ���ַ�Ĵ���
#define RX_PW_P0			0x11			//ͨ��0������Ч���ݿ�ȼĴ���
#define RX_PW_P1			0x12			//ͨ��1������Ч���ݿ�ȼĴ���
#define RX_PW_P2			0x13			//ͨ��2������Ч���ݿ�ȼĴ���
#define RX_PW_P3			0x14			//ͨ��3������Ч���ݿ�ȼĴ���
#define RX_PW_P4			0x15			//ͨ��4������Ч���ݿ�ȼĴ���
#define RX_PW_P5			0x16			//ͨ��5������Ч���ݿ�ȼĴ���
#define FIFO_STATUS			0x17			//FIFO״̬�Ĵ���
#define FEATURE				0x1D			//�����Ĵ�����ACK���س��ȡ�ʹ��ACK���ء�����ACK

#define WR_CONFIG			0x20			//д���üĴ���
#define WR_EN_AA			0x21			//д�����Զ�Ӧ���ܼĴ���
#define WR_EN_RXADDR		0x22			//д����ʹ�ܽ��յ�ַ�Ĵ���
#define WR_SETUP_AW			0x23			//д���õ�ַ��ȼĴ���
#define WR_SETUP_RETR		0x24			//д�����Զ��ط��Ĵ���
#define WR_RF_CH			0x25			//д��������Ƶ���Ĵ���
#define WR_RF_SETUP			0x26			//д�������߷������ʡ����ļĴ���
#define WR_STATUS			0x27			//д״̬�Ĵ���
#define WR_OBSERVE_TX		0x28			//д���ͼ��Ĵ���
#define WR_RPD				0x29			//д���չ��ʼ��Ĵ���
#define WR_RX_ADDR_P0		0x2A			//дͨ��0�������ݵ�ַ�Ĵ���
#define WR_RX_ADDR_P1		0x2B			//дͨ��1�������ݵ�ַ�Ĵ���
#define WR_RX_ADDR_P2		0x2C			//дͨ��2�������ݵ�ַ�Ĵ���
#define WR_RX_ADDR_P3		0x2D			//дͨ��3�������ݵ�ַ�Ĵ���
#define WR_RX_ADDR_P4		0x2E			//дͨ��4�������ݵ�ַ�Ĵ���
#define WR_RX_ADDR_P5		0x2F			//дͨ��5�������ݵ�ַ�Ĵ���
#define WR_TX_ADDR			0x30			//д����Ŀ���ַ�Ĵ���
#define WR_RX_PW_P0			0x31			//дͨ��0������Ч���ݿ�ȼĴ���
#define WR_RX_PW_P1			0x32			//дͨ��1������Ч���ݿ�ȼĴ���
#define WR_RX_PW_P2			0x33			//дͨ��2������Ч���ݿ�ȼĴ���
#define WR_RX_PW_P3			0x34			//дͨ��3������Ч���ݿ�ȼĴ���
#define WR_RX_PW_P4			0x35			//дͨ��4������Ч���ݿ�ȼĴ���
#define WR_RX_PW_P5			0x36			//дͨ��5������Ч���ݿ�ȼĴ���
#define WR_FIFO_STATUS		0x37			//дFIFO״̬�Ĵ���
#define WR_FEATURE			0x3D			//д�����Ĵ�����ACK���س��ȡ�ʹ��ACK���ء�����ACK


/*********************************************NRF24L01+״̬�Ĵ���״ֵ̬***********************************************/
 
#define RX_DR				0x40			//���ճɹ�
#define TX_DS				0x20			//���ͳɹ�
#define MAX_RT				0x10			//�ﵽ����ط�����


/*********************************************���书����Ƶ������ֵ***********************************************/

#define RATE_2Mbps			0x08			//2M����
#define RATE_1Mbps			0x00			//1M����
#define RATE_250Kbps		0x20			//250K����

#define SI24R1_7dBm			0x07			//̨��SI24R1оƬ7dBm
#define SI24R1_4dBm			0x06			//̨��SI24R1оƬ4dBm
#define SI24R1_3dBm			0x05			//̨��SI24R1оƬ3dBm
#define SI24R1_1dBm			0x04			//̨��SI24R1оƬ1dBm
#define SI24R1_0dBm			0x03			//̨��SI24R1оƬ0dBm
#define SI24R1_f4dBm		0x02			//̨��SI24R1оƬ-4dBm
#define SI24R1_f6dBm		0x01			//̨��SI24R1оƬ-6dBm
#define SI24R1_f12dBm		0x00			//̨��SI24R1оƬ-12dBm

#define E01ML01SP4_20dBm	0x06			//�ɶ��ڰ���ģ��20dBm
#define E01ML01SP4_14dBm	0x04			//�ɶ��ڰ���ģ��14dBm
#define E01ML01SP4_8dBm		0x02			//�ɶ��ڰ���ģ��8dBm
#define E01ML01SP4_2dBm		0x00			//�ɶ��ڰ���ģ��2dBm


/*************************************************** �������� ***************************************************/
void RF24_SetRfCh(U8 ch);							//nRF24L01P+����Ƶ������
void RF24_Init();									//nRF24L01P+��ʼ��
void RF24_RX_Mode();								//nRF24L01P+����Ϊ����ģʽ
void RF24_TX_Mode(U8 *toAddr);						//nRF24L01P+����Ϊ����ģʽ
bit RF24_RxData(U8 *rxbuf);							//nRF24L01P+�ж��Ƿ��յ����ݣ����յ�ֱ��ȡ����Ӧ����ѭ���е���
bit RF24_TxData(U8 *txbuf);							//nRF24L01P+��������

#endif

