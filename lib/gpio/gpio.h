#include "LPC17xx.h"

typedef enum {
  PIN_6 = (1 << 8),   //P0.8  LCD Reset
  PIN_8 = (1 << 6),   //P0.6  LCD A0
  PIN_11 = (1 << 18), //P0.18 LCD CS
  PIN_29 = (1 << 5),  //P0.5  XBee Status
  PIN_30 = (1 << 4)   //P0.4  XBee Reset
} gpio_t;

void init_gpio();
void set_gpio(gpio_t gpio);
void clear_gpio(gpio_t gpio);
