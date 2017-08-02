#include "dac.h"

void init_dac(void) {
  //set AOUT on P0.26
  LPC_PINCON->PINSEL1 |= 0x00200000;
}

void write_dac(int d) {
  LPC_DAC->DACR = (d << DAC_VALUE_OFFSET);
}
