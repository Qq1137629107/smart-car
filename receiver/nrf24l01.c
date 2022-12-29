#include "commom.h"


/*-----------------------------------------------------------------------------
SPI�շ�����
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
		pBuf[i] = SPI_RW(0);                   									//��ȡ���ݣ����ֽ���ǰ
	CSN = 1;   
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

void RF24_RX_Mode(U8 *SelfAddr)
{
	CE = 0;
	nRF24L01P_Write_Buf(WR_RX_ADDR_P0, SelfAddr, TX_ADR_WIDTH);  				//�����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
	nRF24L01P_Write_Reg(WR_CONFIG, 0x0F);              							//CRCʹ�ܣ�16λCRCУ�飬����������ģʽ
	nRF24L01P_Write_Reg(WR_STATUS, 0xFF);  										//������е��жϱ�־λ
	CE = 1;                                            							//����CE���������豸
}	

bit RF24_RxData(U8 *rxbuf)
{
	U8 state;

	if(IRQ == 0)																//���жϴ������ж��жϿ������CPUЧ�ʣ�����SPIͨѶ��
	{
		state = nRF24L01P_Read_Reg(STATUS);										//��ȡ״̬�Ĵ�����ֵ    	  
		nRF24L01P_Write_Reg(WR_STATUS, state);									//���RX_DS�жϱ�־
		if(state & RX_DR)														//���յ�����
		{
			nRF24L01P_Read_Buf(RD_RX_PLOAD,rxbuf,TX_PLOAD_WIDTH);				//��ȡ����
			nRF24L01P_Write_Reg(FLUSH_RX,0xFF);									//���RX FIFO�Ĵ���
			return ON; 
		}
	}	   
	return OFF;																	//û�յ��κ�����
}
