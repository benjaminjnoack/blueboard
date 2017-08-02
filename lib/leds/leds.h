#include "LPC17xx.h"

typedef enum {
  LED1 = (1 << 2),
  LED2 = (1 << 4),
  LED3 = (1 << 5),
  LED4 = (1 << 7)
} led_t;

void init_leds();
void led_on(led_t LEDS);
void led_off(led_t LEDS);
