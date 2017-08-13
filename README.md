# BlueBoard

C library for the [LPC1768](https://developer.mbed.org/platforms/mbed-LPC1768/) [mbed application board](https://developer.mbed.org/cookbook/mbed-application-board). It is build with [PlatformIO](http://platformio.org/).

__Complete__
* [ADC](https://github.com/benjaminjnoack/blueboard/tree/master/lib/adc)
* [DAC](https://github.com/benjaminjnoack/blueboard/tree/master/lib/dac)
* [I2C](https://github.com/benjaminjnoack/blueboard/tree/master/lib/i2c)
* [Joystick](https://github.com/benjaminjnoack/blueboard/tree/master/lib/joystick)
* [LEDs](https://github.com/benjaminjnoack/blueboard/tree/master/lib/leds)
* [LM7580 Temperature sensor](https://github.com/benjaminjnoack/blueboard/tree/master/lib/lm75b)
* [Pots](https://github.com/benjaminjnoack/blueboard/tree/master/lib/pots)
* [PWM](https://github.com/benjaminjnoack/blueboard/tree/master/lib/pwm)
* [RGB LED](https://github.com/benjaminjnoack/blueboard/tree/master/lib/rgb)

__In Progress__
* MMA7660 Accelerometer

__Planned__
* Analog In
* Analog Out
* SysTick
* RIT
* Speaker
* SPI
* CR12832
* UART
* USBHost
* USBDevice
* XBee
* RN-XV
* RN42-XV
* Ethernet
* *special guest* UZB

## TODO

* remove unnecessary ADC channels
* read_pot_async
* support double edge PWM
* blueboard.c (initialize() - function to set up the board as necessary)
* mode operation to lm75b
* timeout for i2c
* 7 bit i2c addresses passed as arguments, shifted over on and the R/W bit

## Difficulties

* Had to clear the start bit for I2C.
* Had to clear SI before attempting to write to DAT for I2C.

___

"Take some heart if your working on a project that no one understands, or no one appreciates.
If at the end of the day *you* appreciated it, and *you* enjoyed it, then *you won*."
~guy on the radio.
