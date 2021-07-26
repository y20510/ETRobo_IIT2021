#ifndef EV3_APP_ENTRYRUNNER_H_
#define EV3_APP_ENTRYRUNNER_H_

#include "BlockCarry.h"
#include "LineTracer.h"
#include "ScenarioRunner.h"

class EntryRunner
{
public:
    EntryRunner(LineTracer &lineTracer,
                ScenarioRunner &scenarioRunner,
                BlockCarry &blockCarry);
    void run();
    bool isFinish();

private:
    LineTracer mLineTracer;
    ScenarioRunner mScenarioRunner;
    BlockCarry mBlockCarry;
    bool finishStatus=false;
};

#endif  //EV3_APP_ENTRYRUNNER_H_
