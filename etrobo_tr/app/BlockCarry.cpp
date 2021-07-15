#include "BlockCarry.h"

/**
 * コンストラクタ
 */
BlockCarry::BlockCarry(MeasureDistance *measureDistance,
                       Walker *walker)
    : mMeasureDistance(measureDistance),
      mWalker(walker)
{
}

void BlockCarry::run()
{
  if (mMeasureDistance->getDistance() < 28)
  {
    mWalker->stop();
  }
  else
  {
    mWalker->setCommand(Walker::NORMAL, 0);
    mWalker->run();
  }
}