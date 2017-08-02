#include "LPC17xx.h"

typedef enum {
  LED1,
  LED2,
  LED3,
  LED4
} led_t;

void init_leds();
void led_on(led_t LEDS);
void led_off(led_t LEDS);
