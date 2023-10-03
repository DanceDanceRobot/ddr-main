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
#include "standalone_udp_rx.hpp"

ROBO robo;
StdAlnUdpRx udp_rx;

void setup() {
  udp_rx.init();
  robo.init();
}

void loop() {
  static int cnt = 0;
  udp_rx.update();
  if(udp_rx.is_updated()){
    cnt = 0;
    ConnectionData data = udp_rx.read();
    if(data.data.up) robo.go_up();
    if(data.data.down) robo.go_down();
    if(data.data.left) robo.go_left();
    if(data.data.right) robo.go_right();
    if(data.data.l_turn) robo.turn_left();
    if(data.data.r_turn) robo.turn_right();
  }
  else {
    Serial.println(cnt);
    cnt++;
  }
  if(cnt>=1000) {
    robo.stop(); 
  }
  robo.execute();
  ets_delay_us(1000);
}

// #include <Arduino.h>
// #include "standalone_udp_tx.hpp"

// StdAlnUdpTx udp_tx;

// void setup() {
//   Serial.begin(115200);
//   udp_tx.init();
// }

// void loop() {
//   ConnectionData data;
//   data.down();
//   udp_tx.write(data);
//   if(!udp_tx.get_wifi_flg()) udp_tx.init();
//   ets_delay_us(1000);
// }