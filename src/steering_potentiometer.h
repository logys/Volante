#ifndef STEERING_POTENTIOMETER_H
#define STEERING_POTENTIOMETER_H

#include<stdint.h>
#include"steering.h"
#include"driverADC.h"
steering_driver potentiometerCreate(void);
void potentiometerDestroy(steering_driver);
uint8_t getPotentiometerValue();

#endif // STEERING_H
