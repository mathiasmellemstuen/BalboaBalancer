#include "sensor.h"
#include <LSM6.h>
#include <Wire.h>
#include "compimentaryFilter.h"
#include "vec3.h"

vec3<int> zeroValueAccelerometer;   // Make float?
int zeroValue = 0; 

float gyroScopeAngle;
int finalAngle;
char debugCharacters[80];
LSM6 imu;

void calibrateSensors() {
    delay(500);
    
    vec3<int> totalA;
    int totalG;

    int iterations = 100;

    for (int i = 0; i < iterations; i++) {
        imu.read();

        totalA += imu.a;
        totalG += imu.g.y;
        
        delay(1);
    }

    zeroValueAccelerometer = totalA / iterations;
    zeroValue = totalG / iterations;
}

void sensorSetup() {
    Wire.begin();

    if (!imu.init()) {
        Serial.println("Failed to init IMU."); 
    }

    imu.enableDefault(); 
    imu.writeReg(LSM6::CTRL2_G, 0b01001000); // 104 Hz, 1000 deg/s

    calibrateSensors();

    Serial.println("***Done calibrating***");
}

void sensorUpdate() {
    imu.read();

    float angleRate = (imu.g.y - zeroValue) / 29.0f; 
    
    // TODO: Just do thsi when the robot is balancing. Beacuse we do not need to recalibrate the gyro if the robot is not balancing.
    gyroScopeAngle += angleRate * 10.0f; 
    gyroScopeAngle = gyroScopeAngle * (999.0f / 1000.0f);

    vec3<int> accelerometer(imu.a.x - zeroValueAccelerometer.x,
                            imu.a.y - zeroValueAccelerometer.y,
                            imu.a.z - zeroValueAccelerometer.z);

    float R = sqrt(accelerometer.power(accelerometer, 2));
    
    float accelerometerYAngle = acos(accelerometer.z / R) * 180 / M_PI;

    Serial.print("gyro: ");
    Serial.println(gyroScopeAngle);

    // finalAngle = accelerometerYAngle;

    finalAngle = complimentaryFilter(accelerometerYAngle, gyroScopeAngle, 1, 0.95, 0.01);
    //Serial.print("Degrees: "); 
    //Serial.println(finalAngle);
}

int getAngle() {
    return finalAngle;
}
