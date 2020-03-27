#ifndef STEERING_DRIVER_H
#define STEERING_DRIVER_H
typedef enum steering_type{POTENTIOMETER, ENCODER}STEERING_TYPE;
typedef struct steering_driver_struct * steering_driver;
typedef struct steering_driver_struct{
	STEERING_TYPE type;
}steering_driver_struct;
#endif // STEERING_DRIVER_H
