#include "stm32f0xx.h"
#include "stm32f091xc.h"

#define GPIOAEN (1U<<17)
#define LED (1U<<5)
int main(void)
{
	//Enable clock for gpio port A
	RCC->AHBENR |= GPIOAEN;

	//Set direction of the GPIO pin in 5th pin in port a with MODER resiter
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	while(1)
	{
		GPIOA->ODR ^= LED;

		//inserts few delay
		for(int i = 0;i<77000;i++);

	}
}
