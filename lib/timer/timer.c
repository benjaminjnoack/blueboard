#include "timer.h"

void init_timers() {
  //power timers 0 and 1
  LPC_SC->PCONP |= (PCTIM0 | PCTIM1);
  //disable counters
  LPC_TIM0->TCR = 0;
  LPC_TIM1->TCR = 0;
  //CCLK/8 (12 MHz)
  LPC_SC->PCLKSEL0 |= 0x3C;
  //Divide PCLK by (11 + 1)
  LPC_TIM0->PR = 0x0B;
  //Divide PCLK by (11,999 + 1)
  LPC_TIM1->PR = 0x2DEF;
}

void timer_ms(uint32_t ms) {
  LPC_TIM1->TCR = (1 << 1);
  LPC_TIM1->TCR = 1;
  while (LPC_TIM1->TC < ms) {
    /* busy wait */
  }
}

void timer_ms_async(uint32_t ms, void (*cb)(void)) {
  timer_ms(ms);
  cb();
}

void timer_us(uint32_t us) {
  LPC_TIM0->TCR = (1 << 1);
  LPC_TIM0->TCR = 1;
  while (LPC_TIM0->TC < us) {
    /* busy wait */
  }
}

void timer_us_async(uint32_t us, void (*cb)(void)) {
  timer_us(us);
  cb();
}
