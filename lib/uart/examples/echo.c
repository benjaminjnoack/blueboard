#include "blueboard.h"
//send back what is recieved on interrupt
void callback(char rx) {
  tx_uart(rx);
}

int main(int argc, char const *argv[]) {
  //initialize the necessary peripherals
  init_leds();
  init_timers();
  init_uart(callback);

  while (1) {
    //blinky lights
    led_on(LED1);
    timer_ms(100);
    led_off(LED1);
    timer_ms(100);
  }
  return 0;
}
