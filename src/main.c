#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_pwm();
  init_rgb();
  struct RGB rgb;
  rgb.R = 0x23;
  rgb.G = 0xFF;
  rgb.B = 0x80;
  set_rgb(&rgb);
  while (1) {

    delay();
  }

  return 0;
}
