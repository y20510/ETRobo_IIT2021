#ifndef EV3_APP_SCENARIORUNNER_H_
#define EV3_APP_SCENARIORUNNER_H_

#include "LineMonitor.h"
#include "Walker.h"
#include "RobotTurn.h"
#include "Timer.h"

class ScenarioRunner
{
public:
    ScenarioRunner(LineMonitor *lineMonitor,
                   Walker *walker,
                   RobotTurn *robotTurn);
    void run();
    bool isFinish();

private:
    RobotTurn *mRobotTurn;
    LineMonitor *mLineMonitor;
    Walker *mWalker;
    Timer *mTimer;
    float calc_prop_value(int nowBrightness);
    bool mIsInitialized;
    int scene = 0;
    bool mScenarioFinish;
};

#endif //EV3_APP_SCENARIORUNNER_H_