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
	uart_init();

	while(1)
	{
		printf("seconds : %ld \r\n",counterV++);
		systickMS(1000);
	}
}

