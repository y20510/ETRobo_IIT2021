#include "MesureDistance.h"
#include "Waker.h"

MesureDistance::MesureDistance():leftWheel(PORT_C), rightWheel(PORT_B), sonarSensor(PORT_2){}

void MesureDistance::getDistance(){
    distance = sonarSensor.getDistance();   //距離を取得
    printf("%dcm\n",distance);
}

void MesureDistance::Carry(){   //ブロックを運ぶ
        leftWheel.setPWM(pwm);
        rightWheel.setPWM(pwm);
    }
}

void MesureDistance::CarryStop(){   //ブロック運びの終了
    leftWheel.stop();
    rightWheel.stop();
}
