#include "pedals.h"

void pedalsCreate(void)
{
	initDriverAdc();
}
void pedalsDestroy(void)
{
	closeDriverAdc();
}

uint8_t getPedalValue(PEDAL pedal)
{
	if(pedal == PEDAL_THROTTLE)
		return getAdc(THROTTLE);
	else if(pedal == PEDAL_BRAKE)
		return getAdc(BRAKE);
}

