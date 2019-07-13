
#include <intrins.h>
#include "NRF24L01.h"

//uchar const TX_ADDRESS_P0[TX_ADR_WIDTH]= {0x77,0x35,0xF0,0xD3,0xE7}; //����ͨ��0�����ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const RX_ADDRESS_P0[RX_ADR_WIDTH]= {0x77,0x35,0xF0,0xD3,0xE7}; //����ͨ��0���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const TX_ADDRESS_P1[TX_ADR_WIDTH]= {0xC2,0xC2,0xC2,0xC2,0xC2}; //����ͨ��1�����ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const RX_ADDRESS_P1[RX_ADR_WIDTH]= {0xC2,0xC2,0xC2,0xC2,0xC2}; //����ͨ��1���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const TX_ADDRESS_P2[TX_ADR_WIDTH]= {0xC3,0xC2,0xC2,0xC2,0xC2}; //����ͨ��2�����ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const RX_ADDRESS_P2[RX_ADR_WIDTH]= {0xC3,0xC2,0xC2,0xC2,0xC2}; //����ͨ��2���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
uchar const TX_ADDRESS_P3[TX_ADR_WIDTH]= {0xC4,0xC2,0xC2,0xC2,0xC2}; //����ͨ��3�����ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
uchar const RX_ADDRESS_P3[RX_ADR_WIDTH]= {0xC4,0xC2,0xC2,0xC2,0xC2}; //����ͨ��3���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const TX_ADDRESS_P4[TX_ADR_WIDTH]= {0xC5,0xC2,0xC2,0xC2,0xC2}; //����ͨ��4�����ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const RX_ADDRESS_P4[RX_ADR_WIDTH]= {0xC5,0xC2,0xC2,0xC2,0xC2}; //����ͨ��4���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const TX_ADDRESS_P5[TX_ADR_WIDTH]= {0xC6,0xC2,0xC2,0xC2,0xC2}; //����ͨ��5�����ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
//uchar const RX_ADDRESS_P5[RX_ADR_WIDTH]= {0xC6,0xC2,0xC2,0xC2,0xC2}; //����ͨ��5���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨

//********************���ͻ�����*******************************
uchar TxBuf[TX_PLOAD_WIDTH]={0};

//********************************************************************************
unsigned char bdata sta; //״̬��־
sbit RX_DR =sta^6;
sbit TX_DS =sta^5;
sbit MAX_RT =sta^4;


//*********************��ʱ�Ӻ���************************
void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}


void Delay100us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 43;
	while (--i);
}

//************************************************
unsigned char SPI_RW(unsigned char byte)
{
	uchar bit_ctr;
	for(bit_ctr=0;bit_ctr<8;bit_ctr++)   // ���8λ
	{
		MOSI = (byte & 0x80); 	// output 'byte', MSB to MOSI  ���byte�����λ����
		byte = (byte << 1); 	// shift next bit into MSB..
		SCK = 1; 				// Set SCK high..
		byte |= MISO; 			// capture current MISO bit ��ô�MISO��õ�һλ����
		SCK = 0; 				// ..then set SCK low again
	}
	return(byte);				// return read byte	��󷵻ش�MISO���������� 				
}

/********************************************************/
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value)
{
	uchar status;
	CSN = 0;              // CSN low, init SPI transaction
	status = SPI_RW(reg); //���ش�MISO����������,statusӦΪ�ϴ���üĴ�����д��value
	SPI_RW(value);        // and write value to it
	CSN = 1; 			  // CSN high again
	return(status);       // return nRF24L01 status byte
}

/*************************�����ӻ���ؼĴ���������*******************************/
unsigned char SPI_Read(unsigned char reg)
{
	uchar reg_val;
	CSN = 0; 		     // CSN low, initialize SPI communication...
	SPI_RW(reg);         // Select register to read from..
	reg_val = SPI_RW(0); // ..then read registervalue
	CSN = 1;             // CSN high, terminate SPI communication
	return(reg_val);     // return register value
}

