#include "unity.h"

#include "steering_driver.h"
#include "steering_potentiometer.h"
#include "mock_driverADC.h"

steering_driver steering;

void setUp(void)
{
	initDriverAdc_Ignore();
	steering = potentiometerCreate();
	potentiometerInstallInterface();

}

void tearDown(void)
{
}

void test_getValue(void)
{
	//TEST_ASSERT_EQUAL(200, steeringGetValue(steering));
}
