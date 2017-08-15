#include "mma7760.h"
#include "i2c.h"

mma7760_mode_t mma7760_mode = MMA7760_STANDBY;

mma7760_mode_t init_mma7760(void) {
  //set mode to active
  char set_active_buf[2] = {MMA7760_MODE, MMA7760_ACTIVE};
  if (write_i2c(MMA7760_ADDRESS, set_active_buf, 2) == I2C_OK) {
    mma7760_mode = MMA7760_ACTIVE;
  }

  return mma7760_mode;
}

int8_t parse_axis_reading(char axis_reading) {
  if (axis_reading & MMA7760_XYZ_ALERT) {
    return MMA7760_XYZ_INVALID;
  } else if (axis_reading & MMA7760_XYZ_NEGATIVE){
    return (~axis_reading & 0x3F) + 1;
  } else {
    return axis_reading;
  }
}

struct mma7760_tilt parse_tilt(char tilt_reading) {
  struct mma7760_tilt tilt;
  tilt.Alert = (mma7760_alert_t) ((tilt_reading & 0x40) >> 6);
  tilt.BaFro = (back_front_t) (tilt_reading & 0x03);
  tilt.PoLa = (portrait_landscape_t) ((tilt_reading & 0x1C) >> 2);
  tilt.Tap = (tap_t) ((tilt_reading & 0x20) >> 5);
  return tilt;
}

struct mma7760_xyz parse_xyz(char *buf) {
  struct mma7760_xyz reading;
  reading.x = parse_axis_reading(buf[0]);
  reading.y = parse_axis_reading(buf[1]);
  reading.z = parse_axis_reading(buf[2]);
  return reading;
}

struct mma7760_reading read_mma7760() {
  char buf[4];
  read_i2c_register(MMA7760_ADDRESS, X_AXIS, 0x04, buf);
  struct mma7760_reading reading;
  reading.xyz = parse_xyz(buf);
  reading.tilt = parse_tilt(buf[3]);
  return reading;
}

int8_t read_mma7760_axis(mma7760_axis_t axis) {
  char axis_reading;
  read_i2c_register(MMA7760_ADDRESS, axis, 0x01, &axis_reading);
  return parse_axis_reading(axis_reading);
}

struct mma7760_tilt read_mma7760_tilt() {
  char tilt_reading;
  read_i2c_register(MMA7760_ADDRESS, 0x03, 0x01, &tilt_reading);
  return parse_tilt(tilt_reading);
}

struct mma7760_xyz read_mma7760_xyz() {
  char buf[3];
  read_i2c_register(MMA7760_ADDRESS, X_AXIS, 3, buf);
  return parse_xyz(buf);
}
