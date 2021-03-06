#include "unity.h"

#include "driver_encoder.h"
#include "stub_portb.h"
#include "stub_pcint0.h"

void setUp(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;
	PINB = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00;
	PIND = 0x00;

	PCICR = 0x00;
	PCMSK0 = 0x00;
	EICRA = 0x00;
	initDriverEncoder();
}

void tearDown(void)
{
	closeDriverEncoder();
}

void test_init_registers(void)
{
	TEST_ASSERT_BITS(1<<PB0, 0<<PB0, DDRB);
	TEST_ASSERT_BITS(1<<PD3, 0<<PD3, DDRD);
	TEST_ASSERT_BITS(1<<PB0, 1<<PB0, PORTB);
	TEST_ASSERT_BITS(1<<PD3, 1<<PD3, PORTD);
	TEST_ASSERT_BITS((1<<ISC11)|(1<<ISC10), (1<<ISC11)|(1<<ISC10), EICRA);
	TEST_ASSERT_BITS(1<<INT1, 1<<INT1, EIMSK);


}
void test_get_cero_from_center(void)
{
	PINB = 0;
	TEST_ASSERT_EQUAL(0, getValue());
}
#define A_HIGH (1<<PD3)
#define B_HIGH (1<<PB0)
void test_plus_value(void)
{
	PIND = A_HIGH;
	INT1_vect();
	TEST_ASSERT_EQUAL(1, getValue());

	PINB = B_HIGH;
	PIND = A_HIGH;
	INT1_vect();
	TEST_ASSERT_EQUAL(1, getValue());
}

void test_minus_value(void)
{
	PINB = B_HIGH;
	INT1_vect();
	TEST_ASSERT_EQUAL(0, getValue());

	PINB = B_HIGH;
	PIND = A_HIGH;
	INT1_vect();
	TEST_ASSERT_EQUAL(-1, getValue());
}
