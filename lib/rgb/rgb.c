#include "rgb.h"
#include "pwm.h"

void init_rgb(void) {
  enable_pwm(RED);
  enable_pwm(GREEN);
  enable_pwm(BLUE);
  set_cycle_rate(0x100);
}

void set_rgb(struct RGB *rgb) {
  set_duty_cycle(RED, (uint8_t)~(rgb->R));
  set_duty_cycle(GREEN, (uint8_t)~(rgb->G));
  set_duty_cycle(BLUE, (uint8_t)~(rgb->B));
}
