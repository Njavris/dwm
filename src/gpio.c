#include <gpio.h>
#include <nrf_delay.h>
#include "dwm1001.h"

static uint32_t tick = 0;

void leds_show_tick(void) {
	uint32_t leds[] = LEDS;
	int nm = sizeof(leds) / sizeof(uint32_t);
	int i = tick < (nm * 2) ? tick % nm : nm - 1 - (tick % nm);
	uint32_t val = (tick / 4) % 2;

	nrf_gpio_pin_write(leds[i], val);
	nrf_delay_ms(50);

	tick ++;
	tick %= nm * 4; 
}

void gpio_init(void) {
	int i;
	uint32_t leds[] = LEDS;
	uint32_t btns[] = BTNS;
	for (i = 0; i < sizeof(leds)/sizeof(uint32_t); i++)
		nrf_gpio_cfg_output(leds[i]);
	for (i = 0; i < sizeof(btns)/sizeof(uint32_t); i++)
		nrf_gpio_cfg_input(btns[i], NRF_GPIO_PIN_NOPULL);
}
