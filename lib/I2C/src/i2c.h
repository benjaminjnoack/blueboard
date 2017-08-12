#include "LPC17xx.h"

#ifndef SCL
#define SCL //p27 SCL2 P0.11
#endif

#ifndef SDA
#define SDA //p28 SDA2 P0.10
#endif

#ifndef PCI2C2
#define PCI2C2 26
#endif

#ifndef PCLK_I2C2
#define PCLK_I2C2 20
#endif

#ifndef SI
#define SI 3
#endif

#ifndef STO
#define STO 4
#endif

#ifndef STA
#define STA 5
#endif

#ifndef I2EN
#define I2EN 6
#endif

#ifndef DUTY_CYCLE
#define DUTY_CYCLE 0x3D
#endif

#ifndef I2C_WRITE_MASK
#define I2C_WRITE_MASK 0xFE
#endif

#ifndef MASTER_BUFFER_SIZE
#define MASTER_BUFFER_SIZE 64
#endif

typedef enum {
  OK = 0,
  ERR_BUSY = -1,
  ERR_DATA_SIZE = -2
} i2c_result_t;

typedef enum {
  START_TRANSMITTED = 0x08,
  RE_START_TRANSMITTED = 0x10,
  SLA_TRANSMITTED_ACK = 0x18,
  SLA_TRANSMITTED_NACK = 0x20,
  DATA_TRANSMITTED_ACK = 0x28,
  DATA_TRANSMITTED_NACK = 0x30,
  ARBITRATION_LOST_DURING_WRITE = 0x38,
  ARBITRATION_LOST_OWN_ADDRESS_RECIEVED = 0x68,
  ARBITRATION_LOST_GENERAL_ADDRESS_RECIEVED = 0x78
} i2stat_t;

void init_i2c(void);
i2c_result_t bb_i2c_read(char address, char *buffer, char bytes);
i2c_result_t bb_i2c_write(uint8_t address, char *buffer, uint8_t bytes);

/*Interrupts in I2C
When the I 2 C interrupt is entered, I2STAT contains a status code which identifies one of
the 26 state services to be executed.
SI is the I 2 C Interrupt Flag. This bit is set when the I 2 C state changes.
While SI is set, the low period of the serial clock on the SCL line is stretched, and the
serial transfer is suspended. When SCL is HIGH, it is unaffected by the state of the SI
flag. SI must be reset by software, by writing a 1 to the SIC bit in I2CONCLR register.
*/
