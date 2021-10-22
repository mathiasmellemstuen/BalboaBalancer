#ifndef BALANCER
#define BALANCER

#include <math.h>

// Struct to hold left and right values. For more somple code
struct LAR {
    int left = 0;
    int right = 0;
};

const struct BalboaPinLayout {
    const int MOTOR_LEFT_DIRECTION = 16;
    const int MOTOR_RIGHT_DIRECTION = 15;
    const int MOTOR_LEFT_SPEED = 10;
    const int MOTOR_RIGHT_SPEED = 9;
} balboaPinLayout;

enum BalboaConstants {
    GEAR_RATIO = 111,
    MOTOR_SPEED_LIMIT = 300,
    ANGLE_RATE_RATIO = 140,
    ANGLE_RESPONSE = 12,
    DISTANCE_RESPONSE = 90,
    DISTANCE_DIFF_RESPONSE = -50,
    SPEED_RESPONSE = 3300,
    CALIBRATION_ITERATIONS = 100,

    UPDATE_TIME = 1, // Multiply by 100 to get Hz
};

struct Vars {
    float GYZero = 0.0;
    int angle = 0;
    int angle_rate = 0;
    int nextUpdate = 0;
    int motorSpeed = 0;

    LAR speed;
    LAR drive;
    LAR lastCounts;
    LAR distance;

    bool calibated = false;
    bool balancing = false;
    bool running = false;
};

int imu = 0;

Vars vars;

void Setup() {
    int total = 0;

    for (int i = 0; i < CALIBRATION_ITERATIONS; i++) {
        // Read IMU
        // total += imu.g.y
    }

    vars.GYZero = total / CALIBRATION_ITERATIONS;
    vars.calibated = true;
}

void Start() {
    if (vars.calibated && !vars.running) {
        vars.running = true;
        // Sett time for next update
        // update loop() In thread?
    } else {
        // There is a problem
    }
}

void Stop() {
    if (vars.running) {
        vars.running = false;
        // Join thread
    }
}

void Reset() {
    vars.motorSpeed = 0;
    ResetEncoders();

    if (std::abs(vars.angle_rate) < 2) {
        if (imu > 0) { // imu.a.z
            vars.angle = 110;
        } else {
            vars.angle = -110;
        }
    }
}

void ResetEncoders() {
    vars.distance = {0,0};
}

void StandUp() {
    if (vars.calibated) {
        int sign = 1;

        if (imu == 0) { // imu.a.z
            sign = -1;
        }

        Stop();
        Reset();
        // imu.read()
        // Motors(sign*MOTOR_SPEED_LIMIT, -sign*MOTOR_SPEED_LIMIT)
        // Wait for 0.4s
        // Motors(-sign*MOTOR_SPEED_LIMIT, sign*MOTOR_SPEED_LIMIT)

        for (int i = 0 ; i <= 40; i++) {
            
        }
    }
}

#endif