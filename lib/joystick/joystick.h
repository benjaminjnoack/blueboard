#include "LPC17xx.h"

typedef enum {
  NONE,
  LEFT,   //p13 P0.15
  CENTER, //p14 P0.16
  DOWN,   //p12 P0.17
  UP,     //p15 P0.23
  RIGHT,  //p16 P0.24
} joystick_t;

void init_joystick(void);
joystick_t read_joystick(void);
