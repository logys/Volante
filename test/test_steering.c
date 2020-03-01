#include "unity.h"

#include "steering.h"
#include "stub_adc.h"

void setUp(void)
{
	initSteering();
}

void tearDown(void)
{
	closeSteering();
}

void test_init_adc_ref_Vcc(void)
{
	ADMUX = 0;
	initSteering();
	TEST_ASSERT_BITS(0xC0,0x41, ADMUX);
}

void test_init_left_adjust(void)
{
	ADMUX = 0;
	initSteering();
	TEST_ASSERT_BITS(0x20, 0x20, ADMUX);
}

void test_init_select_channel_0(void)
{
	ADMUX = 0xFF;
	initSteering();
	TEST_ASSERT_BITS(0x0F, 0x00, ADMUX);
}

void test_init_enable_ADC(void)
{
	ADCSRA = 0;
	initSteering();
	TEST_ASSERT_BITS(0x80, 0x80, ADCSRA);
}

void test_preescaler_thirty_two(void)
{
	ADCSRA = 0xFF;
	initSteering();
	TEST_ASSERT_BITS(0x07, 0x05, ADCSRA);
}

void test_get_value(void)
{
	ADCSRA = 0;
	ADCH = 200;
	ADCSRA |= (1<<ADIF);
	TEST_ASSERT_EQUAL(ADCH, getSteeringValue());
	TEST_ASSERT_BITS(1<<ADIF, 1<<ADIF, ADCSRA);
	TEST_ASSERT_BITS(1<<ADSC, 1<<ADSC, ADCSRA);
}
