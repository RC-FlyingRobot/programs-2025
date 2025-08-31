#include <Servo.h>

const int SERVO_PIN = D1;
const int IR_SENSOR_PIN = A2;
const int LED_PIN = D3;

// servo 設定
const int SERVO_DEGREE = 53;
const int SERVO_STEP_DELAY = 15;

// delay 設定
const int SERVO_STOP_DELAY = 3000;
const int MAIN_LOOP_DELAY = 1000;

// 赤外線センサーのしきい値
const int INFRARED_THRESHOLD = 500;

Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(IR_SENSOR_PIN, INPUT);
  myservo.attach(SERVO_PIN);
  pinMode(LED_PIN, OUTPUT);
  myservo.write(0);

}

void loop() {
    int infraredPinPotential = analogRead(IR_SENSOR_PIN);
    Serial.println(infraredPinPotential);
    if (infraredPinPotential < INFRARED_THRESHOLD){

        Serial.println("IR received!");
        digitalWrite(LED_PIN, HIGH);

        int pos;
        Serial.println("servo 0");
        for (pos = 0; pos <= SERVO_DEGREE; pos += 1) {
            // in steps of 1 degree
            myservo.write(pos);
            delay(SERVO_STEP_DELAY);
        }

        Serial.printf("SERVO_DEGREE: %d\n", SERVO_DEGREE);
        delay(SERVO_STOP_DELAY);

      for (pos = SERVO_DEGREE; pos >= 0; pos -= 1) {
        myservo.write(pos);
        delay(SERVO_STEP_DELAY);
      }
      digitalWrite(LED_PIN, LOW);
    }
    delay(MAIN_LOOP_DELAY);
}