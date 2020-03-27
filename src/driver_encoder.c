#include "driver_encoder.h"
volatile static int8_t counter = 0;
static int8_t last_a = 0;
void initDriverEncoder(void)
{
	sei();
	DDRB &= ~((1<<PB0)|(1<<PB1));
	PORTB &= ~((1<<PB0)|(1<<PB1));
	PCICR |= 1<<PCIE0;
	PCMSK0 |= 1<<PCINT0;
}

void closeDriverEncoder(void)
{
	initDriverEncoder();
	counter = 0;
}

int8_t getValue(void)
{
	return counter;
}

static void updatePinEstate(int8_t * a, int8_t * b)
{
	*a = PINB & ( 1<<PB0);
	*b = PINB & ( 1<<PB1);
}
ISR(PCINT0_vect)
{
	static int8_t a;
	static int8_t b;
	updatePinEstate(&a, &b);
	if(a != last_a){
		if(a && !b)
			counter ++;
		else if(a && b)
			counter --;
	}
	last_a = a;
}
