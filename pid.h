#ifndef BALBOA_BALANCER_PID
#define BALBOA_BALANCER_PID

float previousError = 0; 
float integral = 0; 

float pid(const float& kp, const float& ki, const float& kd, const float& wantedValue, const float& sensorValue, const float& deltaTime);

#endif 