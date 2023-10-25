#ifndef keypad_h
#define keypad_h
#include "Arduino.h"
const char keymap[5][3]={{'3','6','9'},{'5','2','8'},{'4','1','7'},{'u','r','0'},{'l','m','d'}};

class matrix_keypad
{
	public:
		matrix_keypad(uint8_t r1,uint8_t r2,uint8_t r3,uint8_t r4,uint8_t r5,uint8_t c1,uint8_t c2,uint8_t c3);
		char key_in();
		void init();
	private:
		uint8_t row[5];
		uint8_t col[3];

};
#endif
