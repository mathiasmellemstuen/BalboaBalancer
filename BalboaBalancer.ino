#include "sensor.h"
#include <Balboa32U4.h>
#include <LSM6.h>
#include <Wire.h>
#include "pid.h"

Balboa32U4Buzzer buzzer;
Balboa32U4Motors motors;
void setup() {
  Serial.begin(9600);
  buzzer.play("!L30 V8 cdefgab>cbagfedc");
  sensorSetup(); 
}

void loop() {

  sensorUpdate();

  float pidValue = pid(1.0f, 0.0f, 0.0f, 0.0f, getGyroscopeAngle(),0.1);

  Serial.println(pidValue); 

  motors.setSpeeds(-pidValue, -pidValue); 
  delay(100);
} 