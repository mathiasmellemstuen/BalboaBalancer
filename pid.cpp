#include "pid.h"

float previousError = 0; 
float previousSmooth = 0;
float integral = 0;

float pid(const float& kp, const float& ki, const float& kd, const float& wantedValue, const float& sensorValue, const float& deltaTime, const float& T) {
    float error = wantedValue - sensorValue;
    integral = integral + error * deltaTime;
    float derivative = (error - previousError) / deltaTime; 

    float smooth = previousSmooth * (T/(T + deltaTime)) + derivative * (deltaTime/(T + deltaTime));

    float output = kp * error + ki * integral + kd * /*derivative*/ smooth;
    previousError = error; 
    previousSmooth = smooth;

    return output; 
}

/*
# smooth the derivative / error.
Store 10 of the last derivatve/error, the take the avrage.

T should be 2, 5 or 10 times deltaTime. 5 is recommended

*/