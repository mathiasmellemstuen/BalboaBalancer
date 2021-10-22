#include "balancer.h"
#include <Balboa32U4.h>

void balancerSetup() {
    // Init IMU


    balancerCalibrateGyro();
}
void isBalancing() {

}

void balancerUpdate() {

}

void balancerUpdateSensors() {

}

void balancerResetEncoders() {

}

void balancerCalibrateGyro() {
    int total = 0;

    for (int i = 0; i < CALIBRATION_ITERATIONS; i++) {
        // Read IMU
        // total += imu.g.y;
        // Sleep 1 milisec
    }

    variables.GYZero = total / CALIBRATION_ITERATIONS;
}

int calculateMotorSpeed(int risingAngleOffset) {
    int angleResponse = ANGLE_RESPONSE * risingAngleOffset;
    int distanceResponse = DISTANCE_RESPONSE * (variable.distance.left + variables.distance.right);
    int speedResponse = SPEED_RESPONSE * (variable.speed.left + variables.speed.right);
    
    return (angleResponse + distanceResponse + speedResponse) / 100 / GEAR_RATIO;
}

// Main code loop for balancing the robot
void balance() {
    variables.angle = variables.angle * 999 / 1000;
    int risingAngleOffset = variables.angleRate * ANGLE_RATE_RATIO + variables.angle;
    
    variables.motorSpeed += calculateMotorSpeed(risingAngleOffset);

    int distanceDiff = varaibles.distance.left - variables.distance.right;

    // TODO: Change to motorSpeed function
    LAR motorSpeed = {
        variables.motorSpeed + distanceDiff * DISTANCE_DIFF_RESPONSE / 100,
        variables.motorSpeed - distanceDiff * DISTANCE_DIFF_RESPONSE / 100
    };
}

void lyingDown() {
    variables.motorSpeed = 0;
    vairables.distance = LAR;
    
    // TODO: Change to motorSpeed function
    LAR motorSpeed = {0,0};

    if (variable.angleRate > -2 && variable.angleRate < 2) {
        // variables.angle = atan2(imu.a.x, imu.a.y) * 57296;

        variable.distance = LAR;
    }
}


