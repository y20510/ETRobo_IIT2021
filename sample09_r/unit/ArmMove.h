#ifndef EV3_UNIT_SETARM_H_
#define EV3_UNIT_SETARM_H_

#include "Motor.h"

class ArmMove
{
public:
    ArmMove(ev3api::Motor &armMotor);
    bool setArm();
    bool isFinish();
    int getCount();
    void armStop();

private:
    ev3api::Motor &mArmMotor;
    bool finishStatus = false;
};

#endif //EV3_UNIT_SETARM_H_