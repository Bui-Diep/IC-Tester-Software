#include "Arduino.h"
#include "lcd.h"
uint8_t din1,clk1;
nokia_lcd::nokia_lcd(uint8_t ce,uint8_t rst,uint8_t dc,uint8_t din,uint8_t clk)
{
	CE=portOutputRegister(digitalPinToPort(ce));	
	RST=portOutputRegister(digitalPinToPort(rst));
	DC=portOutputRegister(digitalPinToPort(dc));
	CEm=digitalPinToBitMask(ce);
	RSTm=digitalPinToBitMask(rst);
	DCm=digitalPinToBitMask(dc);
	pinMode(ce,OUTPUT);
  	pinMode(rst,OUTPUT);
  	pinMode(dc,OUTPUT);
  	pinMode(din,OUTPUT);
  	pinMode(clk,OUTPUT);
	DIN=din;
	CLK=clk;
  	*RST&=~RSTm; 
  	*RST|=RSTm;
	dc_set(C,0x21 );  // LCD Extended Commands
  	dc_set(C,0xB9 );  // Set LCD Vop (Contrast)
  	dc_set(C,0x04 );  // Set Temp coefficent
  	dc_set(C,0x14 );  // LCD bias mode 1:48
  	dc_set(C,0x0C );  // LCD in normal mode
  	dc_set(C,0x20);
  	dc_set(C,0x0C);
}

void nokia_lcd::dis_char(char ch)
{
  dc_set(D,0x00);
  for(int i=0;i<5;i++)
  {
      dc_set(D,gen_font[ch - 0x20][i]);
  }
}

void nokia_lcd::dis_num(long int n,byte y,char ch)
{
    char a[10];
    int no=-1,d;
    if(n<=9999)
    {
        itoa(n,a,10); 
        string(a,y,ch);
    }
    else
    {
	long int temp;
	temp=n;
	while(temp>0)
	{
	    no++;
	    temp=temp/10;
	}
	a[no+1]='\0';
	for(int i=no;i>=0;i--)
	{
	    d=n-(n/10)*10;
	    a[i]=d+48;
	    n=n/10;
        }
    string(a,y,ch);
    }
}

void nokia_lcd::erase()
{
  
    for(int i=0;i<63;i++)
    {
    	dc_set(D,0x00);
	dc_set(D,0x00);
	dc_set(D,0x00);
	dc_set(D,0x00);
	dc_set(D,0x00);
	dc_set(D,0x00);
	dc_set(D,0x00);
	dc_set(D,0x00);
    }
   

}

void nokia_lcd::erase_row(int x)
{
  if(x==0)
  {
    go2xy(0,0);
    for(int i=0;i<=83;i++)
      dc_set(D,0x00);
  }
  else if(x==1)
  {
    go2xy(0,1);
    for(int i=0;i<=83;i++)
      dc_set(D,0x00);
  }
  else if(x==2)
  {
    go2xy(0,2);
    for(int i=0;i<=83;i++)
      dc_set(D,0x00);
  }
  else if(x==3)
  {
    go2xy(0,3);
    for(int i=0;i<=83;i++)
      dc_set(D,0x00);
  }
  else if(x==4)
  {
    go2xy(0,4);
    for(int i=0;i<=83;i++)
      dc_set(D,0x00);
  }
  else if(x==5)
  {
    go2xy(0,5);
    for(int i=0;i<=83;i++)
      dc_set(D,0x00);
  }
}

void nokia_lcd::string(char *ch,int y,char c)
{
  int x,s;
  s=strlen(ch);
  if(c=='c')
  {
    x=(84-6*s+1)/2-1;
    go2xy(x,y);
  }
  if(c=='l')
  {
    go2xy(0,y);
  }
  if(c=='r')
  {
    x=84-(s*6);
    go2xy(x,y);
  }
  while(*ch)
  {
    dis_char(*ch++);
  }
}

void nokia_lcd::dc_set(byte x,byte y)
{
  if(x==1)
  	*DC|=DCm;
  else
	*DC&=~DCm; 

  *CE&=~CEm;

  shiftOut(DIN,CLK,MSBFIRST,y);

  *CE|=CEm;
}

void nokia_lcd::go2xy(int x,int y)
{
  dc_set(0,0x80|x);
  dc_set(0,0x40|y);
}


