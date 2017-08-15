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
  AD2 = 2,  //P0.25 Analog In
  AD3,  //P0.26 Analog Out
  AD4,  //p19 P1.30 POT1
  AD5,  //p20 P1.31 POT2
} ain_t;

void init_adc(void);
void init_ain(ain_t ain);
int read_ain(ain_t ain);
uint8_t read_ain_8(ain_t ain);
