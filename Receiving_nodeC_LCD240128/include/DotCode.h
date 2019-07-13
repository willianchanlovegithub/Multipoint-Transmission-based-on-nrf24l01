
//Ӣ����ĸ��ʮ������ASCII��(WELCOME TO MY SYSTEM)
//Ӣ���ַ����ظ���ֻ��дһ������
//Ӣ���ַ��������ظ�����һ������Ҫ����LCD240128.h�е�ENGLISHCHARNUMBER�ĺ궨��
unsigned int code EnglishCode1[]={
//ASCII���С��������
0x20, //�ַ�001:[ ]
0x43, //�ַ�002:[C]
0x45, //�ַ�003:[E]
0x4C, //�ַ�004:[L]
0x4D, //�ַ�005:[M]
0x4F, //�ַ�006:[O]
0x53, //�ַ�007:[S]
0x54, //�ַ�008:[T]
0x57, //�ַ�009:[W]
0x59, //�ַ�010:[Y]
};

//���ĵ�ʮ������ASCII�룬���ô������ַ������ģ��Է���HEXģʽ���ռ��ɵõ���
//�������ظ���ֻ��дһ������
//CharNumber���ַ��������ظ�����һ����
unsigned int code ChineseCode1[]={
//ASCII���С��������
0xB2C9,	//�ַ�001:[��]
0xB5E3,	//�ַ�002:[��]
0xB6C8,	//�ַ�003:[��]
0xB6E0,	//�ַ�004:[��]
0xBCAF,	//�ַ�005:[��]
0xCDB3,	//�ַ�006:[ͳ]
0xCEC2,	//�ַ�007:[��]
0xCEDE,	//�ַ�008:[��]
0xCFB5,	//�ַ�009:[ϵ]
0xCFDF,	//�ַ�010:[��]
};

//���ĵ�ʮ������ASCII�룬���ô������ַ������ģ��Է���HEXģʽ���ռ��ɵõ���
//�������ظ���ֻ��дһ������
//CharNumber���ַ��������ظ�����һ����
unsigned int code ChineseCode2[]={
//ASCII���С��������
0xA3BA,	//�ַ�001:[��]
0xB3C2,	//�ַ�001:[��]
0xCDA5,	//�ַ�001:[ͥ]
0xCEB0,	//�ַ�001:[ΰ]
0xCFA2,	//�ַ�001:[Ϣ]
0xD0C5,	//�ַ�001:[��]
0xD1A7,	//�ַ�001:[ѧ]
0xD4BA,	//�ַ�001:[Ժ]
0xD5DF,	//�ַ�001:[��]
0xD7F7,	//�ַ�001:[��]
};

//Ӣ���ַ����ظ���ֻ��дһ������
//��unsigned int code EnglishCode[]˳���Ӧ��ASCII���С��������
//��8*��16
unsigned char code EnglishCharDot1[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//U+0020( )
0x00,0x00,0x00,0x3E,0x42,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x44,0x38,0x00,0x00,//U+0043(C)
0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x42,0x42,0xFC,0x00,0x00,//U+0045(E)
0x00,0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0xFE,0x00,0x00,//U+004C(L)
0x00,0x00,0x00,0xEE,0x6C,0x6C,0x6C,0x6C,0x6C,0x54,0x54,0x54,0x54,0xD6,0x00,0x00,//U+004D(M)
0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,//U+004F(O)
0x00,0x00,0x00,0x3E,0x42,0x42,0x40,0x20,0x18,0x04,0x02,0x42,0x42,0x7C,0x00,0x00,//U+0053(S)
0x00,0x00,0x00,0xFE,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,//U+0054(T)
0x00,0x00,0x00,0xD6,0x54,0x54,0x54,0x54,0x54,0x6C,0x28,0x28,0x28,0x28,0x00,0x00,//U+0057(W)
0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,//U+0059(Y)
};

