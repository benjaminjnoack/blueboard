#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_timers();
  init_gpio();
  init_uart();

  while (1) {
    tx_uart('h');
    timer_ms(100);
  }

  return 0;
}
