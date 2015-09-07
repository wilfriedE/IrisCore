#include <Servo.h>

//int incomingByte = 0;   // for incoming serial data
String incomingAction;
int incomingValue;
Servo hzServo, vcServo;
int lazerPin = 13;  

void setup() {
  Serial.begin(9600);
  hzServo.attach(7);
  vcServo.attach(9);
  pinMode(lazerPin, OUTPUT);
  digitalWrite(lazerPin, HIGH);
}
 
void loop() {
 
        // Listen for transmitted data:
        if (Serial.available() > 0) {
                //Listen for action: 
                incomingAction = Serial.readStringUntil(':');
                incomingValue = Serial.readString().toInt();
                if (incomingAction == "H") {
                  Serial.println("Moving Horizontaly");
                  moveHorizontalServos(incomingValue);
                }
                if (incomingAction == "V") {
                  Serial.println("Moving Verticaly");
                  moveVerticalServos(incomingValue);
                }
                if (incomingAction == "C") {
                  Serial.println("Calibrating...");
                  moveHorizontalServos(90);
                  moveVerticalServos(90);
                  controlLight(0);
                }
                if (incomingAction == "L") {
                  Serial.println("Controlling Light");
                  controlLight(incomingValue);
                }
        }
}

void moveHorizontalServos(int degree) {
      hzServo.write(degree);             // tell servo to go to position in variable 'pos' 
 }

 
void moveVerticalServos(int degree) {
      vcServo.write(degree);              // tell servo to go to position in variable 'pos' 
}

void controlLight(int state) {
  if (state == 1) {
    digitalWrite(lazerPin, LOW);
  }
  else {
    digitalWrite(lazerPin, HIGH);
  }
}
