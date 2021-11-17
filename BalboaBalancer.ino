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

void printThing(const char* lable, int value) {
  Serial.print(lable);
  Serial.print(' ');
  Serial.println(value);
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

  int angle = getAngle();
  float desiredAngle = 7.0f;
  float angleNotMove = 10.0f;

  float pidValue = 0;

  if (angle > desiredAngle - angleNotMove && angle < desiredAngle + angleNotMove) {
    // The robot is standing so dont move
    pidValue = 0;
  } /* else if (angle < 5 || angle > 170){
    // The robot has fallen and cant get up
    pidValue = 0;
  } */ else {
    // The robot is moving so run the PID
    pidValue += pid(100.0f, 0.0f, 15.0f, desiredAngle, getAngle(), 0.1, 0.5f);
  }

  if(firstPass == false) {
    // pidValue = pid(10.0f, 1.0f, 1.0f, 80.0f, getAngle(), 0.1);
    drive(-pidValue);
  }

  printThing("PID:", pidValue);
  printThing("Error:", desiredAngle - angle);
  printThing("Angle:", angle);

  // Serial.print("\t\tPID: ");
  // Serial.println(pidValue);

  // Serial.print("error: ");
  // Serial.println(desiredAngle - getAngle());

  delay(10);
}