//�������ظ���ֻ��дһ������
//��unsigned int code ChineseCode1[]˳���Ӧ��ASCII���С��������
//��16*��16
unsigned char code ChineseCharDot1[]={
0x00,0x10,0x00,0xF8,0x3F,0x00,0x02,0x00,0x11,0x10,0x09,0x10,0x08,0x20,0x01,0x00,//U+91C7(��)
0x7F,0xFC,0x03,0x80,0x05,0x40,0x09,0x20,0x11,0x10,0x21,0x08,0xC1,0x06,0x01,0x00,
0x02,0x00,0x02,0x00,0x02,0x00,0x03,0xFC,0x02,0x00,0x02,0x00,0x3F,0xF0,0x20,0x10,//U+70B9(��)
0x20,0x10,0x20,0x10,0x3F,0xF0,0x00,0x00,0x24,0x88,0x22,0x44,0x42,0x44,0x80,0x04,
0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,//U+5EA6(��)
0x23,0xE0,0x20,0x00,0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E,
0x02,0x00,0x02,0x00,0x07,0xF0,0x08,0x20,0x38,0x40,0x04,0x80,0x03,0x40,0x0C,0x80,//U+591A(��)
0x71,0xF8,0x02,0x08,0x0C,0x10,0x32,0x20,0x01,0x40,0x01,0x80,0x0E,0x00,0x70,0x00,
0x09,0x00,0x08,0x80,0x1F,0xFC,0x30,0x80,0x5F,0xF8,0x90,0x80,0x1F,0xF8,0x10,0x80,//U+96C6(��)
0x1F,0xFC,0x11,0x00,0xFF,0xFE,0x05,0x40,0x09,0x20,0x31,0x18,0xC1,0x06,0x01,0x00,
0x10,0x40,0x10,0x20,0x20,0x20,0x23,0xFE,0x48,0x40,0xF8,0x88,0x11,0x04,0x23,0xFE,//U+7EDF(ͳ)
0x40,0x92,0xF8,0x90,0x40,0x90,0x00,0x90,0x19,0x12,0xE1,0x12,0x42,0x0E,0x04,0x00,
0x00,0x00,0x23,0xF8,0x12,0x08,0x12,0x08,0x83,0xF8,0x42,0x08,0x42,0x08,0x13,0xF8,//U+6E29(��)
0x10,0x00,0x27,0xFC,0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x00,0x00,
0x00,0x00,0x3F,0xF0,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x7F,0xFC,0x04,0x80,//U+65E0(��)
0x04,0x80,0x04,0x80,0x08,0x80,0x08,0x80,0x10,0x84,0x20,0x84,0x40,0x7C,0x80,0x00,
0x00,0xF8,0x3F,0x00,0x04,0x00,0x08,0x20,0x10,0x40,0x3F,0x80,0x01,0x00,0x06,0x10,//U+7CFB(ϵ)
0x18,0x08,0x7F,0xFC,0x01,0x04,0x09,0x20,0x11,0x10,0x21,0x08,0x45,0x04,0x02,0x00,
0x10,0x50,0x10,0x48,0x20,0x40,0x24,0x5C,0x45,0xE0,0xF8,0x40,0x10,0x5E,0x23,0xE0,//U+7EBF(��)
0x40,0x44,0xFC,0x48,0x40,0x30,0x00,0x22,0x1C,0x52,0xE0,0x8A,0x43,0x06,0x00,0x02,
};

