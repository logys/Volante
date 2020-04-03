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
static uint8_t getPotentiometerValue(steering_driver driver)
{
	return getAdc(STEERING);
}
static steering_driver_interface_struct potentiometer_interface = {
	.steeringGetValue = getPotentiometerValue
};
void potentiometerInstallInterface(void)
{
	steeringDriver_setInterface(&potentiometer_interface);
}
