#include "hal.h"

void hal_delayms(uint16_t ms)
{
	for(;ms > 0;ms --)
		for(uint32_t i = 129000;i > 0;i --)
			__asm__("nop");
}

void hal_delayus(uint16_t us)
{
	uint8_t i;
	for(;us > 0;us --)
		for(i = 9;i > 0;i --)
			__asm__("nop");
}

static void hal_clock_initial(void)
{
	rcc_clock_setup_hsi(&rcc_3v3[RCC_CLOCK_3V3_216MHZ]);	//for py board
}

void hal_initial(void)
{
	hal_clock_initial();
	board_initila();
}

int _write(int file, char *ptr, int len)
{
	int c = len;

	if (file == STDOUT_FILENO || file == STDERR_FILENO) {
		for(int i = 0;i < len;i ++)
			usart_send_blocking(USART3,ptr[i]);

		return c;
	}
	errno = EIO;
	return -1;
}
