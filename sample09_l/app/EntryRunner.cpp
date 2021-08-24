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
      mScenarioRunner.run(); // バックボタン押下
    }
  }
  else
  {
    mLineTracer.run(); // 走行
  }
  if (mBlockCarry.isFinish())
  {
    finishStatus = true;
  }
}

bool EntryRunner::isFinish()
{
  return finishStatus;
}