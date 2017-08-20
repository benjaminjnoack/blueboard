#include "LPC17xx.h"
#include "spi.h"
#include "timer.h"
#include "gpio.h"

//A0 p8 P0.6/SSEL1 high = display, low = command
#ifndef C12832_A0
#define C12832_A0 PIN_6
#endif
//RES p6 P0.8 active low
#ifndef C12832_RES
#define C12832_RES PIN_8
#endif
//nCS p11 P0.18 active low
#ifndef C12832_CS
#define C12832_CS PIN_11
#endif

typedef enum {
  C12832_NOT_BUSY,
  C12832_BUSY
} c12832_busy_status_t;

typedef enum {
  C12832_REVERSE,
  C12832_NORMAL
} c12832_adc_status_t;

typedef enum {
  C12832_ON,
  C12832_OFF
} c12832_display_status_t;

typedef enum {
  C12832_OPERATING,
  C12832_RESET
} c12832_reset_status_t;

struct c12832_status {
  c12832_busy_status_t busy;
  c12832_adc_status_t adc;
  c12832_display_status_t display;
  c12832_reset_status_t reset;
};

void init_c12832(void);
void c12832_display_on();
void c12832_display_off();
void c12832_page_address_set(char page_address);//0-8
void c12832_column_address_set(char column_address);//0-131
struct c12832_status c12832_status_read();
void c12832_display_data_write(char data);
void c12832_start_line_set(char line);//0-63
char write_c12832(char data);
char c12832_write_cmd(char cmd);
char c12832_write_data(char data);
