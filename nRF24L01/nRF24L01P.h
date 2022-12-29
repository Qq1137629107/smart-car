#ifndef __NRF24L01P__
#define __NRF24L01P__

#include "STC15.H"
#include "Sys.h"
#include "Type.h"
#include "Timer.h"


/***************************************MCU到NRF24L01+的引脚定义（用户操作）******************************************/

#define	MOSI				P13				//主机输出，从机输入引脚（输出）
#define	MISO				P14				//主机输入，从机输出引脚（输入）
#define	SCK					P15				//主机输出，串行时钟引脚（输出）
#define	CSN					P16				//主机输出，从机选择引脚（输出到CSN，低电平有效）
#define	CE					P17				//芯片使能信号引脚（输出，I/O口配置为推挽）
#define	IRQ					P12				//来自NRF24L01的中断信号引脚（输入，低电平有效）

#define	AUTO_RESEND_TIME	500				//自动重发时间间隔，单位uS，必须是250的整数倍，最大4000uS，不启用ACK请忽略此项
#define	AUTO_RESEND_NUM		15				//自动重发次数，最多15次，不启用ACK请忽略此项

#define	RFSETUP		        (RATE_1Mbps | E01ML01SP4_20dBm)	   //RF速率和发射功率


/********************************************NRF24L01+数据常用数据值配置**********************************************/

#define TX_ADR_WIDTH		5				//发送/接收地址宽度
#define TX_PLOAD_WIDTH		32				//数据通道有效数据宽度

/*************************************************** 全局变量声明 ***************************************************/

extern U8 SelfAddr[TX_ADR_WIDTH];			//本机硬件地址


/***************************************************NRF24L01+命令*****************************************************/

#define READ_REG			0x00  			//定义读取寄存器命令
#define WRITE_REG			0x20  			//定义写取寄存器命令
#define RD_RX_PLOAD			0x61  			//定义读有效接收数据寄存器指令
#define WR_TX_PLOAD			0xA0  			//定义写有效发送数据寄存器指令
#define WR_TX_PLOAD_NOACK	0xB0  			//定义写有效发送数据寄存器指令，无ACK应答模式
#define FLUSH_TX			0xE1			//定义清洗发送缓冲区FIFO寄存器指令                                  
#define FLUSH_RX			0xE2			//定义清洗接收缓冲区FIFO寄存器指令
#define REUSE_TX_PL			0xE3			//定义重复装载发送数据寄存器指令
#define NOP					0xFF			//定义无操作，可能会被用来读状态寄存器

#define RETE_VAL			((AUTO_RESEND_TIME/250-1)<<4) + AUTO_RESEND_NUM 	//自动重发配置值


/************************************************NRF24L01+寄存器地址**************************************************/

#define CONFIG				0x00			//配置寄存器
#define EN_AA				0x01			//设置自动应答功能寄存器
#define EN_RXADDR			0x02			//设置使能接收地址寄存器
#define SETUP_AW			0x03			//设置地址宽度寄存器
#define SETUP_RETR			0x04			//设置自动重发寄存器
#define RF_CH				0x05			//设置无线频道寄存器
#define RF_SETUP			0x06			//设置无线发射速率、功耗寄存器
#define STATUS				0x07			//状态寄存器
#define OBSERVE_TX			0x08			//发送检测寄存器
#define RPD					0x09			//接收功率检测寄存器
#define RX_ADDR_P0			0x0A			//通道0接收数据地址寄存器
#define RX_ADDR_P1			0x0B			//通道1接收数据地址寄存器
#define RX_ADDR_P2			0x0C			//通道2接收数据地址寄存器
#define RX_ADDR_P3			0x0D			//通道3接收数据地址寄存器
#define RX_ADDR_P4			0x0E			//通道4接收数据地址寄存器
#define RX_ADDR_P5			0x0F			//通道5接收数据地址寄存器
#define TX_ADDR				0x10			//发送目标地址寄存器
#define RX_PW_P0			0x11			//通道0接收有效数据宽度寄存器
#define RX_PW_P1			0x12			//通道1接收有效数据宽度寄存器
#define RX_PW_P2			0x13			//通道2接收有效数据宽度寄存器
#define RX_PW_P3			0x14			//通道3接收有效数据宽度寄存器
#define RX_PW_P4			0x15			//通道4接收有效数据宽度寄存器
#define RX_PW_P5			0x16			//通道5接收有效数据宽度寄存器
#define FIFO_STATUS			0x17			//FIFO状态寄存器
#define FEATURE				0x1D			//特征寄存器，ACK负载长度、使能ACK负载、禁用ACK

