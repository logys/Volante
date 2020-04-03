#ifndef STEERING_DRIVER_PRIVATE
#define STEERING_DRIVER_PRIVATE
typedef struct steering_driver_interface_struct{
	uint8_t (*steeringGetValue)(steering_driver);
}steering_driver_interface_struct;

#endif
