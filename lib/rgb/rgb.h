#include "LPC17xx.h"

#ifndef RED
#define RED PWM4
#endif

#ifndef GREEN
#define GREEN PWM3
#endif

#ifndef BLUE
#define BLUE PWM2
#endif

struct RGB {
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

void init_rgb(void);
void set_rgb(struct RGB *rgb);
