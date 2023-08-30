#include <Servo.h>
#include <AFMotor.h>  // Include the AFMotor library
// Pin definitions
// const int moistureSensorPin A1;

const int servoPin = 10;
const int motorSpeed = map(50, 0, 100, 0, 255);  // Adjust percentage as needed
int LDRInput = A0;
int LED = 13;
const long interval = 3600000;
// Create servo object
Servo servo1;
// Create motor shield object
AF DCMotor motor1(1);  // Motor 1 on M1/M2
AF_DCMotor motor2(2);
// Motor 2 on M3/M4
AF DCMotor motor3(3);
AF DCMotor motor4(4);

void setup() {
  // Initialize motor shield
  motor1.setSpeed(255);  // Adjust motor speed as needed motor2.setSpeed(255); // Adjust motor speed as needed
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  // Attach servo to its pin
  servo1.attach(servopin);
  pinMode(LDRInput, INPUT);
  pinMode(LED, OUTPUT);
  // Other setup code... Serial.begin(9600);
}

void loop() {
  int value = analogRead(LDRInput);
  if (value < 300) {
    digitalWrite(LED, LOW);
    digitalWrite(LED, HIGH);
  } else {
  }
  delay(500);
  // Control feeding mechanism using servo
  if (shouldFeed()) {
    servo1.write(0);   // Open the feeding mechanism (adjust angle as needed) delay(1000); // wait for servo movement
    servo1.write(90);  // Close the feeding mechanism
  }
  //Sweeping Mechanism
  motor3.run(FORWARD);
  motor3.run(FORWARD);
  motor3.run(FORWARD);
  motor3.run(FORWARD);
  motor3.run(FORWARD);
  motor3.run(FORWARD);
  motor3.run(RELEASE);
  //Sweeping Mechanism
  motor3.run(BACKWARD);
  motor3.run(BACKWARD);
  motor3.run(BACKWARD);
  motor3.run(BACKWARD);
  motor3.run(BACKWARD);
  motor3.run(BACKWARD);

  if (Serial.available() > 0) {
    char command = Serial.read();  // Read incoming command from ESP32
    ///Cattle shed
    if (command == '1') {
      motor1.run(FORWARD);
    } else if (command == '0') {
      motor1.run(RELEASE);
      ///Motor Pump
    } else if (command == '2') {
      motor2.run(RELEASE);
    } else if (command == '3') {
      motor2.run(FORWARD);
    } else if (command == '4') {
      // motor.run(RELEASE);
      motor4.run(FORWARD);
      motor4.run(FORWARD);
      motor4.run(FORWARD);
      motor4.run(FORWARD);
      motor4.run(RELEASE);
    } else if (command == '5') {
      //motor.run(RELEASE);
      motor4.run(BACKWARD);
      motor4.run(BACKWARD);
      motor4.run(BACKWARD);
      motor4.run(BACKWARD);
      motor4.run(RELEASE);
    }
  }
}

bool shouldFeed() {
    static unsigned long lastFeedTime = 0; unsigned long currentTime = millis();
    // Feed every one hour
    if (currentTime - lastFeedTime >= interval) { // 3600000 milliseconds = 1 hour
        lastFeedTime = currentTime;
        return true;
    }
    return false;
}