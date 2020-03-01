#include "steering.h"
void initSteering(void)
{
	initDriverAdc();
}
void closeSteering(void)
{
}
#define DEADZONE 30
uint8_t getSteeringValue(void)
{
	return getAdc(STEERING);
//	if(ADCH > 126 && ADCH < (126+DEADZONE))
//		return ADCH+DEADZONE;
//	else
//		return ADCH - DEADZONE;
}
