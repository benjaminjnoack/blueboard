#include "registers.h"

typedef enum {
  RED = (1 << 3),//p23 p2.3
  GREEN = (1 << 2),//p24 p2.2
  BLUE = (1 << 1)//p25 p2.1
} rgb_t;

void init_rgb(void);
void rgb_off(rgb_t rgb);
void rgb_on(rgb_t rgb);
