
#include "LCD240128.h"
#include "DotCode.h"
#include <intrins.h>

unsigned char XPOS;			//�з���LCD����λ��ָ��
unsigned char YPOS;			//�з���LCD����λ��ָ��
bit CharImageReverse;		//�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)

//-------------------------------------------------------------------------------
//�ӳ�������:void beautifulshow(void)
//����:ͼ�λ���չʾ����
//-------------------------------------------------------------------------------
void beautifulshow(void)
{
	//ͼƬ����: ��(0,0)λ����ʾ32*32����ͼ��
    XPOS=0;
    YPOS=0;
	CharImageReverse=1;//�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)
    putimage(Img_temp1_32);	//д���ݵ���ǰLCDRAM��ַ��
	CharImageReverse=0;//�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)
	
	//ͼƬ����: ��(208,0)λ����ʾ32*32����ͼ��
    XPOS=208;
    YPOS=0;
    CharImageReverse=1;//�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)
    putimage(Img_temp2_32);	//д���ݵ���ǰLCDRAM��ַ��
	CharImageReverse=0;//�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)
	
	//�ַ�����ʾ: ��(40,8)λ����ʾ"���߶���¶Ȳɼ�ϵͳ"�ַ���.
	XPOS=40;
	YPOS=16;
	putstr(ChineseCode1,ChineseCharDot1,"��������¶Ȳɼ�ϵͳ",10);

	//�ַ�������: ��(40,8)λ�÷���"���߶���¶Ȳɼ�ϵͳ"�ַ���.
	XPOS=40;
	YPOS=16;
	CharImageReverse=1;//�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)
	putstr(ChineseCode1,ChineseCharDot1,"��������¶Ȳɼ�ϵͳ",10);
	CharImageReverse=0;//�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)
	
	//�ַ�����ʾ: ��(40,0)λ����ʾ"WELCOME TO MY SYSTEM"�ַ���.
	XPOS=40;
	YPOS=0;
	putstr(EnglishCode1,EnglishCharDot1,"WELCOME TO MY SYSTEM",10);

	//��ͼ: ��(0,35)Ϊ���Ͻ�-��(239,51)Ϊ���½�,������.
	rect(0,35,239,51,1);
	rect(0,51,239,67,1);
	rect(0,67,239,83,1);
	rect(0,83,239,99,1);

	//��ͼ: ��(0,104)-(119,127)-(239,104)����������,��������.
	triangle(0  ,104,119,127,239,104,1);//�ȱ�������
	triangle(0  ,107,104,127,0  ,127,1);//ֱ��������1
	triangle(239,107,134,127,239,127,1);//ֱ��������2
}

//-------------------------------------------------------------------------------
//����putcharΪ�ַ�����Ļ����ӳ���,putstrΪ�ַ�����������ӳ���,getchinesecodepos,
//getenglishcodeposΪ�ַ�����ĸ����ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:void putchar(unsigned int c).
//����:��(XPOS,YPOS)λ��д�����ַ�����,��c>128 ��ʾΪ�����ַ�,����Ϊ�����ַ�
//-------------------------------------------------------------------------------
void putchar(unsigned int *C_E_Code_Name,unsigned char *C_E_CharDot_Name,unsigned int c,unsigned int CharNumber)            //��λд�ַ��ӳ���
{   
	if(c>128)
        putsizeimage(CHINESECHARSIZE,CHINESECHARSIZE,getchinesecodepos(C_E_Code_Name,C_E_CharDot_Name,c,CharNumber));
    else
        putsizeimage(ENGLISHCHARSIZE,CHINESECHARSIZE,getenglishcodepos(C_E_Code_Name,C_E_CharDot_Name,c,CharNumber));
}

//-------------------------------------------------------------------------------
//�ӳ�������:void putstr(unsigned char code *s).
//����:д�ַ�������,��*s=0 ��ʾ�ַ�������.
//-------------------------------------------------------------------------------
void putstr(unsigned int *C_E_Code_Name,unsigned char *C_E_CharDot_Name,unsigned char code *s,unsigned int CharNumber)      //��ʾ�ַ����ӳ���,�ַ���Ϊ0ʱ�˳�
{   
	unsigned int c;
    while(1)
    {   
		c=*s;
        s++;
        if(c==0)
			break;
        if(c<128)
            putchar(C_E_Code_Name,C_E_CharDot_Name,c,CharNumber);			//Ӣ���ַ���
        else
        {   
			putchar(C_E_Code_Name,C_E_CharDot_Name,c*256+*s,CharNumber);	//�����ַ���
            s++;
        }
    }
}

