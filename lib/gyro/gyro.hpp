#pragma once 

#include <Arduino.h>
#include <stdbool.h>
#include "../board_data/board_pins.hpp"
#include<Wire.h>

struct xyz_t{
    float x;
    float y;
    float z;
};
class BMX055{
private:
    static constexpr uint8_t ACC_ID = 0x19; //加速度センサID
    static constexpr uint8_t GYRO_ID = 0x69; //ジャイロID
    static constexpr uint8_t MAG_ID = 0x13; //磁気センサID
    TwoWire &i2c;
public:
    BMX055(TwoWire &_i2c):i2c(_i2c){}

    void init(void);

    xyz_t read_acc(void);
    xyz_t read_gyro(void);
    xyz_t read_mag(void);
};