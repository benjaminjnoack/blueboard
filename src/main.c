#include "blueboard.h"

const char greeting[] = "hello world\n";

int main(int argc, char const *argv[]) {
  init_timers();
  init_gpio();
  init_uart();

  while (1) {
    for (uint8_t i = 0; i < sizeof(greeting); i++) {
      tx_uart(greeting[i]);
    }
    timer_ms(100);
  }

  return 0;
}
