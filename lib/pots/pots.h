#include "LPC17xx.h"
#include "adc.h"

typedef enum {
  POT1, //p1.30
  POT2  //p1.31
} pot_t;

void init_pots(void);
int read_pot(pot_t pot);
