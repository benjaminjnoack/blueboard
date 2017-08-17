#include "c12832.h"

//TODO init A0
void init_c12832(void) {
  //set chip select as output
  LPC_GPIO0->FIODIR2 |= CS;
  //set high
  LPC_GPIO0->FIOSET2 |= CS;
}

//TODO set A0 bit
char write_c12832(char data) {
  LPC_GPIO0->FIOCLR2 |= CS;
  char read = write_spi(data);
  LPC_GPIO0->FIOSET2 |= CS;
  return read;
}
