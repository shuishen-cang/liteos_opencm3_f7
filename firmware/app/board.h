#ifndef __BOARD_H__
#define __BOARD_H__

#include "hal.h"

/*********************************************************************
 * config_name:配置基本的输入输出或者模式方式
 * config_name_af:配置输入输出为af模式
 * 例如：
 *      config_LD1(GPIO_MODE_OUTPUT);
 *      config_UART3_RX_af(GPIO_AF7,GPIO_PUPD_NONE,GPIO_OTYPE_PP,GPIO_OSPEED_25MHZ);
 * ******************************************************************/
#define __PIN_FUNC_(name,PORT,PIN)                                              \
static inline void set_##name(void){gpio_set(PORT,PIN);}                        \
static inline void clr_##name(void){gpio_clear(PORT,PIN);}                      \
static inline void toggle_##name(void){gpio_toggle(PORT,PIN);}                  \
static inline uint8_t get_##name(void){if(gpio_get(PORT,PIN))return 1;return 0;}\
static inline void config_##name(uint8_t mode){                                 \
    rcc_periph_clock_enable(RCC_##PORT);                                        \
    gpio_mode_setup(PORT, mode, GPIO_PUPD_NONE, PIN);                           \
    gpio_set_output_options(PORT, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ,PIN);        \
}                                                                               \
static inline void config_##name##_af(  uint8_t af,uint8_t pupd,                \
                                        uint8_t otype,uint8_t ospeed){          \
    rcc_periph_clock_enable(RCC_##PORT);                                        \
    gpio_mode_setup(PORT, GPIO_MODE_AF, pupd, PIN);                             \
    gpio_set_af(PORT, af, PIN);                                                 \
    gpio_set_output_options(PORT, otype, ospeed,PIN);                           \
}




/*********************** led ************************/
__PIN_FUNC_(LD1,GPIOB,GPIO0)
__PIN_FUNC_(LD2,GPIOB,GPIO7)
__PIN_FUNC_(LD3,GPIOB,GPIO14)

/*********************** usart ************************/
__PIN_FUNC_(UART3_TX,GPIOD,GPIO9)
__PIN_FUNC_(UART3_RX,GPIOD,GPIO8)


void board_initila(void);


#endif