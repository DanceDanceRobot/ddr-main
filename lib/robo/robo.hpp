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

    // コマンド入力に対応して呼ぶ
    void go_up();
    void go_down();
    void go_left();
    void go_right();
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

    BMX055 gyro_sens; // ジャイロ

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

};