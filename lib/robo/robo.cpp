#include "robo.hpp"
#include <Wire.h>
#include <math.h>

ROBO::ROBO() :
    gyro_sens(Wire),
    md1(DRIVER1_pin),
    md2(DRIVER2_pin),
    /**
     * #debug モータ、どれがどこにつながってるの？
     * とりあえず右側だけ反転用係数
    */

   /**       
    * 
    * 
    *       M1
   */
    motorLF(MOTOR4_pin, 1.0f),
    motorLB(MOTOR3_pin, 1.0f),
    motorRF(MOTOR1_pin, 1.0f),
    motorRB(MOTOR2_pin, 1.0f),

    vel{0, 0, 0},
    target_dir(0),
    angle_error(0),
    gyro_x_offset(0),
    gyro_y_offset(0),
    angle_offset(0),
    direction(0),

    state(states::STATE_STANDBY)
{}

void ROBO::init()
{
    Serial.begin(115200);
    // // ジャイロ
    Wire.begin();
    gyro_sens.init();

    // ドライバ
    md1.init();
    md2.init();

    motorLF.init();
    motorLB.init();
    motorRF.init();
    motorRB.init();

    // 地磁気のオフセット、角度の初期値を設定
    xyz_t first_data = gyro_sens.read_mag();
    // 回転することで中心値を確認
    vel.angular = 1;
    vel_to_motor();
    float x_max = -10000;
    float x_min = 10000;
    float y_max = -10000;
    float y_min = 10000;
    for (int i = 0; i < 1000; i++) {
        xyz_t data = gyro_sens.read_mag();
        if (data.x > x_max) {
            x_max = data.x;
        } else if (data.x < x_min) {
            x_min = data.x;
        }
        if (data.y > y_max) {
            y_max = data.y;
        } else if (data.y < y_min) {
            y_min = data.y;
        }
        ets_delay_us(1000);
    }
    gyro_x_offset = -1 * (x_min + x_max) / 2;
    gyro_y_offset = -1 * (y_min + y_max) / 2; 
    angle_offset = std::atan2(first_data.x + gyro_x_offset, first_data.y + gyro_y_offset);
}

void ROBO::execute()
{
    direction = get_angle();
    Serial.printf("angle%lf, ", direction);
    angle_error = direction - target_dir;

    while(angle_error > PI) {
        angle_error -= PI * 2;
    }
    while(angle_error < -PI) {
        angle_error += PI * 2;
    }

    // 向きを一定にする
     vel.angular = 2.0 * angle_error; 

    vel_to_motor();
}

void ROBO::set_velocity(float vx, float vy) {
    vel.x = vx;
    vel.y = vy;
}

void ROBO::set_vel_x(float vx) {
    vel.x = vx;
}

void ROBO::set_vel_y(float vy) {
    vel.y = vy;
}

void ROBO::turn_right() {
    if (std::abs(angle_error) > 0.1) return;
   target_dir -= PI / 2; 
}

void ROBO::turn_left() {
    if (std::abs(angle_error) > 0.1) return;
   target_dir += PI / 2; 
}

void ROBO::stop() {
    vel.x = 0;
    vel.y = 0;
}

float ROBO::get_angle() {
    // ジャイロのついてる向きが分からんので確認して #debug
    xyz_t data = gyro_sens.read_mag();
    Serial.printf("x:%lf, y:%lf, z:%lf\n", data.x, data.y, data.z);
    return std::atan2(data.x + gyro_x_offset, data.y + gyro_y_offset) - angle_offset;
}

void ROBO::vel_to_motor() {
    // XYベクトルを回転
    float x = std::cos(-direction) * vel.x - std::sin(-direction) * vel.y;
    float y = std::sin(-direction) * vel.x + std::cos(-direction) * vel.y;

    // -1~1の間に抑える
    auto clamp = [](float vel)->float {
        if (vel > 1.0) {
            return 1.0;
        } else if (vel < -1.0) {
            return -1.0; 
        } else {
            return vel;
        }
    };
    // with black wheel
    /*
    motorLF.out(clamp(-(x - y + vel.angular) / 1.0f));
    motorRF.out(clamp((x + y - vel.angular) / 1.0f));
    motorLB.out(clamp(-(x + y + vel.angular) / 1.0f));
    motorRB.out(clamp(-(x - y - vel.angular) / 1.0f));   
    */

    // with white wheel
    motorLF.out(clamp(-(x - y + vel.angular) / 1.0f));
    motorRF.out(clamp(-(x + y - vel.angular) / 1.0f));
    motorLB.out(clamp((x + y + vel.angular) / 1.0f));
    motorRB.out(clamp((x - y - vel.angular) / 1.0f));
}