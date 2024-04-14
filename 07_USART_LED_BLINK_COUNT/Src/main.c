#include "stm32f0xx.h"
#include "stm32f091xc.h"
#include <stdbool.h>
#include "uart.h"

int rec_data;
void blink_led(int);

int main(void)
{
	uart_init();

	while(1)
	{
		rec_data = uart_read();
		rec_data = (int)rec_data - '0';
		uart_write(rec_data+'0');

		if(can_blink())
		{
			blink_led(rec_data*10);
		}
	}
}

void blink_led(int blink_count)
{
	for(int i = 0;i<blink_count;i++)
	{
		GPIOA->ODR ^= LED;
		for(int j = 0;j<=40000;j++);
	}
}
