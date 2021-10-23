#include "balancer.h"
#include <Balboa32U4.h>
#include <Wire.h>

void balancerSetup() {
    // Init imuT
    Wire.begin();
    if (!imuT.init()) {
        while(true) {
            // Serial.println("Failed to detect imuT");
        }
    }
    imuT.enableDefault();
    imuT.writeReg(LSM6::CTRL2_G, 0b01011000);

    // Wait for imuT to sabilize
    delay(10000);

    balancerCalibrateGyro();
}

void balancerUpdate() {
    unsigned int lastMillis;
    unsigned int ms = millis();
    int count = 0;

    // Make the update only on the desired Hz
    if ((ms - lastMillis) < (UPDATE_TIME / 100)) {
        return;
    }

    variables.balanceUpdateDelayStatus = ms - lastMillis > (UPDATE_TIME / 100) + 1;
    lastMillis = ms;

    balancerUpdateSensors();
    
    // Check if the robot is trying to balance or if it is laying down. Then do the correct thign
    if (variables.balancing) {
        balanceing();
        
        if (abs(variables.angle) > STOP_BALANCING_ANGLE) {
            if (++count > 5) {
                variables.balancing = false;
                count = 0;
            }
        } else {
            count = 0;
        }
    } else {
        lyingDown();

        if (abs(variables.angle) < START_BALANCING_ANGLE) {
            if (++count > 5) {
                variables.balancing = true;
                count = 0;
            }
        } else {
            count = 0;
        }
    }
}

void balancerUpdateSensors() {
    imuT.read();
    integrateGyro();
    integrateEncoders();
}

void balancerResetEncoders() {
    variables.distance = LAR();
}

void balancerCalibrateGyro() {
    int total = 0;

    for (int i = 0; i < CALIBRATION_ITERATIONS; i++) {
        imuT.read();
        total += imuT.g.y;
        delay(1);
    }

    variables.GYZero = total / CALIBRATION_ITERATIONS;
}

int calculateMotorSpeed(int risingAngleOffset) {
    // Calculate the speed the wheels need to turn
    int angleResponse = ANGLE_RESPONSE * risingAngleOffset;
    int distanceResponse = DISTANCE_RESPONSE * (variables.distance.left + variables.distance.right);
    int speedResponse = SPEED_RESPONSE * (variables.speed.left + variables.speed.right);
    
    int motorSpeed = (angleResponse + distanceResponse + speedResponse) / 100 / GEAR_RATIO;

    // Check if the speed is inside of the speed limit
    if (motorSpeed > MOTOR_SPEED_LIMIT)
        motorSpeed = MOTOR_SPEED_LIMIT;
    if (motorSpeed < -MOTOR_SPEED_LIMIT)
        motorSpeed = -MOTOR_SPEED_LIMIT;

    return motorSpeed;
}

// Main code loop for balancing the robot
void balanceing() {
    variables.angle = variables.angle * 999 / 1000;
    int risingAngleOffset = variables.angleRate * ANGLE_RATE_RATIO + variables.angle;
    
    variables.motorSpeed += calculateMotorSpeed(risingAngleOffset);

    int distanceDiff = variables.distance.left - variables.distance.right;

    motorsT.setSpeeds(
        variables.motorSpeed + distanceDiff * DISTANCE_DIFF_RESPONSE / 100,
        variables.motorSpeed - distanceDiff * DISTANCE_DIFF_RESPONSE / 100
    );
}

void lyingDown() {
    variables.motorSpeed = 0;
    variables.distance = LAR();
    
    motorsT.setSpeeds(0,0);

    if (variables.angleRate > -2 && variables.angleRate < 2) {
        variables.angle = atan2(imuT.a.x, imuT.a.y) * 57296;

        variables.distance = LAR();
    }
}

void integrateGyro() {
    variables.angleRate = (imuT.g.y - variables.GYZero) / 29;
    variables.angle += variables.angleRate * UPDATE_TIME;
}

void integrateEncoders() {
    // Make counts for left and right
    LAR lastCounts;
    LAR counts;
    counts.left = encodersT.getCountsLeft();
    counts.right = encodersT.getCountsRight();
    

    // Calculate counts for left the right
    variables.speed.left = (counts.left - lastCounts.left);
    variables.distance.left += counts.left - lastCounts.left;
    lastCounts.left = counts.left;

    variables.speed.right = (counts.right - lastCounts.right);
    variables.distance.right += counts.right - lastCounts.right;
    lastCounts.right = counts.right;
}