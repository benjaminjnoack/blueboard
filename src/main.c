#include "blueboard.h"

void p5off() {
  LPC_GPIO0->FIOCLR1 |= (1 << 1);
}

void p5on() {
  LPC_GPIO0->FIOSET1 |= (1 << 1);
}

int main(int argc, char const *argv[]) {
  init_timers();
  LPC_GPIO0->FIODIR1 |= (1 << 1);
  while (1) {
    timer_us_async(50, p5on);
    timer_us_async(50, p5off);
  }

  return 0;
}
