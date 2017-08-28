#include "joystick.h"
#include "leds.h"
void (*cb)(joystick_t joystick);

void init_joystick(void (*callback)(joystick_t joystick)) {
  cb = callback;
  //set GPIO port direction
  LPC_GPIO0->FIODIR1 &= 0x7F; //P0.15
  LPC_GPIO0->FIODIR2 &= 0xFE  //P0.16
                      & 0xFD  //P0.17
                      & 0x7F; //P0.23
  LPC_GPIO0->FIODIR3 &= 0xFE; //P0.24
  //set pull down resistors
  LPC_PINCON->PINMODE0 |= 0xC0000000;
  LPC_PINCON->PINMODE1 |= 0x0003C00F;
  //enable rising edge interrupts
  LPC_GPIOINT->IO0IntEnR |= ((1 << 15) | (1 << 16) | (1 << 17) | (1 << 23) | (1 << 24));
  //enable falling edge interrupts
  LPC_GPIOINT->IO0IntEnF |= ((1 << 15) | (1 << 16) | (1 << 17) | (1 << 23) | (1 << 24));
  //enable EINT3_IRQn
  NVIC_EnableIRQ(EINT3_IRQn);
}

void EINT3_IRQHandler(void) {
  joystick_t joy;
  long stat = LPC_GPIOINT->IO0IntStatF;

  if (stat & ((1 << 15) | (1 << 16) | (1 << 17) | (1 << 23) | (1 << 24))) {
    joy = NONE;
  } else {
    stat = LPC_GPIOINT->IO0IntStatR;
    if (stat & (1 << 15)) {
      LPC_GPIOINT->IO0IntClr |= (1 << 15);
      joy = LEFT;
    } else if (stat & (1 << 16)) {
      joy = CENTER;
    } else if (stat & (1 << 17)) {
      joy = DOWN;
    } else if (stat & (1 << 23)) {
      joy = UP;
    } else if (stat & (1 << 24)) {
      joy = RIGHT;
    } else {
      joy = NONE;
    }
  }

  LPC_GPIOINT->IO0IntClr |= ((1 << 15) | (1 << 16) | (1 << 17) | (1 << 23) | (1 << 24));
  cb(joy);
}