//-------------------------------------------------------------------------------
//�ӳ�������:unsigned char code *getchinesecodepos(unsigned char ac).
//����:���ݵ�ǰ�����ַ���������õ���ǰ�����ַ�����ֿ����λ��.
//-------------------------------------------------------------------------------
unsigned char code *getchinesecodepos(unsigned int *ChineseCode_Name,unsigned char *ChineseCharDot_Name,unsigned int ac,unsigned int CharNumber)
{   
	unsigned int min,max,mid,midc;
    min=0;
    max=CharNumber-1;
    while(1)
    {   
		if(max-min<2)
        {   
			if(ChineseCode_Name[min]==ac)
                mid=min;
            else if(ChineseCode_Name[max]==ac)
                mid=max;
            else
                mid=0;
            break;
        }
        mid=(max+min)/2;
        midc=ChineseCode_Name[mid];
        if(midc==ac)
            break;
        else if(midc>ac)
            max=mid-1;
        else
            min=mid+1;
    }
    return ChineseCharDot_Name+mid*CHINESECHARDOTSIZE;
}

//-------------------------------------------------------------------------------
//�ӳ�������:unsigned char code *getenglishcodepos(unsigned char ac).
//����:���ݵ�ǰASCII�ַ���������õ���ǰASCII�ַ�����ֿ����λ��.
//-------------------------------------------------------------------------------
unsigned char code *getenglishcodepos(unsigned int *EnglishCode_Name,unsigned char *EnglishCharDot_Name,unsigned char ac,unsigned int CharNumber)
{   
	unsigned char min,max,mid,midc;
    min=0;
    max=CharNumber-1;
    while(1)
    {   
		if(max-min<2)
        {   
			if(EnglishCode_Name[min]==ac)
                mid=min;
            else if(EnglishCode_Name[max]==ac)
                mid=max;
            else
                mid=0;
            break;
        }
        mid=(max+min)/2;
        midc=EnglishCode_Name[mid];
        if(midc==ac)
            break;
        else if(midc>ac)
            max=mid-1;
        else
            min=mid+1;
    }
    return EnglishCharDot_Name+mid*ENGLISHCHARDOTSIZE;
}

//-------------------------------------------------------------------------------
//����putsizeimageΪͼ�ζ���Ļ����ӳ���,putimageΪͼ�ζ���������ӳ���
//-------------------------------------------------------------------------------
//�ӳ�������:void putsizeimage(unsigned char XSIZE,unsigned YSIZE,unsigned char code *s)
//����:��(XPOS,YPOS)λ�û���XSIZE�м�YISZE�е����ͼ��*S.
//-------------------------------------------------------------------------------
void putsizeimage(unsigned char XSIZE,unsigned char YSIZE,unsigned char code *s)
{  
	unsigned char k,lx,ly,a1,a2,x,Lcd_Mask;
	k=XPOS&0x7;
	XSIZE+=k;
	x=XPOS;
	s--;
	for(ly=0;ly<YSIZE;ly++,YPOS++)
	{  
		for(XPOS=x,lx=k;lx<XSIZE;)
		{  
			unsigned char p;
			a1=*s;
			s++;
			a2=*s;
			if(CharImageReverse)
			{   
				a1=~a1;
				a2=~a2;
			}
			for(p=0;p<k;p++)
			{  
				a2>>=1;
				if((a1&0x1)==1)
					a2+=0x80;
				a1>>=1;
			}
			if((k==0) && (XSIZE<lx+8))
			{   
				lcdpos();
				lx+=8;
				XPOS+=8;
			}
			else
			{   
				lcdpos();
				a1=lcdrd();
				lcdpos();
				lx+=8;
				XPOS+=8;
				Lcd_Mask=0xff;
				p=XSIZE&0x7;
				while(p>0)
				{   
					Lcd_Mask>>=1;
					XPOS--;
					p--;
				}
				p=0xff;
				while(XSIZE<lx)
				{   
					lx--;
					XPOS--;
					p<<=1;
				}
				Lcd_Mask&=p;
				a2&=Lcd_Mask;
				a2|=a1&(~Lcd_Mask);
			}
			lcdwd(a2);
		}
      if((k!=0) && (XSIZE&0x7 != 0) && (k >= XSIZE&0x7)) s--;
	}
	if(XDOTS-x < XSIZE-k)
		XPOS=0;
	else
		YPOS-=YSIZE;
}

