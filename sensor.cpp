#include "sensor.h"
#include <LSM6.h>
#include <Wire.h>

int zeroValue = 0; 
int gyroScopeAngle = 0; 
char debugCharacters[80];
LSM6 imu;

void gyroscopeCalibration() {
    delay(500); // Making sure the gyroscope values is in steady state

    int total; 

    int iterations = 100; 

    for(int i = 0; i < iterations; i++) {

        imu.read(); 

        total += imu.g.y; 

        delay(1);
    }

    zeroValue = total / iterations; 
}
void sensorSetup() {

    Wire.begin();

    if(!imu.init()) {
        Serial.println("Failed to init IMU."); 
    }

    imu.enableDefault(); 
    imu.writeReg(LSM6::CTRL2_G, 0b01011000); // 208 Hz, 1000 deg/s

    gyroscopeCalibration(); 
}

void sensorUpdate() {
    imu.read();

    int angleRate = (imu.g.y - zeroValue) / 29; 
    gyroScopeAngle += angleRate;
}

void sensorDebugPrint() {
    snprintf(debugCharacters, sizeof(debugCharacters), "GYRO  y: %6d", gyroScopeAngle);
    Serial.println(debugCharacters);
}