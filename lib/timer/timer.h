#include "LPC17xx.h"

#ifndef PCTIM0
#define PCTIM0 (1 << 1)
#endif

#ifndef PCTIM1
#define PCTIM1 (1 << 2)
#endif

#ifndef PCTIM2
#define PCTIM2 (1 << 22)
#endif

#ifndef PCTIM3
#define PCTIM3 (1 << 23)
#endif

#ifndef COUNTER_ENABLE
#define COUNTER_ENABLE (1 << 0)
#endif

#ifndef PRESCALER_US//Divide PCLK by (11 + 1)
#define PRESCALER_US 0x0B
#endif

#ifndef PRESCALER_MS//Divide PCLK by (11,999 + 1)
#define PRESCALER_MS 0x2DEF
#endif

#ifndef MR0I
#define MR0I (1 << 0)
#endif

#ifndef MR0R
#define MR0R (1 << 1)
#endif

#ifndef MR0S
#define MR0S (1 << 2)
#endif

void init_timers();
void timer_ms(uint32_t ms);
void timer_ms_async(uint32_t ms, void (*cb)(void));
void timer_us(uint32_t us);
void timer_us_async(uint32_t us, void (*cb)(void));
