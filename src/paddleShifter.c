#include "paddleShifter.h"

void initPaddleShifter(void)
{
	DDRB &= ~((1<<PB2)|(1<<PB3));
	PORTB |= (1<<PB2)|(1<<PB3);
}
uint8_t getPaddleShifter(void)
{
	static uint8_t paddlebits = 0;
	paddlebits = PINB & 0xc;
	if(paddlebits == 0xc)
		return 0;
	else if(paddlebits == 0x8)
		return 1;
	else if(paddlebits == 0x4)
		return 2;
	return 0;
}

