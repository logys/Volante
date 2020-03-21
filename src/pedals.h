#ifndef PEDALS_H
#define PEDALS_H
#include<stdint.h>
#include"driverADC.h"

typedef enum {PEDAL_THROTTLE, PEDAL_BRAKE}PEDAL;

void pedalsCreate(void);
void pedalsDestroy(void);

uint8_t getPedalValue(PEDAL);

#endif // PEDALS_H
