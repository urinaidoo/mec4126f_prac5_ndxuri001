#define STM32F051
#include "stm32f0xx.h"
#include "lcd_stm32f0.h"
#include <stdio.h>
#include <string.h>

volatile int presscount = 0;

void main(void);
void display_on_LCD(uint8_t i);
void init_LEDS(void);
void display_on_LEDS(uint8_t i);
void init_switches(void);
void init_external_interrupts(void);

void main(void)
{
	init_LEDS();
	init_switches();
	init_LCD();
	init_external_interrupts();


	uint8_t count = 0;
	while(count<=256)
	{
		if((presscount%2)!=0)
		{	lcd_command(DISPLAY_ON);
			if ((GPIOA->IDR & GPIO_IDR_1) == 0)
			{
				++count;
			}
			if ((GPIOA->IDR & GPIO_IDR_2) == 0)
			{
				--count;
			}
			display_on_LEDS(count);
			display_on_LCD(count);
		}
		else
		{
			count=0;
			lcd_command(DISPLAY_OFF);
			lcd_command(CLEAR);
			display_on_LEDS(count);
			delay(25000);

		}

	}
}


void display_on_LCD(uint8_t i){


	char str[3];
	int deci = i;
	sprintf(str,"%d", deci);
	lcd_putstring(str);
	delay(65000);
	lcd_command(CLEAR);

}

void init_LEDS(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER0_0;
	GPIOB->MODER |= GPIO_MODER_MODER1_0;
	GPIOB->MODER |= GPIO_MODER_MODER2_0;
	GPIOB->MODER |= GPIO_MODER_MODER3_0;
	GPIOB->MODER |= GPIO_MODER_MODER4_0;
	GPIOB->MODER |= GPIO_MODER_MODER5_0;
	GPIOB->MODER |= GPIO_MODER_MODER6_0;
	GPIOB->MODER |= GPIO_MODER_MODER7_0;
}

void display_on_LEDS(uint8_t i){
	GPIOB->ODR = i;
}


void init_switches(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	GPIOA->MODER &= ~GPIO_MODER_MODER1;
	GPIOA->MODER &= ~GPIO_MODER_MODER2;
	GPIOA->MODER &= ~GPIO_MODER_MODER3;

	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR2_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_0;
}

void init_external_interrupts(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;
	EXTI->IMR |= EXTI_IMR_MR3;
	EXTI->FTSR |= EXTI_FTSR_TR3;
	NVIC_EnableIRQ(EXTI2_3_IRQn);
}

void EXTI2_3_IRQHandler(void)
{
	presscount+=1;
	EXTI->PR |= EXTI_PR_PR3;
}
