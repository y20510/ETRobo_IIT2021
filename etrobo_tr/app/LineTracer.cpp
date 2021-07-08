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
 */
LineTracer::LineTracer(LineMonitor *lineMonitor,
                       Walker *walker, TouchMonitor *touchMonitor)
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
    }
    else if (mLineMonitor->getBlueCount())
    {

        int nowBrightness = mLineMonitor->nowBrightness();

        // 走行体の向きを計算する
        float turn = calc_prop_value(nowBrightness);

        mWalker->setCommand(Walker::LOW, turn);

        // 走行を行う
        mWalker->run();
    }
    else
    {
        mWalker->stop();
    }
}

/**
 * 走行体の向きを計算する
 * @retval turn 目標値との差
 */
float LineTracer::calc_prop_value(int nowBrightness)
{
    const float Kp = 0.83;
    const int target = 24;
    const int bias = 0;
    int diff = nowBrightness - target;
    float turn = Kp * diff + bias;
    return turn;
}
