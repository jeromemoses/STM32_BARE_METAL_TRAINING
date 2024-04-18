#include "stm32f0xx.h"
#include "stm32f091xc.h"

#define GPIOCEN 	(1U<<19)
#define SYSCFGEN 	(1U<<0)
#define BUTTON 		(1U<<13)
#define MR13 		(1U<<13)
#define TR13 		(1U<<13)

void exti_pc13_init(void)
{
	/*Disable global interrupt*/
	__disable_irq();

	/*Enable clock for GPIOC*/
	RCC->AHBENR |= GPIOCEN;

	//enable clock for sysconfig
	RCC->APB2ENR |= SYSCFGEN;

	//set GPIO PC13 as input
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	//pc1 should generator EXTI13
	SYSCFG->EXTICR[3] &= ~(1U<<6);
	SYSCFG->EXTICR[3] |= (1U<<5);
	SYSCFG->EXTICR[3] &= ~(1U<<4);

	//unmask PC13
	EXTI->IMR |= MR13;

	//Enable falling trigger for PC13
	EXTI->FTSR |= TR13;

	//enable the interrupt in global
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	//enable the global interrupt
	__enable_irq();
}
