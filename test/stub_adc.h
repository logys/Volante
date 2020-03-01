#ifndef STUB_ADC_H
#define STUB_ADC_H

#include<stdint.h>
uint8_t ADMUX;
#define MUX0 0
#define MUX1 1
#define MUX2 2
#define MUX3 3
#define ADLAR 5
#define REFS0 6
#define REFS1 7

uint8_t ADCSRA;
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE 3
#define ADIF 4
#define ADATE 5
#define ADSC 6
#define ADEN 7

uint8_t ADCH;


#endif
