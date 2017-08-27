#include "pots.h"

void init_pots(void) {
  init_ain(AD4);
  init_ain(AD5);
}

int read_pot(pot_t pot) {
  int ADCdata = 0;
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

uint8_t read_pot_8(pot_t pot) {
  uint8_t ADCdata;
  switch (pot) {
    case POT1:
      ADCdata = read_ain_8(AD4);
      break;
    case POT2:
      ADCdata = read_ain_8(AD5);
      break;
  }

  return ADCdata;
}
