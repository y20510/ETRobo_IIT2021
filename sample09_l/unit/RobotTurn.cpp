#include "RobotTurn.h"

/**
 * コンストラクタ
 * @param  steering ステアリング（両輪）
 */
RobotTurn::RobotTurn(ev3api::Steering &steering)
    : mSteering(steering)
{
}

/**
 * ロボットを回転させる
 * @param power モータのパワー [-100..+100]<br>マイナスの値は後退
 * @param turnRatio ステアリングの度合い [-100..100]<br>マイナスの値は左への転回、プラスの値は右への転回
 */
void RobotTurn::turnRight(int power, int turnRatio)
{
    mSteering.setPower(power, turnRatio);
}