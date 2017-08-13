#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();

  char buf[5] = {'h', 'e', 'l', 'l', 'o'};

  while (1) {
    i2c_result_t res = bb_i2c_write(0xA0, &buf[0], 5);
    delay();
  }

  return 0;
}
