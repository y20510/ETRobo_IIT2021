#include "ScenarioRunner.h"

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
 * ３段階に分けており scene によって管理する
 * scene=0が指定の時間ライントレース（真っ直ぐ）
 * scene=1が黒線を感知するまで右回転
 * scene=2がブロック運び開始位置までのライントレース
 */
void ScenarioRunner::run()
{
  if (mIsInitialized == false)
  {
    sClock.reset();
    mWalker->init();
    mIsInitialized = true;
  }
  switch (scene)
  {
  case 0:
    if (sClock.now() < 4300000)
    {
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
    mRobotTurn->turnRight(40, -100); //右回りの変更点
    if (mLineMonitor->getColorNumber() == COLOR_BLACK)
    {
      scene = 2;
      sClock.reset();
    }
    break;
  case 2:
    if (sClock.now() < 3000000)
    {
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
 * @param nowBrightness 現在の反射光の強さ
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

/**
 * 終了の判定
 * @retval mScenarioFinish シナリオランナーが終わったか true:終了
 */
bool ScenarioRunner::isFinish()
{
  return mScenarioFinish;
}