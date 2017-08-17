#include "LPC17xx.h"
/*
MOSI p5 P0.9/MOSI1
RESET p6 P0.8/MISO1 reset low
SCLK p7 P0.7/SCK1
A0 p8 P0.6/SSEL1 high = display, low = command
nCS p11 P0.18/MOSI0/MOSI1 should be kept high and driven low
*/

#ifndef BUSY
#define BUSY (1 << 4)
#endif

#ifndef CPHA//clock out phase
#define CPHA (1 << 7)
#endif

#ifndef CPOL//clock polarity high
#define CPOL (1 << 6)
#endif

#ifndef CS
#define CS (1 << 2)
#endif

#ifndef DSS//data select size 8 bits
#define DSS 0x07
#endif

#ifndef PINMODE_MOSI1
#define PINMODE_MOSI1 (1 << 19)
#endif

#ifndef PINSEL_MOSI1
#define PINSEL_MOSI1 (1 << 17)
#endif

#ifndef PCSSP1
#define PCSSP1 10
#endif

#ifndef PINMODE_SCK1
#define PINMODE_SCK1 (1 << 15)
#endif

#ifndef PINSEL_SCK1
#define PINSEL_SCK1 (1 << 15)
#endif

#ifndef SSE
#define SSE (1 << 1)
#endif

void init_spi(void);
char write_spi(char data);
