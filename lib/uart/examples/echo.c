#include "blueboard.h"

void callback(char rx) {
  tx_uart(rx);
}

int main(int argc, char const *argv[]) {
  init_leds();
  init_timers();
  init_uart(callback);

  while (1) {
    led_on(LED1);
    timer_ms(100);
    led_off(LED1);
    timer_ms(100);
  }
  return 0;
}
