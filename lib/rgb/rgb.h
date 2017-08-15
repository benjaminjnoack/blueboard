#include "LPC17xx.h"

struct RGB {
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

void init_rgb(void);
void set_rgb(struct RGB *rgb);
