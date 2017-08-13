#include "pwm.h"

void init_pwm(void) {
  //select CCLK/4 for PCLK_PWM1
  LPC_SC->PCLKSEL1 &= ~(0x3000);
  //select P2.5 as PWM1.6
  LPC_PINCON->PINSEL4 |= (1 << 10);
  //select P2.4 as PWM1.5
  LPC_PINCON->PINSEL4 |= (1 << 8);
  //enable counters and PWM module
  LPC_PWM1->TCR |= (1 << COUNTER_ENABLE) | (1 << PWM_ENABLE);
  //no pre-scalar
  LPC_PWM1->PR = 0x0;
  //reset on PWMMR0
  LPC_PWM1->MCR |= (1 << 1);
}

void enable_pwm(pwm_t pwm) {
  switch (pwm) {
    case PWM1:
      LPC_PWM1->PCR |= (1 << PWMENA5);
      break;
    case PWM2:
      LPC_PWM1->PCR |= (1 << PWMENA6);
      break;
    case PWM3:
      LPC_PWM1->PCR |= (1 << PWMENA1);
  }
}

void disable_pwm(pwm_t pwm) {
  switch (pwm) {
    case PWM1:
      LPC_PWM1->PCR &= ~(1 << PWMENA5);
      break;
    case PWM2:
      LPC_PWM1->PCR &= ~(1 << PWMENA6);
      break;
    case PWM3:
      LPC_PWM1->PCR &= ~(1 << PWMENA1);
  }
}

void set_cycle_rate(uint32_t rate) {
  //set Match 0 register
  LPC_PWM1->MR0 = rate;
  //latch match register 0
  LPC_PWM1->LER |= (1 << 0);
}

void set_duty_cycle(pwm_t pwm, uint32_t duty) {
  switch (pwm) {
    case PWM1:
      //match
      LPC_PWM1->MR6 = duty;
      //latch
      LPC_PWM1->LER |= (1 << 6);
      break;
    case PWM2:
      LPC_PWM1->MR5 = duty;
      LPC_PWM1->LER |= (1 << 5);
      break;
    case PWM3:
      LPC_PWM1->MR1 = duty;
      LPC_PWM1->LER |= (1 << 1);
  }
}
