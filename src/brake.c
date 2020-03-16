#include "brake.h"

uint8_t getBrakeValue(void)
{
	return getAdc(BRAKE);
}
