#include <libopencm3/stm32/rcc.h>
#include "usb.h"
#include "led.h"

int main(void)
{
	rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_48MHZ]);
	led_init();
	usb_init();

	while (1) {
		usb_poll();
		led_blink();
	}

	return 0;
}
