#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_pots();
  init_pwm();
  init_rgb();
  struct RGB rgb;

  while (1) {
    rgb.R = read_pot_8(POT1);
    rgb.G = read_pot_8(POT2);
    rgb.B = 0x00;
    set_rgb(&rgb);
  }

  return 0;
}
