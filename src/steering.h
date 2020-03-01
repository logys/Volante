#ifndef STEERING_H
#define STEERING_H

#include<stdint.h>
#include"driverADC.h"
void initSteering(void);
void closeSteering(void);
uint8_t getSteeringValue(void);

#endif // STEERING_H
