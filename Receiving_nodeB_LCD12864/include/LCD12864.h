
#ifndef __LCD12864_H__
#define __LCD12864_H__

#include<reg52.h>
//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#define  LCD12864_DB P3		//���ݶ˿�

//���ƶ˿ڶ���**********************************************************
sbit LCDEN = P1^7;//ʹ���ź�
sbit RS = P1^5;//����/����ѡ���
sbit RW = P1^6;//��/дѡ���

//ȫ�ֱ�������**************************************************************
extern unsigned char datas[9]; //��һλ����������ţ��ڶ���������λ����¶�ֵ�������λ���С����'.'���¶ȵ�λ'C'

//��������************************************************************
extern void Lcd12864_Delay_ms(uint z);
extern void Busy_Check(void);
extern void Lcd12864_Write_Cmd(uchar com);
extern void Lcd12864_Write_Data(uchar dat);
extern void Lcd12864_Init(void);
extern void Lcd12864_WriteAddressSetting(uchar x , uchar y);
extern void Lcd12864_WriteSomething(uchar x , uchar y , uchar *str);
extern void LcdDisplayTemp(int temp);

#endif