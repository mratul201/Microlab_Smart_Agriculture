// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "30e7ad3b-03e6-4e2d-bfd5-8097a9b92e2a";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onCattleShedExhaustChange();
void onMotorPumpChange();
void onRoofChange();

int cattleShedExhaust;
int cattleShedTemperature;
int countAnimal;
int motorPump;
int roof;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(cattleShedExhaust, READWRITE, ON_CHANGE, onCattleShedExhaustChange);
  ArduinoCloud.addProperty(cattleShedTemperature, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(countAnimal, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(motorPump, READWRITE, ON_CHANGE, onMotorPumpChange);
  ArduinoCloud.addProperty(roof, READWRITE, ON_CHANGE, onRoofChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
