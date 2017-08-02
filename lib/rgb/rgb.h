#include "LPC17xx.h"

typedef enum {
  BLUE, //P2.1
  GREEN,//P2.2
  RED,  //P2.3
} rgb_t;

void init_rgb(void);
void rgb_off(rgb_t rgb);
void rgb_on(rgb_t rgb);
