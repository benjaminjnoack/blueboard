#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_leds();
  init_spi();

  while (1) {
    led_on(LED1);
    write_spi(0xAA);
    delay();
    led_off(LED1);
    delay();
  }

  return 0;
}
