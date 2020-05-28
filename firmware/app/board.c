#include "board.h"

void board_initila(void){
    config_LD1(GPIO_MODE_OUTPUT);
	config_LD2(GPIO_MODE_OUTPUT);
    config_LD3(GPIO_MODE_OUTPUT);

    config_UART3_TX_af(GPIO_AF7,GPIO_PUPD_NONE,GPIO_OTYPE_PP,GPIO_OSPEED_25MHZ);
    config_UART3_RX_af(GPIO_AF7,GPIO_PUPD_NONE,GPIO_OTYPE_PP,GPIO_OSPEED_25MHZ);




    // config_xGPIO_OTYPE_PP, GPIO_OSPEED_25MHZ


    // config_UART3_TX(GPIO_MODE_AF,7);
    // config_UART3_RX(GPIO_MODE_INPUT,7);

    // rcc_periph_clock_enable(RCC_GPIOD);

    // gpio_mode_setup(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE,GPIO9);
    // gpio_set_af(GPIOD, GPIO_AF7, GPIO9);
    // gpio_set_output_options(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ,GPIO9);    

    // gpio_mode_setup(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE,GPIO8);
    // gpio_set_af(GPIOD, GPIO_AF7, GPIO8);
}