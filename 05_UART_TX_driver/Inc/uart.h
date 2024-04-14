/*
 * uart.h
 *
 *  Created on: Apr 14, 2024
 *      Author: jerom
 */

#ifndef UART_H_
#define UART_H_

void uart_init(void);
void uart_write(int ch);
#define LED (1U<<5);


#endif /* UART_H_ */
