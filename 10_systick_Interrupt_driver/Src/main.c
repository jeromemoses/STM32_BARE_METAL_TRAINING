#include "stm32f0xx.h"
#include "stm32f091xc.h"
#include <stdint.h>
#include <stdio.h>
#include <exti.h>

#define PR13 	(1U<<13)

#define LED (1U<<5);

long int counterV = 0;

int main(void)
{

	//initialize uart
	uart_init();

	//initialize systick interrupt
	systick_interrupt_init();

	while(1)
	{

	}
}

static void systick_callback (void)
{
	GPIOA->ODR ^= LED;
}

void SysTick_Handler(void)
{
	//do anything you want call back function
	systick_callback();
}
