//pin 18 P0.26
//Vout = (Vrefp * D) / 1024
#include "LPC17xx.h"

#ifndef DAC_VALUE_OFFSET
#define DAC_VALUE_OFFSET 6
#endif

#ifndef DAC_10_BIT_MASK
#define DAC_10_BIT_MASK 0x03FF
#endif

void init_dac(void);
void write_dac(int d);
