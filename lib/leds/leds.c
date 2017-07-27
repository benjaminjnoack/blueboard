#include "leds.h"

void init_leds(void) {
  FIO1DIR2 |= (LED1 | LED2 | LED3 | LED4);
}

void led_off(led_t led) {
  FIO1PIN2 &= ~led;
}

void led_on(led_t led) {
  FIO1PIN2 |= led;
}
