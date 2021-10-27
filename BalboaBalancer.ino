#include "sensor.h"
#include <Balboa32U4.h>
#include <LSM6.h>
#include <Wire.h>
#include "pid.h"
#include "balancer.h"

Balboa32U4Buzzer buzzer;
Balboa32U4Motors motors;
Balboa32U4Encoders encoders;
Balboa32U4ButtonA button; 

const char song[] =
"!O6 T"
"l32ab-b>cl8r br b-bb-a a-r gr g-4 g4"
"a-r gr g-gg-f er e-r d4 e-4"
"gr msd8d8ml d-4d4"
"l32efg-gl8r msd8d8ml d-4d4"
"<bcd-d e-efg- ga-ab- a4 gr";

void setup() {

  Serial.begin(9600);

   
  const char *s = 
  "!L20 V10 O5 "
  "<g<g#<a<a#<bcc#dd#ef#g"
  "g#ab>c.b.a#ba#ag#."
  "g.f#.g.a.g#.gg#g"
  "f#f.e.d#.e.g.ff"
  "c#.d.g.ffc#.d.<b"
  "cc#dd#eff#gg#aba."
  "g.>c.b.a#ba#ag#.g."
  "f#.g.a.g#.gg#gf#"
  "f.e.d#.e.d#.d#d#f#."
  "<b.gagf#e.g.b."
  "bbb.b.bbbbbbb."
  ">c.b.a#ba#ag#.g."
  "f#.g.a.g#.gg#gf#f."
  "e.d#.e.g.ffc#."
  "d.g.ffc#.d.<bcc#"
  "dd#eff#gg#aba.g."
  ">c.b.a#ba#ag#.g.f#."
  "g.a.g#.gg#gf#f."
  "e.dd#.e.d#.d#d#f#.<b."
  "gagf#e.g.b.bb"
  "b.b.bbbbbbb.d."
  "dda.d.d#.d#d#a.."
  "b>d>c>cb.a.g.d."
  ">g";
  //buzzer.play(s);
  sensorSetup(); 
}

bool firstPass = true;

void loop() {
  if(button.getSingleDebouncedRelease()) {
    firstPass = false;

    drive(-300);
    delay(300);
    drive(300); 
    delay(300); 

  }

  sensorUpdate();

  if(firstPass == false) {
    float pidValue = pid(24.0f, 0.0f, 20.0f, 80.0f, getAngle(),0.1);
    drive(pidValue);
  }
  //sensorDebugPrint();

  //delay(100);
  delay(20);
}