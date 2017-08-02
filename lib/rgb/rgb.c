#include "rgb.h"

void init_rgb(void) {
  LPC_GPIO2->FIODIR0 |= (1 << (BLUE + 1))
                      | (1 << (GREEN + 1))
                      | (1 << (RED + 1));
  LPC_GPIO2->FIOPIN0 |= (1 << (BLUE + 1))
                      | (1 << (GREEN + 1))
                      | (1 << (RED + 1));
}

void rgb_off(rgb_t rgb) {
  LPC_GPIO2->FIOPIN0 |= (1 << (rgb + 1));
}

void rgb_on(rgb_t rgb) {
  LPC_GPIO2->FIOPIN0 &= ~(1 << (rgb + 1));
}
