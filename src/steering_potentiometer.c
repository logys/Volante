#include "steering_potentiometer.h"
typedef struct potentiometer_steering_driver_struct * potentiometer_driver;
typedef struct potentiometer_steering_driver_struct{
	steering_driver_struct base;
}potentiometer_steering_driver_struct;

steering_driver potentiometerCreate(void)
{
	initDriverAdc();
	potentiometer_driver self = calloc(1, sizeof (struct potentiometer_steering_driver_struct));
	self->base.type = POTENTIOMETER;
	return (steering_driver)self;
}

void potentiometerDestroy(steering_driver driver)
{
	if(!driver)
		return ;
	potentiometer_driver self =(potentiometer_driver) driver;
	free(self);
}
#define DEADZONE 30
uint8_t getPotentiometerValue()
{
	return getAdc(STEERING);
//	if(ADCH > 126 && ADCH < (126+DEADZONE))
//		return ADCH+DEADZONE;
//	else
//		return ADCH - DEADZONE;
}
