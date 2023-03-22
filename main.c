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
