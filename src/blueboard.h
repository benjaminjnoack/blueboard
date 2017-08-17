#include "dac.h"
#include "leds.h"
#include "i2c.h"
#include "joystick.h"
#include "lm75b.h"
#include "mma7760.h"
#include "pots.h"
#include "pwm.h"
#include "rgb.h"
#include "spi.h"

void delay() {
  double j;
  for (j = 0; j < 50000; j++) {
    j++;
    j--;
  }
}
