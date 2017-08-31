#include "blueboard.h"

volatile int led3_state = 0;
volatile int led4_state = 0;

void toggle_led3() {
  if (led3_state) {
    led_off(LED3);
    led3_state = 0;
  } else {
    led_on(LED3);
    led3_state = 1;
  }
  timer_ms_async(100, toggle_led3);
}

void toggle_led4() {
  if (led4_state) {
    led_off(LED4);
    led4_state = 0;
  } else {
    led_on(LED4);
    led4_state = 1;
  }
  timer_us_async(1000000, toggle_led4);
}

int main(int argc, char const *argv[]) {
  init_leds();
  init_timers();
  timer_ms_async(100, toggle_led3);
  timer_us_async(1000000, toggle_led4);
  while (1) {
    led_on(LED1);
    timer_ms(100);
    led_off(LED1);
    timer_us(100000);
  }

  return 0;
}
