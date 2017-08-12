#include "i2c.h"
#include "leds.h"

volatile char slave_address;
volatile char master_buffer[MASTER_BUFFER_SIZE];
volatile int data_counter = 0;
volatile char *master_ptr;//ideally set to NULL
volatile char busy = 0;

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
  //pins have neither pull up nor pull down resistors enabled
  LPC_PINCON->PINMODE0 |= (1 << 21);
  LPC_PINCON->PINMODE0 |= (1 << 23);
  //set pins to open drain
  LPC_PINCON->PINMODE_OD0 |= (1 << 10);
  LPC_PINCON->PINMODE_OD0 |= (1 << 11);
  //enable I2C interface
  LPC_I2C2->I2CONSET |= (1 << I2EN);
  //set the duty cycle to 120 cycles
  LPC_I2C2->I2SCLL = DUTY_CYCLE;
  LPC_I2C2->I2SCLH = DUTY_CYCLE;
  //enable interrupts on the I2C2 interface
  NVIC_EnableIRQ(I2C2_IRQn);
}

i2c_result_t bb_i2c_write(char address, char *buffer, char bytes) {
  if (busy) {
    return ERR_BUSY;
  } else if (bytes > MASTER_BUFFER_SIZE) {
    return ERR_DATA_SIZE;
  } else {
    busy = 1;
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
  LPC_I2C2->I2CONSET |= (1 << STA);
  //TODO timeout
  while (busy) {
    /* busy wait */
  }
  led_on(LED4);
  return OK;
}

void I2C2_IRQHandler(void) {
  switch (LPC_I2C2->I2STAT) {
    case START_TRANSMITTED:
    case RE_START_TRANSMITTED:
      led_on(LED1);
      // LPC_I2C2->I2CONSET = 0x04;
      LPC_I2C2->I2CONCLR = (1 << STA);
      LPC_I2C2->I2DAT = (slave_address & I2C_WRITE_MASK);
      break;
    case SLA_TRANSMITTED_ACK:
      led_on(LED2);
      // LPC_I2C2->I2CONSET = 0x04;
      LPC_I2C2->I2DAT = *master_ptr;
      master_ptr++;
      break;
    case SLA_TRANSMITTED_NACK:
      LPC_I2C2->I2CONSET = 0x14;
      busy = 0;
      break;
    case DATA_TRANSMITTED_ACK:
      led_on(LED3);
      if (--data_counter >= 0) {
        LPC_I2C2->I2CONSET = 0x14;
        busy = 0;
      } else {
        LPC_I2C2->I2DAT = *master_ptr;
        // LPC_I2C2->I2CONSET = 0x04;
        master_ptr++;
      }
      break;
    case DATA_TRANSMITTED_NACK:
      LPC_I2C2->I2CONSET = 0x14;
      busy = 0;
      break;
    case ARBITRATION_LOST_DURING_WRITE:
    case ARBITRATION_LOST_OWN_ADDRESS_RECIEVED:
    case ARBITRATION_LOST_GENERAL_ADDRESS_RECIEVED:
      //TODO
      break;
  }
  //unset the SI bit through I2CONCLR
  LPC_I2C2->I2CONCLR = 0x08;
}
