#include <nrf_drv_spi.h>
#include "dwm1001.h"

const nrf_drv_spi_t spi_dev = NRF_DRV_SPI_INSTANCE(0);
void spi_init(void) {
	uint32_t err_code;

	nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;

	spi_config.sck_pin = DW_SPI_CLK;
	spi_config.miso_pin = DW_SPI_MISO;
	spi_config.mosi_pin = DW_SPI_MOSI;
	spi_config.ss_pin = DW_SPI_CS;

	err_code = nrf_drv_spi_init(&spi_dev, &spi_config, NULL, NULL);
	APP_ERROR_CHECK(err_code);
}