#define WR_CONFIG			0x20			//写配置寄存器
#define WR_EN_AA			0x21			//写设置自动应答功能寄存器
#define WR_EN_RXADDR		0x22			//写设置使能接收地址寄存器
#define WR_SETUP_AW			0x23			//写设置地址宽度寄存器
#define WR_SETUP_RETR		0x24			//写设置自动重发寄存器
#define WR_RF_CH			0x25			//写设置无线频道寄存器
#define WR_RF_SETUP			0x26			//写设置无线发射速率、功耗寄存器
#define WR_STATUS			0x27			//写状态寄存器
#define WR_OBSERVE_TX		0x28			//写发送检测寄存器
#define WR_RPD				0x29			//写接收功率检测寄存器
#define WR_RX_ADDR_P0		0x2A			//写通道0接收数据地址寄存器
#define WR_RX_ADDR_P1		0x2B			//写通道1接收数据地址寄存器
#define WR_RX_ADDR_P2		0x2C			//写通道2接收数据地址寄存器
#define WR_RX_ADDR_P3		0x2D			//写通道3接收数据地址寄存器
#define WR_RX_ADDR_P4		0x2E			//写通道4接收数据地址寄存器
#define WR_RX_ADDR_P5		0x2F			//写通道5接收数据地址寄存器
#define WR_TX_ADDR			0x30			//写发送目标地址寄存器
#define WR_RX_PW_P0			0x31			//写通道0接收有效数据宽度寄存器
#define WR_RX_PW_P1			0x32			//写通道1接收有效数据宽度寄存器
#define WR_RX_PW_P2			0x33			//写通道2接收有效数据宽度寄存器
#define WR_RX_PW_P3			0x34			//写通道3接收有效数据宽度寄存器
#define WR_RX_PW_P4			0x35			//写通道4接收有效数据宽度寄存器
#define WR_RX_PW_P5			0x36			//写通道5接收有效数据宽度寄存器
#define WR_FIFO_STATUS		0x37			//写FIFO状态寄存器
#define WR_FEATURE			0x3D			//写特征寄存器，ACK负载长度、使能ACK负载、禁用ACK


/*********************************************NRF24L01+状态寄存器状态值***********************************************/
 
#define RX_DR				0x40			//接收成功
#define TX_DS				0x20			//发送成功
#define MAX_RT				0x10			//达到最大重发次数


/*********************************************发射功率与频率配置值***********************************************/

#define RATE_2Mbps			0x08			//2M速率
#define RATE_1Mbps			0x00			//1M速率
#define RATE_250Kbps		0x20			//250K速率

#define SI24R1_7dBm			0x07			//台产SI24R1芯片7dBm
#define SI24R1_4dBm			0x06			//台产SI24R1芯片4dBm
#define SI24R1_3dBm			0x05			//台产SI24R1芯片3dBm
#define SI24R1_1dBm			0x04			//台产SI24R1芯片1dBm
#define SI24R1_0dBm			0x03			//台产SI24R1芯片0dBm
#define SI24R1_f4dBm		0x02			//台产SI24R1芯片-4dBm
#define SI24R1_f6dBm		0x01			//台产SI24R1芯片-6dBm
#define SI24R1_f12dBm		0x00			//台产SI24R1芯片-12dBm

#define E01ML01SP4_20dBm	0x06			//成都亿佰特模块20dBm
#define E01ML01SP4_14dBm	0x04			//成都亿佰特模块14dBm
#define E01ML01SP4_8dBm		0x02			//成都亿佰特模块8dBm
#define E01ML01SP4_2dBm		0x00			//成都亿佰特模块2dBm


/*************************************************** 函数声明 ***************************************************/
void RF24_SetRfCh(U8 ch);							//nRF24L01P+工作频道设置
void RF24_Init();									//nRF24L01P+初始化
void RF24_RX_Mode();								//nRF24L01P+设置为接收模式
void RF24_TX_Mode(U8 *toAddr);						//nRF24L01P+设置为发送模式
bit RF24_RxData(U8 *rxbuf);							//nRF24L01P+判断是否收到数据，若收到直接取出，应在主循环中调用
bit RF24_TxData(U8 *txbuf);							//nRF24L01P+发送数据

#endif

