#include "stm32f0xx.h"
#include "stm32f091xc.h"
#include <stdbool.h>
#include "uart.h"

int main(void) {

	uart_init();
	char string_data[20] = "Praise The Lord\n";
	int count = 0;
	while(1)
	{
		uart_write(string_data[count++]);

		for(int i=0;i<=75000;i++);
		GPIOA->ODR ^= LED;

		if (count == 17)
		{
			count = 0;
		}
	}
}
