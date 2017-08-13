#include "i2c.h"
#include "leds.h"
#include "rgb.h"

volatile char slave_address;
volatile char master_buffer[MASTER_BUFFER_SIZE];
volatile int data_counter = 0;
volatile char *master_ptr;
volatile i2c_mode_t mode = IDLE;

void init_i2c(void) {
  //power the I2C peripheral
  LPC_SC->PCONP |= (1 << PCI2C2);
  //PCLK_I2C2 = CCLK/8
  LPC_SC->PCLKSEL1 |= (0x3 << 20);
  //set the direction to output
  LPC_GPIO0->FIODIR1 |= ((1 << 2) | (1 << 3));
  //select I2C2 SDA and SCK
  LPC_PINCON->PINSEL0 |= (1 << 21);
  LPC_PINCON->PINSEL0 |= (1 << 23);
  //pins have neither pull up nor pull down resistors
  LPC_PINCON->PINMODE0 |= (1 << 21);
  LPC_PINCON->PINMODE0 |= (1 << 23);
  //set pins to open drain
  LPC_PINCON->PINMODE_OD0 |= (1 << 10);
  LPC_PINCON->PINMODE_OD0 |= (1 << 11);
  //enable I2C interface
  LPC_I2C2->I2CONSET |= I2EN;
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
    mode = READ;
  }
  //set the address to read from
  slave_address = address;
  //copy the data to the master buffer
  for (uint8_t i = 0; i < bytes; i++) {
    master_buffer[i] = buffer[i];
  }
  //set the master_ptr to tbe first byte
  master_ptr = &master_buffer[0];
  //set the data counter;
  data_counter = bytes;
  //set the start bit
  LPC_I2C2->I2CONSET = STA;
  //TODO timeout
  while (mode) {
    /* busy wait */
  }

  return OK;
}

void I2C2_IRQHandler(void) {
  switch (LPC_I2C2->I2STAT) {
    case START_TRANSMITTED:
    case RE_START_TRANSMITTED:
      led_on(LED1);
      LPC_I2C2->I2CONCLR = STA;
      switch (mode) {
        case IDLE:
          //TODO
          break;
        case READ:
          LPC_I2C2->I2DAT = (slave_address | 1);
          break;
        case WRITE:
          LPC_I2C2->I2DAT = (slave_address & I2C_WRITE_MASK);
          break;
      }
      break;
    case SLA_W_TRANSMITTED_ACK:
      LPC_I2C2->I2DAT = *master_ptr;
      master_ptr++;
      data_counter--;
      break;
    case SLA_W_TRANSMITTED_NACK:
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
      break;
    case DATA_W_TRANSMITTED_ACK:
      if (data_counter--) {
        LPC_I2C2->I2DAT = *master_ptr;
        master_ptr++;
      } else {
        LPC_I2C2->I2CONSET = (AA | STO);
        mode = IDLE;
      }
      break;
    case DATA_W_TRANSMITTED_NACK:
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
      break;
    case SLA_R_TRANSMITTED_ACK:
      led_on(LED2);
      LPC_I2C2->I2CONSET = AA;
      break;
    case SLA_R_TRANSMITTED_NACK:
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
      break;
    case DATA_R_TRANSMITTED_ACK:
      *master_ptr = LPC_I2C2->I2DAT;
      master_ptr++;
      if (--data_counter - 1) {
        led_on(LED3);
      } else {
        LPC_I2C2->I2CONCLR = AA;
        mode = IDLE;
      }
      break;
    case DATA_R_TRANSMITTED_NACK:
      led_on(LED4);
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
      break;
    default:
      rgb_on(RED);//easy enough to connect a red led
      LPC_I2C2->I2CONSET = (AA | STO);
      mode = IDLE;
  }
  //unset the SI bit through I2CONCLR
  LPC_I2C2->I2CONCLR = SI;
}
