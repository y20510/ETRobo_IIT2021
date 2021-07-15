#include "ScenarioRunner.h"
#include "Clock.h"

using ev3api::Clock;
Clock mColck;

/**
 * コンストラクタ
 * @param lineMonitor ライン判定
 * @param walker 走行
 * @param robotTurn 走行体の回転
 */
ScenarioRunner::ScenarioRunner(LineMonitor *lineMonitor,
                               Walker *walker,
                               RobotTurn *robotTurn)
    : mLineMonitor(lineMonitor),
      mWalker(walker),
      mRobotTurn(robotTurn),
      mIsInitialized(false),
      mScenarioFinish(false)
{
}

/**
 * ライントレース（シナリオラン）
 */
void ScenarioRunner::run()
{
  if (mIsInitialized == false)
  {
    mColck.reset();
    mIsInitialized = true;
  }
  switch (scene)
  {
  case 0:
    if (mColck.now() < 4400000)
    {
      printf("nowTime=%d\n", mColck.now());
      int nowBrightness = mLineMonitor->nowBrightness();

      // 走行体の向きを計算する
      float turn = calc_prop_value(nowBrightness);

      mWalker->setCommand(Walker::HIGH, turn);

      // 走行を行う
      mWalker->run();
    }
    else
    {
      scene = 1;
    }
    break;
  case 1:
    mRobotTurn->turnRightAngle(40, 100);
    if (mLineMonitor->getColorNumber() == COLOR_BLACK)
    {
      scene = 2;
      mColck.reset();
    }
    break;
  case 2:
    if (mColck.now() < 1700000)
    {
      printf("nowTime=%d\n", mColck.now());
      int nowBrightness = mLineMonitor->nowBrightness();
      float turn = calc_prop_value(nowBrightness);
      mWalker->setCommand(Walker::LOW, turn);
      mWalker->run();
    }
    else
    {
      mWalker->stop();
      mScenarioFinish = true;
    }
    break;
  }
}

/**
 * 走行体の向きを計算する
 * @retval turn 目標値との差
 */
float ScenarioRunner::calc_prop_value(int nowBrightness)
{
  const float Kp = 0.83;
  const int target = 24;
  const int bias = 0;
  int diff = nowBrightness - target;
  float turn = Kp * diff + bias;
  return turn;
}

bool ScenarioRunner::isFinish()
{
  return mScenarioFinish;
}