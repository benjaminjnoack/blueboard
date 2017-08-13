#include "LPC17xx.h"

//Configuration register: contains a single 8-bit data byte;
//to set the device operating condition; default = 0.
#ifndef LM75B_CONF_REG
#define LM75B_CONF_REG 0x01
#endif

#ifndef LM75B_SHUTDOWN
#define LM75B_SHUTDOWN 0x01
#endif

#ifndef LM75B_SLAVE_ADDRESS
#define LM75B_SLAVE_ADDRESS 0x90
#endif

/*
Temperature register:
contains two 8-bit data bytes to store the measured Temp data.
At power-up, the Pointer value is equal to 00 and the Temp register is selected;
users can then read the Temp data without specifying the pointer byte.
However, the first temperature reading will be incorrect and must be ignored.
Subsequent reads of the temperature register will be correct.
*/
#ifndef LM75B_TEMP_REG
#define LM75B_TEMP_REG 0x00
#endif

typedef enum {
  LM75B_SHUTDOWN_MODE,
  LM75B_NORMAL_MODE
} lm75b_mode_t;

lm75b_mode_t init_lm75b(void);
float read_lm75b(void);
lm75b_mode_t shutdown_lm75b(void);
lm75b_mode_t normal_lm75b(void);
