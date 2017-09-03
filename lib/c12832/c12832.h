#include "LPC17xx.h"
#include "spi.h"
#include "timer.h"

//A0 p8 P0.6/SSEL1 high = display, low = command
#ifndef C12832_A0
#define C12832_A0 (1 << 6)
#endif
//RES p6 P0.8 active low
#ifndef C12832_RES
#define C12832_RES (1 << 0)
#endif
//nCS p11 P0.18 active low
#ifndef C12832_CS
#define C12832_CS (1 << 2)
#endif

void init_c12832(void);
void clear_c12832(void);
void display_c12832_all_points(char on_off);
void set_c12832_column_address(char col);//0-131
void set_c12832_cursor(char page, char col);
void set_c12832_page_address(char page_address);//0-8
//TODO void set_c12832_start_line(char line);//0-63
void write_c12832(char data);
void write_c12832_cmd(char cmd);
void write_c12832_data(char data);
