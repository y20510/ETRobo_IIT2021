#include "MeasureDistance.h"

/**
 * コンストラクタ
 * @param sonarSensor ソナーセンサー
 */
MeasureDistance::MeasureDistance(ev3api::SonarSensor &sonarSensor)
    : mSonarSensor(sonarSensor)
{
}

/**
 * 壁との距離を取得する
 * @retval distance 前方との距離
 */
int MeasureDistance::getDistance()
{
    distance = mSonarSensor.getDistance();
    return distance;
}