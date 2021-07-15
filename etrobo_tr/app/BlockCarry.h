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

private:
    MeasureDistance *mMeasureDistance;
    Walker *mWalker;
};

#endif  //EV3_APP_BLOCKCARRY_H_