/*
 * timebase.h
 */

// Paths & Symbols must contain
#ifndef __TIMEBASE_H__
#define __TIMEBASE_H__

#include <stdint.h>
uint32_t get_recent_tick_count(void);
void delay(uint32_t delay_count);
void timebase_init(void);

#endif




