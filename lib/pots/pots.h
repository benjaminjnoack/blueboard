#include "LPC17xx.h"

#ifndef AD0CR_START_MASK
#define AD0CR_START_MASK 0x01000000
#endif

#ifndef AD0CR_STOP_MASK
#define AD0CR_STOP_MASK 0xF8FFFFFF
#endif

#ifndef AD0GDR_DONE_MASK
#define AD0GDR_DONE_MASK 0x80000000
#endif

#ifndef AD0GDR_RESULT_MASK
#define AD0GDR_RESULT_MASK 0x3FF0
#endif

#ifndef ADC_DATA_MASK
#define ADC_DATA_MASK 0x0FFF
#endif

#ifndef PCADC
#define PCADC 12
#endif

#ifndef PDN
#define PDN 21
#endif

typedef enum {
  POT1 = (0x01 << 6),  //p19 p1.30
  POT2 = (0x01 << 7)   //p20 p1.31
} pot_t;

void init_pots(void);
int read_pot(pot_t pot);
