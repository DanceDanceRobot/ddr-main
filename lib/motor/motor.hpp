#pragma once

#include <Arduino.h>
#include <stdbool.h>
#include "../board_data/board_pins.hpp"

constexpr uint32_t PWM_FRQ = 78125;
constexpr uint32_t PWM_WIDTH = 10;
constexpr uint32_t PWM_RESOL = 1024; //分解能

class DRIVER{
private:
    const driver_pin_t &pin;
public:
    DRIVER(const driver_pin_t &_pin):pin(_pin){
    }

    void init(void);
    void reset(void);

    //inline functions
    bool is_error(void){
        return digitalRead((int)pin.ERR);
    }
};

//motor control by phase mode
class MOTOR{
private:
    const float motor_k;
    const motor_pin_t &pin;
public:
    MOTOR(const motor_pin_t &_pin,float _motor_k)
        :pin(_pin),motor_k(_motor_k/2){
    }

    void init(void);
    void out(float duty); //-1~1
    void free(void);
};