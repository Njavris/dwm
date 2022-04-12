#include <nrf_drv_spi.h>
#include "dwm1001.h"
#include "log.h"

const nrf_drv_spi_t spi_dev = NRF_DRV_SPI_INSTANCE(0);

void spi_set_freq(int freq_kh) {
	LOG_INFO("%s: setting frequency %dkHz\n", __func__, freq_kh);
	if (freq_kh < 250) {
		NRF_SPI0->FREQUENCY = SPI_FREQUENCY_FREQUENCY_K125;
		LOG_DBG("%s: frequency: 125kHz\n", __func__);
	} else if (freq_kh < 500) {
		NRF_SPI0->FREQUENCY = SPI_FREQUENCY_FREQUENCY_K250;
		LOG_DBG("%s: frequency: 256kHz\n", __func__);
	} else if (freq_kh < 1000) {
		NRF_SPI0->FREQUENCY = SPI_FREQUENCY_FREQUENCY_K500;
		LOG_DBG("%s: frequency: 599kHz\n", __func__);
	} else if (freq_kh < 2000) {
		NRF_SPI0->FREQUENCY = SPI_FREQUENCY_FREQUENCY_M1;
		LOG_DBG("%s: frequency: 1MHz\n", __func__);
	} else if (freq_kh < 4000) {
		NRF_SPI0->FREQUENCY = SPI_FREQUENCY_FREQUENCY_M2;
		LOG_DBG("%s: frequency: 2MHz\n", __func__);
	} else if (freq_kh < 8000) {
		NRF_SPI0->FREQUENCY = SPI_FREQUENCY_FREQUENCY_M4;
		LOG_DBG("%s: frequency: 4MHz\n", __func__);
	} else {
		NRF_SPI0->FREQUENCY = SPI_FREQUENCY_FREQUENCY_M8;
		LOG_DBG("%s: frequency: 8MHz\n", __func__);
	}
}

void spi_init(void) {
	uint32_t err_code;

	nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;

	spi_config.sck_pin = DW_SPI_CLK;
	spi_config.miso_pin = DW_SPI_MISO;
	spi_config.mosi_pin = DW_SPI_MOSI;
	spi_config.ss_pin = DW_SPI_CS;

	err_code = nrf_drv_spi_init(&spi_dev, &spi_config, NULL, NULL);
	APP_ERROR_CHECK(err_code);
	spi_set_freq(2000);
}

