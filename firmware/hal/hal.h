#ifndef __HAL_H__
#define __HAL_H__

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/can.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dac.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/usart.h>
#include "board.h"

#include "hal_uart.h"
#include "usr_uart.h"
#include "usr_blink.h"


#define irq_enable() 	__asm__ volatile("CPSIE  I":::"memory");
#define irq_disable() 	__asm__ volatile("CPSID  I":::"memory");
#define cang_abs(n)     ((n >= 0) ? n : -n)

void hal_initial(void);
void hal_delayus(uint16_t us);
void hal_delayms(uint16_t ms);
int _write(int file, char *ptr, int len);

#endif
