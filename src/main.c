#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_spi();
  init_c12832();

  while (1) {
    for (uint8_t i = 0; ; i++) {
      if (i % 2) {
        c12832_write_cmd(i);//odd
      } else {
        c12832_write_data(i);//even
      }
    }
  }

  return 0;
}
