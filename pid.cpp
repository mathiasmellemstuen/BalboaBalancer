#include "pid.h"

float previousError = 0; 
float integral = 0; 

float pid(const float& kp, const float& ki, const float& kd, const float& wantedValue, const float& sensorValue, const float& deltaTime) {
    float error = wantedValue - sensorValue;
    integral = integral + error * deltaTime;
    float derivative = (error - previousError) / deltaTime; 
    float output = kp * error + ki * integral + kd * derivative;
    previousError = error; 

    return output; 
}