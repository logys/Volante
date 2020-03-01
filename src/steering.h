#ifndef STEERING_H
#define STEERING_H
#ifndef TEST
	#include<avr/io.h>
#else
	#include"stub_adc.h"
#endif

#include<stdint.h>
void initSteering(void);
void closeSteering(void);
uint8_t getSteeringValue(void);

#endif // STEERING_H
