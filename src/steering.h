#ifndef STEERING_H
#define STEERING_H
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include"steering_driver.h"
#include"steering_potentiometer.h"
#include"steering_encoder.h"
void steeringCreate(void);
void steeringDestroy(steering_driver);
uint8_t steeringGetValue(void);
void steeringAddDriver(steering_driver);
#endif // STEERING_H
