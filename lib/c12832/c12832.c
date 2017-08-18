#include "c12832.h"

void init_c12832(void) {
  //set chip select as output
  LPC_GPIO0->FIODIR0 |= A0;
  //set high
  LPC_GPIO0->FIOSET0 |= A0;
  //set A0 as output
  LPC_GPIO0->FIODIR2 |= CS;
  //init low for command
  LPC_GPIO0->FIOCLR2 |= CS;
}

void c12832_display_on() {

}

char write_c12832(char data) {
  LPC_GPIO0->FIOCLR2 |= CS;
  char read = write_spi(data);
  LPC_GPIO0->FIOSET2 |= CS;
  return read;
}

char c12832_write_cmd(char cmd) {
  LPC_GPIO0->FIOCLR0 |= A0;
  return write_c12832(cmd);
}

char c12832_write_data(char data) {
  LPC_GPIO0->FIOSET0 |= A0;
  return write_c12832(data);
}
