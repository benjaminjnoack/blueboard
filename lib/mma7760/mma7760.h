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
  BA_FRO_UNKNOWN,
  BA_FRO_FRONT,
  BA_FRO_BACK
} back_front_t;

typedef enum {
  PO_LA_UNKNOWN,
  PO_LA_LEFT,
  PO_LA_RIGHT,
  PO_LA_DOWN,
  PO_LA_UP
} portrait_landscape_t;

typedef enum {
  NO_TAP,
  TAP
} tap_t;

typedef enum {
  VALID,
  ALERT
} mma7760_alert_t;

//NOTE:shake is ignored
struct mma7760_tilt {
  mma7760_alert_t Alert;
  back_front_t BaFro;
  portrait_landscape_t PoLa;
  tap_t Tap;
};

struct mma7760_xyz {
  int8_t x;
  int8_t y;
  int8_t z;
};

struct mma7760_reading {
  struct mma7760_xyz xyz;
  struct mma7760_tilt tilt;
};

typedef enum {
  MMA7760_STANDBY,
  MMA7760_ACTIVE
} mma7760_mode_t;

mma7760_mode_t init_mma7760(void);
struct mma7760_reading read_mma7760();
struct mma7760_tilt read_mma7760_tilt();
struct mma7760_xyz read_mma7760_xyz();
int8_t read_mma7760_axis(mma7760_axis_t axis);
