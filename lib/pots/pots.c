#include "pots.h"

void init_pots(void) {
  LPC_GPIO1->FIODIR3 &= (~POT1 & ~POT2);//set pot pins to input
  LPC_PINCON->PINSEL3 |= 0xF0000000;  // p1.30 -> AD0.4 and p1.31 -> AD0.5
  LPC_SC->PCONP |= (1 << PCADC);     // Power the ADC
  LPC_ADC->ADCR = (0x4 << 8)      // Divide incoming clock by (4+1), giving 4.8MHz
         | (0x0 << 16)    // BURST = 0, conversions under software control
         | (0x1 << PDN);   // PDN = 1, enables power
}

int read_pot(pot_t pot) {
  int ADCdata;
  switch (pot) {
    case POT1:
      LPC_ADC->ADCR = (LPC_ADC->ADCR & 0xFFFFFF00) | (1 << 4);
      break;
    case POT2:
      LPC_ADC->ADCR = (LPC_ADC->ADCR & 0xFFFFFF00) | (1 << 5);
      break;
  }

  LPC_ADC->ADCR |= AD0CR_START_MASK;
  while ((LPC_ADC->ADGDR & AD0GDR_DONE_MASK) == 0) {
    /*test DONE bit, wait till it’s 1*/
  }
  ADCdata = LPC_ADC->ADGDR;
  LPC_ADC->ADCR &= AD0CR_STOP_MASK;
  ADCdata = (ADCdata >> 4) & ADC_DATA_MASK;//Right justify and mask
  return ADCdata;
}
