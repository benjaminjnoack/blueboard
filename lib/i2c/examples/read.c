#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();

  char buf[5];

  while (1) {
    bb_i2c_read(0xA0, &buf[0], 5);
    delay();
  }

  return 0;
}
