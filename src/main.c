#include "blueboard.h"

led_t leds[] = {LED1, LED2, LED3, LED4};

void blink(led_t led) {
  led_on(led);
  hard_delay();
  led_off(led);
  hard_delay();
}

int main(int argc, char const *argv[]) {
  init_leds();

  while (1) {
    short i;
    for (i = 0; i < 4; i++) {
      blink(leds[i]);
    }
    for (i = 3; i >= 0; i--) {
      blink(leds[i]);
    }
  }
  return 0;
}
