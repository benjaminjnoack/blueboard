#include "uart.h"
#include "gpio.h"

volatile char tx_bufs[255];
volatile char *tx_char;
volatile uint8_t uart_data_counter;

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
  LPC_UART3->IER = 0x03;
  //NVIC enable UART3 interrupts
  NVIC_EnableIRQ(UART3_IRQn);
}

void tx_uart(char tx) {
  while(!((LPC_UART3->LSR) & (1 << 5))) {
    /*busy wait*/
  }

  LPC_UART3->THR = tx;
}

void tx_uarts(const char *str, uint8_t tx_num) {
  uart_data_counter = tx_num;
  for (uint8_t i = 0; i < tx_num; i++) {
    tx_bufs[i] = str[i];
  }
  tx_char = tx_bufs;
  tx_uart(*(tx_char++));
}

//is the flag cleared?
void UART3_IRQHandler(void) {
  switch ((LPC_UART3->IIR & 0x0E) >> 1) {
    case CTI://TODO no idea
      break;
    case RDA:
      /*
      this should be paired with an attach function?
      it could buffer up the data
      then there could be a readable_uart which tells if there
      are characters in the buffer
      */
      break;
    case THRE:
      if (--uart_data_counter) {
        LPC_UART3->THR = *tx_char++;
      }
      break;
  }

}
