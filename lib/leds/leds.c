#include "leds.h"

void init_leds(void) {
  LPC_GPIO1->FIODIR2 |= ((1 << 2) | (1 << 4) | (1 << 5) | (1 << 7));
}

void led_off(led_t led) {
  switch (led) {
    case LED1:
      LPC_GPIO1->FIOPIN2 &= ~(1 << 2);
      break;
    case LED2:
      LPC_GPIO1->FIOPIN2 &= ~(1 << 4);
      break;
    case LED3:
      LPC_GPIO1->FIOPIN2 &= ~(1 << 5);
      break;
    case LED4:
      LPC_GPIO1->FIOPIN2 &= ~(1 << 7);
      break;
  }
}

void led_on(led_t led) {
  switch (led) {
    case LED1:
      LPC_GPIO1->FIOPIN2 |= (1 << 2);
      break;
    case LED2:
      LPC_GPIO1->FIOPIN2 |= (1 << 4);
      break;
    case LED3:
      LPC_GPIO1->FIOPIN2 |= (1 << 5);
      break;
    case LED4:
      LPC_GPIO1->FIOPIN2 |= (1 << 7);
      break;
  }
}
