#include "LPC17xx.h"

#ifndef PCPWM1
#define PCPWM1 6
#endif

#ifndef PWMENA5
#define PWMENA5 13
#endif

#ifndef PWMENA6
#define PWMENA6 14
#endif

#ifndef COUNTER_ENABLE
#define COUNTER_ENABLE 0
#endif

#ifndef PWM_ENABLE
#define PWM_ENABLE 2
#endif

typedef enum {
  PWM1, //p21 P2.5 pwm1.6
  PWM2  //p22 P2.4 pwm1.5
} pwm_t;

void init_pwm(void);
void set_cycle_rate(uint32_t rate);
void set_duty_cycle(pwm_t pwm, uint32_t duty);
void enable_pwm(pwm_t pwm);
void disable_pwm(pwm_t pwm);
