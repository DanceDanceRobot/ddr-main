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

#include <FastLED.h>
 
#define numberOfLEDs 6
#define controlPin 23
 
/*

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 51 bytes
  { 255,5,0,0,0,44,0,16,31,1,5,0,16,34,30,30,2,26,31,1,
  0,7,13,12,12,2,31,76,0,1,0,44,13,12,12,2,31,82,0,1,
  3,25,78,12,12,2,31,115,101,116,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_1_x; // from -100 to 100  
  int8_t joystick_1_y; // from -100 to 100  
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t button_2; // =1 if button pressed, else =0 
  uint8_t button_3; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

*/


#include "standalone_udp_rx.hpp"

ROBO robo;
StdAlnUdpRx udp_rx;

CRGB leds[numberOfLEDs];

void setup() {
  //RemoteXY_Init (); 
  
  udp_rx.init();

  FastLED.addLeds<WS2812B, controlPin, GRB>(leds, numberOfLEDs);
  for (int thisLED = 0; thisLED < numberOfLEDs; thisLED++) {
    if (thisLED <= 1 || 4 <= thisLED) {
      leds[thisLED].r = 200;
      leds[thisLED].g = 200;
      leds[thisLED].b = 0;
    } else {
      leds[thisLED].r = 255;
      leds[thisLED].g = 0;
      leds[thisLED].b = 0;
    }
    
    FastLED.show();
  }

  robo.init();
}

void loop() {
  //RemoteXY_Handler ();

  // robo.set_vel_x(RemoteXY.joystick_1_y / 100);
  // robo.set_vel_y(RemoteXY.joystick_1_x / -100);
  // if (RemoteXY.button_1 == 1) {
  //   robo.turn_left();
  // }
  // if (RemoteXY.button_2 == 1) {
  //   robo.turn_right();
  // }


  static int cnt = 0;

  udp_rx.update();
  if(udp_rx.is_updated()){
    cnt = 0;
    ConnectionData data = udp_rx.read();
    Serial.print(data.serialize());
    robo.set_velocity(0.0, 0.0);
    if(data.data.up) {
      Serial.print(" up");
      robo.set_vel_x(1.0);
    }
    if(data.data.down) {
      Serial.print(" down");
      robo.set_vel_x(-1.0);
      };
    if(data.data.left) {
      Serial.print(" left");
      robo.set_vel_y(1.0);
      };
    if(data.data.right) {
      Serial.print(" right");
      robo.set_vel_y(-1.0);
      };
    if(data.data.l_turn) {
      Serial.print(" l_turn");
      robo.turn_left();
      };
    if(data.data.r_turn) {
      Serial.print(" r_turn");
      robo.turn_right();
      };
  }
  else {
    //Serial.println(cnt);
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
//   static int cnt = 0;
//   cnt++;
//   data.reset();
//   if(cnt < 1000){
//     data.up();
//     data.up();
//   }
//   else if(cnt < 2000){
//     data.left();
//     data.up();
//   }
//   else if(cnt < 3000){
//     data.down();
//     data.up();
//   }
//   else if(cnt < 4000){
//     data.right();
//     data.up();
//   }
//   else if(cnt < 7000){
//     cnt = 0;
//   }
//   udp_tx.write(data);
//   if(!udp_tx.get_wifi_flg()) udp_tx.init();
//   ets_delay_us(1000);
// }