//-------------------------------------------------------------------------------
//�ӳ�������:void putimage(unsigned char code *s).
//����:��(XPOS,YPOS)λ�û���XSIZE[*s]�м�YISZE[*(s+1)]�е����ͼ��[*(s+2)].
//-------------------------------------------------------------------------------
void putimage(unsigned char code *s)    //��ʾͼ���ӳ���
{   
	unsigned char XSIZE,YSIZE;
    XSIZE=*s;
    s++;
    YSIZE=*s;
    s++;
    putsizeimage(XSIZE,YSIZE,s);
}

//-------------------------------------------------------------------------------
//����pointΪ��ͼ�����Ļ����ӳ���,line,rect,triangleΪ��ͼ�����������ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:void point(bit b).
//����:��b��������(XPOS,YPOS)λ�û��Ƶ�.
//-------------------------------------------------------------------------------
void point(bit b)
{   
	unsigned char i,Lcd_Mask,j;
    Lcd_Mask=0x80;
    i=XPOS&0x7;
    while(i>0)
    {   
		Lcd_Mask>>=1;
        i--;
    }
    lcdpos();
    j=lcdrd();
    lcdpos();
    if(b)
        lcdwd(j|Lcd_Mask);
    else
        lcdwd(j&(~Lcd_Mask));
}

//-------------------------------------------------------------------------------
//�ӳ�������:void line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b)
//����:��b�����ݻ���(x0,y0)-(x1,y1)��ֱ��
//-------------------------------------------------------------------------------
void line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b)
{   
	unsigned char dx,dy;
	unsigned int dk;
	XPOS=x0;
	YPOS=y0;
	point(b);
	dx=(x1>=x0)?x1-x0:x0-x1;
	dy=(y1>=y0)?y1-y0:y0-y1;
	if(dx==dy)
	{
		while(XPOS!=x1)
		{
			if(x1>x0) XPOS++;else XPOS--;
            if(y1>y0) YPOS++;else YPOS--;
			point(b);
        }
    }
    else if (dx>dy)
    {   
		dk=dy;
        dy=0;
        while(XPOS!=x1)
        {   
			if(x1>x0) XPOS++;else XPOS--;
            dy++;
            if(y1>y0) YPOS=y0+(dk*dy+dx/2)/dx;else YPOS=y0-(dk*dy+dx/2)/dx;
            point(b);
        }
    }
    else
    {   
		dk=dx;
        dx=0;
        while(YPOS!=y1)
        {   
			if(y1>y0) YPOS++;else YPOS--;
            dx++;
            if(x1>x0) XPOS=x0+(dk*dx+dy/2)/dy;else XPOS=x0-(dk*dx+dy/2)/dy;
            point(b);
        }
    }
}

//-------------------------------------------------------------------------------
//�ӳ�������:void rect(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b)
//����:��b�����ݻ���(x0,y0)-(x1,y1)�ľ���
//-------------------------------------------------------------------------------
void rect(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b)
{   
	line(x0,y0,x1,y0,b);
	line(x1,y0,x1,y1,b);
	line(x1,y1,x0,y1,b);
	line(x0,y1,x0,y0,b);
}

//-------------------------------------------------------------------------------
//�ӳ�������:void triangle(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,bit b)
//����:��b�����ݻ���(x0,y0)-(x1,y1)-(x2,y2)��������
//-------------------------------------------------------------------------------
void triangle(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,bit b)
{   
	line(x0,y0,x1,y1,b);
	line(x1,y1,x2,y2,b);
	line(x2,y2,x0,y0,b);
}

//-------------------------------------------------------------------------------
//����lcdfill,lcdpos,lcdresetΪT6963��Ӳ���ӿڵ�240128Һ����ʾģ��Ļ����ӳ���
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdfill(unsigned char d).
//����:������ʾd��ʾ���ֽ�����.
//-------------------------------------------------------------------------------
void lcdfill(unsigned char d)          	//������ʾd������ֽ������ӳ���
{   
	unsigned char i,j;
	lcdwc3(0x24,0x00,0x00);            	//�����ڲ�RAM��ַΪ0
	lcdwc(0xb0);						//�����Զ�д��ʽ��һ��Ҫ���ϡ��Զ�дģʽ���Ĵ��룬���������������ʾ��������������������
	for(i=0;i<128;i++)    				//128��
		for(j=0;j<30;j++)               //30���ֽ����ݹ�240��
			lcdwd(d);                   //��ͼ������
	lcdwc(0xb2);						//�˳��Զ���д��ʽ
}

