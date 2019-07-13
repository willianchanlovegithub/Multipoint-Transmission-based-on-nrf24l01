
#include <intrins.h>
#include "NRF24L01.h"

uchar const RX_ADDRESS_P0[TX_ADR_WIDTH]= {0x77,0x35,0xF0,0xD3,0xE7}; //����ͨ��0���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
uchar const RX_ADDRESS_P1[TX_ADR_WIDTH]= {0xC2,0xC2,0xC2,0xC2,0xC2}; //����ͨ��1���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨
uchar const RX_ADDRESS_P2[1]= {0xC3}; //����ͨ��2���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨������ֻ�ǵͰ�λ��ͨ��0��ַ��һ����ֻд�Ͱ�λ����
uchar const RX_ADDRESS_P3[1]= {0xC4}; //����ͨ��3���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨������ֻ�ǵͰ�λ��ͨ��0��ַ��һ����ֻд�Ͱ�λ����
uchar const RX_ADDRESS_P4[1]= {0xC5}; //����ͨ��4���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨������ֻ�ǵͰ�λ��ͨ��0��ַ��һ����ֻд�Ͱ�λ����
uchar const RX_ADDRESS_P5[1]= {0xC6}; //����ͨ��5���յ�ַ����д���ֽڣ���д�ֽ�������SETUP_AW�����õ�ַ��ȵļĴ������趨������ֻ�ǵͰ�λ��ͨ��0��ַ��һ����ֻд�Ͱ�λ����

//********************���ջ�����*******************************
uchar RxBuf_P0[RX_PLOAD_WIDTH]={0};//���ջ�����
uchar RxBuf_P1[RX_PLOAD_WIDTH]={0};//ͨ��1���ջ�����
uchar RxBuf_P2[RX_PLOAD_WIDTH]={0};//ͨ��2���ջ�����
uchar RxBuf_P3[RX_PLOAD_WIDTH]={0};//ͨ��3���ջ�����
uchar RxBuf_P4[RX_PLOAD_WIDTH]={0};//ͨ��4���ջ�����
uchar RxBuf_P5[RX_PLOAD_WIDTH]={0};//ͨ��5���ջ�����

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

//***********************************************************************
unsigned char SPI_RW(unsigned char byte)
{
	uchar bit_ctr;
	for(bit_ctr=0;bit_ctr<8;bit_ctr++)   // ���8λ
	{
		MOSI = (byte & 0x80); 	//���byte�����λ����
		byte = (byte << 1); 	// shift next bit into MSB..
		SCK = 1; 				// Set SCK high..
		byte |= MISO; 			//��ô�MISO��õ�һλ����
		SCK = 0; 				// ..then set SCK low again
	}
	return(byte);				//��󷵻ش�MISO���������� 				
}

//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value)
{
	uchar status;
	CSN = 0;              // ʹ��SPI����
	status = SPI_RW(reg); //���ͼĴ����� 
	SPI_RW(value);        //д��Ĵ�����ֵ
	CSN = 1; 			  // ��ֹSPI����	 
	return(status);       // ����״ֵ̬
}

//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
unsigned char SPI_Read(unsigned char reg)
{
	uchar reg_val;
	CSN = 0; 		     // ʹ��SPI����		
	SPI_RW(reg);         // ���ͼĴ�����
	reg_val = SPI_RW(0); // ��ȡ�Ĵ�������
	CSN = 1;             // ��ֹSPI����	
	return(reg_val);     // ����״ֵ̬
}

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

