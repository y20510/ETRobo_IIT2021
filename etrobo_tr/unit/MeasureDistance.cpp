#include "MeasureDistance.h"

/**
 * コンストラクタ
 */
MeasureDistance::MeasureDistance(ev3api::SonarSensor &sonarSensor)
    : mSonarSensor(sonarSensor)
{
}

int MeasureDistance::getDistance()
{
    distance = mSonarSensor.getDistance();
    return distance;
}