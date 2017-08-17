#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_spi();
  init_c12832();

  while (1) {
    for (uint8_t i = 0; ; i++) {
      write_c12832(i);
    }
  }

  return 0;
}
