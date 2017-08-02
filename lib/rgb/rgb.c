#include "rgb.h"

void init_rgb(void) {
  LPC_GPIO0->FIODIR0 |= (RED | GREEN | BLUE);
  LPC_GPIO0->FIOPIN0 |= (RED | GREEN | BLUE);
}

void rgb_off(rgb_t rgb) {
  LPC_GPIO0->FIOPIN0 |= rgb;
}

void rgb_on(rgb_t rgb) {
  LPC_GPIO0->FIOPIN0 &= ~rgb;
}
