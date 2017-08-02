#include "adc.h"

void init_adc(void) {
  LPC_SC->PCONP |= (1 << PCADC);  // Power the ADC
  LPC_ADC->ADCR = (0x4 << 8)      // Divide incoming clock by (4+1), giving 4.8MHz
         | (0x0 << BURST)         // BURST = 0, conversions under software control
         | (0x1 << PDN);          // PDN = 1, enables power
}

void init_ain(ain_t ain) {
  //TODO set the pin to input
  switch (ain) {
    case AD0:
      LPC_PINCON->PINSEL1 |= (0x1 << 14);
      break;
    case AD1:
      LPC_PINCON->PINSEL1 |= (0x1 << 16);
      break;
    case AD2:
      LPC_PINCON->PINSEL1 |= (0x1 << 18);
      break;
    case AD3:
      LPC_PINCON->PINSEL1 |= (0x1 << 20);
      break;
    case AD4:
      LPC_PINCON->PINSEL3 |= (0x3 << 28);
      break;
    case AD5:
      LPC_PINCON->PINSEL3 |= (0x3 << 30);
      break;
    case AD6:
      LPC_PINCON->PINSEL0 |= (0x1 << 7);
      break;
    case AD7:
      LPC_PINCON->PINSEL0 |= (0x1 << 5);
      break;
  }
}

int read_ain(ain_t ain) {
  int ADCdata;
  LPC_ADC->ADCR = (LPC_ADC->ADCR & 0xFFFFFF00) | (1 << ain);
  LPC_ADC->ADCR |= AD0CR_START_MASK;
  while ((LPC_ADC->ADGDR & AD0GDR_DONE_MASK) == 0) ;
  ADCdata = LPC_ADC->ADGDR;
  LPC_ADC->ADCR &= AD0CR_STOP_MASK;
  ADCdata = (ADCdata >> 4) & ADC_DATA_MASK;
  return ADCdata;
}
