#include "Tracer.h" // <1>

/*--------------------------//トレーサークラス---------------------------------*/
Tracer::Tracer() : leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_3)
{ // <2>
}

void Tracer::init() //初期化
{
  init_f("Tracer");
}

void Tracer::terminate()  //ストップする
{
  msg_f("Stopped.", 1);
  leftWheel.stop(); // <1>
  rightWheel.stop();
}

void Tracer::run()  //ライントレースする
{
  msg_f("Running...", 1);
  float turn = calc_prop_value();
  leftWheel.setPWM(pwm - turn);
  rightWheel.setPWM(pwm + turn);
}

float Tracer::calc_prop_value() //P制御の計算
{
  if (colorSensor.getColorNumber() == COLOR_BLUE || colorSensor.getColorNumber() == COLOR_YELLOW)
  {
    float turn = 0;
    return turn;
  }
  else
  {
    const float Kp = 0.83;
    const int target = 24;
    const int bias = 0;
    int diff = colorSensor.getBrightness() - target;
    float turn = Kp * diff + bias;
    return turn;
  }
}

/*----------------------スタータークラス---------------------------------*/
Starter::Starter() : touchSensor(PORT_1)
{
}

void Starter::start() //タッチボタンが押されたかどうか
{
  if (touchSensor.isPressed() == true)
  {
    printf("押されています。");
    status = true;
  }
}

/*--------------------------カラーリードクラス----------------------------------*/
ColorReader::ColorReader() : colorSensor(PORT_3)
{
}

void ColorReader::bluecount() //青い線を通った回数
{
  printf("nowcolor:%d, bluecount:%d\n", colorread(), count);
  if (colorread() == COLOR_BLUE)
  {
    printf("青色を検知しました。");
    count++;
  }
}

int ColorReader::colorread()  //カラーセンサーの読み取った色の値を返す
{
  int color = colorSensor.getColorNumber();
  return color;
}

void ColorReader::countReset()  //カウントをリセットする
{
  count = 0;
}

/*--------------------シナリオランナークラス--------------------------*/
ScenarioRunner::ScenarioRunner() : leftWheel(PORT_C), rightWheel(PORT_B), steering(leftWheel, rightWheel), colorSensor(PORT_3)
{
}
void ScenarioRunner::forward(float tn)  //前に進む
{
  float turn = tn;
  leftWheel.setPWM(pwm - turn);
  rightWheel.setPWM(pwm + turn);
}

int ScenarioRunner::colorRead() //読み込んだ色の定数値を返す
{
  int color;
  color = colorSensor.getColorNumber();
  return color;
}

void ScenarioRunner::stop() //シナリオランナー停止
{
  leftWheel.setPWM(0);
  rightWheel.setPWM(0);
}


/*-----------------------ロボットターンクラス-------------------------*/
RobotTurn::RobotTurn() : leftWheel(PORT_C), rightWheel(PORT_B), steering(leftWheel, rightWheel), colorSensor(PORT_3)
{
}

void RobotTurn::turn()  //ロボットを回転させる
{
  if (colorSensor.getColorNumber() == COLOR_BLACK)
  {
    printf("黒を感知しました。");
    rightWheel.stop();
    leftWheel.stop();
    count = 1;
  }
  else
  {
    steering.setPower(25, +100);
    printf("count=%d", count);
  }
}

int RobotTurn::countGet() //黒の検知した回数
{
  printf("count=%d\n", count);
  return count;
}

void RobotTurn::stop()  //ロボットの回転を止める
{
  rightWheel.stop();
  leftWheel.stop();
}

void RobotTurn::run() //ライントレース（シナリオ版）
{
  float turn = calc_prop_value();
  leftWheel.setPWM(pwm - turn);
  rightWheel.setPWM(pwm + turn);
}

float RobotTurn::calc_prop_value()  //P制御のための計算
{
  const float Kp = 0.83;
  const int target = 24;
  const int bias = 0;
  int diff = colorSensor.getBrightness() - target;
  float turn = Kp * diff + bias;
  return turn;
}

/*-----------------------ブロック運びのクラス----------------------*/
BlockMove ::BlockMove() : sonarSensor(PORT_2), leftWheel(PORT_C), rightWheel(PORT_B)
{
}

void BlockMove::blockCarry()  //ブロックを運ぶ
{
  distance = sonarSensor.getDistance(); //距離を取得する
  printf("%dcm\n", distance);
  if (distance < 28)
  {
    wheelInit();
  }
  else
  {
    leftWheel.setPWM(pwm);
    rightWheel.setPWM(pwm);
  }
}

void BlockMove::wheelInit() //ホイールを止める
{
  leftWheel.stop();
  rightWheel.stop();
}