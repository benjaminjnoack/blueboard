#include "blueboard.h"

rgb_t rgb[] = {RED, GREEN, BLUE};

void blink(rgb_t rgb) {
  rgb_on(rgb);
  hard_delay();
  rgb_off(rgb);
  hard_delay();
}

int main(int argc, char const *argv[]) {
  rgb_init();

  while (1) {
    short i;
    for (i = 0; i < 3; i++) {
      blink(rgb[i]);
    }
    for (i = 2; i >= 0; i--) {
      blink(rgb[i]);
    }
  }
  return 0;
}
