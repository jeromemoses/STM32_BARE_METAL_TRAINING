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
#define UE			(1U<<0)
#define OVER8 		(1U<<15)
#define TXE			(1U<<7)

int main(void) {

	//set clock to GPIO A port
	RCC->AHBENR |= GPIOAEN;

	//setting PA2 (UART TX pins) as for alternative function for UART pin
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<4);

	//Setting GPIOA - Pin 5 as a output with moder Register
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	//Setting PA2 as UART2 TX
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] &= ~(1U<<10);
	GPIOA->AFR[0] &= ~(1U<<9);
	GPIOA->AFR[0] |= (1U<<8);

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

	//Enable the USART2
	USART2->CR1 |= UE;

	char string[50] = "Praise the lord\n";

	int j = 0;

	while (1)
	{
		while((USART2->ISR & TXE)==0){}
		USART2->TDR = (string[j++] & 0xff);

		for(int i=0;i<=75000;i++);
		GPIOA->ODR ^= LED;

		if(j>=17)j=0;
	}
}
