#include "app.h"    // <1>
#include "Tracer.h" // <2>
#include "Clock.h"  // <3>
#include "TouchSensor.h"
#include "Motor.h"
using namespace ev3api;

Tracer tracer; // <4>
Clock clock;   // <5>
Starter starter;
ColorReader colorReader;
ScenarioRunner scenarioRunner;
RobotTurn robotTurn;
BlockMove blockMove;
Motor leftWheel(PORT_C);
Motor rightWheel(PORT_B);

void starter_task(intptr_t exinf)
{
  printf("starter呼ばれています\n");
  starter.start();
  if (starter.status == true)
  {
    stp_cyc(STARTER_CYC);
  }
  ext_tsk();
}

void tracer_task(intptr_t exinf)
{ // <1>
  printf("tracerが呼ばれています\n");
  if (starter.status == true)
  {
    tracer.run(); // <2>
    colorReader.bluecount();
    if (colorReader.count >= 14)
    {
      tracer.terminate();
      stp_cyc(TRACER_CYC);
      sta_cyc(SCENARIO_CYC);
      colorReader.countReset();
      clock.reset();
      printf("nowTime=%d", clock.now());
    }
    if (colorReader.colorread() == COLOR_RED)
    {
      tracer.terminate();
      stp_cyc(TRACER_CYC);
      sta_cyc(BLOCKMOVE_CYC);
    }
    ext_tsk();
  }
}

void scenariorunner_task(intptr_t exinf)
{
  float turn = tracer.calc_prop_value();
  printf("シナリオランナー起動中\n");
  printf("nowTime=%d", clock.now());
  if (clock.now() >= 4450000)
  {
    scenarioRunner.stop();
    stp_cyc(SCENARIO_CYC);
    sta_cyc(TURN_CYC);
  }
  else if (scenarioRunner.colorRead() == COLOR_RED)
  {
    printf("赤を検知しました。");
    scenarioRunner.stop();
    stp_cyc(SCENARIO_CYC);
  }
  else
  {
    scenarioRunner.forward(turn);
  }
  ext_tsk();
}

void turn_task(intptr_t exinf)
{
  printf("ロボットターン起動中\n");
  if (robotTurn.countGet() == 1)
  {
    robotTurn.stop();
    stp_cyc(TURN_CYC);
    clock.reset();
    while (clock.now() < 45000)
    {
      printf("nowToime=%d\n", clock.now());
      leftWheel.setPWM(60);
      rightWheel.setPWM(60);
    }
    leftWheel.stop();
    rightWheel.stop();
  }
  else
  {
    robotTurn.turn();
  }

  ext_tsk();
}

void block_move_task(intptr_t exinf)
{
  blockMove.blockCarry();
  ext_tsk();
}

void main_task(intptr_t unused)
{                                // <1>
  const uint32_t duration = 100; // <2>
  sta_cyc(STARTER_CYC);
  tracer.init();       // <3>
  sta_cyc(TRACER_CYC); // <4>

  while (!ev3_button_is_pressed(LEFT_BUTTON))
  {                        // <1>
    clock.sleep(duration); // <2>
  }

  printf("左のボタンが押されました。");
  stp_cyc(TRACER_CYC); // <3>
  tracer.terminate();  // <4>
  ext_tsk();           // <5>
}
