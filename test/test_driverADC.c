#include "unity.h"

#include "driverADC.h"

void setUp(void)
{
	initDriverAdc();
}

void tearDown(void)
{
}

void test_init_left_adjust(void)
{
        ADMUX = 0;
        initDriverAdc();
        TEST_ASSERT_BITS(0x20, 0x20, ADMUX);
}
void test_preescaler(void)
{
        ADCSRA = 0xFF;
	initDriverAdc();
        TEST_ASSERT_BITS(0x07, 0x05, ADCSRA);
}
void test_init_enable_ADC(void)
{
        ADCSRA = 0;
        initDriverAdc();
        TEST_ASSERT_BITS(0x80, 0x80, ADCSRA);
}
void test_on_request_value_check_star_conversion(void)
{
	ADCSRA = 0xFF;
	ADCSRA &= ~(1<<ADSC);
	getAdc(STEERING);
	TEST_ASSERT_BITS(1<<ADSC, 1<<ADSC, ADCSRA);
}
void test_on_request_check_steering_channel_to_cero(void)
{
	ADMUX = 0xFF;
	getAdc(STEERING);
	TEST_ASSERT_BITS(0x0F, 0x00, ADMUX);
}
void test_register_a_adc_channel(void)
{
	adcRegisterChannel(ADC0);
	getAdc(THROTTLE);
	TEST_ASSERT_BITS(0x0F, 1, ADMUX);
}
