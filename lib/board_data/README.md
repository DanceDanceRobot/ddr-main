# ピン定義ファイル  

[board_pins.hpp](board_pins.hpp)

## enum class GPIO_num  

ピン番号をenum してるやつ  

## pwm_pin_t  

```c
struct pwm_pin_t{
  GPIO_num pin;
  uint8_t ch;
};
```  

PWM出力ピン番号とPWM出力チャンネルをまとめたやつ  
チャネルはチャネルでenumにしてもいいかも  

## motor_pin_t  

```c
struct motor_pin_t{
  pwm_pin_t pwm;
  GPIO_num en;
};
```

モーターにPWMを送ったりするピンをまとめたやつ  
ENピンとPWMピンだけ  

## driver_pin_t  

```c
struct driver_pin_t{
  GPIO_num ERR;
  GPIO_num MODE;
  GPIO_num STBY;
};
```

モタドラICの制御ピンをまとめたやつ  