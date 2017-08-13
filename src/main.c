#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();
  init_leds();
  init_rgb();

  char buf[5];

  while (1) {

    bb_i2c_read(0xA0, &buf[0], 5);
    delay();
    delay();
    delay();
    led_off(LED1);
    led_off(LED2);
    led_off(LED3);
    led_off(LED4);
    delay();
    delay();
    delay();
  }

  return 0;
}
