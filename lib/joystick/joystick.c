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
  LPC_GPIOINT->IO0IntEnR |= (LEFT | CENTER | DOWN | UP | RIGHT);
  //enable falling edge interrupts
  LPC_GPIOINT->IO0IntEnF |= (LEFT | CENTER | DOWN | UP | RIGHT);
  //enable EINT3_IRQn
  NVIC_EnableIRQ(EINT3_IRQn);
}

void EINT3_IRQHandler(void) {
  joystick_t joy;
  long stat = LPC_GPIOINT->IO0IntStatF;

  if (stat & (LEFT | CENTER | DOWN | UP | RIGHT)) {
    joy = NONE;
  } else {
    stat = LPC_GPIOINT->IO0IntStatR;
    if (stat & LEFT) {
      joy = LEFT;
    } else if (stat & CENTER) {
      joy = CENTER;
    } else if (stat & DOWN) {
      joy = DOWN;
    } else if (stat & UP) {
      joy = UP;
    } else if (stat & RIGHT) {
      joy = RIGHT;
    } else {
      joy = NONE;
    }
  }

  LPC_GPIOINT->IO0IntClr |= (LEFT | CENTER | DOWN | UP | RIGHT);
  cb(joy);
}
