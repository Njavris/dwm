#include <stdio.h>
#include <nrf_gpio.h>
#include <nrf_delay.h>

#include "nrf.h"
#include <app_uart.h>
#include <app_error.h>
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif

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
	nrf_gpio_cfg_output(DW_RST);
}

#define MAX_TEST_DATA_BYTES	(15U)
#define UART_TX_BUF_SIZE	256
#define UART_RX_BUF_SIZE	256

void uart_error_handle(app_uart_evt_t * p_event)
{
	if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR) {
		APP_ERROR_HANDLER(p_event->data.error_communication);
	} else if (p_event->evt_type == APP_UART_FIFO_ERROR) {
		APP_ERROR_HANDLER(p_event->data.error_code);
	}
}

void uart_init(void) {
	uint32_t err_code;
	const app_uart_comm_params_t comm_params = {
		.rx_pin_no = DWM_UART_RX,
		.tx_pin_no = DWM_UART_TX,
		.flow_control = 0,
		.use_parity = false,
#if defined (UART_PRESENT)
		.baud_rate = NRF_UART_BAUDRATE_115200
#else
		.baud_rate = NRF_UARTE_BAUDRATE_115200
#endif
	};

	APP_UART_FIFO_INIT(&comm_params,
                     UART_RX_BUF_SIZE,
                     UART_TX_BUF_SIZE,
                     uart_error_handle,
                     APP_IRQ_PRIORITY_LOWEST,
                     err_code);

APP_ERROR_CHECK(err_code);
}

int main(void) {
	gpio_init();
	uart_init();

	printf("\r\nHello!\r\n");
	while (true) {
		if (nrf_gpio_pin_read(BT_WAKE))
			leds_blink();
	}
}
