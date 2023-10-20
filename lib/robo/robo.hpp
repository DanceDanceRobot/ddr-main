#pragma once

#include "gyro.hpp"
#include "motor.hpp"
#include "board_pins.hpp"

// x, y, 角速度 
struct velocity_t {
    float x;
    float y;
    float angular;
};

/**
 * @brief ロボットを制御するためのクラス
*/
class ROBO {
    
public:
    // コンストラクタ
    ROBO();

    // init関数
    void init();

    // 毎ループ呼ぶ関数
    void execute();

    void set_velocity(float vx, float vy);
    void set_vel_x(float vx);
    void set_vel_y(float vy);
    void turn_right();
    void turn_left();
    void stop();

    /**
     * @brief 地磁気センサから角度を算出
     * @return 地磁気センサから算出した角度
    */
    float get_angle();

    enum class states {
        STATE_STANDBY,
        STATE_STRAIGHT,
        STATE_TURN    
    };
 
private:
    velocity_t vel; // 目標速度
    float target_dir; // 目標角度
    float angle_error; // 目標角度
    float angle_offset;

    BMX055 gyro_sens; // ジャイロ
    float gyro_x_offset;
    float gyro_y_offset;

    // ドライバ
    DRIVER md1;
    DRIVER md2;

    // モータ
    // L:左側、R:右側
    // F:前側、B:後側
    MOTOR motorLF;
    MOTOR motorLB;
    MOTOR motorRF;
    MOTOR motorRB;

    // 状態
    ROBO::states state;

    void vel_to_motor();

};