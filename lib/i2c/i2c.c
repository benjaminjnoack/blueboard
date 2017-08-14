#include "i2c.h"

volatile char slave_address;
volatile char master_buffer[MASTER_BUFFER_SIZE];
volatile int data_counter = 0;
volatile char *master_ptr;
volatile i2c_mode_t mode = IDLE;

void init_i2c(void) {
  //power the I2C peripheral
  LPC_SC->PCONP |= PCI2C2;
  //PCLK_I2C2 = CCLK/8
  LPC_SC->PCLKSEL1 |= (0x3 << 20);
  //set the direction to output
  LPC_GPIO0->FIODIR1 |= ((0x1 << 2) | (0x1 << 3));
  //select I2C2 SDA and SCK
  LPC_PINCON->PINSEL0 |= (0x1 << 21) | (0x1 << 23);
  //pins have neither pull up nor pull down resistors
  LPC_PINCON->PINMODE0 |= (0x1 << 21) | (0x1 << 23);
  //set pins to open drain
  LPC_PINCON->PINMODE_OD0 |= (0x3 << 10);
  //enable I2C interface
  LPC_I2C2->I2CONSET = I2EN;
  //set the duty cycle to 120 cycles
  LPC_I2C2->I2SCLL = DUTY_CYCLE;
  LPC_I2C2->I2SCLH = DUTY_CYCLE;
  //enable interrupts on the I2C2 interface
  NVIC_EnableIRQ(I2C2_IRQn);
}

i2c_result_t bb_i2c_read(uint8_t address, char *buffer, uint8_t bytes) {
  if (mode) {
    return ERR_BUSY;
  } else if (bytes > MASTER_BUFFER_SIZE) {
    return ERR_DATA_SIZE;
  } else {
    mode = READ;
  }

  slave_address = address;
  master_ptr = &buffer[0];
  data_counter = bytes;
  LPC_I2C2->I2CONSET = STA;
  while (mode) {
    /* busy wait */
  }
  // move data to buffer
  for (uint8_t i = 0; i < bytes; i++) {
    buffer[i] = master_buffer[i];
  }

  return OK;
}

i2c_result_t bb_i2c_write(uint8_t address, char *buffer, uint8_t bytes) {
  if (mode) {
    return ERR_BUSY;
  } else if (bytes > MASTER_BUFFER_SIZE) {
    return ERR_DATA_SIZE;
  } else {
    mode = WRITE;
  }

  for (uint8_t i = 0; i < bytes; i++) {
    master_buffer[i] = buffer[i];
  }
  slave_address = address;
  master_ptr = &master_buffer[0];
  data_counter = bytes;
  LPC_I2C2->I2CONSET = STA;
  while (mode) {
    /* busy wait */
  }
  return OK;
}

i2c_result_t read_i2c_register(uint8_t address, char reg, uint8_t bytes) {
  if (mode) {
    return ERR_BUSY;
  } else if (bytes > MASTER_BUFFER_SIZE) {
    return ERR_DATA_SIZE;
  } else {
    mode = READ_REGISTER;
  }

  slave_address = address;
  master_buffer[0] = reg;
  master_ptr = &master_buffer[0];
  data_counter = bytes;
  LPC_I2C2->I2CONSET = STA;
  while (mode) {
    /* busy wait */
  }
  return OK;
}

void I2C2_IRQHandler(void) {
  switch (LPC_I2C2->I2STAT) {
    case START_TRANSMITTED:
      LPC_I2C2->I2CONCLR = (STA | SI);
      switch (mode) {
        case IDLE:
          //TODO
          break;
        case READ:
          LPC_I2C2->I2DAT = (slave_address | 0x1);
          break;
        case READ_REGISTER:
        case WRITE:
          LPC_I2C2->I2DAT = (slave_address & I2C_WRITE_MASK);
          break;
      }
      break;
    case RE_START_TRANSMITTED:
      LPC_I2C2->I2CONCLR = (STA | SI);
      if (mode == READ_REGISTER) {
        LPC_I2C2->I2DAT = (slave_address | 0x1);
      }
      break;
    case SLA_W_TRANSMITTED_ACK:
      LPC_I2C2->I2CONCLR = SI;
      LPC_I2C2->I2DAT = *master_ptr;
      if (mode == WRITE) {
        master_ptr++;
        data_counter--;
      }
      break;
    case SLA_W_TRANSMITTED_NACK:
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
      LPC_I2C2->I2CONCLR = SI;
      break;
    case DATA_W_TRANSMITTED_ACK:
      LPC_I2C2->I2CONCLR = SI;
      if (mode == READ_REGISTER) {
        LPC_I2C2->I2CONSET = STA;
      } else {
        if (data_counter--) {
          LPC_I2C2->I2DAT = *master_ptr++;
        } else {
          LPC_I2C2->I2CONSET = (AA | STO);
          mode = IDLE;
        }
      }
      break;
    case DATA_W_TRANSMITTED_NACK:
      LPC_I2C2->I2CONCLR = SI;
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
      break;
    case SLA_R_TRANSMITTED_ACK:
      LPC_I2C2->I2CONCLR = SI;
      LPC_I2C2->I2CONSET = AA;
      data_counter--;
      break;
    case SLA_R_TRANSMITTED_NACK:
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
      LPC_I2C2->I2CONCLR = SI;
      break;
    case DATA_R_TRANSMITTED_ACK:
      if (--data_counter) {
        LPC_I2C2->I2CONCLR = SI;
        mode = IDLE;
      } else {
        LPC_I2C2->I2CONCLR = (AA | SI);
      }
      *master_ptr++ = LPC_I2C2->I2DAT;
      break;
    case DATA_R_TRANSMITTED_NACK:
      LPC_I2C2->I2CONCLR = SI;
      mode = IDLE;
      LPC_I2C2->I2CONSET = (AA | STO);
      *master_ptr = LPC_I2C2->I2DAT;
      break;
    default:
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
      LPC_I2C2->I2CONCLR = SI;
      break;
  }
}
