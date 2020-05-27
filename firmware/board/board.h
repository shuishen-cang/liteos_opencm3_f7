#ifndef __BOARD_H__
#define __BOARD_H__

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
#include "usr_uart.h"

#define __PIN_FUNC_(name,PORT,PIN)                                              \
static inline void set_##name(uint8_t value){if(value)gpio_set(PORT,PIN);       \
                                else gpio_clear(PORT,PIN);}                     \
static inline uint8_t get_##name(void){if(gpio_get(PORT,PIN))return 1;return 0;}\
static inline void toggle_##name(void){gpio_toggle(PORT,PIN);}                  \
static inline void config_##name(uint8_t mode,uint8_t af_num){                  \
    rcc_periph_clock_enable(RCC_##PORT);                                        \
    gpio_mode_setup(PORT, mode, GPIO_PUPD_NONE, PIN);                           \
    if(mode == GPIO_MODE_OUTPUT)                                                \
        gpio_set_output_options(PORT, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ,PIN);    \
    else if(mode == GPIO_MODE_AF)                                               \
        gpio_set_af(PORT, af_num, PIN);                                         \
}

/*********************** led ************************/
__PIN_FUNC_(LD1,GPIOB,GPIO0)
__PIN_FUNC_(LD2,GPIOB,GPIO7)

/*********************** usart ************************/
__PIN_FUNC_(UART3_TX,GPIOD,GPIO9)
__PIN_FUNC_(UART3_RX,GPIOD,GPIO8)


void board_initila(void);


#endif