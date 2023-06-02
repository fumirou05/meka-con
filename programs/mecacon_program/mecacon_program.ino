#define THRE 500      // フォトリフレクタの閾値
#define BASESPEED 100 // 基準のモータ回転数(notRPM)
#define MOTORL00 22   // 左のモータの正逆転を決めるポート1
#define MOTORL01 23   // 左のモータの正逆転を決めるポート2
#define MOTORR00 24   // 右の 〃
#define MOTORR01 25   // 右の 〃
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
int black = 0; // 黒を読んでいる個数
double calib = 6;
double output_l; // 左のモータに出力するpwm
double output_r; // 右のモータに出力するpwm
int refrection[8];
int mode;
void goForward();
void goForwardSlow();
void stp();
void turnRight();
void turnLeft();
void grip();
void liftup();
void unload();
void releasee();
void setOnLine(int mode);
int digitalReadNot(int pin);
int getModeNumber();

void setup(){
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
void loop(){
  mode = getModeNumber();
  Serial.println(mode);
  while (digitalRead(LIM0) != 0);
  if (mode == 1){ //鉄球・ゾーン１
    goForwardSlow();
    stp();
    grip();
    liftup();
    setOnLine(1);
    goForward(3);
    stp();
    setOnLine(1);
    goForward(2);
    stp();
    unload();
    releasee();
  }
  else if (mode == 2){ //鉄球・ゾーン２
    goForward(1);
    stp();
    setOnLine(1);
    goForwardSlow();
    grip();
    liftup();
    goForward(1);
    stp();
    turnLeft();
    stp();
    goForward(1);
    stp();
    turnRight();
    stp();
    goForward(3);
    stp();
    unload();
    releasee();
  }
  else if (mode == 3){ //鉄球・ゾーン３ 工藤さんのを変更
    goForwardSlow();
    stp();
    grip();
    liftup();
    goForward(1);
    stp();
    turnLeft();
    stp();
    goForward(2);
    stp();
    turnRight();
    stp();
    goForward(2);
    stp();
    setOnLine(1);
    stp();
    goForward(2);
    stp();
    unload();
    releasee();
  }
  else if (mode == 4){ //鉄球・ゾーン４
    goForward(1);
    stp();
    goForwardSlow();
    stp();
    grip();
    liftup();
    goForward(1);
    stp();
    turnLeft();
    stp();
    goForward(1);
    stp();
    setOnLine(1);
    goForward(1);
    stp();
    turnRight();
    stp();
    goForward(3);
    stp();
    unload();
    releasee();
  }
  else if (mode == 5){ //ゴム・ゾーン１
    goForward(1);
    stp();
    grip();
    liftup();
    goForward(2);
    stp();
    turnRight();
    stp();
    goForward(1);
    stp();
    turnLeft();
    stp();
    goForward(3);
    stp();
    unload();
    releasee();
  }
  else if (mode == 6){ //ゴム・ゾーン２
    goForward(2);
    stp();
    grip();
    liftup();
    setOnLine(1);
    goForward(4);
    stp();
    unload();
    releasee();
  }
  else if (mode == 7){ //ゴム・ゾーン３
    goForward(1);
    stp();
    grip();
    liftup();
    goForward(2);
    stp();
    turnLeft();
    stp();
    goForward(1);
    stp();
    turnRight();
    stp();
    goForward(3);
    stp();
    unload();
    releasee();
  }
  else if (mode == 8){ //ゴム・ゾーン４
    goForward(2);
    stp();
    grip();
    liftup();
    goForward(1);
    stp();
    turnLeft();
    stp();
    goForward(1);
    stp();
    turnRight();
    stp();
    goForward(3);
    stp();
    unload();
    releasee();
  }
  else if (mode == 9){ //円錐・ゾーン１
    goForwardSlow();
    stp();
    grip();
    liftup();
    goForward(2);
    stp();
    turnRight();
    stp();
    goForward(3);
    stp();
    turnLeft();
    stp();
    goForward(3);
    stp();
    unload();
    releasee();
  }
  else if (mode == 10){ //円錐・ゾーン２
    goForward(1);
    stp();
    goForwardSlow();
    stp();
    grip();
    liftup();
    goForward(1);
    stp();
    turnRight();
    stp();
    goForward(2);
    stp();
    turnLeft();
    stp();
    goForward(3);
    stp();
    unload();
    releasee();
  }
  else if (mode == 11){ //円錐・ゾーン３
    goForwardSlow();
    stp();
    grip();
    liftup();
    goForward(2);
    stp();
    turnRight();
    stp();
    goForward(1);
    stp();
    turnLeft();
    stp();
    goForward(3);
    stp();
    unload();
    releasee();
  }
  else if (mode == 12){ //円錐・ゾーン４
    goForward(1);
    stp();
    goForwardSlow();
    stp();
    grip();
    liftup();
    setOnLine(1);
    goForward(4);
    stp();
    unload();
    releasee();
  }
}

//関数定義//
int digitalReadNot(int pin){
  return !digitalRead(pin);
  }
int getModeNumber(){
  return digitalReadNot(DIP1) * 2 * 2 * 2 + digitalReadNot(DIP2) * 2 * 2 + digitalReadNot(DIP3) * 2 + digitalReadNot(DIP4);
}
void goForward(int val){
  for (int i = 0; i < val; i++) {
    digitalWrite(MOTORL00, 1);
    digitalWrite(MOTORL01, 0);
    digitalWrite(MOTORR00, 1);
    digitalWrite(MOTORR01, 0);
    analogWrite(MOTORL, BASESPEED);
    analogWrite(MOTORR, BASESPEED + calib);
    delay(600);
    while (analogRead(0) < THRE) {
      analogWrite(MOTORL, BASESPEED);
      analogWrite(MOTORR, BASESPEED + calib);
    }
    calib = 9;
  }
}
void goForwardSlow(){
  digitalWrite(MOTORL00, 1);
  digitalWrite(MOTORL01, 0);
  digitalWrite(MOTORR00, 1);
  digitalWrite(MOTORR01, 0);
  analogWrite(MOTORL, BASESPEED);
  analogWrite(MOTORR, BASESPEED + calib);
  delay(600);
  while (analogRead(0) < THRE) {
    digitalWrite(MOTORL00, 1);
    digitalWrite(MOTORL01, 0);
    digitalWrite(MOTORR00, 1);
    digitalWrite(MOTORR01, 0);
    analogWrite(MOTORL, BASESPEED/2);
    analogWrite(MOTORR, BASESPEED/2 + calib);
  }
}
void stp(){
  analogWrite(MOTORL, 0);
  analogWrite(MOTORR, 0);
  delay(1000);
}
void turnRight() {
  int adjus = 0;
  if (analogRead(1) > THRE) adjus = 20;
  if (analogRead(2) > THRE) adjus = 10;
  if (analogRead(5) > THRE) adjus = -10;
  if (analogRead(6) > THRE) adjus = -20;
  digitalWrite(MOTORL00, 0);
  digitalWrite(MOTORL01, 1);
  digitalWrite(MOTORR00, 0);
  digitalWrite(MOTORR01, 1);
  analogWrite(MOTORL, 60);
  analogWrite(MOTORR, 60);
  while (analogRead(7) < THRE);
  digitalWrite(MOTORL00, 1);
  digitalWrite(MOTORL01, 0);
  digitalWrite(MOTORR00, 0);
  digitalWrite(MOTORR01, 1);
  analogWrite(MOTORL, 80 + adjus);
  analogWrite(MOTORR, 80);
  delay(1500);
  while ((analogRead(0) > THRE && analogRead(7) > THRE) != 1) {
    if (analogRead(0) < THRE) {
      digitalWrite(MOTORR00, 0);
      digitalWrite(MOTORR01, 1);
      analogWrite(MOTORR, 60);
    }
    else {
      digitalWrite(MOTORR00, 1);
      digitalWrite(MOTORR01, 0);
      analogWrite(MOTORR, 60);
    }
    if (analogRead(7) > THRE) {
      digitalWrite(MOTORL00, 0);
      digitalWrite(MOTORL01, 1);
      analogWrite(MOTORL, 60);
    }
    else {
      digitalWrite(MOTORL00, 1);
      digitalWrite(MOTORL01, 0);
      analogWrite(MOTORL, 60);
    }
  }
  analogWrite(MOTORR,0);
  digitalWrite(MOTORL00,1);
  digitalWrite(MOTORL01,0);
  analogWrite(MOTORL,70);
  while(analogRead(7)>THRE);
}
void turnLeft() {
  int adjus = 0;
  if (analogRead(1) > THRE) adjus = 20;
  if (analogRead(2) > THRE) adjus = 10;
  if (analogRead(5) > THRE) adjus = -10;
  if (analogRead(6) > THRE) adjus = -20;
  digitalWrite(MOTORL00, 0);
  digitalWrite(MOTORL01, 1);
  digitalWrite(MOTORR00, 0);
  digitalWrite(MOTORR01, 1);
  analogWrite(MOTORL, 60);
  analogWrite(MOTORR, 60);
  while (analogRead(0) < THRE);
  digitalWrite(MOTORL00, 0);
  digitalWrite(MOTORL01, 1);
  digitalWrite(MOTORR00, 1);
  digitalWrite(MOTORR01, 0);
  analogWrite(MOTORL, 80 + adjus);
  analogWrite(MOTORR, 80);
  delay(1500);
  while ((analogRead(0) > THRE && analogRead(7) > THRE) != 1) {
    if (analogRead(0) > THRE) {
      digitalWrite(MOTORR00, 0);
      digitalWrite(MOTORR01, 1);
      analogWrite(MOTORR, 60);
    }
    else {
      digitalWrite(MOTORR00, 1);
      digitalWrite(MOTORR01, 0);
      analogWrite(MOTORR, 60);
    }
    if (analogRead(7) > THRE) {
      digitalWrite(MOTORL00, 1);
      digitalWrite(MOTORL01, 0);
      analogWrite(MOTORL, 60);
    }
    else {
      digitalWrite(MOTORL00, 0);
      digitalWrite(MOTORL01, 1);
      analogWrite(MOTORL, 60);
    }
  }
  analogWrite(MOTORL, 0);
  digitalWrite(MOTORR00, 1);
  digitalWrite(MOTORR01, 0);
  analogWrite(MOTORR,70);
  while(analogRead(0)>THRE);
}
void setOnLine(int mode){
  // mode = 0: forward
  // mode = 1: backward
  black = 0;
  int rotate = 0;
  int isBlack;
  while (true){
    black = 0;
    rotate = 0;
    for (int i = 0; i < 8; i++){
      refrection[i] = analogRead(i);
      if (refrection[i] > THRE){
        isBlack = 1;
        black++;
      }
      else{
        isBlack = 0;
      }
      if (i <= 3){
        rotate += isBlack * (i - 4) * 2;
      }
      else{
        rotate += isBlack * (i - 4 + 1) * 2;
      }
    }
    if (black <= 1){
      digitalWrite(MOTORL00, 1 - mode);
      digitalWrite(MOTORL01, 0 + mode);
      digitalWrite(MOTORR00, 1 - mode);
      digitalWrite(MOTORR01, 0 + mode);
      analogWrite(MOTORL, 50);
      analogWrite(MOTORR, 50);
    }
    else if (black == 7){
      analogWrite(MOTORL, 0);
      analogWrite(MOTORR, 0);
      break;
    }
    else{
      if (rotate <= 0){
        digitalWrite(MOTORL00, 1 - mode);
        digitalWrite(MOTORL01, 0 + mode);
        digitalWrite(MOTORR00, 0 + mode);
        digitalWrite(MOTORR01, 1 - mode);
        analogWrite(MOTORL, 6 * rotate * (-1));
        analogWrite(MOTORR, 6 * rotate * (-1));
      }
      else{
        digitalWrite(MOTORL00, 0 + mode);
        digitalWrite(MOTORL01, 1 - mode);
        digitalWrite(MOTORR00, 1 - mode);
        digitalWrite(MOTORR01, 0 + mode);
        analogWrite(MOTORL, 6 * rotate);
        analogWrite(MOTORR, 6 * rotate);
      }
    }
    delay(10);
  }
}
void grip(){
  digitalWrite(MOTOR300, 1);
  digitalWrite(MOTOR301, 0);
  analogWrite(MOTOR3, 235);
  delay(500);
  analogWrite(MOTORL, 0);
  analogWrite(MOTORR, 0);
  analogWrite(MOTOR3, 135);
  delay(1300);
  analogWrite(MOTOR3, 0);
  digitalWrite(MOTOR300, 1);
  digitalWrite(MOTOR301, 1);
}
void liftup(){
  digitalWrite(MOTOR400, 1);
  digitalWrite(MOTOR401, 0);
  analogWrite(MOTOR4, 255);
  delay(1500);
  digitalWrite(MOTOR400, 1);
  digitalWrite(MOTOR401, 1);
  analogWrite(MOTOR4, 0);
  delay(2000);
}
void unload(){
  digitalWrite(MOTOR400, 0);
  digitalWrite(MOTOR401, 1);
  analogWrite(MOTOR4, 100);
  delay(1500);
  analogWrite(MOTOR4, 0);
  digitalWrite(MOTOR400, 1);
  digitalWrite(MOTOR401, 1);
}
void releasee(){
  digitalWrite(MOTOR300, 0);
  digitalWrite(MOTOR301, 1);
  analogWrite(MOTOR3, 125);
  delay(1500);
  analogWrite(MOTOR3, 0);
  digitalWrite(MOTOR300, 1);
  digitalWrite(MOTOR301, 1);
}
