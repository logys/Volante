#include "unity.h"

#include "driverADC.h"

void setUp(void)
{
	ADCSRA = 0;
	ADMUX = 0x00;
	initDriverAdc();
}

void tearDown(void)
{
}

void test_disable_adc(void)
{
	ADCSRA = 0xFF;
	closeDriverAdc();
	TEST_ASSERT_BITS(0x80, 0, ADCSRA);
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
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(STEERING);
	TEST_ASSERT_BITS(1<<ADSC, 1<<ADSC, ADCSRA); //inited conversion
}
void test_on_request_check_steering_channel_to_cero(void)
{
	ADMUX = 0xFF;
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(STEERING);
	TEST_ASSERT_BITS(0x0F, 0x00, ADMUX);
}
void test_on_request_check_throttle_channel_to_one(void)
{
	ADMUX = 0xFF;
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(THROTTLE);
	TEST_ASSERT_BITS(0x0F, 0x01, ADMUX);
}
void test_on_request_check_brake_channel_to_two(void)
{
	ADMUX = 0xFF;
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(BRAKE);
	TEST_ASSERT_BITS(0x0F, 0x02, ADMUX);
}
void test_ref_vcc_on_steering(void)
{
	ADMUX = 0x00;
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(STEERING);
	TEST_ASSERT_BITS(0xC0, 0x40, ADMUX);
}
void test_ref_one_dot_one_on_throttle(void)
{
	ADMUX = 0x00;
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(THROTTLE);
	TEST_ASSERT_BITS(0xC0, 0xF0, ADMUX);
}
void test_ref_one_dot_one_on_brake(void)
{
	ADMUX = 0x00;
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(BRAKE);
	TEST_ASSERT_BITS(0xC0, 0xF0, ADMUX);
}
void test_on_change_ref_voltaje_drop_first_conversion(void)
{
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(STEERING);

	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(STEERING);

}
void test_register_a_adc_channel(void)
{
	adcRegisterChannel(ADC0);
	ADCSRA |= (1<<ADIF); //finish conversion
	getAdc(THROTTLE);
	TEST_ASSERT_BITS(0x0F, 1, ADMUX);
}
