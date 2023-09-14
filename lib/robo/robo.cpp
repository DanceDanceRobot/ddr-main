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
    motorLF(MOTOR1_pin, 1.0f),
    motorLB(MOTOR2_pin, 1.0f),
    motorRF(MOTOR3_pin, -1.0f),
    motorRB(MOTOR4_pin, -1.0f),

    vel{0, 0, 0},
    target_dir(0),

    state(states::STATE_STANDBY)
{
    // ジャイロ
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
    // 回転をとめる判定のマージン
    constexpr float margin = 0.1;
    float direction = get_angle();

    switch (state)
    {
    case states::STATE_TURN:
        // 目標角度に近づいたら回転を止める
        // これで止まるのか分からん #debug
        if ((vel.angular > 0 && direction > target_dir - margin) ||
            (vel.angular < 0 && direction < target_dir + margin))
        {
            vel.angular = 0.0;
            state = states::STATE_STANDBY;
        }
        break;

    default:
        break;
    }

    // モータを回す
    // こんな計算で…いいのか？ #debug
    motorLF.out((vel.x - vel.y + vel.angular) / 3.0);
    motorRF.out((vel.x + vel.y + vel.angular) / 3.0);
    motorLB.out((vel.x + vel.y - vel.angular) / 3.0);
    motorRB.out((vel.x - vel.y + vel.angular) / 3.0);
}

void ROBO::go_up() {
    vel.x = 1.0;
    vel.y = 0.0;
}

void ROBO::go_down() {
    vel.x = -1.0;
    vel.y = 0.0;
}

void ROBO::go_left() {
    vel.x = 0.0;
    vel.y = 1.0;
}

void ROBO::go_right() {
    vel.x = 0.0;
    vel.y = -1.0;
}

void ROBO::turn_right() {
    // 回転途中だったら抜ける
    if (state == states::STATE_TURN) return;

    target_dir -= 3.14 / 2;
    if (target_dir < -3.14) {
        target_dir = 3.14 / 2;
    }
    vel.angular = -1.0;
    state = states::STATE_TURN;
}

void ROBO::turn_left() {
    // 回転途中だったら抜ける
    if (state == states::STATE_TURN) return;

    target_dir += 3.14 / 2;
    if (target_dir > 3.14) {
        target_dir = -3.14 / 2;
    }
    vel.angular = 1.0;
    state = states::STATE_TURN;
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
