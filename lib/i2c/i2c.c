#include "i2c.h"

volatile char slave_address;
volatile char master_buffer[MASTER_BUFFER_SIZE];
volatile int data_counter = 0;
volatile char *master_ptr;
volatile i2c_mode_t mode = IDLE;
volatile i2c_result_t i2c_result;
//private function
void run_i2C(uint8_t address, uint8_t bytes);

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

i2c_result_t read_i2c(uint8_t address, char *buffer, uint8_t bytes) {
  if (mode) {
    return I2C_ERR_BUSY;
  } else if (bytes > MASTER_BUFFER_SIZE) {
    return I2C_ERR_DATA_SIZE;
  }

  mode = READ;
  address = ((address << 1) | 0x01);
  run_i2C(address, bytes);
  // move data to buffer
  for (uint8_t i = 0; i < bytes; i++) {
    buffer[i] = master_buffer[i];
  }

  return i2c_result;
}

i2c_result_t write_i2c(uint8_t address, char *buffer, uint8_t bytes) {
  if (mode) {
    return I2C_ERR_BUSY;
  } else if (bytes > MASTER_BUFFER_SIZE) {
    return I2C_ERR_DATA_SIZE;
  }

  mode = WRITE;
  for (uint8_t i = 0; i < bytes; i++) {
    master_buffer[i] = buffer[i];
  }
  address = (address << 1);
  run_i2C(address, bytes);
  return i2c_result;
}

i2c_result_t read_i2c_register(uint8_t address, char reg, uint8_t bytes, char *dest)
{
  if (mode) {
    return I2C_ERR_BUSY;
  } else if (bytes > MASTER_BUFFER_SIZE) {
    return I2C_ERR_DATA_SIZE;
  }

  mode = READ_REGISTER;
  address = (address << 1);
  master_buffer[0] = reg;
  run_i2C(address, bytes);

  for(uint8_t i = 0; i < bytes; i++) {
    dest[i] = master_buffer[i];
  }

  return i2c_result;
}

void run_i2C(uint8_t address, uint8_t bytes) {
  slave_address = address;
  master_ptr = master_buffer;
  data_counter = bytes;
  LPC_I2C2->I2CONSET = STA;
  while (mode) {
    /* busy wait */
  }
}

void I2C2_IRQHandler(void) {
  switch (LPC_I2C2->I2STAT) {
    case TX_START:
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
    case TX_RESTART:
      LPC_I2C2->I2CONCLR = (STA | SI);
      if (mode == READ_REGISTER) {
        LPC_I2C2->I2DAT = (slave_address | 0x1);
      }
      break;
    case TX_SLAW_RX_ACK:
      LPC_I2C2->I2CONCLR = SI;
      LPC_I2C2->I2DAT = *master_ptr;
      if (mode == WRITE) {
        master_ptr++;
        data_counter--;
      }
      break;
    case TX_SLAW_RX_NAK:
      LPC_I2C2->I2CONSET = (AA | STO);
      i2c_result = I2C_ADDR_NAK;
      mode = IDLE;
      LPC_I2C2->I2CONCLR = SI;
      break;
    case TX_DATAW_RX_ACK:
      LPC_I2C2->I2CONCLR = SI;
      if (mode == READ_REGISTER) {
        LPC_I2C2->I2CONSET = STA;
      } else {
        if (data_counter--) {
          LPC_I2C2->I2DAT = *master_ptr++;
        } else {
          LPC_I2C2->I2CONSET = (AA | STO);
          i2c_result = I2C_OK;
          mode = IDLE;
        }
      }
      break;
    case TX_DATAW_RX_NAK:
      LPC_I2C2->I2CONSET = (AA | STO);
      i2c_result = I2C_DATA_NAK;
      mode = IDLE;
      LPC_I2C2->I2CONCLR = SI;
      break;
    case TX_SLAR_RX_ACK:
      LPC_I2C2->I2CONCLR = SI;
      data_counter--;
      if (data_counter) {
        LPC_I2C2->I2CONSET = AA;
      } else {
        LPC_I2C2->I2CONCLR = AA;
      }
      break;
    case TX_SLAR_RX_NAK:
      LPC_I2C2->I2CONSET = (AA | STO);
      i2c_result = I2C_ADDR_NAK;
      mode = IDLE;
      LPC_I2C2->I2CONCLR = SI;
      break;
    case TX_DATAR_RX_ACK:
      if (--data_counter) {
        LPC_I2C2->I2CONCLR = SI;
        i2c_result = I2C_OK;
        mode = IDLE;
      } else {
        LPC_I2C2->I2CONCLR = (AA | SI);
      }
      *master_ptr++ = LPC_I2C2->I2DAT;
      break;
    case TX_DATAR_RX_NAK:
      LPC_I2C2->I2CONCLR = SI;
      i2c_result = I2C_DATA_NAK;
      mode = IDLE;
      LPC_I2C2->I2CONSET = (AA | STO);
      *master_ptr = LPC_I2C2->I2DAT;
      break;
    default:
      LPC_I2C2->I2CONSET = (AA | STO);
      i2c_result = I2C_ERR_UNKNOWN;
      mode = IDLE;
      LPC_I2C2->I2CONCLR = SI;
      break;
  }
}
