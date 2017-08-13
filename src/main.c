#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();
  init_lm75b();

  while (1) {
    read_lm75b();
    delay();
    delay();
    delay();
  }

  return 0;
}
