#include "timer.h"
#include "leds.h"

void (*timer_ms_cb)(void);
void (*timer_us_cb)(void);

void init_timers() {
  //power timers 0, 1, 2, and 3
  LPC_SC->PCONP |= (PCTIM0 | PCTIM1 | PCTIM2 | PCTIM3);
  //CCLK/8 (12 MHz) for timers 0 and 1
  LPC_SC->PCLKSEL0 |= 0x3C;
  //CCLK/8 (12 MHz) for timers 2 and 3
  LPC_SC->PCLKSEL1 |= 0xF000;
  //timer_ms (TIM0)
  LPC_TIM0->PR = PRESCALER_MS;
  LPC_TIM0->MCR = (MR0S);
  //timer_ms_async (TIM1)
  LPC_TIM1->PR = PRESCALER_MS;
  LPC_TIM1->MCR = (MR0I | MR0R | MR0S);
  NVIC_EnableIRQ(TIMER1_IRQn);
  //timer_us (TIM2)
  LPC_TIM2->PR = PRESCALER_US;
  LPC_TIM2->MCR = (MR0S);
  //timer_us_async (TIM3)
  LPC_TIM3->PR = PRESCALER_US;
  LPC_TIM3->MCR = (MR0I | MR0R | MR0S);
  NVIC_EnableIRQ(TIMER3_IRQn);
}

void timer_ms(uint32_t ms) {
  LPC_TIM0->MR0 = ms;
  LPC_TIM0->TCR |= (1 << 1);
  LPC_TIM0->TCR = COUNTER_ENABLE;
  while (LPC_TIM0->TC < ms) {
    /* busy wait */
  }
}

void timer_ms_async(uint32_t ms, void (*cb)(void)) {
  timer_ms_cb = cb;
  LPC_TIM1->MR0 = ms;
  LPC_TIM1->TCR = COUNTER_ENABLE;
}

void TIMER1_IRQHandler() {
  LPC_TIM1->IR |= MR0I;
  timer_ms_cb();
}

void timer_us(uint32_t us) {
  LPC_TIM2->MR0 = us;
  LPC_TIM2->TCR |= (1 << 1);
  LPC_TIM2->TCR = COUNTER_ENABLE;
  while (LPC_TIM2->TC < us) {
    /* busy wait */
  }
}

void timer_us_async(uint32_t us, void (*cb)(void)) {
  timer_us_cb = cb;
  LPC_TIM3->MR0 = us;
  LPC_TIM3->TCR = COUNTER_ENABLE;
}

void TIMER3_IRQHandler() {
  LPC_TIM3->IR |= MR0I;
  timer_us_cb();
}