//�������ظ���ֻ��дһ������
//��unsigned int code ChineseCode2[]˳���Ӧ��ASCII���С��������
//��16*��16
unsigned char code ChineseCharDot2[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,//U+FF1A(��)
0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x40,0x04,0x60,0x3C,0x40,0x24,0x58,0x2B,0xE0,0x28,0xA0,0x2D,0x20,//U+9648(��)
0x25,0x7C,0x23,0xA0,0x21,0x20,0x21,0x2C,0x22,0x24,0x20,0xE0,0x00,0x40,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x40,0x00,0x70,0x0F,0x80,0x08,0x10,0x0B,0x60,0x0E,0x20,//U+5EAD(ͥ)
0x14,0x78,0x13,0xA0,0x1A,0x38,0x26,0xC0,0x25,0x80,0x48,0x70,0x00,0x1C,0x00,0x00,
0x00,0x00,0x00,0xC0,0x04,0x40,0x04,0x40,0x08,0x78,0x09,0xC0,0x10,0x70,0x28,0xC0,//U+4F1F(ΰ)
0x48,0x7C,0x0B,0xC4,0x08,0x44,0x08,0x4C,0x08,0x58,0x08,0x40,0x00,0x40,0x00,0x00,
0x00,0x00,0x01,0x00,0x02,0x00,0x04,0x40,0x07,0xE0,0x05,0x20,0x06,0x40,0x07,0x40,//U+606F(Ϣ)
0x04,0xC0,0x07,0x40,0x01,0x8E,0x20,0x80,0x24,0x10,0x22,0x18,0x01,0xF0,0x00,0x00,
0x00,0x00,0x00,0x00,0x04,0x60,0x08,0x20,0x08,0x04,0x13,0xF8,0x10,0x00,0x28,0xE0,//U+4FE1(��)
0x48,0x00,0x08,0xE0,0x08,0x10,0x09,0xE8,0x09,0x10,0x08,0xF8,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x30,0x05,0x20,0x04,0x40,0x00,0x48,0x0F,0xBE,0x30,0x88,0x27,0xC0,//U+5B66(ѧ)
0x01,0x00,0x00,0xFC,0x3F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xC0,0x3C,0x40,0x28,0x78,0x29,0x80,0x2A,0x20,0x2D,0xC0,//U+9662(Ժ)
0x24,0x30,0x23,0xC0,0x20,0xC0,0x21,0x40,0x22,0x44,0x24,0x3E,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x10,0x07,0xD0,0x01,0x20,0x01,0x5E,0x7E,0xA0,//U+8005(��)
0x01,0x00,0x03,0xE0,0x06,0x20,0x0B,0xA0,0x32,0x20,0x03,0xE0,0x00,0x20,0x00,0x00,
0x00,0x00,0x00,0x40,0x04,0x40,0x04,0x40,0x08,0x84,0x08,0xF8,0x19,0x40,0x2A,0x40,//U+4F5C(��)
0x48,0x38,0x08,0x40,0x08,0x48,0x08,0x70,0x08,0x40,0x08,0x40,0x00,0x40,0x00,0x00,
};

unsigned char code Img_temp1_32[]={32,32,
/*--  ������һ��ͼ��D:\Pictures\ICON\www.easyicon.net\temperature_128px_1169919_easyicon.net.ico  --*/
/*--  ����x�߶�=32x32  --*/
0x00,0x07,0xC0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x1F,0xF0,0x00,0x00,0x1C,0x38,0x00,
0x00,0x1C,0x38,0x00,0x00,0x1C,0x38,0x00,0x00,0x1C,0xFF,0x00,0x00,0x1C,0xFF,0x80,
0x00,0x1C,0xFF,0x00,0x00,0x1C,0xF8,0x00,0x00,0x1C,0xF8,0x00,0x00,0x1C,0xFF,0x80,
0x00,0x1C,0xFF,0x80,0x00,0x1C,0xFF,0x00,0x00,0x1C,0xF8,0x00,0x00,0x1C,0xF8,0x00,
0x00,0x1C,0xF8,0x00,0x00,0x38,0xFC,0x00,0x00,0x71,0xFE,0x00,0x00,0xE7,0xFF,0x00,
0x00,0xEF,0xFF,0x00,0x01,0xDF,0xFF,0x00,0x01,0xDF,0xFF,0x00,0x01,0xDF,0xFF,0x00,
0x01,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFE,0x00,
0x00,0x7F,0xFE,0x00,0x00,0x3F,0xFC,0x00,0x00,0x1F,0xF0,0x00,0x00,0x07,0xC0,0x00,
};

