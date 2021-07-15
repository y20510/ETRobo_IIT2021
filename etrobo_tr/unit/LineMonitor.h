/******************************************************************************
 *  LineMonitor.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_UNIT_LINEMONITOR_H_
#define EV3_UNIT_LINEMONITOR_H_

#include "ColorSensor.h"

// 定義
class LineMonitor
{
public:
    explicit LineMonitor(ev3api::ColorSensor &colorSensor);

    int nowBrightness();
    bool getBlueCount();
    int getColorNumber();

private:
    ev3api::ColorSensor &mColorSensor;
    int blueCount = 0;
    int nowColor = 0;
    int oldColor = 0;
};

#endif // EV3_UNIT_LINEMONITOR_H_
