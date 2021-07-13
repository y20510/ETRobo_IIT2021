#include "Timer.h"

/**
 * コンストラクタ
 * @param timer 時間を測る
 */
Timer::Timer(ev3api::Clock clock)
    : mClock(clock)
{
}

/**
 * タイマーをリセットする
 */
void Timer::timerReset()
{
    mClock.reset();
}

/**
 * 経過時間を取る
 * @retval 開始時間からのタイムを得る
 */
int Timer::getPastTime()
{
    uint64_t time = mClock.now();
    return time;
}