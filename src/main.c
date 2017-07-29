#include "blueboard.h"

int main(int argc, char const *argv[]) {

  init_leds();
  init_pots();

  while (1) {
    led_off(LED1);
    led_off(LED2);
    led_off(LED3);
    led_off(LED4);

    int ADCdata = read_pot(POT2);

    if (ADCdata > 1000) {
      led_on(LED1);
    }
    if (ADCdata > 2000) {
      led_on(LED2);
    }
    if (ADCdata > 3000) {
      led_on(LED3);
    }
    if (ADCdata > 4000) {
      led_on(LED4);
    }

    delay();
  }
  return 0;
}
