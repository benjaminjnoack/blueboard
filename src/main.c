#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_timers();
  init_uart();
  init_leds();
  char rx;

  while (1) {
    if (readable_uart()) {
      rx = rx_uart();
      tx_uart(rx);
    }
  }

  return 0;
}
