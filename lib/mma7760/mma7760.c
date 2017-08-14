#include "mma7760.h"
#include "i2c.h"

mma7760_mode_t mma7760_mode = MMA7760_STANDBY;

mma7760_mode_t init_mma7760(void) {
  //set mode to active
  char set_active_buf[2] = {MMA7760_MODE, MMA7760_ACTIVE};
  write_i2c(MMA7760_ADDRESS, set_active_buf, 2);
  //TODO check result
  mma7760_mode = MMA7760_ACTIVE;
  //TODO set the sample rate
  return MMA7760_ACTIVE;
}

int8_t read_mma7760_axis(mma7760_axis_t axis) {
  char axis_reading;
  read_i2c_register(MMA7760_ADDRESS, axis, 0x01, &axis_reading);
  //TODO parse the result
  return 0;//TODO
}
