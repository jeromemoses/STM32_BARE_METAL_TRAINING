#include "stm32f0xx.h"

#define SYSTICK_LOAD_VALUE 8000
#define SYSTICK_ENABLE (1U<<0)
#define SYSTICK_CLOCK_SOURCE (1U<<2)
#define COUNT_FLAG (1U<<16)

void systickMS (int delay)
{
	//load the systick value for 1 nano second in SysTick->LOAD register
	SysTick->LOAD = SYSTICK_LOAD_VALUE;

	//clear the value the value inside sitick
	SysTick->VAL = 0;

	//Enable system clock in SysTick->CTRL (CVR) register // check CMSIS generic guide
	SysTick->CTRL |= SYSTICK_ENABLE;

	//enable processor clock
	SysTick->CTRL |= SYSTICK_CLOCK_SOURCE;

	for(int i = 0;i<delay;i++)
	{
		while((SysTick->CTRL & COUNT_FLAG) == 0);
	}

	//stop SysTick
	SysTick->CTRL = 0;
}
