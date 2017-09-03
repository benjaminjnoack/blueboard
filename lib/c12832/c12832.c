#include "c12832.h"

void init_c12832(void) {
  //set control lines to output
  LPC_GPIO0->FIODIR0 |= (C12832_A0);
  LPC_GPIO0->FIODIR1 |= (C12832_RES);
  LPC_GPIO0->FIODIR2 |= (C12832_CS);
  //initialize control lines high
  LPC_GPIO0->FIOSET0 |= (C12832_A0);
  LPC_GPIO0->FIOSET1 |= (C12832_RES);
  LPC_GPIO0->FIOSET2 |= (C12832_CS);
  //assert reset
  LPC_GPIO0->FIOCLR1 |= (C12832_RES);
  timer_us(50);
  LPC_GPIO0->FIOSET1 |= (C12832_RES);
  //delay for voltage pumps to charge
  timer_us(5000);
  //start up sequence
  write_c12832_cmd(0xAE);//display off
  write_c12832_cmd(0xA2);//bias voltage
  write_c12832_cmd(0xA0);//set normal RAM address SEG output
  write_c12832_cmd(0xC8);//column normal
  write_c12832_cmd(0x22);//voltage resistor ratio
  write_c12832_cmd(0x2F);//power on
  write_c12832_cmd(0x40);//start at line 0
  write_c12832_cmd(0xAF);//display on
  write_c12832_cmd(0x81);//set contrast
  write_c12832_cmd(0x17);//set contrast
  write_c12832_cmd(0xA6);//display normal
}

void	clear_c12832(void){
	int i, j;
	for (i=0;i<4;i++) {
  	set_c12832_cursor(i,0);
  	for (j = 0; j < 128; j++) {
      write_c12832_data(0x00);
    }
	}
	set_c12832_cursor(0,0);
}

void display_c12832_all_points(char on_off) {
  on_off &= 0x01;
  write_c12832_cmd(0xA4 | on_off);
}

void set_c12832_column_address(char col) {
  col &= 0x7F;
  write_c12832_cmd(0x00+ (col & 0x0F)); 	// set column low nibble 0
	write_c12832_cmd(0x10 + (col/16)); 	// set column hi nibble 0
}

void 	set_c12832_cursor(char page, char col) {
	set_c12832_column_address(col);
	set_c12832_page_address(page);
}

void set_c12832_page_address(char page) {
  page &= 0x03;
  write_c12832_cmd(0xB0 + page); 	// set page address 0
	write_c12832_cmd(0xE0); 	//auto increment display
}

void write_c12832(char data) {
  LPC_GPIO0->FIOCLR2 |= C12832_CS;
  write_spi(data);
  LPC_GPIO0->FIOSET2 |= C12832_CS;
}

void write_c12832_cmd(char cmd) {
  LPC_GPIO0->FIOCLR0 |= C12832_A0;
  return write_c12832(cmd);
}

void write_c12832_data(char data) {
  LPC_GPIO0->FIOSET0 |= C12832_A0;
  return write_c12832(data);
}
