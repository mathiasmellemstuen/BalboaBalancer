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
    if (button.getSingleDebouncedRelease()) {
        firstPass = false;

        drive(-300);
        delay(300);
        drive(300); 
        delay(300);
    }

    sensorUpdate();

    int angleRange = 10;
    float desiredAngle = 80.0f;
    int angle = getAngle();

    float pidValue = pid(20.0f, 0.0f, 0.0f, desiredAngle, angle, 0.1, 0.5f);
    if (angle < desiredAngle + angleRange && angle > desiredAngle - angleRange) {
        pidValue = 0;
    }

    if (firstPass == false) {
        // pidValue = pid(10.0f, 1.0f, 1.0f, 80.0f, getAngle(), 0.1);
        drive(pidValue);
    }

    Serial.print("\t\tPID: ");
    Serial.println(pidValue);

    // Serial.print("error: ");
    // Serial.println(80.0f - getAngle());

    Serial.println("\n");

    delay(10);
}