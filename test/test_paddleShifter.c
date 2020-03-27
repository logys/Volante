#include "unity.h"

#include "paddleShifter.h"
#include "stub_portb.h"

void setUp(void)
{
	initPaddleShifter();
}

void tearDown(void)
{
}

void test_on_init_pinout_as_input_and_pullUp(void)
{
	DDRB = 0xFF;
	PORTB = 0;
	initPaddleShifter();
	TEST_ASSERT_BITS(0xC, 0, DDRB);
	TEST_ASSERT_BITS(0xC, 0xC, PORTB);
}

void test_get_cero_when_no_push(void)
{
	PINB = 0xC;
	TEST_ASSERT_BITS(0xC, 0, getPaddleShifter());
}
void test_get_1_when_push_PB2(void)
{
	PINB = 0x8;
	TEST_ASSERT_EQUAL( 1, getPaddleShifter());
}
void test_get_2_when_push_PB3(void)
{
	PINB = 0x4;
	TEST_ASSERT_EQUAL( 2, getPaddleShifter());
}
