#include "arduino_secrets.h"
#include "thingProperties.h"
#include <DHT.h>
// #include <Arduino.h>
///Count Animal
#define TRIGGER_PIN_1 2  // Connected to D2 (GPIO 2) - Trigger pin of Ultrasonic Sensor 1
#define ECHO_PIN_1 15     // Connected to D15 (GPIO 15) - Echo pin of Ultrasonic Sensor 1
#define TRIGGER_PIN_2 21  // Connected to D21 (GPIO 21) - Trigger pin of Ultrasonic Sensor 2
#define ECHO_PIN_2 19     // Connected to D19 (GPIO 19) - Echo pin of Ultrasonic Sensor 2

#define DHT_PIN 18  // Replace with the actual pin connected to the DHT22 sensor
#define DHT_TYPE DHT22
// Pin definitions
#define SOIL_MOISTURE_PIN  32  // Pin connected to SIG pin of the sensor
#define RAIN_SENSOR_PIN 33   // Pin connected to rain sensor
DHT dht(DHT_PIN, DHT_TYPE);


int LED = 13;

void setup() {
  //Ultrsonic pin
  pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  
  pinMode(LED, OUTPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT); // Set sensor pin as input
  pinMode(RAIN_SENSOR_PIN, INPUT);    // Set rain sensor pin as input


  // Initialize DHT sensor
  dht.begin();


  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // ArduinoCloud.addProperty(arduinoPinState, READWRITE, ON_CHANGE, NULL);


  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  
  int sensorValue = analogRead(SOIL_MOISTURE_PIN);
  int rainSensorValue = analogRead(RAIN_SENSOR_PIN);

  int moisturePercentage = map(sensorValue, 0, 1023, 0, 100);

  // Your code here
  // Read temperature and humidity from the DHT sensor
  // cattleShedTemperature = moisturePercentage;
  cattleShedTemperature = dht.readTemperature();


  // Read selected value from the dropdown property
  // String cattleExaust = cattleShedExhaust;

  // // Perform actions based on the selected mode
  if (cattleShedExhaust == 0) {
    //if value matches, execute code
    Serial.write('0');
  } else if (cattleShedExhaust == 1) {
    Serial.write('1');
  } else if (cattleShedExhaust == 2){
    if (cattleShedTemperature >= 30) {
      Serial.write('1');
    } else {
      Serial.write('0');
    }
  }

    // // Perform actions based on the selected mode
  if (motorPump == 0) {
    //if value matches, execute code
    Serial.write('2');
  } else if (motorPump == 1) {
    Serial.write('3');
  } else if (motorPump == 2){
    if (moisturePercentage <= 45) {
      Serial.write('3');
    } else {
      Serial.write('2');
    }
  }

    // // Perform actions based on the selected mode
  if (roof == 0) {
    //if value matches, execute code
    Serial.write('4');
  } else if (roof == 1) {
    Serial.write('5');
  } else if (roof == 2){
    if (rainSensorValue > 500) {
      Serial.write('5');
    } else {
      Serial.write('4');
    }
  }
  
  // Measure distance for Sensor 1
  digitalWrite(TRIGGER_PIN_1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_1, LOW);

  long duration_1 = pulseIn(ECHO_PIN_1, HIGH);
  float distance_1 = duration_1 * 0.0343 / 2;

  // Measure distance for Sensor 2
  digitalWrite(TRIGGER_PIN_2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_2, LOW);

  long duration_2 = pulseIn(ECHO_PIN_2, HIGH);
  float distance_2 = duration_2 * 0.0343 / 2;

  // Update animal count based on distances
  if (distance_1 < 20) {  // Adjust threshold as needed
    countAnimal ++;
  }
  if (distance_2 < 20 and countAnimal >= 0) { // Adjust threshold as needed
    countAnimal --;
  }
  delay(500);
}





/*
  Since Command is READ_WRITE variable, onCommandChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onCommandChange()  {
  // Add your code here to act upon Command change
}
/*
  Since CattleShedExhaust is READ_WRITE variable, onCattleShedExhaustChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onCattleShedExhaustChange()  {
  // Add your code here to act upon CattleShedExhaust change

}
/*
  Since MotorPump is READ_WRITE variable, onMotorPumpChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMotorPumpChange()  {
  // Add your code here to act upon MotorPump change
}
/*
  Since Roof is READ_WRITE variable, onRoofChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRoofChange()  {
  // Add your code here to act upon Roof change
}