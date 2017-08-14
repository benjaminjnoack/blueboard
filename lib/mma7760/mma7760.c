#include "mma7760.h"
#include "i2c.h"

mma7760_mode_t mma7760_mode = MMA7760_STANDBY;

mma7760_mode_t init_mma7760(void) {
  //set mode to active
  char set_active_buf[2] = {MMA7760_MODE, (1 << 1)};
  bb_i2c_write(MMA7760_ADDRESS, set_active_buf, 2);
  //TODO check result
  mma7760_mode = MMA7760_ACTIVE;
  //TODO set the sample rate
  return MMA7760_ACTIVE;
}

int8_t read_mma7760_axis(mma7760_axis_t axis) {

  return 0;//TODO
}
