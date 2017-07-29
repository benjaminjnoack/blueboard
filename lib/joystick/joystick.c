#include "joystick.h"

void init_joystick(void) {
  //set GPIO port direction
  FIO0DIR1 &= 0x7F; //P0.15
  FIO0DIR2 &= 0xFE  //P0.16
            & 0xFD  //P0.17
            & 0x7F; //P0.23
  FIO0DIR3 &= 0xFE; //P0.24
  PINMODE0 |= 0xC0000000;
  PINMODE1 |= 0x0003C00F;
}

joystick_t read_joystick(void) {
  joystick_t joy;

  if ((FIO0PIN2 & 0x02) >> 1) {
    joy = DOWN;
  } else if (FIO0PIN3 & 0x01) {
    joy = RIGHT;
  } else if ((FIO0PIN1 & 0x80) >> 7) {
    joy = LEFT;
  } else if (FIO0PIN2 & 0x01) {
    joy = CENTER;
  } else if ((FIO0PIN2 & 0x80) >> 7) {
    joy = UP;
  } else {
    joy = NONE;
  }

  return joy;
}
