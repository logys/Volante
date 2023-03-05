#include "led.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void led_init(void)
{
	rcc_periph_clock_enable(RCC_GPIOB);
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
}

void led_blink(void)
{
	static int i = 0;
	if(i < 800000)
		i++;
	else{
		gpio_toggle(GPIOB, GPIO12);
		i = 0;
	}
}
