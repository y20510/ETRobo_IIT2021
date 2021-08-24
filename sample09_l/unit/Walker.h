/******************************************************************************
 *  Walker.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class Walker
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_UNIT_WALKER_H_
#define EV3_UNIT_WALKER_H_

#include "Motor.h"

class Walker
{
public:
    static const int LOW;
    static const int NORMAL;
    static const int HIGH;
    
    Walker(ev3api::Motor &leftWheel,
           ev3api::Motor &rightWheel);

    void init();
    void run();
    void setCommand(int forward, int turn);
    void stop();

private:
    ev3api::Motor &mLeftWheel;
    ev3api::Motor &mRightWheel;
    int mForward;
    int mTurn=0;
};

#endif // EV3_UNIT_WALKER_H_
