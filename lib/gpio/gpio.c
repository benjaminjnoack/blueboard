#include "gpio.h"

void init_gpio() {
  LPC_GPIO0->FIODIR |= (PIN_6 | PIN_8 | PIN_11 | PIN_29 | PIN_30);
}

void gpio_set(gpio_t gpio) {
  LPC_GPIO0->FIOSET |= (gpio);
}

void gpio_clear(gpio_t gpio) {
  LPC_GPIO0->FIOCLR |= (gpio);
}
