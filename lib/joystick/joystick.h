#include "registers.h"

// int main(int argc, char const *argv[]) {
//
//   init_leds();
//   init_joystick();
//   init_rgb();
//
//   while (1) {
//     rgb_off(RED);
//     led_off(LED1);
//     led_off(LED2);
//     led_off(LED3);
//     led_off(LED4);
//
//     switch (read_joystick()) {
//       case LEFT:
//         led_on(LED1);
//         break;
//       case CENTER:
//         led_on(LED1);
//         led_on(LED2);
//         led_on(LED3);
//         led_on(LED4);
//         break;
//       case DOWN:
//         led_on(LED3);
//         break;
//       case UP:
//         led_on(LED4);
//         break;
//       case RIGHT:
//         led_on(LED2);
//         break;
//       case NONE:
//         rgb_on(RED);
//         break;
//     }
//
//     delay();
//   }
//   return 0;
// }

typedef enum {
  NONE,
  LEFT,   //p13 P0.15
  CENTER, //p14 P0.16
  DOWN,   //p12 P0.17
  UP,     //p15 P0.23
  RIGHT,  //p16 P0.24
} joystick_t;

void init_joystick(void);
joystick_t read_joystick(void);
//TODO bus in
