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
}

void ROBO::execute()
{
    float direction = get_angle();
    float angle_error = direction - target_dir;
    Serial.printf("angle_error %lf\n", angle_error);

    // 向きを一定にする
    //vel.angular = 1.0 * angle_error;

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

    // モータを回す
    // こんな計算で…いいのか？ #debug
    Serial.print(vel.x);
    Serial.print(", ");
    Serial.print(vel.y);
    Serial.print(", ");
    Serial.print(vel.angular);
    Serial.println(" ");
    motorLF.out(clamp(-(vel.x - vel.y + vel.angular) / 1.0f));
    motorRF.out(clamp((vel.x + vel.y - vel.angular) / 1.0f));
    motorLB.out(clamp(-(vel.x + vel.y + vel.angular) / 1.0f));
    motorRB.out(clamp(-(vel.x - vel.y - vel.angular) / 1.0f));
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
    
}

void ROBO::turn_left() {

}

void ROBO::stop() {
    vel.x = 0;
    vel.y = 0;
}

float ROBO::get_angle() {
    // ジャイロのついてる向きが分からんので確認して #debug
    xyz_t data = gyro_sens.read_mag();
    return std::atan2(data.y, data.x);
}
