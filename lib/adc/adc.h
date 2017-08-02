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

#ifndef BURST
#define BURST 16
#endif

#ifndef PCADC
#define PCADC 12
#endif

#ifndef PDN
#define PDN 21
#endif

typedef enum {
  AD0,  //P0.23
  AD1,  //P0.24
  AD2,  //P0.25
  AD3,  //P0.26
  AD4,  //P1.30
  AD5,  //P1.31
  AD6,  //P0.3
  AD7   //P0.2
} ain_t;

void init_adc(void);
void init_ain(ain_t ain);
int read_ain(ain_t ain);
