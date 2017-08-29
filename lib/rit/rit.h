#include "LPC17xx.h"

#ifndef RITINT
#define RITINT 0
#endif

#ifndef PCLK_RIT
#define PCLK_RIT 26
#endif

#ifndef RITENCLR
#define RITENCLR 1
#endif

void init_rit(uint32_t us, void (*cb)(void));
void set_rit(uint32_t us);
void set_rit(uint32_t ms);
