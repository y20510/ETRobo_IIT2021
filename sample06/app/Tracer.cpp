#include "Tracer.h" // <1>

Tracer::Tracer() : leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_3)
{ // <2>
}

Starter::Starter() : touchSensor(PORT_1)
{
}

void Tracer::init()
{
  init_f("Tracer");
}

void Tracer::terminate()
{
  msg_f("Stopped.", 1);
  leftWheel.stop(); // <1>
  rightWheel.stop();
}

void Tracer::run()
{
  msg_f("Running...", 1);
  float turn = calc_prop_value();
  leftWheel.setPWM(pwm - turn);
  rightWheel.setPWM(pwm + turn);
}

float Tracer::calc_prop_value()
{
  const float Kp = 0.83;
  const int target = 24;
  const int bias = 0;
  int diff = colorSensor.getBrightness() - target;
  float turn = Kp * diff + bias;
  return turn;
}

void Starter::start()
{
  if (touchSensor.isPressed() == true)
  {
    printf("押されています。");
    status = true;
  }
}

ColorReader::ColorReader() : colorSensor(PORT_3)
{
}

void ColorReader::bluecount()
{
  printf("nowcolor:%d, bluecount:%d\n", colorSensor.getColorNumber(), count);
  if (colorSensor.getColorNumber() == COLOR_BLUE)
  {
    printf("青色を検知しました。");
    count++;
  }
}

int ColorReader::colorread()
{
  int color = colorSensor.getColorNumber();
  return color;
}

void ColorReader::countReset()
{
  count = 0;
}

ScenarioRunner::ScenarioRunner() : leftWheel(PORT_C), rightWheel(PORT_B), steering(leftWheel, rightWheel), colorSensor(PORT_3)
{
}
void ScenarioRunner::forward(float tn)
{
  float turn = tn;
  leftWheel.setPWM(pwm - turn);
  rightWheel.setPWM(pwm + turn);
}

int ScenarioRunner::colorRead()
{
  int color;
  color = colorSensor.getColorNumber();
  return color;
}

void ScenarioRunner::stop()
{
  leftWheel.setPWM(0);
  rightWheel.setPWM(0);
}

void ScenarioRunner::clockinit()
{
  clock.reset();
}

bool ScenarioRunner::finishWork()
{
  if (clock.now() >= 9000000)
  {
    printf("9秒経ったので、停止します。\n");
    return true;
  }
}

RobotTurn::RobotTurn() : leftWheel(PORT_C), rightWheel(PORT_B), steering(leftWheel, rightWheel)
{
}

void RobotTurn::turn()
{
  if (count == 1)
  {
    rightWheel.stop();
    leftWheel.stop();
  }
  else
  {
    steering.setPower(52, pwm);
    count++;
    printf("count=%d", count);
  }
}

int RobotTurn::countGet()
{
  printf("count=%d\n", count);
  return count;
}

void RobotTurn::stop()
{
  rightWheel.stop();
  leftWheel.stop();
}

BlockMove ::BlockMove() : sonarSensor(PORT_2), leftWheel(PORT_C), rightWheel(PORT_B)
{
}

void BlockMove::blockCarry()
{
  distance = sonarSensor.getDistance();
  printf("%dcm\n", distance);
  if (distance < 30)
  {
    wheelInit();
  }
  else
  {
    leftWheel.setPWM(pwm);
    rightWheel.setPWM(pwm);
  }
}

void BlockMove::wheelInit()
{
  leftWheel.stop();
  rightWheel.stop();
}