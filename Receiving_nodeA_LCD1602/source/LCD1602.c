
#include <intrins.h>
#include "LCD1602.h"

//��ʱ�����������STC89xxx
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

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

uchar LCD1602_Wait(void) //��1602�ڲ�״̬�� ���鿴�Ƿ�׼����
{
	uchar Sta;
	LcdRs=0;				   //LcdRS=L,LcdRw=H,LcdEn=H ���D0~D7״̬��
	LcdRw=1;		   Delay1ms();   
	LcdEn=1;	      
  Delay1ms();   
	Sta = LCD1602_Port;	 
  Delay1ms();   							 
	LcdEn=0;
	Sta = Sta & 0x80;
	return Sta;		
}

void LCD1602_Write(bit style, uchar input)
{
	while(LCD1602_Wait());	   			//��æµ����ȴ�,�����ʾ����
	LcdEn = 0;											
	LcdRs = style;					        //����������'1',��������'0'
	LcdRw = 0;		 
  Delay1ms();	
	LCD1602_Port = input;
 	Delay1ms();		 
	LcdEn = 1;		 
  Delay1ms();	
	LcdEn = 0;	
	Delay1ms();
}

void LCD1602_Initial()
{
	LcdEn=0;
	LCD1602_Write(0,0x38);    //8λ���ݶ˿�,2����ʾ,5*7���� 
	LCD1602_Write(0,0x0c);	  //������ʾ, �޹��
	LCD1602_Write(0,0x06);	  //AC����, ���治��       
	LCD1602_Write(0,0x01);    //����
	Delay10ms();
}

void LCD1602_GotoXY(uchar x, uchar y)	 //XΪ��ʾָ���λ�ã���Ϊ���еĵڼ���λ�ã�Yѡ��
{
	if(x==0)
		LCD1602_Write(0,0x80+y);
	if(x==1)
		LCD1602_Write(0,(0x80+0x40+y));
}

void LCD1602_Display_NoXY(uchar *str)	//��LCDд���ַ���
{
	while(*str!='\0')
	{
		LCD1602_Write(1,*str);
		str++;
	}
}