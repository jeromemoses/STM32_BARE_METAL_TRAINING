#include "stm32f0xx.h"
#include "stm32f091xc.h"
#include <stdbool.h>
#include "uart.h"

int chr;

int main(void) {

	uart_init();


	while(1)
	{

		chr = uart_read();
		uart_write(chr);

		if(chr == '1')
		{
			GPIOA->ODR |= LED;
		}
		else
		{
			GPIOA->ODR &= ~LED;
		}
	}
}
