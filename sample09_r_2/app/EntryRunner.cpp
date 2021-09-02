#include "EntryRunner.h"

/**
 * コンストラクタ
 */
EntryRunner::EntryRunner(LineTracer &lineTracer,
                         ScenarioRunner &scenarioRunner,
                         BlockCarry &blockCarry)
    : mLineTracer(lineTracer),
      mScenarioRunner(scenarioRunner),
      mBlockCarry(blockCarry)
{
}

void EntryRunner::run()
{
  if (mLineTracer.isFinish())
  {
    if (mScenarioRunner.isFinish())
    {
      mBlockCarry.run();
    }
    else
    {
      mScenarioRunner.run();
    }
  }
  else
  {
    mLineTracer.run(); // 走行
  }
  if (mBlockCarry.isFinish()) //最後まで終了した
  {
    finishStatus = true;
  }
}

/**
 * 終了したか調べる
 * @retval finishStatus 終了状態
 */
bool EntryRunner::isFinish()
{
  return finishStatus;
}