#include "Arduino.h"
#include "keypad.h"

matrix_keypad::matrix_keypad(uint8_t r1,uint8_t r2,uint8_t r3,uint8_t r4,uint8_t r5,uint8_t c1,uint8_t c2,uint8_t c3)
{
	row[0]=r1;
	row[1]=r2;
	row[2]=r3;
	row[3]=r4;
	row[4]=r5;
	col[0]=c1;
	col[1]=c2;
	col[2]=c3;
}

void matrix_keypad::init()
{
	for(int r=0;r<5;r++)
  	{
   		pinMode(row[r],INPUT);       // Set row pins as input
    		digitalWrite(row[r],1);   // turn on Pull-ups
 	 }
  	for(int c=0;c<3;c++)
  	{
    		pinMode(col[c],OUTPUT);     // Set column pins as outputs for writing
    		digitalWrite(col[c],1);  // Make all columns inactive
  	}
}

char matrix_keypad::key_in()
{
  	char ch=0;
  	for(int c=0;c<3;c++)
  	{
    		digitalWrite(col[c],0);
    		for(int r=0;r<5;r++)
    		{
      			if(digitalRead(row[r])==0)
      			{
        			while(digitalRead(row[r])==0);  
        			ch=keymap[r][c];
			}
    		}
    		digitalWrite(col[c],1);
  	}
  	return ch;
}