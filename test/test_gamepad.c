#include "unity.h"

#include "gamepad.h"
#include "mock_steering.h"
#include "mock_throttle.h"
#include "mock_brake.h"

void setUp(void)
{
	initSteering_Expect();
	initGamepad();
}

void tearDown(void)
{
	closeSteering_Ignore();
	closeGamepad();
}

void test_initGamepad(void)
{
	initSteering_Expect();
	initGamepad();
}

void test_closeGamepad(void)
{
	closeSteering_Expect();
	closeGamepad();
}

void test_get_array_pointer(void)
{
	TEST_ASSERT_EQUAL(0, *getPointerToReport());
}

void test_store_steering_to_byte_cero_of_report(void)
{
	unsigned short data_from_steering = 255;
	unsigned short data_from_throttle = 200;
	unsigned short data_from_brake = 190;
	getSteeringValue_ExpectAndReturn(data_from_steering);
	getThrottleValue_ExpectAndReturn(data_from_throttle);
	getBrakeValue_ExpectAndReturn(data_from_brake);
	updateGamepad();
	TEST_ASSERT_EQUAL(data_from_steering, *(getPointerToReport()+0));
	TEST_ASSERT_EQUAL(data_from_throttle, *(getPointerToReport()+1));
	TEST_ASSERT_EQUAL(data_from_brake, *(getPointerToReport()+2));
}
