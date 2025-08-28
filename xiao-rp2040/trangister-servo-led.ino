#include <Servo.h>

int servoButton = D1;
int irButton = A2;
int ledButton = D3;

Servo myservo;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // make the irButton's pin an input:
  pinMode(irButton, INPUT);
  myservo.attach(servoButton);  // attaches the servo on GIO2 to the servo object
  pinMode(ledButton, OUTPUT);

}

void loop() {
  // read the input pin:
    int buttonState = analogRead(irButton);
    Serial.println(buttonState);
    if (buttonState < 500){

        Serial.println("IR recieved!");
        digitalWrite(ledButton, HIGH);

        int pos;
        Serial.println("servo 0");
        for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }

        Serial.println("servo 90");
        delay(3000);

      for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      digitalWrite(ledButton, LOW);
    }
    delay(1000);
}