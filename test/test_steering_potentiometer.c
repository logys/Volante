#include "unity.h"

#include "steering_potentiometer.h"
#include "steering_driver.h"
#include "mock_driverADC.h"

steering_driver steering;
void setUp(void)
{
	initDriverAdc_Expect();
	steering = potentiometerCreate();
	potentiometerInstallInterface();
}
void tearDown(void)
{
	potentiometerDestroy(steering);
	steering = NULL;
}

void test_create_object(void)
{
	TEST_ASSERT_EQUAL(POTENTIOMETER, steering->type);
}
void test_free_object(void)
{
	potentiometerDestroy(steering);
	steering = NULL;
	TEST_ASSERT_EQUAL_PTR(NULL, steering);
}
void test_get_value(void)
{
	getAdc_ExpectAndReturn(STEERING, 100);
	TEST_ASSERT_EQUAL(100, steeringGetValue(steering));
}
