#include "rgb.h"
#include "pwm.h"

void init_rgb(void) {
  enable_pwm(PWM2);
  enable_pwm(PWM3);
  enable_pwm(PWM4);
  set_cycle_rate(0xFF);
}

void set_rgb(uint8_t red, uint8_t green, uint8_t blue) {
  set_duty_cycle(PWM4, red);
  set_duty_cycle(PWM3, green);
  set_duty_cycle(PWM2, blue);
}
