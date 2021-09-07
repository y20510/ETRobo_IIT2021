/******************************************************************************
 *  LineTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracer.h"

/**
 * コンストラクタ
 * @param lineMonitor     ライン判定
 * @param walker 走行
 * @param touchMonitor　タッチセンサーの判定
 * @param armMove アームモーター
 */
LineTracer::LineTracer(LineMonitor *lineMonitor,
                       Walker *walker,
                       TouchMonitor *touchMonitor)
    : mLineMonitor(lineMonitor),
      mWalker(walker),
      mTouchMonitor(touchMonitor),
      mIsInitialized(false),
      mStartButton(false)
{
}

/**
 * ライントレースする
 */
void LineTracer::run()
{
    if (mIsInitialized == false)
    {
        mWalker->init();

        mIsInitialized = true;
    }
    if (mStartButton == false) //タッチセンサーが押されるまで走らない
    {
        mStartButton = mTouchMonitor->isPushed();
        lClock.reset();
    }
    else if (mLineMonitor->getBlueCount())
    {
        switch (scene)
        {
        case 0:
            setTimeSpeed(5300000, Walker::lHIGH);
            break;

        case 1:
            setTimeSpeed(3600000, Walker::lLOW);
            break;
        case 2:
            setTimeSpeed(2000000, Walker::lHIGH);
            break;

        case 3:
            setTimeSpeed(2800000, Walker::lLOW);
            break;

        case 4:
            setTimeSpeed(4600000, Walker::lHIGH);
            break;
        case 5:
            setTimeSpeed(2000000, Walker::lLOW);
            break;
        case 6:
            setTimeSpeed(2000000, Walker::lHIGH);
            break;
        default:
            setTimeSpeed(5000000, Walker::lLOW);
            break;
        }
    }
    else
    {
        mWalker->stop();
        mTracerFinish = true;
    }
}

/**
 * 走行体の向きを計算する
 * @retval turn 目標値との差
 */
float LineTracer::calc_prop_value(int nowBrightness)
{
    const float Kp = 0.91;
    const int target = 24;
    const int bias = 0;
    int diff = nowBrightness - target;
    float turn = Kp * diff + bias;
    return turn;
}

/**
 * ライントレースの終了判定
 * @retval mTracerFinish true:終了
 */
bool LineTracer::isFinish()
{
    return mTracerFinish;
}

/**
 * 走行の手順のメソッド
 * @param time 走行時間
 * @param speed 速度
 */
void LineTracer::setTimeSpeed(int time, int speed)
{
    printf("time=%d scene=%d\n", lClock.now(), scene);
    if (lClock.now() < time)
    {
        int nowBrightness = mLineMonitor->nowBrightness();
        float turn = calc_prop_value(nowBrightness);
        mWalker->setCommand(speed, turn);
        mWalker->run();
    }
    else
    {
        scene++;
        lClock.reset();
    }
}