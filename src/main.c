#include "blueboard.h"

int main(int argc, char const *argv[]) {
  init_dac();

  while (1) {
    for (int i = 0; i < 0x03FF; i++) {
      write_dac(i);
    }
  }

  return 0;
}
