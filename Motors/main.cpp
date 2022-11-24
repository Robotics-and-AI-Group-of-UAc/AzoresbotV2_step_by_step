#include <Arduino.h>
#include "ESP32MotorControl.h"

// Inicialização dos motores
ESP32MotorControl MotorControl = ESP32MotorControl();

void setup() {
  // 17,18,26,27 pinos dos motores no ESP32 
  // correspondentes aos motores esquerdos e direitos
  MotorControl.attachMotors(17, 18, 26, 27);
}

void loop() {  
  MotorControl.motorForward(0,50);
  MotorControl.motorForward(1,50);
  delay(5000);
  MotorControl.motorReverse(0,50);
  MotorControl.motorReverse(1,50);
  delay(5000); 
  MotorControl.motorStop(0);
  MotorControl.motorStop(1);
  delay(5000);
}
