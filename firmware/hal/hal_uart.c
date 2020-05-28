#include "hal_uart.h"
#include "los_hwi.h"
#include "los_config.h"
#include "los_task.h"
#include "los_queue.h"


UINT32	uart_tx_fifoid,uart_rx_fifoid;

static void usart3_interrupt(void)
{
	if(usart_get_flag(USART3,USART_FLAG_RXNE)){
		uint8_t _data = usart_recv(USART3);
		LOS_QueueWrite(uart_rx_fifoid, &_data, 1, LOS_NO_WAIT);		//中断里面不能等
	}

	if(usart_get_flag(USART3,USART_FLAG_TXE)){
		uint8_t _data;
		if(LOS_QueueRead(uart_tx_fifoid,&_data,1,LOS_NO_WAIT) == LOS_OK){
			usart_send(USART3,_data);
		}	
		else{
			usart_disable_tx_interrupt(USART3);
		}
	}
}

uint32_t hal_uart_read(void* dat,uint16_t len,uint32_t timeout){
	for(uint16_t i = 0;i < len; i ++){
		if(LOS_OK != LOS_QueueRead(uart_rx_fifoid,dat + i,1,timeout))	return i;
	}
	return len;
}

uint32_t hal_uart_write(void* dat,uint16_t len,uint32_t timeout){
	for (uint16_t i = 0; i < len; i++){
		if(LOS_OK != LOS_QueueWrite(uart_tx_fifoid,dat + i,1,timeout)){
			if(i != 0)	usart_enable_tx_interrupt(USART3);			//表示有数据写入
			return i;
		}
	}
	usart_enable_tx_interrupt(USART3);
	return len;
}

void hal_uart_initial(void){
    rcc_periph_clock_enable(RCC_USART3);
	LOS_HwiCreate(NVIC_USART3_IRQ,	5,	1,	usart3_interrupt,	0);

    usart_set_baudrate(USART3, 115200);
	usart_set_databits(USART3, 8);
	usart_set_stopbits(USART3, USART_STOPBITS_1);
	usart_set_mode(USART3, USART_MODE_TX_RX);
	usart_set_parity(USART3, USART_PARITY_NONE);
	usart_set_flow_control(USART3, USART_FLOWCONTROL_NONE);

	usart_enable_rx_interrupt(USART3);
	usart_enable(USART3);

	LOS_QueueCreate("setx",	256,	&uart_tx_fifoid ,	0,	1);
	LOS_QueueCreate("serx",	64,	&uart_rx_fifoid ,	0,	1);
}

// vmt hal_uart = {hal_uart_read,	hal_uart_read};



	// /* Check if we were called because of RXNE. */
	// if (((USART_CR1(USART2) & USART_CR1_RXNEIE) != 0) &&
	//     ((USART_SR(USART2) & USART_SR_RXNE) != 0)) {

	// 	/* Indicate that we got data. */
	// 	gpio_toggle(GPIOD, GPIO12);

	// 	/* Retrieve the data from the peripheral. */
	// 	data = usart_recv(USART2);

	// 	/* Enable transmit interrupt so it sends back the data. */
	// 	usart_enable_tx_interrupt(USART2);
	// }

	// /* Check if we were called because of TXE. */
	// if (((USART_CR1(USART2) & USART_CR1_TXEIE) != 0) &&
	//     ((USART_SR(USART2) & USART_SR_TXE) != 0)) {

	// 	/* Put data into the transmit register. */
	// 	usart_send(USART2, data);

	// 	/* Disable the TXE interrupt as we don't need it anymore. */
	// 	usart_disable_tx_interrupt(USART2);
	// }