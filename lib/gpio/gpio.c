#include "gpio.h"

void init_gpio() {
  LPC_GPIO0->FIODIR |= (PIN_6 | PIN_8 | PIN_11 | PIN_29 | PIN_30);
}

void set_gpio(gpio_t gpio) {
  LPC_GPIO0->FIOSET |= (gpio);
}

void clear_gpio(gpio_t gpio) {
  LPC_GPIO0->FIOCLR |= (gpio);
}
