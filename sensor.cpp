#include "sensor.h"
#include <LSM6.h>
#include <Wire.h>
#include "compimentaryFilter.h"

int zeroValue = 0; 
int zeroValueAccelerometerX = 0; 
int zeroValueAccelerometerY = 0; 
int zeroValueAccelerometerZ = 0; 

float gyroScopeAngle;
int finalAngle;
char debugCharacters[80];
LSM6 imu;

void accelerometerCalibration() {
    delay(500); // Making sure the gyroscope values is in steady state
    int totalX; 
    int totalY; 
    int totalZ; 

    int iterations = 100; 

    for(int i = 0; i < iterations; i++) {

        imu.read(); 

        totalX += imu.a.x; 
        totalY += imu.a.y; 
        totalZ += imu.a.z; 

        delay(1);
    }

    zeroValueAccelerometerX = totalX / iterations; 
    zeroValueAccelerometerY = totalY / iterations; 
    zeroValueAccelerometerZ = totalZ / iterations; 
}

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
    accelerometerCalibration();
}

void sensorUpdate() {
    imu.read();

    float angleRate = (imu.g.y - zeroValue) / 29.0f; 
    
    gyroScopeAngle += angleRate * 10.0f; 

    gyroScopeAngle = gyroScopeAngle * (999.0f / 1000.0f);

    int accelerometerX = (imu.a.x - zeroValueAccelerometerX);
    int accelerometerY = (imu.a.y - zeroValueAccelerometerY);
    int accelerometerZ = (imu.a.z - zeroValueAccelerometerZ);

    float R = sqrt(pow(accelerometerX,2) + pow(accelerometerY,2) + pow(accelerometerZ,2));
    float accelerometerYAngle = acos(accelerometerZ / R) * 180 / M_PI;

    finalAngle = complimentaryFilter(accelerometerYAngle, gyroScopeAngle, 1, 0.95, 0.01);
    Serial.print("Degrees: "); 
    Serial.println(finalAngle);
}

int getAngle() {
    return finalAngle;
}
