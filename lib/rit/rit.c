#include "rit.h"

void (*rit_cb)(void);

int init_rit(uint32_t us, void (*cb)(void)) {
  if (us > 44739242) {
    return 1;
  } else {
    us = us * 96;
  }
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
  return 0;
}

void RIT_IRQHandler(void) {
  LPC_RIT->RICTRL |= (1 << RITINT);
  rit_cb();
}
