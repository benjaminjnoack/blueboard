#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_rgb();
  init_joystick();
  char ledOn = 0;

  while (1) {
    switch (read_joystick()) {
      case UP:
        rgb_on(RED);
        ledOn = 1;
        break;
      case DOWN:
        rgb_on(GREEN);
        ledOn = 1;
        break;
      case RIGHT:
        rgb_on(BLUE);
        ledOn = 1;
        break;
      case LEFT:
        break;
      case CENTER:
        rgb_on(RED);
        rgb_on(GREEN);
        rgb_on(BLUE);
        ledOn = 1;
        break;
      case NONE:
        if (ledOn) {
          rgb_off(RED);
          rgb_off(GREEN);
          rgb_off(BLUE);
          ledOn = 0;
        }
        break;
    }
  }

  return 0;
}
