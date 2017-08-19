#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_timers();
  LPC_GPIO0->FIODIR1 |= (1 << 1);
  while (1) {
    LPC_GPIO0->FIOSET1 |= (1 << 1);
    wait_ms(100);
    LPC_GPIO0->FIOCLR1 |= (1 << 1);
    wait_ms(100);
  }

  return 0;
}
