#include "steering_driver.h"

static steering_driver_interface interface = NULL;

void steeringDriver_setInterface(steering_driver_interface i)
{
	interface = i;
}
uint8_t steeringGetValue(steering_driver driver)
{
	return interface->steeringGetValue(driver);
}
