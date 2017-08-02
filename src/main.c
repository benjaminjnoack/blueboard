#include "blueboard.h"
//NOTE: Don't forget the super loop!
int main(int argc, char const *argv[]) {
  init_dac();

  while (1) {
    for (int i = 0; i < 1024; i++) {
      write_dac(i);
    }
  }

  return 0;
}
