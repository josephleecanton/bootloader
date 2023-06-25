
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f411xe.h"

#define BUSFREQ 16000000
#define TXBAUD 115200
static uint16_t compute_baud_rate_div(uint32_t busfreq, uint32_t txbaudrate);
static void uart_set_baudrate(uint32_t busfreq,uint32_t txbaudrate);
static void uart_write(int ch);
/* static fns don't go into header files, used only in this file */

void uart_init(void){

RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* Enable clock access for GPIOA */

GPIOA->MODER |=  GPIO_MODER_MODER2_1;   /* set high bit as "1" */
GPIOA->MODER &=~  GPIO_MODER_MODER2_0;    /* set low bit to "0"  10 is AF mode*/

/* set alternate function type to AF7 */
GPIOA->AFR[0] |=(1U<<8);
GPIOA->AFR[0] |=(1U<<9);
GPIOA->AFR[0] |=(1U<<10);
GPIOA->AFR[0] &=~(1U<<11);

/* enable clock access to uart2 module */
RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

/* config UART2 baud rate */
uart_set_baudrate(BUSFREQ,TXBAUD);


/* configure transfer  direction */

USART2->CR1 =  0UL;   /* ? reset - should I do this or just stop TX ?*/
USART2->CR2 =  0UL;   /* ?reset should I do this or just stop TX */

/*8-N-1  8 data bits, 1 start bit , 1 stop , no parity */
/* hint: hover over macro, also these macros are in CMSIS drivers */
USART2->CR1 |=~  USART_CR1_M ;    /* set 1 Start bit, 8 Data bits pg550 */
USART2->CR1 |=~  USART_CR1_PCE;   /* disable parity pg pg 551 */
USART2->CR2 |=~  USART_CR2_STOP;  /* set 1 Stop Bit  pg 553*/

USART2->CR1 |= USART_CR1_UE;        /* enable USART    */
USART2->CR1 |= USART_CR1_TE;        /* ENABLE transmit */

}


int __io_putchar(int ch){  /* special STM32CubeIDE method to hookup fprint to USART */
	uart_write(ch);        /*  See file Src/syscalls.c for hints on this hookup */
	return ch;
}

static void uart_write(int ch){
	 while(!(USART2->SR & USART_SR_TXE)){} /* read a bit in a reg with &  */
	 USART2->DR = (ch & 0xFF); /* ?? */
	}


static uint16_t compute_baud_rate_div(uint32_t busfreq, uint32_t txbaudrate){
	uint16_t x =    (   (   busfreq + (txbaudrate/2U)  )/txbaudrate);
	return x;
}

static void uart_set_baudrate(uint32_t busfreq,uint32_t txbaudrate) {
	USART2->BRR = compute_baud_rate_div(busfreq,txbaudrate);
}