//-------------------------------------------------------------------------------
//�ӳ�������:void lcdpos(void).
//����:���������(XPOS,YPOS)λ�ö�Ӧ���ڲ�RAM��ַ.
//-------------------------------------------------------------------------------
void lcdpos(void)                       //���������(XPOS,YPOS)�ڲ�RAM��ַ���ӳ���
{  
	unsigned int CurrentAddress;
	//LCDRAM��ַ=30*YPOS+(XPOS/8)+3840(or+0x0f00)����Ϊ��ʼ����ʱ������ͼ����ʾ���׵�ַΪlcdwc3(0x42,0x00,0x0f)����д�ڰ�λ��д�߰�λ��
	CurrentAddress=YPOS*30+XPOS/8+0x0f00;//��3840��3840��0x0f00��ʮ���Ʊ����Ա���ͼ�κ��ı�ͬʱ��ʾʱ���룡������������������
	lcdwc3(0x24,CurrentAddress&0xff,CurrentAddress/256);
}

//-------------------------------------------------------------------------------
//�ӳ�������:void lcdreset(void)
//����:Һ����ʾ��������ʼ��
//-------------------------------------------------------------------------------
void lcdreset(void)					//Һ����ʾ��������ʼ���ӳ���
{   
	CEPIN=0;						//ʹ��Ƭѡ�ź�
	WRPIN=1;						//��ֹд
	RDPIN=1;						//��ֹ��
	lcdwc3(0x24,0x00,0x00);			//�����ı���ʾ�׵�ַ
	lcdwc3(0x40,0x00,0x00);			//�����ı���ʾ���׵�ַ
	lcdwc3(0x41,0x1e,0x00);			//�����ı���ʾ�����
	lcdwc3(0x42,0x00,0x0f);			//����ͼ����ʾ���׵�ַ���ı�����ַ��ͼ������ַҪ�����ı��Ļ�128*30=3840=0x0f00������ͼ���׵�ַ��0x0f00��������������������
	lcdwc3(0x43,0x1e,0x00);			//����ͼ����ʾ�����Ϊ30�ֽڹ�240��
	lcdwc3(0x22,0x02,0x00);			//CGRAMƫ�õ�ַ����
	lcdwc(0x80);                    //OR MODE
	lcdwc(0x9c);					//�����ı���ʾ������ͼ����ʾ
}

//-------------------------------------------------------------------------------
//����lcdwd,lcdrd,lcdwc,lcdwc2,lcdwc3ΪT6963C��Ӳ���ӿ�[MCS51ģ����߽ӿڷ�ʽ]��
//    �����ӳ���;lcdwdata,lcdrdata,lcdwaitidleΪ�ڲ��ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdwd(unsigned char d).
//����:��Һ����ʾ������дͼ������.
//-------------------------------------------------------------------------------
void lcdwd(unsigned char d)             //��ͼ�������ӳ���
{   
	lcdwc2(0xc0,d);
}

//-------------------------------------------------------------------------------
//�ӳ�������:unsigned char lcdrd(void).
//����:��Һ����ʾ�������ж�ͼ������.
//-------------------------------------------------------------------------------
unsigned char lcdrd(void)               //��ͼ�������ӳ���
{   
	lcdwc(0xc1);                        //�Ͷ�ͼ������ָ��
	return lcdrdata();                  //������
}

//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc(unsigned char c).
//����:��Һ����ʾ��������ָ��.
//-------------------------------------------------------------------------------
void lcdwc(unsigned char c)             //��ָ���ӳ���
{   
	lcdwaitidle();                      //���Һ����ʾ�������Ƿ����
	lcd_DATA=c;
	CDPIN=1;                            //CD=1 CE=0 WR=0
	CEPIN=0;
	WRPIN=0;
	_nop_();
	WRPIN=1;
	CEPIN=1;
}

