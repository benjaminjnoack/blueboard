#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_leds();
  init_joystick();

  while (1) {
    led_off(LED1);
    led_off(LED2);
    led_off(LED3);
    led_off(LED4);

    switch (read_joystick()) {
      case UP:
        led_on(LED1);
        break;
      case DOWN:
        led_on(LED2);
        break;
      case RIGHT:
        led_on(LED3);
        break;
      case LEFT:
        led_on(LED4);
        break;
      case CENTER:
        led_on(LED1);
        led_on(LED2);
        led_on(LED3);
        led_on(LED4);
        break;
      case NONE:
        //do nothing
        break;
    }
  }




  return 0;
}
