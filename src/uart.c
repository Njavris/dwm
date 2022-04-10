#include <stdio.h>
#include <errno.h>
#include <nrf_drv_uart.h>
#include <app_uart.h>
#if defined (UART_PRESENT)
#include <nrf_uart.h>
#endif
#if defined (UARTE_PRESENT)
#include <nrf_uarte.h>
#endif

#include "dwm1001.h"

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

int _write(int fd, char *buf, int len){
	int cnt = 0;
	/* only stdout and stderr */
	if (fd != 1 && fd != 2) {
		errno = EBADF;
		return -errno;
	}

	for (; cnt < len; cnt++) {
		/* reset position on new line */
		if (buf[cnt] == '\n')
			app_uart_put('\r');
		app_uart_put(buf[cnt]);
	}
	return cnt;
}

int _read(int fd, char *buf, int len) {
	int cnt = 0;
	/* only stdeout */
	if (fd) {
		errno = EBADF;
		return -errno;
	}

	for (; cnt < len; cnt++) {
		uint8_t c;
        	while (app_uart_get(&c));
		/* echo */
		app_uart_put(c);
		buf[cnt] = c;
		if (c == '\0' || c == '\r' || c == '\n')
			break;
	}
	return ++cnt;
}
