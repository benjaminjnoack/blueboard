#include "blueboard.h"

void handle_rx(char rx) {
  tx_uart(rx);
}

int main(int argc, char const *argv[]) {
  init_timers();
  init_uart();
  init_leds();
  rx_uart_async(handle_rx);

  while (1) {
    led_on(LED1);
    timer_ms(100);
    led_off(LED1);
    timer_ms(100);
  }

  return 0;
}
