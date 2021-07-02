#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>
#include "TouchSensor.h"
#include "Steering.h"
#include "Clock.h"
#include "SonarSensor.h"
using namespace ev3api; // <4>

class Tracer
{ // <1>
public:
  Tracer();
  void run(); // <2>
  void init();
  void terminate();
  float calc_prop_value();

private:
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor;      // <3>
  const int8_t mThreshold = 20; // <4>
  const int8_t pwm = (Motor::PWM_MAX) / 4;
};

class Starter
{
public:
  Starter();
  void start();
  bool status = false;

private:
  TouchSensor touchSensor;
};

class ColorReader
{
public:
  void bluecount();
  int count = 0;
  int colorread();
  ColorReader();
  void countReset();

private:
  ColorSensor colorSensor;
};

class ScenarioRunner
{
private:
  Motor leftWheel;
  Motor rightWheel;
  Steering steering;
  ColorSensor colorSensor;
  const int8_t pwm = (Motor::PWM_MAX) / 2;
  Clock clock;

public:
  ScenarioRunner();
  void forward(float turn);
  int colorRead();
  void stop();
};

class RobotTurn
{
private:
  Steering steering;
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor;
  const int8_t pwm = (Motor::PWM_MAX) / 8;
  int count = 0;

public:
  void turn();
  RobotTurn();
  int countGet();
  void stop();
  void run();
  float calc_prop_value();
};

class BlockMove
{
private:
  SonarSensor sonarSensor;
  int distance;
  Motor leftWheel;
  Motor rightWheel;
  const int8_t pwm = (Motor::PWM_MAX) / 6;

public:
  BlockMove();
  void blockCarry();
  void wheelInit();
};