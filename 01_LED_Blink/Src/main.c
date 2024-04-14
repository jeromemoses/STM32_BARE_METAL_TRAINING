#include "stm32f0xx.h"
#include "stm32f091xc.h"

#define GPIOAEN (1U<<17)
#define LED (1U<<5)

int i=0,k=0;

int main(void)
{
	//Enable clock for gpio port A
	RCC->AHBENR |= GPIOAEN;

	//Set direction of the GPIO pin in 5th pin in port a with MODER register
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	while(1)
	{
		//uses ODR resiter to turn the pin HIGH and LOW
		GPIOA->ODR |= LED;

		for( i = 1;i<=500;i++)
		{
			for( k = 0; k<=500;k++);
		}
		//turns off the LED
		GPIOA->ODR &= ~LED;

		for( i = 1;i<=500;i++)
		{
			for( k = 0; k<=500;k++);
		}

	}
}
