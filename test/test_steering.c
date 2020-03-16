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
static void setFlagADCconvertedFinished(void)
{
	ADCSRA |= (1<<ADIF);
}
void test_get_value(void)
{
	short value_from_ADC = 200;
	ADCH = value_from_ADC;
	setFlagADCconvertedFinished();
	TEST_ASSERT_EQUAL(value_from_ADC, getSteeringValue());
}
