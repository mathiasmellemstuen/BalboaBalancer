#ifndef BALBOA_BALANCER_SENSOR
#define BALBOA_BALANCER_SENSOR

void gyroscopeCalibration();
void sensorSetup();
void sensorUpdate();
void sensorDebugPrint(); 
int getGyroscopeAngle(); 
#endif