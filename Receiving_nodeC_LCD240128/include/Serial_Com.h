

#ifndef __SERIAL_COM_H__
#define __SERIAL_COM_H__

#include<reg52.h>
//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

extern void UART_Init(void);//���ڳ�ʼ������
extern void UART_SendByte(uchar uDat);//����һ���ֽں���
extern void UART_SendStr(uchar *pStr);//����һ���ַ����ĺ���
	
#endif