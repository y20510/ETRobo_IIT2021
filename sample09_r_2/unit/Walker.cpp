/******************************************************************************
 *  Walker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Class Walker
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Walker.h"
#include "LineTracer.h"

// 定数宣言
const int Walker::lLOW = 40; // 低速
const int Walker::sLOW = 8;
const int Walker::NORMAL = 8; // 通常
const int Walker::lHIGH = 75; // 高速
const int Walker::sHIGH = 50;

/**
 * コンストラクタ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 */
Walker::Walker(ev3api::Motor &leftWheel,
               ev3api::Motor &rightWheel)
    : mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mForward(lLOW),
      mTurn(0)
{
}

/**
 * 走行する
 */
void Walker::run()
{
    // 左右モータに回転を指示する
    int rightPWM = 0;
    int leftPWM = 0;

    leftPWM = mForward + mTurn;
    rightPWM = mForward - mTurn;

    mLeftWheel.setPWM(leftPWM);
    mRightWheel.setPWM(rightPWM);
}

/**
 * 走行に必要なものをリセットする
 */
void Walker::init()
{
    // モータをリセットする
    mLeftWheel.reset();
    mRightWheel.reset();
}

/**
 * PWM値を設定する
 * @param forward 前進値
 * @param turn    旋回方向
 */
void Walker::setCommand(int forward, int turn)
{
    mForward = forward;
    mTurn = turn;
}

/**
 * ロボットを停止させる
 */
void Walker::stop()
{
    mLeftWheel.stop();
    mRightWheel.stop();
}

/**
 * ブロック運び専用
 */
void Walker::blockRun()
{
    int rightPWM = 8;
    int leftPWM = 8;

    mLeftWheel.setPWM(leftPWM);
    mRightWheel.setPWM(rightPWM);
}