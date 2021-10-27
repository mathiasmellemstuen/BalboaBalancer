#ifndef BALBOA_BALANCER_SENSOR
#define BALBOA_BALANCER_SENSOR

void gyroscopeCalibration();
void accelerometerCalibration();
void sensorSetup();
void sensorUpdate();
void sensorDebugPrint(); 
int getAngle();

#endif