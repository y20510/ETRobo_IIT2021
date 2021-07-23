#include "BlockCarry.h"

/**
 * コンストラクタ
 * @param measureDistance メジャーディスタンスクラス
 * @param walker ウォーカークラス
 * @param robotTurn ロボットターンクラス
 */
BlockCarry::BlockCarry(MeasureDistance *measureDistance,
                       //RobotTurn *robotTurn,
                       Walker *walker)
    : mMeasureDistance(measureDistance),
      //mRobotTurn(robotTurn),
      mWalker(walker),
      finishStatus(false)
{
}

/**
 * ブロック運び開始
 */
void BlockCarry::run()
{
  if (mMeasureDistance->getDistance() < 34)
  {
    mWalker->stop();
    finishStatus = true;
  }
  else
  {
    mWalker->setCommand(Walker::NORMAL, 0);
    mWalker->run();
    //mRobotTurn->turnRightAngle(50, 0);
  }
}

/**
 * ブロック運びが終了したかどうか
 * @retval finishStatus true:終了した
 */
bool BlockCarry::isFinish()
{
  return finishStatus;
}