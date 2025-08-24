#include <Servo.h>
int irButton = D2;
int irRecievedCount = 0;


Servo myservo;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // make the irButton's pin an input:
  pinMode(irButton, INPUT_PULLUP);
  myservo.attach(D1);  // attaches the servo on GIO2 to the servo object
}

// the loop routine runs over and over again forever:

void loop() {
  // read the input pin:
    int buttonState = digitalRead(irButton);

  // print out the state of the button:
    if (buttonState == 0){
        irRecievedCount++;

        Serial.println("IR recieved!");
        Serial.print("count: ");
        Serial.println(irRecievedCount);

        int pos;
        Serial.println("servo 0");
        for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }

        Serial.println("servo 90");
        delay(2000);

      for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
    }
    delay(100);
}