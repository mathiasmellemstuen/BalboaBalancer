#include "sensor.h"
#include <Balboa32U4.h>
#include <LSM6.h>
#include <Wire.h>
#include "pid.h"
#include "balancer.h"

Balboa32U4Motors motors;
Balboa32U4Encoders encoders;
Balboa32U4ButtonA button; 

bool firstPass = true, doDrive = false;

void setup() {
    Serial.begin(9600);
      
    sensorSetup(); 
}

void loop() {
    Serial.print("kake");

    if (button.getSingleDebouncedRelease()) {
        firstPass = false;
        
        sensorUpdate();

        if (doDrive) {
            drive(-300);
            delay(300);
            drive(300);
            delay(300);
        }
    }

    int angleRange = 10;
    float desiredAngle = 80.0f;
    int angle = getAngle();

    int pidValue = 0;

    if (angle < desiredAngle + angleRange && angle > desiredAngle - angleRange) {
        pidValue = 0;

        // TODO: Recalibreate the Gyro to move it closer to 0. At this angle the robot is "balancing" . This wil make up for the gyro drifting
    } else {
        pidValue = pid(20.0f, 0.0f, 0.0f, desiredAngle, angle, 0.1, 0.5f); 
    }

    if (firstPass == false && doDrive) {
        drive(pidValue);
    }

    // Serial.print("\t\tPID: ");
    // Serial.println(pidValue);

    // Serial.print("error: ");
    // Serial.println(80.0f - getAngle());

    // Serial.println("\n");

    delay(10);
}