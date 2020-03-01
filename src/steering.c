#include "steering.h"
static void setRefADC(void)
{
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
}
static void alingToLeftADC(void)
{
	ADMUX |=(1<<ADLAR);
}
static void selectChannelCero(void)
{
	ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
}
static void enableADC(void)
{
	ADCSRA |= 1 << ADEN;
}
static void setPreescalerThirtyTwo(void)
{
	ADCSRA |= (1<<ADPS2)|(1<<ADPS0);
	ADCSRA &= ~(1<<ADPS1);
}
void initSteering(void)
{
	setRefADC();
	alingToLeftADC();
	selectChannelCero();
	setPreescalerThirtyTwo();
	enableADC();
}
void closeSteering(void)
{
}
static void startConversion(void)
{
	ADCSRA |= 1<<ADSC;
}
#define DEADZONE 35
uint8_t getSteeringValue(void)
{
	startConversion();
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA |= 1 << ADIF;
	return 200;
//	if(ADCH > 126 && ADCH < (126+DEADZONE))
//		return ADCH+DEADZONE;
//	else
//		return ADCH - DEADZONE;
}
