#include "unity.h"

#include "gamepad.h"
#include "mock_steering.h"

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
	getSteeringValue_ExpectAndReturn(data_from_steering);
	updateGamepad();
	TEST_ASSERT_EQUAL(data_from_steering, *getPointerToReport());
}