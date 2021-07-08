#ifndef EV3_UNIT_TOUCHMONITOR_H_
#define EV3_UNIT_TOUCHMONITOR_H_

#include "TouchSensor.h"

class TouchMonitor{
public:
    TouchMonitor(ev3api::TouchSensor& touchSensor);
    bool isPushed();

private:
    bool mStatus;
    ev3api::TouchSensor& mTouchSensor;
};

#endif  //EV3_UNIT_TOUCHMONITOR_H_