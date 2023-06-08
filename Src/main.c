
#include <stdio.h>
#include <stdint.h>
//    # include "stm32f4xx.h"
//    # include "stm32f411xe.h"
#include "fpu.h"   /* don't have to include fpu.c - it's compiled separately from this file */
#include "uart.h"  /*  ditto */


/*
 * Printf with  USART2  with GPIO PA2 pin for transmit (AF7)
 */


int main(void){

    fpu_enable();
 	uart_init();


		 while(1){
			 printf("Frank11 says Hello from Stm32\n\r");
			 /* printf is redirected to usart communication*/

		 }

	}





