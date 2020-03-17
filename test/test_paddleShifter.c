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
	TEST_ASSERT_BITS(0x3, 0, DDRB);
	TEST_ASSERT_BITS(0x3, 0x3, PORTB);
}

void test_get_cero_when_no_push(void)
{
	PINB = 0x3;
	TEST_ASSERT_BITS(0x3, 0, getPaddleShifter());
}
void test_get_1_when_push_PB0(void)
{
	PINB = 0x2;
	TEST_ASSERT_BITS(0x3, 1, getPaddleShifter());
}
void test_get_2_when_push_PB1(void)
{
	PINB = 0x1;
	TEST_ASSERT_BITS(0x3, 2, getPaddleShifter());
}
