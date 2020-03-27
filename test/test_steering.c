#include "unity.h"

#include "steering.h"
#include "mock_steering_potentiometer.h"
#include "mock_steering_encoder.h"

static steering_driver steering;

void setUp(void)
{
	steering = calloc(1, sizeof(struct steering_driver_struct));
	encoderCreate_ExpectAndReturn(NULL);
	steeringCreate();
}

void tearDown(void)
{
	potentiometerDestroy_Ignore();
	encoderDestroy_Ignore();
	steeringDestroy(steering);
}

void test_get_value_from_potentiometer(void)
{
	int value_from_potentiomer = 200;
	steering->type = POTENTIOMETER;
	steeringAddDriver(steering);
	getPotentiometerValue_ExpectAndReturn(value_from_potentiomer);
	TEST_ASSERT_EQUAL(value_from_potentiomer, steeringGetValue());
}
void test_get_value_from_encoder(void)
{
	int value_from_encoder = 100;
	steering->type = ENCODER;
	steeringAddDriver(steering);
	getEncoderValue_ExpectAndReturn(value_from_encoder);
	TEST_ASSERT_EQUAL(value_from_encoder, steeringGetValue());
}
void test_addDriver_destroy_previous(void)
{
	steering_driver otro = calloc(1, sizeof(struct steering_driver_struct));
	steeringAddDriver(otro);
}
