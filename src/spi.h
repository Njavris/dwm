#ifndef __SPI_H__
#define __SPI_H__
#include <nrf_drv_spi.h>

extern const nrf_drv_spi_t spi_dev;

void spi_set_freq(int freq_kh);
void spi_init(void);

#endif
