/*
 * fpu.c
 *
 *  Created on: May 31, 2023
 *
 *  The fpu is a Cortex M4 peripherial, that is built into the M4 architecture.
 *  fpu Documentation is in "Cortex - M4 Devices Generic User Guide"
 *  However do a pdf search for "0XE000ED00" and you find 2 occurances
 *  on which indicates the SCB resides here but Table 4-12 on page 4-11
 *  appears incorrect as it show this address as the CPUID Base Register.
 *  my user guide is the second release dated 3 August 2011 so there maybe an
 *  update to my user guide  ARM DUI 0553B   ID012616
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f411xe.h"
void fpu_enable(void);       /* also in fpu.h */


void fpu_enable(){
	SCB->CPACR |=(1<<20);    /* setup floating point */
	SCB->CPACR |=(1<<21);    /* CPACR is Coprocessor Access Control Register */
	SCB->CPACR |=(1<<22);    /* pg 4-48 page 4-52  Cortex M4 User Guide */
	SCB->CPACR |=(1<<23);    /*  SCB macro found in core_cm4.h file */

}
