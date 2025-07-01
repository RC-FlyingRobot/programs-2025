#include <Servo.h> // サーボモーターを制御するためのライブラリをインクルード

// ピンの定義
const int pirPin = 2;   // 赤外線人感センサーのOUTピンをArduinoのデジタルピン2に接続
const int servoPin = 9; // サーボモーターの信号線をArduinoのデジタルピン9に接続

// サーボオブジェクトの作成
Servo myServo;

// 割り込み処理用のフラグ
volatile bool motionDetected = false; // volatileキーワードは、割り込みルーチン内で変更される変数に使用します

// --- ここに関数の前方宣言を追加 ---
// 割り込みサービスルーチン (ISR) の前方宣言
void detectMotion();

void setup() {
  Serial.begin(9600); // シリアル通信の開始（デバッグ用）
  Serial.println("Arduino PIR Sensor & Servo Control");

  pinMode(pirPin, INPUT); // PIRセンサーのピンを入力に設定

  // サーボモーターをピンにアタッチ
  myServo.attach(servoPin);
  myServo.write(0); // 初期位置を0度にする（サーボによっては90度が中央の場合もあります）

  // PIRセンサーのHIGHへの立ち上がりで割り込みを発生させる
  attachInterrupt(digitalPinToInterrupt(pirPin), detectMotion, RISING);
}

void loop() {
  // 割り込みフラグがセットされたらサーボを動かす
  if (motionDetected) {
    Serial.println("Motion detected! Moving servo...");
    myServo.write(90); // サーボを90度回す
    delay(2000);       // 2秒間待つ（サーボが動き終わるのを待つ）
    myServo.write(0);  // サーボを元の位置に戻す
    Serial.println("Servo returned to 0 degrees.");

    // フラグをリセット
    motionDetected = false;
  }

  // メインループでは他の処理も実行できる
  // 例: LEDを点滅させる、別のセンサーを読むなど
}

// 割り込みサービスルーチン (ISR) の定義
// nRF52840では IRAM_ATTR は不要です
void detectMotion() {
  motionDetected = true;
}