#include <reg52.h>
#include "NRF24L01.h"
#include "LCD12864.h"
#include "DS18B20.h"

//************************************������*******************************/
void main(void)
{
	init_NRF24L01();
	Lcd12864_Init();
	Lcd12864_Delay_ms(10);
	
	//���ڼ��nRF24L01ģ���Ƿ���ڻ�����������
	if(!NRF24L01_Check())
	{
		Lcd12864_WriteSomething(0 , 0 , "nRF24L01+ Module");
		Lcd12864_WriteSomething(1 , 0 , "Check OK!");
		Lcd12864_WriteSomething(2 , 0 , "System detection");
		Lcd12864_WriteSomething(3 , 0 , "is normal!");
		Lcd12864_Delay_ms(1500);
		Lcd12864_WriteSomething(0 , 0 , "A-TEMP:         ");
		Lcd12864_WriteSomething(1 , 0 , "B-TEMP:         ");
		Lcd12864_WriteSomething(2 , 0 , "C-TEMP:         ");
		Lcd12864_WriteSomething(3 , 0 , "D-TEMP:         ");
	}
	else
	{
		Lcd12864_WriteSomething(0 , 0 , "nRF24L01+ Module");
		Lcd12864_WriteSomething(1 , 0 , "Check Failed!");
		Lcd12864_WriteSomething(2 , 0 , "ֻ����ʾ�����¶�");
		Lcd12864_WriteSomething(3 , 0 , "L-temp:         ");
		while(1)
		{
			LcdDisplayTemp(Ds18b20ReadTemp());//�Ѵ������¶�ֵ��12864����ʾ�����������¶ȣ�
		}
	}
	
	RX_Mode();
	
	while(1)
	{
		if(!Rx_Pipe_Num_Choose())
		{
			Lcd12864_WriteSomething(0 , 4 , RxBuf_P0);//��ʾ����ͨ��0������
			Lcd12864_WriteSomething(1 , 4 , RxBuf_P1);//��ʾ����ͨ��1������
			Lcd12864_WriteSomething(2 , 4 , RxBuf_P2);//��ʾ����ͨ��2������
			Lcd12864_WriteSomething(3 , 4 , RxBuf_P3);//��ʾ����ͨ��3������
		}
	}
}