#include "unity.h"

#include "steering_encoder.h"
#include "mock_driver_encoder.h"

steering_driver steering;
void setUp(void)
{
	initDriverEncoder_Expect();
	steering = encoderCreate();
}

void tearDown(void)
{
	closeDriverEncoder_Ignore();
	
	encoderDestroy(steering);
	steering = NULL;
}

void test_new_object(void)
{
	TEST_ASSERT_EQUAL(ENCODER, steering->type);
}

void test_destroy(void)
{
	closeDriverEncoder_Expect();
	encoderDestroy(steering);
	steering = NULL;
	TEST_ASSERT_EQUAL(NULL, steering);
}

void test_get_value(void)
{
	int value_from_encoder = 0;
	getValue_ExpectAndReturn(value_from_encoder);
	TEST_ASSERT_EQUAL(127 + ENCODER_GAIN*value_from_encoder, getEncoderValue());

	value_from_encoder = - 5;
	getValue_ExpectAndReturn(value_from_encoder);
	TEST_ASSERT_EQUAL(127 + ENCODER_GAIN*value_from_encoder, getEncoderValue());

	value_from_encoder = 5;
	getValue_ExpectAndReturn(value_from_encoder);
	TEST_ASSERT_EQUAL(127 + ENCODER_GAIN*value_from_encoder, getEncoderValue());
}

void test_bounded_values(void)
{
	int value_from_encoder = 128;
	getValue_ExpectAndReturn(value_from_encoder);
	TEST_ASSERT_EQUAL(255, getEncoderValue());

	value_from_encoder = -127;
	getValue_ExpectAndReturn(value_from_encoder);
	TEST_ASSERT_EQUAL(0, getEncoderValue());
}
