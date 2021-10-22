#ifndef BALBOA_BALANCER_BALANCER
#define BALBOA_BALANCER_BALANCER

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

    UPDATE_TIME = 1, // Multiply by 100 to get Hz
};

struct Variables {
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

} variables;

void balancerSetup();
void isBalancing();
void balancerUpdate();
void balancerUpdateSensors();
void balancerResetEncoders();

#endif