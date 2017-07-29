#include "leds.h"
#include "pots.h"
#include "rgb.h"

void delay() {
  double j;
  for (j = 0; j < 100000; j++) {
    j++;
    j--;
  }
}
