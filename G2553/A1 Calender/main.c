#include<msp430g2553.h>
typedef unsigned char uchar;
typedef unsigned int uint;
/**************�궨��***************/
#define DataDir P1DIR
#define DataPort P1OUT
#define Busy 0x80
#define CtrlDir P2DIR
#define CLR_RS P2OUT&=~BIT0; //RS = P2.0
#define SET_RS P2OUT|=BIT0;
#define CLR_RW P2OUT&=~BIT1; //RW = P2.1
#define SET_RW P2OUT|=BIT1;
#define CLR_EN P2OUT&=~BIT2; //EN = P2.2
#define SET_EN P2OUT|=BIT2;
/**************�궨��***************/
#define DS_RST BIT3 //DS_RST = P2.3
#define DS_SCLK BIT4 //DS_SCLK = P2.4
#define DS_IO BIT5 //DS_IO = P2.5
#define DS_RST_IN P2DIR &= ~DS_RST
#define DS_RST_OUT P2DIR |= DS_RST
#define DS_RST0 P2OUT &= ~DS_RST
#define DS_RST1 P2OUT |= DS_RST
#define DS_SCLK_IN P2DIR &= ~DS_SCLK
#define DS_SCLK_OUT P2DIR |= DS_SCLK
#define DS_SCLK0 P2OUT &= ~DS_SCLK
#define DS_SCLK1 P2OUT |= DS_SCLK
#define DS_IO_IN P2DIR &= ~DS_IO
#define DS_IO_OUT P2DIR |= DS_IO
#define DS_IO0 P2OUT &= ~DS_IO
#define DS_IO1 P2OUT |= DS_IO
#define DS_IO_BIT P2IN & DS_IO
uchar sign;//����һ������־λ
uchar second,minute,hour,week,day,month,year;//�롢�֡�ʱ�����ڡ��ա��¡���
/*******************************************
�������ƣ�delay
�� �ܣ���ʱһ��ʱ��
�� ����time--��ʱ����
********************************************/
void delay( uint time)
{
 uint i;
for(i = 0;i < time;i++) _NOP();
}
/*******************************************
�������ƣ�Delay5ms �� �ܣ���ʱԼ5ms
********************************************/
void Delay5ms(void)
{
 uint i=40000;
while (i != 0)
{
i--;
}
}
/*******************************************
�������ƣ�WaitForEnable
�� �ܣ��ȴ�1602Һ������ڲ�����
********************************************/
void WaitForEnable(void)
{
P1DIR &= 0x00; //��P1���л�Ϊ����״̬
CLR_RS;
SET_RW;
_NOP();
SET_EN;
_NOP();
_NOP();
while((P1IN & Busy)!=0); //���æ��־
CLR_EN;
P1DIR |= 0xFF; //��P1���л�Ϊ���״̬
}
/*******************************************
�������ƣ�write_com
�� �ܣ���Һ��ģ��д������
********************************************/
void write_com(uchar cmd)
{
WaitForEnable(); // ���æ�ź�?
CLR_RS;
CLR_RW;
_NOP();
DataPort = cmd; //��������д�����ݶ˿�
_NOP();
SET_EN; //����ʹ�������ź�
_NOP();
_NOP();
CLR_EN;
}
/*******************************************
�������ƣ�write_data
�� �ܣ���Һ����ʾ�ĵ�ǰ��ַд����ʾ����
�� ����data--��ʾ�ַ�����
����ֵ ����
********************************************/
void write_data( uchar data )
{
WaitForEnable(); //�ȴ�Һ����æ
SET_RS;
CLR_RW;
_NOP();
DataPort = data; //����ʾ����д�����ݶ˿�
_NOP();
SET_EN; //����ʹ�������ź�
_NOP();
_NOP();
CLR_EN;
}
void Write1602(uchar add,uchar dat)
{
write_com(add);
write_data(dat);
}
void zifuchuan(uchar *ch)
{
while(*ch!=0)
write_data(*ch++);
Delay5ms();
}
/*******************************************
�������ƣ�LcdReset
�� �ܣ���1602Һ��ģ����и�λ����
********************************************/
void LcdReset(void)
{
CtrlDir |= 0x07; //�����߶˿���Ϊ���״̬
DataDir = 0xFF; //���ݶ˿���Ϊ���״̬
write_com(0x38);//�涨�ĸ�λ����
Delay5ms();
write_com(0x38);
Delay5ms();
write_com(0x38);
Delay5ms();
write_com(0x38);//��ʾģʽ����
write_com(0x06);//д�ַ�ʱ���岻�ƶ�
write_com(0x0c);//��ʾ���������α꣬����˸
write_com(0x01);//��ʾ����
Write1602(0x80,'2');
Write1602(0x81,'0');
Write1602(0x80+4,'-');
Write1602(0x80+7,'-');
Write1602(0x80+0x40+5,':');
Write1602(0x80+0x40+8,':');
}
/*******************************************
�������ƣ�Reset_DS1302
�� �ܣ���DS1302���и�λ����
********************************************/
void Reset_DS1302(void)
{
DS_RST_OUT; //RST��Ӧ��IO����Ϊ���״̬
DS_SCLK_OUT; //SCLK��Ӧ��IO����Ϊ���״̬
DS_SCLK0; //SCLK=0
DS_RST0; //RST=0
delay(10);
DS_SCLK1; //SCLK=1
}
/*******************************************
�������ƣ�Write1Byte
�� �ܣ���DS1302д��1���ֽڵ�����
********************************************/
void Write_Byte(uchar wdata)
{
uchar i;
DS_IO_OUT; //IO��Ӧ��IO����Ϊ���״̬
DS_RST1; //REST=1;
for(i = 8; i > 0; i--)
{
if(wdata&0x01)
DS_IO1;
else
DS_IO0;
DS_SCLK0;
delay(10);
DS_SCLK1;
delay(10);
wdata >>= 1;
}
}
/*******************************************
�������ƣ�Read1Byte
�� �ܣ���DS1302����1���ֽڵ�����
********************************************/
uchar Read_Byte()
{
uchar i;
uchar rdata = 0X00;
DS_IO_IN; //SDA��Ӧ��IO����Ϊ����״̬
DS_RST1; //REST=1;
for(i = 8; i > 0; i--)
{
DS_SCLK1;
delay(10);
DS_SCLK0;
delay(10);
rdata >>= 1;
if(DS_IO_BIT)
rdata |= 0x80;
}
return(rdata);
}
/*******************************************
�������ƣ�Write_dat
�� �ܣ���ĳ���Ĵ���д��һ���ֽ�����
�� ����add--�Ĵ�����ַ
dat--д�������
********************************************/
void Write_dat(uchar add, uchar dat)
{
DS_RST0;
DS_SCLK0;
_NOP();
DS_RST1;
Write_Byte(add); //д���ַ
Write_Byte(dat); //д������
DS_SCLK1;
DS_RST0;
}
/*******************************************
�������ƣ�Read_dat
�� �ܣ���ĳ���Ĵ�������һ���ֽ�����
�� ����addr--�Ĵ�����ַ
����ֵ ������������
********************************************/
uchar read_1302add(uchar add)
{
uchar rdata;
DS_RST0;
DS_SCLK0;
_NOP();
DS_RST1;
Write_Byte(add); //д���ַ
rdata = Read_Byte(); //��������
DS_SCLK1;
DS_RST0;
return(rdata);
}
/***********��ʼ��1302*************/
void init_1302()
{
sign=read_1302add(0x81);//����Ĵ������λ,����ʱ��״̬
if((sign&0x80)!=0);//�ж�ʱ���Ƿ�ر�,���ڲ��ر�,���ʼ��,���������
{
Write_dat(0x8e,0x00);
Write_dat(0x80,((30/10)<<4|(30%10)));//д��Ĵ�������д���ֵ30
Write_dat(0x82,((47/10)<<4|(47%10)));//д�ּĴ�������д���ֵ47
Write_dat(0x84,((23/10)<<4|(23%10)));//дСʱ�Ĵ�������д���ֵ23
Write_dat(0x86,((18/10)<<4|(18%10)));//д�ռĴ�������д���ֵ18
Write_dat(0x88,((6/10)<<4|(6%10)));//д�¼Ĵ�������д���ֵ6
Write_dat(0x8a,((4/10)<<4|(4%10)));//д�ܼĴ�������д���ֵ4
Write_dat(0x8c,((20/10)<<4|(20%10)));//д��Ĵ�������д���ֵ20������д2019��
Write_dat(0x90,0xa5);//д��緽ʽ
Write_dat(0x8e,0x80);//����д����
}
}
/*****************�������ʮ������***************************/
uchar readsecond()
{
uchar dat;
dat=read_1302add(0x81);
second=((dat&0x70)>>4)*10+(dat&0x0f);
return second;
}
/*****************�����ֵ�ʮ������***************************/
uchar readminute()
{
uchar dat;
dat=read_1302add(0x83);
minute=((dat&0x70)>>4)*10+(dat&0x0f);
return minute;
}
/*****************����Сʱ��ʮ������***************************/
uchar readhour()
{
uchar dat;
dat=read_1302add(0x85);
hour=((dat&0x70)>>4)*10+(dat&0x0f);
return hour;
}
/*****************�������ʮ������***************************/
uchar readday()
{
uchar dat;
dat=read_1302add(0x87);
day=((dat&0x70)>>4)*10+(dat&0x0f);
return day;
}
/*****************�����µ�ʮ������***************************/
uchar readmonth()
{
uchar dat;
dat=read_1302add(0x89);
month=((dat&0x70)>>4)*10+(dat&0x0f);
return month;
}
/*****************�����ܵ�ʮ������***************************/
uchar readweek()
{
uchar dat;
dat=read_1302add(0x8b);
week=((dat&0x70)>>4)*10+(dat&0x0f);
return week;
}
/*****************�������ʮ������***************************/
uchar readyear()
{
uchar dat;
dat=read_1302add(0x8d);
year=((dat&0xf0)>>4)*10+(dat&0x0f);
return year;
}
/************************��������ʱ��**********************/
void readtime()
{
readsecond();
readminute();
readhour();
readday();
readmonth();
readweek();
readyear();
}
/*********************��1602д��ʱ��****************************/
void write_second()
{
uchar shi,ge;
shi=second/10;
ge=second%10;
Write1602(0x80+0x40+9,0x30+shi);
Write1602(0x80+0x40+10,0x30+ge);
}
void write_minute()
{
uchar shi,ge;
shi=minute/10;
ge=minute%10;
Write1602(0x80+0x40+6,0x30+shi);
Write1602(0x80+0x40+7,0x30+ge);
}
void write_hour()
{
uchar shi,ge;
shi=hour/10;
ge=hour%10;
Write1602(0x80+0x40+3,0x30+shi);
Write1602(0x80+0x40+4,0x30+ge);
}
void write_day()
{
uchar shi,ge;
shi=day/10;
ge=day%10;
Write1602(0x80+8,0x30+shi);
Write1602(0x80+9,0x30+ge);
}
void write_month()
{
uchar shi,ge;
shi=month/10;
ge=month%10;
Write1602(0x80+5,0x30+shi);
Write1602(0x80+6,0x30+ge);
}
void write_year()
{
uchar shi,ge;
shi=year/10;
ge=year%10;
Write1602(0x80+2,0x30+shi);
Write1602(0x80+3,0x30+ge);
}
void write_week()
{
Write1602(0x80+12,0x30+week);
switch(week)
{
case 1: Write1602(0x80+12,'M');
Write1602(0x80+13,'O');
Write1602(0x80+14,'N');
break;
case 2:Write1602(0x80+12,'T');
Write1602(0x80+13,'U');
Write1602(0x80+14,'E');
break;
case 3:Write1602(0x80+12,'W');
Write1602(0x80+13,'E');
Write1602(0x80+14,'N');
break;
case 4:Write1602(0x80+12,'T');
Write1602(0x80+13,'H');
Write1602(0x80+14,'U');
break;
case 5:Write1602(0x80+12,'F');
Write1602(0x80+13,'R');
Write1602(0x80+14,'I');
break;
case 6:Write1602(0x80+12,'S');
Write1602(0x80+13,'A');
Write1602(0x80+14,'T');
break;
case 7:Write1602(0x80+12,'S');
Write1602(0x80+13,'U');
Write1602(0x80+14,'N');
break;
}
}
/*************************������*************************/
void main( void )
{
/*�������г���ر����е�IO��*/
P1DIR = 0XFF;P1OUT = 0XFF;
P2DIR = 0XFF;P2OUT = 0XFF;
WDTCTL = WDTPW + WDTHOLD; //�رտ��Ź�
LcdReset();
//zifuchuan("The time is:");
//ѭ��������ʾ
init_1302();
while(1)
{
readtime();
write_second();
write_minute();
write_hour();
write_day();
write_month();
write_year();
write_week();
}
}
