/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineMonitor.h"

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineMonitor::LineMonitor(ev3api::ColorSensor &colorSensor)
    : mColorSensor(colorSensor)

{
}

/**
 * 現在通っている線の線の反射を返す
 * @retval nowBrightness  現在の反射光の値
 */
int LineMonitor::nowBrightness()
{
    // 光センサからの取得値を見る
    int nowBrightness = mColorSensor.getBrightness();
    return nowBrightness;
}

/**
 * 青い線の通過回数を調べて、場合によって停止する
 * @retval false 青ゾーンを２回検知した
 * @retval true 青線を検知する(LineTracerの続行)
 */
bool LineMonitor::getBlueCount()
{
    nowColor = mColorSensor.getColorNumber();
    if (blueCount == 2)
    {
        return false;
    }
    else if (nowColor == COLOR_WHITE && oldColor == COLOR_BLUE)
    {
        blueCount++;
    }
    oldColor = nowColor;
    return true;
}

/**
 * カラーナンバーの取得
 * @retval mColorSensor.getColorNumber() カラーナンバー
 */
int LineMonitor::getColorNumber()
{
    return mColorSensor.getColorNumber();
}