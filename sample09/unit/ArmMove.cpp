#include "ArmMove.h"

/**
 * コンストラクタ
 * @param armMotor アーム用モーター
 */
ArmMove::ArmMove(ev3api::Motor &armMotor)
    : mArmMotor(armMotor)
{
}

/**
 * アームをセットする
 * @retval isFinish true:セット完了
 */
bool ArmMove::setArm()
{
    if (mArmMotor.getCount() == -46)
    {
        mArmMotor.stop();
        return isFinish();
    }
    else if (mArmMotor.getCount() > 0)
    {
        mArmMotor.setPWM(-2);
        return false;
    }
    else
    {
        mArmMotor.setPWM(2);
        return false;
    }
}

/**
 * 終了の時finishStatusをtrueに
 * @retval finishStatus 終了判定
 */
bool ArmMove::isFinish()
{
    finishStatus = true;
    return finishStatus;
}