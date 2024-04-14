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

int main(void)
{
	//Enable clock for gpio port A

	RCC->AHBENR |= GPIOAEN;
	RCC->AHBENR |= GPIOCEN;

	//Set direction of the GPIO pin in 5th pin in port a with MODER resiter
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	//setting the button pin as input
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	while(1)
	{
		bt_prvs_state = bt_cur_state;
		bt_cur_state = (GPIOC->IDR&=BUTTON);

		if(((GPIOC->IDR&=BUTTON) == 0) && (bt_prvs_state != bt_cur_state))
		{
			GPIOA->ODR ^= LED;
			counter += 1;
			Blink_flag = 1;
		}

		if(counter >= 11)
		{
			counter = 0;
		}


		if( Blink_flag == 1)
		{
			for(int j = 0; j <= counter*2;j++)
			{
				GPIOA->ODR ^= LED;
				for(int i = 0;i<=75000;i++);
			}
			Blink_flag = 0;
		}


	}
}
