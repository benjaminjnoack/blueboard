#include "pots.h"

void init_pots(void) {
  init_adc();
  init_ain(AD4);
  init_ain(AD5);
}

int read_pot(pot_t pot) {
  int ADCdata;
  switch (pot) {
    case POT1:
      ADCdata = read_ain(AD4);
      break;
    case POT2:
      ADCdata = read_ain(AD5);
      break;
  }

  return ADCdata;
}
