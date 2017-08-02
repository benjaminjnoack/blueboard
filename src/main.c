#include "blueboard.h"
//NOTE: Don't forget the super loop!
int main(int argc, char const *argv[]) {
  init_leds();
  init_pots();

  while (1) {
    led_off(LED1);
    led_off(LED2);
    led_off(LED3);
    led_off(LED4);

    int adc = read_pot(POT1);
    if (adc > 1000) {
      led_on(LED1);
    }
    if (adc > 2000) {
      led_on(LED2);
    }
    if (adc > 3000) {
      led_on(LED3);
    }
    if (adc > 4000) {
      led_on(LED4);
    }

    delay();
  }

  return 0;
}
