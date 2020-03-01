#include "driverADC.h"
static void setRefADC(void)
{
        ADMUX |= (1<<REFS0);
        ADMUX &= ~(1<<REFS1);
}
static void alingToLeftADC(void)
{
        ADMUX |=(1<<ADLAR);
}
static void setPreescaler(void)
{
        ADCSRA |= (1<<ADPS2)|(1<<ADPS0);
        ADCSRA &= ~(1<<ADPS1);
}
static void enableADC(void)
{
        ADCSRA |= 1 << ADEN;
}
void initDriverAdc(void)
{
	setRefADC();
	alingToLeftADC();
	setPreescaler();
	enableADC();
}

static void selectChannelCero(void)
{
	ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
}
static void startConversion(void)
{
	ADCSRA |= 1<<ADSC;
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA |= 1 << ADIF;
}
uint8_t getAdc(ADC_CHANNEL channel)
{
	selectChannelCero();
	startConversion();
	return ADCH;
}
