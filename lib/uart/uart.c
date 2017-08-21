#include "uart.h"
#include "gpio.h"

void init_uart() {
  //power UART3
  LPC_SC->PCONP |= (1 << PCUART3);
  //PCLK = CCLK
  LPC_SC->PCLKSEL1 |= (0x01 << PCLK_UART3);
  //Enable access to Divisor Latches.
  LPC_UART3->LCR |= (1 << DLAB);
  //set divisor latches for 9600
  LPC_UART3->DLL = 0x71;
  LPC_UART3->DLM = 0x02;
  //enable FIFO
  LPC_UART3->LCR |= 0x01;
  //select TXD3 and RXD3
  LPC_PINCON->PINSEL0 |= ((0x02 << 0) | (0x02 << 2));
  //select RX as output
  LPC_GPIO0->FIODIR0 |= (1 << 0);
  //set 8 bit word length
  LPC_UART3->LCR |= (0x03 << 0);
  //latch divisor
  LPC_UART3->LCR &= ~(1 << DLAB);
  //enable RBR and THRE interrupts
  // LPC_UART3->IER = 0x03;
  // //NVIC enable UART3 interrupts
  // NVIC_EnableIRQ(UART3_IRQn);
}

void tx_uart(char tx) {
  while(!((LPC_UART3->LSR) & (1 << 5))) {

  }

  LPC_UART3->THR = tx;
}

// void UART3_IRQHandler(void) {
//   // clear_gpio(PIN_8);
//   switch ((LPC_UART3->IIR & 0x0E) >> 1) {
//     case THRE:
//       break;
//     case RDA:
//       break;
//     case CTI://TODO
//       break;
//   }
//
// }
