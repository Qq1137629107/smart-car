#include "commom.h"


/*-----------------------------------------------------------------------------
SPI收发函数
------------------------------------------------------------------------------*/
U8 SPI_RW(U8 byte)
{
	U8 i;
	for(i=0; i<8; i++)
	{
		if(byte & 0x80)
			MOSI = 1;
		else
			MOSI = 0;
		byte = (byte << 1);
		SCK = 1;
		byte |= MISO;
		SCK = 0;
	}
	return byte;
}

void nRF24L01P_Write_Reg(U8 reg, U8 value)
{
	CSN = 0; 
	SPI_RW(reg);
	SPI_RW(value);
	CSN = 1;
}

U8 nRF24L01P_Read_Reg(U8 reg){
 	U8 value;

	CSN = 0;    
	SPI_RW(reg);			
	value = SPI_RW(0);
	CSN = 1;              

	return(value);
}

void nRF24L01P_Write_Buf(U8 reg, const U8 *pBuf, U8 bytes){
	U8 i;

	CSN = 0;                                  			
	SPI_RW(reg);                          
	for(i=0; i<bytes; i++)     
		SPI_RW(*pBuf++);
	CSN = 1;     
}	
void nRF24L01P_Read_Buf(U8 reg, U8 *pBuf, U8 bytes){
	U8 i;

	CSN = 0;                                        
	SPI_RW(reg);                           
	for(i=0; i<bytes; i++)
		pBuf[i] = SPI_RW(0);                   									//读取数据，低字节在前
	CSN = 1;   
}

void RF24_SetRfCh(U8 ch){
	CE = 0;
	nRF24L01P_Write_Reg(WR_RF_CH, ch);         									//设置变更射频通道
	CE = 1;
}

void RF24_Init(){
	SCK = 0; 																	//SPI时钟线拉低
	CSN = 1;																	//片选脚拉高处于未选状态
	CE 	= 0;																	//拉低使能配置，收发时要拉高
	IRQ = 1;																	//中断引脚抬高处于未触发中断状态

	CE = 0;
	nRF24L01P_Write_Reg(WR_SETUP_AW, 0x03);             		  				//设置地址宽度为5字节
	nRF24L01P_Write_Reg(WR_RF_SETUP, RFSETUP);    								//数据传输率、发射功率配置为公共变量RfSetup的值
	nRF24L01P_Write_Reg(WR_EN_AA, 0x01);               							//使能接收通道0自动应答
	nRF24L01P_Write_Reg(WR_EN_RXADDR, 0x01);   									//使能接收通道0
	nRF24L01P_Write_Reg(WR_RX_PW_P0, TX_PLOAD_WIDTH);  							//接收通道0选择和发送通道相同有效数据宽度，仅接收有效
	nRF24L01P_Write_Reg(WR_SETUP_RETR, RETE_VAL);								//自动重发时间间隔和重发次数，仅发送有效
	CE = 1;
}

void RF24_RX_Mode(U8 *SelfAddr)
{
	CE = 0;
	nRF24L01P_Write_Buf(WR_RX_ADDR_P0, SelfAddr, TX_ADR_WIDTH);  				//接收设备接收通道0使用和发送设备相同的发送地址
	nRF24L01P_Write_Reg(WR_CONFIG, 0x0F);              							//CRC使能，16位CRC校验，开机，接收模式
	nRF24L01P_Write_Reg(WR_STATUS, 0xFF);  										//清除所有的中断标志位
	CE = 1;                                            							//拉高CE启动接收设备
}	

bit RF24_RxData(U8 *rxbuf)
{
	U8 state;

	if(IRQ == 0)																//有中断触发，判断中断可以提高CPU效率，减少SPI通讯量
	{
		state = nRF24L01P_Read_Reg(STATUS);										//读取状态寄存器的值    	  
		nRF24L01P_Write_Reg(WR_STATUS, state);									//清除RX_DS中断标志
		if(state & RX_DR)														//接收到数据
		{
			nRF24L01P_Read_Buf(RD_RX_PLOAD,rxbuf,TX_PLOAD_WIDTH);				//读取数据
			nRF24L01P_Write_Reg(FLUSH_RX,0xFF);									//清除RX FIFO寄存器
			return ON; 
		}
	}	   
	return OFF;																	//没收到任何数据
}
