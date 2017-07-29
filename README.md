# BlueBoard

BlueBoard is a C library for the [LPC1768](https://developer.mbed.org/platforms/mbed-LPC1768/) [mbed application board](https://developer.mbed.org/cookbook/mbed-application-board).

__Complete__
* [LEDs](https://github.com/benjaminjnoack/blueboard/tree/master/lib/leds)
* [RGB LED](https://github.com/benjaminjnoack/blueboard/tree/master/lib/rgb)
* [Pots](https://github.com/benjaminjnoack/blueboard/tree/master/lib/pots)

__In Progress__
* Joystick

__Planned__
* Port
* GPIO
* Speaker
* PWM
* DAC
* ADC
* I2C
* SPI
* UART
* USBHost
* USBDevice
* XBee
* RN-XV
* RN42-XV
* Ethernet
* *special guest* UZB

## Notes

Example programs in every header file

IRQ implementation requires setting the handler's address in the vector table (I think).
The addresses in the vector table are 4 bytes (32 bits)
platformio supports cmsis...I really need to support them!
Maybe __FIOSET__ should be used for output pins instead of __FIOPIN__
Notation like `7:0` means from 7 (MSB) to 0 (LSB)
AD0CR |= 0x04; did not work but AD0CR |= (1 << 4); did
