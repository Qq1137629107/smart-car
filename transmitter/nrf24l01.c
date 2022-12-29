#include "commom.h"


U8 SPI_RW(U8 byte){
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

void nRF24L01P_Write_Reg(U8 reg, U8 value){
	CSN = 0;
	SPI_RW(reg);
	SPI_RW(value);
	CSN = 1;
}

void nRF24L01P_Write_Buf(U8 reg, const U8 *pBuf, U8 bytes){
	U8 i;

	CSN = 0;                                  			
	SPI_RW(reg);                          
	for(i=0; i<bytes; i++)     
		SPI_RW(*pBuf++);
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


void RF24_SetRfCh(U8 ch){
	CE = 0;
	nRF24L01P_Write_Reg(WR_RF_CH, ch);         									//���ñ����Ƶͨ��
	CE = 1;
}

void RF24_Init(){
	SCK = 0; 																	//SPIʱ��������
	CSN = 1;																	//Ƭѡ�����ߴ���δѡ״̬
	CE 	= 0;																	//����ʹ�����ã��շ�ʱҪ����
	IRQ = 1;																	//�ж�����̧�ߴ���δ�����ж�״̬

	CE = 0;
	nRF24L01P_Write_Reg(WR_SETUP_AW, 0x03);             		  				//���õ�ַ���Ϊ5�ֽ�
	nRF24L01P_Write_Reg(WR_RF_SETUP, RFSETUP);    								//���ݴ����ʡ����书������Ϊ��������RfSetup��ֵ
	nRF24L01P_Write_Reg(WR_EN_AA, 0x01);               							//ʹ�ܽ���ͨ��0�Զ�Ӧ��
	nRF24L01P_Write_Reg(WR_EN_RXADDR, 0x01);   									//ʹ�ܽ���ͨ��0
	nRF24L01P_Write_Reg(WR_RX_PW_P0, TX_PLOAD_WIDTH);  							//����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ�ȣ���������Ч
	nRF24L01P_Write_Reg(WR_SETUP_RETR, RETE_VAL);								//�Զ��ط�ʱ�������ط���������������Ч
	CE = 1;
}

void RF24_TX_Mode(U8 *toAddr)
{
	CE = 0;
	nRF24L01P_Write_Buf(WR_TX_ADDR, toAddr, TX_ADR_WIDTH);						//д�뷢�͵�ַ
	nRF24L01P_Write_Reg(WR_CONFIG, 0x0E);      									//CRCʹ�ܣ�16λCRCУ�飬����������ģʽ�������Զ��ط��ж�
	nRF24L01P_Write_Buf(WR_RX_ADDR_P0, toAddr, TX_ADR_WIDTH);					//Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
	nRF24L01P_Write_Reg(WR_STATUS, 0xFF);  										//������е��жϱ�־λ
	//CE = 1;
}

bit RF24_TxData(U8 *txbuf)
{
	U8 state;
	
	while(RPD == 1);
	CE=0;																		//CE���ͣ�ʹ��24L01����
	nRF24L01P_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);						//д���ݵ�TX FIFO,32���ֽ�
	CE=1;																		//CE�øߣ�ʹ�ܷ���	   

	while(IRQ == 1);															//�ȴ��������
	state=nRF24L01P_Read_Reg(STATUS);  											//��ȡ״̬�Ĵ�����ֵ	   
	nRF24L01P_Write_Reg(WR_STATUS, state); 										//���TX_DS��MAX_RT�жϱ�־
	if(state&TX_DS)																//�������
		return ON;
	nRF24L01P_Write_Reg(FLUSH_TX,0xff);											//���TX FIFO�Ĵ��� 
	return OFF;																	//����ʧ��
}



















