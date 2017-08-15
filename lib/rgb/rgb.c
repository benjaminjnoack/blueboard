#include "rgb.h"
#include "pwm.h"

void init_rgb(void) {
  enable_pwm(PWM2);
  enable_pwm(PWM3);
  enable_pwm(PWM4);
  set_cycle_rate(0xFF);
}

void set_rgb(struct RGB *rgb) {
  set_duty_cycle(PWM4, rgb->R);
  set_duty_cycle(PWM3, rgb->G);
  set_duty_cycle(PWM2, rgb->B);
}
