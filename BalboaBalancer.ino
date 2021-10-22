#include <Balboa32U4.h>
#include "balancer.h"

Balboa32U4Motors motors;
Balboa32U4ButtonA startStopButton;
Balboa32U4Buzzer buzzer;
 
bool running = false; 

void setup() {
  buzzer.play("!L30 V8 cdefgab>cbagfedc");
  variables.speed.left = 100;
  variables.speed.right = 200;

}

void balance() {
  
  motors.setSpeeds(variables.speed.left, variables.speed.right); 
}

void loop() {

  if(startStopButton.isPressed()) {
    running = !running; 
  }
  if(running == false) {
    motors.setSpeeds(0, 0);
  }
  else {
    balance(); 
  }
  
  delay(2);
} 
