#ifndef DRIVER_ENCODER_H
#define DRIVER_ENCODER_H
#ifdef TEST
	#include"stub_portb.h"
	#include"stub_pcint0.h"
#else 
	#include"avr/io.h"
	#include"avr/interrupt.h"
#endif
void initDriverEncoder(void);
void closeDriverEncoder(void);

int8_t getValue(void);


#endif // DRIVER_ENCODER_H
