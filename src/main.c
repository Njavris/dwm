#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <nrf_delay.h>
#include <nrf.h>

#include "uart.h"
#include "spi.h"
#include "gpio.h"
#include "dwm1001.h"

static void dw_reset(uint32_t reset) {
	if (reset) {
		nrf_gpio_cfg_output(DW_NRST);
		nrf_gpio_pin_write(DW_NRST, !reset);
	} else {
		/* HI-Z */
		nrf_gpio_cfg_input(DW_NRST, NRF_GPIO_PIN_NOPULL);
	}
}

int main(void) {
	gpio_init();
	uart_init();
	spi_init();
	dw_reset(0);

	printf("\nHello!\n");

	uint8_t cmd = 0;
	uint8_t id[4];
	memset(id, 0, sizeof(id));
	nrf_drv_spi_transfer(&spi_dev, &cmd, 1, id, 4);
	printf("DEV_ID=%08x\n", *((unsigned *)id));

	while (true) {
		if (nrf_gpio_pin_read(BT_WAKE))
			leds_show_tick();
	}
}
