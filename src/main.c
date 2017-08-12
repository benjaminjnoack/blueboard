#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();
  init_leds();
  led_off(LED1);
  led_off(LED2);
  led_off(LED3);
  led_off(LED4);
  char buf[5] = {'h', 'e', 'l', 'l', 'o'};

  while (1) {

    i2c_result_t res = bb_i2c_write(0xA0, &buf[0], 5);

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
