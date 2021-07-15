#include "ArmMove.h"

/**
 * コンストラクタ
 * @param armMotor アーム用モーター
 */
ArmMove::ArmMove(ev3api::Motor &armMotor)
    : mArmMotor(armMotor)
{
}

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

bool ArmMove::isFinish()
{
    finishStatus = true;
    return finishStatus;
}

int ArmMove::getCount()
{
    return mArmMotor.getCount();
}

void ArmMove::armStop()
{
    mArmMotor.stop();
}