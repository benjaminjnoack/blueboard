#include "blueboard.h"

int led_status = 0;

void callback(void) {
  if (led_status) {
    led_status = 0;
    led_off(LED2);
  } else {
    led_status = 1;
    led_on(LED2);
  }
}

int main(int argc, char const *argv[]) {
  init_leds();
  init_timers();
  init_rit((uint32_t) 0x01000000, callback);

  while (1) {
    led_on(LED1);
    timer_ms(100);
    led_off(LED1);
    timer_ms(100);
  }
  return 0;
}
