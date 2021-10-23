#include "sensor.h"
#include <Balboa32U4.h>
#include <LSM6.h>
#include <Wire.h>

Balboa32U4Motors motors;
Balboa32U4ButtonA startStopButton;
Balboa32U4Buzzer buzzer;
 
bool running = false; 

void setup() {
  buzzer.play("!L30 V8 cdefgab>cbagfedc");


  Serial.begin(9600);

  sensorSetup(); 
}

void balance() {
  
//  motors.setSpeeds(variables.speed.left, variables.speed.right); 
}


void loop() {


  sensorUpdate();


  if(startStopButton.isPressed()) {
    running = !running; 
  }
  if(running == false) {
    motors.setSpeeds(0, 0);
  }
  else {
    balance(); 
  }
  sensorDebugPrint(); 
  delay(100);
} 
