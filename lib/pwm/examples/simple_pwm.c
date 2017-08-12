#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_pwm();
  set_cycle_rate(1000);
  enable_pwm(PWM1);
  enable_pwm(PWM2);
  set_duty_cycle(PWM1, 100);
  set_duty_cycle(PWM2, 200);

  while (1) {
    /* super loop */
  }

  return 0;
}
