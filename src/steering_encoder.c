#include "steering_encoder.h"
typedef struct encoder_steering_struct * encoder_driver;
typedef struct encoder_steering_struct{
	steering_driver_struct base;
}encoder_steering_struct;

steering_driver encoderCreate(void)
{
	initDriverEncoder();
	encoder_driver driver = calloc(1, sizeof(struct encoder_steering_struct));
	driver->base.type = ENCODER;
	return (steering_driver)driver;
}

void encoderDestroy(steering_driver driver)
{
	if(!driver)
		return ;
	encoder_driver self = (encoder_driver) driver;
	free(self);
	closeDriverEncoder();
}

uint8_t getEncoderValue(void )
{
	int value ;
	value = 127 + ENCODER_GAIN*getValue();
	if(value > 255)
		value = 255;
	else if(value < 0)
		value = 0;
	return value;
}
