

#include <main.h>    /* makes necessary device defines required by CMSIS */
#include <stdio.h>
#include <stdint.h>
//#include "stm32f4xx.h"
//    # include "stm32f411xe.h"
#include "fpu.h"   /* don't have to include fpu.c - it's compiled separately from this file */
#include "uart.h"  /*  ditto */
#include "timebase.h"

/*
 * Printf with  USART2  with GPIO PA2 pin for transmit (AF7)
 */
int dummy(void);

int main(void){



	fpu_enable();
 	uart_init();
    timebase_init();
    int i = 0;
    printf("buffer1x\r\n");
	while(i<10){
			 i++;
			 printf("Frank22 the lazy brown fox%d \r\n",i);
			 delay(1);
    }

//			 delay(uint32_t delay_count); delay count is interrupt count.we have
//			 already setup ticks per interrupt such that we get an interruppt every 1 second

}








