#include "stm32f0xx.h"
#include "stm32f091xc.h"
#include <stdbool.h>

#define GPIOAEN (1U<<17)
#define GPIOCEN (1U<<19)
#define LED (1U<<5)
#define BUTTON (1U<<13)

int bt_prvs_state = 1;
int bt_cur_state = 1;
int counter = 0;
bool Blink_flag = 0;

int main(void) {
	//enable the clock for the GPIO PORT that we are going to use
	RCC->AHBENR |= GPIOAEN;
	RCC->AHBENR |= GPIOCEN;

	//Setting up the OUTPUT and INPUT functionality for GPIOS

	//SETTING GPIOC - 13TH PIN AS A INPUT WITH MODER REGISTER
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

	//Setting GPIOA - Pin 5 as a output with moder Register
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while (1)
	{
		while ((GPIOC->IDR &= BUTTON) == 0)
		{
			GPIOA->ODR |= LED;
		}
		GPIOA->ODR &= ~LED;
	}
}
