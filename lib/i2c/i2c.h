#include "LPC17xx.h"

#ifndef SCL
#define SCL //p27 SCL2 P0.11
#endif

#ifndef SDA
#define SDA //p28 SDA2 P0.10
#endif

#ifndef PCI2C2
#define PCI2C2 (1 << 26)
#endif

#ifndef PCLK_I2C2
#define PCLK_I2C2 20
#endif

#ifndef AA
#define AA (0x1 << 2)
#endif

/*
SI is the I 2 C Interrupt Flag. This bit is set when the I 2 C state changes.
While SI is set, the low period of the serial clock on the SCL line is stretched, and the
serial transfer is suspended. When SCL is HIGH, it is unaffected by the state of the SI
flag. SI must be reset by software, by writing a 1 to the SIC bit in I2CONCLR register.
*/
#ifndef SI
#define SI (0x1 << 3)
#endif

#ifndef STO
#define STO (0x1 << 4)
#endif

#ifndef STA
#define STA (0x1 << 5)
#endif

#ifndef I2EN
#define I2EN (0x1 << 6)
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
  I2C_OK,
  I2C_ERR_BUSY,
  I2C_ERR_DATA_SIZE,
  I2C_ADDR_NAK,
  I2C_DATA_NAK,
  I2C_ERR_UNKNOWN
} i2c_result_t;

typedef enum {
  IDLE,
  READ,
  READ_REGISTER,
  WRITE
} i2c_mode_t;

typedef enum {
  TX_START = 0x08,
  TX_RESTART = 0x10,
  TX_SLAW_RX_ACK = 0x18,
  TX_SLAW_RX_NAK = 0x20,
  TX_DATAW_RX_ACK = 0x28,
  TX_DATAW_RX_NAK = 0x30,
  TX_SLAR_RX_ACK = 0x40,
  TX_SLAR_RX_NAK = 0x48,
  TX_DATAR_RX_ACK = 0x50,
  TX_DATAR_RX_NAK = 0x58
} i2stat_t;

void init_i2c(void);
i2c_result_t read_i2c(uint8_t address, char *buffer, uint8_t bytes);
i2c_result_t write_i2c(uint8_t address, char *buffer, uint8_t bytes);
i2c_result_t read_i2c_register(uint8_t address, char reg, uint8_t bytes, char *dest);
