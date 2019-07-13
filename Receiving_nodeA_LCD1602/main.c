
#include <reg52.h>
#include "NRF24L01.h"
#include "LCD1602.h"

//************************************������*******************************
void main(void)
{
//	uchar Display_Buff[7];           //��ʾ������մ���
//	long uint Recive_Count = 0;      //��¼���ճɹ�����������
	init_NRF24L01() ;
//	RX_Mode();
	LCD1602_Initial();		//LCD1602��ʼ��
	Delay10ms();					//������ʱ
	
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
	
	//��ʼ������
	LCD1602_GotoXY(0,0);
	LCD1602_Display_NoXY("                ");
	LCD1602_GotoXY(1,0);
	LCD1602_Display_NoXY("                ");
	
	RX_Mode();
	
	while(1)
	{
		
		if(!Rx_Pipe_Num_Choose())
		{
			LCD1602_GotoXY(0,0);
	 		LCD1602_Display_NoXY(RxBuf_P0);//��ʾ����ͨ��0������
			LCD1602_GotoXY(0,8);
	 		LCD1602_Display_NoXY(RxBuf_P1);//��ʾ����ͨ��1������
			LCD1602_GotoXY(1,0);
	 		LCD1602_Display_NoXY(RxBuf_P2);//��ʾ����ͨ��2������
			LCD1602_GotoXY(1,8);
	 		LCD1602_Display_NoXY(RxBuf_P3);//��ʾ����ͨ��3������
		}
	}		
}