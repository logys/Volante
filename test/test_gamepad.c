#include "unity.h"

#include "gamepad.h"
#include "mock_steering.h"
#include "mock_pedals.h"
#include "mock_paddleShifter.h"

void setUp(void)
{
	steeringCreate_Expect();
	pedalsCreate_Expect();
	initPaddleShifter_Expect();
	initGamepad();
}

void tearDown(void)
{
	closeGamepad();
}

void test_initGamepad(void)
{
	steeringCreate_Expect();
	pedalsCreate_Expect();
	initPaddleShifter_Expect();
	initGamepad();
}

void test_closeGamepad(void)
{
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
	unsigned short data_from_paddleShifter = 2;
	steeringGetValue_ExpectAndReturn(data_from_steering);
	getPedalValue_ExpectAndReturn(PEDAL_THROTTLE, data_from_throttle);
	getPedalValue_ExpectAndReturn(PEDAL_BRAKE, data_from_brake);
	getPaddleShifter_ExpectAndReturn(data_from_paddleShifter);
	updateGamepad();
	TEST_ASSERT_EQUAL(data_from_steering, *(getPointerToReport()+0));
	TEST_ASSERT_EQUAL(data_from_throttle, *(getPointerToReport()+1));
	TEST_ASSERT_EQUAL(data_from_brake, *(getPointerToReport()+2));
	TEST_ASSERT_BITS(0x3, data_from_paddleShifter, *(getPointerToReport()+4));
}
