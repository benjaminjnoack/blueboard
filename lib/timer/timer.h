#include "LPC17xx.h"

#ifndef PCTIM0
#define PCTIM0 (1 << 1)
#endif

#ifndef PCTIM1
#define PCTIM1 (1 << 2)
#endif

void init_timers();
void timer_ms(uint32_t ms);
void timer_us(uint32_t us);
void timer_ms_async(uint32_t ms, void *callback());
void timer_us_async(uint32_t us, void *callback());
