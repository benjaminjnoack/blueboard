#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();
  init_mma7760();
  char buf[3];
  while (1) {
    read_mma7760_xyz(buf);
    delay();
  }

  return 0;
}
