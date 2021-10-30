#include "sensor.h"
#include <Balboa32U4.h>
#include <LSM6.h>
#include <Wire.h>
#include "pid.h"
#include "balancer.h"

Balboa32U4Motors motors;
Balboa32U4Encoders encoders;
Balboa32U4ButtonA button; 

void setup() {
  Serial.begin(9600);
   
  sensorSetup(); 
}

bool firstPass = true;

void loop() {
  if(button.getSingleDebouncedRelease()) {
    firstPass = false;

    drive(-300);
    delay(300);
    drive(300); 
    delay(300); 
  }

  sensorUpdate();

  float pidValue = pid(40.0f, 0.0f, 3.0f, 80.0f, getAngle(), 0.1, 0.5f);

  if(firstPass == false) {
    // pidValue = pid(10.0f, 1.0f, 1.0f, 80.0f, getAngle(), 0.1);
    drive(pidValue);
  }

  Serial.print("\t\tPID: ");
  Serial.println(pidValue);

  Serial.print("error: ");
  Serial.println(80.0f - getAngle());

  delay(10);
}