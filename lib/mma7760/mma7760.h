#include "LPC17xx.h"

//7 bit address: 0x4C
#ifndef MMA7760_ADDRESS
#define MMA7760_ADDRESS 0x4C
#endif

//to write to the registers the Mode must be 0 standby
#ifndef MMA7760_MODE
#define MMA7760_MODE 0x07
#endif

#ifndef MMA7760_SR
#define MMA7760_SR 0x08
#endif

#ifndef MMA7760_TILT
#define MMA7760_TILT 0x03
#endif

#ifndef MMA7760_XOUT
#define MMA7760_XOUT 0x00
#endif

#ifndef MMA7760_YOUT
#define MMA7760_YOUT 0x01
#endif

#ifndef MMA7760_ZOUT
#define MMA7760_ZOUT 0x02
#endif

#ifndef MMA7760_XYZ_ALERT
#define MMA7760_XYZ_ALERT (1 << 6)
#endif

#ifndef MMA7760_XYZ_INVALID
#define MMA7760_XYZ_INVALID 0xFF
#endif

#ifndef MMA7760_XYZ_NEGATIVE
#define MMA7760_XYZ_NEGATIVE (1 << 5)
#endif

typedef enum {
  X_AXIS,
  Y_AXIS,
  Z_AXIS
} mma7760_axis_t;

typedef enum {
  MMA7760_STANDBY,
  MMA7760_ACTIVE
} mma7760_mode_t;

mma7760_mode_t init_mma7760(void);
void read_mma7760_xyz(char *buf);
int8_t read_mma7760_axis(mma7760_axis_t axis);
