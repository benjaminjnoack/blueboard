#include "pwm.h"

void init_pwm(void) {
  //select CCLK/4 for PCLK_PWM1
  LPC_SC->PCLKSEL1 &= ~(0x3000);
  //select PWM1.1 through PWM1.6
  LPC_PINCON->PINSEL4 |= 0x0555;
  //enable counters and PWM module
  LPC_PWM1->TCR |= (1 << COUNTER_ENABLE) | (1 << PWM_ENABLE);
  //no pre-scalar
  LPC_PWM1->PR = 0x0;
  //reset on PWMMR0
  LPC_PWM1->MCR |= (1 << 1);
}

void enable_pwm(pwm_t pwm) {
  LPC_PWM1->PCR |= (1 << (pwm + PWMENA_OFFSET));
}

void disable_pwm(pwm_t pwm) {
  LPC_PWM1->PCR &= ~(1 << (pwm + PWMENA_OFFSET));
}

void set_cycle_rate(uint32_t rate) {
  //match
  LPC_PWM1->MR0 = rate;
  //latch
  LPC_PWM1->LER |= 0x01;
}

void set_duty_cycle(pwm_t pwm, uint32_t duty) {
  //match
  switch (pwm) {
    case PWM1:
      LPC_PWM1->MR1 = duty;
      break;
    case PWM2:
      LPC_PWM1->MR2 = duty;
      break;
    case PWM3:
      LPC_PWM1->MR3 = duty;
      break;
    case PWM4:
      LPC_PWM1->MR4 = duty;
      break;
    case PWM5:
      LPC_PWM1->MR5 = duty;
      break;
    case PWM6:
      LPC_PWM1->MR6 = duty;
      break;
  }
  //latch
  LPC_PWM1->LER |= (1 << pwm);
}
