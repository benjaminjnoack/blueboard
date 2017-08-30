#include "blueboard.h"

#ifndef PORT0_PIN9
#define PORT0_PIN9 (1 << 1)
#endif

int flip = 0;

void callback(void) {
  if (flip) {
    flip = 0;
    LPC_GPIO0->FIOCLR1 |= PORT0_PIN9;
  } else {
    flip = 1;
    LPC_GPIO0->FIOSET1 |= PORT0_PIN9;
  }
}

int main(int argc, char const *argv[]) {
  LPC_GPIO0->FIODIR1 |= PORT0_PIN9;
  init_leds();
  init_timers();
  //toggle pin5 at 1KHz
  init_rit(500, callback);

  while (1) {
    led_on(LED2);
    timer_ms(100);
    led_off(LED2);
    timer_ms(100);
  }

  return 0;
}
