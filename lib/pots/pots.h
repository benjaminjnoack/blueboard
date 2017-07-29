#include "registers.h"

// int main(int argc, char const *argv[]) {
//
//   init_leds();
//   init_pots();
//
//   while (1) {
//     led_off(LED1);
//     led_off(LED2);
//     led_off(LED3);
//     led_off(LED4);
//
//     int ADCdata = read_pot(POT1);
//
//     if (ADCdata > 1000) {
//       led_on(LED1);
//     }
//     if (ADCdata > 2000) {
//       led_on(LED2);
//     }
//     if (ADCdata > 3000) {
//       led_on(LED3);
//     }
//     if (ADCdata > 4000) {
//       led_on(LED4);
//     }
//
//     delay();
//   }
//   return 0;
// }

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
