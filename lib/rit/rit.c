#include "rit.h"

void (*rit_cb)(void);
//TODO the first parameter is not translated to any time base
void init_rit(uint32_t us, void (*cb)(void)) {
  //set the callback
  rit_cb = cb;
  //power rit
  LPC_SC->PCONP |= (1 << 16);
  //PCLK = CCLK
  LPC_SC->PCLKSEL1 |= (0x01 << PCLK_RIT);
  //timer enable clear
  LPC_RIT->RICTRL |= (1 << RITENCLR);
  //set the compare value
  LPC_RIT->RICOMPVAL = us;
  //enable interrupts
  NVIC_EnableIRQ(RIT_IRQn);
}

void RIT_IRQHandler(void) {
  LPC_RIT->RICTRL |= (1 << RITINT);
  rit_cb();
}
