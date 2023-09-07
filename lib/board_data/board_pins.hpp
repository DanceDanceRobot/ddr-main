#pragma once

//GPIO number
enum class GPIO_num{
    //driver1
    DRIVER1_ERR = 27,
    DRIVER1_MODE = 14,
    DRIVER1_STBY = 12,

    //driver2
    DRIVER2_ERR = 4,
    DRIVER2_MODE = 2,
    DRIVER2_STBY = 15,

    //motor1
    MOTOR1_EN = 32,
    MOTOR1_PWM = 25,

    //motor2
    MOTOR2_EN = 33,
    MOTOR2_PWM = 26,
    
    //motor3
    MOTOR3_EN = 17,
    MOTOR3_PWM = 13,

    //motor4
    MOTOR4_EN = 16,
    MOTOR4_PWM = 5,

    //LED
    LED_R = 3,
    LED_G = 1,

    //LED SERIAL(for decoration LED)
    LED_SERIAL = 23,

    //BMX(gyro sensor,i2c)
    BMX_SDA = 21,
    BMX_SCL = 22,
};


struct pwm_pin_t{
  GPIO_num pin;
  uint8_t ch;
};

const pwm_pin_t motor1_pwm = {GPIO_num::MOTOR1_PWM,0};
const pwm_pin_t motor2_pwm = {GPIO_num::MOTOR2_PWM,1};
const pwm_pin_t motor3_pwm = {GPIO_num::MOTOR3_PWM,2};
const pwm_pin_t motor4_pwm = {GPIO_num::MOTOR4_PWM,3};


struct motor_pin_t{
  pwm_pin_t pwm;
  GPIO_num en;
};

const motor_pin_t MOTOR1_pin = {motor1_pwm,GPIO_num::MOTOR1_EN};
const motor_pin_t MOTOR2_pin = {motor2_pwm,GPIO_num::MOTOR2_EN};
const motor_pin_t MOTOR3_pin = {motor3_pwm,GPIO_num::MOTOR3_EN};
const motor_pin_t MOTOR4_pin = {motor4_pwm,GPIO_num::MOTOR4_EN};


struct driver_pin_t{
  GPIO_num ERR;
  GPIO_num MODE;
  GPIO_num STBY;
};

const driver_pin_t DRIVER1_pin = {
    .ERR = GPIO_num::DRIVER1_ERR,
    .MODE = GPIO_num::DRIVER1_MODE,
    .STBY = GPIO_num::DRIVER1_STBY,
};
const driver_pin_t DRIVER2_pin = {
    .ERR = GPIO_num::DRIVER2_ERR,
    .MODE = GPIO_num::DRIVER2_MODE,
    .STBY = GPIO_num::DRIVER2_STBY,
};