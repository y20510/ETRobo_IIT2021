#include "MesureDistance.h"

class BlockCarry{
    public:
    BlockCarry(const MesureDistance* mesureDistance);

    void run();

    private:
    const MesureDistance* mesureDistance;
}