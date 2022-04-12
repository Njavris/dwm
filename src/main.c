#include <stdio.h>
#include <errno.h>
#include <nrf_delay.h>
#include <nrf.h>

#include "log.h"
#include "gpio.h"
#include "dwm_iface.h"
#include "dwm1001.h"

enum log_level curr_log_level = LOG_LEVEL_MAX;

int main(void) {
	uart_init();
	dwm_iface_init();

	while (true) {
		if (nrf_gpio_pin_read(BT_WAKE))
			leds_show_tick();
	}
}
