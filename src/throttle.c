#include "throttle.h"

void initThrottle(void)
{
	initDriverAdc();
}

uint8_t getThrottleValue(void)
{
	return getAdc(THROTTLE);
}
