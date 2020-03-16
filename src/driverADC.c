#include "driverADC.h"
static void setRefADCOne(void)
{
        ADMUX |= (1<<REFS1)|(1<<REFS0);
}
static void setRefADCFive(void)
{
        ADMUX |= (1<<REFS1);
        ADMUX &= ~(1<<REFS0);
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
	setRefADCFive();
	alingToLeftADC();
	setPreescaler();
	enableADC();
}

static void selectChannel(ADC_CHANNEL channel)
{
	if(channel == STEERING){
		setRefADCFive();
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
	}
	else if(channel == THROTTLE){
		setRefADCOne();
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(0<<MUX0));
		ADMUX |= 1<<MUX0;
	}else if(channel == BRAKE){
		setRefADCOne();
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(0<<MUX1)|(0<<MUX0));
		ADMUX |= 1<<MUX1;
	}
}
static void startConversion(void)
{
	ADCSRA |= 1<<ADSC;
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA |= 1 << ADIF;
}
uint8_t getAdc(ADC_CHANNEL channel)
{
	selectChannel(channel);
	startConversion();
	return ADCH;
}
void adcRegisterChannel(short channel)
{
}
