#include "LPC17xx.h"

#ifndef PCPWM1
#define PCPWM1 6
#endif

#ifndef PWMENA_OFFSET
#define PWMENA_OFFSET 8
#endif

#ifndef COUNTER_ENABLE
#define COUNTER_ENABLE 0
#endif

#ifndef PWM_ENABLE
#define PWM_ENABLE 2
#endif

typedef enum {
  PWM1 = 1, //p26 P2.0 PWM1.1 SPEAKER
  PWM2,     //p25 P2.1 PWM1.2 BLUE
  PWM3,     //p24 P2.2 PWM1.3 GREEN
  PWM4,     //p23 P2.3 PWM1.4 RED
  PWM5,     //p21 P2.4 PWM1.5 PWM2
  PWM6      //p22 P2.5 PWM1.6 PWM1
} pwm_t;

void init_pwm(void);
void set_cycle_rate(uint32_t rate);
void set_duty_cycle(pwm_t pwm, uint32_t duty);
void enable_pwm(pwm_t pwm);
void disable_pwm(pwm_t pwm);
