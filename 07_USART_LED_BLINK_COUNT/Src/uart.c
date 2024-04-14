#include "stm32f0xx.h"
#include "stm32f091xc.h"
#include <stdbool.h>

#define GPIOAEN 	(1U<<17)
#define GPIOCEN 	(1U<<19)
#define LED 		(1U<<5)
#define BUTTON 		(1U<<13)
#define USART2EN 	(1U<<17)
#define periphCLK 	8000000
#define BAUDRATE 	115200
#define TE			(1U<<3)
#define RE			(1U<<2)
#define UE			(1U<<0)
#define OVER8 		(1U<<15)
#define TXE			(1U<<7)
#define RXNE		(1U<<5)

int blink_flag = 0;

void uart_init(void)
{
	//set clock to GPIO A port
		RCC->AHBENR |= GPIOAEN;

		//setting PA2 (UART TX pins) as for alternative function for UART pin
		GPIOA->MODER |= (1U<<5);
		GPIOA->MODER &= ~(1U<<4);

		//setting PA3 (UART RX pins) as for alternative function for UART pin
		GPIOA->MODER |= (1U<<7);
		GPIOA->MODER &= ~(1U<<6);

		//Setting GPIOA - Pin 5 as a output with moder Register
		GPIOA->MODER |= (1U << 10);
		GPIOA->MODER &= ~(1U << 11);

		//Setting PA2 as UART2 TX
		GPIOA->AFR[0] &= ~(1U<<11);
		GPIOA->AFR[0] &= ~(1U<<10);
		GPIOA->AFR[0] &= ~(1U<<9);
		GPIOA->AFR[0] |= (1U<<8);

		//Setting PA3 as UART2 RX
		GPIOA->AFR[0] &= ~(1U<<15);
		GPIOA->AFR[0] &= ~(1U<<14);
		GPIOA->AFR[0] &= ~(1U<<13);
		GPIOA->AFR[0] |= (1U<<12);

		//setting clock to Advanced peripheral bus for USART
		RCC->APB1ENR |= USART2EN;

		/*
		 * baudrate = Fclk / USARTDIV
		 *
		 * */

		//sets the baud rate
		USART2->BRR |= (periphCLK / BAUDRATE);//(periphCLK + (BAUDRATE/2)) / BAUDRATE;

		//Enable transmitter
		USART2->CR1 |= TE;

		//Enable receiver
		USART2->CR1 |= RE;

		//Enable the USART2
		USART2->CR1 |= UE;
}

void uart_write(int ch)
{
	//waits until the TXE becomes 1
	while ((USART2->ISR & TXE) == 0);

	USART2->TDR = (ch & 0xff);
}

int uart_read(void)
{
	//waits until the RXNE becomes 1
	while((USART2->ISR & RXNE) == 0);
	blink_flag = 1;
	return USART2->RDR;
}

bool can_blink(void)
{
	return blink_flag;
}
