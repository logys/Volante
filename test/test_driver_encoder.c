#include "unity.h"

#include "driver_encoder.h"
#include "stub_portb.h"
#include "stub_pcint0.h"

void setUp(void)
{
	DDRB = 0xFF;
	PORTB = 0xFF;
	PINB = 0x00;
	PCICR = 0x00;
	PCMSK0 = 0x00;
	initDriverEncoder();
}

void tearDown(void)
{
	closeDriverEncoder();
}

void test_init_registers(void)
{
	TEST_ASSERT_BITS(0x3, 0, DDRB);
	TEST_ASSERT_BITS(0x3, 0, PORTB);
	TEST_ASSERT_BITS(1<<PCIE0, 1<<PCIE0, PCICR);
	TEST_ASSERT_BITS(1<<PCINT0, 1<<PCINT0, PCMSK0);
}
void test_get_cero_from_center(void)
{
	PINB = 0;
	TEST_ASSERT_EQUAL(0, getValue());
}
#define A_HIGH (1<<PB0)
#define B_HIGH (1<<PB1)
#define AB_HIGH ((1<<PB1)|(1<<PB0))
void test_plus_value(void)
{
	PINB = A_HIGH;
	PCINT0_vect();
	TEST_ASSERT_EQUAL(1, getValue());

	PINB = AB_HIGH;
	PCINT0_vect();
	TEST_ASSERT_EQUAL(1, getValue());
}

void test_minus_value(void)
{
	PINB = B_HIGH;
	PCINT0_vect();
	TEST_ASSERT_EQUAL(0, getValue());

	PINB = AB_HIGH;
	PCINT0_vect();
	TEST_ASSERT_EQUAL(-1, getValue());
}
