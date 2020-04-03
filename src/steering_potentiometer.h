#ifndef STEERING_POTENTIOMETER_H
#define STEERING_POTENTIOMETER_H

#include<stdint.h>
#include"steering_driver.h"
#include"driverADC.h"
steering_driver potentiometerCreate(void);
void potentiometerDestroy(steering_driver);
void potentiometerInstallInterface(void);

#endif // STEERING_POTENTIOMETER_H
