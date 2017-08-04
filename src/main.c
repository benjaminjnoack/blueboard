#include "blueboard.h"

int main(int argc, char const *argv[]) {
  SystemInit();
  init_pwm();
  set_cycle_rate(50000);
  enable_pwm(PWM1);
  enable_pwm(PWM2);
  set_duty_cycle(PWM1, 10000);
  set_duty_cycle(PWM2, 20000);

  while (1) {
    /* super loop */
  }

  return 0;
}
