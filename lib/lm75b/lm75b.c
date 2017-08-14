#include "lm75b.h"
#include "i2c.h"

lm75b_mode_t lm75b_mode = LM75B_NORMAL_MODE;
char temperature[2];

lm75b_mode_t init_lm75b(void) {
  read_lm75b();
  return lm75b_mode;
}

float read_lm75b(void) {
  read_i2c(LM75B_SLAVE_ADDRESS, &temperature[0], 2);
  uint16_t temp = (temperature[0] << 8);
  temp |= (temperature[1] & 0xFF);
  temp = (temp >>  5);
  return (float) (temp * 0.125);
}

lm75b_mode_t shutdown_lm75b(void) {
  //TODO shutdown, leave pointer at conf
  return lm75b_mode;
}

lm75b_mode_t normal_lm75b(void) {
  //TODO normal mode, move pointer to temp
  return lm75b_mode;
}
