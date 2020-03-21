#include "unity.h"

#include "pedals.h"
#include "mock_driverADC.h"

void setUp(void)
{
	initDriverAdc_Expect();
	pedalsCreate();
}

void tearDown(void)
{
	closeDriverAdc_Ignore();
	pedalsDestroy();
}

void test_init_pedals(void)
{
	initDriverAdc_Expect();
	pedalsCreate();
}

void test_destroy_pedals(void)
{
	closeDriverAdc_Expect();
	pedalsDestroy();

}

void test_get_trhottle_value(void)
{
	int actualValueFromThrottle = 127;
	getAdc_ExpectAndReturn(THROTTLE, actualValueFromThrottle);
	TEST_ASSERT_EQUAL(actualValueFromThrottle, getPedalValue(PEDAL_THROTTLE));

	actualValueFromThrottle = 14;
	getAdc_ExpectAndReturn(THROTTLE, actualValueFromThrottle);
	TEST_ASSERT_EQUAL(actualValueFromThrottle, getPedalValue(PEDAL_THROTTLE));
}

void test_get_brake_value(void)
{
	int actualValueFromBrake = 127;
	getAdc_ExpectAndReturn(BRAKE, actualValueFromBrake);
	TEST_ASSERT_EQUAL(actualValueFromBrake, getPedalValue(PEDAL_BRAKE));
}
