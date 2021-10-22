#include <Balboa32U4.h>

Balboa32U4Motors motors;
Balboa32U4ButtonA startStopButton;
Balboa32U4Buzzer buzzer;
 
bool running = false; 

void setup() {
  buzzer.play("!L30 V8 cdefgab>cbagfedc");
}

void balance() {
  
  motors.setSpeeds(150, 150); 
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
