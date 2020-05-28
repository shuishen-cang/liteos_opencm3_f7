#ifndef __HAL_UART_H__
#define __HAL_UART_H__

#include "hal.h"

void    hal_uart_initial(void);
uint32_t hal_uart_read(void* dat,uint16_t len,uint32_t timeout);
uint32_t hal_uart_write(void* dat,uint16_t len,uint32_t timeout);

#endif
