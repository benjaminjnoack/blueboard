#include "blueboard.h"
//NOTE: Don't forget the super loop!
int main(int argc, char const *argv[]) {
  init_leds();
  init_rgb();

  while (1) {
    led_on(LED1);
    rgb_off(BLUE);
    rgb_off(RED);
    rgb_off(GREEN);
    delay();
    led_off(LED1);
    rgb_on(RED);
    delay();
    rgb_on(GREEN);
    delay();
    rgb_on(BLUE);
    delay();
  }

  return 0;
}
