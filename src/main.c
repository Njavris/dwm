#include <nrf_gpio.h>
#include <nrf_delay.h>
#include "dwm1001.h"

static void leds_blink(void) {
	int i;
	uint32_t leds[] = LEDS;
	static uint32_t val = 0;
	val = !val;
	for (i = 0; i < sizeof(leds)/sizeof(uint32_t); i++) {
		nrf_gpio_pin_write(leds[i], val);
		nrf_delay_ms(200);
	}
}

static void gpio_init(void) {
	int i;
	uint32_t leds[] = LEDS;
	uint32_t btns[] = BTNS;
	for (i = 0; i < sizeof(leds)/sizeof(uint32_t); i++)
		nrf_gpio_cfg_output(leds[i]);
	for (i = 0; i < sizeof(btns)/sizeof(uint32_t); i++)
		nrf_gpio_cfg_input(btns[i], NRF_GPIO_PIN_NOPULL); // Pull up resistor is on board
}

int main(void)
{
	gpio_init();

	while (true) {
		if (!nrf_gpio_pin_read(BT_WAKE))
			leds_blink();
	}
}
