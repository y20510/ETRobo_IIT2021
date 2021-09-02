#ifndef EV3_UNIT_MEASUREDISTANCE_H_
#define EV3_UNIT_MEASUREDISTANCE_H_

#include "SonarSensor.h"

class MeasureDistance
{
public:
    MeasureDistance(ev3api::SonarSensor &sonarSensor);
    int getDistance();

private:
    ev3api::SonarSensor &mSonarSensor;
    int distance;
};

#endif //UNIT_MEASUREDISTANCE_H_