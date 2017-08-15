#include "LPC17xx.h"
#include "adc.h"

typedef enum {
  POT1, //p19 p1.30
  POT2  //p20 p1.31
} pot_t;

void init_pots(void);
int read_pot(pot_t pot);
uint8_t read_pot_8(pot_t pot);
