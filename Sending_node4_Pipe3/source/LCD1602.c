
#include <intrins.h>
#include "LCD1602.h"

unsigned char datas[6] = {0}; //��һλ����������ţ��ڶ�λ������λ����¶�ֵ

//��ʱ�����������STC89xxx
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

/*uchar LCD1602_Wait(void)		   //��1602�ڲ�״̬�� ���鿴�Ƿ�׼����
{
	uchar Sta;
	LcdRs=0;				   //LcdRS=L,LcdRw=H,LcdEn=H ���D0~D7״̬��
	LcdRw=1;		 
        Delay1ms();   
	LcdEn=1;	      
        Delay1ms();   
	Sta = LCD1602_Port;	 
        Delay1ms();   							 
	LcdEn=0;
	Sta = Sta & 0x80;
	return Sta;		
}*/

void LCD1602_Write(bit style, uchar input)
{
	//while(LCD1602_Wait());			//��æµ����ȴ�,�����ʾ����
	LcdEn = 0;											
	LcdRs = style;					        //����������'1',��������'0'
	//LcdRw = 0;		  
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
  LcdRw=0;
	LcdEn=0;
	LCD1602_Write(0,0x38);               //8λ���ݶ˿�,2����ʾ,5*7����
	LCD1602_Write(0,0x0c);  //������ʾ, �޹��
	LCD1602_Write(0,0x06);       //AC����, ���治��
	LCD1602_Write(0,0x01);   //����
	Delay10ms();
}

void LCD1602_GotoXY(uchar x, uchar y)	   //XΪ��ʾָ���λ�ã���Ϊ���еĵڼ���λ�ã�Yѡ��
{
	if(x==0)
		LCD1602_Write(0,0x80+y);
	if(x==1)
		LCD1602_Write(0,(0x80+0x40+y));
}

void LCD1602_Display_NoXY(uchar *str)					 //��LCDд���ַ���
{
	while(*str!='\0')
	{
		LCD1602_Write(1,*str);
		str++;
	}
}


//1602��ʾ�¶�ֵ
void LcdDisplayTemp(int temp) 	 //lcd��ʾ
{
	
    
  //unsigned char datas[5] = {0, 0, 0, 0, 0}; //�������飬����¶�ֵ
	float tp;  
	if(temp< 0)				//���¶�ֵΪ����
  	{
	  	LCD1602_GotoXY(1,5);
	    LCD1602_Write(1,'-');  		//��ʾ��
			datas[0]=0x2d;//�ѡ�-����ASCII������datas[]�����һλ
			
		//��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Լ�1����ȡ�����ԭ��
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
 
  	}
 	else
  	{			
	  	LCD1602_GotoXY(1,05);
	    LCD1602_Write(1,'+');  		//��ʾ��
		datas[0]=0x2b;//�ѡ�+����ASCII������datas[]�����һλ
			
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		//����¶���������ô����ô������ԭ����ǲ���������
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
	}
	datas[1] = temp / 10000;
	datas[2] = temp % 10000 / 1000;
	datas[3] = temp % 1000 / 100;
	datas[4] = temp % 100 / 10;
	datas[5] = temp % 10;
	
	LCD1602_GotoXY(1,6);
	LCD1602_Write(1,'0'+datas[1]); //��λ 	
	LCD1602_GotoXY(1,7);
	LCD1602_Write(1,'0'+datas[2]); //ʮλ
	LCD1602_GotoXY(1,8);
	LCD1602_Write(1,'0'+datas[3]); //��λ 
	LCD1602_GotoXY(1,9);
	LCD1602_Write(1,'.'); 		   //��ʾ ��.��
	LCD1602_GotoXY(1,10);
	LCD1602_Write(1,'0'+datas[4]); //��ʾС�����һλ
	LCD1602_GotoXY(1,11);
	LCD1602_Write(1,'0'+datas[5]); //��ʾС�������λ
	LCD1602_GotoXY(1,12);
	LCD1602_Write(1,0x43); //��ʾ��C��
}
