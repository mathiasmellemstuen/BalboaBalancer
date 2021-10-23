#ifndef BALBOA_BALANCER_BALANCER
#define BALBOA_BALANCER_BALANCER

#include <LSM6.h>
#include <Balboa32U4.h>

// Struct to hold left and right values. For more somple code
struct LAR {
    int left = 0;
    int right = 0;
};

enum BalboaConstants {
    GEAR_RATIO = 111,
    MOTOR_SPEED_LIMIT = 300,
    ANGLE_RATE_RATIO = 140,
    ANGLE_RESPONSE = 12,
    DISTANCE_RESPONSE = 90,
    DISTANCE_DIFF_RESPONSE = -50,
    SPEED_RESPONSE = 3300,
    CALIBRATION_ITERATIONS = 100,

    START_BALANCING_ANGLE = 45000,  // 45 Deg 
    STOP_BALANCING_ANGLE = 70000,   // 70 Deg

    UPDATE_TIME = 1, // Devide by 100 to get Hz
};

struct Variables {
    float GYZero = 0.0;
    int angle = 0;      // Millidegrees
    int angleRate = 0; // degrees / s
    int nextUpdate = 0;
    int motorSpeed = 0;

    LAR speed;
    LAR drive;
    LAR lastCounts;
    LAR distance;

    bool calibated = false;
    bool balancing = false;
    bool running = false;

    bool balanceUpdateDelayStatus = false;

} variables;

LSM6 imuT;
Balboa32U4Motors motorsT;
Balboa32U4Encoders encodersT;

void balanceing();
void lyingDown();

void balancerSetup();
void balancerUpdate();
void balancerUpdateSensors();
void balancerResetEncoders();
void balancerCalibrateGyro();

void integrateGyro();
void integrateEncoders();

#endif