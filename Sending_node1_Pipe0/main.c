#include <reg52.h>
#include "NRF24L01.h"
#include "LCD1602.h"
#include "DS18B20.h"

//************************************������*******************************/
void main(void)
{
	uchar Display_Buff[7];
	long uint Send_Count = 0;//��¼���ʹ���������
	init_NRF24L01();
//	TX_Mode(); 
	LCD1602_Initial();		//LCD1602��ʼ��
	Delay10ms();
	
	//���ڼ��nRF24L01ģ���Ƿ���ڻ�����������
	if(!NRF24L01_Check())
	{
		LCD1602_GotoXY(0,0);
		LCD1602_Display_NoXY("nRF24L01+ Module");
		LCD1602_GotoXY(1,0);
		LCD1602_Display_NoXY("Check OK!");	
		Delay1000ms();
		Delay1000ms();
	}
	else
	{
		LCD1602_GotoXY(0,0);
		LCD1602_Display_NoXY("nRF24L01+ Module");
		LCD1602_GotoXY(1,0);
		LCD1602_Display_NoXY("Check Failed!");
		while(1);
	}
	
	LCD1602_GotoXY(0,0);
	LCD1602_Display_NoXY("Times:          ");
	LCD1602_GotoXY(1,0);
	LCD1602_Display_NoXY("Send:           ");
	
	TX_Mode();
	
	while(1)
	{
		//�����ͻ�����TxBuf��ֵ
		TxBuf[0]=datas[0];//��ʾ��+����-��
		TxBuf[1]=datas[1]+'0';//��λ
		TxBuf[2]=datas[2]+'0';//ʮλ
		TxBuf[3]=datas[3]+'0';//��λ
		TxBuf[4]=0x2E;//��ʾС���㡰.��
		TxBuf[5]=datas[4]+'0';//С�����һλ
		TxBuf[6]=datas[5]+'0';//С�������λ
		TxBuf[7]=0x43;//��ʾ��C��
		
		//SPI_Write_Buf(WR_TX_PLOAD, Display_Buff, TX_PLOAD_WIDTH); // �������Display_Buff(�������)�����Ǵ�������(TxBuf)
		SPI_Write_Buf(WR_TX_PLOAD, TxBuf, TX_PLOAD_WIDTH); // װ������
		SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e); //CRCʹ�ܣ�16λУ�飬�ϵ磬����ģʽ����������
		CE=1;
		Delay10us();	   //��ʱ10us���ȴ��������
		//CheckACK();	
		
		if(!CheckACK())//���ڷ�����Ӧ���źţ�����ɹ�����0
		{
			if(Send_Count<99999)
			{
				Send_Count++;	//���ͼ�������1	
				Delay1000ms();//ÿ��һ�뷢��һ������
			}
			else
				Send_Count=1;
		}
		
		//����LCD1602��ʾ����
		Display_Buff[0] = Send_Count / 10000 + '0';
		Display_Buff[1] = (Send_Count % 10000) / 1000 + '0';
		Display_Buff[2] = (Send_Count % 1000) / 100 + '0';
		Display_Buff[3] = (Send_Count % 100) / 10 + '0';
		Display_Buff[4] = Send_Count % 10 + '0';
		Display_Buff[5] = '\0';
		
		//��ʾ���͵Ĵ���
		LCD1602_GotoXY(0,6);
		LCD1602_Display_NoXY(Display_Buff); 
		//�Ѵ������¶�ֵ��1602����ʾ����
		LcdDisplayTemp(Ds18b20ReadTemp());
	}
}

