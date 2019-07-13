
#ifndef __LCD240128_H__
#define __LCD240128_H__

#include<reg52.h>
//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//-------------------------------------------------------------------------------
//PIN1: FG   [�����]-------------------VSS
//PIN2: VSS  [��Դ��]-------------------VSS
//PIN3: VDD  [��Դ����]-----------------VDD(+5V)
//PIN4: Vo   [LCD ƫѹ����]-------------��10K�Ŀɵ�����2K���赽VSS��VEE
//                                      Vo=VEEʱΪ��ʾ����
//PIN5: WR   [д�ź� ����Ч]------------P1.3
//PIN6: RD   [���ź� ����Ч]------------P1.2
//PIN7: CE   [ʹ���ź� ����Ч]----------P1.1
//PIN8: CD   [����/����ѡ��ˣ�H/L��]---P1.0
//PIN9: NC   [�ս�]---------------------������
//PIN10:RST  [��λ�� ����Ч]------------VDD
//PIN11:D0   [Data I/O]-----------------P0.0
//PIN12:D1   [Data I/O]-----------------P0.1
//PIN13:D2   [Data I/O]-----------------P0.2
//PIN14:D3   [Data I/O]-----------------P0.3
//PIN15:D4   [Data I/O]-----------------P0.4
//PIN16:D5   [Data I/O]-----------------P0.5
//PIN17:D6   [Data I/O]-----------------P0.6
//PIN18:D7   [Data I/O]-----------------P0.7
//PIN19:FS   [�������]-----------------VSS
//PIN20:VEE  [LCD��ѹ���]--------------�ṩҺ������ѹ.
//PIN21:BLA  [����Դ����]---------------��ʹ��˵����.
//PIN22:BLK  [����Դ����]---------------VSS
//ע:89C52�ľ���Ƶ��Ϊ11.0592MHz.

//-------------------------------------------------------------------------------
//����Ϊ��Ʒ�ӿ���������ʾ�����е�Ԥ����
//�û��ڱ�дӦ�ó���ʱ,�谴�Լ���ʵ��Ӳ�����������¶���
sbit CDPIN=P1^0;                        // C/D��Ӧ��Ƭ������
sbit CEPIN=P1^1;                        // CE��Ӧ��Ƭ������
sbit WRPIN=P1^3;                        // WR��Ӧ��Ƭ������
sbit RDPIN=P1^2;                        // RD��Ӧ��Ƭ������

//-------------------------------------------------------------------------------
//ȫ�ֱ���
extern unsigned char XPOS;			//�з���LCD����λ��ָ��
extern unsigned char YPOS;			//�з���LCD����λ��ָ��
extern bit CharImageReverse;		//�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)


//-------------------------------------------------------------------------------
//����Ϊ�������Ӣ���ֿ�
//ʵ��ʹ��ʱ�������Sunman�������Ӣ���ַ������������.exe�Զ����ɵ�charlib.c��
//�ļ����滻�ò���
//�������Ӣ���ַ��ⳣ������
//#define ENGLISHCHARNUMBER  10       //�����Ӣ���ַ����е�Ӣ���ַ��ĸ���
//#define CHINESECHARNUMBER  10      	//����������ַ����е������ַ��ĸ���
#define ENGLISHCHARSIZE    8       	//Ӣ���ַ�X������ʾ��ĸ���
#define CHINESECHARSIZE    16      	//�����ַ�X������Ӣ���ַ�Y������ʾ��ĸ���
#define ENGLISHCHARDOTSIZE 16      	//����Ӣ���ַ�������ֽ���
#define CHINESECHARDOTSIZE 32      	//���������ַ�������ֽ���
#define XDOTS   240               	//ͼ�οռ�X�����С
#define YDOTS   128     			//ͼ�οռ�X�����С
#define lcd_DATA P0					//���ݶ˿�

//-------------------------------------------------------------------------------
//ȫ�ֱ�������
extern unsigned int code EnglishCode1[];
extern unsigned int code ChineseCode1[];
extern unsigned int code ChineseCode2[];
extern unsigned char code EnglishCharDot1[];
extern unsigned char code ChineseCharDot1[];
extern unsigned char code ChineseCharDot2[];
extern unsigned char code Img_temp1_32[];
extern unsigned char code Img_temp2_32[];
extern unsigned char code Img_check_ok_32[];
extern unsigned char code Img_check_no_ok_32[];

//-------------------------------------------------------------------------------
//����Ϊ��ʾ����ĺ�������
extern void beautifulshow(void);								//ͼ�λ���չʾ����
extern void putchar(unsigned int *C_E_Code_Name,unsigned char *C_E_CharDot_Name,unsigned int c,unsigned int CharNumber);		
																//��λд�ַ��ӳ���
extern void putstr(unsigned int *C_E_Code_Name,unsigned char *C_E_CharDot_Name,unsigned char code *s,unsigned int CharNumber);	
																//��ʾ�ַ����ӳ���,�ַ���Ϊ0ʱ�˳�
extern unsigned char code *getchinesecodepos(unsigned int *ChineseCode_Name,unsigned char *ChineseCharDot_Name,unsigned int ac,unsigned int CharNumber);
extern unsigned char code *getenglishcodepos(unsigned int *EnglishCode_Name,unsigned char *EnglishCharDot_Name,unsigned char ac,unsigned int CharNumber);
extern void putimage(unsigned char code *s);   					//��ʾͼ���ӳ���
extern void putsizeimage(unsigned char XSIZE,unsigned char YSIZE,unsigned char code *s);
																//��ʾָ����С��ͼ���ӳ���
extern void point(bit b);										//��b��������(XPOS,YPOS)λ�û��Ƶ�
extern void line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b);
extern void rect(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b);
extern void triangle(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,bit b);
extern void lcdfill(unsigned char d);          					//������ʾd������ֽ������ӳ���
extern void lcdpos(void);                      					//���������(XPOS,YPOS)�ڲ�RAM��ַ���ӳ���
extern void lcdreset(void);                    					//Һ����ʾ��������ʼ���ӳ���
extern void lcdwd(unsigned char d);            					//��ͼ�������ӳ���
extern unsigned char lcdrd(void);              					//��ͼ�������ӳ���
extern void lcdwc(unsigned char c);            					//��ָ���ӳ���
extern void lcdwc2(unsigned char c,unsigned char d);			//��2�ֽ�ָ���ӳ���
extern void lcdwc3(unsigned char c,unsigned char d1,unsigned char d2);
																//��3�ֽ�ָ���ӳ���
extern unsigned char lcdrdata(void);           					//�������ӳ���
extern void lcdwdata(unsigned char d);         					//�������ӳ���
extern void lcdwaitidle(void);                 					//æ����ӳ���
extern void CharLocateXY(uchar x,uchar y);						//ֱ����ʾʱ�趨��ʾ��ַ����
extern void DirectDisplayChar(uchar x,uchar y,uchar CharByte);	//ֱ����ʾһ��ASCII�뺯��
extern void DirectDisplayString(uchar x,uchar y,uchar *str);	//ֱ����ʾһ���ַ���

#endif