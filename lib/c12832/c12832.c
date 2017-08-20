#include "c12832.h"

void init_c12832(void) {
  //set command
  gpio_clear(C12832_A0);
  //release chip select
  gpio_set(C12832_CS);
  //assert reset
  gpio_clear(C12832_RES);
  timer_us(50);
  //clear reset
  gpio_set(C12832_RES);
  timer_us(5000);
  //Start Sequence
  c12832_write_cmd(0xAE);
  c12832_write_cmd(0xA2);
  c12832_write_cmd(0xA0);
  c12832_write_cmd(0xC8);
  c12832_write_cmd(0x22);
  c12832_write_cmd(0x2F);
  c12832_write_cmd(0x40);
  c12832_write_cmd(0xAF);
  c12832_write_cmd(0x81);
  c12832_write_cmd(0x17);
  c12832_write_cmd(0xA6);
  //TODO locate(0,0)
}

void c12832_display_on() {
  c12832_write_cmd(0xAF);
}

void c12832_start_line_set(char line) {
  c12832_write_cmd(((line &= 0x3F) | 0x40));
}

char write_c12832(char data) {
  LPC_GPIO0->FIOCLR2 |= C12832_CS;
  char read = write_spi(data);
  LPC_GPIO0->FIOSET2 |= C12832_CS;
  return read;
}

char c12832_write_cmd(char cmd) {
  LPC_GPIO0->FIOCLR0 |= C12832_A0;
  return write_c12832(cmd);
}

char c12832_write_data(char data) {
  LPC_GPIO0->FIOSET0 |= C12832_A0;
  return write_c12832(data);
}
