#include "dac.h"

void init_dac(void) {
  //p18 P0.26 AOUT
  LPC_PINCON->PINSEL1 |= 0x00200000;
}

void write_dac(int d) {
  LPC_DAC->DACR = ((d & DAC_10_BIT_MASK) << DAC_VALUE_OFFSET);
}
