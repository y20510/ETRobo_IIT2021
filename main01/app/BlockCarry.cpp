#include "BlockCarry.h"

BlockCarry::BlockCarry(const MesureDistance* mesureDistance)
            : mMesureDistance(mesureDistance){}

void BlockCarry::run(){
    while(1){
    mesureDistance->getDistance();
    if(mesureDistance.distance<28){
        mesureDistance->CarryStop();
        break;
    }else{
        mesureDistance->Carry();
    }
    break;
    }
}
}