//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//bytes:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
unsigned char SPI_Write_Buf(uchar reg, uchar *pBuf, uchar bytes)
{
	uchar status,byte_ctr;
	CSN = 0; // ʹ��SPI����
	status = SPI_RW(reg); // ���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
	Delay10us();
	for(byte_ctr=0; byte_ctr<bytes; byte_ctr++) // д������	 
		SPI_RW(*pBuf++);
	CSN = 1; //�ر�SPI����
	return(status); // ���ض�����״ֵ̬
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

//�ж��Ƿ���յ�����
//���յ�����1��û���յ�����0
//uchar NRFRevDate(uchar *RevDate)
//{
//	uchar RevFlags=0;
//	sta=SPI_Read(STATUS);//�������ݺ��ȡ״̬�Ĵ���
//  if(RX_DR)				// �ж��Ƿ���յ�����
//	{
//		CE=0; 			//SPIʹ��
//		SPI_Read_Buf(RD_RX_PLOAD,RevDate,RX_PLOAD_WIDTH);// ��RXFIFO��ȡ����
//		RevFlags=1;	   //��ȡ������ɱ�־
//		CE=1;
//		SPI_RW_Reg(WRITE_REG+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
//	 	CSN=0;
//		SPI_RW(FLUSH_RX);
//		CSN=1;
//	}
//	return(RevFlags);
//}
/**********************NRF24L01��ʼ��*********************************/
void init_NRF24L01(void)
{	
	Delay100us();
	CSN=1; // SPIƬѡȡ��		
	SCK=0; // Spi clock line init high
}

//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������	
void RX_Mode(void)
{
	//NRF����Ϊ����ģʽ����������
	CE=0;
	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS_P0, RX_ADR_WIDTH);//дRX�ڵ��ַ������ͨ��0��
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P1, RX_ADDRESS_P1, RX_ADR_WIDTH);//дRX�ڵ��ַ������ͨ��1��
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P2, RX_ADDRESS_P2, 1);//дRX�ڵ��ַ������ͨ��2��
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P3, RX_ADDRESS_P3, 1);//дRX�ڵ��ַ������ͨ��3��
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P4, RX_ADDRESS_P4, 1);//дRX�ڵ��ַ������ͨ��4��
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P5, RX_ADDRESS_P5, 1);//дRX�ڵ��ַ������ͨ��5��
	
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x3F); // ����ͨ��0~5�Զ�Ӧ��
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x3F); //����ͨ��0~5��������
	
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);//ѡ��ͨ��0��Ч���ݿ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P1, RX_PLOAD_WIDTH);//ѡ��ͨ��1��Ч���ݿ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P2, RX_PLOAD_WIDTH);//ѡ��ͨ��2��Ч���ݿ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P3, RX_PLOAD_WIDTH);//ѡ��ͨ��3��Ч���ݿ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P4, RX_PLOAD_WIDTH);//ѡ��ͨ��4��Ч���ݿ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P5, RX_PLOAD_WIDTH);//ѡ��ͨ��5��Ч���ݿ��
	
	SPI_RW_Reg(WRITE_REG + RF_CH, 40); //���ù���ͨ��Ƶ�ʣ�Fo=(2400+RF-CH)MHz��2440MHz=2.440GHz
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x0f);//���÷�����������÷�������2MHz�����书��Ϊ���ֵ0dB��
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f); //CRCʹ�ܣ�16λУ�飬�ϵ磬����ģʽ ����������
	
	CE = 1; //CE�øߣ���������ģʽ
}

//��������ͨ����ѡ���Ӧ�Ľ��ջ�����RxBuf_P0~RxBuf_P5
uchar Rx_Pipe_Num_Choose(void)
{
    uchar state;
    state=SPI_Read(STATUS);  			//��ȡ״̬�Ĵ�����ֵ
    SPI_RW_Reg(WRITE_REG + STATUS,state); //���TX_DS��MAX_RT�жϱ�־
    if(state&0x40)								//���յ�����
    {
        CE = 0;  //����
        switch(state&0X0E) 
		{
			case 0x00:
				SPI_Read_Buf(RD_RX_PLOAD,RxBuf_P0,RX_PLOAD_WIDTH);
				break;			//��ȡͨ��0����
			case 0x02:
				SPI_Read_Buf(RD_RX_PLOAD,RxBuf_P1,RX_PLOAD_WIDTH);
				break;			//��ȡͨ��1����
			case 0x04:
				SPI_Read_Buf(RD_RX_PLOAD,RxBuf_P2,RX_PLOAD_WIDTH);
				break;			//��ȡͨ��2����
			case 0x06:
				SPI_Read_Buf(RD_RX_PLOAD,RxBuf_P3,RX_PLOAD_WIDTH);
				break;			//��ȡͨ��3����
			case 0x08:
				SPI_Read_Buf(RD_RX_PLOAD,RxBuf_P4,RX_PLOAD_WIDTH);
				break;			//��ȡͨ��4����
			case 0x0A:
				SPI_Read_Buf(RD_RX_PLOAD,RxBuf_P5,RX_PLOAD_WIDTH);
				break;			//��ȡͨ��5����
        }
        SPI_RW_Reg(FLUSH_RX,0xff);					//���RX FIFO�Ĵ���
        CE = 1;
        Delay100us();
        return 0;
    }
	else
		return 1;  //û�յ��κ�����
}