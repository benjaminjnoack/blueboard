#include "rgb.h"

void rgb_init(void) {
  FIO2DIR0 |= (RED | GREEN | BLUE);
  FIO2PIN0 |= (RED | GREEN | BLUE);
}

void rgb_off(rgb_t rgb) {
  FIO2PIN0 |= rgb;
}

void rgb_on(rgb_t rgb) {
  FIO2PIN0 &= ~rgb;
}
