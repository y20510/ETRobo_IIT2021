#include "TouchMonitor.h"

/**
 * コンストラクタ
 * @param touchSensor タッチセンサー
 */
TouchMonitor::TouchMonitor(ev3api::TouchSensor &touchSensor)
    : mTouchSensor(touchSensor)
{
}


/**
 * タッチセンサーが押されたかの判定
 * @retval mStatus 押された場合true　押されなかった場合false
 */
bool TouchMonitor::isPushed()
{
    mStatus = mTouchSensor.isPressed();
    return mStatus;
}