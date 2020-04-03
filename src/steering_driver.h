#ifndef STEERING_DRIVER_H
#define STEERING_DRIVER_H
#include<stdlib.h>
#include<stdint.h>
typedef enum steering_type{POTENTIOMETER, ENCODER}STEERING_TYPE;
typedef struct steering_driver_interface_struct * steering_driver_interface;
typedef struct steering_driver_struct * steering_driver;
typedef struct steering_driver_struct{
	STEERING_TYPE type;
}steering_driver_struct;

void steeringDriver_setInterface(steering_driver_interface);
uint8_t steeringGetValue(steering_driver);

#include"steering_driver_private.h"

#endif // STEERING_DRIVER_H
