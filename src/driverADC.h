#ifndef DRIVERADC_H
#define DRIVERADC_H
#ifndef TEST
	#include<avr/io.h>
#else
	#include<stub_adc.h>
#endif
typedef enum adc_channel{STEERING}ADC_CHANNEL;
void initDriverAdc(void);
uint8_t getAdc(ADC_CHANNEL);


#endif // DRIVERADC_H
