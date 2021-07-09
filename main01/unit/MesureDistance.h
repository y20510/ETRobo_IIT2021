#include "Motor.h"       // <1>
#include "util.h"        // <3>
#include "SonarSensor.h"
using namespace ev3api; // <4>

class MesureDistance
{
private:
  SonarSensor sonarSensor;
  int distance;
 
  public:
  getDistance();
  Carry();
  CarryStop();
};