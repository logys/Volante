#ifndef STEERING_ENCODER_H
#define STEERING_ENCODER_H
#include<stdint.h>
#include"steering_driver.h"
#include"driver_encoder.h"
#define ENCODER_GAIN 1
steering_driver encoderCreate(void);
void encoderDestroy(steering_driver);
uint8_t getEncoderValue(void);

#endif // STEERING_ENCODER_H
