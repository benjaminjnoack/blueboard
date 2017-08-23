#include "blueboard.h"

const char greeting[] = "HELLO WORLD\n";

int main(int argc, char const *argv[]) {
  init_timers();
  init_gpio();
  init_uart();

  while (1) {
    tx_uarts(greeting, 12);
    timer_ms(100);
  }

  return 0;
}
