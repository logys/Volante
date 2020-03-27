#include "steering.h"
static steering_driver steering;
void steeringCreate(void)
{
	steering = 0;
	steering = encoderCreate();
}
void steeringDestroy(steering_driver driver)
{
	if(!steering)
		return ;
	else if(steering->type == POTENTIOMETER)
		potentiometerDestroy(driver);
	else if(steering->type == ENCODER)
		encoderDestroy(driver);
	steering = NULL;
}
uint8_t steeringGetValue(void)
{
	if(steering->type == POTENTIOMETER)
		return getPotentiometerValue();
	else if(steering->type == ENCODER)
		return getEncoderValue();
	return 0;
}

void steeringAddDriver(steering_driver base)
{
	steeringDestroy(steering);
	steering = base;
}
