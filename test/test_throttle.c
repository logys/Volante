#include "unity.h"

#include "throttle.h"
#include "driverADC.h"
#include "stub_adc.h"

void setUp(void)
{
	initThrottle();
}

void tearDown(void)
{
}

void test_get_value_from_adc(void)
{
	ADCH = 100;
	ADCSRA |= 1 << ADIF;
	TEST_ASSERT_EQUAL(ADCH, getThrottleValue());

	ADCH = 150;
	ADCSRA |= 1 << ADIF;
	TEST_ASSERT_EQUAL(ADCH, getThrottleValue());
}

void test_check_mux_channel_1(void)
{
	getThrottleValue();
	TEST_ASSERT_BITS(0x0F, 0x01, ADMUX);
}
