#ifndef EV3_UNIT_ROBOTTURN_H_
#define EV3_UNIT_ROBOTTURN_H_

#include "Steering.h"
#include "Motor.h"
#include "Walker.h"

class RobotTurn
{
public:
    RobotTurn(ev3api::Steering &steering);
    void turnRight(int power, int turnRatio);

private:
    ev3api::Steering &mSteering;
};

#endif //EV3_UNIT_ROBOTTURN_H_