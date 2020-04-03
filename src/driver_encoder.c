#include "driver_encoder.h"
volatile static int8_t counter = 0;
static int8_t last_a = 0;
void initDriverEncoder(void)
{
	sei();
	DDRB &= ~((1<<PB0));
	DDRD &= ~((1<<PD3));
	PORTB |= ((1<<PB0));
	PORTD |= ((1<<PD3));
	EICRA |= (1<<ISC11)|(1<<ISC10);
	EIMSK |= 1<<INT1;
}

void closeDriverEncoder(void)
{
	initDriverEncoder();
	counter = 0;
}

int16_t getValue(void)
{
	return counter;
}

static void updatePinEstate(int8_t * a, int8_t * b)
{
	*b = PINB & (1<<PB0);
	*a = PIND & (1<<PD3);
}
ISR(INT1_vect)
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
