#ifndef EV3_APP_BLOCKCARRY_H_
#define EV3_APP_BLOCKCARRY_H_

#include "MeasureDistance.h"
#include "Walker.h"

class BlockCarry
{
public:
    BlockCarry(MeasureDistance *measureDistance,
               Walker *walker);
    void run();
    bool isFinish();

private:
    MeasureDistance *mMeasureDistance;
    Walker *mWalker;
    bool finishStatus;
};

#endif //EV3_APP_BLOCKCARRY_H_