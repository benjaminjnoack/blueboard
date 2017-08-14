#include "leds.h"

void init_leds(void) {
  LPC_GPIO1->FIODIR2 |= (LED1 | LED2 | LED3 | LED4);
}

void led_off(led_t led) {
  LPC_GPIO1->FIOPIN2 &= ~(led);
}

void led_on(led_t led) {
  LPC_GPIO1->FIOPIN2 |= led;
}
