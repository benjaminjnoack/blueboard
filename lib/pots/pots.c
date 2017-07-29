#include "pots.h"

void init_pots(void) {
  FIO1DIR3 &= (~POT1 & ~POT2);
  PINSEL3 |= 0xF0000000;  // p1.30 -> AD0.4 and p1.31 -> AD0.5
  PCONP |= (1 << 12);     // Power the ADC
  AD0CR = (0x4 << 8)      // Divide incoming clock by (4+1), giving 4.8MHz
         | (0x0 << 16)    // BURST = 0, conversions under software control
         | (0x1 << 21);   // PDN = 1, enables power
}

int read_pot(pot_t pot) {
  int ADCdata;
  switch (pot) {
    case POT1:
      AD0CR = (AD0CR & 0xFFFFFF00) | (1 << 4);
      break;
    case POT2:
      AD0CR = (AD0CR & 0xFFFFFF00) | (1 << 5);
      break;
  }

  AD0CR |= AD0CR_START_MASK;
  while ((AD0GDR & AD0GDR_DONE_MASK) == 0) {
    /*test DONE bit, wait till it’s 1*/
  }
  ADCdata = AD0GDR;
  AD0CR &= AD0CR_STOP_MASK;
  ADCdata = (ADCdata >> 4) & ADC_DATA_MASK;//Right justify and mask
  return ADCdata;
}

//TODO read_pot_async (0x98 ADC A/D Converter end of conversion vector table entry)
