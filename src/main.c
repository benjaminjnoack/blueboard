#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();
  init_mma7760();

  while (1) {
    read_mma7760_axis(Y_AXIS);
    delay();
  }

  return 0;
}
