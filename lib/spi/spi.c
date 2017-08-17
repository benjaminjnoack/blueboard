#include "spi.h"

void init_spi(void) {
  //SSP1 power/clock control
  LPC_SC->PCONP |= (1 << PCSSP1);
  //Peripheral clock CCLK/8
  LPC_SC->PCLKSEL0 |= (0x03 << 20);
  //SSP1 Clock Prescale
  LPC_SSP1->CPSR = 0x02;
  //select SCK1 MOSI1
  LPC_PINCON->PINSEL0 |= (PINSEL_MOSI1 | PINSEL_SCK1);
  //select no pull down/no pull up
  LPC_PINCON->PINSEL0 |= (PINMODE_MOSI1 | PINMODE_SCK1);
  //configure SSP1
  LPC_SSP1->CR0 |= (CPOL | CPHA | DSS);
  //enable SPI1
  LPC_SSP1->CR1 |= SSE;
}

char write_spi(char data) {
  LPC_SSP1->DR = data;
  while (LPC_SSP1->SR & BUSY) ;
  return (char)(LPC_SSP1->DR & 0xFF);
}
