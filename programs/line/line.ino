#define THRE 500      // フォトリフレクタの閾値
#define BASESPEED 100 // 基準のモータ回転数(notRPM)
#define KP 0.25       // pゲイン
#define MOTORL00 22   // 左のモータの正逆転を決めるポート1
#define MOTORL01 23   // 左のモータの正逆転を決めるポート2
#define MOTORR00 24   // 右の
#define MOTORR01 25   // 右の
#define MOTOR300 26   // 把持モータの正逆転
#define MOTOR301 27   // 把持モータの正逆転
#define MOTOR400 28   // 持ち上げモータの正逆転
#define MOTOR401 29   // 持ち上げモータの正逆転
#define LIM0 41       // リミットスイッチ
#define LIM1 48       // リミットスイッチ
#define LIM2 50       // リミットスイッチ
#define LIM3 52       // リミットスイッチ
#define MOTORL 2      // 左の車輪を回すモータ
#define MOTORR 3      // 右の車輪を回すモータ
#define MOTOR3 4      // 把持モータ
#define MOTOR4 5      // 持ち上げモータ
#define PHREF0 0      // フォトリフレクタのポート番号(最左)
#define PHREF1 1
#define PHREF2 2
#define PHREF3 3
#define PHREF4 4
#define PHREF5 5
#define PHREF6 6
#define PHREF7 7
#define DIP1 33 // DIPスイッチ
#define DIP2 35 // DIPスイッチ
#define DIP3 37 // DIPスイッチ
#define DIP4 39 // DIPスイッチ

int phref0val; // フォトリフレクタの値
int diff = 0;  // 閾値との差分
int black = 0; // 黒を読んでいる個数
int binnum = 0;
double output_l; // 左のモータに出力するpwm
double output_r; // 右のモータに出力するpwm
int refrection[8];
int mode;
int oneblock = 1700; // 1ブロック進むのに必要な時間[ms]

void straight();
void stop();
void turnRight();
void turnLeft();
void grip();
void lift();
void unload();
void release();
void setOnLine(int mode);
int digitalReadNot(int pin);
int getModeNumber();

void setup()
{
  Serial.begin(9600);
  pinMode(DIP1, INPUT);
  pinMode(DIP2, INPUT);
  pinMode(DIP3, INPUT);
  pinMode(DIP4, INPUT);
  pinMode(LIM0, INPUT);
  pinMode(LIM1, INPUT);
  pinMode(LIM2, INPUT);
  pinMode(LIM3, INPUT);
}
void loop()
{
  mode = getModeNumber();
  if (digitalRead(LIM0) == 0)
  {
    if (mode == 1)
    {
      straight(oneblock);
      stop();
      grip();
      lift();
      straight(oneblock * 5);
      stop();
      unload();
      release();
    }
    else if (mode == 2)
    {
      straight(oneblock * 2);
      stop();
      grip();
      lift();
      straight(oneblock);
      stop();
      turnLeft();
      stop();
      straight(oneblock);
      stop();
      turnRight();
      stop();
      straight(oneblock * 3);
      stop();
      unload();
      release();
    }
    else if (mode == 3)
    {
      straight(oneblock);
      stop();
      grip();
      lift();
      straight(oneblock * 2);
      stop();
      turnLeft();
      stop();
      straight(oneblock * 2);
      stop();
      turnRight();
      straight(oneblock * 3);
      unload();
      release();
    }
    else if (mode == 5)
    {
      setOnLine(0);
      stop();
    }
    else if (mode == 6)
    {
      setOnLine(1);
      stop();
    }
    else if (mode == 7) {
      straight(oneblock * 2);
      digitalWrite(MOTORL00, 0);
      digitalWrite(MOTORL01, 1);
      digitalWrite(MOTORR00, 1);
      digitalWrite(MOTORR01, 0);
      analogWrite(MOTORL, BASESPEED);
      analogWrite(MOTORR, BASESPEED);
      delay(2500);
      straight(500);
      setOnLine(1);
      stop();
    }
  }
}

