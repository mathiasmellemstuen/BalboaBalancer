#ifndef BALANCER
#define BALANCER

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

struct BalboaConstants {
    int GEAR_RATIO = 111;
    int MOTOR_SPEED_LIMIT = 300;
    int ANGLE_RATE_RATIO = 140;
    int ANGLE_RESPONSE = 12;
    int DISTANCE_RESPONSE = 90;
    int DISTANCE_DIFF_RESPONSE = -50;
    int SPEED_RESPONSE = 3300;
    int CALIBRATION_ITERATIONS = 100;

    float UPDATE_TIME = 0.01;
};


#endif