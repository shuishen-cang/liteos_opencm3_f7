#include "hal_uart.h"

void hal_uart_initial(void){
    rcc_periph_clock_enable(RCC_USART3);
	nvic_enable_irq(NVIC_USART3_IRQ);

    usart_set_baudrate(USART3, 115200);
	usart_set_databits(USART3, 8);
	usart_set_stopbits(USART3, USART_STOPBITS_1);
	usart_set_mode(USART3, USART_MODE_TX_RX);
	usart_set_parity(USART3, USART_PARITY_NONE);
	usart_set_flow_control(USART3, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable_rx_interrupt(USART3);
	usart_enable(USART3);
}


void usart3_isr(void)
{
	if(usart_get_flag(USART3,USART_FLAG_RXNE)){
		uint8_t data = usart_recv(USART3);

		usart_send_blocking(USART3,data);
	}
	else if(usart_get_flag(USART3,USART_FLAG_IDLE)){
		
	}

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
}