int digitalReadNot(int pin)
{
  return !digitalRead(pin);
}
int getModeNumber()
{
  return digitalReadNot(DIP1) * 2 * 2 * 2 + digitalReadNot(DIP2) * 2 * 2 + digitalReadNot(DIP3) * 2 + digitalReadNot(DIP4);
}
void straight(int val)
{
  digitalWrite(MOTORL00, 1);
  digitalWrite(MOTORL01, 0);
  digitalWrite(MOTORR00, 1);
  digitalWrite(MOTORR01, 0);
  analogWrite(MOTORL, BASESPEED);
  analogWrite(MOTORR, BASESPEED);
  delay(val);
}
void stop()
{
  analogWrite(MOTORL, 0);
  analogWrite(MOTORR, 0);
  delay(1000);
}
void turnRight()
{
  digitalWrite(MOTORL00, 1);
  digitalWrite(MOTORL01, 0);
  digitalWrite(MOTORR00, 0);
  digitalWrite(MOTORR01, 1);
  while (black < 8)
  {
    for (int i = 0; i < 8; i++)
    {
      refrection[i] = analogRead(i);
      if (refrection[i] > THRE)
      {
        black++;
      }
    }
    analogWrite(MOTORL, 50);
    analogWrite(MOTORL, 50);
  }
}
void turnLeft()
{
  digitalWrite(MOTORL00, 0);
  digitalWrite(MOTORL01, 1);
  digitalWrite(MOTORR00, 1);
  digitalWrite(MOTORR01, 0);
  while (black < 8)
  {
    for (int i = 0; i < 8; i++)
    {
      refrection[i] = analogRead(i);
      if (refrection[i] > THRE)
      {
        black++;
      }
    }
    analogWrite(MOTORL, 50);
    analogWrite(MOTORL, 50);
  }
}
void setOnLine(int mode)
{
  // mode = 0: forward
  // mode = 1: backward
  black = 0;
  int rotate = 0;
  int isBlack;
  while (true)
  {
    black = 0;
    rotate = 0;
    for (int i = 0; i < 8; i++)
    {
      refrection[i] = analogRead(i);
      if (refrection[i] > THRE)
      {
        isBlack = 1;
        black++;
      }
      else
      {
        isBlack = 0;
      }
      if (i <= 3)
      {
        rotate += isBlack * (i - 4);
      }
      else
      {
        rotate += isBlack * (i - 4 + 1);
      }
    }
    if (black <= 1)
    {
      digitalWrite(MOTORL00, 1 - mode);
      digitalWrite(MOTORL01, 0 + mode);
      digitalWrite(MOTORR00, 1 - mode);
      digitalWrite(MOTORR01, 0 + mode);
      analogWrite(MOTORL, 50);
      analogWrite(MOTORR, 50);
    }
    else if (black == 8)
    {
      analogWrite(MOTORL, 0);
      analogWrite(MOTORR, 0);
      break;
    }
    else
    {
      if (rotate <= 0)
      {
        digitalWrite(MOTORL00, 1 - mode);
        digitalWrite(MOTORL01, 0 + mode);
        digitalWrite(MOTORR00, 0 + mode);
        digitalWrite(MOTORR01, 1 - mode);
        analogWrite(MOTORL, 10 * rotate * (-1));
        analogWrite(MOTORR, 10 * rotate * (-1));
      }
      else
      {
        digitalWrite(MOTORL00, 0 + mode);
        digitalWrite(MOTORL01, 1 - mode);
        digitalWrite(MOTORR00, 1 - mode);
        digitalWrite(MOTORR01, 0 + mode);
        analogWrite(MOTORL, 10 * rotate);
        analogWrite(MOTORR, 10 * rotate);
      }
    }
    delay(10);
  }
}
void grip()
{
  digitalWrite(MOTOR300, 0);
  digitalWrite(MOTOR301, 1);
  analogWrite(MOTOR3, 125);
  delay(1500);
  analogWrite(MOTOR3, 0);
  digitalWrite(MOTOR300, 1);
  digitalWrite(MOTOR301, 1);
}
void lift()
{
  digitalWrite(MOTOR400, 1);
  digitalWrite(MOTOR401, 0);
  analogWrite(MOTOR4, 255);
  delay(1500);
  digitalWrite(MOTOR400, 1);
  digitalWrite(MOTOR401, 1);
  analogWrite(MOTOR4, 0);
  delay(2000);
}
void unload()
{
  digitalWrite(MOTOR400, 0);
  digitalWrite(MOTOR401, 1);
  analogWrite(MOTOR4, 100);
  delay(1500);
  analogWrite(MOTOR4, 0);
  digitalWrite(MOTOR400, 1);
  digitalWrite(MOTOR401, 1);
}
void release()
{
  digitalWrite(MOTOR300, 1);
  digitalWrite(MOTOR301, 0);
  analogWrite(MOTOR3, 125);
  delay(1500);
  analogWrite(MOTOR3, 0);
  digitalWrite(MOTOR300, 1);
  digitalWrite(MOTOR301, 1);
}