/**********************��������**********************************/
//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//bytes:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
	uchar status,byte_ctr;
	CSN = 0; // ʹ��SPI����
	status = SPI_RW(reg); // ���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
	for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
		pBuf[byte_ctr] = SPI_RW(0); // ��������
	CSN = 1; // �ر�SPI����
	return(status); // ���ض�����״ֵ̬
}

/**********************д������**********************************/
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//bytes:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
unsigned char SPI_Write_Buf(uchar reg, uchar *pBuf, uchar bytes)
{
	uchar status,byte_ctr;
	CSN = 0; // Set CSN low, init SPI tranaction
	status = SPI_RW(reg); // Select register to write to and read status byte
	Delay10us();
	for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) // then write all byte in buffer(*pBuf)
	SPI_RW(*pBuf++);
	CSN = 1; // Set CSN high again
	return(status); // return nRF24L01 status byte
}

//���24L01�Ƿ����
//��ַ�Ĵ���TX_ADDR���ɶ�Ҳ��д�����Կ����õ�ַ�Ĵ���TX_ADDR��֤һ��SPIͨ���Ƿ������������д��ȥ�ĺͶ������������Ƿ�һ��
//����ֵ:0���ɹ�;1��ʧ��
uchar NRF24L01_Check(void)
{
	uchar check_in_buf[5]={0x11,0x22,0x33,0x44,0x55};
	uchar check_out_buf[5]={0x00,0x00,0x00,0x00,0x00};
	
	SPI_Write_Buf(WRITE_REG + TX_ADDR , check_in_buf , 5);  //д��check_in_buf�ĵ�ַ����
	SPI_Read_Buf(READ_REG + TX_ADDR , check_out_buf , 5);  //����д��ĵ�ַ��check_out_buf
	
	//�Ƚ�check_in_buf��check_out_buf�������Ƿ�һ��
	if((check_out_buf[0] == 0x11)&&\
	   (check_out_buf[1] == 0x22)&&\
	   (check_out_buf[2] == 0x33)&&\
       (check_out_buf[3] == 0x44)&&\
       (check_out_buf[4] == 0x55))
		return 0;//������ȫһ�£����⵽24L01
	
    else 
		return 1;//������24L01����
}

/********************����Txģʽ******************/
void TX_Mode(void)
{
	CE=0;
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS_P3, TX_ADR_WIDTH); //дTX�ڵ�ĵ�ַ������ͨ��3��
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS_P3, RX_ADR_WIDTH);//дRX�ڵ�ĵ�ַ�����յ�ַ��
	
	//�����д���ò�Ʋ�ҪnRF24L01Ҳ���ܹ��������͵ģ�Ϊʲô�أ�
//	SPI_RW_Reg(WRITE_REG + EN_AA, 0x3F); // ����ͨ��0ͨ��1ͨ��2�Զ�Ӧ������һ�գ�
//	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x3F); //��������ͨ��0ͨ��1ͨ��2��������һ�գ�
	
	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x1a); // �Զ��ط���ʱ500us + 86us,�Զ��ط�10�� 
	SPI_RW_Reg(WRITE_REG + RF_CH, 40); //���ù���ͨ��Ƶ��
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x0f); // ���÷�������2MHz�����书��Ϊ���ֵ0dB 
	SPI_RW_Reg(WRITE_REG + CONFIG,0x0e);//CRCʹ�ܣ�16λУ�飬�ϵ磬����ģʽ����������
	CE=1;
}

//**********************NRF24L01��ʼ��*********************************/
void init_NRF24L01(void)
{
	Delay100us();
	CSN=1; // Spi disable
	SCK=0; // Spiʱ���߳�ʼ��	  
}
/****************************���ڷ�����Ӧ���ź�******************************/
uchar CheckACK()
{  
	sta=SPI_Read(STATUS);               // ����״̬�Ĵ���
//	if(TX_DS||MAX_RT) 		//��������ж�
	if(IRQ==0)
	{
	   SPI_RW_Reg(WRITE_REG+STATUS,0xff);  // ���TX_DS��MAX_RT�жϱ�־
	   CSN=0;
	   SPI_RW(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס����  
       CSN=1; 
	   return(0);
	}
	else
	   return(1);
}