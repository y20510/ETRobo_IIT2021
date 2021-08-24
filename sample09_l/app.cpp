/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "app.h"
#include "LineTracer.h"
#include "ScenarioRunner.h"
#include "BlockCarry.h"
#include "EntryRunner.h"

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
void *__dso_handle = 0;

// using宣言
using ev3api::ColorSensor;
using ev3api::Motor;
using ev3api::SonarSensor;
using ev3api::Steering;
using ev3api::TouchSensor;

// Device objects
// オブジェクトを静的に確保する
ColorSensor gColorSensor(PORT_3);
Motor gLeftWheel(PORT_C);
Motor gRightWheel(PORT_B);
TouchSensor gTouchSensor(PORT_1);
Steering gSteering(gLeftWheel, gRightWheel);
SonarSensor gSonarSensor(PORT_2);

// オブジェクトの定義
static LineMonitor *gLineMonitor;
static Walker *gWalker;
static TouchMonitor *gTouchMonitor;
static LineTracer *gLineTracer;
static RobotTurn *gRobotTurn;
static ScenarioRunner *gScenarioRunner;
static MeasureDistance *gMeasureDistance;
static BlockCarry *gBlockCarry;
static EntryRunner *gEntryRunner;

/**
 * EV3システム生成
 */
static void
user_system_create()
{
    // オブジェクトの作成
    gWalker = new Walker(gLeftWheel, gRightWheel);
    gLineMonitor = new LineMonitor(gColorSensor);
    gTouchMonitor = new TouchMonitor(gTouchSensor);
    gMeasureDistance = new MeasureDistance(gSonarSensor);
    gRobotTurn = new RobotTurn(gSteering);
    gLineTracer = new LineTracer(gLineMonitor, gWalker, gTouchMonitor);
    gScenarioRunner = new ScenarioRunner(gLineMonitor, gWalker, gRobotTurn);
    gBlockCarry = new BlockCarry(gMeasureDistance, gWalker);
    gEntryRunner = new EntryRunner(*gLineTracer, *gScenarioRunner, *gBlockCarry);

    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy()
{
    gLeftWheel.reset();
    gRightWheel.reset();

    delete gLineTracer;
    delete gLineMonitor;
    delete gWalker;
    delete gTouchMonitor;
    delete gRobotTurn;
    delete gScenarioRunner;
    delete gBlockCarry;
    delete gMeasureDistance;
    delete gEntryRunner;
}

/**
 * メインタスク
 */
void main_task(intptr_t unused)
{
    user_system_create(); // センサやモータの初期化処理

    // 周期ハンドラ開始
    sta_cyc(CYC_TRACER);

    slp_tsk(); // ブロック運び終了まで待つ

    // 周期ハンドラ停止
    stp_cyc(CYC_TRACER);

    slp_tsk();

    user_system_destroy(); // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf)
{
    gEntryRunner->run();
    if (gEntryRunner->isFinish())
    {
        wup_tsk(MAIN_TASK);
    }
    ext_tsk();
}
