
#include "LCD12864.h"

unsigned char datas[9] = {0}; //��һλ����������ţ��ڶ���������λ����¶�ֵ�������λ���С����'.'���¶ȵ�λ'C'

//��ʱ�Ӻ���
void Lcd12864_Delay_ms(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

//æ��⣨����⣬û��æ���Ҳ��ʵ����ʾ���ܣ�
void Busy_Check(void)
{
	LCD12864_DB = 0xff;
	RS = 0;
	RW = 1;//WRΪ�ߵ�ƽ��ʱ��Ϊ��
	LCDEN = 1;
	while(LCD12864_DB & 0x80);//״̬����STA7��1����ֹ��0��ʹ�ܡ�����ֹʱ��æʱ�����ó�������whileѭ����
	Lcd12864_Delay_ms(1);
	LCDEN = 0;
}

//дָ���Ӻ��������������ֲ�ʱ��ͼ��д��
void Lcd12864_Write_Cmd(uchar com)
{
	Busy_Check();
	RS = 0;//дָ��RSΪ�͵�ƽ
	RW = 0;//WRΪ�͵�ƽ��ʱ��Ϊд
	LCDEN = 1;
	LCD12864_DB = com;
	Lcd12864_Delay_ms(1);
	LCDEN = 0;
	
}

//д�����Ӻ��������������ֲ�ʱ��ͼ��д��
void Lcd12864_Write_Data(uchar dat)
{
	Busy_Check();
	RS = 1;//д����RSΪ�ߵ�ƽ
	RW = 0;//WRΪ�͵�ƽ��ʱ��Ϊд
	LCDEN = 1;
	LCD12864_DB = dat;
	Lcd12864_Delay_ms(1);
	LCDEN = 0;
}

//��ʼ���Ӻ���
void Lcd12864_Init(void)
{
	Lcd12864_Write_Cmd(0x30);//��������
	Lcd12864_Delay_ms(5);
	//Lcd12864_Write_Cmd(0x0f);//������á�����ʾ���±���ʾ�������˸
	//Lcd12864_Write_Cmd(0x0e);//������á�����ʾ���±���ʾ����겻��˸
	Lcd12864_Write_Cmd(0x0c);//������á�����ʾ���±겻��ʾ����겻��˸
	Lcd12864_Delay_ms(5);
	Lcd12864_Write_Cmd(0x01);//����
}

//��ʾ��ַ����
void Lcd12864_WriteAddressSetting(uchar x , uchar y)
{
	uchar addr;
	if(x == 0) addr = 0x80 + y;//�ӵ�һ����ʾ
	else if(x == 1) addr = 0x90 + y;//�ӵڶ�����ʾ
	else if(x == 2) addr = 0x88 + y;//�ӵ�������ʾ
	else if(x == 3) addr = 0x98 + y;//�ӵ�������ʾ
	Lcd12864_Write_Cmd(addr);
}

//��ʾ�ַ�������װ
void Lcd12864_WriteSomething(uchar x , uchar y , uchar *str)
{
	Lcd12864_WriteAddressSetting(x , y);
	while(*str != '\0')
	{
		Lcd12864_Write_Data(*str++);
		Lcd12864_Delay_ms(1);//����ÿ����ÿ���ַ���ʾ������Ҳ���Բ�Ҫ��ʱ
	}
}

void LcdDisplayTemp(int temp)  //lcd��ʾ
{
	float tp;  
	if(temp < 0)  //���¶�ֵΪ����
  	{
	  	Lcd12864_WriteSomething(3 , 4 , '-');  //��ʾ��
		datas[0]=0x2d;  //�ѡ�-����ASCII������datas[]�����һλ
		
		//��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Լ�1����ȡ�����ԭ��
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//����?.5��������С������档
 
  	}
 	else
  	{			
	  	Lcd12864_WriteSomething(3 , 4 , '+');  //��ʾ��
		datas[0]=0x2b;  //�ѡ�+����ASCII������datas[]�����һλ
			
		tp=temp;  //��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		          //����¶���������ô����ô������ԭ����ǲ���������
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
	}
	datas[1] = (temp / 10000)+'0';
	datas[2] = (temp % 10000 / 1000)+'0';
	datas[3] = (temp % 1000 / 100)+'0';
	datas[4] = '.';
	datas[5] = (temp % 100 / 10)+'0';
	datas[6] = (temp % 10)+'0';
	datas[7] = 'C';
	
	Lcd12864_WriteSomething(3 , 4 , datas); //�ڵ����е��ĸ��ַ�λ�ÿ�ʼ��ʾ�¶ȣ�����+025.52C
}
