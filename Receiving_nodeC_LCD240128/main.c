
//240128������ֱ����ʾ16��*30��=480���ַ�
//240128��������ʾ8��*15��=120��16*16��ģ�ĺ���
//lcdwc(0x90);//�ر��ı���ʾ���ر�ͼ����ʾ
//lcdwc(0x94);//�����ı���ʾ���ر�ͼ����ʾ
//lcdwc(0x98);//�ر��ı���ʾ������ͼ����ʾ
//lcdwc(0x9c);//�����ı���ʾ������ͼ����ʾ

#include <reg52.h>
#include <intrins.h>
#include "LCD240128.h"
#include "NRF24L01.h"
#include "Serial_Com.h"

//1s��ʱ����
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//������
void main(void)
{   
	lcdreset();					//��ʼ��Һ����ʾ������
	lcdfill(0x00);				//����
	UART_Init();				//��ʼ������ͨ��
	init_NRF24L01();			//��ʼ��nRF24L01����ģ��
	RX_Mode();					//��ʼ��nRF24L01������ģʽ
	
	//���ڼ��nRF24L01ģ���Ƿ���ڻ�����������
	if(!NRF24L01_Check())
	{
		DirectDisplayString(0,5,"  nRF24L01+ Module Check OK!  ");
		//ͼƬ��ʾ: ��(104,50)λ����ʾ32*32����ͼ��
		XPOS=104;
		YPOS=50;
		putimage(Img_check_ok_32);	//д���ݵ���ǰLCDRAM��ַ��
		Delay1000ms();
		lcdfill(0x00);				//����
		beautifulshow();			//ͼ�λ���չʾ����
		DirectDisplayString(0,5, ">>> A-Temperature: NO DATA <<<");
		DirectDisplayString(0,7, ">>> B-Temperature: NO DATA <<<");
		DirectDisplayString(0,9, ">>> C-Temperature: NO DATA <<<");
		DirectDisplayString(0,11,">>> D-Temperature: NO DATA <<<");
	}
	else
	{
		DirectDisplayString(0,5,"nRF24L01+ Module Check Failed!");
		//ͼƬ��ʾ: ��(104,50)λ����ʾ32*32����ͼ��
		XPOS=104;
		YPOS=50;
		putimage(Img_check_no_ok_32);	//д���ݵ���ǰLCDRAM��ַ��
		while(1);
	}
	
	while(1)
	{
		//���ݲ�ͬ������ͨ����ʾ���Ե�����
		if(!Rx_Pipe_Num_Choose())
		{
			//��ʽPutString(x������,y������,����);
			DirectDisplayString(18,5, RxBuf_P0);//��ʾ����ͨ��0������
			DirectDisplayString(18,7, RxBuf_P1);//��ʾ����ͨ��1������
			DirectDisplayString(18,9, RxBuf_P2);//��ʾ����ͨ��2������
			DirectDisplayString(18,11,RxBuf_P3);//��ʾ����ͨ��3������
			
			//����ͨ�ŷ�������
			UART_SendStr(RxBuf_P0);//����ͨ��0������ͨ�����ڷ��͸���λ��
			UART_SendStr(RxBuf_P1);//����ͨ��1������ͨ�����ڷ��͸���λ��
			UART_SendStr(RxBuf_P2);//����ͨ��2������ͨ�����ڷ��͸���λ��
			UART_SendStr(RxBuf_P3);//����ͨ��3������ͨ�����ڷ��͸���λ��
		}
	}
}