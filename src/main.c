#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();
  init_leds();

  char buf = 'h';

  while (1) {
    led_off(LED1);
    led_off(LED2);
    led_off(LED3);
    led_off(LED4);

    i2c_result_t res = bb_i2c_write(0xA0, &buf, 1);


    delay();
    delay();
    delay();
  }

  return 0;
}
