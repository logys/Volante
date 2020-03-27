#include "driverADC.h"
static void setRefADCOne(void)
{
        ADMUX |= (1<<REFS1)|(1<<REFS0);
}
static void setRefADCFive(void)
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
	setRefADCFive();
	alingToLeftADC();
	setPreescaler();
	enableADC();
}

void closeDriverAdc(void)
{
	ADCSRA &= ~(1<<ADEN);
}
static void cleanMux(void)
{
	ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
}
static void selectChannel(ADC_CHANNEL channel)
{
	cleanMux();
	if(channel == STEERING){
		setRefADCFive();
		return ;
	}else if(channel == THROTTLE){
		ADMUX |= 1<<MUX0;
	}else if(channel == BRAKE){
		ADMUX |= 1<<MUX1;
	}
	setRefADCOne();
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
