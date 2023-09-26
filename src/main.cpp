// #include <Arduino.h>
// #include "motor.hpp"
// DRIVER md1(DRIVER1_pin);
// DRIVER md2(DRIVER2_pin);
// MOTOR motor1(MOTOR1_pin,1.0f);
// MOTOR motor2(MOTOR2_pin,1.0f);
// MOTOR motor3(MOTOR3_pin,1.0f);
// MOTOR motor4(MOTOR4_pin,1.0f);
// void setup() {
//   // put your setup code here, to run once:
//   md1.init();
//   md2.init();
//   motor1.init();
//   motor2.init();
//   motor3.init();
//   motor4.init();
// }

#include <Arduino.h>
#include "robo.hpp"

ROBO robo;

void setup() {
  robo.init();
}

void loop() {
  void execute();
  ets_delay_us(1000);
}