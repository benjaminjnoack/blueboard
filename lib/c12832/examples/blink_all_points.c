#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_timers();
  init_spi();
  init_c12832();
  clear_c12832();

  while (1) {
    display_c12832_all_points(0x01);
    timer_ms(200);
    display_c12832_all_points(0x00);
    timer_ms(200);
  }

  return 0;
}
