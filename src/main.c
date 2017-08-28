#include "blueboard.h"

void joystick_handler(joystick_t joystick) {
  switch (joystick) {
    case NONE:
      led_off(LED1);
      led_off(LED2);
      led_off(LED3);
      led_off(LED4);
      break;
    case LEFT:
      led_on(LED1);
      break;
    case CENTER:
      led_on(LED1);
      led_on(LED2);
      led_on(LED3);
      led_on(LED4);
      break;
    case DOWN:
      led_on(LED2);
      break;
    case UP:
      led_on(LED3);
      break;
    case RIGHT:
      led_on(LED4);
      break;
  }
}

int main(int argc, char const *argv[]) {
  init_leds();
  init_joystick(joystick_handler);

  while (1) {

  }

  return 0;
}
