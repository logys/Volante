#include "unity.h"

#include "steering.h"
#include "stub_adc.h"
#include "driverADC.h"

void setUp(void)
{
	initSteering();
}

void tearDown(void)
{
	closeSteering();
}

void test_get_value(void)
{
	ADCH = 200;
	ADCSRA |= (1<<ADIF);
	TEST_ASSERT_EQUAL(ADCH, getSteeringValue());
}
