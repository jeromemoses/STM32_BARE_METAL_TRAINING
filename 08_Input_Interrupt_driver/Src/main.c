#include "stm32f0xx.h"
#include "stm32f091xc.h"
#include <stdint.h>
#include <stdio.h>
#include <exti.h>

#define PR13 	(1U<<13)

#define LED (1U<<5);

int var = 0;

int main(void)
{
	uart_init();
	exti_pc13_init();

	long int counter = 0;
	while(1)
	{
		printf("count = %ld\r\n",counter++);
		for (var = 0; var < 54000; ++var);
	}
}

static void exti_callback (void)
{
	GPIOA->ODR ^= LED;
	printf("Interrupt occurred!\r\n");
	for(int i = 0;i<100000;i++);
}

void EXTI4_15_IRQHandler(void)
{
	if((EXTI->PR & PR13) != 0)
	{
		EXTI->PR |= PR13; //clearing pr 13

		/*do something*/
		exti_callback();
	}
}
