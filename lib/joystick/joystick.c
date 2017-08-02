#include "joystick.h"

void init_joystick(void) {
  //set GPIO port direction
  LPC_GPIO0->FIODIR1 &= 0x7F; //P0.15
  LPC_GPIO0->FIODIR2 &= 0xFE  //P0.16
                      & 0xFD  //P0.17
                      & 0x7F; //P0.23
  LPC_GPIO0->FIODIR3 &= 0xFE; //P0.24
  //Set the pinmode to input
  LPC_PINCON->PINMODE0 |= 0xC0000000;
  LPC_PINCON->PINMODE1 |= 0x0003C00F;
}

joystick_t read_joystick(void) {
  joystick_t joy;

  if ((LPC_GPIO0->FIOPIN2 & 0x02) >> 1) {
    joy = DOWN;
  } else if (LPC_GPIO0->FIOPIN3 & 0x01) {
    joy = RIGHT;
  } else if ((LPC_GPIO0->FIOPIN1 & 0x80) >> 7) {
    joy = LEFT;
  } else if (LPC_GPIO0->FIOPIN2 & 0x01) {
    joy = CENTER;
  } else if ((LPC_GPIO0->FIOPIN2 & 0x80) >> 7) {
    joy = UP;
  } else {
    joy = NONE;
  }

  return joy;
}
