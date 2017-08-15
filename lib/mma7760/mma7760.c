#include "mma7760.h"
#include "i2c.h"

mma7760_mode_t mma7760_mode = MMA7760_STANDBY;

int8_t parse_axis_reading(char axis_reading) {
  if (axis_reading & MMA7760_XYZ_ALERT) {
    return MMA7760_XYZ_INVALID;
  } else if (axis_reading & MMA7760_XYZ_NEGATIVE){
    return (~axis_reading & 0x3F) + 1;
  } else {
    return axis_reading;
  }
}

mma7760_mode_t init_mma7760(void) {
  //set mode to active
  char set_active_buf[2] = {MMA7760_MODE, MMA7760_ACTIVE};
  if (write_i2c(MMA7760_ADDRESS, set_active_buf, 2) == I2C_OK) {
    mma7760_mode = MMA7760_ACTIVE;
  }

  return mma7760_mode;
}

int8_t read_mma7760_axis(mma7760_axis_t axis) {
  char axis_reading;
  read_i2c_register(MMA7760_ADDRESS, axis, 0x01, &axis_reading);
  return parse_axis_reading(axis_reading);
}

void read_mma7760_xyz(char *buf) {
  read_i2c_register(MMA7760_ADDRESS, X_AXIS, 3, buf);
  for (int8_t i = 0; i < 3; i++) {
    buf[i] = parse_axis_reading(buf[i]);
  }
}
