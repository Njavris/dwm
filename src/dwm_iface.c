#include <string.h>
#include "spi.h"
#include "gpio.h"
#include "dwm1001.h"

#include "spi.h"
#include "log.h"
#include "deca_device_api.h"

static void dw_reset(uint32_t reset) {
	if (reset) {
		nrf_gpio_cfg_output(DW_NRST);
		nrf_gpio_pin_write(DW_NRST, !reset);
	} else {
		/* HI-Z */
		nrf_gpio_cfg_input(DW_NRST, NRF_GPIO_PIN_NOPULL);
	}
}

static uint32_t dwm_id(void) {
	uint8_t cmd = 0;
	uint8_t id[5];
	memset(id, 0, sizeof(id));
	nrf_drv_spi_transfer(&spi_dev, &cmd, 1, id, 5);
	return *(uint32_t *)(&id[1]);
}

void dwm_iface_init(void) {
	LOG_INFO("%s\n", __func__);

	gpio_init();
	spi_init();
	dw_reset(0);

	LOG_INFO("DWM_ID=%08lx\n", dwm_id());

}