//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc2(unsigned char c,unsigned char d).
//����:��Һ����ʾ��������2�ֽ�ָ��.
//-------------------------------------------------------------------------------
void lcdwc2(unsigned char c,unsigned char d) //��2�ֽ�ָ���ӳ���
{   
	lcdwdata(d);                        //��ָ�����
	lcdwc(c);                           //��ָ����
}

//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc3(unsigned char c,unsigned char d1,unsigned char d2).
//����:��Һ����ʾ��������3�ֽ�ָ��.
//-------------------------------------------------------------------------------
void lcdwc3(unsigned char c,unsigned char d1,unsigned char d2) //��3�ֽ�ָ���ӳ���
{   
	lcdwdata(d1);                        //��ָ�����1
	lcdwdata(d2);                        //��ָ�����2
	lcdwc(c);                            //��ָ����
}

//-------------------------------------------------------------------------------
//�ӳ�������:unsigned char lcdrdata(void).
//����:��Һ����ʾ�������ж�����.
//-------------------------------------------------------------------------------
unsigned char lcdrdata(void)            //�������ӳ���
{   
	unsigned char d;
	lcdwaitidle();                      //���Һ����ʾ�������Ƿ����
	lcd_DATA=0xff;
	CDPIN=0;                            //CD=0 CE=0 RD=0
	CEPIN=0;
	RDPIN=0;
	_nop_();
	d=lcd_DATA;
	RDPIN=1;
	CEPIN=1;
	return d;
}

//-------------------------------------------------------------------------------
//�ӳ�������:void lcdwdata(unsigned char d).
//����:��Һ����ʾ������������.
//-------------------------------------------------------------------------------
void lcdwdata(unsigned char d)          //�������ӳ���
{   
	lcdwaitidle();                      //���Һ����ʾ�������Ƿ����
	lcd_DATA=d;
	CDPIN=0;                            //CD=0 CE=0 WR=0
	CEPIN=0;
	WRPIN=0;
	_nop_();
	WRPIN=1;
	CEPIN=1;
}

//-------------------------------------------------------------------------------
//�ӳ�������:voidlcdwaitidle(void).
//����:æ���,�ڶ�Һ����ʾ������������ÿһ��ָ��֮ǰ,����Һ����ʾ���Ƿ����.
//-------------------------------------------------------------------------------
void lcdwaitidle(void)                  //æ����ӳ���
{   
	unsigned char i,d;
	lcd_DATA=0xff;
	CDPIN=1;                            //CD=1 CE=0 RD=0
	CEPIN=0;
	for(i=0;i<20;i++)                   //
	{   RDPIN=0;
		_nop_();
		d=lcd_DATA;
		RDPIN=1;
		if( (d&0x3) == 0x3 ) break;     //D0D1=11 �����˳�
	}
	CEPIN=1;
}

//-------------------------------------------------------------------------------
//����CharLocateXY,DirectDisplayChar,DirectDisplayStringΪֱ����ʾ�ַ����Ļ����ӳ���
//-------------------------------------------------------------------------------
//�ӳ�������:void CharLocateXY(uchar x,uchar y)
//����:ֱ����ʾʱ�趨��ʾ��ַ����
void CharLocateXY(uchar x,uchar y)
{
	uint  temp;
	temp= XDOTS/8*y + x;
	lcdwc3(0x24,temp&0xff,temp/256);
}

//-------------------------------------------------------------------------------
//�ӳ�������:void DirectDisplayChar(uchar x,uchar y,uchar CharByte)
//����:ֱ����ʾһ��ASCII�뺯��
void DirectDisplayChar(uchar x,uchar y,uchar CharByte)
{
	CharLocateXY(x,y);
	lcdwc2(0xC4,CharByte-0x20);	//�ڲ�����Ӣ���ֿ��Ǵ�0x00��ʼ,Ҳ����˵�ո�0x20���ֿ�ֵ��0x00,����-0x20
}

//-------------------------------------------------------------------------------
//�ӳ�������:void DirectDisplayString(uchar x,uchar y,uchar *str)
//����:ֱ����ʾһ���ַ���
void DirectDisplayString(uchar x,uchar y,uchar *str)
{
	while(*str != 0)
	{
		if(x> (XDOTS/8-1))//�Զ�����
		{
			x=0;
			y++;
		}
		DirectDisplayChar(x,y,*str);
		++x;
		++str;
	}
}
