#include "paddleShifter.h"

void initPaddleShifter(void)
{
	DDRB &= ~((1<<PB1)|(1<<PB0));
	PORTB |= (1<<PB1)|(1<<PB0);
}
uint8_t getPaddleShifter(void)
{
	static uint8_t paddlebits = 0;
	paddlebits = PINB & 0x3;
	if(paddlebits == 3)
		return 0;
	else if(paddlebits == 2)
		return 1;
	else if(paddlebits == 1)
		return 2;
	return 0;
}

