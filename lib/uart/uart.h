#include "LPC17xx.h"

//p9 P0.0/CAN_RX1/TXD3/SDA1
#ifndef UART_TX
#define UART_TX 9
#endif
//p10 P0.1/CAN_TX1/RXD3/SCL1
#ifndef UART_RX
#define UART_RX 10
#endif

#ifndef PCUART3
#define PCUART3 25
#endif

#ifndef PCLK_UART3
#define PCLK_UART3 18
#endif
//Divisor Latch Access Bit
#ifndef DLAB
#define DLAB 7
#endif

typedef enum {
  LSR_RDR = 0x01,
  LSR_OE = 0x02,
  LSR_PE = 0x04,
  LSR_FE = 0x08,
  LSR_BI = 0x10,
  LSR_THRE = 0x20,
  LSR_TEMT = 0x40,
  LSR_RXFE = 0x80
} uart_line_status_t;

typedef enum {
  THRE = 0x01,//Transmit Holding Register Empty
  RDA = 0x02, //Receive Data Available
  RLS = 0x03, //Receive Line Status
  CTI = 0x06  //Character Time-out Indicator
} uart_int_id_t;

void init_uart(void (*callback)(char rx));
void tx_uart(char tx);
void tx_uarts(const char *str, uint8_t tx_num);
