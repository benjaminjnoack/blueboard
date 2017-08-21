#include "LPC17xx.h"
/*
attach a callback
TODO utilize scratch pad register?
*/
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
  THRE = 0x01,
  RDA = 0x02,
  RLS = 0x03,
  CTI = 0x06
} uart_interrupt_t;

void init_uart();
//TODO set_uart_baud()
void tx_uart(char tx);
int readable_uart();
char rx_uart();
