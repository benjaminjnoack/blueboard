#include "leds.h"
#include "joystick.h"
#include "pots.h"
#include "rgb.h"

void delay() {
  double j;
  for (j = 0; j < 50000; j++) {
    j++;
    j--;
  }
}
