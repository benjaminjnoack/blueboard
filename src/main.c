#include "blueboard.h"
//NOTE: Don't forget the super loop!
volatile unsigned char led = 0;
void RIT_IRQHandler(void) {
  if (led) {
    rgb_off(RED);
    led = 0;
  } else {
    rgb_on(RED);
    led = 1;
  }
  LPC_RIT->RICTRL |= 1;
}

int main(int argc, char const *argv[]) {
  init_rgb();
  LPC_SC->PCONP |= (1L<<16);

  LPC_RIT->RICOMPVAL = (uint32_t) 0x00100000;
  LPC_RIT->RICTRL |= (1 << 1);
  LPC_RIT->RICOUNTER = 0;

  NVIC_EnableIRQ(RIT_IRQn);

  while (1) {
    /* code */
  }


  return 0;
}