unsigned char code Img_temp2_32[]={32,32,
/*--  ������һ��ͼ��D:\Pictures\ICON\www.easyicon.net\temperature_128px_1156063_easyicon.net.ico  --*/
/*--  ����x�߶�=32x32  --*/
0x1F,0x00,0x1F,0xE0,0x3F,0xC0,0x7F,0xF8,0x7F,0xE0,0xFF,0xFC,0xFF,0xE0,0xFF,0xFE,
0xF0,0xE1,0xE0,0x1E,0xE0,0xF1,0xE0,0x0F,0xE0,0xF3,0xC0,0x0F,0xE0,0xF3,0xC0,0x07,
0xF0,0xE3,0xC0,0x07,0xFF,0xE3,0xC0,0x07,0x7F,0xC3,0xC0,0x00,0x3F,0xC3,0xC0,0x00,
0x1F,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,
0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,
0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,0x02,0x00,0x03,0xC0,0x07,
0x00,0x03,0xC0,0x07,0x00,0x03,0xC0,0x0F,0x00,0x01,0xC0,0x0F,0x00,0x01,0xE0,0x1F,
0x00,0x00,0xFC,0x7E,0x00,0x00,0xFF,0xFC,0x00,0x00,0x7F,0xF8,0x00,0x00,0x1F,0xF0,
};

unsigned char code Img_check_ok_32[]={32,32,
/*--  ������һ��ͼ��C:\Users\Willian Chan\Downloads\emoticon_128px_1147394_easyicon.net.ico  --*/
/*--  ����x�߶�=32x32  --*/
0x00,0x1F,0xF8,0x00,0x00,0xFF,0xFE,0x00,0x01,0xFF,0xFF,0x80,0x07,0xE0,0x07,0xC0,
0x0F,0x80,0x01,0xE0,0x1F,0x00,0x00,0xF0,0x1C,0x00,0x00,0x78,0x3C,0x00,0x00,0x3C,
0x78,0x00,0x00,0x1C,0x70,0x00,0x08,0x0E,0x70,0x3C,0x3C,0x0E,0xE0,0x3C,0x3C,0x0E,
0xE0,0x3C,0x3C,0x07,0xE0,0x10,0x08,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,
0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x60,0x00,0x07,0xE0,0x60,0x00,0x07,
0xE0,0x78,0x00,0x0E,0x70,0x3F,0x80,0x0E,0x70,0x1F,0x80,0x1E,0x38,0x0F,0x00,0x1C,
0x3C,0x00,0x00,0x3C,0x1E,0x00,0x00,0x78,0x0F,0x00,0x00,0xF0,0x07,0x80,0x03,0xE0,
0x03,0xF0,0x0F,0xC0,0x01,0xFF,0xFF,0x80,0x00,0x7F,0xFE,0x00,0x00,0x0F,0xF0,0x00,
};

unsigned char code Img_check_no_ok_32[]={32,32,
/*--  ������һ��ͼ��C:\Users\Willian Chan\Downloads\disgusted_128px_1147386_easyicon.net.ico  --*/
/*--  ����x�߶�=32x32  --*/
0x00,0x1F,0xF8,0x00,0x00,0xFF,0xFE,0x00,0x01,0xFF,0xFF,0x80,0x07,0xE0,0x07,0xC0,
0x0F,0x80,0x01,0xE0,0x1F,0x00,0x00,0xF0,0x1C,0x00,0x00,0x78,0x3C,0x00,0x00,0x3C,
0x78,0x00,0x00,0x1C,0x70,0x60,0x06,0x0E,0x70,0x70,0x0E,0x0E,0xE0,0x18,0x18,0x0E,
0xE0,0x70,0x0E,0x07,0xE0,0x60,0x06,0x07,0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,
0xE0,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0xE0,0x1F,0x78,0x07,0xE0,0x3B,0xCC,0x07,
0xE0,0x20,0x06,0x0E,0x70,0x20,0x06,0x0E,0x70,0x20,0x06,0x1E,0x38,0x38,0x0C,0x1C,
0x3C,0x1F,0xF8,0x3C,0x1E,0x00,0x00,0x78,0x0F,0x00,0x00,0xF0,0x07,0x80,0x03,0xE0,
0x03,0xF0,0x0F,0xC0,0x01,0xFF,0xFF,0x80,0x00,0x7F,0xFE,0x00,0x00,0x0F,0xF0,0x00,
};
