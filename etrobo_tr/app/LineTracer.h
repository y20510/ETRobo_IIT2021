/******************************************************************************
 *  LineTracer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_LINETRACER_H_
#define EV3_APP_LINETRACER_H_

#include "LineMonitor.h"
#include "Walker.h"
#include "TouchMonitor.h"

class LineTracer
{
public:
    LineTracer(LineMonitor *lineMonitor,
               Walker *walker, TouchMonitor *touchMonitor);

    void run();
    bool isFinish();

private:
    LineMonitor *mLineMonitor;
    Walker *mWalker;
    bool mIsInitialized;
    TouchMonitor *mTouchMonitor;
    float calc_prop_value(int nowBrightness);
    bool mStartButton;
    bool mTracerFinish = false;
};

#endif // EV3_APP_LINETRACER_H_
