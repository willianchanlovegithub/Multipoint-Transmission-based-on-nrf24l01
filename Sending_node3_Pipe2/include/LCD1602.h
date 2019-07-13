
#ifndef __LCD1602_H__
#define __LCD1602_H__

#include<reg52.h>
//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#define  LCD1602_Port P0		//���ݶ˿�

//���ƶ˿ڶ���**********************************************************
sbit LcdRs		= P1^2;
sbit LcdRw    = P1^1;
sbit LcdEn  	= P1^0;

//ȫ�ֱ�������**************************************************************
extern unsigned char datas[6]; //��һλ����������ţ��ڶ�λ������λ����¶�ֵ

//����������************************************************************
extern void Delay1000ms();
extern void Delay10ms();
extern void Delay1ms();
extern void LCD1602_Write(bit style, uchar input);
extern void LCD1602_Initial();
extern void LCD1602_GotoXY(uchar x, uchar y);
extern void LCD1602_Display_NoXY(uchar *str);
extern void LcdDisplayTemp(int temp);

#endif