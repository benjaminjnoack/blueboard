#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_i2c();
  init_mma7760();
  struct mma7760_reading reading;
  while (1) {
    reading = read_mma7760();
    delay();
  }

  return 0;
}
