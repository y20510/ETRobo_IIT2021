#ifndef EV3_UNIT_TIMER_H_
#define EV3_UNIT_TIMER_H_

#include "Clock.h"

class Timer
{
public:
    Timer(ev3api::Clock clock);
    void timerReset();
    int getPastTime();

private:
    ev3api::Clock mClock;
};

#endif //EV3_UNIT_TIMER_H_