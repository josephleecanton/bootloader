/*
 * timebase.c
 *
 *  Created on: Jun 7, 2023
 *      Author: josep
 *
 *  Systick timer is a core peripheral, not one provided by vendors.
 *  Documentation is in Cortex M4 Devices Generic User Guide.
 *  Docs dont match CMCIS here is the map:
 *  pg 4.33  SYST_CSR  is the CTRL register    SysTick->CTRL
 *               _RVR  is the LOAD register
 *               _CVR  is the VAL register
 *
 *
 *  also note the User Guide does not give the base address of SysTick
 *  look at SysTick macro expanision: shows E000E000 + 0x10
 *
 */

#include "stm32f4xx.h"
#include "timebase.h"

#define CTRL_ENABLE (1U<<0)
#define CTRL_TICKINIT (1U<<1)
#define CTRL_CLCKSRC (1U<<2)
#define CTRL_COUNTFLAG (1U<<16)

#define ONE_SEC_LOAD    16000000
/* milliseconds:        16000 */

void timebase_init(void){  /*should be "Systick timer init" */


/*Disable global interrupts */

	__disable_irq();

/*Load the timer with number of clock cycles per second*/
	SysTick->LOAD = ONE_SEC_LOAD - 1; /* count from 0 */
/*Clear systick current value register - has nbr of ticks, not interrupts*/
	SysTick->VAL = 0U;
/*Select internal clock source*/
/*Enable Systick interrupt*/
/*Enable Systick timer*/
	SysTick->CTRL = CTRL_CLCKSRC; /*reset entire register, set clcksrc bit */
	SysTick->CTRL |= CTRL_TICKINIT; /* same reg set for tick interrupts */
	SysTick->CTRL |= CTRL_ENABLE;  /* enable systick hardware */

	/*Enable global interrrupt*/
	__enable_irq();  /* systick interrupts go to NVIC first */

}


#define MAX_DELAY   30
#define TICK_FREQ   1
volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;

/* functiion to delay a certain nbr of seconds */
void delay(uint32_t xseconds){
	uint32_t waitrequest = xseconds;
	uint32_t tickstart= get_tick();  /* tickstart is nbr of interupts since systick init? */
	if (waitrequest < MAX_DELAY){
		waitrequest += (uint32_t)TICK_FREQ;  /* why TICK_FREQ not always 1? */
	}  /* xseconds wait request limited to MAX_DELAY */
	while((get_tick() - tickstart) < waitrequest){
		;
	}

}

uint32_t get_tick(void){  /* defines a return uint32_t but instead updates global variable. */
	__disable_irq();/* updates global variable AND returns it also */
	g_curr_tick_p = g_curr_tick;
	__enable_irq();
	return g_curr_tick_p;
}

/*
 *   INTERUPT HANDLERS
 *
 *  tick_increment is part of the Systick_handler - why a separate function?
 */
void tick_increment(void){
	g_curr_tick =+TICK_FREQ; /* not sure why TICK_FREQ would not always be 1 ? */
}

void SysTick_Handler(void){
	tick_increment();     /* increment the count on each interrupt */
}



