#ifndef PADDLESHIFTER_H
#define PADDLESHIFTER_H
#include<stdint.h>
#ifndef TEST
	#include<avr/io.h>
#else
	#include"stub_portb.h"
#endif

uint8_t getPaddleShifter(void);
void initPaddleShifter(void);

#endif // PADDLESHIFTER_H
