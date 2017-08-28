#include "LPC17xx.h"

typedef enum {
  NONE,
  LEFT = (1 << 15),   //p13 P0.15
  CENTER = (1 << 16), //p14 P0.16
  DOWN = (1 << 17),   //p12 P0.17
  UP = (1 << 23),     //p15 P0.23
  RIGHT = (1 << 24),  //p16 P0.24
} joystick_t;

void init_joystick(void (*callback)(joystick_t joystick));
