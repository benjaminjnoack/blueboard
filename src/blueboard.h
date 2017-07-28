#include "math.h"
#include "leds.h"
#include "rgb.h"

//TODO a parameterized delay
void hard_delay(void) {
  for (double i = 0; i <= 2000; i++) {
    sin(i);
  }
}
